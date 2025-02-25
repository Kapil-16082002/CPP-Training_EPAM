#1. Constructor
A constructor is a special member function that is automatically called when an object of a class is created. 
 Its main purpose is to initialize the objects attributes.

Properties of Constructors:
Same Name as the Class:       The constructor has the same name as the class.
No Return Type:           Constructors do not have a return type, not even void.
Automatic Call:           It is invoked automatically when an object is created.
Can Be Overloaded:        Multiple constructors can be defined with different parameters (constructor overloading).

#Two constructor can't have same Arguments(i.e can not be overloaded)
#Two objects can't have same name

class Demo {                                                       
    public:
        Demo() {
            cout << "Constructor Called!" << endl;
        }
        ~Demo() {
            cout << "Destructor Called!" << endl;
        }
        cout<  
    };   
    int main() {
        Demo a,b,c;
        return 0;
    }
Output:  
Constructor Called!
Constructor Called!
Constructor Called!
Destructor Called!
Destructor Called!
Destructor Called!
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
       cout<<endl;//Const,cons,dest called after this endl;
       //Demo(10);
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
       //Demo d(10); 
        cout<<endl;
        Demo(10);//both const, dest called immediately
        Demo a;
        return 0;
    }
Output:
x 10
Destructor Called!
Constructor Called!
Destructor Called!

Difference betwen Demo d(10) and Demo(10) -> ////////////////////////
1. Demo d(10); (Named Object)
This creates an automatic (stack-based) object named d of type Demo.
The constructor Demo(int) is called with 10 as an argument.
The object d persists until it goes out of scope (typically the end of the enclosing block).

2. Demo(10); (Temporary Object)
This creates a temporary (unnamed) object of type Demo.
The constructor Demo(int) is invoked with 10 as an argument.
The object exists only for that statement and is immediately destroyed after its creation (unless assigned to a reference).
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