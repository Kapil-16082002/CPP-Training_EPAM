
To do ->
    Try to implement using Linked list also??
    Other Approach??

#include <iostream>
#include <cstdlib>  // For malloc/free
using namespace std;

struct MemoryRecord {      // Define a struct to hold memory allocations
    void* address;
    size_t size;
};
// Array to track allocated memory
const int MAX_ALLOC = 100;  
MemoryRecord memoryList[MAX_ALLOC];          // static MemoryRecord memoryList[MAX_ALLOC];
int allocCount = 0;                         // static int allocCount = 0;

// Function to add an allocation to the tracking array
void addRecord(void* p, size_t size) {
    if (allocCount < MAX_ALLOC) {
        memoryList[allocCount++] = {p, size};
    }
}
// Function to remove an allocation from the tracking array
void removeRecord(void* p) {
    for (int i = 0; i < allocCount; ++i) {
        if (memoryList[i].address == p) {
            // Shift elements left to fill the gap
            for (int j = i; j < allocCount - 1; ++j) {
                memoryList[j] = memoryList[j + 1];
            }
            --allocCount;
            break;
        }
    }
}

// Overloaded new operator with file and line info
void* operator new(size_t size,  int line) {
    cout << "Overloaded new at " << ":" << line << " (size: " << size << " bytes)" << endl;
    void* p = malloc(size);
    if (!p) throw bad_alloc();
    addRecord(p, size);  // Track allocation
    return p;
}

// Overloaded delete operator
void operator delete(void* p) noexcept {
    if (p) {
        removeRecord(p);  // Remove from tracking array
        cout << "Overloaded delete at " << p << endl;
        free(p);
    }
}

// Overloaded new[] operator (for arrays)
void* operator new[](size_t size, int line) {
    cout << "Overloaded new[] at "  << ":" << line << " (size: " << size << " bytes)" << endl;
    void* p = malloc(size);
    if (!p) throw bad_alloc();
    addRecord(p, size);
    return p;
}

// Overloaded delete[] operator (for arrays)
void operator delete[](void* p) noexcept {
    if (p) {
        removeRecord(p);
        cout << "Overloaded delete[] at " << p << endl;
        free(p);
    }
}
// Function to check for memory leaks
void checkLeak() {
    if (allocCount > 0) {
        cout << "Memory Leak Detected!" << endl;
        for (int i = 0; i < allocCount; ++i) {
            cout << "Leaked: Address=" << memoryList[i].address << ", Size=" << memoryList[i].size << " bytes" << endl;
        }
    } else {
        cout << "No Memory Leak Detected!" << endl;
    }
}
// Macro to pass file and line info to new
//#define new new(__FILE__, __LINE__)
int main() {
 
    int* x = new int;
    int* y = new int[5];

    delete x;
    delete[] y;

    checkLeak();
    
    return 0;
}
