
✅A stack in C++ STL is a container adaptor designed on the principle of Last-In-First-Out (LIFO) manner.
This means the last element added to the stack will be the one removed first.
//Container adapter does not provide new container but modify the interface of existing container to provide specific functionalities.
The std::stack is built on top of other containers such as std::deque, std::vector, or std::list.
By default, std::deque is used as the underlying container.


🔹 Template Syntax:
The general syntax for specifying a std::stack is:
std::stack<T, Container>
Where:
  T is the type of elements stored in the stack.
  Container is the underlying container type (default: std::deque<T>).

By default, std::deque is used as the underlying container for std::stack.
You can also specify std::vector or std::list as the underlying container. For example:

std::stack<int> myStack;  // default: std::deque<T>
std::stack<int, std::vector<int>> myStack; // by modifying the interface of vector, we wil get stack
std::stack<int, std::list<int>> myStack;   // by modifying the interface of vector, we wil get stack

/*
What Does a std::stack Require from Its Underlying Container?
push: Adding elements to the top of the stack.
pop: Removing elements from the top of the stack.
These operations must be efficient, ideally in constant time (O(1)).

✅Why Is std::deque the Default?
Efficient Push/Pop at Back:
std::deque provides O(1) (constant time) operations for both push_back (equivalent to stack::push) and pop_back (equivalent to stack::pop).
This is because std::deque uses a series of memory blocks, not contiguous memory block (like std::vector), 
Series of memory blocks allows efficient resizing without memory reallocation or shifting of elements.

1. Contiguous Memory Block:
single continuous memory blocks without any gaps.
The memory locations are adjacent, with sequential addresses.
Advantages:
Faster access times due to spatial locality (data elements are located close to one another).
Simplifies pointer arithmetic, as all elements are in a sequential array-like structure.
Disadvantages:
If a large contiguous block of memory is required, it may not always be available, even if enough free memory exists (due to fragmentation).
Example:
Allocating an array: int arr[5]; is a contiguous memory block where all 5 integers are stored in adjacent memory locations.

2. Series of Memory Blocks:
A series of memory blocks refers to multiple distinct blocks of memory that may or may not be physically adjacent to each other in the address space. 
These blocks are logically linked or used together but are spread across different parts of memory.
Characteristics:
Data does not need to be stored sequentially in memory.
Logical connection among different blocks is typically maintained through pointers or references.
Advantages:
More flexible and dynamic memory allocation compared to contiguous memory.
Useful in situations where contiguous memory is unavailable due to fragmentation.
Suitable for complex data structures like linked lists, trees, and graphs.
Disadvantages:
Slower access times, as elements are scattered, leading to poor spatial locality.
Overhead of memory management, such as keeping track of multiple memory blocks and maintaining links/pointers.
Example:
A linked list, where each node contains a pointer to the next node, and nodes are located at different memory addresses.


✅Why Isn't std::vector the Default?
The std::vector is designed for contiguous memory storage and random access, which are features not particularly useful for a stack. 
While std::vector can be used as the underlying container for std::stack, it has some limitations:
Inefficient Growth for Push Operations:
When a std::vector runs out of allocated memory, it needs to allocate a new, larger contiguous memory block and copy all existing elements into the new memory block. 
This results in a time complexity of O(n) for such push_back operations in the worst case.

*/



✅ In-Built Functions Provided by std::stack

Time complexity of all functions: O(1) in all best,Average,Worst if std::deque as container

Member Function	       Time(std::vector)                   Description
push(const T& value) 	 O(1),O(1),O(n)  Pushes (inserts) an element onto the top of the stack.
pop()	                O(1),O(1),O(1)    Removes the element at the top of the stack (but does not return it).
top()	              O(1),O(1),O(1)       Returns a reference to the top element of the stack (does not remove it).
empty()	               O(1),O(1),O(1)      Returns true if the stack is empty, otherwise false.
size()	               O(1),O(1),O(1)      Returns the number of elements in the stack.
emplace(args...)	    O(1),O(1),O(n)    Constructs and inserts an element at the top of the stack in-place (more efficient).
emplace allows you to construct the element directly in the stack (avoiding an additional copy).

swap(stack s)	O(n),O(n),O(n)  Swaps the contents of two stacks (requires both have the same underlying container type and size).
#include <iostream>
#include <stack>
int main() {
    std::stack<int> stack1, stack2;

    stack1.push(1); // Push elements onto both stacks
    stack1.push(2);

    stack2.push(10);
    stack2.push(20);
    stack2.push(30);

    stack1.swap(stack2);// Swap the contents of stack1 and stack2

    std::cout << "Contents of stack1 after swap: ";
    while (!stack1.empty()) {
        std::cout << stack1.top() << " ";
        stack1.pop();
    }
    return 0;
}
Output:
Contents of stack1 after swap: 30 20 10


✅Complete Code for std::stack
#include <iostream>
#include <stack> 

