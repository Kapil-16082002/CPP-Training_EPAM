
✅std::unordered_map and std::map are two widely used associative containers in C++ STL (Standard Template Library). 
Their primary purpose is to store key-value pairs.

✅When to Use std::map vs std::unordered_map
1.Use std::map when:
You need the keys to remain sorted.
You plan to perform range queries (e.g., lower_bound/upper_bound).
The dataset is relatively small, or you require predictable log-time performance.

2.Use std::unordered_map when:
You care more about speed and less about ordering.
Handling large datasets with frequent insertions and lookups.
You want average case O(1) performance for lookups instead of O(log(n)).


/*
✅Internal Structure of std::map:

1. Elements in std::map are stored in dynamically allocated tree nodes in the form of std::pair<key,value>pair.
2. Each tree node is Linked via parent/left/right pointers
3.There is no array, no contiguous block.
struct Node {
    std::pair<const Key, T> data;
    Node* left;
    Node* right;
    Node* parent;
    bool color; // red or black
};
🔷 Memory Layout Visualization
Suppose:
mp[20] = "A";
mp[10] = "B";
mp[30] = "C";
Internally:
        (20,A)
        /     \
   (10,B)    (30,C)


std::map uses a Red-Black Tree, which is a type of self-balancing binary search tree (BST).
Red-Black Tree ensures that:
1. Tree remains approximately balanced after each insert, delete, or update operation, 
2. Guarantee a worst-case time complexity of O(log n) for search, insertion, and deletion operations.
3. Data will be sorted


Each node in the Red-Black Tree stores a key-value pair (std::pair<Key, Value>), where:
Key: The identifier by which the value can be accessed.
Value: The data associated with the key.
Nodes in the tree are arranged based on the sorted order of their keys.

✅Operations in std::map:
1.Insertion: ( O(\log N) )
Place the element in the correct position in the Red-Black Tree.
If the key already exists, std::map does not insert duplicates.

2.Search (find): ( O(\log N) )
Start from the root and navigate left or right based on key comparison until you find the key or hit a leaf.

3.Deletion: ( O(\log N) )
Locate the key in the tree and perform removal, rebalancing the Red-Black Tree afterward.

✅Main Properties of a Red-Black Tree:
1.Each node is either red or black.
2.The root node must be black.
3.Red nodes cannot have red children (no two consecutive red nodes).
4.Leaf nodes (NULL pointers) are always black.
5.Every path from a node to its descendant NULL pointers (leaves) must contain the same number of black nodes.

Applications:
The red-black tree is widely used in applications such as database systems, compiler design, and associative containers in the STL(e.g., std::map and std::set in C++).


🔷 Why Not Just Normal BST?
If data is sorted, Normal BST can become right-skewed BST:

1
 \
  2
   \
    3
     \
      4
Height becomes O(n) → bad performance. Search = O(n) ❌

Red-Black Tree ensures: Height ≤ 2 * log2(n+1)
So operations stay O(log n).



🔷 Why Not Use Array?

If std::map used an array:
Insertion would require shifting elements → O(n)
Deletion → O(n)
Not efficient.


//==================================================================================================================

Internal Structure of std::unordered_map:
Data Structure: It uses a Hash Table.
A hash table consists of an array of buckets.
A bucket typically implemented as linked list or a dynamic array to store multiple key-value pairs when hash collisions occur.
Each key is processed through a hash function and a hash value is generated and that hash value is an index for that bucket within the hash table.
The key-value pair is stored in the bucket at the resulting index.
If more than one key hashes to the same bucket (a collision), the bucket may use a chain (e.g., a linked list) to hold key-value pairs.

Hash Function:
Converts the key into an integer(hash value), which acts as the index in the array of buckets.
Default hash function is provided (e.g., std::hash<Key>) but you can supply a custom one.

Bucket Collision:
If two different keys after passing through Hash Function have same hash value (bucket collision).
The keys are chained together into that bucket via a linked list or other collision resolution mechanisms (typically chaining is used in std::unordered_map).


🔷 Main Collision Resolution Techniques:
There are two major categories:
✅ 1. Separate Chaining
✅ 2. Open Addressing
🔸 (a) Linear Probing
🔸 (b) Quadratic Probing
🔸 (c) Double Hashing

*/

