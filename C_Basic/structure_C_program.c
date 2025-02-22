Execution Flow of a C Program
  Preprocessing: Header files are included (#include).
  Compilation: Code is converted into machine code.
  Linking: External libraries (like stdio.h) are linked.
  Execution: main() is executed line by line.

Basic Structure of a C Program
#include <stdio.h>   // Preprocessor Directive
int globalVar = 10;  // Global Variable Declaration 
void displayMessage();  // Function Prototype

int main() {   // Main Function (Entry Point)
    int localVar = 20; // Local Variable Declaration
    displayMessage(); // Function Call
    printf("Global Variable: %d\n", globalVar);
    printf("Local Variable: %d\n", localVar);
    return 0;  // Exit Status
}
// Function Definition
void displayMessage() {
    printf("Hello from displayMessage() function!\n");
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////

(1) Preprocessor Directives (#include, #define)

 Preprocessor directives  begin with # (hash symbol) and are executed before the compilation of the program. 
 They instruct the compiler to include libraries, define macros, and set conditions.
 Preprocessor directives do not end with a semicolon (;) because they are processed before the compiler translates the program.
 
 Types of Preprocessor Directives
Directive	            Purpose
#include	           Includes header files
#define	               Defines macros (constants or functions)
#undef	               Undefines a macro
#ifdef / #ifndef	   Checks if a macro is defined or not
#if / #elif / #else / #endif	 Conditional compilation
#pragma	             Special compiler instructions
#error	              Generates custom error messages

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
 #include	       Includes header files(standard or user-defined) 
Types of #include
1. Standard Header Files (angle brackets < >)
 Includes system-provided files.
 #include <stdio.h>  // Includes standard I/O functions like printf(), scanf()
 #include <math.h>   // Includes mathematical functions like sqrt(), pow()

2.User-Defined Header Files (double quotes " ")
Includes files created by the user.
#include "myfile.h"  // Includes "myfile.h" from the same directory

myfile.h might contain:
void greet() {
    printf("Hello, World!\n");
}
               Key Difference:

                <stdio.h> searches in system directories.
                "myfile.h" searches in the local directory first, then system directories.

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
 #define	       Defines macros (constants or functions)
 
 2. #define   Macro Definition
The #define directive creates macros, which are named constants or inline functions.

(a) Defining Constants
#define PI 3.14159
int main() {
    printf("Value of PI: %f\n", PI);
    return 0;
}
🔹 PI is replaced with 3.14159 before compilation.

(b) Defining Inline Functions (Macro Functions)
#define SQUARE(x) ((x) * (x))  // Inline macro function
int main() {
    printf("Square of 5: %d\n", SQUARE(5));
    return 0;
}
🔹 SQUARE(5) expands to (5 * 5) before compilation.

⚠ Avoid using macros with side effects:
#define SQUARE(x) x * x  // ⚠ Incorrect
int result = SQUARE(4+1);  // Expands to 4+1 * 4+1 = 4+4+1 = 9 (wrong!)

✅ Use parentheses for safety:
#define SQUARE(x) ((x) * (x))  // ✅ Correct
 //////////////////////////////////////////////////////////////////////////////////////////////////////////////
 3. #undef – Undefining a Macro
Used to remove a previously defined macro.
#define MAX 100
#undef MAX  // Now MAX is undefined
🔹 After #undef, MAX cannot be used in the program.
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
4. Conditional Compilation
Conditional compilation allows compiling parts of the program based on conditions.

(a) #ifdef / #ifndef – Check if Macro is Defined
#define DEBUG
#ifdef DEBUG
    #define LOG(x) printf("Debug: %s\n", x)
#else
    #define LOG(x)  // No operation
#endif
int main() {
    LOG("This is a debug message.");
    return 0;
}
If DEBUG is defined, LOG(x) prints debug messages.
If DEBUG is not defined, LOG(x) does nothing.

(b) #if / #elif / #else / #endif – Conditional Compilation
#define VERSION 2
#if VERSION == 1
    #define MESSAGE "Version 1"
#elif VERSION == 2
    #define MESSAGE "Version 2"
#else
    #define MESSAGE "Unknown Version"
#endif
int main() {
    printf("%s\n", MESSAGE);
    return 0;
}
🔹 Only the block for VERSION == 2 gets compiled.
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
5. #pragma – Compiler-Specific Directives
#pragma gives special instructions to the compiler. It is compiler-dependent.

(a) #pragma once – Prevent Multiple Inclusion of files
#pragma once  // Ensures file is included only once
#include <stdio.h>
🔹 Used in header files to prevent duplicate inclusion.

(b) #pragma warn – Suppress Warnings (GCC/Clang)
#pragma GCC diagnostic ignored "-Wunused-variable"
int main() {
    int unusedVar;  // No warning issued
    return 0;
}
🔹 This suppresses "unused variable" warnings.


 

