
✅Raw pointers:
A raw pointer is a low-level pointer in C++ that directly stores the memory address of an variable, object or memory location. 
It is called "raw" because it provides no automatic management of the memory, user manually have to manage.
Example:
int* rawPtr = new int(42); 


✅Auto pointer:
std::auto_ptr is a smart pointer included in the C++98 standard for managing dynamic memory automatically.
It automatically deallocates the object, leaving no risk of memory leaks if used properly.

✅Features of std::auto_ptr
1.Automatic Resource Management:
When the auto_ptr goes out of scope, it automatically deallocates the memory of the object it owns, reducing manual delete calls.

2.Ownership Semantics:
Ownership of the object can be transferred from one auto_ptr to another by assignment or copy operation.
After ownership is transferred, the original auto_ptr is set to nullptr to prevent double deletion.
3.Ease of Use:
Provides RAII (Resource Acquisition Is Initialization), which prevents memory leaks in many simple scenarios.

#include <iostream>
#include <memory> // for std::auto_ptr (only in pre-C++11!)
class MyClass {
public:
    MyClass() { std::cout << "Constructor called\n"; }
    ~MyClass() { std::cout << "Destructor called\n"; }
};
int main() {
    std::auto_ptr<MyClass> ptr1(new MyClass()); // Constructs MyClass object
    std::auto_ptr<MyClass> ptr2 = ptr1;         // Ownership transferred to ptr2 (ptr1 is now null)

    // Access the owned object using ptr2
    if (ptr1.get() == nullptr) {
        std::cout << "ptr1 is null\n"; // Pointer ownership was transferred
    }
    return 0; // Destructor for MyClass called when ptr2 goes out of scope
}
Output:
Constructor called
ptr1 is null
Destructor called

✅Issues and Limitations of std::auto_ptr  or Why std::auto_ptr Was Deprecated and Removed ??????????????
1. Ownership Transfer (No Copy Semantics):
Ownership of the object can be transferred from one auto_ptr to another.
After ownership is transferred, the original auto_ptr is set to nullptr.
❌ This breaks normal copy semantics rule.
Copying should mean both objects remain valid, not one becoming empty.

2. Not Compatible with Standard Containers(_STL_DISABLED_WARNING_C5053):
Due to the transfer-of-ownership semantics for copy and assignment, std::auto_ptr cannot be used with STL containers (std::vector, std::list, etc.), which require proper copy semantics.
std::vector<std::auto_ptr<int>> vec;
vec.push_back(std::auto_ptr<int>(new int(42))); // Leads to undefined behavior

3.. No Support for Arrays:
std::auto_ptr does not support managing arrays via pointers (new T[]).
/* 
Why std::auto_ptr Doesn't Support Arrays???
std::auto_ptr is designed to manage only single object, created using new, which will invoke delete only, When the std::auto_ptr destructor is called.

if you try to manage an dynamically allocated array with new[], the proper way to deallocate that array is by calling delete[]. 
but std::auto_ptr does not do this — it always calls delete instead of delete[]. 
As a result: 
Using std::auto_ptr with new[] leads to undefined behavior (UB).
This mismatch (calling delete for a memory block allocated with new[]) results in memory corruption or unexpected program behavior.

*/
4❌ Cannot Be Used Safely in Functions:  if Pass by VALUE
void func(std::auto_ptr<int> p) { }

std::auto_ptr<int> x(new int(10));
func(x);   // ownership transferred!

Deprecated and Removed in C++ Standards:
In C++11, std::auto_ptr was marked as deprecated.
In C++17, std::auto_ptr was completely removed from the standard library.

Alternatives to std::auto_ptr
std::unique_ptr (C++11):   std::make_unique , make_shared was introduced in C++14.
std::shared_ptr (C++11):
std::weak_ptr (C++11):

//===============================================================================================================

✅Declaration and Initialization:
1.std::shared_ptr<MyClass> ptr = std::make_shared<MyClass>();
2.std::shared_ptr<int> ptr(new int(42)); 

which approach is best??
std::shared_ptr<MyClass> ptr = std::make_shared<MyClass>() is best approach:
Because:
1. Efficiency: Internally, std::make_shared dynamically allocated only single memory for both the control block (used to manage reference counting) and the object itself. 
This reduces the overhead of separate memory allocations.

2.Exception safety:
If exception  is thrown, you would not  have a dangling pointer or memory leak  because everything is managed atomically by std::make_shared.

why not std::shared_ptr<int> ptr(new int(42)); ???

1. Efficiency:
Here, we are manually allocating dynamic memory  with new int(42) and passing it to the std::shared_ptr constructor.
This leads to two separate memory allocations—one for the control block of the std::shared_ptr and one for the int object itself. 
This is less efficient.
2.Exception Safety Risk: 
If an exception is thrown after the new allocation but before transferring ownership to the std::shared_ptr(e.g., if some other code executes between these steps), 
then the raw pointer new int(42) may leak memory. 

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