✅Traverse in std::map and std::unordered_map
1. Using Iterators:
int main() {
    std::map<int, std::string> m = {{1, "one"}, {2, "two"}, {3, "three"}};

    std::cout << "Traversing using iterators:\n";
    for (auto it = m.begin(); it != m.end(); ++it) {
        std::cout << it->first << ": " << it->second << "\n"; // Accessing key and value
    }
    /*  Traversing from end
    for (auto it = m.rbegin(); it != m.rend(); ++it) {
        std::cout << it->first << ": " << it->second << "\n"; // Accessing key and value
    }
    Output:
    3: three
    2: two
    1: one
    */
}
Output:
1: one
2: two
3: three

2. Using Range-based for Loop
int main() {
    std::map<int, std::string> m = {{1, "one"}, {2, "two"}, {3, "three"}};

    std::cout << "Traversing std::map using range-based for loop:\n";
    for (auto& it : m) {
        std::cout << it.first << ": " << it.second << "\n"; // Accessing key-value pair directly
    }
    return 0;
}
Output:
1: one
2: two
3: three

3. Using Reverse Iterators (rbegin, rend)
For std::unordered_map:
Note: Reverse iterators are not supported for unordered containers because they are not ordered.

For std::map:
Reverse iterators start from the largest key and go to the smallest.

---------------------------------------------------------------------------------------------------------------

✅Member Functions
1. size()
Returns the total number of elements currently stored in the container.
int main() {
    std::map<int, std::string> m;
    m[1] = "one";
    m[2] = "two";
    m[3] = "three";
    std::cout << "Size of the map: " << m.size() << '\n'; // Output: 3
    return 0;
}
-------------------------------------------------------------------------------------------------------------------
✅2. empty()
Checks if the container is empty.
Returns true if empty, false otherwise.
int main() {
    std::unordered_map<int, std::string> um;
    std::cout << "Is unordered_map empty? " << (um.empty() ? "Yes" : "No") << '\n'; // Output: Yes
    
    um[1] = "one";
    
    std::cout << "Is unordered_map empty? " << (um.empty() ? "Yes" : "No") << '\n'; // Output: No
    return 0;
}
------------------------------------------------------------------------------------------------------------------
✅3. clear()
Removes all elements from the container. 
The size becomes zero.

int main() {
    std::map<int, std::string> m;
    m[1] = "one";
    m[2] = "two";
    std::cout << "Size before clear: " << m.size() << '\n'; // Output: 2
    m.clear();
    std::cout << "Size after clear: " << m.size() << '\n';  // Output: 0
    return 0;
}
-----------------------------------------------------------------------------------------------------------------
✅4. max_size()
Returns the maximum number of elements the container can theoretically hold (depends on the system and memory constraints).

int main() {
    std::unordered_map<int, std::string> um;
    std::cout << "Maximum size of unordered_map: " << um.max_size() << '\n';
    return 0;
}
------------------------------------------------------------------------------------------------------------------
Element Access
✅5. operator[]
Retrieves the value associated with the given key.
If the key does not exist, it inserts the key with a default value and then returns the default value.
In case of:
string -> will give empty string.
int -> will give 0
char-> empty char

int main() {
    std::map<int, std::string> m;

    m[1] = "one"; // Insert using operator[]
    std::cout << m[1] << '\n'; // Output: one
    std::cout << m[2] << '\n'; // Default value: empty string because key 2 doesn't exist
    cout<<m.size(); // 2 , now map size will be 2;
    return 0;
}
------------------------------------------------------------------------------------------------------------------
✅6. at(key)
Provides access to the value associated with the given key.
This function throws std::out_of_range exception if the key is not present.

