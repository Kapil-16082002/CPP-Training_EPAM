
To do ->
    Try to implement using Linked list also??
    Other Approach??

    #include <iostream>
    #include <cstdlib>  
    using namespace std;
    
    struct MemoryRecord {  
        void* address;
        size_t size;
        int line;  
    };
    
     const int MAX_ALLOC = 100;  
     MemoryRecord memoryList[MAX_ALLOC];  
     int allocCount = 0;  
    
    // Function to add allocation record
    void addRecord(void* p, size_t size, int line) {
        if (allocCount < MAX_ALLOC) {
            memoryList[allocCount++] = {p, size, line};
        }
    }
    
    // Function to remove allocation record
    void removeRecord(void* p) {
        for (int i = 0; i < allocCount; ++i) {
            if (memoryList[i].address == p) { cout<<"Line No." <<memoryList[i].line;
                // Shift elements left to maintain order
                for (int j = i; j < allocCount - 1; ++j) {
                    memoryList[j] = memoryList[j + 1];
                }
                --allocCount;
                break;
            }
        }
    }
    
    // Overloaded new operator with file & line tracking
    void* operator new(size_t size, const char* file, int line) {
        void* p = malloc(size);
        if (!p) throw bad_alloc();
        addRecord(p, size, line);
        cout << "[Allocated] " << size << " bytes at " << p << " (Line " << line << ")" << endl;
        return p;
    }
    
    // Overloaded delete operator
    void operator delete(void* p) noexcept {
        if (p) {
            removeRecord(p);
            cout << "[Freed] Memory at " << p << endl;
            free(p);
        }
    }
    
    // Overloaded new[] operator (for array allocations)
    void* operator new[](size_t size, const char* file, int line) {
        void* p = malloc(size);
        if (!p) throw bad_alloc();
        addRecord(p, size, line);
        cout << "[Allocated Array] " << size << " bytes at " << p << " (Line " << line << ")" << endl;
        return p;
    }
    
    // Overloaded delete[] operator (for array deletions)
    void operator delete[](void* p) noexcept {
        if (p) {
            removeRecord(p);
            cout << "[Freed Array] Memory at " << p << endl;
            free(p);
        }
    }
    
    // Function to check for memory leaks
    void checkLeaks() {
        if (allocCount > 0) {
            cout<< "Total: "<<allocCount<<  "   MEMORY LEAK DETECTED! " << endl;
            for (int i = 0; i < allocCount; ++i) {
                cout << "Leaked " << memoryList[i].size << " bytes at " 
                     << memoryList[i].address << " (Line " << memoryList[i].line << ")" << endl;
            }
        } else {
            cout << "\n✅ No Memory Leaks Detected!" << endl;
        }
    }
    
    // Macro to replace new with line tracking
    #define new new(__FILE__, __LINE__)
    
    int main() {
        int* x = new int;     // Leak
        int* y = new int[5];  // Leak
        int* z = new int;     // Leak
    
        //delete x;  
        // delete[] y;
        // delete z;
    
        checkLeaks(); // Check for memory leaks
    
        return 0;
    }
    