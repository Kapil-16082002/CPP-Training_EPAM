
Memory management  involves the allocation, deallocation, and management of memory during a program’s execution.
What is malloc()?
malloc() (Memory Allocation) is a function in the C standard library (stdlib.h) used for dynamic memory allocation. 
It allocates a specified number of bytes in the heap and returns a pointer to the allocated memory.
malloc() allocates raw, uninitialized, contiguous memory from the heap.

Allocates a single block of memory of size n * sizeof(int).
Memory is not initialized — contains garbage values.

Syntax of malloc() in C
ptr = (cast-type*) malloc(byte-size)

For Example:
ptr = (int*) malloc(100 * sizeof(int));
  Since the size of int is 4 bytes, this statement will allocate 400 bytes of memory. 
  And, the pointer ptr holds the address of the first byte in the allocated memory.
  If allocation fails, it returns NULL.
/* 
✅(cast-type*) in ptr = (cast-type*) malloc(byte-size); is a type cast that converts the void* returned by malloc into a pointer of the appropriate data type.
malloc is a function in C and C++ that allocates a block of memory on the heap dynamically. It returns a void pointer (void*).
A void* is a generic pointer type, meaning it can point to memory of any data type, but actually it doesn't know the type of the memory it is pointing to.
To use the memory allocated by malloc properly, you need to convert the void* into a pointer of the desired type. This is achieved using explicit type casting, represented by (cast-type*).

✅Why Is (cast-type*) Necessary?
1. In C:
It is optional because implicit casting occurs automatically in C when assigning a void* to another pointer type.
Example:
#include <stdlib.h>
int main() {
    int* ptr = malloc(10 * sizeof(int)); // No explicit cast needed in C
    return 0;
}
This works because the C compiler will implicitly convert the void* returned by malloc() to the type of int*, 
without requiring the programmer to specify an explicit cast.

2. In C++:
Casting the return value of malloc() is mandatory because C++ does not allow implicit conversion from void* to another pointer type.
Also C++ is quite stricter about type safety compared to C.
C++ will not allow direct assignment of a void* to a pointer of any other type.
Example:
int* ptr = (int*)malloc(sizeof(int));  // Explicit cast required in C++
Without the (cast-type*) in C++, the code will not compile due to type mismatch between void* and int*.

In C++, you should generally avoid malloc() and instead use C++-specific memory management techniques such as:
new and delete: These provide type safety and automatically determine the type.
std::vector, std::unique_ptr, std::shared_ptr: These Standard Library features handle memory allocation and lifetime management automatically, minimizing the risk of memory leaks.

*/
✅Common Problems with Heap Memory: malloc , calloc, new etc...
1.Memory Leaks:
If you forget to free() memory after use, the allocated memory remains inaccessible, wasting resources.
int* ptr = (int*) malloc(10 * sizeof(int));
ptr = NULL; // Memory leak: Lost reference to the allocated memory

2.Double-Free Errors:
Freeing the same block of memory more than once can lead to undefined behavior.
free(ptr);
free(ptr); // Undefined behavior

3.Dangling Pointers:
Accessing a pointer after freeing its memory leads to dangling pointers and undefined behavior.
free(ptr);
printf("%d\n", *ptr); // Dangling pointer: Accessing freed memory



✅Best Practices for Using malloc()
Always Check for NULL: Ensure memory allocation succeeds before using the memory.
Free Allocated Memory: Always free() memory when it is no longer needed to avoid memory leaks.
Avoid Dangling Pointers: Do not use pointers after freeing them. Set them to NULL after free().


#include <stdio.h>
#include <stdlib.h>
int main(){
    int* ptr;  // This pointer will hold the base address of the block created
    int n, i;
    printf("Enter number of elements:");// Get the number of elements for the array
    scanf("%d",&n);

    ptr = (int*)malloc(n * sizeof(int)); // Dynamically allocate memory using malloc()
    if (ptr == NULL) {      // Check if the memory has been successfully allocated by malloc or not
        printf("Memory not allocated.\n");
        exit(0);
    }
    else {
        for (i = 0; i < n; ++i) {
            ptr[i] = i + 1;       // Get the elements of the array
        }
        printf("The elements of the array are: ");
        for (i = 0; i < n; ++i) {
            printf("%d, ", ptr[i]);
        }
    }
    free(ptr); // Free allocated memory
    return 0;
}
✅ Key Takeaways:
malloc() allocates uninitialized memory.
Always check if malloc() returns NULL.
Use free(ptr) to prevent memory leaks.

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

