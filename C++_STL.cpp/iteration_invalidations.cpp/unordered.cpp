✅Iterator Invalidations in Unordered Containers

//All unordered containers (std::unordered_map, std::unordered_set, std::unordered_multimap, std::unordered_multiset) follow the same rules for iterator invalidation.

Key Scenarios for Iterator Invalidations in Unordered Containers:
1.Reallocation due to size growth:
If the container must increase its underlying bucket array (when the load factor exceeds a threshold), all iterators are invalidated.

2.Element removal (erase):
Only the iterator to the erased element is invalidated; other iterators remain valid.

int main() {

    // Problem 1: Iterator invalidation due to reallocation
    std::cout << "\n--- Problem 1: Invalidating Iterators on Reallocation ---\n";
    {
        std::unordered_map<int, std::string> umap = {{1, "one"}, {2, "two"}, {3, "three"}};

        // Get an iterator to the second element
        auto it = umap.find(2); // Points to key 2

        // Insert enough elements to trigger reallocation
        for (int i = 4; i <= 100; i++) {
            umap[i] = "value" + std::to_string(i);
        }
        // Dereferencing the old iterator causes undefined behavior after reallocation
        // std::cout << "Iterator pointing to invalid spot: " << it->first << "\n"; // Undefined behavior

        // SOLUTION: Avoid using iterators after reallocation; refresh iterators
        it = umap.find(2); // Re-acquire a valid iterator
        std::cout << "Safe access after reallocation: " << it->first << " -> " << it->second << "\n";
    }

    // Problem 2: Iterator invalidation on element removal
    std::cout << "\n--- Problem 2: Invalidating Iterators on Erase ---\n";
    {
        std::unordered_map<int, std::string> umap = {{1, "one"}, {2, "two"}, {3, "three"}};

        // Get an iterator to the second element
        auto it = umap.find(2); // Points to key 2

        // Erase the element with key 2
        umap.erase(it);

        // Dereferencing the iterator causes undefined behavior
        // std::cout << "Iterator pointing to invalid spot: " << it->first << "\n"; // Undefined behavior

        // SOLUTION: Avoid using iterators after erase; find the next valid element
        for (const auto& pair : umap) {
            std::cout << pair.first << " -> " << pair.second << "\n";
        }
    }

    return 0;
}
