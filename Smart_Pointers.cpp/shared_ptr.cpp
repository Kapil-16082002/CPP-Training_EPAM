✅std::shared_ptr?
std::shared_ptr is a smart pointer in C++ that allows multiple pointers to share ownership of a dynamically allocated object. 
When the last shared_ptr that have ownership of an object is destroyed or reset, the object is automatically deleted.

✅Declaration and Initialization:
1.std::shared_ptr<MyClass> ptr = std::make_shared<MyClass>();
std::unique_ptr<MyClass[]> myClassArray = std::make_unique<MyClass[]>(size);// array of objects
  
2.std::shared_ptr<int> ptr(new int(42)); 
std::shared_ptr<int[]> ptr(new int[42]);

/* 
std::shared_ptr<MyClass[]> ptr(new MyClass[3]);
ptr[0]= MyClass(1);
ptr[1]= MyClass(2);
ptr[2]= MyClass(3); 

std::shared_ptr<MyClass[]> ptr(new MyClass[3] {MyClass(1), MyClass(2), MyClass(3)});

*/

2. Key Features of std::shared_ptr
✅ Shared Ownership → Multiple shared_ptr instances can own the same object.
✅ Reference Counting → Uses a reference counter to track the number of owners.
✅ Automatic Cleanup(deallocation) → The object is deleted when the last shared_ptr goes out of scope.
✅ Safe Memory Management → Prevents memory leaks and dangling pointers.
✅ Supports Move Semantics → Ownership can be transferred using std::move().When ownership is moved, the original std::shared_ptr becomes empty (nullptr) because it no longer owns the resource.

✅Use Case: Suitable where multiple objects might need access to the same resource (e.g., in shared data structures).


✅Disadvantages of std::shared_ptr
1.Increased Overhead:
Reference counting introduces a small runtime overhead.

2.Circular References:
If not accompanied by std::weak_ptr, shared pointers can cause memory leaks in circular dependency scenarios.

3.Requires Explicit Use:
Developers must understand its semantics and usage to avoid misuse (e.g., storing raw pointers outside its scope).


/* 
1.Reference count keeps track of how many std::shared_ptr instances currently share ownership of the same resource.
2.When a std::shared_ptr is created and takes ownership of a resource, the reference count is initialized to 1.
3.When a new std::shared_ptr is created from an existing std::shared_ptr (via copy construction or assignment), the reference count is incremented to indicate that the resource is shared by another owner.
4.When a std::shared_ptr is destroyed or reset, the reference count is decremented. 
If the reference count reaches 0, meaning there are no more std::shared_ptr instances owning the resource, the resource is automatically deallocated (using its associated deleter).

The reference count is internally managed in a thread-safe manner, which means you can safely share std::shared_ptr instances across multiple threads.

//-----------------------------------------------------------------------------------------------------------------------------------------------------------------

✅Detailed Explanation of How std::shared_ptr Works

1.Control Block:    dynamically allocated control block (also called a shared memory block or control structure).

When a std::shared_ptr is created, a control block is allocated dynamically alongside the object being managed. 
This block contains:
-Reference Count (use_count): Tracks how many std::shared_ptr objects currently share ownership of the managed object.
-Weak Reference Count (weak_count): Tracks the number of std::weak_ptr objects referring to the same managed object.
-Custom Deleter (if any): If the std::shared_ptr is constructed with a custom deleter, this deleter is also stored in the control block.

The control block is initialized when the first std::shared_ptr is created for an object, and it's destroyed only when both:
The reference count (use_count) becomes 0.
The weak reference count (weak_count) becomes 0.

2.Reference Count Increment & Decrement:
Every time a std::shared_ptr is copied or assigned to another std::shared_ptr, the reference count (use_count) in the control block is incremented.
When a std::shared_ptr is destroyed (or reset), the reference count (use_count) is decremented.
When the reference count reaches 0, the managed object is destroyed.

3.Pointer to the Managed Object:
The actual pointer to the managed object is stored separately in the control block. 
This prevents ownership issues when multiple std::shared_ptr instances share the same managed object.



//-----------------------------------------------------------------------------------------------------------------

✅get():
Returns the raw pointer to the managed object without affecting the reference count.
std::shared_ptr<int> ptr = std::make_shared<int>(5);
int* raw = ptr.get();
Here, raw is just a raw pointer to the same object that ptr manages. However, raw does not own the resource, so it does not contribute to the reference count.

Ownership and Destruction:
The std::shared_ptr (ptr) still owns the resource (the integer with value 5, in this case).
The destructor for the resource will not be called until the std::shared_ptr goes out of scope or is reset, and the reference count drops to zero.
If you dereference or use the raw pointer after its owning shared_ptr is destroyed, you'll encounter undefined behavior because raw does not know anything about the lifetime of the managed object.
int main() {
    int* raw = nullptr;
    {
        // Create a shared_ptr that manages an integer
        std::shared_ptr<int> ptr = std::make_shared<int>(5);
        raw = ptr.get(); // Get the raw pointer from the shared_ptr
        std::cout << "Managed resource value: " << *raw << "\n"; // Output: 5
    } // 'ptr' goes out of scope here, resource is destroyed, and raw becomes a dangling pointer.
    // Now 'raw' is a dangling pointer
    // std::cout << *raw << "\n"; // Undefined behavior if uncommented
}
✅unique():
Returns true if the std::shared_ptr is the sole owner of the object (use_count == 1).
std::shared_ptr<int> ptr1 = std::make_shared<int>(10);
std::cout << std::boolalpha << ptr1.unique(); // Output: true

*/

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
    std::cout << "Reference Count: " << car1.use_count() << std::endl; // Output: 0
    std::cout << "Reference Count: " << car2.use_count() << std::endl; // Output: 1
    //❌ car1.reset(); does not delete the Car object immediately because car2 is still managing it.
  // ✅ The Car object is deleted only after car2.reset();, when the reference count becomes 0.
    car2.reset(); // Releases car2's ownership of the object
    std::cout << "Reference Count: " << car1.use_count() << std::endl; // Output: 0
    std::cout << "Reference Count: " << car2.use_count() << std::endl; // Output: 0

    // car1->drive(); // This will now crash or cause an error
    // car2->drive(); // This will now crash or cause an error

    std::cout << "Car object has been deleted" << std::endl;

    return 0;
}
Output:
Car Created
Driving the car!
Driving the car!
Car Destroyed
Car object has been deleted

