std::shared_ptr?
std::shared_ptr is a smart pointer in C++ that allows multiple pointers to share ownership of a dynamically allocated object. 
When the last shared_ptr that owns an object is destroyed or reset, the object is automatically deleted.

2. Key Features of std::shared_ptr
✅ Shared Ownership → Multiple shared_ptr instances can own the same object.
✅ Reference Counting → Uses a reference counter to track the number of owners.
✅ Automatic Cleanup → The object is deleted when the last shared_ptr goes out of scope.
✅ Safe Memory Management → Prevents memory leaks and dangling pointers.

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
        car1->drive();
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
    //{
        std::shared_ptr<Car> car1 = std::make_shared<Car>(eng); // Shares Engine ownership
        car1->drive();
        std::cout << "Reference Count of Car: " << car1.use_count() << std::endl; // Output: 1
        std::cout << "Reference Count of Engine: " << eng.use_count() << std::endl;// output:2
    //} // Car is destroyed, but Engine still exists
  //  car1.reset(); // Engine Destroyed
  car1->engine->start();
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
void useCar(std::shared_ptr<Car> car) {
    std::cout << "Inside function, Reference Count: " << car.use_count() << std::endl;
    car->drive();
}
int main() {
    std::shared_ptr<Car> myCar = std::make_shared<Car>();
    std::cout << "Before function call, Reference Count: " << myCar.use_count() << std::endl;
    
    useCar(myCar);
    
    std::cout << "After function call, Reference Count: " << myCar.use_count() << std::endl;
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
    std::cout << "Inside function, Reference Count: " << car.use_count() << std::endl;
    car->drive();
}
int main() {
    std::shared_ptr<Car> myCar = std::make_shared<Car>();
    
    std::cout << "Before function call, Reference Count: " << myCar.use_count() << std::endl;
    useCar(myCar); // Reference count remains unchanged
    std::cout << "After function call, Reference Count: " << myCar.use_count() << std::endl;
    
    return 0;
}Output:
Before function call, Reference Count: 1
Inside function, Reference Count: 1
Car is being driven.
After function call, Reference Count: 1

✅ Use this when the function only reads data and should not extend object lifetime.
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

5️⃣ Handling Cyclic References with weak_ptr ->:
When two objects have shared_ptr references to each other, they create a circular reference that prevents proper deletion.
In the below code:
1.A owns B via std::shared_ptr<B>, and B owns A via std::shared_ptr<A>.
2.This creates a circular reference where the reference count never reaches zero, causing a memory leak.

Problem: Circular Reference
// #include <iostream>
// #include <memory>
// class B; // Forward declaration
// class A {
// public:
//     std::shared_ptr<B> bptr; // Shared pointer to B
//     //std::cout << "Reference Count b: " << bptr.use_count() << std::endl;
//     A() { 
//         std::cout << "A Created\n"; 
//     }
//     ~A() { 
//         std::cout << "A Destroyed\n"; 
//     }
// };
// class B {
// public:
//     std::shared_ptr<A> aptr; // Shared pointer to A
//     //std::cout << "Reference Count aptr: " << a.use_count() << std::endl;
//     B() { std::cout << "B Created\n"; }
//     ~B() { std::cout << "B Destroyed\n"; }
// };
// int main() {
//     std::shared_ptr<A> a = std::make_shared<A>();
//     std::cout << "Reference Count a: " << a.use_count() << std::endl;
//     std::shared_ptr<B> b = std::make_shared<B>();
//     std::cout << "Reference Count b: " << b.use_count() << std::endl;

//     a->bptr = b; // A owns B
//     b->aptr = a; // B owns A

//     return 0; // Memory leak! A & B never get destroyed
// }
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


