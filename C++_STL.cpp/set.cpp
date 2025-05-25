✅Differences Between Containers
Container	            Duplicacy	 Ordering	Underlying Data Str. Performance
std::set	            No	         Sorted	     Red-Black Tree	      O(log(n)) for insert/find/delete
std::unordered_set	    No	         Unordered	 Hash Table	          O(1) average, O(n) worst-case for insert/find/delete
std::multiset	        Yes	         Sorted	     Red-Black Tree       O(log(n)) for insert/find/delete
std::unordered_multiset	Yes	         Unordered	 Hash Table	          O(1) average, O(n) worst-case for insert/find/delete

✅When to Use Which Container
Use std::set When:
No duplicate elements are required.
You need elements to remain sorted.
You plan to perform range queries (e.g., lower_bound/upper_bound).

✅Use std::unordered_set When:
No duplicate elements are required.
You care more about fast insertion/lookups (O(1) average) rather than ordering.
Handling large datasets with frequent operations.

✅Use std::multiset When:
Duplicate elements are allowed.
Sorting of elements is required.

✅Use std::unordered_multiset When:
Duplicate elements are allowed.
Sorting is not required, but fast lookups and insertions are necessary.

✅Internal Structures
1. std::set and std::multiset:
Red-Black Tree is used internally.
Elements are stored based on increasing order (or custom comparator, if provided).
For example: {1, 3, 5} is automatically sorted.
Operations like insertion, deletion, and searching take ( O(\log(n)) ) time.

✅2. std::unordered_set and std::unordered_multiset:
Hash Table is used internally.
Hash-based storage ensures ( O(1) ) time complexity for most operations on average, but collisions can result in ( O(n) ) complexity in the worst case.
The order of elements is not guaranteed and depends on the hash function distribution.


✅Traversal in Sets
1. Using Iterators
int main() {
    std::set<int> s = {1, 3, 5};
    for (auto it = s.begin(); it != s.end(); ++it) {
        std::cout << *it << "\n"; // Accessing each element
    }
    return 0;
}
Output:
1
3
5

✅2. Using Range-based for Loop
int main() {
    std::unordered_set<int> uset = {3, 1, 5};
    for (auto it : uset) {
        std::cout << it << "\n"; // Accessing each element
    }
    return 0;
}
Output (Order May Vary):
3
1
5

✅3. Using Reverse Iterators (Only for(ordered)std::map,std::multimap, std::set and std::multiset):
Reverse iteration is not supported by std::unordered_set, std::unordered_map, std::unordered_multiset, or std::unordered_multimap 
because these containers don’t maintain a specific ordering of their elements.
If reverse iteration is required for unordered containers, you can copy the elements into a sequential container (like std::vector) and perform reverse iteration there.

std::vector supports reverse iteration.
Since std::vector is a sequential container that stores elements in contiguous memory, you can iterate over its elements in reverse order using reverse iterators.

Explore above part more??
int main() {
    std::set<int> s = {1, 3, 5};
    for (auto it = s.rbegin(); it != s.rend(); ++it) {
        std::cout << *it << "\n"; // Accessing elements in reverse order
    }

    return 0;
}
Output:
5
3
1


✅Common Member Functions
1. size()
Returns the total number of elements in the container.
int main() {
    std::set<int> s = {1, 2, 3};
    std::cout << "Size of the set: " << s.size() << '\n'; // Output: 3
    return 0;
}
✅2. empty()
Returns true if the container is empty, and false otherwise.
int main() {
    std::unordered_set<int> uset;
    std::cout << "Is the unordered_set empty? " << (uset.empty() ? "Yes" : "No") << '\n'; // Output: Yes

    uset.insert(1);
    std::cout << "Is the unordered_set empty now? " << (uset.empty() ? "Yes" : "No") << '\n'; // Output: No

    return 0;
}

✅3. clear()
Removes all elements from the container.
int main() {
    std::set<int> s = {1, 2, 3};
    std::cout << "Size before clear: " << s.size() << '\n';
    s.clear();
    std::cout << "Size after clear: " << s.size() << '\n';
    return 0;
}

✅4. insert()
Adds an element to the container. For:
std::set or std::unordered_set: Duplicate elements will be ignored.
std::multiset or std::unordered_multiset: Duplicate elements will be stored.

int main() {
    std::multiset<int> ms;
    ms.insert(1);
    ms.insert(1); // Duplicate allowed in multiset
    ms.insert(2);

    for (auto i : ms) {
        std::cout << i << " ";
    }
    return 0;
}
Output:
1 1 2

✅5. find()
Finds an element in the container and returns an iterator pointing to it. 
If the element is not present, it returns end().

int main() {
    std::set<int> s = {1, 2, 3};
    auto it = s.find(2); // Find element 2

    if (it != s.end()) {
        std::cout << "Found: " << *it << '\n';
    } else {
        std::cout << "Not Found\n";
    }
    return 0;
}

