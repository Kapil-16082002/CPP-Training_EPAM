1. Integer (int) - Stores whole numbers (positive, negative, zero).
Types of Integer Data Types in C++ - 
Data Type           	Size (bytes)	                                   Range (Approx.)
short int	            2 bytes	                                          -32,768 to 32,767
int	                    4 bytes	                                          -2,147,483,648 to 2,147,483,647
long int	            4 or 8 bytes	                                 -2,147,483,648 to 2,147,483,647 (or more)
long long int	        8 bytes	                             -9,223,372,036,854,775,808 to 9,223,372,036,854,775,807
unsigned int	        4 bytes	                                                    0 to 4,294,967,295
⚠ Note: Sizes depend on the system architecture (e.g., 32-bit vs. 64-bit).

#Unsigned Integers- (unsigned keyword)
By default, integer types are signed (can store positive and negative values).
Using unsigned allows storing only positive numbers, effectively doubling the positive range.

Unsigned Type	            Size (bytes)	                         Range
unsigned short int	        2 bytes	                                  0 to 65,535
unsigned int	            4 bytes	                                  0 to 4,294,967,295
unsigned long int	        4 or 8 bytes	                          0 to larger values
unsigned long long int	8 bytes	0 to 18,446,744,073,709,551,615



//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
2. Floating Point (float, double)- Stores decimal numbers.
In C++, floating-point data types are used to represent numbers with a fractional part (decimal values). There are three main types of floating-point numbers:

Data Type	        Size (bytes)	        Precision                             Range
float	            4 bytes         	   upto 7 decimal digits	            ±3.4 × 10⁻³⁸ to ±3.4 × 10³⁸
double	            8 bytes	               upto 15 decimal digits	            ±1.7 × 10⁻³⁰⁸ to ±1.7 × 10³⁰⁸
long double         8, 12, or 16 bytes	   upto 19+ decimal digits	            ±3.4 × 10⁻⁴⁹³² to ±1.1 × 10⁴⁹³²

Prefer double for accuracy and float for memory efficiency.
Floating-Point Constants and Notation - floating-point numbers can be represented in scientific notation 
using exponents (e or E).
int main() {
    float num1 = 3.14e2;  // output: 3.14 × 10² = 314
    double num2 = 1.5E-3; // output: 1.5 × 10⁻³ = 0.0015
    cout << "Scientific Notation 1: " << num1 << endl;
    cout << "Scientific Notation 2: " << num2 << endl;
    return 0;
}
#Precision Issues in Floating-Point Arithmetic - 
Floating-point numbers cannot represent all decimal values exactly due to binary storage limitations.
Example Code: Precision Issue
int main() {
    float a = 0.1 + 0.2;
    cout << "0.1 + 0.2 = " << a << endl; // Expected: 0.3, but output might be different!
    return 0;
}
Output // (may vary):
0.1 + 0.2 = 0.30000001
🔹 Why? The binary representation of 0.1 and 0.2 is not exact, leading to rounding errors.

# setprecision(n) Method-
int main() {
    double pi = 3.1415926535;
    cout << fixed << setprecision(4) << "Pi: " << pi << endl; // 4 decimal places
    return 0;
}
Output:
Pi: 3.1416
////////////////////////////////////////////////////////////////////////////////////////////////////////////
3.  Character (char)- Stores a single character.

int main() {
    char grade = 'A';
    cout << "Grade: " << grade << endl;
    return 0;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////
4. Boolean (bool) - Stores true or false.

int main() {
    bool isStudent = true;
    cout << "Is Student: " << isStudent << endl;
    return 0;
}
Pointers - 