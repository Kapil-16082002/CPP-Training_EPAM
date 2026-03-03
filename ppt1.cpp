
Smart pointers are special C++ objects that automatically manage raw pointers.
Smart pointers ensure that memory is freed properly when it is no longer needed,so helping in prevent memory leaks, dangling pointers, and double deletion.

✅Smart pointers automatically handle:
Memory Allocation: Allocating resources (e.g., heap memory) for objects.
Memory Deallocation: Automatically freeing memory when it is no longer needed.
Ownership Semantics: Managing ownership of dynamic objects without ambiguity.
Exception safety - They ensure objects are cleaned up during exceptions.


//=================================================================================================================

2️⃣ Why Were Smart Pointers Introduced? (Problems with Raw Pointers) ??
Before smart pointers, memory management was done manually using new and delete, leading to common issues:
✅Raw pointers:
A raw pointer is a low-level pointer in C++ that directly stores the memory address of an variable, object or memory location. 
It is called "raw" because it provides no automatic management of the memory, user manually have to manage.
Example:
int* rawPtr = new int(42);


✅ Problem 1: Memory Leak (Forgetting to Call delete)
Problems Caused by Memory Leaks:
1.Increased Memory Usage:
2.Reduced System Performance:
Excessive memory usage due to leaks can cause the operating system to run out of RAM, and it may use virtual memory (swapping memory to disk). 
so virtual memory will slow down your computer performance.


class Sample {
public:
    Sample() { std::cout << "Constructor Called\n"; }
    ~Sample() { std::cout << "Destructor Called\n"; }
};
int main() {
    Sample* obj = new Sample();
    // Forgot to delete obj → Memory leak!
    return 0;
}
🚨 Issue: Object is never deleted, causing a memory leak.



2️⃣ Dangling Pointer (Accessing Freed Memory)
❌ Problem: Accessing memory after deletion
class Sample {
public:
    Sample() { std::cout << "Constructor Called\n"; }
    void show(){
        cout<<"hello"<<endl;
    }
    ~Sample() { std::cout << "Destructor Called\n"; }
};
int main() {
    Sample* obj = new Sample();
    delete obj;     // memory is freed but obj still points
    obj->show(); // ❌ Accessing deleted memory undefined behavior.
    return 0;
}



3️⃣ Double Delete (Crash or Memory Corruption)
❌ Problem: Deleting the same pointer twice

class Sample {
public:
    Sample() { std::cout << "Constructor Called\n"; }
    void show(){
        cout<<"hello"<<endl;
    }
    ~Sample() { std::cout << "Destructor Called\n"; }
};
int main() {
    Sample* obj = new Sample();
    delete obj;
    delete obj;// ❌ Second delete -> ERROR
    return 0;
}


4️⃣ Exception Safety (Memory Leak on Exception)
❌ Problem: Memory leak when an exception occurs

class ExceptionSafet{

};
int main() {
    try {
        
        ExceptionSafety* obj = new ExceptionSafety();
        throw std::runtime_error("Error occurred!"); // ❌ Memory leak, delete never called
        delete obj;
    } catch (const std::exception& e) {
        std::cout << "Exception caught: " << e.what() << "\n";
    }
    return 0;
}

//==================================================================================================================

Types of Smart Pointers:
1. auto_ptr()  C++98,Deprecated C++12, removed C++17
2. unique_ptr
3.shared_ptr
4.weak_ptr


✅Auto pointer:
std::auto_ptr is a smart pointer included in the C++98 standard for managing dynamic memory automatically.
It automatically deallocates the object, leaving no risk of memory leaks if used properly.


Syntax:
std::auto_ptr<MyClass> p(new MyClass());

✅Features of std::auto_ptr
1.Automatic Resource Management:
When the auto_ptr goes out of scope, it automatically deallocates the memory of the object it owns, reducing manual delete calls.

2.Ownership Semantics:
Ownership of the object can be transferred from one auto_ptr to another by assignment or copy operation.
After ownership is transferred, the original auto_ptr is set to nullptr to prevent double deletion.

//Code for auto_ptr
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




✅Issues and Limitations of std::auto_ptr  or Why std::auto_ptr Was Deprecated and Removed ??
1. Ownership Transfer (No Copy Semantics):
Ownership of the object can be transferred from one auto_ptr to another.
After ownership is transferred, the original auto_ptr is set to nullptr.
❌ This breaks normal copy semantics rule.
Copying should mean both objects remain valid, not one becoming empty.


