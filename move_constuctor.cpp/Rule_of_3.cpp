✅The Rule of 3 in C++:
The Rule of 3 is a design principle.
If you implement any one of the three special member functions (copy constructor, copy assignment operator, or destructor), you should implement all three.
If you only implement one or two but depend on the compiler-generated versions for the others, then risk of memory leaks, or undefined behavior.
The Rule of Three is a design principle in C++ that applies when your class manages resources directly (e.g., dynamic memory, file handles, database connections, etc.)


✅Special Member Functions in Rule of 3:

1.Destructor (~ClassName()): Cleans up resources when an object is destroyed (e.g., freeing memory, closing files).
2.Copy Constructor (ClassName(const ClassName&)): Defines how an object is copied during construction (deep copy for resources like memory or file handles).
3.Copy Assignment Operator (ClassName& operator=(const ClassName&)): Defines how an object is copied during assignment (again, deep copy if needed).


✅Why Is the Rule of 3 Important?:
If you do not implement these special member functions explicitly, the compiler will generate default versions.
The compiler-generated versions use shallow copying for pointers, resulting in sharing pointers between objects. 
If one object is destroyed, the pointer could become dangling, causing undefined behavior.


✅Advantages of the Rule of 3:

1.Ensures deep copies are created for dynamically allocated resources, avoiding issues like dangling pointers or double deletions.
2.Prevents memory and resource leaks.
3.Debugging Easy: Having explicit implementations for these functions allows tracking and debugging resource management issues more easily than relying on compiler-generated behavior.

✅Disadvantages of the Rule of 3:
1.Requires implementing all three functions even if only one is needed.
2.Poor implementations of the copy constructor or assignment operator can lead tobugs like partial copying, resource leaks, or undefined behavior.
3. Explicit copying may be more expensive than other modern approaches (e.g., move semantics, smart pointers).

#include <iostream>

class MyClass {
private:
    int* data;  // Pointer to a dynamically allocated resource
public:
    // Constructor
    MyClass(int value) {
        data = new int(value);  // Allocate and initialize the memory in one step
    }
    // Copy Constructor (Rule of Three)
    MyClass(const MyClass& other) {
        data = new int(*(other.data));  // Allocate memory and copy the value
    }
    // Copy Assignment Operator (Rule of Three)
    MyClass& operator=(const MyClass& other) {
        if (this == &other) return *this;  // Prevent self-assignment
        delete data;               // Release the current memory
        data = new int(*(other.data));  // Allocate new memory and copy the value
        return *this;
    }
    // Destructor (Rule of Three)
    ~MyClass() {
        delete data;  // Free the dynamically allocated memory
    }
    void print() const {
        std::cout << *data << std::endl;  // Output the value of the integer
    }
};

int main() {
    MyClass obj1(42);    // Initialize with an integer value
    MyClass obj2 = obj1; // Copy constructor
    MyClass obj3(100);   // Initialize with a different integer
    obj3 = obj2;         // Copy assignment operator

    obj1.print();  // Output: 42
    obj2.print();  // Output: 42
    obj3.print();  // Output: 42

    return 0;
}

// #include <iostream>
// #include <cstring>

// class MyClass {
// private:
//     char* data;  // Pointer to a dynamically allocated resource
// public:
//     // Constructor
//     MyClass(const char* str) {
//         data = new char[std::strlen(str) + 1];  // Allocate memory
//         std::strcpy(data, str);                // Copy string into allocated memory
//     }
//     // Copy Constructor (Rule of Three)
//     MyClass(const MyClass& other) {
//         data = new char[std::strlen(other.data) + 1];  // Allocate new memory
//         std::strcpy(data, other.data);                // Copy data from other
//     }
//     // Copy Assignment Operator (Rule of Three)
//     MyClass& operator=(const MyClass& other) {
//         if (this == &other) return *this;  // Prevent self-assignment

//         delete[] data;    // Release current resource
//         data = new char[std::strlen(other.data) + 1];  // Allocate new memory
//         std::strcpy(data, other.data);  // Copy data from other

//         return *this;
//     }
//     // Destructor (Rule of Three)
//     ~MyClass() {
//         delete[] data;  // Free memory when the object is destroyed
//     }
//     void print() const {
//         std::cout << data << std::endl;
//     }
// };
// int main() {
//     MyClass obj1("Hello");
//     MyClass obj2 = obj1; // Uses copy constructor
//     MyClass obj3("World");
//     obj3 = obj2; // Uses copy assignment operator

//     obj1.print();  // Output: Hello
//     obj2.print();  // Output: Hello
//     obj3.print();  // Output: Hello

//     return 0;
// }

