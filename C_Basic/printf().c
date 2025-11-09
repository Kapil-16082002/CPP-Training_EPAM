
 The printf() function in C is used to print formatted output to the standard output (console). 
 It belongs to the Standard I/O Library (stdio.h).

Syntax of printf() - 
int printf(const char *format, ...);
   format – A string containing text and format specifiers.
... (ellipsis) – Represents variable arguments.


Number of Arguments in printf()-//////////////////////
The number of arguments passed to printf() depends on:
   At least one argument is required (the format string).
   Additional arguments depend on the format specifiers used.
Example 1: printf() with One Argument
printf("Hello, World!\n"); // ✅ Only one argument
🔹 Valid because the format string contains no placeholders.

Example 2: printf() with Multiple Arguments
printf("Number: %d, Letter: %c, Float: %.2f\n", 10, 'A', 3.14);
First argument: "Number: %d, Letter: %c, Float: %.2f\n"
Second argument: 10 (for %d)
Third argument: 'A' (for %c)
Fourth argument: 3.14 (for %.2f)
🔹 Total 4 arguments passed.

How Many Arguments Can printf() Take?
    At least one (the format string).
    Theoretically, unlimited arguments, but in practice:
    System & Compiler Limits: Usually around 127-255 arguments.
    Exceeding the limit may cause stack overflow.
Example:
printf("%d %d %d %d %d\n", 1, 2, 3, 4, 5); // ✅ 6 arguments (1 format + 5 values)
Handling Variable Arguments in printf()
printf() internally processes arguments using the stdarg.h library.
Example using vprintf() (a version of printf() that takes va_list):
#include <stdarg.h>
#include <stdio.h>

void my_printf(const char *format, ...) {
    va_list args;
    va_start(args, format);
    vprintf(format, args);
    va_end(args);
}

int main() {
    my_printf("Custom Print: %d %s\n", 42, "Hello");
    return 0;
}
🔹 vprintf() handles the variable arguments dynamically.

Conclusion
printf() requires at least one argument (the format string).
The number of additional arguments depends on the format specifiers.
Theoretically unlimited, but practical limits depend on compiler and system.

/////////////////////////////////////////////////////////////////////////////////////////////////

Return Value of printf() - 
    printf() returns the number of characters printed.

Example:
int count = printf("Hello, C!");
printf("\nCharacters Printed: %d\n", count);
🔹 Output:
Hello, C!
Characters Printed: 9
/////////////////////////
int main() {
    int x=324;
    int count = printf("%d",x);
    printf("\nCharacters Printed: %d\n", count);
    return 0;
}
Output: 
324
Characters Printed:3
////////////////////////
int main() {
    float x=324;
    int count = printf("%f",x);
    printf("\nCharacters Printed: %d\n", count);
    return 0;
}
Output:
324.000000
Characters Printed:10

//////////////////////////

int count = printf("Hello:%d%d%c%s",1,1,'c',"ka");
printf("\nCharacters Printed: %d\n", count);
Output:
Hello:11cka
Characters Printed: 11
////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Format Specifiers in printf() - 
Format specifiers define how values should be printed.

Specifier	      Type	                            Example
%d / %i	          Integer	                        printf("%d", 10); → 10
%f	              Float	                            printf("%f", 3.14); → 3.140000 up to 6 decimal places
%lf          	  Double	                        printf("%lf", 3.14159); // By default, %lf (or %f) prints 6 digits after the decimal point.
/* 
Controlling float  Decimal Places — %.nf
int main(void) {
    printf("%.0f\n", num);  // No decimal places
    printf("%.2f\n", num);  // 2 decimal places
    return 0;
}
Control  double Decimal Places — %.nlf
int main(void) {
    double pi = 3.14159265358979;
    printf("%.2lf\n", pi); // 3.14
    printf("%.5lf\n", pi); //  3.14159
    printf("%.10lf\n", pi); //  3.1415926536
    return 0;
}

Field Width + Precision — %m.nlf

int main(void) {
    double val = 123.456;

    printf("%10.2lf\n", val);   // total width = 10, 2 decimals   ✅ %10.2lf → right aligned, total width = 10
    printf("%-10.2lfEnd\n", val); // left aligned                 ✅ %-10.2lf → left aligned
    return 0;
}
Output:   
        123.46
123.46    End



%f vs %lf — Important Difference
| Function   | `%f`                     | `%lf`                    | Notes                                                                          |
| ---------- | ------------------------ | ------------------------ | ------------------------------------------------------------------------------ |
| `printf()` | ✅ Same behavior for both | ✅ Same behavior for both | Because of **default argument promotion** (all `float` values become `double`) |
| `scanf()`  | ❌ Wrong for double       | ✅ Correct for double     | `scanf("%f", &f)` for `float`, `scanf("%lf", &d)` for `double`                 |

✅ Always use:
%f for float in scanf
%lf for double in scanf
Either %f or %lf in printf (both same)
*/
%c	              Character	                        printf("%c", 'A'); → A
%s	              String	                        printf("%s", "C"); → C
%hhd	          signed char	1 byte