int main() {
    std::map<int, std::string> m;
    m[1] = "one";
    std::cout << m.at(1) << '\n';  // Output: one

    try {
        std::cout << m.at(2) << '\n'; // Throws exception because key 2 doesn't exist
    } catch (std::out_of_range &e) {
        std::cout << e.what() << '\n'; // Shows error message
    }
    return 0;
}
------------------------------------------------------------------------------------------------------------------
Modifiers
✅7. insert()
Inserts a pair of key-value into the container.
If the key already exists, the insertion fails.

Return type:
1️⃣ Insert single element: auto res = m.insert({3, "three"}); 
👉 Return type:
std::pair<iterator, bool>
Meaning:
iterator → points to element
bool → true if inserted, false if key already exists


2️⃣ If Insert multiple element:  auto res = m.insert({{3, "three"}, {4, "four"}, {5, "five"}});
👉 Return type = void

🔥Why does single insert return pair but initializer_list returns void?
Because:
1. If we insert Multiple elements,then multiple return type are possible.
Example: If you insert 10,000 elements, then:
C++ standard should Allocate 10,000 result pairs and then all pairs have to store in vactor of pairs or other container.
👉That would results in :
Increase complexity
Increase memory overhead
Complicate interface

2. If we insert Single elemnts
🔹 Did insertion happen?
🔹 Where is the element located?
So it returns: std::pair<iterator, bool>


int main() {
    std::map<int, std::string> m;

    //m.insert({{3, "three"}, {4, "four"}, {5, "five"}});
    //m.insert(std::make_pair(1, "one"));
    //for(auto it:m) cout<<it.first<<" "<<it.second<<endl; 

    // Insert using make_pair
    auto result = m.insert(std::make_pair(1, "one"));
    std::cout << "Key: " << result.first->first << ", Value: " << result.first->second << '\n';
    std::cout << "Insertion " << (result.second ? "succeeded" : "failed") << '\n'; // Output: succeeded

    // Try inserting a duplicate key
    result = m.insert(std::make_pair(1, "ONE"));
    std::cout << "Insertion " << (result.second ? "succeeded" : "failed") << '\n'; // Output: failed

    return 0;
}
------------------------------------------------------------------------------------------------------------------
✅8. emplace()
Similar to insert(), but constructs the pair in place instead of copying.

int main() {
    std::map<int, std::string> m;
    m.emplace(1, "one");   // Emplace a value
    for (auto &pair : m) { 
        std::cout << pair.first << ": " << pair.second << '\n';
    }
}
------------------------------------------------------------------------------------------------------------------
9✅. erase(key)
Removes an element by its key.
If the key does not exist, nothing happens.
int main() {
    std::map<int, std::string> m;
    m[1] = "one";
    m[2] = "two";
    // Erase key 2
    m.erase(2);
}
------------------------------------------------------------------------------------------------------------------
✅. lower_bound(key) and upper_bound(key)
No, lower_bound and upper_bound do not work for std::unordered_map.

1. lower_bound(key): Returns an iterator pointing to the first element GREATER THAN or EQUAL to given key  (>= key).
If no such element exists (i.e., the key is greater than all keys in the map), it returns m.end(), which is an iterator past the last element of the map.
Accessing m.end() leads to undefined behavior if you try to dereference it.

2. upper_bound(key):
Returns an iterator pointing to the first element GREATER THAN the given key (> key).
If no such element exists (i.e., the key is the largest or greater than all keys in the map), it also returns m.end().
Accessing m.end() leads to undefined behavior if you try to dereference it.

std::map<int, std::string> m;
m[2] = "two";
m[3] = "three";
//m[4] = "four";
m[5] = "five";
std::cout << "Lower bound of 1: " << m.lower_bound(1)->second << '\n'; // Output: two
std::cout << "Upper bound of 1: " << m.upper_bound(1)->second << '\n'; // Output: two

std::cout << "Lower bound of 2: " << m.lower_bound(2)->second << '\n'; // Output: two
std::cout << "Upper bound of 2: " << m.upper_bound(2)->second << '\n'; // Output: three

std::cout << "Lower bound of 3: " << m.lower_bound(3)->second << '\n'; // Output: three
std::cout << "Upper bound of 3: " << m.upper_bound(3)->second << '\n'; // Output: five

