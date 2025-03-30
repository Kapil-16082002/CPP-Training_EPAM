
Dynamic Casting :
Dynamic casting is a type of casting that is used to safely convert pointers or references between polymorphic base and derived classes. 
It ensures that the conversion is valid at runtime using Run-Time Type Information (RTTI). 
If the cast is invalid, dynamic_cast returns nullptr (for pointers) or throws an exception (for references).

1. Syntax of dynamic_cast
dynamic_cast<target_type>(expression)

target_type: The desired type to cast to (must be a pointer or reference to a polymorphic type).
expression: The object to be cast.

2. When to Use dynamic_cast
Dynamic casting is mainly used in scenarios where:
You have inheritance with polymorphism (i.e., a base class with at least one virtual function).
You need to safely downcast (cast from a base class pointer to a derived class pointer).
You are unsure whether the object actually belongs to the derived type.

3. Example of dynamic_cast
a) Safe Downcasting (Base → Derived)
#include <iostream>
using namespace std;

class Base {
public:
    virtual void show() { cout << "Base class" << endl; } // Virtual function
};
class Derived : public Base {
public:
    void show() override { cout << "Derived class" << endl; }
};
int main() {
    Base* basePtr = new Derived(); //A Derived object is assigned to a Base* pointer. Upcasting (Implicit & Safe)
    basePtr->show();  // Derived class
    // Attempting a downcast using dynamic_cast
    Derived* derivedPtr = dynamic_cast<Derived*>(basePtr);
    derivedPtr->show();  // Derived class
    
    if (derivedPtr)  derivedPtr->show();    // Check if cast was successful
    else   cout << "Cast failed" << endl;
        
    delete basePtr;
    return 0;
}
Output:
Derived class
Here, since basePtr actually points to a Derived object, dynamic_cast succeeds.
What happens if Base had no virtual function?
dynamic_cast requires at least one virtual function in Base.
If show() was not virtual, dynamic_cast would fail and return nullptr, printing "Cast failed".

/* 
Understanding Base* basePtr = new Derived();  ->
1.new Derived();
This creates an object of the Derived class dynamically on the heap.
The object has all the properties of both Base and Derived.

2.Base* basePtr = ...;
A pointer of type Base* is assigned the address of the newly created Derived object.
This is called upcasting, where a derived class object is referenced using a base class pointer.
Upcasting is always safe in C++.

What basePtr Can Access?
Since basePtr is a pointer to Base, it can only access members of Base (that are not private).
However, if the Base class has virtual functions, it will call the overridden version from Derived.

Example Code:
#include <iostream>
using namespace std;

class Base {
public:
    virtual void show() { cout << "Base class" << endl; } // Virtual function
    void baseFunction() { cout << "Base function" << endl; } // Non-virtual function
};
class Derived : public Base {
public:
    void show() override { cout << "Derived class" << endl; } // Overriding function
    void derivedFunction() { cout << "Derived function" << endl; }
};

int main() {
    Base* basePtr = new Derived(); // Upcasting

    basePtr->show();          // Calls Derived's show() because it's virtual
    basePtr->baseFunction();  // Calls Base's function (non-virtual)
 // basePtr->derivedFunction();  // ❌ ERROR: Base pointer can't access Derived-specific members

    delete basePtr; // Free memory
    return 0;
}
Output:
Derived class
Base function
Key Takeaways
basePtr can only access Base class members, unless overridden virtual functions exist.
If a function is virtual, it follows dynamic dispatch and calls the derived version.
basePtr cannot directly access Derived-specific members (like derivedFunction()).
To access Derived-specific members, we need dynamic_cast or explicit downcasting.
*/
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*     Issue in this code
#include <iostream>
using namespace std;

class Base {
public:
    virtual void show() { cout << "Base class" << endl; } // Virtual function
};
class Derived : public Base {
public:
    void show() override { cout << "Derived class" << endl; }
};
int main() {
    Base* basePtr = new Base();   // basePtr is a pointer to a Base object, not a Derived object.
    basePtr->show();  // Base class
    
    // Attempting a downcast using dynamic_cast
    Derived* derivedPtr = dynamic_cast<Derived*>(basePtr);
    derivedPtr->show();// will not print Derived class
    
    if (derivedPtr)  derivedPtr->show();    // Check if cast was successful
    else   cout << "Cast failed" << endl;
        
    delete basePtr;
    return 0;
}
Explanation:
Since basePtr was never pointing to a Derived object, dynamic_cast fails, and "Cast failed" would be printed.
1.Downcasting (Derived* derivedPtr = dynamic_cast<Derived*>(basePtr);)
basePtr actually points to a Base object, not a Derived object.
Since dynamic_cast only works when the actual object is of the target derived type, the cast fails and returns nullptr.

