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
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
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

🔹 Example: Specialized Template for char*
#include <iostream>
using namespace std;
template <typename T>
class Printer {
public:
    static void print(T value) {
        cout << "Value: " << value << endl;
    }
};
// Specialized version for char*
template <>
class Printer<char*> {
public:
    static void print(char* value) {
        cout << "String Value: " << value << endl;
    }
};
int main() {
    Printer<int>::print(10);
    Printer<double>::print(10.5);
    Printer<char*>::print("Hello");
    return 0;
}
🔹 Output:
Value: 10
Value: 10.5
String Value: Hello
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
Use Case	Description
Mathematical Operations	Creating generic math functions.
Data Structures	Generic implementation of Stack, Queue, LinkedList, etc.
Smart Pointers	std::unique_ptr<T>, std::shared_ptr<T> in C++ STL.
Generic Algorithms	Sorting, searching using templates.
Compile-time Computation	Meta-programming techniques.
7️⃣ Templates in STL (Standard Template Library)
The C++ STL heavily uses templates for generic data structures.

🔹 Example: Using std::vector<int>
#include <iostream>
#include <vector>
using namespace std;
int main() {
    vector<int> v = {1, 2, 3, 4, 5};
    for (int num : v) {
        cout << num << " ";
    } 
    return 0;
}
🔹 Output:
1 2 3 4 5
8️⃣ Common Issues & Solutions in Templates
Issue	Reason	Solution
Error: "undefined reference"	Function template is not instantiated properly.	Call the function with correct types.
Ambiguous Overload	Multiple template instances match.	Use explicit specialization.
Template Instantiation Error	Incorrect or missing type parameters.	Verify template usage.
Complex Debugging	Templates create multiple versions of code.	Use explicit instantiations for debugging.
9️⃣ Summary
Concept	Usage
Function Template	Generic function for multiple data types.
Class Template	Generic class for data structures.
Variadic Templates	Functions that take multiple arguments.
Template Specialization	Custom implementation for specific types.
Non-Type Template Parameters	Templates with constant values.
🔟 Final Thoughts
✅ Templates make code reusable and efficient.
✅ Avoid unnecessary using namespace std; in large projects.
✅ Use explicit specialization when needed.
✅ Understand STL containers, which heavily rely on templates.