// why address/pointers not stored in register??
// accessing auot variable from other scope ?? using ::

storage classes define the scope (visibility), lifetime, and memory location of variables.
There are five major storage classes:
Automatic (auto)
External (extern)
Static (static)
Register (register)
Mutable (mutable) (specific to C++)
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

1.Automatic Storage Class-

The auto storage class is the default storage class for local variables in C. 
Variables declared with the auto keyword are automatically allocated memory when the function or block is entered and deallocated when the function or block exits. 
These variables are stored in the stack memory and have automatic duration.

Key Features of Auto Storage Class
✅Automatic Storage Duration
Memory is allocated when the variable is declared and deallocated when it goes out of scope.
It is only accessible within the function or block in which it is declared.

✅Default Storage Class
If no storage class is specified, a variable inside a function is considered auto by default.

✅Scope
It has a block scope, meaning it is accessible only within the block or function where it is declared.

✅Lifetime
The lifetime of an auto variable is limited to the execution of the function or block in which it is declared.

✅Storage Location
The memory for auto variables is allocated in the stack.

✅Initialization
The auto variable contains garbage value if not explicitly initialized.

Syntax
auto int a;  // Explicit declaration
int b;       // Implicitly auto (default behavior)
Both declarations are equivalent because auto is the default storage class for local variables.

Example 
#include <stdio.h>
void display() {
    auto int num = 10;  // 'auto' keyword is optional
    printf("Value of num: %d\n", num);
}
int main() {
    display();
    return 0;
}
Output
Value of num: 10
Here, the variable num is an auto variable inside the function display(). It is created when display() is called and destroyed when the function ends.

/*
In modern C++ (C++11 and later), auto is used for type inference instead of specifying the storage class.
Example of auto in C++ (Modern Usage - Type Inference)
#include <iostream>
using namespace std;
int main() {
    auto x = 10;      // x is deduced as int
    auto y = 3.14;    // y is deduced as double
    auto z = "Hello"; // z is deduced as const char*

    cout << "x: " << x << "\ny: " << y << "\nz: " << z << endl;
    return 0;
}
Output
x: 10
y: 3.14
z: Hello
Conclusion
In C, auto is a storage class specifier (though redundant because local variables are auto by default).
In C++, auto is used for type inference (C++11 and later), which allows the compiler to determine the type automatically.
If you're working in modern C++, forget about auto as a storage class—instead, use it for type deduction.

Key Differences Between C and C++
Feature	                    C	                                                              C++
auto keyword meaning	Specifies automatic storage duration (default for local variables)	Used for type deduction (automatically determines variable type)
Default storage class for local variables	    auto (implicitly used)	                    auto is not needed; local variables still have automatic storage
Example usage	       auto int x = 10; (valid but redundant)	                                auto x = 10; (x becomes int automatically)

Example of auto in C++ (Modern Usage - Type Inference)
#include <iostream>
using namespace std;
int main() {
    auto x = 10;      // x is deduced as int
    auto y = 3.14;    // y is deduced as double
    auto z = "Hello"; // z is deduced as const char*

    cout << "x: " << x << "\ny: " << y << "\nz: " << z << endl;
    return 0;
}
Output:
y: 3.14
z: Hello
 */

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

External Storage Class (extern) in C++ 

The external storage class in C++ is specified using the extern keyword. 
It is used to declare a global variable or function that is defined in another file or outside the current scope. 
The extern keyword tells the compiler not to allocate memory for the variable, as it is already defined elsewhere.

✅ It is mainly used for multi-file programming to share global variables or functions.
✅ const variables need extern if they are to be accessed from another file.
✅ extern does not work with local variables   —     only global variables and functions.

✅ The extern declaration does not allocate new memory for variable or function .Instead, it tells the compiler that variable or function exists somewhere else .

At link time, the linker resolves extern int num; to refer to num in file1.cpp.
Key Features of extern Storage Class
1.Global Scope
Variables declared with extern have global scope and can be accessed from multiple files.

2.Storage Location
extern variables are stored in the data segment of memory.

3.Lifetime
These variables exist throughout the program execution.

4.No Memory Allocation
The extern declaration does not allocate memory; it only refers to an existing definition.

5.Used for Multi-File Programming
It is commonly used when a variable or function is defined in one file and used in another.

Syntax
extern int a;  // Declaration (no memory allocation)
int a = 10;    // Definition (memory allocated)
The declaration using extern tells the compiler that a exists somewhere.
The definition actually allocates memory.

Example 1: Using extern in a Single File
#include <iostream>
using namespace std;
// Global variable
extern int num;  // Declaration (Tells compiler 'num' is defined somewhere)
int num = 50;    // Definition (Memory allocated)
//Even though num is declared before its definition, the program works correctly because extern tells the compiler that num exists somewhere.

void display() {
    cout << "Value of num: " << num << endl;
}
int main() {
    display();
    return 0;
}
Output
Value of num: 50
Here, num is declared with extern before it is defined.