Explanation://------------------------------------------------------------------------------------
What does .reset() do?
The function reset() is a member function of std::shared_ptr that:
1.Decreases the reference count of the shared object.
2.If the reference count reaches zero,Deletes the object.
3.Makes the shared_ptr null (empty) after releasing the ownership.

car1.reset();
Decrements the reference count of the Car object.
If car2 is still pointing to the object, the reference count remains 1.
If car1 was the last owner, the object is deleted.

car2.reset();
Decrements the reference count again.
If this was the last shared_ptr holding the object, the Car object gets destroyed.
The destructor (~Car()) of Car is called.

3. What happens in memory?
Before reset():
car1 ---> [Car Object] <--- car2
Reference Count = 2

After car1.reset();
car1 ---> NULL
car2 ---> [Car Object]
Reference Count = 1

After car2.reset();
car1 ---> NULL
car2 ---> NULL
Reference Count = 0
[Car Object] is destroyed (calls ~Car())

//----------------------------------------------------------------------------------------------------------------

2️⃣ Using shared_ptr as a Class Member
When a class owns an object using std::shared_ptr, the object remains alive as long as any shared pointer holds ownership.

#include <iostream>
#include <memory>

class Engine {
public:
    Engine() { std::cout << "Engine Created\n"; }
    ~Engine() { std::cout << "Engine Destroyed\n"; }
    void start() { std::cout << "Engine Started\n"; }
};
class Car {
 private:
    //public: 
    std::shared_ptr<Engine> engine; // Shared ownership

public:
    Car(std::shared_ptr<Engine> eng) : engine(eng) {
        std::cout << "Car Created\n";
    }
    ~Car() { std::cout << "Car Destroyed\n"; }
    void drive() {
        std::cout << "Car is driving...\n";
        engine->start();
    }
};
int main() {
    std::shared_ptr<Engine> eng = std::make_shared<Engine>(); // Creates Engine
    std::cout << "Reference Count of Engine: " << eng.use_count() << std::endl;// output:1
    {
        std::shared_ptr<Car> car1 = std::make_shared<Car>(eng); // Shares Engine ownership
        car1->drive();           // Car is driving...
        std::cout << "Reference Count of Car: " << car1.use_count() << std::endl; // Output: 1
        std::cout << "Reference Count of Engine: " << eng.use_count() << std::endl;// output:2
    } // Car is destroyed, but Engine still exists
    std::cout << "Reference Count of Engine: " << eng.use_count() << std::endl; // Output: 1
    eng.reset(); // Engine Destroyed
    std::cout << "Reference Count of Engine: " << eng.use_count() << std::endl; // Output: 0
    return 0;
}Output:
Engine Created
Reference Count of Engine: 1
Car Created
Car is driving...
Engine Started
Reference Count of Car: 1
Reference Count of Engine: 2
Car Destroyed
Reference Count of Engine: 1
Engine Destroyed
Reference Count of Engine: 0
//------------------------------------------------------------------------------------------------------------------

