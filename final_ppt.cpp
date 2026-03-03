

✅What exceptions are :
Exceptions basically are runtime errors and unexpected behaviour in a program

🚗 Real Life Example: Moving Car


✅ Example 1: Division by Zero
int a = 10;
int b = 0;
int result = a / b;   // ❌ division by zero not allowed


✅ Example 2: Accessing Invalid Index in a vector
vector<int> v = {1, 2, 3};
cout << v.at(5);   // throws std::out_of_range


✅ Example 3: Memory Allocation Failure

    int* p = new int[1000000000000];


====================================================================================================================


✅ How To Handle Properly in C++
3 Keywords:
try → Defines a block of code that might throw an exception.
throw → Used to throw an exception.
catch → is used to handle an exception that was thrown inside a try block.


✅ Basic Syntax of exception handling:
try {
    // Code that may cause an exception 
     
}
catch (ExceptionType1& e) {
    // will Handle exception of type ExceptionType1
}
catch (ExceptionType2 &e) {
    // Handle another type
}
catch (...) { // Catch-All Handler
    // Catch any type of exception (optional)
}

-------------------------------------------------------------------------------------------------------------------
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
    catch (const std::exception& e) {
        cout << "Exception caught: " << e.what() << endl;
    }
    cout << "Program continues..." << endl;
    return 0;
}
What Happens When You Write  throw std::runtime_error("Division by zero"); ??

1️⃣. Program Execution stops immediately.
1️⃣Step 1: A Temporary Exception Object Is Created
throw 5;                // exception object type: int
throw "error";          // exception object type: const char*
throw std::runtime_error("x");  // exception object type: runtime_error

2️⃣ Step 2: Memory Allocation Happens
3️⃣ Stack Unwinding Begins
4️⃣ Compiler looks for matching catch


===================================================================================================================


✅What is Stack Unwinding and how object destruction works when an exception is thrown

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
