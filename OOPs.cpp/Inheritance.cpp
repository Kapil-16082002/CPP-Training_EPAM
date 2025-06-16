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


// Diamond problem: virtual inheritance?? pre-post increment difference which better?

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
A combination of multiple and multilevel inheritance to prevent ambiguity using the virtual keyword.

Ambiguity Without Virtual Inheritance:

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
