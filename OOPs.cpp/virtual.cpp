Keyword: virtual
The keyword virtual in C++ allows the function to be overridden in derived classes, enabling runtime polymorphism through virtual table (vtable) mechanics.

✅Virtual Table (VTable)
When a class contains virtual functions:
1.The compiler creates a data structure called the Virtual Table (VTable).
2.The VTable is an array of function pointers where each pointer points to the most derived implementation of a virtual function for a particular class.
Each class has its own VTable (if it contains virtual functions), and all objects of that class share the same VTable.

NOTE:
The VTable allows the program to decide which function implementation to execute dynamically at runtime, rather than determining the function to be called at compile time. 
This is central to achieving runtime polymorphism.


✅Virtual Pointer (VPTR)
Each object of a class that contains virtual functions has a hidden pointer to the class's VTable. 
This pointer is called the vptr and set up by the compiler automatically when the object is created.

✅virtual function
virtual function is a member function of a class that is declared using the virtual keyword. 
Virtual functions enable function overriding in derived classes and support runtime polymorphism.

purpose of the virtual keyword :
1. Virtual functions enable function overriding in derived classes and support runtime polymorphism.
2.It ensures that the most derived version of a function is called when the function is invoked through a base class reference or pointer.


✅pure virtual function in C++?
A virtual function that is declared by assigning = 0 in its declaration. 
Example:
class Base {
    virtual void func() = 0;  // Pure virtual function
};
It makes the class abstract, meaning it cannot be instantiated.

✅Dynamic Dispatch
When you call a virtual function via a base class pointer or reference, the object’s vptr is used to look up the overridden function in the VTable at runtime. 
This process, called dynamic dispatch, enables polymorphic behavior.

✅Late Binding vs Early Binding
Non-virtual functions are resolved at compile-time (early binding), while virtual functions are resolved at runtime (late binding).


✅How the Virtual Table Works:
For every class containing virtual functions, the compiler generates a vtable.
The table stores pointers to the class's virtual functions, and when a derived class overrides a virtual function, its implementation replaces the corresponding entry in the vtable.
Each object of the class contains a virtual pointer (vptr) that points to the vtable. At runtime, the vptr is used to determine which function implementation to call.


✅Structure of the VTable
The VTable is a simple array-like structure, where:

Each entry is a pointer to a virtual function defined in the class or in its derived classes.
For pure virtual functions, there’s no actual function pointer, and the compiler often uses special entries to indicate that the class cannot be instantiated directly (abstract class).

#include <iostream>
using namespace std;
class Base {
public:
    virtual void func1() { cout << "Base: func1" << endl; }
    virtual void func2() { cout << "Base: func2" << endl; }
    virtual ~Base() {}  // Virtual destructor
};
class Derived : public Base {
public:
    void func1() override { cout << "Derived: func1" << endl; }
    void func2() override { cout << "Derived: func2" << endl; }
};
Base class VTable:
Index	Function Pointer
0	    Address of Base::func1
1	    Address of Base::func2
2	    Address of Base::~Base

Derived VTable:
Index	Function Pointer
0	Address of Derived::func1
1	Address of Derived::func2
2	Address of Derived::~Derived

Reason: 
Every Derived object is assigned a vptr that points to the Derived VTable.
A call to func1() or func2() through a Base pointer will resolve to the Derived implementation because the vptr in the derived object points to the Derived VTable.

int main() {
    Base* obj = new Derived();
    obj->func1();  // Dynamic lookup via vptr: Derived::func1() is called
    obj->func2();  // Dynamic lookup via vptr: Derived::func2() is called
    delete obj;    // Proper destruction: calls ~Derived() and ~Base()
}
Output:
Derived: func1
Derived: func2


✅VTable and Dynamic Dispatch

1.Dispatch Without Virtual Functions:
Without virtual, function calls are resolved at compile time based on the type of the pointer/reference. 
This is called static binding( Early Binding ):