int main() {
    // Create a stack of integers
    std::stack<int> stk;


    stk.push(10);  // Adds 10
    stk.push(20);  // Adds 20
    stk.push(30);  // Adds 30
    stk.push(40);  // Adds 40

    // 2. Display the size of the stack
    std::cout << "Size of stack: " << stk.size() << std::endl; // Should print 4

    // 3. Access the top element
    std::cout << "Top element: " << stk.top() << std::endl; // Should print 40

    // 4. Remove elements using pop()
    stk.pop(); // Removes 40

    // Check the new size and top element
    std::cout << "New size of stack: " << stk.size() << std::endl; // Should print 3
    std::cout << "New top element: " << stk.top() << std::endl; // Should print 30

    // 5. Check if the stack is empty
    if (stk.empty()) {
        std::cout << "The stack is empty." << std::endl;
    } else {
        std::cout << "The stack is not empty." << std::endl; // Should print "not empty"
    }

    // 6. Swap two stacks
    std::stack<int> stk2;
    stk2.push(100); // Adds 100 to second stack
    stk2.push(200);
    stk2.push(300);

    std::cout << "\nSwapping stacks..." << std::endl;

    // Swap stk and stk2
    stk.swap(stk2);

    // After swapping, stk should now have the contents of stk2
    std::cout << "After swapping, size of first stack: " << stk.size() << std::endl; // Should print 3
    std::cout << "Top element of first stack after swapping: " << stk.top() << std::endl; // Should print 300

    // 7. Clear the swapped stack by popping all elements
    while (!stk.empty()) {
        std::cout << "Popping element: " << stk.top() << std::endl; // Print and remove top element
        stk.pop();
    }

    // Verify if the stack is now empty
    if (stk.empty()) {
        std::cout << "The stack is empty after clearing!" << std::endl;
    } else {
        std::cout << "The stack is not empty after clearing!" << std::endl;
    }

    return 0;
}



//----------------------------------------------------------------------------------------------------------------

✅Differences Between push and emplace
push:
It inserts a copy (or move) of an existing object into the container.
You need to first construct the object and then pass it to the container for insertion (e.g., myStack.push(obj)).
This involves either a copy operation or a move operation, which could potentially result in an additional performance overhead.

emplace:
It constructs the object in-place directly inside the container using the provided arguments.
This avoids the creation of a temporary object and eliminates the need for a separate copy or move operation.
Therefore, emplace is usually more efficient than push, especially for objects that are expensive to move or copy.

✅🔸 Code Examples for push and emplace
Example 1: Using push
#include <iostream>
#include <stack>
#include <string>

class MyClass {
public:
    MyClass(std::string name, int value) : name(name), value(value) {
        std::cout << "Constructor called for " << name << "\n";
    }
    MyClass(const MyClass& other) {
        std::cout << "Copy Constructor called for " << other.name << "\n";
        name = other.name;
        value = other.value;
    }
    void print() const {
        std::cout << "Name: " << name << ", Value: " << value << "\n";
    }
private:
    std::string name;
    int value;
};
int main() {
    std::stack<MyClass> myStack;

    // Create an object first
    MyClass obj1("Object1", 10);
    
    // Push object to the stack
    myStack.push(obj1); // Copy constructor is called here!

    // Push a temporary object (rvalue)
    myStack.push(MyClass("Object2", 20)); // Constructor and Move/Copy constructor are called

    // Access the top element
    myStack.top().print();

    return 0;
}
Output:
Constructor called for Object1
Copy Constructor called for Object1
Constructor called for Object2
Name: Object2, Value: 20

In this example:
An object is constructed outside of the stack (obj1).
When using push, a copy of the object is created and inserted into the stack.
For temporary objects (rvalues), the constructor is called, followed by a potential move or copy operation.


✅Example 2: Using emplace
#include <iostream>
#include <stack>
#include <string>
class MyClass {
public:
    MyClass(std::string name, int value) : name(name), value(value) {
        std::cout << "Constructor called for " << name << "\n";
    }
    void print() const {
        std::cout << "Name: " << name << ", Value: " << value << "\n";
    }
private:
    std::string name;
    int value;
};
int main() {
    std::stack<MyClass> myStack;

    // Use emplace to construct an object directly in the stack
    myStack.emplace("Object1", 10); // Constructor called directly in-place
    myStack.emplace("Object2", 20); // Constructor called directly in-place

    // Access the top element
    myStack.top().print();

    return 0;
}
Output:
Constructor called for Object1
Constructor called for Object2
Name: Object2, Value: 20
In this example:

Unlike push, we pass the constructor arguments directly to emplace, and the object is constructed directly inside the stack.
There are no copies or moves involved, making emplace more efficient for complex objects.

✅🔸 When to Use?
Use push:
When you already have the object created.
When the construction of the object is trivial.

Use emplace:
When you want to construct objects directly within the container.
When dealing with complex objects or objects that are expensive to copy/move

Conclusion:
emplace is generally more efficient than push because it avoids temporary object creation and copying/moving.
However, in simple cases where you already have an object, push is perfectly fine.

//----------------------------------------------------------------------------------------------------------------

✅Use Cases of Stack:
1. Undo and Redo Operations (in Text Editors or IDEs):
 Undo(Ctrl + Z): returning the document or application to its previous state
 Redo(Ctrl + Y): returning the document or application to the next state it was in after the original action

When typing or editing text, actions are pushed onto a stack. 
"Undo" pops the last action while "Redo" re-applies it by pushing it back.

2.Function Call Stack (Recursion)
Every time a function is called, its execution information (parameters, local variables, etc.) is pushed onto the stack. 
When the function returns, its data is popped off the stack.

3.Browser History Navigation:
Scenario: When you navigate web pages, each visited page is pushed onto the stack. 
Clicking "Back" pops the latest page, and clicking "Forward" re-applies the page (using another stack).

4.Backtracking in Algorithms (e.g., Maze Solving, Searching):
While exploring paths in a maze, you push possible paths onto a stack and backtrack by popping paths when a dead-end is encountered.
Use DFS to traverse a graph.

5.Loading bullets into the magazine of a gun. The last one inserted will be fired first. 