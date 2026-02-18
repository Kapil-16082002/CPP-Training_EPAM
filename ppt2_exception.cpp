
✅What exceptions are:
Exceptions basically are runtime errors and unexpected behaviour in a program, that interrupts normal flow of program and we can handle it using C++ exception handling mechanism.

🚗 Real Life Example: Moving Car

Imagine:
You are driving a car normally.
👉 Suddenly a dog comes in front of the car. Then you have to stop car.
 So, That dog came in front of your car is an unexpected situation.


Basic Example of Exception:
✅ Example 1: Division by Zero
int a = 10;
int b = 0;
int result = a / b;   // ❌ division by zero not allowed

If you don’t handle the exception, program will:
will give Undefined Behavior, On most systems → Program crashes


✅ Example 2: Accessing Invalid Index in a vector
vector<int> v = {1, 2, 3};
cout << v.at(5);   // throws std::out_of_range

If you don’t handle the exception, program will:
Throw std::out_of_range
Call std::terminate() // When std::terminate() is called, it means the program will immediately stop execution.
Program crashes
/*When std::terminate() is invoked:
The program stops immediately.
Stack unwinding may NOT complete.
Destructors may NOT run.
*/

✅ Example 3: Memory Allocation Failure

    int* p = new int[1000000000000];

If you don’t handle the exception, program will:
std::bad_alloc is thrown
std::terminate() is called, Program crashes.

===================================================================================================================

✅ How To Handle Properly in C++
Basically C++ provides 3 Keywords that helps in Exception Handling:
try → Defines a block of code that might throw an exception.
throw → Used to throw an exception.
catch → Handles exceptions thrown by the try block.


✅ Basic Syntax of exception handling:
try {
    // Code that may cause an exception
     
}
catch (ExceptionType1 e) {
    // Handle exception of type ExceptionType1
}
catch (ExceptionType2 e) {
    // Handle another type
}
catch (...) {
    // Catch any type of exception (optional)
}
⚠ But there are some Limitation of catch-all handler catch(...) Like:

❌ You cannot access the exception object
❌ You cannot call what()
❌ You don’t know what was thrown

--------------------------------------------------------------------------------------------------------------------

Lets understand by example:

void divide(int a, int b) {
    if (b == 0)  throw std::runtime_error("Division by zero");

    cout << "Result: " << a / b << endl;
}
int main() {
    try {
        divide(10, 0);   // This will throw
    }
    // catch(int){};
    catch (const std::runtime_error ) {
        cout << "Exception caught: " << e.what() << endl;
    }
    catch (const std::exception& e) {
        cout << "Exception caught: " << e.what() << endl;
    }
    cout << "Program continues..." << endl;
    return 0;
}


✅try:
Tells the compiler:
“If an exception occurs inside this block, look for matching catch handlers.”



What Happens When this line execute  throw std::runtime_error("Division by zero"); ??

1️⃣. Program Execution stops immediately.
1️⃣Step 1: A Temporary Exception Object Is Created
The type of the Exception Object is Exactly same as the type of the expression after throw.

throw 5;                // exception object type: int
throw "error";          // exception object type: const char*
throw std::runtime_error("x");  // exception object type: runtime_error

And corresponding matching catch blocks will be:
catch(int)
catch(const char*)
catch(const std::exception&)

2️⃣ Step 2: Memory Allocation Happens for exception object.
🔥The runtime copies/moves this exception object into Special memory and that memory is managed by the C++ runtime (not stack)
Why not stack?
Because stack will be destroyed during stack unwinding.

3️⃣ Stack Unwinding Begins. I will Explain it later, what is it
4️⃣C++ runtime look for matching catch block and Control Transfers to the matching Catch Block

✅What if No Catch block  Matches?
std::terminate() is called and Program immediately stops or may be Program crashes.



/*catch (const std::exception&e)
std::exception&e will catch only those exceptions that are derived from the std::exception class.
Example, std::runtime_error, std::logic_error, or create a custom exception class.


🔥 So What Is The Role of throw?
throw does 3 major things:
| Role                 | Meaning                           |
| -------------------- | --------------------------------- |
| 1️⃣ Signal Error     | Something went wrong              |
| 2️⃣ Stop Execution   | Exit current function immediately |
| 3️⃣ Transfer Control | Jump to matching catch block      |

If an exception is thrown:
1. Program Execution stops immediately.
2. Stack unwinding begins.
3. Compiler looks for matching catch.
4. Control transfers to matched handler.
*/
=================================================================================================================


✅ Stack unwinding and how object destruction works when an exception is thrown

✅What is Stack Unwinding in C++?
Stack unwinding refers to the process of cleaning up the stack when an exception is thrown in a C++ program.
When an exception occurs, the C++ runtime traverses the call stack (from the point where the exception was thrown) and:
1.Look for a matching catch block.
2.Destruct objects (including local variables) in reverse order of their construction (starting from the current scope and moving upward).
3.Perform proper cleanup of resources (memory, file handles, etc.) during this traversal.
If no matching catch block is found,the program will terminate by invoking the std::terminate() function.

🧠 Code Flow
main()
 └── functionA()
      └── functionB()
           └── functionC()



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
    cout<<"Program will continue.....";
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
Program will continue.....


🔥 Now the important part begins.
When throw runs:
An exception object is created (of type runtime_error).
Control immediately leaves functionC.
The runtime starts searching for a matching catch.

