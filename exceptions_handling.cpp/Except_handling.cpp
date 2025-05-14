Exception handling in C++ provides a mechanism to handle runtime errors and unexpected conditions in a program.

Keywords in C++ Exception Handling:
try → Defines a block of code that might throw an exception.
throw → Used to throw an exception.
catch → Handles exceptions thrown by the try block.
/*Catch-All Handler
Use catch(...) to handle all exceptions when the type is unknown or irrelevant.  */


Scenarios in Exception Handling:
1. Divide by Zero (Mathematical Errors) -> can lead to undefined behavior
2. Array Index Out of Bounds ->  throw out_of_range exception
3. Memory Allocation Errors -> When the system runs out of memory, a std::bad_alloc exception is thrown.
4. File Handling Errors -> While working with files, exceptions can arise if the file is not found, cannot be opened, or there's a read/write failure.

✅Types of Exceptions:
1.Standard exceptions (std::exception, std::runtime_error, etc.).
2.User-defined exceptions (custom exception classes).
3.System-generated exceptions (e.g., division by zero, out of memory).

Multiple Catch Blocks:
A try block can have multiple catch handlers for different types.

Re-throwing Exceptions:
A caught exception can be re-thrown for higher-level handling.

Exception Specifications (deprecated in C++11):
throw(type) was used to declare which exceptions a function might throw.
This feature was removed in modern C++ because it was difficult to enforce at runtime.

//----------------------------------------------------------------------------------------------------------------

Basic Example of Exception Handling 
#include <iostream>
using namespace std;
void divide(int a, int b) {
    if (b == 0)
        throw "Division by zero error!";  // Throwing a string exception
    cout << "Result: " << a / b << endl;
}
int main() {
    try {
        divide(10, 2);
        divide(5, 0);  // This will cause an exception
    }
    catch (const char* msg) {  // Catching the exception
        cout << "Exception caught: " << msg << endl;
    }
    return 0;
}
Output
Result: 5
Exception caught: Division by zero error!

// =------------------------     throw exception in constructor      ----------------------------------------------

When an Exception is Thrown in a Constructor
In C++, if a constructor of a class throws an exception, the destructor for the object being created will NOT be called, because the object is considered incomplete at the time of the exception.
However:
Any objects that have already been fully constructed (e.g., objects for member variables, base classes) will have their destructors called.
The destructor for the object itself (the one whose constructor threw the exception) is not called, because the object was never fully constructed.


✅Case 1: Destructor of the Object Itself Is NOT Called
If an exception is thrown in the constructor of a class, the destructor for the object itself will not be called because the object is considered incomplete—its lifetime did not officially begin.

#include <iostream>
#include <stdexcept>
class Test {
public:
    Test() {
        std::cout << "Constructor: Test" << std::endl;
        throw std::runtime_error("Exception in constructor");
    }
    ~Test() {
        std::cout << "Destructor: Test" << std::endl;
    }
};
int main() {
    try {
        Test t; // Attempt to create an object of `Test`
    } catch (const std::exception& e) {
        std::cout << "Caught exception: " << e.what() << std::endl;
    }
    return 0;
}
Output:
Constructor: Test
Caught exception: Exception in constructor

Explanation:
The ~Test() destructor is NOT called because the exception was thrown before the object t was fully constructed.
The lifetime of t never started since the object construction failed.

//---------------------------------------------------------------------------------------------------------------

✅Case 2: Destructor for Fully Constructed Base Classes or Member Variables IS Called
If the constructor of a derived class or a containing class throws an exception after base classes or member variables have been constructed, 
then  destructors for those already-constructed components are called.
#include <iostream>
#include <stdexcept>

class Member {
public:
    Member() {
        std::cout << "Constructor: Member" << std::endl;
    }
    ~Member() {
        std::cout << "Destructor: Member" << std::endl;
    }
};
class Test {
private:
    Member m; // Member variable
public:
    Test() {
        std::cout << "Constructor: Test" << std::endl;
        throw std::runtime_error("Exception in constructor");
    }
    ~Test() {
        std::cout << "Destructor: Test" << std::endl;
    }
};
int main() {
    try {
        Test t; // Attempt to create `Test`
    } catch (const std::exception& e) {
        std::cout << "Caught exception: " << e.what() << std::endl;
    }

    return 0;
}
Output:
Constructor: Member
Constructor: Test
Destructor: Member
Caught exception: Exception in constructor

Explanation:
The constructor for the member variable m (of type Member) is called before the exception is thrown.
When the exception is thrown in Test constructor:
The destructor for m is called because m was fully constructed.
The destructor for Test itself is NOT called because the Test object was never fully constructed.

//----------------------------------------------------------------------------------------------------------------

✅Case 3: Destructors for Partially Constructed Base Classes Are Called
If a derived class constructor throws an exception while the base class constructor has fully executed successfully, the destructor for the base class will be called.

#include <iostream>
#include <stdexcept>

class Base {
public:
    Base() {
        std::cout << "Constructor: Base" << std::endl;
    }
    ~Base() {
        std::cout << "Destructor: Base" << std::endl;
    }
};
class Derived : public Base {
public:
    Derived() {
        std::cout << "Constructor: Derived" << std::endl;
        throw std::runtime_error("Exception in Derived constructor");
    }
    ~Derived() {
        std::cout << "Destructor: Derived" << std::endl;
    }
};
int main() {
    try {
        Derived d; // Attempt to create `Derived`
    } catch (const std::exception& e) {
        std::cout << "Caught exception: " << e.what() << std::endl;
    }

    return 0;
}
Output:
Constructor: Base
Constructor: Derived
Destructor: Base
Caught exception: Exception in Derived constructor
Explanation:
The base class (Base) is fully constructed before control enters the derived class (Derived) constructor.
When an exception is thrown in the Derived constructor:
The destructor for the base class (~Base()) is called to clean up the successfully constructed base portion.
The destructor for the Derived class (~Derived()) is NOT called because the Derived object was never fully constructed.


