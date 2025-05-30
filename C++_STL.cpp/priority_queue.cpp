✅A priority queue in C++ STL is a container adaptor that provides constant-time retrieval of the largest (or smallest) element, 
while insertion and deletion take logarithmic time. 
Specifically, it’s implemented as a max-heap or min-heap, depending on the comparison function used.


In C++ Standard Template Library (STL), the priority_queue class is implemented using a heap data structure. 
Specifically, it uses a binary heap (a complete binary tree) to store the elements efficiently.


By default, std::priority_queue uses a std::vector as its underlying container to store the elements.
Internally, the elements in the vector are arranged in the form of a binary heap using the heap algorithms provided by STL (e.g., std::make_heap, std::push_heap, and std::pop_heap).


C++ STL provides the std::priority_queue container to implement priority queues.
✅Types of Priority Queues:

1.Max-Heap (Default):
Returns the largest element as the top of the priority queue.
This is the default behavior of std::priority_queue.

2.Min-Heap:
Returns the smallest element as the top of the priority queue.
This can be achieved by providing a custom comparison function.

✅Syntax:
std::priority_queue<value_type> pq;  // Max-Heap by default

std::priority_queue<value_type, container_type, comparison_function> pq; // Custom behavior such as Min-Heap
Parameters
value_type: The type of elements stored in the priority queue (e.g., int, float, std::pair, etc.).
container_type: The underlying container that stores elements. By default, it is std::vector (usually std::deque for other adapters like queue).
comparison_function: A binary predicate used for custom comparison of elements (e.g., std::less for max-heap, std::greater for min-heap).

✅Built-in Functions of std::priority_queue
Function	Description	                                                                     Syntax
empty()	  Checks whether the priority queue is empty. Returns true if empty, else false.	 pq.empty()
size()	  Returns the number of elements in the priority queue.	                             pq.size()
push(const value_type& val)	Inserts an element into the priority queue.	                     pq.push(val)
emplace(args...)	Constructs an element in-place and inserts it into the priority queue.	  pq.emplace(args...)
top()	  Returns a reference to the largest (or smallest in min-heap) element of the priority queue.	pq.top()
pop()	  Removes the top element from the priority queue.	                            pq.pop()
swap(priority_queue& other) 	Swaps the contents of one priority queue with another.	pq1.swap(pq2)

✅Custom Comparator with a Min-Heap (Struct or Lambda)
To use a custom comparator, you can use a struct or a lambda function.

1.Comparator Using a Free Function(Function Pointers:)
You can define a free-standing function and use its address as the custom comparator.

#include <iostream>
#include <queue>
#include <vector>
// Free-standing comparison function
bool customComparator(int left, int right) {
    return left > right; // Min-Heap
}
int main() {
    std::priority_queue<int, std::vector<int>, decltype(&customComparator)> minHeap(customComparator);
/*
decltype(customComparator) also work fine because it is also treated as a function pointer type bool (*)(int, int) by compiler.
decltype(customComparator) will give the same result as decltype(&customComparator) — the function pointer type.

decltype(&customComparator) : a function pointer type bool (*)(int, int).
decltype is a C++ feature that determines the type of an expression at compile time.
&customComparator takes the address of the function, and its type is bool (*)(int, int) (a pointer to a function taking two int arguments and returning a bool).

minHeap(customComparator): explicitly passes the function pointer instance to the priority_queue's constructor because it knows which comparator to use for comparing elements.   

*What Happens If You Directly Pass cmp Without Using decltype?
The Compare parameter expects a type, not an object or instance
This will not work because cmp refers to the instance of the lambda (i.e., its object), not its type. 
The std::priority_queue template requires the type of the comparator to be known at compile-time.

*/
    minHeap.push(30);
    minHeap.push(10);
    minHeap.push(20);
    std::cout << "Min-Heap elements: ";
    while (!minHeap.empty()) {
        std::cout << minHeap.top() << " ";
        minHeap.pop();
    }
    return 0;
}
//-----------------------------------------------------------------------------------------------------------------
2.Using a Lambda Function:
#include <iostream>
#include <queue>
using namespace std;

