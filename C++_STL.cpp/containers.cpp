The C++ Standard Template Library (STL) is a powerful collection of C++ template-based classes and predefined functions that provide generic, reusable implementations for some common programming data structures and algorithms. 
✅Advantages of STL:
Code Reusability: Predefined templates save time and effort.
Efficiency: STL containers and algorithms are optimized for performance.
Generic Programming: You can work with any data types due to STL template-based nature.
Consistency: Iterators and algorithms provide a consistent interface for many data structures.


✅Components of STL:
STL is mainly divided into four components:
1. Containers
2. Algorithms
3. Iterators
4. Functions

✅Types of STL Containers

1.Sequence Containers
2.Associative Containers
3.Non-Associative(Unordered) Containers
4.Container Adapters
//-----------------------------------------------------------------------------------------------------------------
1. Sequence Containers
Sequence containers store elements in a sequence order. They are optimized for sequential access.
1.std::vector
2.std::deque
3.std::list
4.std::forward_list (C++11)
5.std::array
//-----------------------------------------------------------------------------------------------------------------
2. Associative Containers
These store data elements in the form of key-value pairs and automatically arrange them in a sorted order based on the keys. 
They use tree-based data structures (typically red-black trees).
Types of Associative Containers:
1.std::set:
2.std::multiset
3.std::map
4.std::multimap
//---------------------------------------------------------------------------------------------------------------

3. Unordered Associative Containers (C++11+)
These are similar to associative containers but do not store elements in sorted order. 
Instead, they use hash tables for faster lookup, insertion, and deletion (average O(1) complexity).
Types of Unordered Associative Containers:
1.std::unordered_set
2.std::unordered_multiset
3.std::unordered_map
4.std::unordered_multimap

//----------------------------------------------------------------------------------------------------------------
4. Container Adaptors
Container adapters does not provide new containers but modify the interface of existing containers to provide specific functionalities.
Types:
1.std::stack
2.std::queue
3.std::priority_queue

/* 
5. Specialized Containers (total 2)
These are containers with specific use cases.
1.std::bitset
2.std::span (introduced in C++20)
*/



