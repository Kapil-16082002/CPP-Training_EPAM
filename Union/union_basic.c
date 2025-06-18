union in C: 
A union in C is a special data type that allows storing different types of data in the same memory location. 
Unlike structures, where each member gets separate memory, all members of a union share the same memory.
//struct and union are user-defined data types in both C and C++

A union is a user-defined data type similar to a structure, but only one of its members can hold a value at a time 
 because they share the same memory location.

📌 Syntax of Union
union UnionName {
    data_type member1;
    data_type member2;
    ...
};
🔹Example: Declaring and Using a Union
#include <stdio.h>
#include <cstring>
union Data {
    int i;
    float f;
    char str[20];
};
int main() {
    union Data d;
    
    d.i = 10;   // Stores an integer
    printf("i: %d\n", d.i);

    d.f = 20.5; // Overwrites 'i'
    printf("f: %.2f\n", d.f);

    strcpy(d.str, "Hello"); // Overwrites 'f'
    printf("str: %s\n", d.str);

    printf("i after storing str: %d\n", d.i); // Value is corrupted-> gives some 
    return 0;
}
✅ Output:
i: 10
f: 20.50
str: Hello
i after storing str: 1819308124 (corrupted data)
📌 Explanation:

Only one member is stored at a time.
Assigning a new value overwrites the previous one.
Accessing old values after overwriting leads to corruption.
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

🔹 2. Size of a Union
Since all members share the same memory, the size of a union is equal to the size of the largest member.
📌 Example: Checking Union Size
#include <stdio.h>
union Test {
    char a;
    int b;
    double c;
};
int main() {
    printf("Size of union: %lu bytes\n", sizeof(union Test));
    return 0;
}
✅ Output:
Size of union: 8 bytes
📌 Explanation:
char a → 1 byte
int b → 4 bytes
double c → 8 bytes (largest member)
Total size = 8 bytes (size of the largest member).
////////////////////////////////////////////////////////////////////////////////////////////////////////////
🔹 3. Difference Between struct and union
Feature	                   struct	                                            union
Memory Allocation	Each member gets separate memory	    All members share the same memory
Size	            Sum of sizes of all members	            Size of largest member
Usage	            Used when storing multiple values	    Used when storing one value at a time
Data Overwriting	Members retain their values	            Assigning a new value overwrites the previous
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
🔹4. Union with Pointers -> 
#include <stdio.h>
union Number {
    int *ptr;
    double d;
};
int main() {
    union Number u;
    int num = 10;
    u.ptr = &num;

    printf("Value of num using pointer: %d\n", *u.ptr);
    u.d = 5.5; // Overwrites pointer
    printf("Value of d: %.1f\n", u.d);
    printf("Value of num using pointer: %d\n", *u.ptr); // The pointer value is lost after assigning u.d.
    return 0;
}
✅ Output:
Value of num using pointer: 10
Value of d: 5.5
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

🔹 5. Union Inside a Structure
Sometimes, we use a union inside a structure to save memory.
📌 Example: Efficient Memory Use with Union
#include <stdio.h>
struct Employee {
    char name[20];
    int id;
    union {
        float salary;
        int hourlyWage;
    } pay;
};
int main() {
    struct Employee e;
    strcpy(e.name, "Kapil");
    e.id = 101;
    e.pay.salary = 50000.50;
    printf("Name: %s, ID: %d, Salary: %.2f\n", e.name, e.id, e.pay.salary);
    e.pay.hourlyWage = 500; // Overwrites salary
    printf("Hourly Wage: %d\n", e.pay.hourlyWage);
    return 0;
}
✅ Output:
Name: Kapil, ID: 101, Salary: 50000.50
Hourly Wage: 500
📌 Key Points:

Uses union inside structure to store either salary or hourly wage.
Saves memory by not storing both simultaneously.
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
🔹 6. Anonymous Union
An anonymous union doesn’t require a name and can be used without a variable name.

📌 Example: Anonymous Union
#include <stdio.h>
struct Example {
    int id;
    union {
        float salary;
        int hourlyWage;
    }; // No union name
};
int main() {
    struct Example e;
    e.id = 101;
    e.salary = 40000.75; // Direct access
    printf("ID: %d, Salary: %.2f\n", e.id, e.salary);
    e.hourlyWage = 500; // Overwrites salary
    printf("Hourly Wage: %d\n", e.hourlyWage);
    return 0;
}
✅ Output:
ID: 101, Salary: 40000.75
Hourly Wage: 500
📌 Key Points:
No need for a union variable name.
Members can be directly accessed.
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
🔹 7. Using typedef with Union
typedef simplifies the use of unions.
📌 Example: typedef with Union
#include <stdio.h>
typedef union {
    int x;
    float y;
} Number;
int main() {
    Number num;
    num.x = 42;
    printf("x: %d\n", num.x);
    num.y = 3.14;
    printf("y: %.2f\n", num.y);
    return 0;
}
✅ Output:
x: 42
y: 3.14
📌 Key Point: typedef allows using Number instead of union Number.

📌 Summary
Topic	                                         Details
Union Basics	               A user-defined data type where all members share one memory location
Memory Allocation	           Size of the union is equal to the size of the largest member
Difference from Struct	       Struct stores all members separately, union stores one at a time
Union with Pointers	           Assigning a new value overwrites the pointer
Union in a Structure	       Used for saving memory, especially in employee records
Anonymous Union	               No need to name the union, can access members directly
typedef with Union	           Makes union declaration simpler