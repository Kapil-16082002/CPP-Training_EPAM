✅A memory leak occurs when a program continuously allocates memory dynamically without releasing it, leading to increased memory usage over time. 
This can cause performance degradation and even crashes if the system runs out of memory.

Example: Memory Leak in C
#include <stdio.h>
#include <stdlib.h>
void memoryLeak() {
    int* ptr = (int*)malloc(sizeof(int) * 5); // Allocating memory on Heap
    if (ptr == NULL) {
        printf("Memory allocation failed\n");
        return;
    }
    ptr[0] = 10;
    ptr[1] = 20;
    // Forgot to free memory → Memory Leak
}
int main() {
    for (int i = 0; i < 1000000; i++) {
        memoryLeak(); // Memory is allocated repeatedly but never freed
    }
    return 0;
}
Fix: Free Memory Using free()
void memoryLeakFixed() {
    int* ptr = (int*)malloc(sizeof(int) * 5);
    if (ptr == NULL) return;
    ptr[0] = 10;
    ptr[1] = 20;
    free(ptr); // Freeing allocated memory
}
✅ Best Practice: Always use free(ptr); for every malloc(), calloc(), or realloc().

//----------------------------------------------------------------------------------------------------------------

Memory Leak in C++
Example: Memory Leak in C++
#include <iostream>
void memoryLeak() {
    int* ptr = new int[5]; // Dynamically allocated memory (Heap)
    ptr[0] = 10;
    ptr[1] = 20;
    // Memory not freed → Memory Leak
}
int main() {
    for (int i = 0; i < 1000; i++) {
        memoryLeak(); // Memory keeps accumulating
    }
    return 0;
}

Fix: Use delete to Free Memory
void memoryLeakFixed() {
    int* ptr = new int[5];
    ptr[0] = 10;
    ptr[1] = 20;
    delete[] ptr; // Freeing allocated memory
}
✅ Best Practice: Use delete ptr; for new and   delete[] ptr; for new[]

//---------------------------------------------------------------------------------------------------------------

✅ Undefine behavior or program crash Using Dangling Pointer in C++
A dangling pointer is a pointer that still refers to memory that has already been deallocated. 
If the memory is not properly managed, it can cause undefined behavior.
👉 In simple words:
The pointer still holds an old address, but that memory is no longer valid.

Example 1: Dangling Pointer causing  Undefine behavior or program crash
#include <iostream>
void memoryLeak() {
    int* ptr = new int(10);  // Dynamically allocated memory
    delete ptr;  // Memory is freed, but ptr is now dangling
    std::cout << *ptr; // Undefined behavior (dangling pointer)
}
int main() {
    memoryLeak();
    return 0;
}
Fix: Set Pointer to nullptr After Deleting
void memoryLeakFixed() {
    int* ptr = new int(10);
    delete ptr;
    ptr = nullptr;  // Now ptr does not point to invalid memory
}
✅ Best Practice: Always set pointers to nullptr after delete to prevent dangling pointers.
/*
The difference between delete ptr; and ptr = nullptr; lies in their purpose and effect on the pointer:

1. delete ptr;
Purpose: Frees (deallocates) the dynamically allocated memory that ptr is pointing to.
Effect: The memory that ptr pointed to is released, but ptr itself still contains the same address (now a "dangling pointer").
Issue: If ptr is accessed after deletion, it results in undefined behavior.

2. ptr = nullptr;
Purpose: Assigns nullptr to ptr, ensuring it doesn't point to an invalid (freed) memory location.
Effect: The pointer now holds a nullptr value, meaning it is safe to check before using.
*/

//----------------------------------------------------------------------------------------------------------------
Memory Leak Due to Uninitialized Pointer ->
A pointer that is declared but not initialized can cause memory access issues or undefined behavior.

Example : Pointer Declared but Not Allocated Memory
#include <iostream>
void uninitializedPointer() {
    int* ptr;  // Pointer is declared but not initialized
    *ptr = 10; // Undefined behavior (may crash)
    std::cout << *ptr << std::endl;
}
int main() {
    uninitializedPointer();
    return 0;
}
Fix: Always Initialize Pointers Before Use
void fixedPointer() {
    int* ptr = nullptr; // Initialize pointer to nullptr
    ptr = new int(10);  // Now allocate memory
    std::cout << *ptr << std::endl;
    delete ptr; // Free memory to prevent leak
}
✅ Best Practice: Always initialize pointers before dereferencing them.

Summary
Issue	                Example	                                        Fix
Dangling Pointer	    Deleting memory but still using the pointer	    Set pointer to nullptr after delete
Uninitialized Pointer	Declaring a pointer without allocating memory	Always initialize pointers before using

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Disadvantages of Memory Leaks in C++ ->
1. Increased Memory Usage
A memory leak causes memory to accumulate over time, leading to high RAM usage.
In long-running applications, this can slow down performance and cause system crashes.

Example: Memory Keeps Increasing
#include <iostream>
void memoryLeak() {
    int* ptr = new int[1000]; // Memory allocated but never freed
}
int main() {
    for (int i = 0; i < 100000; i++) {
        memoryLeak(); // Memory keeps accumulating
    }
    return 0;
}
🔴 Disadvantage: This program keeps allocating memory but never frees it, leading to high memory consumption.

//-----------------------------------------------------------------------------------------------------------------

2. Slower System Performance
Memory leaks reduce available system memory, causing other applications to slow down.
The system may swap memory to disk, making the program significantly slower.
Example: Memory Leak Slows Down System
#include <iostream>
#include <vector>
void memoryLeakSlowdown() {
    std::vector<int>* v = new std::vector<int>(1000000, 1); // Large allocation
    // Forgot to delete v → Memory Leak
}
int main() {
    for (int i = 0; i < 10000; i++) {
        memoryLeakSlowdown(); // Consumes large memory
    }
    return 0;
}
🔴 Disadvantage: The system runs out of RAM, forcing it to use disk swap, making everything slow.
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
How Slower System Performance ??
What Happens If You Keep Allocating Memory Without Freeing It?
When a program keeps allocating memory dynamically (heap memory) without freeing it, it leads to continuous RAM consumption, and eventually, the system may run out of available RAM. 
When that happens, the operating system (OS) uses virtual memory (swap space on disk) to handle the memory shortage.

Step-by-Step Explanation of Memory Exhaustion ->
✅Heap Memory Usage Grows
Every new or malloc() call allocates memory from the heap.
If the program never calls delete or free, heap memory keeps growing.

✅RAM Gets Filled
The OS keeps assigning physical RAM pages to the program.
Other applications also use RAM, and eventually, RAM is fully occupied.

✅OS Uses Virtual Memory (Swap Space on Disk)
When RAM is full, the OS swaps inactive pages of memory to disk (swap space or page file).
This makes space in RAM for the running program.

✅Performance Decreases (Disk Thrashing)
Reading/writing to disk is much slower than RAM.
If too much memory is swapped, the system starts thrashing, where it spends more time swapping memory than executing tasks.
The program slows down drastically.

✅System May Crash (Out of Memory - OOM Kill)
If the program keeps allocating memory and swap space is also exhausted, the OS will terminate processes to free memory.
In Linux, the OOM Killer (Out-of-Memory Killer) forcibly stops memory-hogging processes.
On Windows, the system may freeze or force close applications.

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

