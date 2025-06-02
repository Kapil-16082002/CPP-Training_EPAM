✅storage classes define the scope (visibility), lifetime, and memory location(where a variable or function is stored) of a variable or function.
There are five major storage classes:
Automatic (auto)
External (extern)
Static (static)
Register (register)
Mutable (mutable) (specific to C++)
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

1.Automatic Storage Class-
The auto storage class is the default storage class for local variables in C. 
Memory is allocated when the variable is declared and deallocated when it goes out of scope.
It is only accessible within the function or block in which it is declared.

These variables are stored in the stack memory and have automatic duration.

/*

The 'auto' keyword is only applicable to local variables (those declared within a function or block).

✅Why auto Doesn’t Work for Global Variables:
Global variables already have static storage duration by default, meaning they exist for the entire runtime of the program and are initialized to 0 (if uninitialized explicitly). 
Since global variables persist for the entire lifetime of the program, they cannot use auto (which is designed for local variables with limited lifetime). 
Thus, all "global" variables have static storage duration implicitly, and you cannot change that.

*/

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
Here, the variable num is an auto variable inside the function display(). 
It is created when display() is called and destroyed when the function ends.

#include <stdio.h>
int main() {
    // These two variables have the same behavior
    auto int x = 10;   // Using 'auto' explicitly
    int y = 20;        // Without 'auto'

    printf("x = %d, y = %d\n", x, y);
    {
        auto int z = 30; // 'z' only exists inside this block
        printf("z = %d\n", z);
    }
    // printf("z = %d\n", z); // Uncommenting this will cause an error because 'z' is out of scope
    return 0;
}

/*
In modern C++ (C++11 and later), auto is used for type inference(deduction) instead of specifying the storage class.
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

 */
