✅Function Pointers in C++
A function pointer is a pointer that stores the address of a function.Just like pointers to data.
Using a function pointer, you can call the function it points to and even pass it as an argument to other functions. 

Syntax of Function Pointers:
return_type (*function_pointer_name)(parameter_list);

return_type: Type of the function’s return value.
pointer_name: Name of the function pointer.
parameter_list: Same argument types as the function it points to.

void myFunction(int);  // Function declaration
void (*funcPtr)(int);  // Function pointer declaration

✅Examples:
int add(int a, int b) {
   return a + b;
}
int (*funcPtr)(int, int) = add; // funcptr is holding the address of add function
int result = funcPtr(2, 3); // or you can also call this function using (*funcptr)(2,3)


✅Compile-Time vs Runtime Behavior of Function Pointers:
1.At Compile-Time:
The declaration of the function(i.e return type, parameters ) pointer (void (*funcPtr)();) is checked at compile time to ensure it is valid.

2.At Runtime:
The function that the pointer points to is invoked dynamically at runtime.



✅How to Use Function Pointers:
1. Declare a Function Pointer
A function pointer has the same signature as the function it points to.
void myFunction(int);  // Function declaration
void (*funcPtr)(int);  // Function pointer declaration

2. Assign to a Function
Assign the address of the function to the pointer:
funcPtr = &myFunction;  // Assign the function's address.
funcPtr = myFunction;  // Same as above,  & may be omitted when assigning:


1. Basic Example:
#include <iostream>
using namespace std;
void display(int value) {
    cout << "Value: " << value << endl;
}
int main() {
    void (*funcPtr)(int);  // Declare a function pointer
    funcPtr = display;     // Assign the display function to the pointer
    funcPtr(5);            // Call the function via the pointer
    return 0;
}

//==================================================================================================================

2. Function Pointers in Arrays
we can crate the array of function pointer for the functions that take same number of arguments(same type) and have same return type.
/*you generally need to ensure that all function pointers in the array share the same type (i.e., same return type and parameter signature). 
This is because arrays are homogeneous containers, meaning all elements must be of the same type.*/

#include <iostream>
using namespace std;
void add(int a, int b) { cout << "Sum: " << a + b << endl; }
void subtract(int a, int b) { cout << "Difference: " << a - b << endl; }
void multiply(int a, int b) { cout << "Product: " << a * b << endl; }

int main() {
    // Array of function pointers
    void (*arr[])(int, int) = {add, subtract, multiply};

    // Call each function via the pointers
    arr[0](10, 5);  // Calls add(10, 5)
    arr[1](10, 5);  // Calls subtract(10, 5)
    arr[2](10, 5);  // Calls multiply(10, 5)
    return 0;
}
Output:
Sum: 15
Difference: 5
Product: 50

✅//Where Are Function Pointers Used ?
//==================================================================================================================
| Scenario          | Address decided | Call resolved              |
| ----------------- | --------------- | -------------------------- |
| Normal function   | Compile time    | Compile time               |
| Function pointer  | Compile time    | Run time                   |
| Callback function | Compile time    | Run time                   |
| Virtual function  | Compile time    | Run time (dynamic binding) |



1. Function Pointers as Callback Mechanisms:
Callback is a function passed to another function using a function pointer, which is executed inside the receiving function.
#include <iostream>
using namespace std;

// Callback function
void greet() {
    cout << "Hello from callback!" << endl;
}
// Function that accepts a callback
void execute(void (*func)()) {
    cout << "Before callback" << endl;
    func();   // calling back
    cout << "After callback" << endl;
}
int main() {
    execute(greet);   // pass function as argument
    return 0;
}
/*
Which callback Function to be executed is not known at compile time but instead is determined at runtime.why??
Because In callback-based code, the compiler only knows the function signature, not the actual function. 
The function address is supplied at runtime, so the function executed is determined during execution.
🔹1️⃣ What the compiler knows at compile time
When the compiler sees:
void execute(void (*func)())

It only knows:
func is a pointer to a function
That function returns void
That function takes no parameters

❌ The compiler does NOT know:
Which function func will point to
Whether it is greet() or any other function

🔹2️⃣What happens at runtime
In main():
execute(greet);

At runtime:
greet address is passed to execute
func now points to greet




*/

