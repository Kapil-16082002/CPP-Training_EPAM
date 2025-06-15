Exception safety guarantee in C++ refers to a set of programming guidelines and guarantees that ensures that if an exception is thrown an object or application behavior remains well-defined and consistent.
These guarantees are designed to maintain program correctness, resource management, and data consistency.

In C++, exception safety guarantees are typically classified into three levels of guarantees (or four, including one for functions with no exceptions).
Here's an explanation of each level of guarantee:

1. No-Throw Guarantee (Strongest):
A function that provides this guarantee will never throw an exception and object or application behavior remains well-defined and consistent.
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

//=================================================================================================================

2. Strong Guarantee:
A function providing the strong guarantee ensures that, if any exception is thrown, the program’s state remains unchanged (rollback semantics). 
Either the operation completes successfully, or the program state is restored to what it was before the operation began.
Example : Transaction
1. Either whole transaction will be completed successfully.
2. or Not at all

Characteristics:
Provides transactional behavior: "all or nothing."
Requires special care to implement, such as relying on copy-and-swap idioms or resource management patterns like RAII (Resource Acquisition Is Initialization).
Often involves making a copy of data before modifications, so changes can be discarded if an exception occurs.

#include <iostream>
#include <vector>
void safeOperation(std::vector<int>& vec, const int value) {

    std::vector<int> temp(vec); // Use a temporary copy of the vector
    temp.push_back(value);      // This might throw
    temp.push_back(value * 2);  // This might throw
    
    // If everything succeeds, swap the result into the original vector
    vec.swap(temp); // Commit the changes (no-throw guaranteed)
}
int main() {
    try {
        std::vector<int> myVec = {1, 2, 3};
        safeOperation(myVec, 10);
        for (int val : myVec)
            std::cout << val << " ";
    } catch (...) {
        std::cout << "An exception occurred. Program state remains unchanged!" << std::endl;
    }
    return 0;
}
Here, if push_back(value) throws an exception, the original vector remains unchanged because of the use of a temporary copy.

//================================================================================================================

3. Basic Guarantee:
The basic exception safety guarantee ensures that:
1.Resources will not leak, even if an exception is thrown.
2.The program will not crash or will not give undefined behavior, but the program state may remains unchanged or may be altered. 

#include <iostream>
#include <vector>
#include <exception>
int main() {
    std::vector<int> myVec;  // Simple vector of integers
    try {
        // Adding 10 to the vector
        try {
            myVec.push_back(10);  // May throw (e.g., memory allocation failure)
            std::cout << "Successfully added: 10" << std::endl;
        } catch (const std::exception& e) {
            // Basic exception safety: If `push_back` throws, the state is valid but no rollback
            std::cout << "Exception occurred while adding 10: " << e.what() << std::endl;
        }

        // Adding 20 to the vector
        try {
            myVec.push_back(20);  // Same as above
            std::cout << "Successfully added: 20" << std::endl;
        } catch (const std::exception& e) {
            std::cout << "Exception occurred while adding 20: " << e.what() << std::endl;
        }

        // Simulate an exception after some successful modifications
        throw std::runtime_error("Simulated exception after adding elements.");

        // Adding 30 to the vector (this line will not execute)
        try {
            myVec.push_back(30);
            std::cout << "Successfully added: 30" << std::endl;
        } catch (const std::exception& e) {
            std::cout << "Exception occurred while adding 30: " << e.what() << std::endl;
        }

    } 
    catch (const std::exception& e) {
        // Catch any other exception thrown in `main`
        std::cerr << "Caught exception in main: " << e.what() << std::endl;
    }

    // Final state of the vector
    std::cout << "Final contents of the vector: ";
    for (int val : myVec) {
        std::cout << val << " ";
    }
    std::cout << std::endl;

    return 0;
}
Output:
Successfully added: 10
Successfully added: 20
Caught exception in main: Simulated exception after adding elements.
Final contents of the vector: 10 20

/* 
Why push_back May Throw Exceptions:
std::vector::push_back() dynamically allocates memory when the capacity of the vector is exceeded. 
If memory allocation fails (e.g., due to low system memory), it throws std::bad_alloc.
*/

//==================================================================================================================

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
Mark functions as noexcept if you are confident that they would not throw. 
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