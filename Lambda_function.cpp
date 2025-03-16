lambda function->
A lambda function is an inline, unnamed function that can be defined within expressions.
It is primarily used for short, simple operations like callbacks, sorting, or quick calculations.

🔹 Lambda Function Syntax
[capture_list](parameters) -> return_type { function_body };

capture_list → Captures variables from the surrounding scope.
parameters → Similar to function parameters.
return_type → (Optional) Specifies the return type.
function_body → Contains the logic of the lambda.

#include <iostream>
using namespace std;
int main() {

    auto sum = [](int a, int b) { return a + b; };
    cout << "Sum: " << sum(5, 3) << endl;
    return 0;
}
✅ Output:
Sum: 8
✔ The lambda behaves like a function but is defined inline.

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

3️⃣ Capturing Variables in Lambda
Lambdas can capture variables from their surrounding scope.

🔹 1. Capture by Value ([=] or [var])
🔹 Difference Between [x] vs [=]
Capture Type	   Effect	                                      Example
[x]	               Captures only x by value	                      auto lambda = [x]() { cout << x; };
[=]	               Captures all variables in scope by value	      auto lambda = [=]() { cout << x << y; };
The lambda makes a copy of the captured variable.

#include <iostream>
using namespace std;
int main() {
    int x = 10;
    auto printX = [x]() { cout << "Captured by value: " << x << endl; };
    x = 20;  // Changing x doesn't affect lambda
    printX();  

    return 0;
}
✅ Output:
Captured by value: 10
✔ Lambda captured x by value, so it retains 10 even after x changes.
//--------------------------------------------------------------------------------------------------------------
🔹 2. Capture by Reference ([&] or [&var])
The lambda uses the actual variable, so changes are reflected.

#include <iostream>
using namespace std;
int main() {
    int x = 10;
    auto modifyX = [&x]() { x += 5; };  
    modifyX();  
    cout << "Modified x: " << x << endl;  
    return 0;
}
✅ Output:
Modified x: 15
✔ Lambda modifies the actual variable because it was captured by reference.

//---------------------------------------------------------------------------------------------------------------
🔹 3. Mixed Capture ([=, &y])
Some variables by value, some by reference.

#include <iostream>
using namespace std;
int main() {
    int a = 10, b = 20;
    auto lambda = [=, &b]() { b += a; };  // `a` by value, `b` by reference
    lambda();
    cout << "a: " << a << ", b: " << b << endl;
    return 0;
}
✅ Output:
a: 10, b: 30
✔ b was modified, but a remained unchanged.
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

4️⃣ Specifying Return Type
By default, the return type is inferred(return automatic by compiler based on expression computation).
If needed, specify explicitly using -> return_type.

🔹 Example: Explicit Return Type
#include <iostream>
using namespace std;
int main() {
    auto divide = [](int a, int b) -> double { return (double)a / b; };  //  2.5
    auto divide = [](int a, int b) -> int { return (double)a / b; };     //  2

    cout << "Division: " << divide(5, 2) << endl;
    return 0;
}
✅ Output:
Division: 2.5
✔ Ensures floating-point division.

////////////////////////////////////////////////////////////////////////////////////////////////////////////////
5️⃣ Lambdas in STL Algorithms
Lambdas are commonly used in STL algorithms.

🔹 1. Sorting with Lambda
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
int main() {
    vector<int> numbers = {5, 2, 8, 1, 3};
    sort(numbers.begin(), numbers.end(), [](int a, int b) { return a > b; });
    for (int num : numbers) cout << num << " ";
    return 0;
}
✅ Output:
8 5 3 2 1
✔ Lambda sorts the vector in descending order.

//----------------------------------------------------------------------------------------------------------------
🔹 2. Using for_each
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    vector<int> nums = {1, 2, 3, 4, 5};
    for_each(nums.begin(), nums.end(), [](int n) { cout << n * 2 << " "; });
    return 0;
}
✅ Output:
2 4 6 8 10
✔ Applies the lambda to each element.

//--------------------------------------------------------------------------------------------------------------

6️⃣ Lambdas with mutable Keyword

The mutable keyword allows modification of captured variables when using pass-by-value ([=]).
By default, lambdas cannot modify captured variables (if captured by value).
To modify them, use mutable.

🔹 Example: Using mutable
#include <iostream>
using namespace std;
int main() {
    int x = 10;
    auto modify1 = [x]() mutable { x += 5; cout << "1__Inside lambda: " << x << endl; }; // 15
  //auto modify1 = [x]()      { x += 5; cout << "1__Inside lambda: " << x << endl; };// give error because x is read only variable
   modify1(); 
   cout << "Outside lambda: " << x << endl;


    auto modify2 = [=]() mutable { x += 5; cout << "2__Inside lambda: " << x << endl; }; // 15
  //auto modify3 = [=]()     { x += 5; cout << "3__Inside lambda: " << x << endl; };// give error because x is read only variable
    modify2(); 
    cout << "Outside lambda: " << x << endl;  //  10


    auto modify3 = [&]() mutable { x += 5; cout << "3__Inside lambda: " << x << endl; };//15
  //auto modify3 = [&]()       { x += 5; cout << "3__Inside lambda: " << x << endl; };// 15, x will changes because passing x as &
   modify3();
    cout << "Outside lambda: " << x << endl; //   15 now x changes because we take x as &

    return 0;
}
✅ Output:
Inside lambda: 15   //  The change is only inside the lambda since x was captured by value.
Outside lambda: 10

