Templates in C++ (Complete Guide with Code & Use Cases)
Templates in C++ allow writing generic and reusable code. They enable functions and classes to work with different data types without code duplication.

1️⃣ Types of Templates in C++
✅ 1. Function Templates
✅ 2. Class Templates
✅ 3. Variadic Templates (C++11)
✅ 4. Template Specialization
✅ 5. Template Non-Type Parameters

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
1️⃣ Function Templates
A function template allows creating a function that works with any data type.

🔹 Syntax:
template <typename T>
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
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
2️⃣ Class Templates
A class template allows defining a class with generic data types.

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

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

4️⃣ Template Specialization
Template specialization allows writing a specific implementation for a particular type.

🔹 Example: Specialized Template for 
#include <iostream>
#include <string>
using namespace std;

template <typename T>
class Printer {
public:
    static void print(T value) {
        cout << "Value: " << value << endl;
    }
};
// Specialized version for std::string
template <> 
class Printer<string> {      // this specialization applies ONLY when T = string.
public:
    static void print(string value) {
        cout << "String Value: " << value << endl;
    }
};

int main() {
    Printer<int>::print(10);       // Calls the generic template
    Printer<double>::print(10.5);  // Calls the generic template
    Printer<string>::print("Hello"); // Calls the specialized version

    return 0;
}
🔹 Output:
Value: 10
Value: 10.5
String Value: Hello

Explanation:
1️⃣ template <>
This declares a template specialization.
The empty angle brackets <> mean this is a full specialization, not a generic template.
Unlike normal templates (template <typename T>), here we don’t have a generic type because we are specializing for a specific type (string).

2️⃣ class Printer<string>
class Printer<string> {
This defines a specialized version of the Printer class only for string (which is std::string).
Normally, templates allow us to use Printer<T> for different data types (int, double, etc.), but this is a special case that only applies when T = string.

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
////////////////////////////////////
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
Solution (Use Different Function Names or Remove General Template)
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
/// @brief /////////////////////////////////////////

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