2.Dereferencing nullptr (derivedPtr->show();)
Since derivedPtr is nullptr, calling derivedPtr->show(); results in undefined behavior (likely a crash).

Fix 2: Use Base* that Actually Points to a Derived Object
If you actually want the downcast to succeed, make sure that basePtr points to a Derived object:
Base* basePtr = new Derived(); // First Upcasting - basePtr now points to a Derived object
basePtr->show();  // Calls Derived::show() due to virtual function

Derived* derivedPtr = dynamic_cast<Derived*>(basePtr);
if (derivedPtr)
    derivedPtr->show();  // Now works correctly!
else
    cout << "Cast failed" << endl;

delete basePtr;  // Important to prevent memory leak
*/
//---------------------------------------------------------------------------------------------------------------

b) Unsuccessful Downcasting
If the object does not actually belong to the derived type, dynamic_cast returns nullptr.

Base* basePtr = new Base(); // Base class object
Derived* derivedPtr = dynamic_cast<Derived*>(basePtr);

if (derivedPtr)   derivedPtr->show();
    
else  cout << "Cast failed" << endl;
    
Output:
Cast failed
Since basePtr does not actually point to a Derived object, the cast fails.
//----------------------------------------------------------------------------------------------------------------

c) Using dynamic_cast with References
When using dynamic_cast on references, if the cast fails, it throws a std::bad_cast exception instead of returning nullptr.
#include <iostream>
#include <typeinfo>

class Base { public: virtual ~Base() {} };
class Derived : public Base {};

int main() {
    try {
        Base baseObj;
        Derived& derivedRef = dynamic_cast<Derived&>(baseObj); // Unsafe!
    }
    catch (const std::bad_cast& e) {
        std::cerr << "Exception caught: " << e.what() << std::endl;
    }
    return 0;
}
Output:
Exception caught: std::bad_cast

4. Rules & Restrictions of dynamic_cast
Works only with polymorphic classes
      The base class must have at least one virtual function.
      Otherwise, compilation will fail.

Only meaningful for class hierarchies
        dynamic_cast should be used only when dealing with polymorphic objects.
        It does not work for non-polymorphic types like int, float, etc.

Slower than static_cast
        dynamic_cast involves runtime type checking using RTTI, which has a performance cost.

Safer than static_cast
     If an invalid cast is attempted, dynamic_cast returns nullptr (for pointers) or throws an exception (for references), preventing undefined behavior.

     5. Difference Between dynamic_cast and static_cast
     Feature	dynamic_cast	static_cast
     Type Checking	Performed at runtime (RTTI)	Performed at compile-time
     Failure Handling	Returns nullptr for pointers, throws exception for references	Can lead to undefined behavior
     Speed	Slower due to RTTI	Faster (no runtime checking)
     Use Case	Used for polymorphic class hierarchies	Used for conversions within related types (e.g., base to derived when safe)
          
//-----------------------------------------------------------------------------------------------------------------

3.Upcasting using dynamic_cast in C++ ->

Upcasting refers to converting a Derived class pointer/reference to a Base class pointer/reference.
It is safe and implicit (does not require dynamic_cast explicitly).
However, you can still use dynamic_cast for type safety.

Why Use dynamic_cast for Upcasting?
Normally, upcasting is implicit and does not need dynamic_cast.
But using dynamic_cast<Base*> ensures that the object is derived from Base at runtime.
If dynamic_cast fails (which is rare for upcasting), it returns nullptr, which can be useful for error checking.

Example: Upcasting Using dynamic_cast
#include <iostream>
using namespace std;