Base base;
Derived derived;
Base* ptr = &derived;
ptr->func1();  // Calls Base::func1(), because the pointer type is Base*

2.Dispatch with Virtual Functions:
When a function is marked virtual, calls are resolved at runtime based on the actual type of the object being pointed to (not the type of the pointer itself). 
This is called dynamic binding(late binding):

Base* ptr = new Derived();
ptr->func1();  // Dynamic dispatch: Derived::func1() is called
Dynamic dispatch ensures that the correct version of the function in the derived class is executed, even when accessed through a base class pointer/reference.



✅Key Points about VTable: 
1.created Per-Class, Not Per-Object:
A VTable is created for the class, not for individual objects.
All objects of a class share the same VTable.

2.Pure Virtual Functions:
If a class has a pure virtual function, the VTable may store special markers or null function pointers to indicate the class is abstract and cannot be instantiated.

✅ Performance Costs of the VTable Mechanism:

Performance Overhead:
Function calls via the VTable require an indirect function lookup (following the vptr to the VTable and then invoking the function). 
This adds a small runtime overhead compared to direct calls.

Memory Overhead:
Each class with virtual functions requires a VTable.
Each object contains an additional vptr (hidden pointer), which increases object size.

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

✅Frequently Asked Questions
//----------------------------------------------------------------------------------------------------------------
✅why is virtual table called 'virtual'?

The virtual table (vtable) is called "virtual" because it supports the dynamic resolution of virtual function calls at runtime, a key feature of runtime polymorphism. 
It is specifically created for classes with virtual functions, enabling behavior to change dynamically based on the actual type of the object rather than its static type at compile time. 
The vtable facilitates dynamic dispatch by storing pointers to virtual function implementations, allowing overridden functions in derived classes to be correctly invoked.

//----------------------------------------------------------------------------------------------------------------

✅Difference between virtual double area() = 0;  and   virtual double area() ;
1. virtual double area() = 0;
This syntax declares a pure virtual function.
which basically means that  base class does not provide an implementation and derived class must implement it.

Derived classes must provide their own implementation of the pure virtual function. 
if do not make implementation of the pure virtual function in derived class will make the derived class abstract as well.

2. virtual double area();
This syntax declares a regular virtual function, not a pure virtual function.
A regular virtual function is a function that can be overridden in derived classes but it is not mandatory.

The base class can provide a default implementation, which derived classes can optionally override.
Behavior:
If a derived class overrides the function, polymorphism ensures the overridden version is called when accessed through a base class pointer/reference.
However, if the derived class does not override the function, the base class's implementation is used.

#include <iostream>
using namespace std;
class Shape {
public:
    // Regular virtual function
    virtual double area() {
        return 0.0; // Default implementation
    }
    virtual ~Shape() {}
};
class Circle : public Shape {
private:
    double radius;
public:
    Circle(double r) : radius(r) {}
    double area() override { // Overriding area() function
        return 3.14 * radius * radius;
    }
};
class Square : public Shape {
private:
    double side;
public:
    Square(double s) : side(s) {}
    double area() override { // Overriding area() function
        return side * side;
    }
};
int main() {
    Shape* circle = new Circle(5.0);
    Shape* square = new Square(4.0);
    Shape* genericShape = new Shape(); // Base class object

    cout << "Circle Area: " << circle->area() << endl;
    cout << "Square Area: " << square->area() << endl;
    cout << "Generic Shape Area (default): " << genericShape->area() << endl;

    delete circle;
    delete square;
    delete genericShape;
    return 0;
}
//----------------------------------------------------------------------------------------------------------------

✅. What happens if no virtual functions exist in the class?
If a class has no virtual functions, no VTable is created for it, and no vptr is needed. All function calls are resolved at compile time (static binding).

2. Can VTables be shared across classes?
No, every class with virtual functions has its own VTable.
3. Can I control or inspect the VTable?
The VTable is generated and managed entirely by the compiler. It’s possible to inspect the VTable indirectly using debugging tools but not programmatically manipulate it.

