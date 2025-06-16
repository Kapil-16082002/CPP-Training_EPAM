
Templates in C++ allow writing generic and reusable code. 
They enable functions and classes to work with different data types without code duplication.

1️⃣ Types of Templates in C++
✅ 1. Function Templates
✅ 2. Class Templates
✅ 3. Variadic Templates (C++11)
✅ 4. Template Specialization
✅ 5. Template Non-Type Parameters

✅Advantages:
1. Code Reusability
Example: Instead of writing multiple versions of a function for int, float, double, etc., you can use templates:
template <typename T>
T add(T a, T b) {
    return a + b;
}
2. Reduced Code Size
By using templates, you avoid writing redundant code for similar functionalities that differ only by data type.

3. Type Safety:  Templates ensure type safety at compile time
4. Performance:  Templates are implemented at compile-time, which eliminates the overhead of runtime type checking
5.Generic Containers:
Templates are heavily used in the implementation of generic containers, such as C++ Standard Template Library (STL), including std::vector, std::list, and std::map. 

Disadvantages of Template->
.cpp               .obj                  .exe
Source code        Object code           executable code
            ----->>             ------>>
           Compiler             Linker
Templates in C++ increase the size of the object code because each template instantiation generates a separate version of the code for every different data_type used. 
This leads to code bloat and a larger .obj (object file) size.

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
1️⃣ Function Templates
A function template allows defining a function that can works with any data type.

🔹 Syntax:
template <typename T>     // Declares a template type T. The T is called a template type parameter( or placeholder for a data type)

T add(T a, T b) {
    return a + b;
}
T is a placeholder for the data type.
The compiler determines T based on the function call.
🔹 Example:
#include <iostream>
using namespace std;

template <typename T>
T add(T a, T b) {
    return a + b;
}
int main() {
    cout << "Addition (int): " << add(10, 20) << endl;
    cout << "Addition (double): " << add(10.5, 20.3) << endl;
    return 0;
}
🔹 Output:
Addition (int): 30
Addition (double): 30.8
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

How to Decide the Return Type of a Template Function?
In template functions with multiple types (T1, T2), the return type depends on how the compiler deduces the result type of an expression. 
Lets break this down.

✅1. Implicit Return Type (Compiler Deduction)
template <typename T1, typename T2>
T1 add(T1 a, T2 b) {
    return a + b;
}
The return type is T1, meaning the result will always be of the first type.
Problem: If T1 is int and T2 is double, the result will be truncated (loss of precision).
✅ Example:
cout << add(10, 20.5); // Output: 30 (instead of 30.5) because T1 is int

✅2. Using decltype to Infer Correct Return Type
To return the correct type based on a + b, use decltype(a + b):

template <typename T1, typename T2>
auto add(T1 a, T2 b) -> decltype(a + b) {
    return a + b;
}
decltype(a +b) deduces the type of (a + b) at compile time and uses it as the return type.
If a is int and b is double, the return type will be double.
No loss of precision or truncation issues.
✅ Example: cout << add(10, 20.5); // Output: 30.5 (correct!)


✅3.std::common_type<T1, T2>::type  (C++11 introduced )
 It determines a common return type based on available types.
#include <iostream>
#include <type_traits>

template<typename T1, typename T2>
typename std::common_type<T1, T2>::type subtract(T1 a, T2 b) {
    return a - b;
}