%u	              Unsigned int	                    printf("%u", 100); → 100
/* 
What is unsigned int?
In C/C++,
int → can store both positive and negative numbers.
unsigned int → can store only positive numbers (and zero), but with double the positive range.

✅ %u prints an unsigned int in base 10 (decimal) — without any sign.
int main(void) {
    int x = -1;
    printf("%u\n", x);  //  4294967295 (on 32-bit system)
}

✅ Explanation:
-1 in binary (2’s complement, 32-bit) = 11111111 11111111 11111111 11111111
Interpreted as unsigned, that’s 2^32 - 1 = 4294967295.
💡 %u doesn’t know about signs — it just prints the bit pattern as an unsigned value.
*/
%ld         	  Long int	                        printf("%ld", 123456789L);
%lld	          long long int	8 bytes
%llu	          unsigned long long int  8 byte
%hhu	          unsigned char           1 byte
%hhd	          signed char	1 byte
%x / %X      	  Hexadecimal	                    printf("%x", 255); → ff
%o	              Octal	                            printf("%o", 255); → 377
%p	              Pointer	                        printf("%p", ptr);
%e / %E	          Scientific notation	            printf("%e", 12345.6); → 1.234560e+04
%g / %G	          Shortest of %e or %f	            printf("%g", 123.456000); → 123.456  by default will print 6 significant digits and remove trailing zeros
%%	              Percent sign	                    printf("%%"); → %

Explanation of Hexadecimal, Octal, and Other Specifiers
%x: Prints the integer in hexadecimal (base 16, lowercase).
    printf("%x", 255); → ff

%X: Prints the integer in hexadecimal (uppercase).
    printf("%X", 255); → FF

%o: Prints the integer in octal (base 8).
    printf("%o", 255); → 377
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
1. %e / %E - Used to print int and floating-point numbers in scientific (exponential) notation.
    The format is:
    %e prints lowercase exponent (e), and %E prints uppercase exponent (E).
    #include <stdio.h>
    int main() {
        double num = 12345.6;
        printf("Lowercase Scientific Notation: %e\n", num);
        printf("Uppercase Scientific Notation: %E\n", num);
        return 0;
    }
    Output:
    Lowercase Scientific Notation: 1.234560e+04
    Uppercase Scientific Notation: 1.234560E+04
    Explanation:
    12345.6 is printed as 1.234560e+04, meaning:
    1.234560×10^4 = 12345.6
    The exponent (+04) represents 4 places shift in the decimal point.
    %E works the same way, except the e is replaced with E (1.234560E+04).

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

2. %g / %G - Shortest of %e or %f
    Prints the number in the most compact form between:-
        Fixed-point notation (%f)
        Scientific notation (%e)
    Removes trailing zeros in decimal values.
    %g uses lowercase (e for exponent if needed), while %G uses uppercase (E).
    Example 1 (Regular Floating-Point Number)
    #include <stdio.h>
    int main() {
        double num = 123.45600;
        printf("Shortest representation: %g\n", num);//  123.456
        printf("Uppercase version: %G\n", num);// 123.456
        return 0;
    }
    Output:
    Shortest representation: 123.456
    Uppercase version: 123.456
    Explanation:
    Since 123.456 can be fully represented in normal decimal notation, %g chooses %f.
    No scientific notation is needed.


    Example 2 (Large Floating-Point Number): %g switches to scientific notation for a shorter representation.
    int main() {
        double num = 0.00001234;
        printf("Shortest representation: %g\n", num);// 1.234e-05
        printf("Uppercase version: %G\n", num);// 1.234E-05
        return 0;
    }
    Output:
    Shortest representation: 1.234e-05
    Uppercase version: 1.234E-05
    Explanation:
    Since 0.00001234 is very small, %g switches to scientific notation for a shorter representation.
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Precision and Width in printf()-///////////////////////////
Width with Integer Numbers - 
#include <stdio.h>
int main() {
    int num = 123;
    printf("Default: |%d|\n", num); // |123|
    printf("Width 6: |%6d|\n", num); // |   123|
    printf("Width 6: |%-6d|\n", num);// |123   |
    printf("Width 6 (Larger Number): |%6d|\n", 123456);// |123456| (No extra spaces)
    printf("Width 6 (Negative Number): |%6d|\n", -123);// |  -123|
    printf("Width 6 (Negative Number): |%6d|\n",  123);// |   123|
    return 0;
}
// A minus(-) sign tells left alignment i.e everything will be printed from left
// A plus(+) sign tells right alignment i.e everything will be printed from right

