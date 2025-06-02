✅Static Storage Class (static) in C++:
Static variables are stored in a special segment of memory called the data segment, rather than the stack.
The static storage class determines the visibility (scope) and lifetime of a variable or function.
Static global variables/functions have internal linkage, meaning they are not shared across (files).

Definition and Behavior
1️⃣Lifetime: Variables declared as static have a lifetime that spans the entire execution of the program.

2️⃣Scope:
If a static variable is declared inside a function, it retains its value between function calls.
If a static variable is declared outside a function, it has file scope, meaning it is not accessible from other files.
If a static function is declared, it has internal linkage, meaning it is not accessible from other files.


✅Types of Static Variables

1.Static Local Variables:
Declared inside a function or block.
Scope is local to the function/block, but their value persists throughout the program’s execution.

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


2.Static Global Variables:
Declared outside of any function.
Scope is limited to the file in which they are defined (internal linkage).

#include <iostream>
using namespace std;

static int globalVar = 10; // File-scoped static variable
void demo() {
    cout << "GlobalVar: " << globalVar << endl;
}
int main() {
    demo();
    return 0;
}


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
/* 
Static member function can access only static members (variables or other static functions). 

Non-static member function can access static member variables and static member functions of the class. 
This is because a non-static member function belongs to an object of the class, and object of any class have  access to the class-level data (i.e., static members).
*/
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

//-----------------------------------------------------------------------------------------------------------------

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

//----------------------------------------------------------------------------------------------------------------

✅Static Objects of a Class:

A static object is created only once and persists throughout the lifetime of the program.
Its constructor is called only once, and its destructor is invoked when the program ends.

Static Object of a Class:
A static object of a class is declared using the static keyword. 

It has the following characteristics:
It is shared among all instances of the class.
It is allocated memory only once (in the global or static storage area).
It is destroyed automatically when the program ends.
It is independent of any particular instance of the class (it belongs to the class itself).

#include <iostream>
class MyClass {
public:
    MyClass() {
        std::cout << "Constructor called\n";
    }
    ~MyClass() {
        std::cout << "Destructor called\n";
    }
};
void function() {
    static MyClass obj; // Static object inside a function
}
int main() {
    function(); // First call, static object gets created
    function(); // Second call, static object is not created again
    return 0;
}

✅Static Objects in Different Scopes
#include <iostream>
using namespace std;

class MyClass {
public:
    MyClass() { cout << "Constructor called\n"; }
    ~MyClass() { cout << "Destructor called\n"; }
    void print() { cout << "Static object function called\n"; }
};
void function1() {
    static MyClass obj1; // Static object in function1
    obj1.print();
}
void function2() {
    static MyClass obj2; // Static object in function2
    obj2.print();
}
int main() {
    function1(); // obj1 is created and initialized in function1
    function2(); // obj2 is created and initialized in function2
    function1(); // obj1 persists and is reused
    function2(); // obj2 persists and is reused
    return 0;
}
Output:
Constructor called
Static object function called
Constructor called
Static object function called
Static object function called
Static object function called
Destructor called
Destructor called

✅Explanation:
obj1 and obj2 are static objects, but they are scoped within function1 and function2 respectively.
They are initialized once during the first call to their respective functions.
On subsequent calls, the existing static object is reused (rather than being reinitialized).

//---------------------------------------------------------------------------------------------------------------

#include <iostream>
class MyClass {
public:
    MyClass() {
        std::cout << "Constructor called for static object\n";
    }
    ~MyClass() {
        std::cout << "Destructor called for static object\n";
    }
};
int main() {
    std::cout << "Program started\n";

    static MyClass obj1; 
    static MyClass obj2;

    std::cout << "Program is running\n";
}
Output:
Program started
Constructor called for non-static object
Constructor called for non-static object
Program is running
Destructor called for non-static object
Destructor called for non-static object

//----------------------------------------------------------------------------------------------------------------

✅Example: Class with Two Static Objects
#include <iostream>

class MyClass {
public:
    MyClass() {
        std::cout << "Constructor called for non-static object\n";
    }
    ~MyClass() {
        std::cout << "Destructor called for non-static object\n";
    }
    static MyClass obj1; // Static object 1
    static MyClass obj2; // Static object 2
};

// Initialize static objects outside the class definition
MyClass MyClass::obj1; // Static object 1 initialized
MyClass MyClass::obj2; // Static object 2 initialized

int main() {
    std::cout << "Program started\n";

    MyClass::obj1; // Accessing the first static object directly using the class name
    MyClass::obj2; // Accessing the second static object directly using the class name

    std::cout << "Program is running\n";
}
Output:
Constructor called for non-static object
Constructor called for non-static object
Program started
Program is running
Destructor called for non-static object
Destructor called for non-static object

✅Explanation:
The constructor for the static/global objects is called first, before the main() function executes
Because global/static object initialization is guaranteed to happen before main() begins execution.

