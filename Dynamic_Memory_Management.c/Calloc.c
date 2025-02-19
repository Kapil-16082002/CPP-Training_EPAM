What is calloc()? (Contiguous Allocation)
calloc()  is a function in C used for dynamic memory allocation. It is similar to malloc(), but with two key differences:

    Allocates multiple blocks of memory instead of a single block.
    Initializes all allocated memory to zero (unlike malloc(), which leaves memory uninitialized).
    //It initializes each block with a default value ‘0’.
Syntax:
  ptr = (cast-type*)calloc(n, element-size);
  here, n is the no. of elements and element-size is the size of each element.
  
For Example: 
ptr = (float*) calloc(25, sizeof(float));
This statement allocates contiguous space in memory for 25 elements each with the size of the float.
 ///////////////////////////////////////////////////////////////////////////////////////////////////////
 1. Allocating Memory for an Integer
#include <stdio.h>
#include <stdlib.h>
int main() {
    int *ptr = (int*)calloc(1, sizeof(int));
    if (ptr == NULL) {
        printf("Memory allocation failed\n");
        return 1;
    }
    printf("Default value: %d\n", *ptr);  // Should be 0
    free(ptr);
    return 0;
}
Output:
Default value: 0
/////////////////////////////////////////////////////////////////////////////////////////////////////////
2. Allocating Memory for an Integer array - 
#include <stdio.h>
#include <stdlib.h>
int main() {
    int *arr;
    int n;
    printf("Enter the number of elements in the array: ");
    scanf("%d", &n);
    arr = (int*)calloc(n, sizeof(int));

    if (arr == NULL) {
        printf("Memory allocation failed\n");
        return 1;
    }

    printf("Enter %d numbers:\n", n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    printf("You entered:\n");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    free(arr);
    return 0;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

2. Allocating Memory for a Float
#include <stdio.h>
#include <stdlib.h>
int main() {
    float *ptr = (float*)calloc(1, sizeof(float));
    if (ptr == NULL) {
        printf("Memory allocation failed\n");
        return 1;
    }
    printf("Default float value: %.2f\n", *ptr);  // Should be 0.00
    free(ptr);
    return 0;
}
Output:
Default float value: 0.00
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

3. Allocating Memory for a String
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main() {
    char *str;
    int size = 20;
    // Allocating memory
    str = (char*)calloc(size, sizeof(char));
    if (str == NULL) {
        printf("Memory allocation failed\n");
        return 1;
    }
    strcpy(str, "Hello, calloc!"); // Copying string
    printf("String: %s\n", str);
    free(str);
    return 0;
}
Output:
String: Hello, calloc!
✅ Key Takeaway: calloc() ensures all characters are initialized to \0, making it ideal for dynamic strings.
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
5. Using calloc() for a Structure
#include <stdio.h>
#include <stdlib.h>
struct Student {
    int id;
    float marks;
};
int main() {
    struct Student *ptr;
    ptr = (struct Student*)calloc(1, sizeof(struct Student));  // Allocating memory for one Student structure
    if (ptr == NULL) {
        printf("Memory allocation failed\n");
        return 1;
    }
    printf("Default ID: %d, Marks: %.2f\n", ptr->id, ptr->marks); // Default values (should be 0)

    ptr->id = 101;
    ptr->marks = 95.5;
    printf("Updated ID: %d, Marks: %.2f\n", ptr->id, ptr->marks);
    free(ptr);
    return 0;
}
Output:
Default ID: 0, Marks: 0.00
Updated ID: 101, Marks: 95.50
✅ Key Takeaway: calloc() initializes structure members to zero.
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
Handling Memory Allocation Failure
If the system runs out of memory, calloc() returns NULL.
#include <stdio.h>
#include <stdlib.h>
int main() {
    int *ptr = (int*)calloc(100000000000, sizeof(int)); // Large allocation
    if (ptr == NULL) {
        printf("Memory allocation failed\n");
        return 1;
    }
    free(ptr);
    return 0;
}
Output:
Memory allocation failed
✅ Always check if (ptr == NULL) before using allocated memory.
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
Conclusion
Feature	                    malloc()	                             calloc()
Memory Initialization	  ❌ Uninitialized	                        ✅ Zero-initialized
Parameters	               (size)	                                  (num, size)
Usage	                   Single block	                               Multiple blocks
Speed	                   Faster	                                   Slower
🚀 Best Use Cases for calloc():

When memory must be initialized to zero.
Allocating arrays or structures dynamically.
Preventing garbage values in allocated memory.





  