std::cout << "Lower bound of 5: " << m.lower_bound(5)->second << '\n'; // Output: five
std::cout << "Upper bound of 5: " << m.upper_bound(5)->second << '\n'; // Output: unexpected value

std::cout << "Lower bound of 6: " << m.lower_bound(6)->second << '\n'; // Output: unexpected value
std::cout << "Upper bound of 6: " << m.upper_bound(6)->second << '\n'; // Output: unexpected value

-------------------------------------------------------------------------------------------------------------------
✅10. swap()
Exchanges the content between two containers.
int main() {
    std::unordered_map<int, std::string> um1;
    std::unordered_map<int, std::string> um2;

    um1[1] = "one";
    um2[2] = "two";

    std::cout << "Before swap:\n";
    std::cout << "um1 size: " << um1.size() << ", um2 size: " << um2.size() << '\n'; // 1, 1

    um1.swap(um2);

    std::cout << "After swap:\n";
    std::cout << "um1 size: " << um1.size() << ", um2 size: " << um2.size() << '\n'; // 1, 1
    return 0;
}
------------------------------------------------------------------------------------------------------------------
✅11. find(key)
Returns an iterator pointing to the element if found; otherwise it returns end().
int main() {
    std::unordered_map<int, std::string> um;
    um[1] = "one";

    auto it = um.find(1);
    if (it != um.end()) {
        std::cout << "Found key 1: " << it->second << '\n';
    } else {
        std::cout << "Key 1 not found.\n";
    }

    return 0;
}
------------------------------------------------------------------------------------------------------------------
✅12. count(key)
Returns the number of elements matching the given key:
std::map always returns 0 or 1 (only one unique key in std::map).
std::multimap may return >1 if the key is stored multiple times.

int main() {
    std::map<int, std::string> m;

    m[1] = "one";

    std::cout << "Count of key 1: " << m.count(1) << '\n'; // Output: 1
    std::cout << "Count of key 2: " << m.count(2) << '\n'; // Output: 0

    return 0;
}
------------------------------------------------------------------------------------------------------------------
✅13. equal_range(key)
Returns a pair of iterators representing the range for elements matching the key.
For std::map, this range will include either one or zero elements.

#include <iostream>
#include <map>

int main() {
    std::map<int, std::string> m;
    m[1] = "one";
    m[2] = "two";

    auto range = m.equal_range(1);

    if (range.first != range.second) {
        std::cout << "Found key 1: " << range.first->second << '\n';
    } else {
        std::cout << "Key 1 not found.\n";
    }
    return 0;
}
//===============================      multimap    ====================================================================


✅The main difference between non-multi(std::map and std::unordered_map) is that multimap and unordered_multimap allow duplicate keys.

✅std::multimap
A std::multimap is an associative container that allows multiple values with the same key. 
It keeps elements stored in sorted order by key.
Underlying Data Structure -> Balanced Binary Search Tree (e.g., Red-Black Tree).


✅std::unordered_multimap
A std::unordered_multimap is an associative container that allows multiple elements with the same key but does not maintain any ordering of the keys. 
It offers faster insertions and lookups on average because of its hash-table-based structure.
Underlying Data Structure -> Hash Table.


✅Why operator[] and at() are not supported in std::multimap:
std::multimap Characteristics:
A std::multimap is a sorted associative container that allows multiple elements with the same key.
Since multiple values can exist for the same key, it is ambiguous what operator[] or at() should return for such keys. 
These functions are designed for containers where the key is unique (like std::map).
If you attempt to access elements of a std::multimap using [] or at(), you will get a compiler error, as these functions are not defined for std::multimap.

✅How to Access Elements in a std::multimap
✅1. Using for loop with an iterator
The most basic method to iterate through a std::multimap is by using iterators in a for loop.
int main() {
    std::multimap<int, std::string> mmap = {{1, "A"}, {2, "B"}, {2, "C"}, {3, "D"}};
    // Iterator method
    for (std::multimap<int, std::string>::iterator it = mmap.begin(); it != mmap.end(); ++it) {
        std::cout << "Key: " << it->first << ", Value: " << it->second << '\n';
    }
    return 0;
}
------------------------------------------------------------------------------------------------------------------