Why Does not a Lambda Capturing by Value ([=]) Modify the Original Variable?
When a lambda captures a variable by value, it makes a copy of the variable. Any modifications inside the lambda only affect the copied variable, not the original one outside the lambda.
By default, lambdas treat captured variables as const, meaning you cannot modify them inside the lambda unless you explicitly allow it using the mutable keyword.


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Declaring and Using Lambda Functions Outside main() in C++ 
 Lambda functions in C++ are typically declared inside main(),
 but we can also declare them globally (outside main()) and use them both inside and outside main().

2. Declaring a Lambda Function Outside main()
Since C++ requires lambda functions to be stored in variables, we define them as auto outside main().

Example: Lambda Outside main() and Used Inside & Outside
#include <iostream>
using namespace std;
 
auto add = [](int a, int b) -> int {   // Global lambda function
    return a + b;
};
void useLambdaOutside() {           // Function using lambda outside main()
    cout << "Sum (outside main): " << add(10, 20) << endl;
}
int main() {
    useLambdaOutside();  // Using lambda outside main()
    cout << "Sum (inside main): " << add(5, 15) << endl; // Using lambda inside main()
    return 0;
}
🔹 Output:
 Sum (outside main): 30
 Sum (inside main): 20
 ✅ Explanation:
 The lambda add is declared globally and used inside useLambdaOutside() (outside main()).
 It is reused inside main() without redefining it.
//----------------------------------------------------------------------------------------------------------------
3. Lambda with Captured Variables (Global & Local Use)
We can use captured variables to store a value and use it across functions.
 #include <iostream>
 using namespace std;

 // Lambda capturing a constant value
 const int multiplier = 2;
 auto multiply = [](int x) { return x * multiplier; };
 
 void printMultiplied(int num) {
    cout << "Multiplied (outside main): " << multiply(num) << endl;
 }
 int main() {
     printMultiplied(10);  // Using lambda outside main()
     cout << "Multiplied (inside main): " << multiply(5) << endl;
     return 0;
 }
 🔹 Output:
 Multiplied (outside main): 20
 Multiplied (inside main): 10
 ✅ Key Takeaway:
 The capture list ([]) allows the lambda to access multiplier from the outer scope.

 ///////////////////////////////////////////////////////////////////////////////////////////////////////////////

 4. Lambda with Mutable Capture (Modifying Captured Variables)
 By default, captured variables are read-only inside a lambda. We can use the mutable keyword to modify them.

 include <iostream>
 using namespace std;
 
 // Lambda capturing a modifiable variable
 int counter = 0;
 auto increment = []() mutable {
    counter++;
    return counter;
 };
 void showIncrement() {
    cout << "Counter outside main: " << increment() << endl;
 }
 int main() {
     showIncrement();
     cout << "Counter inside main: " << increment() << endl;
     return 0;
 }
 🔹 Output:
 Counter outside main: 1
 Counter inside main: 2
 ✅ Key Point:
 The lambda modifies counter using mutable.

 //-----------------------------------------------------------------------------------------------------------
 5. Using Lambda with Function Pointers
 Since lambdas can be stored in function pointers, they can be passed as arguments.
 #include <iostream>
 using namespace std;
 
 // Lambda stored in a function pointer
 int (*operation)(int, int) = [](int a, int b) { return a * b; };
 
 void compute(int x, int y) {
     cout << "Multiplication (outside main): " << operation(x, y) << endl;
 }
 
 int main() {
     compute(4, 5);
     cout << "Multiplication (inside main): " << operation(3, 6) << endl;
     return 0;
 }
 🔹 Output:
 Multiplication (outside main): 20
 Multiplication (inside main): 18
 ✅ Why Use This?
 Useful for callbacks and higher-order functions.

 //------------------------------------------------------------------------------------------------------------
 6. Passing Lambda as Function Argument
 We can pass lambdas to functions to execute different logic.
 #include <iostream>
 using namespace std;
 
 // Function that accepts a lambda
 void executeLambda(int a, int b, auto func) {
    cout << "Lambda Result: " << func(a, b) << endl;
 }
 
 // Global lambda
 auto sum = [](int x, int y) { return x + y; };
 
 int main() {
     executeLambda(7, 8, sum);  // Passing global lambda
     executeLambda(5, 10, [](int x, int y) { return x * y; });  // Passing inline lambda
     return 0;
 }
 🔹 Output:
 Lambda Result: 15
 Lambda Result: 50
 ✅ Best Use Case:
 
 Higher-order functions in sorting, filtering, and callbacks.
 Final Summary
 Use Case	                                   Code Example
 Global Lambda Used Inside & Outside main()	   auto add = [](int a, int b) { return a + b; };
 Capturing External Variables	               auto multiply = [](int x) { return x * multiplier; };
 Mutable Capture for Modifiable Variables	   auto increment = []() mutable { counter++; return counter; };
 Using Lambda with Function Pointers	       int (*operation)(int, int) = [](int a, int b) { return a * b; };
 Passing Lambda as Function Argument	       executeLambda(7, 8, sum);

 🚀 Conclusion
 Declaring a lambda outside main() allows reuse across functions.
 Captured variables can be read-only or modifiable using mutable.
 Passing lambdas as function arguments enables powerful callback-based designs. 

 ////////////////////////////////////////////////////////////////////////////////////////////////////////////
What are the advantages of using lambda functions over traditional functions in C++?
How do lambda functions impact performance compared to regular functions?
When should I prefer using a lambda function instead of a named function?





