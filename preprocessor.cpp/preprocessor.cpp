✅ What is a Preprocessor?
Preprocessor is a tool that runs before the actual compilation of C++ code.

✅Key Characteristics of the Preprocessor:
It processes lines starting with the # symbol (preprocessor directives).
Preprocessor directives do NOT produce object code; they just modify the programs code before compilation.
It simplifies tasks such as:
1.Including files (reusing code).
2.Defining constants or macros.
3.Conditional compilation (choosing which parts of code to include in the final binary based on conditions).


✅What are Preprocessor Directives?
Preprocessor Directives are instructions for the preprocessor that are processed before the actual compilation of the code begins.
1. Start with the # symbol, such as #define, #include, etc.
2. Are processed before compilation begins.
3. Mainly handle tasks like file inclusion, macro definition, and conditional compilation.

Key Points:
Preprocessor directives are NOT C++ statements; they are instructions to modify the source code.
so They do not require a semicolon (;).

✅Types of Preprocessor Directives:
1. #include – File Inclusion:

The #include directive is used to include the contents of another file into your program. 
This file can be a standard library file or a user-defined header file.

#include <file_name>   // for standard library headers
#include "file_name"   // for user-defined headers
Explanation:
<file_name>: Searches the file in the systems standard include directories (e.g., for C++ STL headers like <iostream>).
"file_name": Searches the specified file in the current working directory first, and then standard include paths.
Example: Including standard and custom headers.

File: myfile.h:
void fun() {
    std::cout << "Hello from myfile.h!" << std::endl;
}
Main program:
#include <iostream>   // Standard library header
#include "myfile.h"   // User-defined header

int main() {
    fun(); // Function declared in user-defined header
    return 0;
}
Output:
Hello from myfile.h!

//================================================================================================================

✅2. #define – Define a Macro
The #define directive defines a macro, like: a name or symbolic constant that is replaced by its value during preprocessing.

#define MACRO_NAME value_or_code
Example: Defining constants with macros.

#include <iostream>
#define PI 3.14

int main() {
    std::cout << "PI = " << PI << std::endl;
    return 0;
}
Output:
PI = 3.14
✨ Use Cases of Macros:
1.Defining constants (#define MAX 100).
2.Writing small reusable expressions without function overhead.

//==================================================================================================================

✅3. #undef – Undefine a Macro
The #undef directive is used to Undefine a previously defined macro. 
After using #undef, previously defined macro name no longer exists.

Example: Removing a macro definition.

#include <iostream>
#define PI 3.14

int main() {
    std::cout << "PI = " << PI << std::endl;
    #undef PI
    // std::cout << PI; // Uncommenting this will result in an error
    return 0;
}
Output:
PI = 3.14
Explanation:
After the #undef PI directive, attempting to use PI results in a compilation error.

//==================================================================================================================

✅4. #ifdef and #ifndef – Conditional Compilation
#ifdef: Compiles the code block only if a macro is defined.
#ifndef: Compiles the code block only if a macro is NOT defined.

#include <iostream>
#define kapil

int main() {
#ifdef kapil
    std::cout << "Kapil available" << std::endl;// will execute
#endif

#ifndef kapil
    std::cout << "Kapil not available" << std::endl;  // not execute
#endif

#ifndef not_kapil   
    std::cout << "Kapil not available" << std::endl; // will execute
#endif

}
//================================================================================================================

✅5. #if, #elif, #else, and #endif – Fine-Grained Conditional Compilation
These directives allow more fine-tuned conditional compilation based on conditions.

#include <iostream>
#define LEVEL 2
// int LEVEL =2; // in this case Conditional Compilation will not work

int main() {
#if LEVEL == 1
    std::cout << "Feature set: 1." << std::endl;
#elif LEVEL == 2
    std::cout << "Feature set: 2." << std::endl;
#elif LEVEL == 3
    std::cout << "Feature set: 3" << std::endl;
#else
    std::cout << "Feature set: UNKNOWN LEVEL." << std::endl;
#endif

    return 0;
}
Output:
Feature set: 2
Explanation:
The #if directive checks the condition LEVEL == 2.
The corresponding block of code is selected and executed.

//==================================================================================================================

✅6. #pragma – Compiler-Specific Instructions
The #pragma directive provides special instructions to the compiler. 
The behavior of #pragma varies compiler to compiler, so it is non-portable.
If a compiler encounters an unsupported #pragma, it generally ignores it without causing a compilation error.

Usecases:
Example 1: Avoid multiple inclusions of a header file.
When a header file is included multiple times in a codebase, you may encounter issues such as duplicate function or variable definitions.
// File: myfile.h
#pragma once    // Ensures a file is included only once during compilation
#include <iostream>
void fun() {
    std::cout << "Hello from pragma!" << std::endl;
}

// File: main.cpp
#include "myfile.h"
#include "myfile.h"  // Multiple inclusions, but #pragma once prevents it.

int main() {
    fun();
    return 0;
}

Example 2: Using #pragma message (Gives a custom message during compilation).
#include <iostream>
// Display message during compilation
#pragma message("Compilation in progress... Do not forget to test feature XYZ!")

void testFunction() {
    std::cout << "Testing pragma message feature." << std::endl;
}
int main() {
    testFunction();
    return 0;
}