✅2. Using Range-based for loop
C++11 introduced range-based for loops, which simplify the syntax.
int main() {
    std::multimap<int, std::string> mmap = {{1, "A"}, {2, "B"}, {2, "C"}, {3, "D"}};
    // Range-based for loop
    for (const auto& entry : mmap) {
        std::cout << "Key: " << entry.first << ", Value: " << entry.second << '\n';
    }
    return 0;
}
-----------------------------------------------------------------------------------------------------------------

✅3. Using std::for_each with Lambda (C++11 and newer)
You can use the std::for_each algorithm with a lambda function for iteration.
int main() {
    std::multimap<int, std::string> mmap = {{1, "A"}, {2, "B"}, {2, "C"}, {3, "D"}};
    // std::for_each with a lambda
    std::for_each(mmap.begin(), mmap.end(), [](const std::pair<int, std::string>& entry) {
        std::cout << "Key: " << entry.first << ", Value: " << entry.second << '\n';
    });
    return 0;
}
------------------------------------------------------------------------------------------------------------------

✅4. Using Reverse Iteration
To iterate in reverse, you can use rbegin() and rend() with a loop.
int main() {
    std::multimap<int, std::string> mmap = {{1, "A"}, {2, "B"}, {2, "C"}, {3, "D"}};
    // Reverse iteration
    for (std::multimap<int, std::string>::reverse_iterator rit = mmap.rbegin(); rit != mmap.rend(); ++rit) {
        std::cout << "Key: " << rit->first << ", Value: " << rit->second << '\n';
    }
    return 0;
}
-------------------------------------------------------------------------------------------------------------------

✅5. Using std::multimap::equal_range for Keys
auto range = mmap.equal_range(key);
is used to retrieve all the elements in the std::multimap that contains the same key 'key'.

What equal_range(key) Does:
returns a pair of iterators ,std::pair<std::multimap::iterator, std::multimap::iterator>.
These two iterators define the range of elements that have the given key.

range.first: An iterator pointing to the first element in the multimap with the key given 'key' (or an iterator to the first element that is greater than key if no such key exists).
range.second: An iterator pointing to the position just past the last element with the key given'key'.

int main() {
    std::multimap<int, std::string> mmap = {{1, "A"}, {2, "B"}, {2, "C"}, {3, "D"}};
    int key = 2;  // Example key
    /*
    cout << mmap.count(2); // 2
    int count = distance(range.first, range.second); // 2 

    int count = 0;
    for (auto it = range.first; it != range.second; ++it)   count++;  // 2

    */
    auto range = mmap.equal_range(key);

    for (auto it = range.first; it != range.second; ++it) {
        std::cout << "Key: " << it->first << ", Value: " << it->second << '\n';
    }
}
-------------------------------------------------------------------------------------------------------------------

✅6. Using std::find_if with Lambda
To find and iterate over specific elements matching a condition, use the std::find_if algorithm.
int main() {
    std::multimap<int, std::string> mmap = {{1, "A"}, {2, "B"}, {2, "C"}, {3, "D"}};

    // Use std::find_if to find a pair where value = "C"
    auto it = std::find_if(mmap.begin(), mmap.end(), [](const std::pair<int, std::string>& entry) {
        return entry.second == "C";
    });
    if (it != mmap.end()) {
        std::cout << "Found: Key: " << it->first << ", Value: " << it->second << '\n';
    }

    return 0;
}
------------------------------------------------------------------------------------------------------------------

✅7. Using std::multimap::count and std::multimap::find
Another technique for iteration over specific keys is using the count and find methods.
int main() {
    std::multimap<int, std::string> mmap = {{1, "A"}, {2, "B"}, {2, "C"}, {3, "D"}};

    // Iterate over a specific key
    int key = 2;
    auto it = mmap.find(key);
    int count = mmap.count(key);  // Number of elements with the given key

    for (int i = 0; i < count; ++i, ++it) {
        std::cout << "Key: " << it->first << ", Value: " << it->second << '\n';
    }

    return 0;
}
//===============================================================================================================