//----------------------------------------------------------------------------------------------------------------

✅What happens if a class does not override all pure virtual functions in its base class?

The derived class becomes abstract and cannot be instantiated until all pure virtual functions are overridden.
Reason: Because anotherPureVirtualFunction is not implemented . See below code..
#include <iostream>
class Base {
public:
    virtual void pureVirtualFunction() = 0; 
    virtual void anotherPureVirtualFunction() = 0; 
};
class Derived : public Base {
public:
    void pureVirtualFunction() override {
        std::cout << "pureVirtualFunction implemented in Derived" << std::endl;
    }
    // Note: anotherPureVirtualFunction is not overridden!
};
int main() {
    Derived obj;  // ERROR: Cannot instantiate an abstract class
    return 0;
}
//--------------------------------------------------------------------------------------------------------------

✅How does the compiler handle virtual function calls at runtime?
The compiler creates a VTable for each class that has virtual functions. 
Each object of such a class contains a vptr. 
At runtime, the vptr is used to determine the correct function pointer in the VTable to dynamically resolve and call the appropriate version of the virtual function.
//---------------------------------------------------------------------------------------------------------------

✅if I define a constructor in abstract class, what will happen then?
Answer:
In C++, you can define a constructor in an abstract class, and it behaves just like a constructor in any other class.

Key Points About Constructors in Abstract Classes:
An Abstract Class Can Have a Constructor:
Although you cannot create an instance of an abstract class directly, its constructor can still be defined and will be called when a derived class is instantiated.
The constructor of the abstract class is mainly used to initialize common data shared by derived classes.

**The Constructor is Called During Derived Class Instantiation:
When a derived class inherits from an abstract class, the abstract class’s constructor is called first (before the derived class constructor). This ensures that any initialization required for the base class is completed before the derived class’s constructor executes.

Object Instantiation Prohibited for Abstract Class:
Since you cannot directly instantiate an abstract class (due to at least one pure virtual function), you cannot call the constructor by creating an object of the abstract class itself.
This does not prevent the constructor from being called indirectly during the creation of a derived class object.
//----------------------------------------------------------------------------------------------------------------

✅Why Can't Abstract Classes Be Instantiated in C++?
Because They are incomplete by design, containing at least one pure virtual function without an implementation.
Abstract classes are designed to serve as blueprints or interfaces, enforcing derived classes to implement specific functionality defined by pure virtual functions. 
Creating an object of an abstract class is not allowed because it does not have all the necessary implementations to function properly.

Let’s break this down in detail:
Key Reasons Why Abstract Classes Cannot Be Instantiated:

1. Presence of Pure Virtual Functions
An abstract class contains at least one pure virtual function, which is declared with the = 0 syntax:
virtual void functionName() = 0;
A pure virtual function does not have an implementation in the abstract class. 
Derived classes are expected to override and provide their own implementation of these functions.
If you were to create an object of an abstract class, the compiler would have no definition to call for the pure virtual function if it is invoked, resulting in undefined behavior. To prevent this, the compiler prohibits instantiation of abstract classes.

//----------------------------------------------------------------------------------------------------------------
✅ Why base class constructor is called first and derived later??

The base class acts as the foundation for the derived class, and its members and states need to be fully initialized before the derived class can add its specific properties. 
This prevents undefined behavior by ensuring that derived class functionality does not access uninitialized base class members. 

//----------------------------------------------------------------------------------------------------------------

✅can i have a pure virtual constructor?

No, constructors cannot be virtual because virtual functions rely(fully dependent) on the virtual table (vtable).
And vtable is formed after the object is constructed—so during construction, the object does not yet have its vtable ready.

Since constructors run top-down (starting with the base class and then the derived class), there’s no way to dynamically decide which constructor to call. 
This means it’s not possible to dispatch constructors dynamically the way we do with virtual functions.

