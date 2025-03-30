RTTI (Run-Time Type Information) is used to get information about an object at runtime, mainly in polymorphic class hierarchies.

🔹 RTTI Features in C++:
typeid → Checks the type of an object at runtime.
dynamic_cast → Safely converts pointers in an inheritance hierarchy.

🔹 1. typeid Example: Checking Object Type
#include <iostream>
#include <typeinfo>  // Required for typeid
using namespace std;
class Base {
public:
    virtual ~Base() {}  // Virtual destructor ensures RTTI works
};
class Derived : public Base {};

int main() {
    Base* base1 = new Base();
    Base* base2 = new Derived();

    cout << "base1 type: " << typeid(*base1).name() << endl;
    cout << "base2 type: " << typeid(*base2).name() << endl;

    delete base1;
    delete base2;
    return 0;
}
🔹 Expected Output (Exact names depend on the compiler):
base1 type: Base
base2 type: Derived

✅ Why is this useful?
Helps identify object types at runtime.
Useful for debugging polymorphic behavior.

//-----------------------------------------------------------------------------------------------------------------

🔹 2. dynamic_cast Example: Safe Downcasting
If you need to convert a Base* to Derived*, use dynamic_cast to ensure safety.
#include <iostream>
using namespace std;

class Base {
public:
    virtual void show() { cout << "Base class" << endl; }
    virtual ~Base() {}  // Virtual destructor for RTTI support
};
class Derived : public Base {
public:
    void show() override { cout << "Derived class" << endl; }
};

int main() {
    Base* basePtr = new Derived();  // Upcasting (safe)
    
    // Safe downcasting with dynamic_cast
    Derived* derivedPtr = dynamic_cast<Derived*>(basePtr);
    
    if (derivedPtr) {
        cout << "Successfully downcasted to Derived!" << endl;
        derivedPtr->show();  // ✅ Calls "Derived class"
    } else {
        cout << "Cast failed!" << endl;
    }

    delete basePtr;
    return 0;
}
🔹 Expected Output:
Successfully downcasted to Derived!
Derived class
✅ Why use dynamic_cast?
Prevents unsafe conversions (returns nullptr if cast fails).
Ensures type safety in polymorphic inheritance.

🔹 When to Use RTTI?
✅ Use typeid when you need to check an object's type dynamically.
✅ Use dynamic_cast when downcasting in a polymorphic hierarchy.
❌ Avoid overusing RTTI—prefer virtual functions when possible.
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

🔹 Summary: When to Use What?
Scenario	                          Use typeid (RTTI)	            Use dynamic_cast
Checking an object’s actual type	  ✅ Yes	                    ❌ No
Safely downcasting	                   ❌ No                 	✅ Yes
Works with non-polymorphic classes	   ✅ Yes	                ❌ No
Works with polymorphic classes	       ✅ Yes	                ✅ Yes
Can return nullptr for failed cast	   ❌ No	                    ✅ Yes
Can throw exceptions (bad_cast)	       ❌ No	                    ✅ Yes (for references)

🔹 In short:
Use typeid when you only need to check an object type.
Use dynamic_cast when you need safe type conversion in polymorphism.

//------------------------------------------------------------------------------------------------------------

🚀 RTTI vs dynamic_cast in C++
Both RTTI (Run-Time Type Information) and dynamic_cast are used for type identification at runtime, but they serve different purposes.

🔹 RTTI (Run-Time Type Information)
RTTI provides runtime type checking through:
typeid → Retrieves the actual type of an object.
dynamic_cast → Safely converts pointers in an inheritance hierarchy.

✅ Use When:
You want to check an object's actual type at runtime.
You need safe downcasting in polymorphic inheritance.

🔹 dynamic_cast
Used only with polymorphic classes (i.e., classes with at least one virtual function).
Performs safe downcasting (returns nullptr if the cast fails).
Works only with pointers and references.

✅ Use When:
You need safe conversion of base-class pointers to derived-class pointers.
You want to check if downcasting is valid at runtime.

🔹 Key Differences
Feature	                     RTTI (typeid)	                           dynamic_cast
Purpose	            Identifies an object's actual type at runtime	 Safely downcasts polymorphic pointers
Works With	        Any class (with or without virtual functions)	 Only polymorphic classes (with virtual functions)
Returns	            type_info object (contains type name)	         nullptr if cast fails (for pointers)
Failure Handling	Throws std::bad_typeid for nullptr references	 Returns nullptr for failed pointer casts, throws std::bad_cast for failed references
Performance	         Faster	                                         Slightly slower due to runtime checks
Use Case	       Logging, debugging, object inspection	         Safe downcasting in polymorphism
🔹 Example Code Comparing Both

#include <iostream>
#include <typeinfo>  // Required for RTTI
using namespace std;

class Base {
public:
    virtual ~Base() {}  // Required for RTTI and dynamic_cast
};

class Derived : public Base {};