Another Variety->

#include <iostream>
#include <memory>

class Engine {
public:
    Engine() { std::cout << "Engine Created\n"; }
    ~Engine() { std::cout << "Engine Destroyed\n"; }
    void start() { std::cout << "Engine Started\n"; }
};

class Car {
//  private:
    public: 
     std::shared_ptr<Engine> engine; // Shared ownership

public:
    Car(std::shared_ptr<Engine> eng) : engine(eng) {
        std::cout << "Car Created\n";
    }
    ~Car() { std::cout << "Car Destroyed\n"; }

    void drive() {
        std::cout << "Car is driving...\n";
        engine->start();
    }
};
int main() {
    std::shared_ptr<Engine> eng = std::make_shared<Engine>(); // Creates Engine
    std::cout << "Reference Count of Engine: " << eng.use_count() << std::endl;// output:1
    
    std::shared_ptr<Car> car1 = std::make_shared<Car>(eng); // Shares Engine ownership
    car1->drive();
    std::cout << "Reference Count of Car: " << car1.use_count() << std::endl; // Output: 1
    std::cout << "Reference Count of Engine: " << eng.use_count() << std::endl;// output:2
   
  car1->engine->start(); // Engine Started
  std::cout << "Reference Count of Engine from car1: " << car1->engine.use_count() << std::endl;// output:2
    std::cout << "Reference Count of Engine: " << eng.use_count() << std::endl; // Output: 2
    std::cout << "Reference Count of Car: " << car1.use_count() << std::endl; // Output: 1
    return 0;
}
Output:
Engine Created
Reference Count of Engine: 1
Car Created
Car is driving...
Engine Started
Reference Count of Car: 1
Reference Count of Engine: 2
Engine Started
Reference Count of Engine from car1: 2
Reference Count of Engine: 2
Reference Count of Car: 1
Car Destroyed
Engine Destroyed

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
3️⃣ Passing shared_ptr to Functions
Using shared_ptr as a function parameter ensures that the object is not destroyed while in use.

📌 Pass by Value (shared_ptr<T>)
This increases the reference count, keeping the object alive.
#include <iostream>
#include <memory>
class Car {
public:
    void drive() {
        std::cout << "Car is being driven." << std::endl;
    }
};
void useCar(std::shared_ptr<Car> car) { // if passes as reference(&), then  car.use_count()=1, no extra copy will be created.
    std::cout << "Inside function, Reference Count: " << car.use_count() << std::endl; // 2
    car->drive();
}
int main() {
    std::shared_ptr<Car> myCar = std::make_shared<Car>();
    std::cout << "Before function call, Reference Count: " << myCar.use_count() << std::endl;  // 1
    
    useCar(myCar);
    
    std::cout << "After function call, Reference Count: " << myCar.use_count() << std::endl; // 1 
    return 0;
}Output:
Before function call, Reference Count: 1
Inside function, Reference Count: 2
Car is being driven.
After function call, Reference Count: 1

✅ Use this if function needs to extend object lifetime.
🚨 Avoid this if unnecessary, as it adds reference overhead.

//---------------------------------------------------------------------------------------------------------------

📌 Pass by Reference (const std::shared_ptr<T>&)
This does not increase the reference count, making it more efficient.

#include <iostream>
#include <memory>
class Car {
public:
    void drive() {
        std::cout << "Car is being driven." << std::endl;
    }
};
void useCar(const std::shared_ptr<Car>& car) {
    std::cout << "Inside function, Reference Count: " << car.use_count() << std::endl; // 1
    car->drive();
}
int main() {
    std::shared_ptr<Car> myCar = std::make_shared<Car>();
    
    std::cout << "Before function call, Reference Count: " << myCar.use_count() << std::endl; //1
    useCar(myCar); // Reference count remains unchanged
    std::cout << "After function call, Reference Count: " << myCar.use_count() << std::endl;  // 1
    
    return 0;
}Output:
Before function call, Reference Count: 1
Inside function, Reference Count: 1
Car is being driven.
After function call, Reference Count: 1
✅ Use this when the function only reads data and should not extend object lifetime.

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