Key Points to Remember
✅ extern is used only for declaration, not for definition.
✅ It helps in multi-file programming.
✅ The compiler does not allocate memory for extern variables.
✅ Functions can also be declared extern to be used across multiple files.
✅ If extern is used without a definition, the program will give a linker error.

//-----------------------------------------------------------------------------------------------------------------

✅ Advantages of Using extern
1️⃣ Enables Multi-File Programming (Code Reusability)
extern allows you to define variables or functions in one file and use them in another, making it easier to organize large projects.
Example: A math library can define functions in one file (math.cpp) and use them in multiple other files.

2️⃣ Reduces Memory Usage
Since extern does not create a new copy of a variable or function, it helps save memory by reusing the same global entity across multiple files.

3️⃣ Improves Compilation Speed
Without extern, large programs would need redundant variable/function definitions, slowing compilation.
extern lets different files use the same entity without duplication, making compilation faster.

4️⃣ Prevents Data Duplication and Linker Errors
Instead of defining a global variable in every file, extern allows one definition with multiple references, avoiding "multiple definition" linker errors.

5️⃣ Allows Sharing of Global Variables
When multiple files need to access the same global variable, extern ensures all files refer to one memory location, preventing inconsistencies.

//----------------------------------------------------------------------------------------------------------------

❌ Disadvantages of Using extern

1.unexpected behavior for global variables
If an extern variable is modified in one file, it changes everywhere, which can cause unintended side effects.
🔹 File 1: file1.cpp (Defines and Modifies Global Variable)
#include <iostream>
using namespace std;

int counter = 0;  // Global variable definition (stored in the data segment)
void increment() {
    counter++;  // Modifying the global variable
    cout << "Counter in file1 (after increment): " << counter << endl;
}

🔹 File 2: file2.cpp (Uses extern and Reads the Modified Value)
#include <iostream>
using namespace std;

extern int counter;  // Declaration (No memory allocated)
void increment();    // Function prototype

int main() {
    cout << "Initial Counter in file2: " << counter << endl;
    increment();  // Calls function from file1.cpp that modifies `counter`
    cout << "Counter in file2 (after function call): " << counter << endl;
    return 0;
}
🖥️ Expected Output
Initial Counter in file2: 0
Counter in file1 (after increment): 1
Counter in file2 (after function call): 1

🛑 Why is This a Problem?
counter is modified in file1.cpp, but the change affects file2.cpp as well.
If file2.cpp expected counter to remain 0, this change could cause unexpected behavior.

Debugging is harder because counter is modified in another file, making it difficult to trace
/*
✅ How to Avoid This Issue?
1️⃣Use static to Restrict Scope
If counter is needed only in file1.cpp, make it static:

#include <iostream>
using namespace std;

static int counter = 0;  // Restricted to file1.cpp
void increment() {
    counter++;  // Modifies only this file's variable
    cout << "Counter inside file1.cpp: " << counter << endl;
}

🔹 file2.cpp (Cannot Access counter)
#include <iostream>
using namespace std;

extern void increment();  // Only the function is accessible
int main() {
    increment();  // Calls function in file1.cpp
    increment();  // Calls again
    return 0;
}

Now, file2.cpp cannot access or modify it.

2️⃣ Use const for Read-Only Global Variables
If a global variable should not be modified, declare it as: extern const int counter;
This prevents unintended modifications.

🔹 file1.cpp (Defines a Read-Only Global Variable)
#include <iostream>
using namespace std;

const int counter = 100;  // Global constant (cannot be modified)

🔹 file2.cpp (Uses extern const to Read the Value)
#include <iostream>
using namespace std;

extern const int counter;  // Read-only access
int main() {
    cout << "Counter value: " << counter << endl;
    // counter++;  // ❌ Error: Cannot modify a const variable
    return 0;
}
🖥️ Expected Output
Counter value: 100  */

Another Disadvanatge
2️⃣ Harder to Debug
If an extern variable is unexpectedly modified, tracking down where the modification happened can be challenging.

3️⃣ Breaks Encapsulation (Global State is Bad)
extern exposes global variables/functions across multiple files, breaking the principle of encapsulation.
This reduces modularity, making the code harder to maintain.

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

✅Static Storage Class (static) in C++:
The static storage class determines the visibility (scope) and lifetime of a variable or function.
The static keyword in C++ has different behaviors depending on where it is used.
It can be applied to variables (both local and global), functions, and class members.

Definition and Behavior
1️⃣Lifetime: Variables declared as static have a lifetime that spans the entire execution of the program.

2️⃣Scope:
If a static variable is declared inside a function, it retains its value between function calls.
If a static variable is declared outside a function, it has file scope, meaning it is not accessible from other files.
If a static function is declared, it has internal linkage, meaning it is limited to that translation unit.


1️⃣📌 Example: Static Local Variable
#include <iostream>
using namespace std;

void counterFunction() {
    static int count = 0;  // Static variable retains value between calls
    count++;
    cout << "Counter value: " << count << endl;
}
int main() {
    counterFunction();  // Output: Counter value: 1
    counterFunction();  // Output: Counter value: 2
    counterFunction();  // Output: Counter value: 3
    return 0;
}
Explanation: The static variable count is initialized only once and retains its value across function calls.
✅ Why Use This?
Useful for tracking function calls or preserving state in recursion.