1. Allocating Memory for an Integer
#include <stdio.h>
#include <stdlib.h>
int main() {
    int *ptr = (int*)malloc(sizeof(int)); // Allocating memory for 1 integer
    if (ptr == NULL) {
        printf("Memory allocation failed\n");
        return 1;
    }
    *ptr = 10; // Assigning value
    printf("Value: %d\n", *ptr);
    free(ptr);
    return 0;
}
Output:
Value: 10
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
2. Allocating Memory for a Float
#include <stdio.h>
#include <stdlib.h>
int main() {
    float *ptr = (float*)malloc(sizeof(float));
    if (ptr == NULL) {
        printf("Memory allocation failed\n");
        return 1;
    }
    *ptr = 3.14; // Assigning value
    printf("Float Value: %.2f\n", *ptr);
    free(ptr);
    return 0;
}
Output:
Float Value: 3.14
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
3. Allocating Memory for an Array of Integers
#include <stdio.h>
#include <stdlib.h>
int main() {
    int *arr = (int*)malloc(5 * sizeof(int)); // Allocating memory for 5 integers
    if (arr == NULL) {
        printf("Memory allocation failed\n");
        return 1;
    }
    for (int i = 0; i < 5; i++) {
        arr[i] = (i + 1) * 10;
    }
    printf("Array Elements:\n");
    for (int i = 0; i < 5; i++) {
        printf("%d ", arr[i]);
    }
    free(arr);
    return 0;
}
Output:
Array Elements:
10 20 30 40 50
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
4. Allocating Memory for a Character Array (String)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main() {
    char *str = (char*)malloc(20 * sizeof(char)); // Allocating memory for 20 characters
    if (str == NULL) {
        printf("Memory allocation failed\n");
        return 1;
    }
    strcpy(str, "Hello, World!"); // Copying string
    printf("String: %s\n", str);

    free(str);
    return 0;
}
Output:
String: Hello, World!
✅ Key Takeaway: malloc() is commonly used for dynamic string allocation.

Another Approach for taking input for C-string ////////////////////////////////- 
Approach 1: Using scanf("%s", str) (No Spaces allowed)
🔹 Limitation: scanf("%s", str); only reads a single word (stops at spaces).

Approach 2: Using scanf(" %[^\n]s", str) (Handles Spaces)
🔹 Solution: scanf(" %[^\n]s", str); allows spaces in input.
🔹 Explanation: "[^\n]" tells scanf() to read until a newline (\n) is encountered.

🔹Approach 3: fgets(str, size + 1, stdin);  // Reads up to 'size' characters, prevents overflow
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
5. Using malloc() for a Structure
#include <stdio.h>
#include <stdlib.h>
struct Student {
    int id;
    float marks;
};
int main() {
    struct Student *ptr = (struct Student*)malloc(sizeof(struct Student));
    if (ptr == NULL) {
        printf("Memory allocation failed\n");
        return 1;
    }
    ptr->id = 101;
    ptr->marks = 95.5;

    printf("Student ID: %d\n", ptr->id);
    printf("Marks: %.2f\n", ptr->marks);

    free(ptr);
    return 0;
}
Output:
Student ID: 101
Marks: 95.50
//////////////////////////////////////////////////////////////////////////////////////////////////////////

Handling Memory Allocation Failure - 
If there isn’t enough memory, malloc() returns NULL.
#include <stdio.h>
#include <stdlib.h>
int main() {
    int *ptr = (int*)malloc(100000000000 * sizeof(int)); // Large allocation
    if (ptr == NULL) {
        printf("Memory allocation failed\n");
        return 1;
    }
    free(ptr);
    return 0;
}
Output:
Memory allocation failed
✅ Key Takeaway: Always check for NULL after malloc().

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////



