✅C++ Macros: 
Macros are a feature of the C++ preprocessor, used to define constants, functions, or even control parts of code. 
They are processed before the actual compilation of the program, allowing certain operations to be done at the preprocessing stage itself.

The preprocessor processes the code when it sees a # directive, such as #define

✅Advantages of Macros
1.Code Reuse:
Define repetitive code snippets or constants once and reuse them.
2.Performance:
No runtime overhead since macros are replaced during preprocessing.
3.common use of macros is to protect against multiple inclusions of the same header file, achieved through "include guards."

✅Disadvantages of Macros
1.No Type Checking: Errors may occur due to unexpected substitutions.
For constants, consider using const or constexpr instead of #define, since they offer type safety.
const int PI = 3.14159;  // Safer than #define PI 3.14159

2.Debugging Difficulty: Debugging macro-expanded code can be challenging because macros are replaced before the compilation phase.
3.Operator Precedence Issues: Improper use of parentheses in macros can lead to incorrect results.


✅Types of Macros
1.Macros for Constants: Used to define fixed values.
2.Function-like Macros: Used to define inline code (like functions).
3.Parameterized Macros: Macros that accept arguments.
4.Conditional Macros: Used for conditional compilation.
5.Special Macros: Built-in macros provided by the preprocessor.


✅Macros for Constants:
#include <iostream>
#define PI 3.14159  // Macro defining a constant value

int main() {
    double radius = 5.0;
    double area = PI * radius * radius;  // PI is replaced by 3.14159
    std::cout << "Area of the circle: " << area << std::endl;
    return 0;
}
Explanation:
The preprocessor replaces PI with 3.14159 wherever it appears in the code before compilation.

//================================================================================================================

2. Parameterized Macros
Macros can take arguments, allowing them to behave like inline functions.
#include <iostream>
#define SQUARE(x) ((x) * (x))  // Macro with a parameter

int main() {
    int number = 4;
    std::cout << "Square of " << number << ": " << SQUARE(number) << std::endl;
    std::cout << "Square of 3 + 1: " << SQUARE(3 + 1) << std::endl;  // Be cautious with macros
    return 0;
}
Output:
Square of 4: 16
Square of 3 + 1: 16
Explanation:
SQUARE(x) expands to ((x) * (x)).
Be careful with expressions like SQUARE(3 + 1) because macros directly replace their arguments. Here, ((3 + 1) * (3 + 1)) is 16, 
but without parentheses, it would evaluate as 3 + 1 * 3 + 1, yielding a different result.
Best Practice: Always enclose macro arguments in parentheses to avoid unintended operator precedence issues.

//==================================================================================================================

3. Multiline Macros
Multiline macros are defined using the backslash (\) character, which allows the macro definition to span multiple lines.

#include <iostream>
#define PRINT_RESULT(a, b) \
    std::cout << "Sum: " << ((a) + (b)) << std::endl; \
    std::cout << "Product: " << ((a) * (b)) << std::endl;

int main() {
    PRINT_RESULT(5, 3);  // This is replaced by the two lines of code
    return 0;
}
Output:
Sum: 8
Product: 15

Explanation:
The macro replaces PRINT_RESULT(5, 3) with the code:
std::cout << "Sum: " << ((5) + (3)) << std::endl;
std::cout << "Product: " << ((5) * (3)) << std::endl;

//==================================================================================================================

4. Conditional Compilation with Macros
Macros can conditionally include or exclude parts of code using #if, #ifdef, #ifndef, #else, and #endif.

#include <iostream>
// Define a macro for platform-specific code
#define WINDOWS

int main() {
#ifdef WINDOWS
    std::cout << "Running on Windows!" << std::endl;
#else
    std::cout << "Running on another platform!" << std::endl;
#endif
    return 0;
}
Output (with WINDOWS defined):
Running on Windows!
Output (without WINDOWS defined):
Running on another platform!

Explanation:
#ifdef WINDOWS checks if the macro WINDOWS has been defined.
If it is defined, the relevant block of code is included; otherwise, the #else branch is included.

//==================================================================================================================

5. Undefining a Macro
You can use #undef to cancel a macro definition, especially if it conflicts with some other code.

#include <iostream>
#define VALUE 100  // Define a macro
int main() {
    std::cout << "Value: " << VALUE << std::endl;
    #undef VALUE  // Undefine the macro
    // This would cause an error if used below:
    // std::cout << VALUE;
    return 0;
}
//=================================================================================================================

6. File Inclusion Guards
A common use of macros is to protect against multiple inclusions of the same header file, achieved through "include guards."

Code Example (math_functions.h):
#ifndef MATH_FUNCTIONS_H  // If not defined
#define MATH_FUNCTIONS_H  // Define the macro

#define SQUARE(x) ((x) * (x))
#define CUBE(x) ((x) * (x) * (x))

#endif  // End of include guard
Explanation:
The inclusion of a header file is protected by checking if MATH_FUNCTIONS_H is already defined.
If it is not defined, the content of the file is processed, and MATH_FUNCTIONS_H is defined.
If the file is included again, the preprocessor skips its content, preventing duplicate definitions.
