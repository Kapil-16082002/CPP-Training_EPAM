
✅The std::deque (Double Ended Queue) is a powerful container in the C++ Standard Template Library (STL) that provides dynamic arrays with efficient insertion and deletion at both ends (front and back). 
It is often used when you need a structure similar to a std::vector but with fast insertions and deletions at both ends.

Key Features of std::deque:
Dynamic array that allows insertion and removal of elements from both front and back in O(1) time complexity.
Provides random access to elements (like std::vector).
Internally allocates memory in chunks(series of memory blocks) to avoid the performance overhead of reallocating contiguous memory (unlike std::vector).
Suitable for scenarios where frequent operations at both ends (e.g., front and back) are required, while still supporting random access.

//==================================================================================================================

✅1.Internal Architecture:

Unlike:
vector → one big contiguous block
list → separate node per element

deque uses:
✅ Multiple fixed-size contiguous blocks (chunks)
✅ a map (array of pointers to blocks)

/*⚠️ This is NOT std::map.
It is simply:
✅ A dynamically allocated array of pointers
✅ Each pointer points to a memory block (chunk) i.e 👉 It stores addresses of memory blocks
*/
🔷 Memory Visualization Example

Assume:
Block size = 4
9 elements
std::deque<int> dq = {1,2,3,4,5,6,7,8,9};

🔹 Blocks in memory
Block A (address 1000)
[1][2][3][4]

Block B (address 5000)
[5][6][7][8]

Block C (address 9000)
[9][ ][ ][ ]

So the map looks like:
map (array of pointers)
Index      Contains
--------------------------------
0          pointer → Block A
1          pointer → Block B
2          pointer → Block C
3          nullptr
4          nullptr

🔷 How deque[7] Works Using Map
std::deque<int> dq = {1,2,3,4,5,6,7,8,9};
Internally:
block_size = 4
block_index = 7 / 4 = 1
offset      = 7 % 4 = 3

Then:
map[1] → Block B
Block B[3] → element 8


🔷 Important Detail
The map itself:

IS contiguous
IS dynamically allocated
Can grow if needed

If map gets full:
Allocate bigger map
Copy block pointers
Delete old map

⚠️ Only block pointers move
⚠️ Blocks themselves DO NOT move

----------------------------------------------------------------------------------------------------------------


std::deque provides O(1) (constant time) operations for both push_back/push_front and pop_back/pop_front.
This is because std::deque uses a series of memory blocks, not contiguous memory block (like std::vector),
Series of memory blocks allows efficient resizing without memory reallocation or shifting of elements.

std::deque uses a series of memory blocks(also called segments or chunks), not contiguous memory block (like std::vector). 
These chunks are dynamically allocated and are stored in differenrt(non-contiguous) memory locations.

A central map (or an array of pointers) is used to keep track of these chunks.
Each element in the map points to a chunk. 
This allows the std::deque to access elements efficiently without requiring all elements to be present in contiguous memory.

/*  
Fixed Chunk Size:
Each chunk in the std::deque is a continuous array of elements of fixed size (e.g., 512 elements for small objects), chosen based on the size of the elements and optimized for caching.
The size of a chunk is determined by implementation details and may depend on element size and the underlying hardware.
*/

✅2.Memory Allocation in std::deque

1. Initial Construction
When a std::deque is created, its internal map (a small array of pointers) is allocated, but no memory chunks are allocated yet for data storage.
Memory for data is allocated only when necessary (upon insertion of the first element).

2. On push_back() (Insertion at the Back)
✅ Case 1: If there is enough space available in the last allocated chunk:
  The element is directly added to the previous chunk in constant time (O(1)).

❌ Case 2:If there is no space in the last chunk:
  A new chunk is allocated, and its address is stored in the map. The new chunk is used to store the element.

If even the map runs out of capacity (e.g., all pointers to chunks are used):
a new (larger) array of pointers is created, and all existing pointers to the chunks are copied to the new map. 
This process is similar to how std::vector reallocates its internal storage when growing.


3. On push_front() (Insertion at the Front)
Similar to push_back() but operates at the front of the std::deque.
✅ Case 1: If there is space in the first chunk, the element is added at the front (O(1)).

❌ Case 2: If there is no space in the first chunk:
A new chunk is allocated, all elements are stored in that chunk, and its address is stored in the map at the appropriate position to handle the new "front" segment.
If the map runs out of capacity, it is reallocated similarly to handle more segments.

Time complexity: Size of 1 block = (total elements / total blocks)

Chunk Allocation Process
Allocation of chunks typically happens via an allocator (e.g., std::allocator<T>).
Allocators ensure that chunks are fetched from dynamic memory (heap), and the map is updated to include their locations.


✅Memory Deallocation in std::deque

1. On pop_back()/pop_front()
When an element is removed from the back/front:
The element is destroyed, but the segment(chunk) will not destroyed until all elements present in it are deleted.
If a chunk becomes empty (i.e., no more elements in the chunk), the chunk is returned to the allocator to free the memory, and its pointer is removed from the map.

2. Destruction of the std::deque
When a std::deque is destroyed (e.g., when it goes out of scope):
First, all elements in the deque are destroyed one by one (calling their destructors if necessary).
Next, all the chunks are deallocated by the allocator.
Finally, the map itself is destroyed (and its memory is deallocated by the system).

-------------------------------------------------------------------------------------------------------------------

✅Disadvantages of std::deque's Memory Design

1.Not Fully Contiguous:
Unlike std::vector, std::deque's segmented memory layout does not guarantee complete contiguity, which makes it less cache-friendly for certain types of algorithms that rely heavily on contiguous data.

2.Memory Overhead:
The map adds additional memory overhead as compared to std::vector, especially if there are many small chunks.