int main() {
    std::cout << subtract(5.5, 2) << std::endl;  // Common type is double
    std::cout << subtract(10, 3.6) << std::endl; // Common type is double
    return 0;
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

2️⃣ Class Templates
A class template allows defining a class with generic data types.

Common Use Cases for Class Templates
1.Custom Data Structures:Templates are commonly used to create generic data structures such as LinkedList, Stack, Queue, and BinaryTree.
2.Type-Safe Containers:Containers like std::vector, std::map, and std::set in the Standard Template Library (STL) are implemented using templates.

🔹 Example: Generic Class for a Pair
#include <iostream>
using namespace std;
template <typename T1, typename T2>
class Pair {
private:
    T1 first;
    T2 second;
public:
    Pair(T1 a, T2 b) : first(a), second(b) {}
    void display() { cout << "First: " << first << ", Second: " << second << endl; }
};
int main() {
    Pair<int, double> p1(10, 5.5);
    p1.display();

    Pair<string, char> p2("Hello", 'A');
    p2.display();

    return 0;
}
🔹 Output:
First: 10, Second: 5.5
First: Hello, Second: A

Class Template with Default Types
You can specify default template arguments, which are used if no specific type is provided during instantiation.

#include <iostream>
using namespace std;

template<typename T = int>
class MyClass {
private:
    T data;
public:
    MyClass(T value) : data(value) {}

    T getData() { return data; }
};
int main() {
    MyClass<> obj1(10);      // Default type is int
    MyClass<float> obj2(3.14f);

    cout << "Default type (int): " << obj1.getData() << endl;
    cout << "Explicit type (float): " << obj2.getData() << endl;

    return 0;
}
Output:
Default type (int): 10
Explicit type (float): 3.14


////////////////////////////////////////////////////////////////////////////////////////////////////////////////

3️⃣ Variadic Templates (C++11)
Variadic templates allow passing any number of arguments to a function or class template.

🔹 Example: Variadic Template Function
#include <iostream>
using namespace std;
template <typename T, typename... Args>
void print(T first, Args... rest) {
    cout << first << " ";
    if constexpr (sizeof...(rest) > 0) // Check if more arguments exist
        print(rest...); // Recursive call
}
int main() {
    print(1, 2.5, "Hello", 'A');
    return 0;
}
🔹 Output:
1 2.5 Hello A

✅What typename... Args  Means?
used to define a variadic template in the language (introduced in C++11).
...  The ellipsis (...) signifies that this is a parameter pack, and it can accept multiple (or no) template arguments.
Args is the name of the parameter pack.

constexpr:
A compile-time conditional introduced in C++17.
It ensures that the expression evaluated at compile time.


#include <iostream>
#include <utility> // for std::index_sequence
using namespace std;
// Variadic template function
template <typename... Args>
void print(Args... args) {
    // Use a fold expression to iterate over the parameter pack
    ((cout << args << " "), ...); // Fold expression applies the operation to all arguments
    cout << endl; // Add a newline at the end
}
int main() {
    print(1, 2.5, "Hello", 'A'); // Passing variadic arguments
    return 0;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

4️⃣ Template Specialization
Template specialization allows writing a specific implementation for a particular type.
Full specialization allows writing a custom, type-specific implementation for a template.

#include <iostream>
using namespace std;
// Generic Template Function
template <typename T>  //primary template for print.
void print(T value) {         
    cout << "Generic Value: " << value << endl;
}
// Full Specialization for string
template <>
void print<string>(string value) {        // Takes 1 Argument
    cout << "String Value: " << value << endl;
}
int main() {
    print(10);        // Uses Generic Template 
    print(3.14);      // Uses Generic Template
    print("Hello");   // invokes the specialized function for string. Uses Specialized Template
    return 0;
}
🔹 Explanation:
template <> → This indicates that the function is a full specialization of a previously defined function template. 
The empty angle brackets (<>) mean that no additional template parameter is being introduced.
void print<string>(string value) → This defines a special version of the print function specifically for the string type.

A full specialization must match exactly the structure of the primary template.
Primary Template and Full Specialization Must Have the Same Number of Arguments.


🔹 Why Use Specialization?
This is useful when you want a custom implementation for a specific type (string in this case) while keeping a generic template for other types.
Full Specialization Requires a Primary Template-> 
Full specialization (template <>) only works if there is a previously defined primary function template.
If the compiler does not find a primary template print<T>, it won’t know what function you are trying to specialize.

🔹 Example: Specialized Template for 
#include <iostream>
using namespace std;

template <typename T>     // Generic template
class Printer {
public:
    void print(T value) {
        cout << "General template: " << value << endl;
    }
};
template <>   // Full specialization for type `int`
class Printer<int> {
public:
    void print(int value) {
        cout << "Specialized for int: " << value << endl;
    }
};
int main() {
    Printer<double> obj1;  
    obj1.print(3.14);  // Calls generic template

    Printer<int> obj2;  
    obj2.print(42);  // Calls specialized template
    return 0;
}


#include <iostream>
#include <string>
using namespace std;

template <typename T1, typename T2>
class Printer {
public:
    static void print(T1 value1, T2 value2) {
        cout << "Value: " << value1 + value2 << endl;
    }
};

// Specialized version when T1 = string and T2 = string
template <>
class Printer<string, string> {  // Now matches the structure of the primary template
public:
    static void print(string value1, string value2) {
        cout << "Concatenated String Value: " << value1 + value2 << endl;
    }
};
int main() {
    Printer<int, int>::print(10, 20);       // Calls the generic template
    Printer<double, double>::print(10.5, 20.5); // Calls the generic template
    Printer<string, string>::print("Hello", " World"); // Calls the specialized version

    return 0;
}
🔹 Output:
Value: 30
Value: 31
Concatenated String Value: Hello World

/* This code will not work ->  

#include <iostream>
using namespace std;
//Specialized version for char*
template <>
class Printer<string> {
public:
    static void print( string value) {
        cout << "String Value: " << value << endl;
    }
};
int main() {
    Printer<string>::print("Hello");
    return 0;
}
Output: error: 'Printer' is not a template
🚨 Issue: No Primary Template for Printer<T>
You have provided a specialization of Printer<string>, but there is no primary template for Printer<T>.
Since Printer<string> is a specialization, the compiler expects a general template for Printer<T> to exist.
Without a primary template, the compiler does not know what Printer<T> is for other types.

*/
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

5️⃣ Template Non-Type Parameters
Templates can also take constant values as parameters.

🔹 Example: Array Wrapper with Fixed Size
#include <iostream>
using namespace std;
template <typename T, int size>
class Array {
private:
    T arr[size];
public:
    void set(int index, T value) { arr[index] = value; }
    T get(int index) { return arr[index]; }
};
int main() {
    Array<int, 5> arr;
    arr.set(0, 10);
    cout << "First Element: " << arr.get(0) << endl;
    return 0;
}
🔹 Output:
First Element: 10
6️⃣ Use Cases of Templates
Use Case	                       Description
Mathematical Operations	           Creating generic math functions.
Data Structures	                   Generic implementation of Stack, Queue, LinkedList, etc.
Smart Pointers	                   std::unique_ptr<T>, std::shared_ptr<T> in C++ STL.
Generic Algorithms	               Sorting, searching using templates.
Compile-time Computation	       Meta-programming techniques.

🔟 Final Thoughts
✅ Templates make code reusable and efficient.
✅ Avoid unnecessary using namespace std; in large projects.
✅ Use explicit specialization when needed.
✅ Understand STL containers, which heavily rely on templates.
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

🔹 Types of Template Specialization
Full Specialization –     Specializes a template for a specific type.
Partial Specialization –  Specializes a template for a subset of template parameters.
Function Template Specialization – Specializes a function template for a specific type.
Member Function Specialization – Specializes a specific member function of a template class.
Variable Template Specialization (C++14) – Specializes template variables.

2. Full Specialization:
Full specialization completely overrides the primary template for a particular type.

📌 Example: Full Specialization of a Class Template
#include <iostream>
using namespace std;
template <typename T>     // Generic template
class Printer {
public:
    void print(T value) {
        cout << "General template: " << value << endl;
    }
};
template <>   // Full specialization for type `int`
class Printer<int> {
public:
    void print(int value) {
        cout << "Specialized for int: " << value << endl;
    }
};
int main() {
    Printer<double> obj1;  
    obj1.print(3.14);  // Calls generic template

    Printer<int> obj2;  
    obj2.print(42);  // Calls specialized template
    return 0;
}
✅ Output:
General template: 3.14
Specialized for int: 42
✔ The specialized class completely replaces the generic template for int.
//-----------------------------------------------------------------------------------------------------------

3. Partial Specialization
Partial specialization allows modifying a subset of the template parameters while keeping others generic.

📌 Example: Partial Specialization
#include <iostream>
using namespace std;

// General template
template <typename T1, typename T2>
class Pair {
public:
    void show() { cout << "General template" << endl; }
};

// Partial specialization when both types are the same
template <typename T>
class Pair<T, T> {
public:
    void show() { cout << "Partial specialization: Same type" << endl; }
};
int main() {
    Pair<int, double> obj1;
    obj1.show();  // Calls general template

    Pair<int, int> obj2;
    obj2.show();  // Calls partial specialization

    return 0;
}
✅ Output:
General template
Partial specialization: Same type
✔ The specialization triggers only when both template parameters are the same.

//---------------------------------------------------------------------------------------------------------------
4. Function Template Specialization
Function template specialization is used to define a different implementation of a function template for a specific type.

📌 Example: Function Template Specialization
#include <iostream>
using namespace std;

// Generic template function
template <typename T>
void display(T value) {
    cout << "Generic function: " << value << endl;
}

// Specialization for `char*`
template <>
void display<char*>(char* value) {
    cout << "Specialized for char*: " << value << endl;
}

int main() {
    display(100);  // Calls generic function
    display("Hello");  // Calls specialized function

    return 0;
}
✅ Output:
Generic function: 100
Specialized for char*: Hello
✔ The specialized version only applies to char*, while other types use the generic version.

//--------------------------------------------------------------------------------------------------------------

5. Member Function Specialization
You can specialize a single function inside a class template while keeping the rest generic.

📌 Example: Specializing a Member Function
#include <iostream>
using namespace std;

// General template
template <typename T>
class Demo {
public:
    void show(double val) {
        cout << "Generic class" << endl;
    }

    // Specialization for `int`
    void show(int value) {
        cout << "Specialized member function for int: " << value << endl;
    }
};
int main() {
    Demo<double> obj1;
    obj1.show();  // Calls generic function

    Demo<int> obj2;
    obj2.show(42);  // Calls specialized function

    return 0;
}
✅ Output:
Generic class
Specialized member function for int: 42
✔ The show(int value) function is only specialized while the rest remains generic.

//--------------------------------------------------------------------------------------------------------------

6. Variable Template Specialization (C++14)
Variable template specialization allows defining a specialized variable for specific types.

📌 Example: Variable Template Specialization
#include <iostream>
using namespace std;
// Generic template variable
template <typename T>
constexpr T pi = T(3.141592653589793);

// Specialization for `int`
template <>
constexpr int pi<int> = 3;

int main() {
    cout << "pi<double>: " << pi<double> << endl;  // Uses generic template
    cout << "pi<int>: " << pi<int> << endl;  // Uses specialized template

    return 0;
}
✅ Output:
pi<double>: 3.14159
pi<int>: 3
✔ The generic version keeps high precision, while the int specialization rounds the value.

///////////////////////////////////////////////////////////////////////////////////////////////////////////////

Template Metaprogramming (TMP) ???->
Template Metaprogramming (TMP) is a technique in C++ that uses templates to perform computations at compile time. 
This allows optimizations, static assertions, and conditional logic before the program even runs.

Key Features of TMP:
Compile-time computations (no runtime overhead)
Type manipulations (type traits, type transformations)
Conditional branching (similar to if-else, but at compile time)
Recursion-based loops (no actual loops, recursion is used)


Example: Here’s a compile-time factorial calculation using TMP.

#include <iostream>
using namespace std;

// Primary template function for factorial computation
template <int N>
constexpr int Factorial() {
    return N * Factorial<N - 1>();
}

// Specialization for the base case
template <>
constexpr int Factorial<0>() {
    return 1;
}
int main() {
    // Compute Factorial of 5
    cout << "Factorial of 5: " << Factorial<5>() << endl;
    return 0;
}



#include <iostream>
using namespace std;
template <int N>      // Primary template for factorial computation
struct Factorial {
    static const int value = N * Factorial<N - 1>::value;
};
template <>
struct Factorial<0> {         // Specialization for base case (Factorial of 0 is 1)
    static const int value = 1;
};
int main() {
    cout << "Factorial of 5: " << Factorial<5>::value << endl;
    return 0;
}
✅ Output:
✔ Factorial is computed at compile time, so there is no runtime overhead.

//-------------------------------------------------------------------------------------------------------------

#include <iostream>
using namespace std;
// Primary template for factorial computation
template <int N>
class Factorial {
public:
    static const int value = N * Factorial<N - 1>::value;
};
// Specialization for base case (Factorial of 0 is 1)
template <>
class Factorial<0> {
public:
    static const int value = 1;
};
int main() {
    cout << "Factorial of 5: " << Factorial<5>::value << endl;
    return 0;
}
//-------------------------------------------------------------------------------------------------------------

constexpr Keyword in c++ -> 
constexpr (short for "constant expression") is a keyword in C++ that tells the compiler that a function or a variable can be evaluated at compile time. 
This allows for optimizations and ensures that values are computed before runtime, reducing unnecessary computations.

#include <iostream>
constexpr int square(int x) {
    return x * x;
}
int main() {
    constexpr int num = 5; // num is known at compile-time
    constexpr int result = square(num); // square(5) is computed at compile-time
    std::cout << "Square of 5: " << result << std::endl;
    return 0;
}

Using constexpr with Class Template (Factorial Example) ->
#include <iostream>
using namespace std;
template <int N>
constexpr int Factorial() {          // Primary template for factorial computation
    return N * Factorial<N - 1>();
}
template <>                         // Specialization for base case (Factorial of 0 is 1)
constexpr int Factorial<0>() {
    return 1;
}
int main() {
    cout << "Factorial of 5: " << Factorial<5>() << endl;
    return 0;
}
🔹 Key Points:
The factorial of 5 (Factorial<5>::value) is calculated before runtime.
The compiler replaces Factorial<5>::value with 120 directly in the binary.
This eliminates function calls and improves performance.

const int x = 5;          // Run-time constant
constexpr int y = 10;     // Compile-time constant
int arr[y]; // ✅ Allowed (since y is compile-time constant)
int arr[x]; // ❌ Error (x is not guaranteed to be compile-time)


////////////////////////////////////////////////////////////////////////////////////////////////////////////////

🔹 1️⃣ "Undefined Reference" Error
🔸 Reason: Function template is declared but not instantiated.
🔹 Solution: Ensure function is called with correct types.
Example (Incorrect)
template <typename T>
void show() {
    cout << "Template function called" << endl;
}
int main() {
    show<int>(); // 🚨 Undefined reference (not instantiated)
    return 0;
}

Solution (Call the Function)
#include <iostream>
using namespace std;
template <typename T>
void show() {
    cout << "Template function called" << endl;
}
int main() {
    show<int>(); // ✅ Now it's instantiated and works.
    return 0;
}
/////////////////////////////////////////////////////////
🔹 2️⃣ Ambiguous Overload
🔸 Reason: Multiple template instances match the call.
🔹 Solution: Use explicit specialization.

Example (Incorrect)
template <typename T>
void print(T value) {
    cout << "Generic print: " << value << endl;
}
template <>
void print(int value) {
    cout << "Specialized print: " << value << endl;
}
int main() {
    print(10);  // 🚨 Ambiguous: Which `print` to use?
    return 0;
}
Solution: (Use Different Function Names or Remove General Template)

template <typename T>
void printValue(T value) {
    cout << "Generic print: " << value << endl;
}
template <>
void printValue<int>(int value) { // ✅ Explicit specialization
    cout << "Specialized print: " << value << endl;
}
int main() {
    printValue(10);  // ✅ Now it works.
    return 0;
}
/////////////////////////////////////////////////////////////

🔹 3️⃣ Template Instantiation Error
🔸 Reason: Incorrect or missing template arguments.
🔹 Solution: Pass correct type parameters.

Example (Incorrect)
template <typename T>
class Box {
    T value;
public:
    Box() { value = 0; }  // 🚨 ERROR: Cannot assign int to `T` always.
};
int main() {
    Box b;  // 🚨 ERROR: Missing type parameter
}
Solution (Specify Type)

Box<int> b; // ✅ Now the template knows `T = int`

/////////////////////////////////////////////////////

🔹 4️⃣ Complex Debugging
🔸 Reason: Templates create multiple copies of the code.
🔹 Solution: Use explicit instantiations to debug only required cases.

Example
template <typename T>
T add(T a, T b) {
    return a + b;
}

// Explicit instantiation for debugging
template int add<int>(int, int);
template double add<double>(double, double);

//////////////////////////////////////////////////

🔹 5️⃣ Non-Deduced Context Error
🔸 Reason: The compiler cannot infer the template type.
🔹 Solution: Explicitly specify template arguments.

Example (Incorrect)
template <typename T>
void func(T x, T y) {}
int main() {
    func(1, 2.5); // 🚨 ERROR: T cannot be both `int` and `double`
}
Solution
func<double>(1, 2.5); // ✅ Explicitly specify template type.

///////////////////////////////////////////////////////////

🔹 6️⃣ Linker Errors with Separate Compilation
🔸 Reason: Function template is defined in .cpp but not instantiated.
🔹 Solution: Define templates in header files.

Example (Incorrect)
// file: mytemplate.h
template <typename T>
void show(T val);
// file: mytemplate.cpp
template <typename T>
void show(T val) { cout << val; } // 🚨 ERROR: Not visible in other files
Solution (Define in Header File)
// file: mytemplate.h
template <typename T>
void show(T val) { cout << val; } // ✅ Works

//////////////////////////////////////////////

🔹 7️⃣ Overuse of Templates (Code Bloat)
🔸 Reason: Too many template instances increase binary size.
🔹 Solution: Use template specializations where necessary.

Example (Reduce Instantiations)
template <typename T>
void compute(T value);
template <>
void compute<int>(int value) { /* Special case for int */ }

compute<int>(5); // ✅ Only instantiates for int.

////////////////////////////////////////////////////////

🔹 8️⃣ SFINAE (Substitution Failure Is Not An Error)
🔸 Reason: Some template specializations fail unexpectedly.
🔹 Solution: Use std::enable_if for better control.

Example: Restrict to Integers Only
#include <iostream>
#include <type_traits>
using namespace std;
template <typename T, typename enable_if<is_integral<T>::value, int>::type = 0>
void process(T value) {
    cout << "Integer processing: " << value << endl;
}
int main() {
    process(10);  // ✅ Works for int
    // process(10.5); // 🚨 ERROR: Disabled for double
    return 0;
}
🎯 Summary
Issue	                Reason	                                   Solution
Undefined Reference  	Template not instantiated properly	       Call function with correct types
Ambiguous Overload	    Multiple template matches	               Use explicit specialization
Instantiation Error	    Missing or incorrect type	               Verify type arguments
Complex Debugging	    Multiple template copies	               Use explicit instantiations
Non-Deduced Context	    Compiler cannot infer type	               Explicitly specify template type
Linker Errors	        Templates not defined in headers	       Move template definitions to header files
Code Bloat	            Too many template instances	               Reduce unnecessary specializations
SFINAE Issues	        Unexpected failures	                        Use std::enable_if for better control

//////////////////////////////////////////////////////////////////////////////////////////////////////////////

Disadvantages of Template->
.cpp               .obj                  .exe
Source code        Object code           executable code
            ----->>             ------>>
           Compiler             Linker
Templates in C++ increase the size of the object code because each template instantiation generates a separate version of the code for every different type used. 
This leads to code bloat and a larger .obj (object file) size.


🔹 How Templates Cause Larger Object Code?
🔸 1️⃣ Multiple Instantiations of the Same Code->
Every time a template is used with a new type, the compiler creates a new version of the code.
Example: Template Instantiation
#include <iostream>
using namespace std;

template <typename T>
void show(T value) {
    cout << "Value: " << value << endl;
}

int main() {
    show(10);     // Creates show<int>()
    show(10.5);   // Creates show<double>()
    show('A');    // Creates show<char>()
}
🔍 How This Affects .obj Size
The compiler does not generate one single show() function.
Instead, it creates separate copies for:
show<int>()
show<double>()
show<char>()
This duplicates code and increases .obj file size.

//////////////////////////////////////////////////////////

🔹 2️⃣ Code Bloat Due to Class Templates
With class templates, every different data type creates a new class definition, leading to more compiled code.

Example: Class Template Instantiations
template <typename T>
class Data {
    T value;
public:
    Data(T val) : value(val) {}
    void display() { cout << "Value: " << value << endl; }
};

int main() {
    Data<int> d1(10);       // Generates Data<int>
    Data<double> d2(10.5);  // Generates Data<double>
    Data<char> d3('A');     // Generates Data<char>
}
🔍 How This Affects .obj Size
The compiler creates different versions:
Data<int>
Data<double>
Data<char>
Each version contains its own separate copy of:
The constructor
display() function
This significantly increases the .obj file size.

//////////////////////////////////////////////////////////////////

🔹 3️⃣ Templates Are Instantiated in Every Compilation Unit
Templates must be instantiated in every .cpp file that uses them, leading to duplicate template instantiations across multiple files.

Example: Using Templates in Multiple Files
Header File (mytemplate.h)
template <typename T>
void show(T value) {
    cout << value << endl;
}
File 1 (file1.cpp)
#include "mytemplate.h"
void func1() {
    show(100);  // Instantiates show<int>()
}
File 2 (file2.cpp)
#include "mytemplate.h"
void func2() {
    show(100);  // Instantiates show<int>() again!
}
🔍 Effect:

show<int>() is instantiated twice, once in file1.obj and again in file2.obj.
This duplicates the object code and increases the overall executable size.
✅ Solution: Use explicit instantiation in one .cpp file and extern declaration elsewhere.

////////////////////////////////////////////////////////////

🔹 4️⃣ Lack of Optimization (Inlining Issue)
Templates are not always inlined by the compiler.
If inlining is disabled, each instantiation adds extra function call overhead, further increasing object code size.
Example: Template Function Not Inlined
template <typename T>
void show(T value) {
    cout << value << endl;  // If not inlined, this adds function call overhead
}
✅ Solution: Use inline keyword when applicable.
template <typename T>
inline void show(T value) {
    cout << value << endl;
}
///////////////////////////////////////////////////////////////
🔹 5️⃣ Explicit Specialization Can Further Increase .obj Size
If explicit specializations are created, they add extra copies of template code.

Example: Specialized Template
template <typename T>
class Printer {
public:
    static void print(T value) {
        cout << "Value: " << value << endl;
    }
};

// Specialization for `string`
template <>
class Printer<string> {
public:
    static void print(string value) {
        cout << "String Value: " << value << endl;
    }
};

int main() {
    Printer<int>::print(10);      // Creates Printer<int>
    Printer<double>::print(10.5); // Creates Printer<double>
    Printer<string>::print("Hi"); // Creates specialized Printer<string>
}
🔍 Effect on .obj Size

The compiler generates separate versions for:
Printer<int>
Printer<double>
Specialized Printer<string>
This further adds extra code, increasing object file size.
✅ Solution: Avoid unnecessary specializations and use partial specialization when possible.

🔹 6️⃣ STL Containers Use Templates and Cause Code Bloat
Using Standard Template Library (STL) containers (like vector, map, set) generates new code for each data type.

Example: STL Template Code Bloat
#include <vector>
using namespace std;
vector<int> v1;     // Generates code for vector<int>
vector<double> v2;  // Generates code for vector<double>
🔍 Effect on .obj File

vector<int> and vector<double> are compiled separately, increasing file size.
✅ Solution: Use references (vector<int>&) when possible to avoid redundant instantiations.


////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Interview Related Questions?? 
Why can not  we separate template definitions into .cpp files like normal functions?
Answer:
Templates must be defined in header files because they are instantiated at compile-time.
🔹 What Happens If You Put Template Code in a .cpp File?
🚨 Error! The compiler will not find the definition.
Example (Incorrect Approach):
mytemplate.h
template <typename T>
void show(T value);

mytemplate.cpp
#include "mytemplate.h"
template <typename T>
void show(T value) { cout << value << endl; }

main.cpp
#include "mytemplate.h"
int main() {
    show(5); // ❌ ERROR: Undefined reference to `show<int>`
    return 0;
}
🔴 Why?
The compiler does not know which types will be used at the time of compilation.

🔹 Correct Approach: Put the Definition in the Header File
mytemplate.h
#ifndef MYTEMPLATE_H
#define MYTEMPLATE_H

#include <iostream>
using namespace std;

template <typename T>
void show(T value) { cout << value << endl; }
#endif
✅ Solution:
Define templates in header files to ensure proper instantiation.

////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Can templates cause an increase in binary size? How do compilers optimize this?
Answer:
Yes, templates can increase binary size because each instantiation creates a new version of the function/class, leading to code bloat.

Example (Code Bloat Problem):
template <typename T>
void print(T value) {
    cout << "Value: " << value << endl;
}
int main() {
    print(10);    // Instantiates print<int>
    print(3.14);  // Instantiates print<double>
    print('A');   // Instantiates print<char>
    return 0;
}
✅ Solution:
Use constexpr when possible to evaluate expressions at compile-time.
Explicitly instantiate common types instead of allowing multiple instantiations.
Example (Optimization Using Explicit Instantiation):
template <typename T>
void print(T value) { cout << "Value: " << value << endl; }

// Explicitly instantiate only required versions
template void print<int>(int);
template void print<double>(double);

int main() {
    print(10);    // Uses precompiled print<int>
    print(3.14);  // Uses precompiled print<double>
    return 0;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

What is the difference between explicit and implicit template instantiation?
non-type template parameters ?? 