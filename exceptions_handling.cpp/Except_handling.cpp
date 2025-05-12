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

Types of Exceptions:
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

Basic Example of Exception Handling ////////////////////////////
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

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include <stdexcept>
class Test {
public:
    Test(const std::string& name) : name(name) {
        std::cout << "Constructor: " << name << std::endl;
    }
    ~Test() {
        std::cout << "Destructor: " << name << std::endl;
    }
private:
    std::string name;
};
void functionC() {
    Test c("C");
    throw std::runtime_error("Exception thrown in functionC");  // Uncaught exception
}
void functionB() {
    Test b("B");
    functionC();  // functionC throws, functionB does not catch it
}
void functionA() {
    Test a("A");
    functionB();  // functionB does not catch the exception either
}
int main() {
    functionA();  // No try-catch, exception remains uncaught
    return 0;
}
Output:
Constructor: A
Constructor: B
Constructor: C   
// Destructor will not called
terminate called after throwing an instance of 'std::runtime_error'
what():  Exception thrown in functionC
Aborted (core dumped)

Why is the Destructor of a Not Called ????
functionC() throws an exception.
functionB() does not handle the exception, so it propagates up.
functionA() also does not handle it, so it propagates to main().
Since main() also does not handle it, the program terminates immediately.
Stack unwinding stops, and destructors of active objects (like a in functionA()) are not called.

                                                          ///////////////////////////////////////////////////
#include <iostream>
class Test {
public:
    Test(const std::string& name) : name(name) {
        std::cout << "Constructor: " << name << std::endl;
    }
    
    ~Test() {
        std::cout << "Destructor: " << name << std::endl;
    }

private:
    std::string name;
};

void functionC() {
    Test c("C");
    throw std::runtime_error("Exception thrown in functionC");
}

void functionB() {
    Test b("B");
    functionC();  // Call functionC which throws an exception
}

void functionA() {
    Test a("A");
    try {
        functionB();  // Call functionB which calls functionC
    } catch (const std::exception& e) {
        std::cout << "Caught exception: " << e.what() << std::endl;
    }
}

int main() {
    functionA();
    return 0;
}
Output:
Constructor: A
Constructor: B
Constructor: C
Destructor: C
Destructor: B
Caught exception: Exception thrown in functionC
Destructor: A

Explanation:
functionA() creates a (Test("A")).
functionB() creates b (Test("B")).
functionC() creates c (Test("C")) and throws an exception.
Since functionC() threw an exception: c is destroyed first (stack unwinding).//Destructor: C
b is destroyed next (stack unwinding in functionB()). // Destructor: B
Control returns to functionA(), where the catch block handles the exception.
a is destroyed last before exiting functionA().
✅ All destructors are called in proper order (reverse of construction order).

                                                         //////////////////////////////////////////////////////
#include <iostream>
#include <stdexcept>
class Test {
public:
    Test(const std::string& name) : name(name) {
        std::cout << "Constructor: " << name << std::endl;
    }
    ~Test() {
        std::cout << "Destructor: " << name << std::endl;
    }
private:
    std::string name;
};
void functionC() {
    Test c("C");
    throw std::runtime_error("Exception thrown in functionC");  // Uncaught exception
}
void functionB() {
    Test b("B");
    functionC();  // functionC throws, functionB does not catch it
}
void functionA() {
    Test a("A");
    functionB();  // functionB does not catch the exception either
}
int main() {
    try{
        functionA();  
    }
    catch (const std::exception& e) {
        std::cout << "Caught exception: " << e.what() << std::endl;
    }
    return 0;
}
Output:
Constructor: A
Constructor: B
Constructor: C
Destructor: C
Destructor: B
Destructor: A
Caught exception: Exception thrown in functionC
