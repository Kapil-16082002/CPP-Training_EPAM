✅The std::deque (Double Ended Queue) is a powerful container in the C++ Standard Template Library (STL) that provides dynamic arrays with efficient insertion and deletion at both ends (front and back). 
It is often used when you need a structure similar to a std::vector but with fast insertions and deletions at both ends.

Key Features of std::deque:
Dynamic array that allows insertion and removal of elements from both front and back in O(1) time complexity.
Provides random access to elements (like std::vector).
Internally allocates memory in chunks(series of memory blocks) to avoid the performance overhead of reallocating contiguous memory (unlike std::vector).
Suitable for scenarios where frequent operations at both ends (e.g., front and back) are required, while still supporting random access.

✅Built-in Functions in std::deque

 
Function	     Theory / Description	                                   Syntax
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
operator[]	    Accesses an element at the specified position (no bounds checking).	T& element = dq[index];
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