3.Middle Insertions Are Inefficient:
Inserting or deleting elements in the middle of the deque requires shifting elements and thus has a time complexity of O(n), making it unsuitable for frequent middle modifications.

//===============================================================================================================
✅Built-in Functions in std::deque
 
Function	     Theory / Description	                                 Syntax
push_back()	    Adds an element to the end of the deque.	              dq.push_back(value);
push_front()	Adds an element to the front of the deque.	              dq.push_front(value);
pop_back()	    Removes the element at the end of the deque.	          dq.pop_back();
pop_front()	    Removes the element at the front of the deque.	          dq.pop_front();
front()	        Returns reference(can modify value also) to the first element in the deque.	  T& element = dq.front();
back()	        Returns reference(can modify value also) to the last element in the deque.	   T& element = dq.back();
size()	        Returns the number of elements in the deque.	          size_t count = dq.size();
empty()	        Checks if the deque is empty; returns true if empty, false otherwise.	bool isEmpty = dq.empty();
clear()	        Removes all elements from the deque.	                  dq.clear();
at(index)	    Accesses an element at the specified position (with bounds checking).	T& element = dq.at(index);
                throws std::out_of_range exception if the index is out of range.

operator[]	    Accesses an element at the specified position (no bounds checking).	T& element = dq[index];
                accessing out-of-range indices results in undefined behavior (UB).

insert()	    Inserts elements at a specified position.	              dq.insert(iterator, value);
erase()	        Removes an element (or range of elements) from the deque.	dq.erase(iterator);
swap()	        Swaps the contents of two deques.	                       dq1.swap(dq2);
resize()	    Changes the number of elements in the deque.	           dq.resize(new_size, value);
emplace_front()	Constructs and inserts an element at the front of the deque.	 dq.emplace_front(args...);
emplace_back()	Constructs and inserts an element at the back of the deque.	     dq.emplace_back(args...);

#include <deque>
#include <iostream>
int main() {
    std::deque<int> dq = {10, 20, 30};
    // Case 1: Resize to a larger size and add a default value
    dq.resize(5);  // Output:  10 20 30 0 0 0
    dq.resize(5, 99);  // Output:  10 20 30 99 99 

    std::cout << "After resizing to larger size:\n";
    for (int x : dq) {
        std::cout << x << " ";
    }
    std::cout << "\n";

    // Case 2: Resize to a smaller size
    dq.resize(2);  // Output: 10 20
    std::cout << "After resizing to smaller size:\n";
    for (int x : dq) {
        std::cout << x << " ";
    }
    std::cout << "\n";
    return 0;
}
/* 
✅std::deque supports iterators, but std::stack and std::queue not ??
The primary goal of std::stack and std::queue is data abstraction:
Providing iterators would break the abstraction:

In stack:
Stack works as LIFO (Last In, First Out).
Allowing iteration would let users access elements in arbitrary ways, violating the LIFO structure.

In queue:
Queue works as FIFO (First In, First Out).
Iteration would similarly allow unauthorized access to elements in the queue directly instead of respecting the FIFO constraints.

*/
✅All Ways to Traverse a std::deque

✅1. Using a Range-Based For Loop (C++11 and later)
This is the simplest and most concise way to traverse a std::deque.

std::deque<int> dq = {10, 20, 30, 40, 50};
for (auto element : dq) {
    std::cout << element << " ";
}

✅2. Using a Normal for Loop with Indexing
Access elements using the [] operator or the .at() function.

std::deque<int> dq = {10, 20, 30, 40, 50};
for (size_t i = 0; i < dq.size(); ++i) {
    std::cout << dq[i] << " ";  // Using []
    // Or: std::cout << dq.at(i) << " ";
}
Note:
Use dq.at(i) if you want bounds checking. (at throws an exception if the index is out of range.)
dq[i] does not perform bounds checking.

✅3. Using Iterators
Traverse the deque using begin() and end() iterators. This gives you full control over traversal.

std::deque<int> dq = {10, 20, 30, 40, 50};
for (auto it = dq.begin(); it != dq.end(); ++it) {
    std::cout << *it << " ";
}

✅4. Using Reverse Iterators
Traverse the deque in reverse order using rbegin() and rend().

std::deque<int> dq = {10, 20, 30, 40, 50};
for (auto rit = dq.rbegin(); rit != dq.rend(); ++rit) {
    std::cout << *rit << " ";
}

✅5. Using Constant Iterators
If you only need read-only access to the deque (elements cannot be modified), use constant iterators (cbegin and cend).

std::deque<int> dq = {10, 20, 30, 40, 50};
for (auto it = dq.cbegin(); it != dq.cend(); ++it) {
    std::cout << *it << " ";
}

✅6. Using std::for_each Algorithm
Use the std::for_each algorithm from <algorithm> to traverse through the deque.
You need to pass a callable object (like a function, lambda, or functor).

#include <algorithm>
std::deque<int> dq = {10, 20, 30, 40, 50};
std::for_each(dq.begin(), dq.end(), [](int element) { 
    std::cout << element << " ";
});

✅7. Using a While Loop with Iterators
You can also manually traverse using iterators in a while loop.

std::deque<int> dq = {10, 20, 30, 40, 50};
auto it = dq.begin();
while (it != dq.end()) {
    std::cout << *it << " ";
    ++it;
}

✅8. Using Reverse Iteration with a While Loop
Similar to the above method, but traversing in reverse order.

std::deque<int> dq = {10, 20, 30, 40, 50};
auto rit = dq.rbegin();
while (rit != dq.rend()) {
    std::cout << *rit << " ";
    ++rit;
}


Application of deque:

1.Implementing Stacks
2.Implementing Queues
3.Undo/Redo Functionality
4.Real-Time Task Scheduling
5. BFS (Breadth-First Search) Implementation
6. Palindrome Checker