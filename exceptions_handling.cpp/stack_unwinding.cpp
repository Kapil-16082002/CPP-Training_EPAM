
✅What is Stack Unwinding in C++?
Stack unwinding refers to the process of cleaning up the stack when an exception is thrown in a C++ program.
When an exception occurs, the runtime traverses the call stack (from the point where the exception was thrown) to:
1.Look for a matching catch block.
2.Destruct objects (including local variables) in reverse order of their construction (starting from the current scope and moving upward).
3.Perform proper cleanup of resources (memory, file handles, etc.) during this traversal.
If no matching catch block is found,the program will terminate by invoking the std::terminate() function.

✅Why is Stack Unwinding Necessary?
When an exception is thrown, program control immediately transfers to the nearest catch block (or the exception handler, if one exists). 
However, before transferring control, all local objects (those created within scopes being unwound) need to be properly destroyed and cleaned up, to avoid:

1.Memory Leaks:
Any dynamically allocated resources must be freed during stack unwinding.
2.Resource Leaks:
Files, handles, or database connections must be closed or released during stack unwinding.
3.Undefined Behavior:
Proper destruction ensures program behaves safely and consistently even during abnormal termination.

✅What Happens During Stack Unwinding:
While unwinding the stack:

The destructors of all fully constructed objects in the current and previous stack frames are called in reverse order of their creation (LIFO—last in, first out).
This ensures that resources acquired previously (e.g., memory, files, or other system resources) are properly cleaned up.
The goal of stack unwinding is to clean up responsibly even in the face of an unhandled exception.

//--------------------------------------------------------------------------------------------------------------

#include <iostream>
#include <stdexcept>
class Test {
private:
    std::string name;
public:
    Test(const std::string& name) : name(name) {
        std::cout << "Constructor: " << name << std::endl;
    }
    ~Test() {
        std::cout << "Destructor: " << name << std::endl;
    }
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
// Destructor: C   
// Destructor: B
// Destructor: A
terminate called after throwing an instance of 'std::runtime_error'
what(): Exception thrown in functionC

Why is the Destructor of a Not Called ????
functionC() throws an exception.
functionB() does not handle the exception, so it propagates up.
functionA() also does not handle it, so it propagates to main().
Since main() also does not handle it, the program terminates immediately.
Stack unwinding stops, and destructors of active objects (like a in functionA()) are not called.

/*Here is how it happens in your code:
functionA() creates the object "A".

Test a("A"); calls the constructor of "A".
functionA() calls functionB():

functionB() creates the object "B".
functionB() calls functionC():

functionC() creates the object "C".
Exception is thrown from functionC().
Stack Unwinding begins:

The exception propagates upward through the call stack (functionC → functionB → functionA → main).
During this propagation, destructors are called for all objects created in the scope of the functions being unwound. Specifically:
Destructor for "C" is called.
Destructor for "B" is called.
Destructor for "A" is called.
Program Termination:

None of the functions (functionC, functionB, functionA, and main) have a try-catch block to handle the exception.
Therefore, the program terminates after stack unwinding is complete.
*/



//----------------------------------------------------------------------------------------------------------------
#include <iostream>
class Test {
private:
    std::string name;
public:
    Test(const std::string& name) : name(name) {
        std::cout << "Constructor: " << name << std::endl;
    }
    ~Test() {
        std::cout << "Destructor: " << name << std::endl;
    }
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
