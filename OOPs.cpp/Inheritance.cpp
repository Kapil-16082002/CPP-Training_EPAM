Inheritance is a fundamental concept of object-oriented programming in C++ that allows one class (derived class) to inherit properties and behaviors (data members and member functions) of another class (base class). 
This promotes code reuse and helps in building a hierarchical relationship between classes.

Advantages of Inheritance
Code Reusability: Common functionality is written once in the base class and reused in derived classes.
Extensibility: The behavior of existing code can be extended by creating new derived classes.
Polymorphism: Enables run-time polymorphism when combined with virtual functions.

Key Notes:
Use virtual inheritance to resolve ambiguity in a hybrid inheritance scenario.
Private members of a base class are never directly accessible in derived classes, even with public inheritance.
Use inheritance only where it logically fits (e.g., "is-a" relationship).

 

✅1. Single Inheritance
In this type, a single derived class inherits from a single base class.

#include <iostream>
using namespace std;

class Base {
public:
    void displayBase() {
        cout << "This is the Base class" << endl;
    }
};
class Derived : public Base { 
public:
    void displayDerived() {
        cout << "This is the Derived class" << endl;
    }
};
int main() {
    Derived obj;
    obj.displayBase();  
    obj.displayDerived();  
    return 0;
}
Output:
This is the Base class
This is the Derived class

//--------------------------------------------------------------------------------------------------------------

✅2. Multilevel Inheritance
In this type, a class is derived from another derived class.

#include <iostream>
using namespace std;

class Grandparent {
public:
    void displayGrandparent() {
        cout << "This is the Grandparent class" << endl;
    }
};
class Parent : public Grandparent {
public:
    void displayParent() {
        cout << "This is the Parent class" << endl;
    }
};
class Child : public Parent {  // Child inherits from Parent
public:
    void displayChild() {
        cout << "This is the Child class" << endl;
    }
};
int main() {
    Child obj;
    obj.displayGrandparent();  
    obj.displayParent(); 
    obj.displayChild(); 
    return 0;
}
Output:
This is the Grandparent class
This is the Parent class
This is the Child class

//-----------------------------------------------------------------------------------------------------------------

✅3. Multiple Inheritance
In this type, a single derived class inherits from multiple base classes.

 Base1  |          |  Base2  |
   +---------+          +---------+
        |                    |
        ------------------------
                   |
            +-------------+
            |   Derived    |

#include <iostream>
using namespace std;

class Base1 {
public:
    void displayBase1() {
        cout << "This is Base1 class" << endl;
    }
};
class Base2 {
public:
    void displayBase2() {
        cout << "This is Base2 class" << endl;
    }
};
class Derived : public Base1, public Base2 {  // Inheriting from both Base1 and Base2
public:
    void displayDerived() {
        cout << "This is the Derived class" << endl;
    }
};
int main() {
    Derived obj;
    obj.displayBase1();  // Accessing Base1 function
    obj.displayBase2();  // Accessing Base2 function
    obj.displayDerived();  // Accessing Derived function
    return 0;
}
Output:
This is Base1 class
This is Base2 class
This is the Derived class

//-----------------------------------------------------------------------------------------------------------------

✅4. Hierarchical Inheritance
In this type, multiple derived classes inherit from a single base class.

         |   Base   |
         +---------+
          /       \
   +---------+   +---------+
   | Derived1 |   | Derived2 |

#include <iostream>
using namespace std;

class Base {
public:
    void displayBase() {
        cout << "This is the Base class" << endl;
    }
};
class Derived1 : public Base {
public:
    void displayDerived1() {
        cout << "This is the Derived1 class" << endl;
    }
};
class Derived2 : public Base {
public:
    void displayDerived2() {
        cout << "This is the Derived2 class" << endl;
    }
};
int main() {
    Derived1 obj1;
    Derived2 obj2;

    obj1.displayBase();
    obj1.displayDerived1();

    obj2.displayBase();
    obj2.displayDerived2();

    return 0;
}
Output:
This is the Base class
This is the Derived1 class
This is the Base class
This is the Derived2 class

//-----------------------------------------------------------------------------------------------------------------

✅5. Hybrid (Virtual) Inheritance

Hybrid Inheritance is a combination of more than one type of inheritance (e.g., single, multiple, multilevel). 
It is not necessarily the same as the Diamond Problem, but the Diamond Problem can occur in hybrid inheritance when multiple inheritance is involved.

#include <iostream>
using namespace std;

class Base {
public:
    void displayBase() {
        cout << "This is the Base class" << endl;
    }
};
class Derived1 : public Base {};
class Derived2 : public Base {};
class Hybrid : public Derived1, public Derived2 {  // Hybrid inherits from two Derived classes
    // Causes ambiguity when accessing Base class methods
};

int main() {
    Hybrid obj;
    // obj.displayBase();  // Error: Ambiguity! Which Base is being referred to?
    return 0;
}
Solution:
Resolving Ambiguity Using Virtual Inheritance:
#include <iostream>
using namespace std;

class Base {
public:
    void displayBase() {
        cout << "This is the Base class" << endl;
    }
};
// Virtual inheritance
class Derived1 : virtual public Base {};
class Derived2 : virtual public Base {};

class Hybrid : public Derived1, public Derived2 {};

int main() {
    Hybrid obj;
    obj.displayBase();  // Unambiguous due to virtual inheritance
    return 0;
}
Output:
This is the Base class

//================================================================================================================

✅Diamond problem: Virtual inheritance 
The Diamond Problem is a specific issue that arises in multiple inheritance when a derived class inherits from two classes, which themselves inherit from a common base class.
This creates a diamond-shaped inheritance hierarchy:

         A
       /   \
      B     C
       \   /
         D
Here:

A is the Base Class.
B and C inherit from A.
D inherits from both B and C.
Problem: The derived class D now has two copies of A (one from B and one from C), leading to ambiguity when accessing members of A through D.

#include <iostream>
using namespace std;

class A {
public:
    void display() {
        cout << "Class A" << endl;
    }
};

class B : public A { };
class C : public A { };

class D : public B, public C { };

int main() {
    D obj;
    obj.display(); // Ambiguity: Which "display()" should be called, B's or C's version of A?
    return 0;
}
Output: Error: ambiguous call to "display"

Correct Code with Virtual Inheritance
#include <iostream>
using namespace std;

// Base Class
class A {
public:
    void display() {
        cout << "Class A" << endl;
    }
};
// Virtual Inheritance
class B : virtual public A { }; // Virtually inherit A
class C : virtual public A { }; // Virtually inherit A

// Derived Class
class D : public B, public C { };

int main() {
    D obj;
    obj.display(); // No ambiguity now! Only one instance of A exists
    return 0;
}
Virtual Inheritance:
The keyword virtual ensures that B and C do not create duplicate instances of A(only a single shared instance of the base class exists.). Instead, they share a single instance of A.
This means the class D has only one copy of A, even though it inherits from both B and C.
