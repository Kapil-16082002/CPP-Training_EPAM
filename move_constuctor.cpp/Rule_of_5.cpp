✅The Rule of Five in C++:
The Rule of Five is an extension of the Rule of 3, introduced with C++11, which includes move semantics.

when to use: use when your class manages resources directly (e.g., dynamic memory, file handles, database connections, etc.)
then you should implement all five special member functions:

1.Destructor (~MyClass()): Cleans up resources when an object is destroyed.
2.Copy Constructor (MyClass(const MyClass&)): Creates a deep copy of the original object's resources.
3.Copy Assignment Operator (MyClass& operator=(const MyClass&)): Allows assignment between objects by properly copying resources.
4.Move Constructor (MyClass(MyClass&&)): Transfers ownership of resources from a temporary object to another, leaving the temporary in a safe state.
5.Move Assignment Operator (MyClass& operator=(MyClass&&)): Transfers ownership of resources during assignment, for cases like obj1 = std::move(obj2).


✅Why the Rule of Five Exists:
C++11 introduced move semantics, which optimize performance by avoiding unnecessary deep copies. 
Move allows to transfer ownership of a resource instead of duplicating it, hence avoiding unnecessary deep copies. 
For example:
Copying large objects (e.g., arrays or strings) using the copy constructor may involve costly memory allocation and data duplication.
but by move operations transfer ownership of resources from one object to another, avoiding expensive resource duplication and improving performance.


✅Advantages of the Rule of Five:
1.Improved Performance (Move Semantics): above content of why rule of 5.
2.prevents bugs, like double-deletes or memory leaks.
3. Safe Ownership Transfer:move constructor and move assignment operator safely transfer resources to a new owner while leaving the source object in a valid but empty state (e.g., nulling out pointers).


✅Disadvantages of the Rule of 5,3:
Direct resource management (using raw pointers) may lead to error (dangling pointer, memeory leak, double deletion etc). 
But Using RAII-compliant classes like std::unique_ptr, std::shared_ptr, or standard containers (e.g., std::vector, std::string) is preferred.


#include <iostream>
#include <utility>  // For std::move

class MyClass {
private:
    int* data;  // Pointer to a dynamically allocated resource
public:
    // Constructor
    MyClass(int value) {
        data = new int(value);  // Allocate and initialize the memory in one step
    }
    // Copy Constructor (Rule of Five)
    MyClass(const MyClass& other) {
        data = new int(*(other.data));  // Allocate and copy the value from the other object
        std::cout << "Copy Constructor called\n";
    }
    // Copy Assignment Operator (Rule of Five)
    MyClass& operator=(const MyClass& other) {
        if (this == &other) return *this;  // Self-assignment check

        delete data;               // Free existing memory
        data = new int(*(other.data));  // Allocate and copy the value
        std::cout << "Copy Assignment Operator called\n";

        return *this;
    }
    // Move Constructor (Rule of Five)
    MyClass(MyClass&& other) noexcept {
        data = other.data;
        other.data = nullptr;  // Nullify the other object's resource pointer
        std::cout << "Move Constructor called\n";
    }
    // Move Assignment Operator (Rule of Five)
    MyClass& operator=(MyClass&& other) noexcept {
        if (this == &other) return *this;  // Self-assignment check

        delete data;        // Free the current resource
        data = other.data;  // Transfer ownership of the resource
        other.data = nullptr;  // Nullify the other object's resource pointer
        std::cout << "Move Assignment Operator called\n";

        return *this;
    }

    /*  you can also write in this way: 
    // Move assignment
    LogBuffer& operator=(LogBuffer&& other) noexcept {
        std::cout << "Move assignment\n";
        data = std::move(other.data);
        return *this;
    }
    */

    // Destructor (Rule of Five)
    ~MyClass() {
        delete data;  // Free the dynamically allocated resource
        std::cout << "Destructor called\n";
    }
    void print() const {
        if (data) {
            std::cout << *data << std::endl;  // Output the value of the integer
        } 
        else {
            std::cout << "No data\n";
        }
    }
};
int main() {
    MyClass obj1(42);           // Constructor
    MyClass obj2 = obj1;        // Copy Constructor
    MyClass obj3(100);          // Constructor
    obj3 = obj2;                // Copy Assignment Operator

    MyClass obj4 = std::move(obj1);  // Move Constructor
    obj3 = std::move(obj2);          // Move Assignment Operator

    obj1.print();  // Output: No data (obj1 has been moved)
    obj2.print();  // Output: No data (obj2 has been moved)
    obj3.print();  // Output: 42
    obj4.print();  // Output: 42

    return 0;
}


// Rule of 5 code:
// #include <iostream>
// #include <utility>  // For std::move

// class MyClass {
// private:
//     int* data;  // Raw resource (dynamic memory)
// public:
//     // Constructor
//     MyClass(int value) : data(new int(value)) {
//         std::cout << "Constructor called.\n";
//     }
//     // Copy Constructor (Rule of Five)
//     MyClass(const MyClass& other) : data(new int(*other.data)) {
//         std::cout << "Copy Constructor called.\n";
//     }
//     // Copy Assignment Operator (Rule of Five)
//     MyClass& operator=(const MyClass& other) {
//         if (this == &other) return *this;  // Prevent self-assignment
//         std::cout << "Copy Assignment Operator called.\n";

//         delete data;                      // Clean up existing resource
//         data = new int(*other.data);      // Create a deep copy

//         return *this;
//     }

//     // Move Constructor (Rule of Five)
//     MyClass(MyClass&& other) noexcept : data(other.data) {
//         std::cout << "Move Constructor called.\n";
//         other.data = nullptr;             // Leave source in a valid state
//     }

//     // Move Assignment Operator (Rule of Five)
//     MyClass& operator=(MyClass&& other) noexcept {
//         if (this == &other) return *this;  // Prevent self-assignment
//         std::cout << "Move Assignment Operator called.\n";

//         delete data;                      // Clean up existing resource
//         data = other.data;                // Transfer ownership
//         other.data = nullptr;             // Leave source in a valid state

//         return *this;
//     }

//     // Destructor (Rule of Five)
//     ~MyClass() {
//         delete data;  // Release dynamic memory
//         std::cout << "Destructor called.\n";
//     }

//     void print() const { std::cout << "Value: " << *data << '\n'; }
// };

// int main() {
//     MyClass obj1(42);       // Constructor
//     MyClass obj2 = obj1;    // Copy Constructor
//     MyClass obj3(17);       // Constructor
//     obj3 = obj1;            // Copy Assignment Operator

//     MyClass obj4 = std::move(obj1);  // Move Constructor
//     obj3 = std::move(obj4);          // Move Assignment Operator

//     return 0;  // Destructor called for all objects
// }