✅Commonly Used Member Functions:
1. insert()
Inserts a key-value pair into the container.
Duplicate keys are automatically allowed.
int main() {
    std::multimap<int, std::string> mmap;
    mmap.insert({1, "one"});
    mmap.insert({1, "uno"});  // Duplicate key

    for (auto& pair : mmap) {
        std::cout << pair.first << ": " << pair.second << '\n';
    }
    return 0;
}
Output:
1: one
1: uno

-------------------------------------------------------------------------------------------------------------------
✅2. find()
Finds one instance of a given key and returns an iterator pointing to it.
For duplicate keys, it may return any one instance.
#include <iostream>
#include <map>

int main() {
    std::multimap<int, std::string> mmap = {{1, "one"}, {1, "uno"}};

    auto it = mmap.find(1);
    if (it != mmap.end()) {
        std::cout << "Found " << it->first << ": " << it->second << '\n';
    } else {
        std::cout << "Key not found!\n";
    }

    return 0;
}
Output:
Found 1: one

-------------------------------------------------------------------------------------------------------------------

✅3. count(key)
Returns the number of elements with the given key.
int main() {
    std::multimap<int, std::string> mmap = {{1, "one"}, {1, "uno"}, {2, "two"}};

    std::cout << "Count of key 1: " << mmap.count(1) << '\n';
    std::cout << "Count of key 2: " << mmap.count(2) << '\n';

    return 0;
}
Output:
Count of key 1: 2
Count of key 2: 1

-------------------------------------------------------------------------------------------------------------------

✅4. equal_range(key)
Returns a range of iterators (pair of begin and end) corresponding to all elements with the given key.
Useful for traversing all values of a given key.
int main() {
    std::multimap<int, std::string> mmap = {{1, "one"}, {1, "uno"}, {2, "two"}};

    std::cout << "Elements with key 1:\n";
    auto range = mmap.equal_range(1); // Gets all elements with key 1
    for (auto it = range.first; it != range.second; ++it) {
        std::cout << it->first << ": " << it->second << '\n';
    }
    return 0;
}
Output:
Elements with key 1:
1: one
1: uno

-------------------------------------------------------------------------------------------------------------------
✅5. erase(key)
Removes all elements with the given key.

int main() {
    std::unordered_multimap<int, std::string> ummap = {{1, "one"}, {1, "uno"}, {2, "two"}};

    ummap.erase(1);  // Erase all elements with key 1

    for (auto& pair : ummap) {
        std::cout << pair.first << ": " << pair.second << '\n';
    }
    return 0;
}
Output:
2: two

-----------------------------------------------------------------------------------------------------------------

✅6. Using Iterators (begin(), end())
Both containers support traversal using iterators.
With std::multimap: Iterates in sorted order.
With std::unordered_multimap: Iterates in arbitrary order.


✅Other Key Functions in std::multimap and std::unordered_multimap
Function	Description
insert(iter, {key, value})	Inserts an element with a hint at a specific position.
empty()	Returns true if the container is empty, otherwise false.
size()	Returns the number of elements in the container.
max_size()	Returns the maximum number of elements the container can hold (depends on memory).
clear()	Clears all elements in the container.

(map1).swap(map2);	Swaps the content of two containers.
bucket_count() (unordered)	Returns the number of buckets in the hash table (specific to unordered_multimap).
load_factor() (unordered)	Returns the average number of elements per bucket (specific to unordered_multimap).
rehash(n) (unordered)	Resizes the hash table to have at least n buckets, reducing collisions (specific to unordered_multimap).

