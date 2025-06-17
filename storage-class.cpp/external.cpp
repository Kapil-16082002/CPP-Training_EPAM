External Storage Class (extern) in C++ 

The external storage class in C++ is specified using the extern keyword. 
It is used to declare a global variable or function that is defined in another file or outside the current scope. 
The extern keyword tells the compiler not to allocate memory for the variable, as it is already defined elsewhere.

✅ It is mainly used for multi-file programming to share global variables or functions.
✅ const variables need extern if they are to be accessed from another file.
✅ extern does not work with local variables   —     only global variables and functions.

✅ The extern declaration does not allocate new memory for variable or function .
Instead, it tells the compiler that variable or function exists somewhere else .

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

//-------------------------------------------------------------------------------------------------------------
Syntax
extern int a;  // Declaration (no memory allocation)
int a = 10;    // Definition (memory allocated)
The declaration using extern tells the compiler that variable 'a' exists somewhere.
The definition actually allocates memory.

Example 1: Using extern in a Single File
#include <iostream>
using namespace std;
// Global variable
extern int num;  // Declaration (Tells compiler 'num' is defined somewhere)
/* 
You cannot initialize variables with the extern keyword 
Because initialization implies memory allocation, which the extern keyword does not perform.
extern int x = 5; // ERROR: Cannot initialize an extern variable
*/

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

//------------------------------------------------------------------------------------------------------------

✅Key Points About extern Functions:
Default Behavior:
In both C and C++, functions that are not static have external linkage by default.
Using extern explicitly for functions is optional and generally unnecessary.

Functions have external linkage by default in both C and C++ unless explicitly declared as static, so the extern keyword is almost unnecessary.
By using extern for functions, you create a declaration without a definition, allowing the compiler and linker to resolve the definition in a different file.

File 1: file1.c (Function Definition)
#include <stdio.h>
void say_hello() {
    printf("Hello from file1.c!\n");
}
int add(int a, int b) {
    return a + b;
}

File 2: file2.c (Function Declaration and Usage)
#include <stdio.h>
// Declare the functions defined in file1.c
extern void say_hello();
extern int add(int, int);
void test_functions() {
    say_hello(); // Call the function defined in file1.c
    int result = add(5, 10); // Call the add() function
    printf("Result of add: %d\n", result);
}

File 3: main.c (Main Program)
#include <stdio.h>
// Declare the function from file2.c
extern void test_functions();

int main() {
    printf("Calling test_functions from file2.c...\n");
    test_functions(); // Calls the function to test imported functions
    return 0;
}

//--------------------------------------------------------------------------------------------------------------

✅Accessing static function from one file to another:
In C++, a static function has internal linkage, meaning it is restricted to the file where it is declared and defined. 
Specifically, when a function is declared as static, it cannot be accessed from other files. 
This behavior makes static functions ideal for creating private, file-local functions that are not exposed as part of a global API.

Problem:
If you try to access a static function declared in file1.cpp from file2.cpp, you will get a linker error 
because the function has internal linkage and is not visible outside file1.cpp.

How to Solve the Problem?

In C++, a static function has internal linkage, meaning it is restricted to the file where it is declared and defined. Specifically, when a function is declared as static, it cannot be accessed from other files. 
This behavior makes static functions ideal for creating private, file-local functions that are not exposed as part of a global API.

Key Point:
A static function in one file cannot directly be accessed from another file. 
This is by design to support encapsulation and limit scope to the file where the function is declared.

Problem:
If you try to access a static function declared in file1.cpp from file2.cpp, you will get a linker error because the function has internal linkage and is not visible outside file1.cpp.

Here’s an example of what happens:

file1.cpp:

#include <iostream>

static void myStaticFunction() {
    std::cout << "Static function in file1.cpp" << std::endl;
}
file2.cpp:

extern void myStaticFunction();  // This is invalid and will cause a linker error

int main() {
    myStaticFunction(); // Linker error: myStaticFunction has internal linkage
    return 0;
}
The attempt to call myStaticFunction() in file2.cpp will fail because myStaticFunction() has internal linkage and is not visible in file2.cpp.

How to Solve the Problem?
Since the static keyword inherently restricts the visibility of the function to the file where it is defined, there are no workarounds to directly access it from another file. 
If you genuinely need to use this function in multiple files, you must remove the static keyword so that the function has external linkage. Alternatively, you can provide an interface or abstraction to achieve what you are trying to do.

Here are a few ways to accomplish this:

1. Remove the static Keyword
2. Use Non-Static Proxy or Wrapper
file1.cpp:
#include <iostream>
static void myStaticFunction() {
    std::cout << "Static function in file1.cpp" << std::endl;
}
// Non-static wrapper function
void callMyStaticFunction() { 
    myStaticFunction();
}
file2.cpp:
#include <iostream>
extern void callMyStaticFunction(); // Declare the wrapper function
int main() {
    callMyStaticFunction(); // Indirectly calls the static function
    return 0;
}

3. Use Function Pointers (Advanced)
you can pass function pointers to the static function to other files.

file1.cpp:
#include <iostream>
static void myStaticFunction() {
    std::cout << "Static function in file1.cpp" << std::endl;
}
void (*getStaticFunctionPointer())() {
    return &myStaticFunction; // Return the address of the static function
}

file2.cpp:
#include <iostream>
extern void (*getStaticFunctionPointer())(); // Declare the function that returns the pointer
int main() {
    void (*staticFunction)() = getStaticFunctionPointer(); // Get pointer to static function
    staticFunction(); // Call the static function indirectly
    return 0;
}


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

extern const int counter;  // Read-only access, but can not modified.
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