Disadvantages:
1.The function to be executed is not known at compile time but instead is determined at runtime.
At runtime, at first program will access the pointer, then dereference it, and then call the function.
 This will make minor performance overhead.

Advantages:
The function pointer callback allows you to dynamically choose which function to call at runtime, making it more reusable and extensible.
/*  Example
#include <iostream>
using namespace std;

// Callback functions
void greet() {
    cout << "Hello from greet() callback!" << endl;
}
void bye() {
    cout << "Goodbye from bye() callback!" << endl;
}
// Function that accepts a callback
void execute(void (*func)()) {
    cout << "Before callback" << endl;
    func();   // dynamic callback
    cout << "After callback" << endl;
}
int main() {
    int choice;
    cout << "Enter 1 for greet, 2 for bye: ";
    cin >> choice;
    void (*callback)();   // function pointer

    // Runtime decision
    if (choice == 1) callback = greet;
    else callback = bye;
        
    execute(callback);    // chosen at runtime
    return 0;
}
*/

//=============================================================================================================================


✅2. Passing Function Pointers as Arguments
#include <iostream>
using namespace std;

// Functions
int add(int a, int b) { return a + b; }
int multiply(int a, int b) { return a * b; }

// Function that accepts a function pointer
int compute(int x, int y, int (*operation)(int, int)) {
    return operation(x, y);
}
int main() {
    cout << "Sum: " << compute(5, 3, add) << endl;
    cout << "Product: " << compute(5, 3, multiply) << endl;
    return 0;
}

//=======================================================================================================================================

✅3. Using Function Pointers with Sorting algorithms like std::sort and std::for_each
You can use function pointers to dynamically choose the comparison logic for a sorting algorithm.

#include<iostream>
#include<vector>
#include<algorithm>
bool cmp(const int& a, const int& b) {
	return a < b;
}
int main() {
	std::vector<int>nums{ 3,2,4,1,4,5,6,3 };

	std::sort(nums.begin(), nums.end(), cmp);

	for (auto i : nums)  std::cout << i << " ";
}


#include<iostream>
#include<algorithm>
#include<vector>
void fun(const int& a) {
	std::cout << a << " ";
}
int main() {
	std::vector<int>nums{ 3,5,2,2,4,4,2,4,6 };
	std::for_each(nums.begin(), nums.end(), fun);
	return 0;
}
//================================================================================================================

✅4. Alternatives to Function Pointers
1.Lambdas
2.std::function
3.Functors (Function Objects)
4.Virtual Functions (and Polymorphism)

//=================================================================================================================
✅1.Lambdas
#include <iostream>
using namespace std;

// Function that accepts a callback
void executeCallback(int value, const auto& func) {
    func(value);  // Call the function
}
int main() {
    int multiplier = 2;
    // Define a lambda as a callback
    auto lambdaCallback = [multiplier](int x) {
        cout << "Value: " << x << ", Multiplied: " << x * multiplier << endl;
    };
    // Pass the lambda to a function
    executeCallback(10, lambdaCallback);
}
//=================================================================================================================

✅2. std::function
std::function (introduced in C++11) is a type-safe way to store and call callable objects, such as function pointers, lambda expressions, or functors. 
It’s a part of the <functional> header.
std::function can store anything that can be called if they match the same signature, such as:
Normal functions
Function pointers
Lambda expressions
Functors (objects with operator())

Basic Syntax of std::function
#include <functional> // Required for std::function
std::function<ReturnType(ArgTypes...)> variable_name;


✅Advantages of std::function:
Flexible: Works with plain functions, lambdas, and functors.
Type-safe: The function signature is strictly enforced.
Clean and reusable.
Use Case: Dynamically Selecting Callbacks

#include <iostream>
#include <functional>  // For std::function
using namespace std;