//---------------------------------------------------------------------------------------------------------------

✅can i have a pure virtual destructor?

Yes, you can have a pure virtual destructor in C++.
What Is a Pure Virtual Destructor?
A pure virtual destructor is a destructor that is declared as pure virtual using the = 0 syntax:
class Base {
public:
    virtual ~Base() = 0; // Pure virtual destructor
};
unlike other pure virtual functions, a pure virtual destructor must still be defined in the class. 
This is an exception to the general rule for pure virtual functions 
because the base class destructor will always be called (directly or indirectly) when an object of a derived class is destroyed.

Why Do We Need a Pure Virtual Destructor?
A pure virtual destructor establishes the base class as an abstract class, meaning that:

1.You cannot instantiate objects of the base class directly.
2.It enforces that derived classes must implement their destructors.

#include <iostream>

class Base {
public:
    // Pure virtual destructor
    virtual ~Base() = 0; // Declaration of a pure virtual destructor

    void display() {
        std::cout << "Base Display function" << std::endl;
    }
};
Base::~Base() {           // Definition of the pure virtual destructor
    std::cout << "Base Destructor called"  << std::endl;
}
class Derived : public Base {
public:
    ~Derived() {
        std::cout << "Derived Destructor called" << std::endl;
    }
};
int main() {
    Base* ptr = new Derived(); // Create a Derived object as a Base pointer
    delete ptr; // Proper destruction sequence: Derived -> Base

    return 0;
}
Output:
Derived Destructor called
Base Destructor called

//----------------------------------------------------------------------------------------------------------------
✅can I have a static virtual function?
or
Why Can’t a Function be Both Static and Virtual?

static functions do not have a this pointer: Since static functions are not tied to any particular object, they cannot access instance-specific data or functionality.
virtual functions operate based on an instance of the class and rely on the this pointer to resolve the correct implementation via the virtual table.
Therefore, it’s logically inconsistent for a function to be both static (no this pointer) and virtual (requires a this pointer).

//----------------------------------------------------------------------------------------------------------------

✅when does a virtual pointer get associated to an object, before construction, after it or at the time of construction?
Answer: vptr is initialized during object construction

1.Before Construction Starts: Before the constructor runs, the object is not fully constructed, and the vptr is not yet set. 
At this point, there is no association between the object and its vtable.
2.During Construction:
When a constructor of a class is invoked, the vptr points to the vtable corresponding to the object type.
If the class has a base class, the base class's constructor is called first. 
During the base class constructor's execution, the vptr points to the vtable of the base class.
After control returns to the derived class constructor, the vptr is updated to point to the vtable of the derived class.
This ensures that any virtual function calls made inside the constructors (or destructors) will resolve to the correct implementation associated with the type of the currently constructed object.

3.After Construction: Once the construction process is complete, the object is fully set up, with its vptr correctly pointing to its vtable

//----------------------------------------------------------------------------------------------------------------

can i have a pure virtual function in a structure?
Answer:
Yes, you can have a pure virtual function in a structure in C++, 
because in C++ there is no fundamental difference between a struct and a class other than the default access specifier.

Key Differences Between struct and class in C++
In a class, members are private by default.
In a struct, members are public by default.
Both struct and class can have member functions, constructor/destructor, data members, inheritance, polymorphism, and even pure virtual functions.

//----------------------------------------------------------------------------------------------------------------

✅What happens if you call a virtual function inside the constructor or destructor of a base class?

Calling a virtual function inside a base class constructor or destructor calls the base class implementation—
because the derived class vtable is either not set up yet (during construction) or reset to the base class (during destruction).

