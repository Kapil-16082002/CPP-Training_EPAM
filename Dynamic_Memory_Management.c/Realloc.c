
What is realloc()?
realloc() (reallocate) is used to resize previously allocated memory dynamically.
It allows us to expand or shrink memory without losing the existing data.

Syntax of realloc() in C
    ptr = realloc(ptr, newSize);
    where ptr is reallocated with new size 'newSize'.

    ptr → Pointer to previously allocated memory (malloc(), calloc(), or realloc()).
    new_size → The new memory size in bytes.
    Returns → A pointer to the new memory block. If it fails, it returns NULL.

How realloc() Works?
    If ptr is NULL, realloc() behaves like malloc().
    If new_size is 0, realloc() behaves like free().
    If a new memory block is allocated, the old data is copied.

/* 
1.If the current block can accommodate the new size:
The memory block is resized in place, and the same pointer is returned.

2.If the current block cannot accommodate the new size:
realloc allocates a new memory block large enough to satisfy the request.
It copies the contents from the old block to the new block (up to the minimum of the old and new sizes).
The old block is freed, and the new block's pointer is returned.

3.If realloc fails (e.g., insufficient memory to satisfy the request):
It returns NULL.
The original memory block remains unchanged and must eventually be freed manually (to prevent memory leaks).
*/    

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Basic Example: Expanding Memory with realloc()
    #include <stdio.h>
    #include <stdlib.h>
    int main() {
        int *arr;
        int n = 3;

        arr = (int*)malloc(n * sizeof(int)); // Step 1: Allocate memory for 3 integers
        if (arr == NULL) {
            printf("Memory allocation failed\n");
            return 1;
        }
        arr[0] = 10; // Step 2: Assign values
        arr[1] = 20;
        arr[2] = 30;

        n = 5;
        arr = (int*)realloc(arr, n * sizeof(int)); // Step 3: Expand array to 5 integers
        if (arr == NULL) {
            printf("Memory reallocation failed\n");
            return 1;
        }
    
        arr[3] = 40; // Step 4: Assign new values
        arr[4] = 50;
    
        printf("Array after realloc:\n");
        for (int i = 0; i < n; i++) {
            printf("%d ", arr[i]);
        }
        free(arr);
        return 0;
    }
    📌 Output
    Array after realloc:
    10 20 30 40 50
    ✅ Key Takeaway: realloc() preserves existing values while expanding memory.
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

Shrinking Memory Using realloc()
#include <stdio.h>
#include <stdlib.h>
int main() {
    int *arr;
    int n = 5;
    arr = (int*)malloc(n * sizeof(int));
    if (arr == NULL) {
        printf("Memory allocation failed\n");
        return 1;
    }
    for (int i = 0; i < n; i++) {
        arr[i] = (i + 1) * 10;
    }
    n = 3;
    arr = (int*)realloc(arr, n * sizeof(int));  // Shrinking to 3 elements

    if (arr == NULL) {
        printf("Memory reallocation failed\n");
        return 1;
    }
    printf("Array after shrinking:\n");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    free(arr);
    return 0;
}
📌 Output
Array after shrinking:
10 20 30
✅ Key Takeaway: Shrinking removes extra elements, but the remaining data is preserved.
///////////////////////////////////////////////////////////////////////////////////////////////////////////
Handling realloc() Failure - 
If realloc() fails, it returns NULL, and the original pointer remains unchanged.
#include <stdio.h>
#include <stdlib.h>
int main() {
    int *arr;
    int n = 3;
    arr = (int*)malloc(n * sizeof(int));
    if (arr == NULL) {
        printf("Memory allocation failed\n");
        return 1;
    }
    arr[0] = 10;
    arr[1] = 20;
    arr[2] = 30;
    int *temp = realloc(arr, 1000000000 * sizeof(int));//Always use a temporary pointer (temp) to avoid losing access to existing data.

    if (temp == NULL) {
        printf("Memory reallocation failed\n");
        free(arr);  // Free old memory
        return 1;
    }
    arr = temp;  // Update pointer if realloc succeeds
    free(arr); 
    return 0;
}
📌 Output
Memory reallocation failed
/////////////////////////////////////////////////////////////////////////////////////////////////////////

    
