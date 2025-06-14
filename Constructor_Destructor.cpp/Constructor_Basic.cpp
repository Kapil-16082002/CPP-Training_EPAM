✅#1. Constructor
A constructor is a special member function that is automatically called when an object of a class is created. 
 Its main purpose is to initialize the objects attributes.

Properties of Constructors:
Same Name as the Class:       The constructor has the same name as the class.
No Return Type:           Constructors do not have a return type, not even void.
Automatic Call:           It is invoked automatically when an object is created.
Can Be Overloaded:        Multiple constructors can be defined with different parameters (constructor overloading).

#Two constructor can't have same Arguments(i.e can not be overloaded)
#Two objects can't have same name

/////////////////////////////////// Code_Logic:1
class Demo {
    public:
        Demo() {
            cout << "Constructor Called!" << endl;
        }
        Demo(int x) {
            cout << "x " <<x<< endl;
        }  
        ~Demo() {
            cout << "Destructor Called!" << endl;
        } 
    };
    int main() {
       Demo d(10); 
        Demo a;
        return 0;
    }
Output:
x 10
Constructor Called!
Destructor Called!
Destructor Called!
///////////////////////////////////////// Code_Logic:2
class Demo {
    public:
        Demo() {
            cout << "Constructor Called!" << endl;
        }
        Demo(int x) {
            cout << "x " <<x<< endl;
        }  
        ~Demo() {
            cout << "Destructor Called!" << endl;
        } 
    };
    int main() {
       //Demo d(10);  // named object
        Demo(10); // Temporary unnamed object, both constructor, destructor called immediately
        Demo a;
        return 0;
    }
Output:
x 10
Destructor Called!
Constructor Called!
Destructor Called!

Case 1: Demo d(10);
This explicitly creates a named (stack-based)object d of type Demo.
The constructor Demo(int) is called with 10 as an argument.
Since d is a named object, its lifetime exist until it goes out of scope  (in main or (typically the end of the enclosing block).).
The destructor is only called when the object d goes out of scope at the end of main.

Case 2: Demo(10);
This creates a temporary (unnamed) object of type Demo.
Temporary object is destroyed immediately after creation.so it exists only for the expression in which it is created.
The destructor is called immediately after the temporary object’s creation completes, since the object is not stored and has no further use beyond its creation.

//////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <iostream>
using namespace std;
class Demo {
public:
    Demo() {
        cout << "Constructor Called!" << endl;
    }
    Demo(int x) {
        cout << "x " << x << endl;
    }
    ~Demo() {
        cout << "Destructor Called!" << endl;
    }
};
int main() {
    Demo d(10);  // (1) Named object
    Demo(10);    // (2) Temporary object
    Demo a;      // (3) Named object
    return 0;
}

Object 1: Demo d(10);///////////////////////////
Scope: Local to main(), exists until main() ends.
Constructor: Demo(int x) is called.
Destructor: Called at the end of main().

Object 2: Demo(10);//////////////////////////////
Scope: Temporary, exists only for that statement.
Constructor: Demo(int x) is called.
Destructor: Called immediately after the statement ends.

Object 3: Demo a;////////////////////////////////
Scope: Local to main(), exists until main() ends.
Constructor: Demo() is called.
Destructor: Called at the end of main().

Expected Output:
x 10                   // Constructor for d
x 10                   // Constructor for temporary object
Destructor Called!     // Destructor for temporary object (immediate destruction)
Constructor Called!    // Constructor for a
Destructor Called!     // Destructor for a (end of main)
Destructor Called!     // Destructor for d (end of main)

//==================================================================================================================

✅Key C++ Object Initialization Order:
When a class object is created:
First: The base class constructors (if any) are called.
Second: The member variables(like: m1,m2) constructors are called (in the order they're declared in the class; not the order in which they are initialized in the body of the constructor).
Lastly: The constructor of the class itself (e.g., Test) is called. 

#include <iostream>

class Base {
public:
    Base() {
        std::cout << "Base class constructor" << std::endl;
    }
    ~Base() {
        std::cout << "Base class destructor" << std::endl;
    }
};
class Member1 {
public:
    Member1() {
        std::cout << "Member1 constructor" << std::endl;
    }
    ~Member1() {
        std::cout << "Member1 destructor" << std::endl;
    }
};
class Member2 {
public:
    Member2() {
        std::cout << "Member2 constructor" << std::endl;
    }
    ~Member2() {
        std::cout << "Member2 destructor" << std::endl;
    }
};
class Derived : public Base {
private:
    Member1 m1; // Member variables
    Member2 m2;
public:
    Derived() {
        std::cout << "Derived class constructor" << std::endl;
    }
    ~Derived() {
        std::cout << "Derived class destructor" << std::endl;
    }
};

int main() {
    std::cout << "Creating Derived object..." << std::endl;
    Derived d; // Create a Derived object
    std::cout << "Derived object created." << std::endl;
    return 0;
}
Output:
Creating Derived object...
Base class constructor
Member1 constructor
Member2 constructor
Derived class constructor
Derived object created.
Derived class destructor
Member2 destructor
Member1 destructor
Base class destructor