int main() {
    Base* base1 = new Base();
    Base* base2 = new Derived();

    // Using typeid (RTTI)
    cout << "base1 type: " << typeid(*base1).name() << endl;
    cout << "base2 type: " << typeid(*base2).name() << endl;

    // Using dynamic_cast for safe downcasting
    Derived* derivedPtr = dynamic_cast<Derived*>(base2);
    if (derivedPtr)
        cout << "Successfully downcasted to Derived!" << endl;
    else
        cout << "dynamic_cast failed!" << endl;

    delete base1;
    delete base2;
    return 0;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

🚀 RTTI (typeid) Works with both polymorphic and Non-Polymorphic Classes ???  Why

The typeid operator in C++ provides type information at runtime and works with both polymorphic and non-polymorphic classes because:
✅For Non-Polymorphic Classes->
typeid works at compile-time when applied to an object of a non-polymorphic class.
The type information is determined statically (at compile time), and typeid directly refers to the declared type.

✅For Polymorphic Classes
When used on a pointer or reference to a base class, typeid works at runtime by retrieving the actual derived type.
This is only possible because polymorphic classes contain a virtual table (vtable), which allows typeid to fetch runtime type information.

Example: typeid with Non-Polymorphic and Polymorphic Classes
#include <iostream>
#include <typeinfo>
using namespace std;

class NonPolymorphic {
public:
    void show() { cout << "NonPolymorphic class" << endl; } 
//NonPolymorphic does not have any virtual functions, so RTTI (Run-Time Type Information) is not dynamically resolved. Instead, it works at compile time.
};
class Base {
public:
    virtual ~Base() {}  // Base has a virtual destructor, it becomes polymorphic, allowing RTTI to work at runtime.
};
class Derived : public Base {};

int main() {
    // ==========================
    // Non-Polymorphic Case
    // ==========================
    NonPolymorphic obj1;
    NonPolymorphic* ptr1 = &obj1;
    
    cout << "Type of obj1: " << typeid(obj1).name() << endl;  // obj1 is of type NonPolymorphic,which is statically known at compile time.
    cout << "Type of ptr1: " << typeid(ptr1).name() << endl;   // ptr1 is a pointer to NonPolymorphic, so the type starts with P (pointer) + NonPolymorphic.
    cout << "Type of *ptr1: " << typeid(*ptr1).name() << endl; // Since NonPolymorphic is not polymorphic, typeid(*ptr1) is resolved at compile time, so the output remains "14NonPolymorphic".

    // ==========================
    // Polymorphic Case
    // ==========================
    Derived obj2;
    Base* ptr2 = &obj2;
    cout << "Type of obj2: " << typeid(obj2).name() << endl;  //obj2 is an object of Derived class, which is known at compile time.
    cout << "Type of ptr2: " << typeid(ptr2).name() << endl;  // ptr2 is a pointer to Base, so the pointer type is printed (P4Base).
    cout << "Type of *ptr2: " << typeid(*ptr2).name() << endl; // Runtime check (dynamic)
    //ptr2 points to a Derived object, so typeid(*ptr2) correctly prints "7Derived" instead of "Base".
    return 0;
}
Output:
Type of obj1: 14NonPolymorphic
Type of ptr1: P14NonPolymorphic
Type of *ptr1: 14NonPolymorphic
Type of obj2: 7Derived
Type of ptr2: P4Base
Type of *ptr2: 7Derived
    /*
    Derived obj2;
    Base* ptr2 = &obj2;
✅This line means:
🔹ptr2 is a pointer to the base class Base.
🔹obj2 is an object of the derived class Derived.
🔹Upcasting happens implicitly—ptr2 stores the address of obj2 as a Base* pointer.
✅ What is Happening?
🔹obj2 is an object of Derived.
🔹Since Derived inherits from Base, obj2 contains all members of Base.

Implicit upcasting happens, meaning:
🔹The Derived object is treated as a Base object when accessed through ptr2.
🔹Only Base class members are accessible via ptr2.

🔹✅ Is This Allowed? Why?
Yes, it is allowed!
Because every Derived object is also a Base object due to inheritance.

Think of:
Let Base = Animal
Let Derived = Dog
A Dog is an Animal, so an Animal* pointer can store a Dog object

🔹 What Can You Do with ptr2?
Base* ptr2 = &obj2;
ptr2->someBaseFunction();  // ✅ Allowed (if defined in Base)
ptr2->someDerivedFunction();  // ❌ Not allowed (only Base members accessible)
Allowed: Calling functions defined in Base.
Not Allowed: Calling functions exclusive to Derived, unless you use downcasting
*/

Key Observations
For Non-Polymorphic Classes:
typeid(obj1) gives NonPolymorphic, determined at compile-time.
typeid(*ptr1) gives NonPolymorphic because the type is statically known.

For Polymorphic Classes:
typeid(*ptr2) evaluates dynamically at runtime and gives Derived, thanks to the virtual table mechanism.
If the base class lacks a virtual function, typeid(*ptr2) would return Base instead of Derived.

Why Does typeid Work in Both Cases ?
For non-polymorphic types, typeid evaluates statically at compile-time.
For polymorphic types, typeid evaluates dynamically at runtime when used on a pointer or reference to a base class.

