
✅# CLASS
1. A Class is a user-defined data type that has data members and member functions.
   Data members are the data variables and member functions are the functions.
2. A class is a blueprint or template for creating objects. 

✅# OBJECTS
1. An object is an instance of a class. It holds the actual data and can use the methods defined by the class.
2. Multiple objects can be created from the same class, each with different data.

Objects represent real-world entities with:
Identity: A unique reference in memory.
State: The data (attribute values) associated with the object.
Behavior: Defined by the methods in the class.

Object Lifecycle
The object lifecycle includes:
Creation: Memory is allocated, and the constructor is invoked.
Usage: The object can call methods and modify attributes.
Destruction: Memory is released when the object goes out of scope. Optionally, a destructor (~class_name()) is invoked.


#Note: When a class is defined, no memory is allocated 
but when it is instantiated (i.e. an object is created) memory is allocated.


// --------------------------- Memory Occupied by object----------------------------------------------------------
Key Points to Remember:
1.An empty class is one that has no non-static data members or member functions.
class Empty {};

2.An object of this empty class will occupy 1 byte in memory:

Empty obj1, obj2;
cout << "Size of obj1: " << sizeof(obj1) << " bytes" << endl;
cout << ( &obj1 == &obj2 ? "Same address" : "Different addresses") << endl;
Output:
Size of obj1: 1 bytes

3. 1 Byte Memory is allocated to ensure that objects of the class have a unique address. 
Even in the case of empty classes, distinct instances (obj1 and obj2) must have different addresses.

//--------------------------------------------------------------------------------------------------------------

What if the Class has Static Members?
Static members belong to the class itself rather than individual objects. 
Therefore, they do not contribute to the size of any instance(object) of the class.

Example:
#include <iostream>
using namespace std;

class StaticTest {
    static int count;  // Static member variable
};
int StaticTest::count = 0;

int main() {
    StaticTest obj1, obj2;
    cout << "Size of static member object: " << sizeof(obj1) << " bytes" << endl;  // Still 1 byte
    return 0;
}
Output:
Size of static member object: 1 bytes.

//----------------------------------------------------------------------------------------------------------------

Empty Base Optimization (EBO)
If an empty class is used as a base class in an inheritance hierarchy, the compiler may optimize and prevent the empty base from occupying memory. 
This is called Empty Base Optimization (EBO).

Example:
#include <iostream>
using namespace std;

class Empty {};   // Empty class
class Derived : public Empty {
    int data;     // Non-empty derived class
};
int main() {
    cout << "Size of empty class: " << sizeof(Empty) << " bytes" << endl;        // 1 byte
    cout << "Size of derived class: " << sizeof(Derived) << " bytes" << endl;   // Size of int (4 bytes, EBO applied here)
    return 0;
}
Output:
Size of empty class: 1 bytes
Size of derived class: 4 bytes
Here, the empty class as a base class does not contribute to the memory used by Derived. 
This optimization avoids wasting memory and is supported by most modern C++ compilers.

✅Conclusion:
The size of an object of an empty class is 1 byte.
This is to ensure that each object has a unique memory address, as required by the C++ standard.
Static members do not contribute to object size.
Inheritance with empty base classes can use Empty Base Optimization (EBO) to eliminate unnecessary memory usage.


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Object Creation Methods in C++

1✅. Stack Allocation (Automatic Storage)
Objects can be created directly on the stack by declaring them in a function or scope using their type.

class MyClass {
public:
    int x;
    MyClass(int val) : x(val) {}
};
int main() {
    MyClass obj(10);  // Object created on stack (automatic memory allocation)

    cout << "Value of x: " << obj.x << endl;
    return 0;
}
Key Characteristics of Stack Objects:

1.Memory is automatically allocated and deallocated.
2.Lifetime within the scope in which it is created.
3.Stored in the stack memory region.

Advantages:
Easy to use.
No need to manually deallocate memory.
Memory management is faster since stack memory has low overhead.

Disadvantages:
Objects are limited by the stack size.
Cannot be shared outside the scope in which they were created (local lifetime).

//----------------------------------------------------------------------------------------------------------------

2✅. Heap Allocation (Dynamic Storage)
Objects can be created on the heap using the new operator. 
Such objects are stored dynamically, allowing manual management of their lifetime.
class MyClass {
public:
    int x;
    MyClass(int val) : x(val) {}
};
int main() {
    MyClass* obj = new MyClass(10);  // Object created on the heap
    cout << "Value of x: " << obj->x << endl;

    delete obj;  // Free memory manually
    return 0;
}
Key Characteristics of Heap Objects:

Stored in the heap memory region.
Explicitly created using new.
Must be manually destroyed using delete.

Advantages:
No lifetime restrictions (exists until you delete it).
These objects can be shared between different parts of the program.

Disadvantages:
Requires manual memory management (potential for memory leaks if delete is missed).
Slower to allocate/deallocate than stack objects due to heap overhead.

////////////////////////////////////////////////////////////////////////////////////////////////////////////////

6. Static Data Members & Static Member Functions
1. What are Static Data Members?
A static data member is a class variable that is shared among all objects of the class.
It belongs to the class, not individual objects.
It is declared using the static keyword inside the class but must be defined outside the class.
It gets memory allocation only once and retains its value across all objects.

6.1 Compile-time Input
class Car {
public:
    static int totalCars;
    Car() { totalCars++; }
    static void showTotal() {
        cout << "Total Cars: " << totalCars << endl;
    }
};
int Car::totalCars = 0;
int main() {
    Car c1, c2, c3;
    Car::showTotal();
    return 0;
}
Output:
Total Cars: 3
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