int main() {
    auto cmp = [](int left, int right) { return left > right; }; // Min-Heap
    priority_queue<int, vector<int>, decltype(cmp)> mini_pq(cmp);

    mini_pq.push(10);
    mini_pq.push(30);
    mini_pq.push(20);
    cout << "Custom Min-Heap with Lambda:\n";
    while (!mini_pq.empty()) {
        cout << mini_pq.top() << " ";
        mini_pq.pop();
    }
    return 0;
}
//---------------------------------------------------------------------------------------------------------------
3.Using a Struct:
#include <iostream>
#include <queue>
using namespace std;

struct Compare {
    bool operator()(int a, int b) {
        return a > b; // Min-Heap (small element first)
    }
};
/*  
✅Why operator()?
In C++, overloading operator() allows objects to behave like functions. These objects are called functors or function objects
std::priority_queue requires a callable comparator to decide the priority of elements. 
By implementing operator() in the comparator, the object becomes callable and satisfies this requirement.
Important:
operator() is invoked internally by the std::priority_queue. You never call it directly in your code. It essentially makes the MinHeapComparator object behave like a function.

Example: How operator() Works in Your Code
When you execute the following code:

std::priority_queue<int, std::vector<int>, MinHeapComparator> minHeap;
minHeap.push(30);
minHeap.push(10);
minHeap.push(20);
1. Initially, 30 is pushed into the heap.
2. Next, when 10 is inserted, the std::priority_queue will compare 30 and 10 using MinHeapComparator::operator():

MinHeapComparator comparator;
comparator(30, 10); // Returns true because 30 > 10.
Since the comparator returns true, 10 is placed above 30 in the heap, as 10 has a higher priority (smaller value).

3. When 20 is added, the comparator will be used multiple times to adjust the heap structure:

comparator(30, 20); // Returns true because 30 > 20.
comparator(10, 20); // Returns false because 10 < 20.
The final heap structure ensures that the smallest value (10) is at the top.


*/
int main() {
    priority_queue<int, vector<int>, Compare> customMinHeap;

    customMinHeap.push(10);
    customMinHeap.push(30);
    customMinHeap.push(20);

    cout << "Custom Min-Heap:\n";
    while (!customMinHeap.empty()) {
        cout << customMinHeap.top() << " ";
        customMinHeap.pop();
    }
    return 0;
}

//-----------------------------------------------------------------------------------------------------------------
4.Comparator for Multiple Conditions (Custom Struct or Lambda)
You can write a comparator to account for multiple conditions. 
Useful when sorting involves multiple criteria (e.g., lexicographically, or nested field comparisons).
#include <iostream>
#include <queue>
#include <vector>
#include <string>

// Struct for complex data
struct Item {
    int priority;
    std::string name;
};
// Custom Comparator
struct ItemComparator {
    bool operator()(const Item& a, const Item& b) {
        // Min-Heap based on priority, then lexicographically by name
        if (a.priority == b.priority) {
            return a.name > b.name; // Lexicographic comparison
        }
        return a.priority > b.priority;  // Compare by priority
    }
};
int main() {
    std::priority_queue<Item, std::vector<Item>, ItemComparator> minHeap;

    // Push elements into the heap
    minHeap.push({2, "Alice"});
    minHeap.push({1, "Bob"});
    minHeap.push({1, "Charlie"});

    std::cout << "Min-Heap with complex struct:\n";
    while (!minHeap.empty()) {
        auto top = minHeap.top();
        std::cout << "Priority: " << top.priority << ", Name: " << top.name << "\n";
        minHeap.pop();
    }
    return 0;
}
Output:
Min-Heap with complex struct:
Priority: 1, Name: Bob
Priority: 1, Name: Charlie
Priority: 2, Name: Alice