#include <iostream>
class Base {
public:
    Base() {
        std::cout << "Base constructor\n";
        print();  // Call to virtual function inside a constructor
    }
    virtual void print() const {
        std::cout << "Base print function\n";
    }
    virtual ~Base() {
        std::cout << "Base destructor\n";
        print();  // Call to virtual function inside a destructor
    }
};
class Derived : public Base {
public:
    Derived() {
        std::cout << "Derived constructor\n";
    }
    void print() const override {
        std::cout << "Derived print function\n";
    }
    ~Derived() {
        std::cout << "Derived destructor\n";
    }
};
int main() {
    Base* obj = new Derived();  // Create a Derived object
    delete obj;                 // Delete the object
    return 0;
}
Output:
Base constructor
Base print function
Derived constructor
Derived destructor
Base destructor
Base print function

//------------------------------------------------------------------------------------------------------------------
✅Can an abstract class have a constructor?
Yes, an abstract class can have a constructor, but it cannot be instantiated directly. 
The constructor can be called when an object of a derived (non-abstract) class is created.
This is useful for initializing the parts of the object that belong to the base class.
#include <iostream>
using namespace std;

class AbstractBase {
public:
    // Constructor in abstract class
    AbstractBase() {
        cout << "AbstractBase constructor called\n";
    }
    virtual void display() const = 0;
};
class Derived : public AbstractBase {
public:
    // Constructor in derived class
    Derived() {
        cout << "Derived constructor called\n";
    }
    // Override the pure virtual function
    void display() const override {
        cout << "Derived display function called\n";
    }
};

int main() {
    // Create an object of the derived class
    Derived obj;
    obj.display();

    return 0;
}
Output:
AbstractBase constructor called
Derived constructor called
Derived display function called

Execution Order:
The base class constructor (AbstractBase) is called first, followed by the derived class constructor (Derived).
This is because the derived class object consists of both the base class and derived class portions, and the base class must be initialized first.

//----------------------------------------------------------------------------------------------------------------

✅what happens if we do not make destructor virtual in abstract class and when a derived class object is deleted using a base class pointer. ??
Answer: Only Base destructor is called and derived destructor never called.
Because, destructor of the Base class is non-virtual.
When you delete a base class pointer (Base* obj) that points to a derived class object (new Derived()), the deletion process only considers the Base destructor. 
The derived class destructor is not called because the base class pointer does not enable runtime polymorphism for the destructor.

This can lead to resource leaks. With a virtual destructor, both base and derived class destructors are called in the correct order.


Base Destructor type   Behavior
Non-Virtual	           Only the base destructor is called; derived destructor is skipped.
Virtual	               Both derived and base destructors are called properly.

class Base {
    public:
        ~Base() {
            std::cout << "Base Destructor" << std::endl;
        }
    };
class Derived : public Base {
    public:
        ~Derived() {
            std::cout << "Derived Destructor" << std::endl;
        }
    };
int main() {
    Base* obj = new Derived();
    delete obj;  // Only Base destructor is called
    return 0;
    /*
    Derived* obj = new Derived(); // both destructor called
    delete obj; 
    Output: 
    Derived Destructor
    Base Destructor
    */

}

Explore gievn code also------>>>>>>>>
#include<bits/stdc++.h>
using namespace std;

class Base {
    public:
     Base() {
            std::cout << "Base Constructor" << std::endl;
        }
        ~Base() {
            std::cout << "Base Destructor" << std::endl;
        }
    };
class Derived : public Base {
    public:
    Derived() {
            std::cout << "Derived Constructor" << std::endl;
        }
        ~Derived() {
            std::cout << "Derived Destructor" << std::endl;
        }
    };
int main() {
    Base* obj = new Derived();
    delete obj; 
    return 0;
    /* 
    Derived* obj = new Derived();
    delete obj; 

    Output:
    Base Constructor
    Derived Constructor
    Base Destructor
    Derived Destructor

    */
}
Output:
Base Constructor
Derived Constructor
Base Destructor



//----------------------------------------------------------------------------------------------------------------

✅Explain the difference between hiding and overriding in the context of inheritance.

