Exception safety guarantee in C++ refers to a set of programming guidelines and guarantees that ensures that if an exception is thrown an object's or application's behavior remains well-defined and consistent.
These guarantees are designed to maintain program correctness, resource management, and data consistency.

In C++, exception safety guarantees are typically classified into three levels of guarantees (or four, including one for functions with no exceptions). Here's an explanation of each level of guarantee:

1. No-Throw Guarantee (Strongest):
A function that provides this guarantee will never throw an exception. 
It is also referred to as the noexcept guarantee because functions marked with noexcept in C++ explicitly promise not to throw exceptions.

Characteristics:
The function guarantees it will neither throw an exception nor leave the program in an unexpected state.
Frequently used in destructors, smart pointer reset operations, low-level utilities, etc.
Any operation that throws an exception would either fail to compile or would invoke std::terminate() (in case of noexcept).

#include <iostream>
#include <vector>

void noThrowFunc() noexcept {
    // This function guarantees it won't throw an exception.
    std::cout << "No exception will be thrown here.\n";
}
int main() {
    try {
        noThrowFunc();
    } catch (...) {
        std::cout << "This will never execute because noThrowFunc is noexcept.\n";
    }
    return 0;
}
If an exception ever emanates from a noexcept function, the program will call std::terminate().

//------------------------------------------------------------------------------------------------------------------

2. Strong Guarantee:
A function providing the strong guarantee ensures that, in case of an exception, the program’s state is completely unchanged (rollback semantics). 
Either the operation completes successfully, or the program state is restored to what it was before the operation began.
Example : Transaction

Characteristics:
Provides transactional behavior: "all or nothing."
Requires special care to implement, such as relying on copy-and-swap idioms or resource management patterns like RAII (Resource Acquisition Is Initialization).
Often involves making a copy of data before modifications, so changes can be discarded if an exception occurs.

#include <iostream>
#include <vector>

class Test {
public:
    void addToVector(std::vector<int>& vec, int value) {
        // Strong exception safety using a temporary for rollback
        std::vector<int> temp = vec;  // Create a copy
        temp.push_back(value);        // Modify the copy
        vec = std::move(temp);        // Commit changes
    }
};
int main() {
    std::vector<int> vec = {1, 2, 3};
    Test t;

    try {
        t.addToVector(vec, 4); // Push back successfully
        std::cout << "Vector after change: ";
        for (int v : vec) std::cout << v << " ";
    } catch (...) {
        // If an exception is thrown, vec will remain unchanged.
        std::cout << "\nException occurred. State is unchanged.";
    }

    return 0;
}
Here, if push_back(value) throws an exception, the original vector remains unchanged because of the use of a temporary copy.

//--------------------------------------------------------------------------------------------------------------

3. Basic Guarantee:
A function providing the basic guarantee ensures that if an exception is thrown, the program:

Does not leak resources (such as dynamic memory, open files, etc.).
Remains in a valid (but not necessarily unchanged) state.
This means that the program would not crash or exhibit undefined behavior, but the program state may be altered and partially completed.

#include <iostream>
#include <vector>

class SafeVector {
private:
    std::vector<int> vec;
public:
    void addElement(int value) {
        vec.push_back(value); // Exception might occur (e.g., during memory allocation).
    }
    void print() const {
        std::cout << "Vector contents: ";
        for (int v : vec) std::cout << v << " ";
        std::cout << "\n";
    }
};
int main() {
    SafeVector sv;

    try {
        sv.addElement(10);
        sv.addElement(20); // If this throws, previous state ("10") is valid.
    } catch (...) {
        std::cout << "Exception occurred. Vector remains valid but may be altered.\n";
    }

    sv.print();
    return 0;
}
If an exception occurs during addElement, the vector remains in a valid state (e.g., no memory leaks), but its content may be partially complete.

4. No Guarantee (Weakest):
A function or operation providing no guarantee makes no promises about the effect of an exception. 
The program state after an exception is thrown may be undefined, leading to bugs, memory leaks, or crashes.

This level is unacceptable for robust programs and should be avoided. However, functions providing no guarantee might still be usable in highly specific or low-requirement contexts.


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Techniques to Achieve Exception Safety:

1.RAII (Resource Acquisition Is Initialization):

Use RAII objects to manage resources (e.g., std::unique_ptr, std::vector).
They automatically release resources during stack unwinding if an exception is thrown.
Example:

void example() {
    std::unique_ptr<int> ptr(new int(42)); // No leaks if an exception occurs
    throw std::runtime_error("Error!");
}

2.Copy-and-Swap Idiom:
Perform mutations on a copy. If the mutation is successful, swap the temporary object with the original.

3.Avoid Raw Memory Management:
Use smart pointers (e.g., std::unique_ptr, std::shared_ptr) instead of raw pointers.
noexcept:

Mark functions as\][ ] noexcept if you are confident that they would not throw. 
This prevents exceptions in critical operations like destructors or move operations.
Example Code Illustrating All Guarantees:

#include <iostream>
#include <vector>
#include <stdexcept>

class Example {
private:
    std::vector<int> vec;
public:
    // No-Throw Guarantee: Destructor
    ~Example() noexcept {
        std::cout << "Destructor called. Resource cleanup guaranteed.\n";
    }

    // Basic Guarantee
    void addElement(int value) {
        vec.push_back(value);  // Exception safety with basic guarantee (e.g., might throw on memory allocation failure).
    }

    // Strong Guarantee
    void addElementSafely(int value) {
        std::vector<int> temp = vec;  // Make a copy for safety
        temp.push_back(value);
        vec = std::move(temp);        // Commit only after success
    }
    void print() const {
        for (int v : vec) std::cout << v << " ";
        std::cout << "\n";
    }
};
int main() {
    try {
        Example ex;
        ex.addElement(10);
        ex.addElementSafely(20); // Strong guarantee
        ex.print();
    } catch (...) {
        std::cerr << "Exception occurred.\n";
    }

    return 0;
}