2. Not Compatible with Standard Containers:
Due to the transfer-of-ownership semantics for copy and assignment, std::auto_ptr cannot be used with STL containers (std::vector, std::list, etc.), which require proper copy semantics.

3.. No Support for Arrays:
std::auto_ptr does not support managing arrays via pointers (new T[]).
std::auto_ptr is designed to manage only single object, created using new, which will invoke delete only, When the std::auto_ptr destructor is called.

if you try to manage an dynamically allocated array with new[], the proper way to deallocate that array is by calling delete[]. 
but std::auto_ptr does not do this — it always calls delete instead of delete[]. 

| C++ Version   | Status auto_ptr        
| ------------- | -------------- 
| C++98 / C++03 | Allowed        
| C++11         | **Deprecated**(can not use it anymore)
| C++17         | **Removed**    

//=================================================================================================================

✅std::shared_ptr?
std::shared_ptr is a smart pointer in C++ that allows multiple pointers to share ownership of a dynamically allocated object. 
When the last shared_ptr that have ownership of an object is destroyed or reset, the object is automatically deleted.

✅Declaration and Initialization:
1. std::shared_ptr<int> ptr  = std::make_shared<int>(5);
std::shared_ptr<int[]> ptr = std::make_shared<int[]>(5); // array of size 5, all elements become 0

2. std::shared_ptr<MyClass> ptr = std::make_shared<MyClass>();
std::unique_ptr<MyClass[]> myClassArray = std::make_unique<MyClass[]>(size);// array of objects


//Syntax:2
std::shared_ptr<int> ptr(new int(42));
std::shared_ptr<int[]> ptr(new int[42]);



✅Key Features of std::shared_ptr
 Shared Ownership → Multiple shared_ptr instances can own the same object.
 Safe Memory Management → Prevents memory leaks and dangling pointers.
 Reference Counting → Uses a reference counter to track the number of owners.
 Supports Move, copy Semantics → Ownership can be transferred using std::move()


✅Most Common methods:
| Method           | Purpose                    | Notes                             |
| ---------------- | -------------------------- | --------------------------------- |
| `get()`          | Returns raw pointer        | Does not change ownership         |
| `use_count()`    | Returns reference count    | Use only for debugging            |
| `reset()`        | Releases ownership         | Deletes object if count becomes 0 |


#include <iostream>
#include <memory>
class Car {
public:
    Car() { std::cout << "Car Created\n"; }
    ~Car() { std::cout << "Car Destroyed\n"; }
    void drive() { std::cout << "Driving the car!\n"; }
};
int main() {
    std::shared_ptr<Car> car1 = std::make_shared<Car>(); // Creates a Car object
    std::shared_ptr<Car> car2 = car1; // car2 shares ownership

    std::cout << "Reference Count: " << car1.use_count() << std::endl; // Output: 2
    std::cout << "Reference Count: " << car2.use_count() << std::endl; // Output: 2

    car1->drive();
    car2->drive();

    car1.reset(); // Releases car1's ownership of the object
    //❌ car1.reset(); does not delete the Car object immediately because car2 is still managing it.
    std::cout << "Reference Count: " << car1.use_count() << std::endl; // Output: 0
    std::cout << "Reference Count: " << car2.use_count() << std::endl; // Output: 1
  // ✅ The Car object is deleted only after car2.reset();, when the reference count becomes 0.
    car2.reset(); // Releases car2's ownership of the object
    std::cout << "Reference Count: " << car1.use_count() << std::endl; // Output: 0
    std::cout << "Reference Count: " << car2.use_count() << std::endl; // Output: 0

    // car1->drive(); // This will now crash or cause an error
    // car2->drive(); // This will now crash or cause an error

    std::cout << "Car object has been deleted" << std::endl;

    return 0;
}
✅Disadvantages of std::shared_ptr
1.Increased Overhead:
Reference counting introduces a small runtime overhead.

2.Circular References:
If not accompanied by std::weak_ptr, shared pointers can cause memory leaks in circular dependency scenarios.

//=================================================================================================================

✅Handling Cyclic References  ->:
When two objects have shared_ptr references to each other, they create a circular reference that prevents proper deletion (destruction) of resources.
In the below code:
1.A owns B via std::shared_ptr<B>, and B owns A via std::shared_ptr<A>.
2.This creates a circular reference where the reference count never reaches zero, causing a memory leak.