Hiding: Occurs when a derived class method with the same name as a base class method has a different signature or is not declared as virtual. The base class method is hidden but can be explicitly accessed using the scope resolution operator.
Overriding: Occurs when a derived class provides a virtual function with the same name, signature, and return type as the base class method.


//------------------------------------------------------------------------------------------------------------------

✅ how many virtual table does a class have?

The number of virtual tables (vtables) a class has depends on whether or not it is part of an inheritance hierarchy and its relationship with virtual base classes.
Here's a breakdown of how it works:

1. Single Inheritance and No Virtual Inheritance
A class generally has one vtable if it has at least one virtual function (including a virtual destructor).
This applies regardless of whether it is a base class or a derived class. All the virtual functions of the class are referenced in this single vtable.


#include <iostream>
class Base {
public:
    virtual void foo() {}
};
class Derived : public Base {
public:
    void foo() override {}
 
};
The Base class has a single virtual function: A vtable is generated for the Base class.
The Derived class overrides the foo() function: A new vtable is generated for the Derived class because it overrides the virtual function.
Total : 2 vtables



#include <iostream>
class Base {
public:
    virtual void foo() {}  // Virtual function
};
class Derived : public Base {
public:
    void foo() {}  // NOT marked `override` or `virtual`
};
Base defines a virtual function foo(). This means a vtable will be created for the Base class.
In Derived, the foo() function is not declared as virtual, and there is no override keyword explicitly used.
Derived simply "hides" Base's foo() due to name hiding. This is sometimes referred to as function hiding in C++.
Since Derived does not override Base's foo() in the virtual table, it does not generate its own vtable.
Both Base and Derived share the same vtable, which points to the Base implementation of foo().
Total: 1 vtable



#include <iostream>
class Base {
public:
    virtual void foo() {}
};
class Derived : public Base {
public:
    void foo()override {}
    virtual void bar() {}
};
The Base class has 1 vtable that includes an entry for foo().
The Derived class also has 1 vtable, but it includes:
An overridden entry for foo().
An additional entry for bar().
So, in this case, both Base and Derived have one vtable each separately.
Total : 2 vtable


2. Multiple Inheritance (No Virtual Inheritance)
In the case of multiple inheritance without virtual base classes, each base class that has virtual functions contributes its own separate vtable to the derived class.

class Base1 {
public:
    virtual void foo1() {}
};
class Base2 {
public:
    virtual void foo2() {}
};

class Derived : public Base1, public Base2 {
public:
    void foo1() override {}
    void foo2() override {}
};
Base1 has 1 vtable that includes an entry for foo1().
Base2 has 1 vtable that includes an entry for foo2().
Derived has 2 separate vtables, one for Base1 and one for Base2.
One vtable overrides foo1().
The second vtable overrides foo2().
Total : 3 vtables not 4..


class Base1 {
    public:
        virtual void foo1() {}
};
class Base2 {
    public:
        virtual void foo2() {}
};
class Derived : public Base1, public Base2 {
    public:
        void foo1() {}
        void foo2() override {}
};



3. Virtual Inheritance
When a class involves virtual inheritance, the derived class might share vtables across the hierarchy to manage the multiple shared instances of its virtual base class.

Example:
cpp


class Base {
public:
    virtual void foo() {}
};

class Derived1 : public virtual Base {
    virtual void bar() {}
};

class Derived2 : public virtual Base {
    virtual void baz() {}
};

class MultiDerived : public Derived1, public Derived2 {};
Here:

The Base class has a vtable with an entry for foo().
Each derived class (Derived1, Derived2) still gets a unique vtable for its own virtual functions (bar() and baz()).
The MultiDerived class:
Shares a single vtable for Base due to virtual inheritance.
Manages separate vtables for entries in Derived1 and Derived2.
Summary:
Single Inheritance without Virtual Inheritance: One vtable per class.
Multiple Inheritance: One vtable per base class with virtual functions; the derived class has multiple vtables.
Virtual Inheritance: Shared vtables for common virtual base classes.
