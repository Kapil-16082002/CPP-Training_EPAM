✅Iterator Invalidation in std::map or std::set 
When Does Iterator Invalidation Occur in std::map or std::set ?

// std::map and std::set, std::multimap and std::multiset all behaves same Iterator Invalidation
Removal of Elements (erase): 
Only the iterator pointing to the erased element becomes invalid. Iterators pointing to other elements remain valid.
Note:
Insertion of Elements (insert, emplace): Inserting elements does NOT invalidate iterators. 
Existing iterators remain valid because adding a new node to the tree does not affect the memory layout of existing nodes.

int main() {

    // Problem 1: Iterator invalidation when erasing an element
    std::cout << "\n--- Problem 1: Invalidating Iterators on Erase ---\n";
    {
        std::map<int, std::string> myMap = {{1, "one"}, {2, "two"}, {3, "three"}, {4, "four"}};

        // Get iterator pointing to the second element
        auto it = myMap.find(2); // Points to key 2

        // Erase the element with key 2
        myMap.erase(it);

        // Dereferencing the iterator after erasure causes undefined behavior
        // std::cout << "After erase: Iterator points to: " << it->first << "\n"; // Undefined behavior!

        // SOLUTION: Avoid using the iterator after erasure
        std::cout << "Valid access after erase by skipping iterator usage:\n";
        for (const auto& pair : myMap) {
            std::cout << pair.first << " -> " << pair.second << "\n";
        }
    }

    // Problem 2: Safe insertion
    std::cout << "\n--- Problem 2: Safe Insertions ---\n";
    {
        std::map<int, std::string> myMap = {{1, "one"}, {3, "three"}, {4, "four"}};

        // Get an iterator pointing to the second element
        auto it = myMap.find(3); // Points to key 3

        // Insert a new element into the map
        myMap.insert({2, "two"}); // Insert a new entry {2, "two"}

        // The insertion does NOT invalidate existing iterators
        std::cout << "After insertion: Iterator still points to key -> " << it->first << ": " << it->second << "\n";
    }

    return 0;
}
Key Notes for std::map:
Insertions are safe and do not affect existing iterators.
Erase only invalidates the iterator pointing to the erased element. Others remain valid.
