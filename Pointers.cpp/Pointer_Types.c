
1. Null Pointer
   Null Pointers are those pointers that do not point to any memory location.
   A null pointer  explicitly assigned wiht value NULL .
   A pointer of any type can be assigned the NULL value.
Example:
#include <stdio.h>
int main() {
    int *ptr = NULL;  // Pointer initialized to NULL
    if (ptr == NULL) {
        printf("Pointer is NULL\n");
    } 
    else {
        printf("Pointer is not NULL\n");
    }
    return 0;
}
Output:
Pointer is NULL
Use Case: Prevents dangling pointers and is useful in error handling.
/*NULL (Pre-C++11):
Type: It is typically defined as an integer constant (usually 0).
Limitation: Can lead to ambiguity because 0 could be interpreted as an integer or a null pointer constant.
It was used in C and early versions of C++ for null pointer representation.

2. nullptr (Introduced in C++11):
Type: It is a keyword that represents a null pointer constant (of type std::nullptr_t).
Advantage: Eliminates ambiguity by specifically denoting a null pointer rather than an integer.

Key Difference in Example:

void func(int x) { std::cout << "Integer function\n"; }
void func(char* x) { std::cout << "Pointer function\n"; }

func(NULL);    // Ambiguous: `NULL` is treated as `0`, could call either version.
func(nullptr); // Unambiguous: Calls the pointer version.  */
      
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

2.Void Pointer (Generic Pointer)
A void* pointer can hold the address of any data type but cannot be dereferenced directly(need to typecast)
They are also called generic pointers as they can point to any type and can be typecasted to any type.

#include <stdio.h>
int main() {
    int x = 10;
    void *ptr = &x;  // Generic pointer
    printf("Address stored in void pointer: %p\n", ptr);
    // Typecasting required for dereferencing
    printf("Value: %d\n", *(int *)ptr);
    return 0;
}
Output
Address stored in void pointer: 0x...
Value: 10
Advantages:  1. Used in dynamic memory allocation (malloc(), calloc(), etc.) and generic functions.
             2. Just because the void pointers can be typecasted into any pointer type, 
                it allows the dynamic memory functions to be used to allocate memory of any data type.

Limitations:
You can not  do pointers arithmetic with the void pointers because:
1) Void pointers cannot be dereferenced.
2) Pointer arithmetic is not allowed with void pointers in C language.

//////////////////////////////////////////////////////////////////////////////////////////////////////////

3. Wild Pointer (Uninitialized Pointer)
A wild pointer is a pointer that has been declared but not initialized and may point to an unpredictable memory location.
It contains a garbage (random) address, which means it points to an unknown or invalid memory location.
#include <stdio.h>
int main() {
    int *ptr;   // ❌ Declared but not initialized — WILD pointer  
    // printf("%d", *ptr);  // if we try to Dereferencing leads to undefined behavior
    return 0;
}
Use Case: Always initialize pointers to NULL before using them.

///////////////////////////////////////////////////////////////////////////////////////////////////////////////

4. Dangling Pointer
  A dangling pointer is a pointer that points to a memory location that has been already deallocated.

#include <stdio.h>
#include <stdlib.h>
int main() {
    int *ptr = (int *)malloc(sizeof(int));  // Allocating memory
    *ptr = 42; 
    printf("Before free: %d\n", *ptr);
    free(ptr);  // Memory freed, but ptr is still pointing to it
    // printf("%d", *ptr);  // Dereferencing now leads to undefined behavior
    ptr = NULL;  // Avoid dangling pointer issue
    return 0;
}
Output
Before free: 42
Use Case: Always set pointers to NULL after free() to avoid dangling pointers.

////////////////////////////////////////////////////////////////////////////////////////////////////////////////

5. Function Pointer
A function pointer stores the address of a function and can be used to call functions dynamically.
#include <stdio.h>
void greet() {       // Function definition
    printf("Hello, World!\n");
}
int main() {
    void (*funcPtr)() = greet;  // Function pointer
    funcPtr();  // Calling function using pointer

    return 0;
}
Output
Hello, World!
Use Case: Used in callbacks, event handling, and dynamic function calls.

//////////////////////////////////////////////////////////////////////////////////////////////////

9.Constant Pointers
There are three types:

1. Pointer to Constant (const int *ptr) → Cannot modify value.
2. Constant Pointer (int *const ptr) → Cannot change address.
3. Constant Pointer to Constant (const int *const ptr) → Cannot change value or address.
#include <stdio.h>
int main() {
    int x = 10, y = 20;
    
    const int *ptr1 = &x; // Pointer to constant (cannot modify value)
    // *ptr1 = 20;  // Error: Cannot modify value

    int *const ptr2 = &x; // Constant pointer (cannot change address)
    *ptr2 = 20;  // Allowed
    // ptr2 = &y;  // Error: Cannot change address

    const int *const ptr3 = &x; // Constant pointer to constant
    // *ptr3 = 30;  // Error
    // ptr3 = &y;   // Error

    return 0;
}
Use Case: Used for read-only variables and function parameters.