//---------------------------------------------------------------------------------------------------------------

✅When a constructor throws an exception:

The object is not fully constructed(created) (the constructor did not successfully finish).
The C++ runtime performs stack unwinding to clean up any partial resources allocated during the objects construction.
Any already fully-constructed base subobjects or member objects will have their destructors automatically called during stack unwinding.
The exception propagates out of the constructor so that it can be caught and handled by a catch block higher in the call stack.

#include <iostream>
#include <exception>
#include <string>
class MyClass {
private:
    std::string resource1;
    std::string* resource2;
public:
    MyClass(const std::string& init) : resource1(init), resource2(nullptr) {
        std::cout << "Constructing MyClass with resource: " << resource1 << std::endl;
        // Allocate memory for resource2
        resource2 = new std::string("Dynamically allocated resource");

        if (init.empty()) {  // Simulate an error:
            throw std::runtime_error("Input string is empty! Constructor failed.");
        }
        std::cout << "MyClass successfully constructed!" << std::endl;
    }
    ~MyClass() {
        std::cout << "Destructor called. Cleaning up resources..." << std::endl;
        delete resource2; // Clean up dynamic memory
    }
};
int main() {
    try {
        // Attempt to construct object with valid input
        std::cout << "Creating object with valid input...\n";
        MyClass obj1("Valid Input");

        // Attempt to construct object with invalid input
        std::cout << "\nCreating object with invalid input...\n";
        MyClass obj2(""); // This will fail due to the empty string
    }
    catch (const std::exception& e) {
        // Catch exceptions thrown by constructors
        std::cerr << "Exception caught: " << e.what() << std::endl;
    }
    std::cout << "Program continues after handling exception." << std::endl;

    return 0;
}
Output:
Creating object with valid input...
Constructing MyClass with resource: Valid Input
MyClass successfully constructed!

Creating object with invalid input...
Constructing MyClass with resource: 
Destructor called. Cleaning up resources...
Exception caught: Input string is empty! Constructor failed.
Program continues after handling exception.

✅Detailed Explanation:
When a Valid Object (obj1) Is Created:
MyClass obj1("Valid Input") is constructed successfully.
The constructor finishes normally, and the destructor will clean up properly when obj1 goes out of scope.

When an Object (obj2) Throws an Exception:
MyClass obj2("") causes the constructor to throw a std::runtime_error because the input string is empty.
The constructor will never completes successfully, so obj2 is not fully constructed.

Since resource2 is a dynamically allocated pointer (new std::string(...)), its memory will NOT be freed automatically by stack unwinding. 
It remains allocated unless you explicitly delete it before throwing the exception.
The destructor of MyClass (~MyClass()) is NOT called for obj2, because exceptions thrown in the constructor prevent the object from being completely constructed.
As a result, the dynamically allocated memory for resource2 will cause a memory leak, and cleanup must be handled manually before the exception is thrown.

/*NOTE:
If resource2 is not allocating memory dynamically, then there will be no memory leak. 
This is because if a resource is allocated on the stack (not dynamically), its destructor will be automatically called during stack unwinding when an exception is thrown, ensuring proper cleanup
*/
✅Fixing the Memory Leak
To fix this issue, you need to ensure that dynamically allocated memory (resource2) is freed before throwing the exception. 
You can do this in one of two ways:

Solution 1: Manual Cleanup Before Throwing
Modify the constructor to delete resource2 before throwing the exception. For example:

MyClass(const std::string& init) : resource1(init), resource2(nullptr) {
    std::cout << "Constructing MyClass with resource: " << resource1 << std::endl;
    resource2 = new std::string("Dynamically allocated resource");
    if (init.empty()) {
        delete resource2;  // Clean up dynamically allocated memory
        resource2 = nullptr;
        throw std::runtime_error("Input string is empty! Constructor failed.");
    }
    std::cout << "MyClass successfully constructed!" << std::endl;
}
After updating the code, there is no memory leak because resource2 is freed before the exception is thrown.

Solution 2: Use Smart Pointers
Instead of using raw pointers (std::string* resource2), use smart pointers, like std::unique_ptr, which automatically manage the memory and clean up resources when exceptions are thrown.

Here’s the updated code using std::unique_ptr:
#include <iostream>
#include <exception>
#include <string>
#include <memory> // For smart pointers

class MyClass {
private:
    std::string resource1;
    std::unique_ptr<std::string> resource2; // Use smart pointer
public:
    MyClass(const std::string& init)
        : resource1(init), resource2(std::make_unique<std::string>("Dynamically allocated resource")) {
        std::cout << "Constructing MyClass with resource: " << resource1 << std::endl;
        if (init.empty()) {
            throw std::runtime_error("Input string is empty! Constructor failed.");
        }
        std::cout << "MyClass successfully constructed!" << std::endl;
    }
    ~MyClass() {
        std::cout << "Destructor called. Cleaning up resources..." << std::endl;
    }
};
Why This Works:
Smart Pointers Manage Memory Automatically:
When an exception is thrown, the std::unique_ptr for resource2 ensures its memory is automatically released.
No Need for Manual Cleanup:
With smart pointers, you don’t need to manually delete resource2 in case of an exception.