✅. bucket_count()
Returns the number of buckets currently in the hash table. 
A bucket is where elements are stored based on their hash.
int main() {
    std::unordered_multimap<int, std::string> umap = {{1, "one"}, {2, "two"}, {1, "uno"}};

    std::cout << "Number of buckets: " << umap.bucket_count() << '\n';

    // Display elements in each bucket
    for (size_t i = 0; i < umap.bucket_count(); ++i) {
        std::cout << "Bucket " << i << " contains: ";
        for (auto it = umap.begin(i); it != umap.end(i); ++it) {
            std::cout << "{" << it->first << ": " << it->second << "} ";
        }
        std::cout << '\n';
    }
    return 0;
}
Output:
Number of buckets: 5
Bucket 0 contains: 
Bucket 1 contains: {1: one} {1: uno} 
Bucket 2 contains: {2: two} 
Bucket 3 contains: 
Bucket 4 contains:


✅. load_factor()
Returns the average number of elements per bucket.
A smaller load factor ensures fewer collisions and hence better performance.
int main() {
    std::unordered_multimap<int, std::string> umap = {{1, "one"}, {2, "two"}, {1, "uno"}};

    std::cout << "Number of elements: " << umap.size() << '\n';
    std::cout << "Number of buckets: " << umap.bucket_count() << '\n';
    std::cout << "Load factor: " << umap.load_factor() << '\n';
    return 0;
}
Output:
Number of elements: 3
Number of buckets: 5
Load factor: 0.6


✅. rehash(n)
rehash(n) increases the number of buckets to at least n.
This minimizes collisions if the container becomes too full, improving lookup and insertion performance.

int main() {
    std::unordered_multimap<int, std::string> umap = {{1, "one"}, {2, "two"}, {3, "three"}, {4, "four"}, {5, "five"}};

    std::cout << "Before rehash:\n";
    std::cout << "Number of elements: " << umap.size() << '\n';
    std::cout << "Number of buckets: " << umap.bucket_count() << '\n';
    std::cout << "Load factor: " << umap.load_factor() << '\n';

    // Rehash to 10 buckets
    umap.rehash(10);

    std::cout << "\nAfter rehash:\n";
    std::cout << "Number of elements: " << umap.size() << '\n';
    std::cout << "Number of buckets: " << umap.bucket_count() << '\n';
    std::cout << "Load factor: " << umap.load_factor() << '\n';
    return 0;
}
Output:
Before rehash:
Number of elements: 5
Number of buckets: 7
Load factor: 0.714286

After rehash:
Number of elements: 5
Number of buckets: 10
Load factor: 0.5


Comparison of Time Complexities
Function	      std::map	    std::unordered_map	    std::multimap
Constructor      	O(1)	     O(1)	                  O(1)

Access & Lookup			
m[key]	         O(log n)	O(1) average, O(n) worst	   O(log n)
m.at(key)	O(log n)	O(1) average, O(n) worst	       O(log n)
m.find(key)	O(log n)	O(1) average, O(n) worst	       O(log n)
m.count(key)	O(log n)	O(1) average, O(n) worst	   O(log n)
m.equal_range(key)	O(log n)	O(1) average, O(n) worst	O(log n + k)` (k = count of key)

Insertions			
m.insert(pair)	O(log n)	O(1) average, O(n) worst	    O(log n)
m.emplace(...)	O(log n)	O(1) average, O(n) worst	    O(log n)
m.insert_or_assign(...)	O(log n)	O(1) average, O(n) worst	N/A
m[key] = value	O(log n)	O(1) average, O(n) worst	        N/A

Deletions			
m.erase(key)	   O(log n)	O(1) average, O(n) worst	    O(log n + k)` (for all duplicates)
m.erase(iterator)	O(1)	O(1)	O(1)
m.clear()	O(n)	O(n)	O(n)

Iteration			
Iterating (e.g., begin() to end())	O(n) traversal	O(n) traversal	O(n) traversal

Capacity			
m.empty()	O(1)	O(1)	O(1)
m.size()	O(1)	O(1)	O(1)

Bucket-Related Operations (for Unordered Maps)	N/A		N/A
m.bucket_count()	N/A	O(1)	N/A
m.load_factor()	N/A	O(1)	N/A
m.max_load_factor()	N/A	O(1)	N/A
m.rehash(buckets)	N/A	O(n)	N/A

Miscellaneous			
m.swap(m2)	O(1)	O(1)	O(1)