Problem: Circular Reference
#include <iostream>
#include <memory>
class B; // Forward declaration
class A {
public:
    std::shared_ptr<B> bptr; // Shared pointer to B
    A() { std::cout << "A Created\n"; }
    ~A() { std::cout << "A Destroyed\n"; }
    void show(){std::cout<<"Class A"<<std::endl;}
};
class B {
public:
    std::shared_ptr<A> aptr; // Shared pointer to A
    B() { std::cout << "B Created\n"; }
    ~B() { std::cout << "B Destroyed\n"; }
    void show(){std::cout<<"Class B"<<std::endl;}
};
int main() {
    std::shared_ptr<A> a = std::make_shared<A>();
    std::cout << "Reference Count of A: " << a.use_count() << std::endl; // Output: 1
    std::shared_ptr<B> b = std::make_shared<B>();
    std::cout << "Reference Count of B: " << b.use_count() << std::endl; // Output: 1


    a->bptr = b ; // A now owns B
    std::cout << "After A owns B, Reference Count of B: " << b.use_count() << std::endl; // Output: 2
    b->aptr = a ; // B now owns A
    std::cout << "After B owns A, Reference Count of A: " << a.use_count() << std::endl; // Output: 2


    a.reset();  //releases ownership of A. However, A is still referenced by b->aptr, so it is NOT actually destroyed.  
    std::cout << "Reference Count of A: " << a.use_count() << std::endl; // Output: 0  a.use_count() is now 0 because a itself no longer owns an object.But the memory allocated for A still exists due to circular reference.
    b->aptr->show();//successfully calls show() on A, because A is not destroyed yet.

    // b.reset(); // releases ownership of B, but B is still alive because A holds a reference (a->bptr).This causes a circular reference, meaning neither A nor B get destroyed.   
    // std::cout << "Reference Count of B: " << b.use_count() << std::endl; // Output: 0
    
    
    return 0; // Memory leak! A & B never get destroyed
}
✅Solution:
✅std::weak_ptr ->
std::weak_ptr is a type of smart pointer that does not participate in the reference count.
std::weak_ptr is a smart pointers used to break circular references between std::shared_ptr objects.
std::weak_ptr is designed to be used in situations where you want a reference to an object but do not want to have direct ownership of the object.


//-----------------------     using weak_ptr in Class B and shared_ptr in Class A    ----------------------------------------------------------------
#include <iostream>
#include <memory>
class B; // Forward declaration
class A {
public:
    std::shared_ptr<B> bptr; // Shared pointer to B
    A() { std::cout << "A Created\n"; }
    ~A() { std::cout << "A Destroyed\n"; }
    void show(){ std::cout << "Class A" << std::endl; }
};
class B {
public:
    std::weak_ptr<A> aptr; // Weak pointer to A to prevent circular reference
    B() { std::cout << "B Created\n"; }
    ~B() { std::cout << "B Destroyed\n"; }
    void show(){ std::cout << "Class B" << std::endl; }
};
int main() {
    std::shared_ptr<A> a = std::make_shared<A>();
    std::cout << "Reference Count of A: " << a.use_count() << std::endl; // Output: 1
    std::shared_ptr<B> b = std::make_shared<B>();
    std::cout << "Reference Count of B: " << b.use_count() << std::endl; // Output: 1


    a->bptr = b; // A now owns B
    std::cout << "After A owns B, Reference Count of B: " << b.use_count() << std::endl; // Output: 2
    b->aptr = a; // B holds a weak reference to A, breaking circular reference
    std::cout << "After B references A, Reference Count of A: " << a.use_count() << std::endl; // Output: 1

    a.reset();  // Releases ownership of A, A can be destroyed if no other shared_ptr exists
    std::cout << "Reference Count of A: " << a.use_count() << std::endl; // Output: 0
    
    if (auto aptr = b->aptr.lock()) { 
        // Check if A is still available before using it
        aptr->show();
    } 
    else {
        std::cout << "A is already destroyed!" << std::endl;
    }
    std::cout << "Reference Count of B: " << b.use_count() << std::endl; // Output: 1
    b.reset(); // Now B is also properly destroyed
    std::cout << "Reference Count of B: " << b.use_count() << std::endl; // Output: 0
    
    return 0; // No memory leak, A & B get properly destroyed
}