5️⃣ Handling Cyclic References with weak_ptr ->:
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

    a->bptr =b ; // A now owns B
    std::cout << "After A owns B, Reference Count of B: " << b.use_count() << std::endl; // Output: 2

    b->aptr = a ; // B now owns A
    std::cout << "After B owns A, Reference Count of A: " << a.use_count() << std::endl; // Output: 2
    
    a.reset();  //releases ownership of A. However, A is still referenced by b->aptr, so it is NOT actually destroyed.  
    std::cout << "Reference Count of A: " << a.use_count() << std::endl; // Output: 0  a.use_count() is now 0 because a itself no longer owns an object.But the memory allocated for A still exists due to circular reference.
    a->show();//a was reset, meaning it no longer holds a valid pointer.Trying to access a->show(); is dereferencing a null pointer, leading to a segmentation fault (crash).
    b->aptr->show();//successfully calls show() on A, because A is not destroyed yet.
    b.reset(); // releases ownership of B, but B is still alive because A holds a reference (a->bptr).This causes a circular reference, meaning neither A nor B get destroyed.   
    std::cout << "Reference Count of B: " << b.use_count() << std::endl; // Output: 0
    b->show();// b was reset, so b is now null. Trying to access b->show(); dereferences a null pointer, causing a crash.
    a->bptr->show();// ❌ ERROR: a is null! . Calling a->bptr->show(); will crash the program.
     
    
    return 0; // Memory leak! A & B never get destroyed
}

🚨 Memory Leak! Since shared_ptr objects reference each other, their reference count never reaches 0.

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
}Output:
A Created
Reference Count of A: 1
B Created
Reference Count of B: 1
After A owns B, Reference Count of B: 2
After B references A, Reference Count of A: 1
A Destroyed
Reference Count of A: 0
A is already destroyed!
Reference Count of B: 1
B Destroyed
Reference Count of B: 0

//----------------------   using weak_ptr in Class A and shared_ptr in Class B  -----------------------------------
#include <iostream>
#include <memory>

class B; // Forward declaration
class A {
public:
    std::weak_ptr<B> bptr; // Weak pointer to B to prevent circular reference
    A() { std::cout << "A Created\n"; }
    ~A() { std::cout << "A Destroyed\n"; }
    void show(){ std::cout << "Class A" << std::endl; }
};
class B {
public:
    std::shared_ptr<A> aptr; // Shared pointer to A (B owns A)
    B() { std::cout << "B Created\n"; }
    ~B() { std::cout << "B Destroyed\n"; }
    void show(){ std::cout << "Class B" << std::endl; }
};
int main() {
    std::shared_ptr<B> b = std::make_shared<B>(); // B instance
    std::shared_ptr<A> a = std::make_shared<A>(); // A instance
    
    b->aptr = a; // B owns A
    a->bptr = b; // A weakly references B

    std::cout << "Reference Count of A: " << a.use_count() << std::endl; // Output: 2
    std::cout << "Reference Count of B: " << b.use_count() << std::endl; // Output: 1

    a.reset(); //  a releases ownership of A, decreasing the reference count by 1. However, b->aptr is still a shared_ptr, so A's reference count is not zero yet.
    b->aptr->show();// output: Class A, still have refrence to class A through  b->aptr i.e means A still exist.
   /*
1. a.reset();
The shared pointer a releases ownership of A, decreasing the reference count by 1.
However, b->aptr is still a shared_ptr, so A's reference count is not zero yet.
Since A is still owned by B, it is NOT destroyed at this point.

2.When b.reset(); happens later:
B is destroyed, and it releases its ownership of A.
Now, A's reference count becomes 0, and A is finally destroyed.
   */
    std::cout << "After resetting A, Reference Count of B: " << b.use_count() << std::endl; // Output: 1

    if (auto ptr = a->bptr.lock()) { // Check if B is still available
        ptr->show();
    } else {
        std::cout << "B is already destroyed!" << std::endl;
    }

    b.reset(); // Now B is also destroyed
    return 0;
}