//---------------------------------------------------------------------------------------------------------------
2️⃣ Static Global Variables (File Scope)
🔹 Behavior:

A static global variable is restricted to the file it is declared in (file scope).
Unlike normal global variables, it cannot be accessed from other files using extern.

📌 Example: Static Global Variable
🔹 file1.cpp
#include <iostream>
using namespace std;

static int count = 10;  // Static global variable (not accessible in file2.cpp)
void display() {
    cout << "Count: " << count << endl;
}
🔹 file2.cpp
#include <iostream>
using namespace std;

extern void display();  // Can access the function, but not `count`

int main() {
    display();  // Output: Count: 10
    // cout << count;  // ❌ Error: 'count' is not accessible here
    return 0;
}
✅ Why Use This?
Prevents global variable conflicts in multi-file projects.
Ensures variables are only accessible where they are needed.

//----------------------------------------------------------------------------------------------------------------

3️⃣ Static Functions (Restricted to File Scope)
🔹 Behavior:

A static function is only accessible within the file where it is declared.
It cannot be called from another file.

📌 Example: Static Function
🔹 file1.cpp
#include <iostream>
using namespace std;

static void secretFunction() {  // Restricted to file1.cpp
    cout << "This is a static function" << endl;
}
void callSecretFunction() {
    secretFunction();  // This works fine within file1.cpp
}
🔹 file2.cpp
#include <iostream>
using namespace std;

extern void callSecretFunction();  // Allowed
int main() {
    callSecretFunction();  // ✅ Allowed, calls function from file1.cpp
    // secretFunction();  // ❌ Error: Cannot access a static function from another file
    return 0;
}
✅ Why Use This?
Encapsulates helper functions that are not needed outside a file.
Prevents name conflicts in multi-file projects.

//--------------------------------------------------------------------------------------------------------------

4️⃣ Static Class Members (Shared Across All Objects)
🔹 Behavior:
A static member variable belongs to the class instead of any specific instance (object). 
It is shared among all objects(instances) of the class.
🚀 Use static when you want shared data across all objects.
A static function can access only static members.
No this pointer in static functions (since they belong to the class, not instances).

📌 Example: 
1. Static Member Variable (Class-Level Variable)
#include <iostream>
using namespace std;

class Car {
    static int carCount;  // Static data member (shared across all objects)
public:
    Car() { carCount++; }  // Increments car count on object creation
    static void showCount() {  // Static function to access static data
        cout << "Total cars: " << carCount << endl;
    }
};
// Definition of static member outside the class
int Car::carCount = 0;
int main() {
    Car c1, c2, c3;  // 3 objects created
    Car::showCount();  // Output: Total cars: 3
    return 0;
}
Key Points:
✅ Declared inside the class but defined outside.
✅ Shared across all objects.
✅ Can be accessed without creating an object: MyClass::count.

✅ Why Use This?
Count total objects of a class (without using global variables).
Common configurations (e.g., settings shared among all objects).
/*
🚀 Why Accessing Static Members via Objects Can Be Confusing?
When a static member is accessed via an object, it may appear as though each object has its own copy of the variable. 
However, all objects share the same static member because it belongs to the class, not any specific object.

📌 Example: Multiple Objects Modifying a Static Variable
#include <iostream>
using namespace std;

class Counter {
public:
    static int count;  // Static variable (shared among all objects)
    void increment() {
        count++;  // Increments the shared variable
    }
    void showCount() {
        cout << "Count: " << count << endl;
    }
};
int Counter::count = 0;  // Initialize static variable outside the class

int main() {
    Counter obj1, obj2, obj3;
    obj1.increment();
    obj2.increment();
    obj3.increment();

    // Accessing static variable using different objects
    obj1.showCount();  // Output: Count: 3
    obj2.showCount();  // Output: Count: 3
    obj3.showCount();  // Output: Count: 3

    // Accessing the same variable using the class name (recommended)
    cout << "Accessing via class: " << Counter::count << endl;

    return 0;
}
🖥️ Expected Output
Count: 3
Count: 3
Count: 3
Accessing via class: 3
❌ Confusion Caused by Object Access
At first glance, it may seem like obj1, obj2, and obj3 each have a separate count variable.
However, since count is static, all objects share the same memory location for count.
Each call to increment() modifies the same variable, leading to confusion when accessing it via different objects.

*/

//----------------------------------------------------------------------------------------------------------------
2. Static Member Function
A static member function can access only static members (variables or other static functions). 
It does not have access to this pointer.

Example:
#include <iostream>
using namespace std;
class MyClass {
public:
    static int count;
    static void showCount() {  // Static member function
        cout << "Count: " << count << endl;
    }
};
int MyClass::count = 5;   // Definition of static member outside the class
int main() {
    MyClass::showCount();  // Calling without object  ✅ Correct way: Accessing static members using the class name
    return 0;
}
Key Points:
✅ Can be called without creating an object (MyClass::showCount()).
✅ Cannot access non-static members because it lacks this pointer.





