
Smart pointers in C++ are special objects that manage raw pointers automatically. 
They ensure that memory is freed properly when it is no longer needed, helping to prevent memory leaks, dangling pointers, and double deletion.

Without Smart Pointers (Manual Memory Management)
#include <iostream>
class MyClass {
public:
    MyClass() {
        std::cout << "Constructor: MyClass object created.\n";
    }
    ~MyClass() {
        std::cout << "Destructor: MyClass object destroyed.\n";
    }
};
int main() {
    MyClass* obj = new MyClass(); // Allocating memory manually
    delete obj;                   // Manually deallocating memory
    return 0;
}
Issues with Manual Memory Management:

Memory leaks:       If delete obj; is forgotten, memory remains allocated indefinitely.
Dangling pointers:  If accessed after deletion, it leads to undefined behavior.
Exception safety:   If an exception occurs before delete, memory leaks.


Benefits of Smart Pointers
✔ No Memory Leaks – They automatically free memory when no longer needed.
✔ No Dangling Pointers – The pointer becomes nullptr after deletion.
✔ No Double Deletion – Prevents accidental multiple delete calls.

2️⃣ Why Were Smart Pointers Introduced? (Problems with Raw Pointers) ??
Before smart pointers, memory management was done manually using new and delete, leading to common issues:

✅ Problem 1: Memory Leak (Forgetting to Call delete)
class Sample {
public:
    Sample() { std::cout << "Constructor Called\n"; }
    ~Sample() { std::cout << "Destructor Called\n"; }
};
void createObject() {
    Sample* obj = new Sample();
    // Forgot to delete obj → Memory leak!
}
int main() {
    createObject(); // Memory leak occurs
    return 0;
}
🚨 Issue: Object is never deleted, causing a memory leak.
✅ Solution using std::unique_ptr
#include <iostream>
#include <memory>
class MemoryLeakFixed {
private:
    std::unique_ptr<int> data;
public:
    MemoryLeakFixed() : data(std::make_unique<int>(10)) {
        std::cout << "Memory allocated safely.\n";
    }
    ~MemoryLeakFixed() {
        std::cout << "Destructor called, memory freed automatically!\n";
    }
};
int main() {
    std::unique_ptr<MemoryLeakFixed> obj = std::make_unique<MemoryLeakFixed>();
    return 0;
}

//------------------------------------------------------------------------------------------------------------

2️⃣ Dangling Pointer (Accessing Freed Memory)
❌ Problem: Accessing memory after deletion
#include <iostream>
class DanglingPointer {
private:
    int* data;
public:
    DanglingPointer() {
        data = new int(5);
        std::cout << "Memory allocated.\n";
    }
    ~DanglingPointer() {
        delete data; // Memory freed
        std::cout << "Memory deleted.\n";
    }
    void showData() {
        std::cout << "Value: " << *data << "\n"; // ❌ Undefined behavior
    }
};
int main() {
    DanglingPointer* obj = new DanglingPointer();
    delete obj; // Memory freed
    obj->showData(); // ❌ Accessing deleted memory
    return 0;
}

✅ Solution using std::unique_ptr
#include <iostream>
#include <memory>
class DanglingPointerFixed {
private:
    std::unique_ptr<int> data;
public:
    DanglingPointerFixed() : data(std::make_unique<int>(5)) {
        std::cout << "Memory allocated safely.\n";
    }
    void showData() {
        std::cout << "Value: " << *data << "\n"; // Safe access
    }
};
int main() {
    std::unique_ptr<DanglingPointerFixed> obj = std::make_unique<DanglingPointerFixed>();
    obj->showData(); // ✅ Safe access, memory is managed automatically
    return 0;
}
//--------------------------------------------------------------------------------------------------------------