// Function that accepts a std::function
void execute_fun(std::function<int(int, int)> operation, int a, int b) {
    cout << "Result: " << operation(a, b) << endl;
}
// Plain functions
int add(int x, int y) { return x + y; }
int multiply(int x, int y) { return x * y; }

int main() {
    // Pass a plain function
    execute_fun(add, 5, 3);  // Result: 8
    // Pass a lambda
    execute_fun([](int x, int y) { return x - y; }, 5, 3);  // Result: 2
    // Reuse with variables
    std::function<int(int, int)> divide = [](int x, int y) { return x / y; };
    execute_fun(divide, 10, 2);  // Result: 5

    return 0;
}
Examples of Using std::function
1. Wrapping a Simple Free Function
A free function is a global or static function that can work independently.

#include <iostream>
#include <functional>  // For std::function
// Free function
void greet() {
    std::cout << "Hello from a free function!" << std::endl;
}

int main() {
    // Using std::function to wrap a free function
    std::function<void()> func = greet;
    // Call the function
    func();
}
Output:
Hello from a free function!
Here, std::function<void()> func is used to store a callable object with the following signature:
Return type: void
Arguments: No arguments ()


2. Wrapping a Function Pointer
std::function can also work with traditional function pointers.

#include <iostream>
#include <functional>
// Function that takes an integer and returns void
void printNumber(int n) {
    std::cout << "Number: " << n << std::endl;
}
int main() {
    // Create a std::function from a function pointer
    std::function<void(int)> func = &printNumber;
    // Call the function
    func(42);
}
Output:
Number: 42
In this case, the std::function<void(int)> wraps a function taking an integer and returning void.

3. Wrapping a Lambda Expression
Lambda functions (introduced in C++11) are anonymous functions that are often concise and inline.

#include <iostream>
#include <functional>
int main() {
    // Lambda expression
    auto lambda = [](int x, int y) {
        std::cout << "Sum: " << (x + y) << std::endl;
    };
    // std::function wrapping the lambda
    std::function<void(int, int)> func = lambda;
    // Call the lambda through std::function
    func(10, 20);

    return 0;
}
Output:
Sum: 30
Here, std::function<void(int, int)> stores the lambda function that takes two integers and returns nothing.


4. Wrapping a Functor (Class with operator())
A functor is a class or struct with an overloaded operator() that allows it to be used like a function.

#include <iostream>
#include <functional>
// Functor
class Multiply {
public:
    int operator()(int a, int b) {
        return a * b;
    }
};

int main() {
    // Create a functor
    Multiply multiply;

    // std::function wrapping the functor
    std::function<int(int, int)> func = multiply;

    // Call the functor via std::function
    std::cout << "Product: " << func(5, 3) << std::endl;

    return 0;
}
Output:
Product: 15
Multiply is a callable object, and std::function<int(int, int)> wraps it.


6. Passing std::function as a Callback
A common use case is passing std::function as a parameter to implement callbacks or event handlers.

#include <iostream>
#include <functional>
// Function that accepts a std::function as a callback
void process(int a, int b, const std::function<int(int, int)>& callback) {
    std::cout << "Result: " << callback(a, b) << std::endl;
}
// Free function to be used as a callback
int add(int x, int y) {
    return x + y;
}
int main() {
    // Pass a free function as the callback
    process(10, 20, add);

    // Pass a lambda expression as the callback
    process(10, 20, [](int x, int y) { return x * y; });

    return 0;
}
Output:
Result: 30
Result: 200
Here, process accepts a callback with the signature int(int, int) wrapped by std::function.


7. Using std::function with State-Capturing Lambdas
Lambda functions with captured state can also be wrapped in std::function.
#include <iostream>
#include <functional>
int main() {
    int multiplier = 3;

    // Lambda that captures state
    std::function<int(int)> func = [multiplier](int x) {
        return x * multiplier;
    };

    // Call the lambda
    std::cout << "Result: " << func(10) << std::endl;

    return 0;
}
Output:
Result: 30
The lambda captures the variable multiplier by value.