class Base {
public:
    virtual void show() { cout << "Base class" << endl; } // Virtual function ensures RTTI
};
class Derived : public Base {
public:
    void show() override { cout << "Derived class" << endl; }
};
int main() {
    Derived* derivedPtr = new Derived();  // Create a Derived object

    // Upcasting using dynamic_cast
    Base* basePtr = dynamic_cast<Base*>(derivedPtr);
    if (basePtr)   basePtr->show();  // Calls Derived::show() due to virtual function
    else    cout << "Upcasting failed!" << endl;

    delete derivedPtr;  // Clean up memory
    return 0;
}
Output
Derived class
Since basePtr actually points to a Derived object and show() is virtual, it calls Derived::show().

Explanation
1.Derived-to-Base Upcasting (Base* basePtr = dynamic_cast<Base*>(derivedPtr);)
dynamic_cast<Base*> checks at runtime whether derivedPtr really points to a Derived object.
Since Derived is a subclass of Base, the cast succeeds.

2.Why Use dynamic_cast for Upcasting?
Upcasting normally does not require dynamic_cast, since it is always safe.
dynamic_cast ensures that the pointer really points to a valid derived object at runtime.

3.What If derivedPtr Was Not Derived from Base?
If derivedPtr pointed to an unrelated class, dynamic_cast would return nullptr.

When Should You Use dynamic_cast for Upcasting?
✅ When you want to confirm the object is actually derived from the base class at runtime.
✅ When working with multiple inheritance, where implicit upcasting might be ambiguous.
✅ When using polymorphism, and you are unsure of the actual type.

Key Takeaways
✔ Upcasting is usually safe and does not require dynamic_cast.
✔ Using dynamic_cast for upcasting is redundant unless verifying the objects actual type.
✔ dynamic_cast is more useful for downcasting, where type safety is needed.

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Is a relationship: 
Example of "Is-A" Relationship with dynamic_cast in C++
In object-oriented programming, the "Is-A" relationship means that a Derived class is a specialized version of a Base class. 
This is achieved using inheritance.

Example:
Dog is a Animal ✅
Car is not a Animal ❌

Since dynamic_cast is used to check if an object belongs to a particular derived class, it helps enforce the "Is-A" relationship at runtime.

🔹 Example: Checking "Is-A" Relationship using dynamic_cast
#include <iostream>
using namespace std;

class Animal {
public:
    virtual void makeSound() { cout << "Some generic animal sound" << endl; }
    virtual ~Animal() {} // Always define a virtual destructor when using polymorphism
};

class Dog : public Animal {
public:
    void makeSound() override { cout << "Bark!" << endl; }
    void wagTail() { cout << "Dog is wagging its tail!" << endl; }
};

class Cat : public Animal {
public:
    void makeSound() override { cout << "Meow!" << endl; }
};

void identifyAnimal(Animal* animal) {
    cout << "Checking type..." << endl;

    Dog* dogPtr = dynamic_cast<Dog*>(animal);    // Checking if the animal is actually a Dog
    if (dogPtr) {
        cout << "This is a Dog!" << endl;        
        dogPtr->wagTail(); // Calls a Dog-specific function
        return;
    }
    Cat* catPtr = dynamic_cast<Cat*>(animal);  // Checking if the animal is a Cat
    if (catPtr) {
        cout << "This is a Cat!" << endl;
        return;
    }
    cout << "Unknown Animal Type!" << endl;
}

int main() {
    Animal* a1 = new Dog(); // Upcasting: Dog is treated as an Animal
    Animal* a2 = new Cat(); // Upcasting: Cat is treated as an Animal

    identifyAnimal(a1); // Should detect Dog
    identifyAnimal(a2); // Should detect Cat

    delete a1;
    delete a2;

    return 0;
}
🔹 Output
Checking type...
This is a Dog!
Dog is wagging its tail!
Checking type...
This is a Cat!
🔹 Explanation
Upcasting (Animal* a1 = new Dog();)
Dog and Cat inherit from Animal.
Since every Dog "Is-An" Animal, we can assign Dog* to Animal* (upcasting).

Using dynamic_cast to check the true type at runtime
dynamic_cast<Dog*>(animal) checks if the given Animal* is actually a Dog*.
If successful, we call dogPtr->wagTail(), which is only available in Dog.

Verifying "Is-A" Relationship
Since Dog is an Animal, dynamic_cast succeeds.
If we try dynamic_cast<Car*>(animal), it will return nullptr because Car is not related to Animal.


