Casting ->
Casting  is the process of converting one data type into another. C++ provides four types of casting:

1.Static Cast (static_cast)
2.Dynamic Cast (dynamic_cast)
3.Const Cast (const_cast)
4.Reinterpret Cast (reinterpret_cast)

1. static_cast (Compile-Time Casting)

Static casting in C++ is a type of casting that is checked at compile time and is used to convert one data type into another. 
It is performed using the static_cast operator and is generally used for conversions that are well-defined and do not require runtime type checking.
Cannot be used for casting between completely unrelated classes.
Syntax:
static_cast<new_type>(expression)

Use Cases of static_cast ->

1. Primitive Type Conversions
You can use static_cast to convert between primitive data types such as int, double, char, etc.
#include <iostream>
using namespace std;
int main() {
    double num = 10.67;
    int intNum = static_cast<int>(num); // Converts double to int (losing decimal part)
    cout << "Original: " << num << ", After static_cast: " << intNum << endl;
    return 0;
}
Output: Original: 10.67, After static_cast: 10
//----------------------------------------------------------------------------------------------------------------
2. Converting Pointers Between Related Types
static_cast can be used to convert pointers between related types (i.e., base and derived classes) in a safe way.

#include <iostream>
using namespace std;

class Base {
public:
    virtual void show() { cout << "Base class" << endl; } //This function is marked as virtual,means support runtime polymorphism (method overriding).
};
class Derived : public Base {
public:
    void show() override { cout << "Derived class" << endl; }
};
int main() {
    Derived d;
    Base* b = static_cast<Base*>(&d); // Upcasting (Safe)
    b->show();

    Derived* d_ptr = static_cast<Derived*>(b); // Downcasting (Needs caution)
    d_ptr->show();
   
    return 0;
}
Output:
Base class
Derived class
📌 Note: Downcasting with static_cast is only safe if the object is actually of the derived type.

Explanation:
  /*
    Upcasting (Safe)-
    Upcasting is the process of treating a derived class object as a base class object. 
    It happens when a pointer or reference of a derived class is assigned to a pointer or reference of its base class.

    pcasting is the process of converting a pointer or reference of a derived class to a pointer or reference of its base class. 
    It is always safe because a derived class object contains all members of its base class.
    After upcasting, the base class pointer/reference cannot access members that are specific to the derived class.

Base* b = static_cast<Base*>(&d);
What is happening?

d is of type Derived, but we are converting &d (address of d) to a Base*.
b is now a pointer of type Base*, but it still points to a Derived object.
Since Base contains a virtual function, calling b->show() invokes the overridden method in Derived (due to runtime polymorphism).
Since Derived is a subclass of Base, this is safe upcasting.

Why is it safe?
Upcasting (converting Derived* to Base*) is always safe because the Derived class contains all members of Base.
*/

/*
    Downcasting (Needs Caution)
    Downcasting is the process of converting a pointer or reference of a base class to a pointer or reference of its derived class. 
    Unlike upcasting, downcasting is unsafe unless we are certain that the base class pointer actually points to a derived class object.

    Derived* d_ptr = static_cast<Derived*>(b);
What is happening?
b is a Base*, but we are converting it to Derived* using static_cast.
Since b was originally pointing to a Derived object (due to upcasting), the downcast works correctly.
Calling d_ptr->show(); correctly calls Derived::show().
However, if b had been pointing to a Base object, this would cause undefined behavior.

Why is this risky?
If b were actually pointing to a Base object (instead of a Derived object), this would lead to undefined behavior.
Here, we know b was originally a Derived*, so it's safe in this specific case
    */

3. Removing const in a Limited Scope
static_cast can remove const from a variable, but it should be used with caution.

Example
#include <iostream>
using namespace std;

int main() {
    const int a = 10;
    int* ptr = const_cast<int*>(&a); // Safe in some cases but risky
    *ptr = 20; // Undefined behavior in some cases

    cout << "Modified a: " << *ptr << endl;
    return 0;
}
🚨 Warning: Although const_cast is better suited for this, static_cast can also remove const, but modifying const objects leads to undefined behavior.

//---------------------------------------------------------------------------------------------------------------

5. Casting to void* and Back
static_cast can be used to convert a pointer to void* and back.

Example
#include <iostream>
using namespace std;

int main() {
    int x = 42;
    void* voidptr1 = static_cast<void*>(&x);// Cast to void*
    
    int *p=&x;
    void* voidPtr2 = static_cast<void*>(p); // Cast to void*
    
    int* intPtr = static_cast<int*>(voidPtr2); // Cast back to int*
    cout << "Value: " << *intPtr << endl;

    return 0;
}
Output:
Value: 42
📌 Note: reinterpret_cast is usually preferred for this kind of conversion.

When NOT to Use static_cast ->
When casting between unrelated types (e.g., converting int* to double*). Use reinterpret_cast instead.
When dealing with polymorphic classes for safe downcasting. Use dynamic_cast instead.
When removing const or volatile. Use const_cast instead.