✅6. count()
Returns the number of occurrences of an element:
For std::set/std::unordered_set: The result will be either 0 or 1.
For std::multiset/std::unordered_multiset: Might return more than 1.

int main() {
    std::multiset<int> ms = {1, 1, 2, 3};

    std::cout << "Count of 1: " << ms.count(1) << '\n'; // Output: 2
    std::cout << "Count of 3: " << ms.count(3) << '\n'; // Output: 1
    return 0;
}

✅7. equal_range()
Returns the range of elements matching the given value in a std::multiset or std::set.
int main() {
    std::multiset<int> ms = {1, 1, 2, 3};

    auto range = ms.equal_range(1);
    for (auto it = range.first; it != range.second; ++it) {
        std::cout << *it << " ";
    }
    return 0;
}
Output:
1 1


✅Special Functions for unordered_set and unordered_multiset
1. bucket_count()
Get the number of buckets in the container.

int main() {
    std::unordered_set<int> uset = {1, 2, 3};
    std::cout << "Number of buckets: " << uset.bucket_count() << '\n';
    return 0;
}
2. load_factor()
Returns the average number of elements per bucket.

3. rehash(n)
Increases the number of buckets to at least n.
int main() {
    std::unordered_set<int> uset = {1, 2, 3};
    uset.rehash(10); // Increase the number of buckets
    std::cout << "Number of buckets after rehash: " << uset.bucket_count() << '\n';
    return 0;
}


1. erase()
Overview:
The erase() function removes elements from the container.
For std::set and std::unordered_set: Removes the key if it exists. 
Returns 1 if the element was removed and 0 otherwise (since duplicates are not allowed).

For std::multiset and std::unordered_multiset: Removes all occurrences of the key. 
Returns the number of elements removed.

int main() {
    // Example for std::set
    std::set<int> s = {1, 2, 3, 4};
    s.erase(2); // Erase element 2
    for (auto num : s) {
        std::cout << num << " "; // Output: 1 3 4
    }
    std::cout << "\n";

    // Example for std::multiset
    std::multiset<int> ms = {1, 1, 2, 3};
    ms.erase(1); // Erase all occurrences of 1
    for (auto num : ms) {
        std::cout << num << " "; // Output: 2 3
    }
    return 0;
}
Output:
1 3 4
2 3

✅2. operator[]
Overview:
operator[] is only available for containers like std::map and std::unordered_map where elements are stored as key-value pairs.
NOT AVAILABLE in std::set, std::unordered_set, std::multiset, or std::unordered_multiset. 
In contrast, set-based containers do not have key-value pairs—they only hold values.
Attempting to use operator[] in set-based containers will result in a compiler error.

✅3. lower_bound(key) and upper_bound(key)
Overview:
lower_bound(key):
Returns an iterator to the first element that is not less than key (>= key).
If no such element exists, it returns end().

upper_bound(key):
Returns an iterator to the first element that is greater than key (> key).
If no such element exists, it returns end().

Supported Containers:
lower_bound and upper_bound are supported in std::set and std::multiset because they are sorted containers.

NOT AVAILABLE in std::unordered_set and std::unordered_multiset 
because these containers are unordered and do not have meaningful "bounds."
int main() {
    std::set<int> s = {10, 20, 30, 40};

    // lower_bound example
    auto lb = s.lower_bound(25); // First element not less than 25
    if (lb != s.end())
        std::cout << "Lower bound of 25: " << *lb << "\n"; // Output: 30
    else
        std::cout << "Lower bound not found\n";

    // upper_bound example
    auto ub = s.upper_bound(20); // First element greater than 20
    if (ub != s.end())
        std::cout << "Upper bound of 20: " << *ub << "\n"; // Output: 30
    else
        std::cout << "Upper bound not found\n";

    return 0;
}
Output:
Lower bound of 25: 30
Upper bound of 20: 30

For std::multiset:
In std::multiset, lower_bound() returns the first occurrence of an element that is >= key, 
while upper_bound() skips all duplicate occurrences of the same key.

int main() {
    std::multiset<int> ms = {10, 20, 20, 30, 40};

    // lower_bound example
    auto lb = ms.lower_bound(20); // Points to the first 20
    if (lb != ms.end())
        std::cout << "Lower bound of 20: " << *lb << "\n"; // Output: 20

    // upper_bound example
    auto ub = ms.upper_bound(20); // Points to 30 (skips all duplicates of 20)
    if (ub != ms.end())
        std::cout << "Upper bound of 20: " << *ub << "\n"; // Output: 30

    return 0;
}
Output:
Lower bound of 20: 20
Upper bound of 20: 30

Key Notes for lower_bound and upper_bound:
Unordered Containers (std::unordered_set and std::unordered_multiset):
These functions are not available because the elements are not sorted.
Sorted Containers (std::set and std::multiset):
These bounds are useful for range-based queries.