// The format specifier %6d means that the integer 123456 will be printed with a minimum width of 6 characters, 
//  right-aligned by default.
// now will add 3spaces extra 

Width with Floating-Point Numbers - ///////////////////////////
#include <stdio.h>
int main() {
    double num = 12.34;
    printf("Default: |%f|\n", num);//
    printf("Width 10: |%10f|\n", num);
    printf("Width 10: |%-10f|\n", num);
    printf("Width 10 (Larger Number): |%10f|\n", 1234567.89);
    return 0;
}
Precision with Floating-Point Numbers /////////////////////////
#include <stdio.h>
int main() {
    double num = 12.3456789;
    printf("Default: |%f|\n", num);
    printf("Precision 2: |%.2f|\n", num);
    printf("Precision 4: |%.4f|\n", num);
    printf("Precision 0: |%.0f|\n", num);
    return 0;
}
Output:
Default: |12.345679|
Precision 2: |12.35|
Precision 4: |12.3457|
Precision 0: |12|
Explanation:
%.2f → Rounds to 2 decimal places.
%.4f → Rounds to 4 decimal places.
%.0f → No decimal places (rounds to nearest integer).

////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Precision with Integers
#include <stdio.h>

int main() {
    int num = 123;
    printf("Default: |%d|\n", num);
    printf("Precision 5: |%.5d|\n", num);
    printf("Precision 8: |%.8d|\n", num);
    printf("|%06d|\n", 45); //   000045  // Zero-padded
    return 0;
}
Output:
Default: |123|
Precision 5: |00123|
Precision 8: |00000123|
Explanation:
%.5d → Ensures at least 5 digits, filling with leading zeros.
If the number is larger than precision, prints normally.

//////////////////////////////////////////////////////////////////////////////////////////////////////////////

Width & Precision Together
#include <stdio.h>
int main() {
    double num = 12.3456;
    printf("Width 10, Precision 2: |%10.2f|\n", num);
    printf("Width 10, Precision 4: |%10.4f|\n", num);
    printf("Width 10, Precision 0: |%10.0f|\n", num);
    return 0;
}
Output:
Width 10, Precision 2: |     12.35|
Width 10, Precision 4: |   12.3456|
Width 10, Precision 0: |        12|
Explanation:
%10.2f → Reserves 10 spaces, rounds to 2 decimal places.
%10.0f → Reserves 10 spaces, no decimal places.

///////////////////////////////////////////////////////////////////////////////////////////////////////////////

Example: Width & Precision with Integers
#include <stdio.h>
int main() {
    int num = 123;
    printf("Width 6, Precision 4: |%6.4d|\n", num);
    printf("Width 8, Precision 6: |%8.6d|\n", num);
    return 0;
}
Output:
Width 6, Precision 4: | 0123|
Width 8, Precision 6: | 000123|

Explanation:
%6.4d → Width = 6, Precision = 4:
Precision ensures at least 4 digits (0123).
Width = 6, so it right-aligns.
%8.6d → Precision = 6 digits (000123).
Width = 8, so it right-aligns.
4. Left-Align with - (Minus Sign)
By default, printf() right-aligns output.
Use %- to left-align.

/*   
To find -1 in binary (8-bit):

Start with +1: 00000001
Invert all bits (1’s complement): 11111110
Add 1: 11111110
       +      1 

11111111
✅ So, **-1 = 11111111**
*/



    

    