🔥 Step 5: Leaving functionC()
Since there is no catch Block in functionC(), Control immediately leaves functionC.
Before exiting functionC:
Destructor: C will be called, c is destroyed.

🔥 Step 6: Enter functionB()
Since there is no catch Block in functionB(), Control immediately leaves functionB.
Before exiting functionB also:
Destructor: B will be called, b is destroyed.

So runtime continues moving upward.

🔥 Step 7: Enter functionA()
Does functionA have a matching catch?
catch (const std::exception& e)
Yes ✅
So propagation stops here.
Catch Block Executes : Caught exception: Exception thrown in functionC

Now here functionA Ends and Destructor: A  will be called.

So in this way  destructors are called during stack unwinding and now Program will continue...doing its task.


//=================  Why exceptions are exist in C++? ===========================================================

️1️⃣Automatic Resource Cleanup ( Exceptions prevent memory leaks only if you use RAII objects.)

When exception occurs:
Stack unwinding happens
Destructors of local objects are called automatically
This prevents memory leaks.


2️⃣ To Separate Error Handling from Normal Code and To Propagate Errors Automatically
Without exceptions:

int divide(int a, int b) {
    if (b == 0)
        return -1;   // error code
    return a / b;
}
Problems:
Error codes mix with real return values
Caller must check error every time
Code becomes messy

If an error happens deep inside function calls:
main()
  ↓
funcA()
  ↓
funcB()
  ↓
funcC()  ← error here


Without exceptions:
Every function must return error codes manually

With exceptions:
Error automatically propagates upward
No need to manually forward error
This reduces boilerplate code.

====================================================================================================================


✅ Why Are Exceptions Expensive in C++ ?
🔥 1️⃣ Stack Unwinding Is Costly
When throw happens:
Program stops normal execution
Runtime starts stack unwinding

It:
Destroys all local objects
Calls destructors
Pops stack frames
Searches for matching catch

Example:
void f3() { throw runtime_error("error"); }
void f2() { f3(); }
void f1() { f2(); }

int main() {
    try {
        f1();
    }
    catch (...) {}
}
If f3() throws:
Runtime must:
Exit f3
Destroy its locals
Exit f2
Destroy its locals
Exit f1
Destroy its locals
Finally reach main

That’s heavy work.


🔥 2️⃣ Exception Object Creation

When you write:
throw runtime_error("Division by zero");

Internally:
Exception object is created
Memory is allocated (usually on heap)
Object is copied into special exception storage
RTTI info stored
Memory allocation = expensive.

======================================================================================================================

✅ Why does a catch block only catch the corresponding exception?
When exception is thrown, C++ Runtime checks the type information of exception object and look for the corresponding catch block that is expecting argument same type as object have.
and the first compatible catch block is selected.”


===================================================================================================================
✅if the thrown object is of a derived type, a catch block with the base class type can catch it.why

Because a derived object IS-A base object, so during exception matching, the runtime allows a base-class reference to bind to the derived exception object (polymorphism).
/*
Derived object IS-A base object
It means:
Every derived class contains all the properties of the base class, so derived class object can be treated as a base class object.
*/

try {
    throw std::runtime_error("error");
}
catch (const std::exception& e) {  // Base class
}
This works because:
std::runtime_error IS-A std::exception


==================================================================================================================


/*🔷  What Happens When You Write throw std::runtime_error("Division by zero"); ??
This line means: we are creating an object of type std::runtime_error with message "Division by zero" and throw it as an exception.
throw is used to throw an exception
🚨 It also Signal that an error has occurred and transfer control to a matching catch block.
🔹 std::runtime_error
This is a class from the C++ Standard Library.
It is part of the exception hierarchy:

std::exception
    ↓
std::runtime_error
So runtime_error is a derived class of std::exception.*/

====================================================================================================================

🔷 Method 1: Check Before Dividing (Best Practice)
🔷 Method 2: Throw Custom Exception: using try, catch block

🔷 Method 1: Check Before Dividing (Best Practice)
int main() {
    int a = 10;
    int b = 0;

    if (b == 0) {
        cout << "Error: Division by zero is not allowed\n";
    } 
    else {
        cout << a / b;
    }
}

🔷 Method 2: Throw Custom Exception: using try, catch block

#include <iostream>
using namespace std;

void divide(int a, int b) {
    if (b == 0)
        throw "Division by zero error!";  // Throwing a string literal as const char* i.e pointer to char array
        //throw string("Division by zero error!");  // Throwing a string exception
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
    //catch (std::string msg)   will catch string exception
    return 0;
}
output:
Exception caught: Division by zero error!


==================================================================================================================

✅ Example 2: Accessing Invalid Index
vector<int> v = {1, 2, 3};
cout << v.at(5);   // throws std::out_of_range

✅ Method 2: Check Before Accessing (Safer in performance code)

int main(){
vector<int> v = {1, 2, 3};
if (5 < v.size()) {
    cout << v.at(5);
} 
else {
    cout << "Index out of range\n";
    }
}
/*
🔷 Internally what at() roughly does:

if (index >= size())
    throw std::out_of_range("vector");
return data[index];


So exception is thrown manually by STL.
*/
🔹 Method 1: Using try–catch (Recommended for exceptions)
#include <iostream>
#include <vector>
using namespace std;

int main() {
    vector<int> v = {1, 2, 3};

    try {
        cout << v.at(5);
    }
    catch (const out_of_range& e) {
        cout << "Exception caught: " << e.what() << endl;
    }
}
Output:
Exception caught: vector::_M_range_check