3️⃣ Double Delete (Crash or Memory Corruption)
❌ Problem: Deleting the same pointer twice
#include <iostream>
class DoubleDelete {
private:
    int* data;
public:
    DoubleDelete() {
        data = new int(5);
        std::cout << "Memory allocated.\n";
    }
    ~DoubleDelete() {
        delete data; // First delete
        std::cout << "Memory freed.\n";
    }
};
int main() {
    DoubleDelete* obj = new DoubleDelete();
    delete obj; // First delete
    delete obj; // ❌ Second delete -> ERROR
    return 0;
}

✅ Solution using std::unique_ptr
#include <iostream>
#include <memory>
class DoubleDeleteFixed {
private:
    std::unique_ptr<int> data;
public:
    DoubleDeleteFixed() : data(std::make_unique<int>(5)) {
        std::cout << "Memory allocated safely.\n";
    }
};
int main() {
    std::unique_ptr<DoubleDeleteFixed> obj = std::make_unique<DoubleDeleteFixed>();
    return 0; // ✅ No double delete, memory is freed automatically
}
//----------------------------------------------------------------------------------------------------------------
4️⃣ Exception Safety (Memory Leak on Exception)
❌ Problem: Memory leak when an exception occurs
#include <iostream>
#include <stdexcept>
class ExceptionSafety {
private:
    int* data;
public:
    ExceptionSafety() {
        data = new int(10);
        std::cout << "Memory allocated.\n";
    }
    ~ExceptionSafety() {
        delete data; // ❌ Not reached if exception is thrown
        std::cout << "Memory freed.\n";
    }
};
void riskyFunction() {
    ExceptionSafety* obj = new ExceptionSafety();
    throw std::runtime_error("Error occurred!"); // ❌ Memory leak, delete never called
    delete obj;
}
int main() {
    try {
        riskyFunction();
    } catch (const std::exception& e) {
        std::cout << "Exception caught: " << e.what() << "\n";
    }
    return 0;
}
Output:
Memory allocated.
Exception caught: Error occurred!

✅ Solution using std::unique_ptr
#include <iostream>
#include <memory>
#include <stdexcept>
class ExceptionSafetyFixed {
private:
    std::unique_ptr<int> data;
public:
    ExceptionSafetyFixed() : data(std::make_unique<int>(10)) {
        std::cout << "Memory allocated safely.\n";
    }
};
void safeFunction() {
    std::unique_ptr<ExceptionSafetyFixed> obj = std::make_unique<ExceptionSafetyFixed>();
    throw std::runtime_error("Error occurred!"); // ✅ No memory leak, smart pointer deletes memory
}
int main() {
    try {
        safeFunction();
    } catch (const std::exception& e) {
        std::cout << "Exception caught: " << e.what() << "\n";
    }
    return 0;
}

//---------------------------------------------------------------------------------------------------------------
5️⃣ Ownership Issues (Who Deletes the Pointer?)
❌ Problem: Multiple parts of code try to delete the same pointer
#include <iostream>
class OwnershipIssue {
private:
    int* data;
public:
    OwnershipIssue() {
        data = new int(100);
        std::cout << "Memory allocated.\n";
    }
    ~OwnershipIssue() {
        delete data;
        std::cout << "Memory freed.\n";
    }
};
void func(OwnershipIssue* ptr) {
    delete ptr; // ❌ What if the caller also deletes it?
}
int main() {
    OwnershipIssue* obj = new OwnershipIssue();
    func(obj);
    delete obj; // ❌ Double delete, leads to crash
    return 0;
}
✅ Solution using std::shared_ptr
#include <iostream>
#include <memory>
class OwnershipIssueFixed {
private:
    std::shared_ptr<int> data;
public:
    OwnershipIssueFixed() : data(std::make_shared<int>(100)) {
        std::cout << "Memory allocated safely.\n";
    }
};
void func(std::shared_ptr<OwnershipIssueFixed> ptr) {
    std::cout << "Function received shared pointer.\n";
}
int main() {
    std::shared_ptr<OwnershipIssueFixed> obj = std::make_shared<OwnershipIssueFixed>();
    func(obj);
    return 0; // ✅ No double delete, shared_ptr handles memory automatically
}


