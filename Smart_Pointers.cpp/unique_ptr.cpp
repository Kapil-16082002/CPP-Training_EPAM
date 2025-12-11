
1. What is std::unique_ptr?
std::unique_ptr is a smart pointer in C++ that provides exclusive ownership of a dynamically allocated object i.e Only one unique_ptr can own a Object(resource) at a time.
std::unique_ptr is a smart pointer in C++ that manages dynamic memory. 
It ensures that the allocated object is automatically deleted when the unique_ptr goes out of scope, preventing memory leaks.

Key Features
✅ Exclusive Ownership → Only one unique_ptr can own a Object(resource) at a time. does not allow copy semantics but supports transfer of ownership using move semantics.
✅ Automatic Cleanup → Automatically deletes the object when unique_ptr goes out of scope.
✅ No Copying Allowed → Copying a unique_ptr is not allowed (unique_ptr can not be shared).
✅ Supports Move Semantics → Ownership can be transferred using std::move().

✅Use Case: Best used when a resource should have a single owner like in resource management (e.g., file handles, network sockets).


/*std::unique_ptr does not use a control block.
Why not?
std::unique_ptr is a single-owner smart pointer, meaning there is no need to track ownership or reference counts.
*/
Syntax:
std::unique_ptr<MyClass> car1 = std::make_unique<MyClass>();
// Create a unique_ptr for an array of MyClass objects
std::unique_ptr<MyClass[]> myClassArray = std::make_unique<MyClass[]>(size);
/* 
// Dynamically create a MyClass object with raw pointer
    MyClass* Obj = new MyClass(42);  // Allocating memory for a single object

    // Dynamically create an array of MyClass objects
    MyClass* Obj = new MyClass[size];  // Uses default constructor for all objects

*/
Step 1: std::make_unique<MyClass>()
std::make_unique<MyClass>() is a C++14 feature.
It dynamically allocates memory for a MyClass object.
Equivalent to: new MyClass();

Step 2: std::unique_ptr<MyClass> ptr = ...;
std::unique_ptr<MyClass> is a smart pointer that Owns the MyClass object.
Ensures proper deletion when it goes out of scope.

2✅. Basic Usage of std::unique_ptr
(A) Creating a std::unique_ptr
#include <iostream>
#include <memory>
class MyClass {
public:
    MyClass() { std::cout << "MyClass Constructor\n"; }
    ~MyClass() { std::cout << "MyClass Destructor\n"; }
    void show() { std::cout << "Hello from MyClass\n"; }
};
int main() {
    std::unique_ptr<MyClass> ptr = std::make_unique<MyClass>(); //std::make_unique<MyClass>() dynamically allocates a MyClass object.
    ptr->show();  // Accessing member function
    return 0;  // `ptr` goes out of scope, object is automatically deleted
}
🔹 Output:
MyClass Constructor
Hello from MyClass
MyClass Destructor
✅ No need to manually delete the object!
✅ Efficient and prevents memory leaks.

//---------------------------------------------------------------------------------------------------------------

3✅. Why std::unique_ptr is Not Copyable
Unlike std::shared_ptr, a std::unique_ptr cannot be copied because it has exclusive ownership.

(B) Copying a std::unique_ptr – Compilation Error
std::unique_ptr<MyClass> ptr1 = std::make_unique<MyClass>();
std::unique_ptr<MyClass> ptr2 = ptr1;  // ❌ Error: Copy constructor is deleted

✅ Fix: Use std::move() Instead
std::unique_ptr<MyClass> ptr1 = std::make_unique<MyClass>();
std::unique_ptr<MyClass> ptr2 = std::move(ptr1);  // Transfers ownership

🔹 std::move() transfers ownership from ptr1 to ptr2.
🔹 After the move, ptr1 becomes empty.

//-----------------------------------------------------------------------------------------------------------------

3.✅unique_ptr with Class Members:

#include <bits/stdc++.h>
#include <memory>
using namespace std;

class Engine {
public:
    Engine() { std::cout << "Engine created\n"; }
    ~Engine() { std::cout << "Engine destroyed\n"; }
    void start() { std::cout << "Engine started!\n"; }
};
class Car {
private:
    std::unique_ptr<Engine> engine;  // Unique ownership of Engine
public:
    Car() : engine(std::make_unique<Engine>()) { // creates an Engine object and transfers ownership to engine.
        std::cout << "Car created\n"; //"Engine created" is printed first, followed by "Car created".
    }
    void startCar() { engine->start(); }
    ~Car(){
        std::cout << "Car destructor\n";
    }
};
int main() {
    Car myCar;
    myCar.startCar();
    return 0;
}
🔹 Final Output:
Engine created
Car created
Engine started!
Car destructor
Engine destroyed
🔹 Why is "Engine destroyed" printed last?
Since std::unique_ptr automatically deletes the Engine when the Car object is destroyed, cleanup happens when main() ends.

/*
🔹 Execution Flow
1.Car myCar;
   Calls Car() constructor:
   Creates an Engine object → Prints "Engine created".
   Creates a Car object → Prints "Car created".

2.myCar.startCar();
   Calls engine->start(), printing "Engine started!".

3.End of main() (Automatic Cleanup)
   myCar goes out of scope, triggering:
   Car destructor (implicit)
   std::unique_ptr automatically deletes the Engine
   "Engine destroyed" is printed.
*/
🔹 Alternative: Without unique_ptr (Manual Memory Management)
class Car {
private:
    Engine* engine;
public:
    Car() {
        engine = new Engine();  // 🚨 Must manually delete later
        std::cout << "Car created\n";
    }
    ~Car() {  // 🚨 Manual deletion required
        delete engine;
        std::cout << "Car destroyed\n";
    }
    void startCar() { engine->start(); }
};
🚨 Problems:
Requires explicit delete engine; in the destructor.
If an exception is thrown before delete engine;, it causes a memory leak.
std::unique_ptr solves this issue automatically.

//---------------------------------------------------------------------------------------------------------------

4✅. std::unique_ptr with Arrays
(C) Managing Arrays
When using std::unique_ptr with arrays, you must specify [] in the constructor.

std::unique_ptr<int[]> arr = std::make_unique<int[]>(5);// arr will take only one  argument(arr of 5 size  in this case), default value of arr elements is 0

for (int i = 0; i < 5; ++i)
    arr[i] = i * 10;  // Access like a normal array

for (int i = 0; i < 5; ++i)
    std::cout << arr[i] << " ";  // Output: 0 10 20 30 40
🔹 No need to use delete[], unique_ptr takes care of it.

//----------------------------------------------------------------------------------------------------------------

5. Using unique_ptr in Functions
(D) Returning std::unique_ptr from a Function
std::unique_ptr<MyClass> createObject() {
    return std::make_unique<MyClass>();  // Return unique_ptr (RVO optimization)
}
int main() {
    std::unique_ptr<MyClass> obj = createObject();  // No extra copies!
}
🔹 Safe and efficient way to return dynamic objects.
🔹 No risk of memory leaks!

//-----------------------------------------------------------------------------------------------------------------

6.unique_ptr with STL Containers->
#include <iostream>
#include <memory>
#include <vector>
class Dog {
private:
    std::string name;
public:
    Dog(std::string name) : name(name) {
        std::cout << name << " created\n";
    }
    ~Dog() { std::cout << name << " destroyed\n"; }
};
int main() {
    std::vector<std::unique_ptr<Dog>> dogs;
    dogs.push_back(std::make_unique<Dog>("Buddy"));
    dogs.push_back(std::make_unique<Dog>("Charlie"));

    return 0;
}
Output:
Buddy created
Charlie created
Charlie destroyed
Buddy destroyed

✅Why is "Buddy destroyed" printed before "Charlie destroyed"?
The order of destruction in std::vector<std::unique_ptr<Dog>> dogs follows the LIFO (Last In, First Out) principle because:
1.std::vector stores elements in sequential order.
2.When the vector is destroyed, it destroys elements in reverse order of insertion.
3.End of main(): Vector dogs goes out of scope
4.std::vector destroys elements in reverse order of insertion.
so,
Charlie was inserted last, so it gets destroyed first.

//-------------------------------------------------------------------------------------------------------------

6. Custom Deleters in std::unique_ptr
Sometimes, we need a custom deleter (e.g., closing a file, releasing a database connection).

(E) Using a Custom Deleter
struct FileCloser {
    void operator()(FILE* file) {
        if (file) {
            fclose(file);
            std::cout << "File closed successfully!\n";
        }
    }
};

int main() {
    std::unique_ptr<FILE, FileCloser> filePtr(fopen("test.txt", "w"));
}
🔹 The custom deleter ensures the file is closed properly when filePtr goes out of scope.



7. std::unique_ptr with Inheritance and Polymorphism
(F) Handling Polymorphic Objects

class Base {
public:
    virtual void show() { std::cout << "Base class\n"; }
    virtual ~Base() = default;
};
class Derived : public Base {
public:
    void show() override { std::cout << "Derived class\n"; }
};
int main() {
    std::unique_ptr<Base> ptr = std::make_unique<Derived>();  // Upcasting
    ptr->show();  // Output: Derived class
}
🔹 Polymorphism works correctly with unique_ptr when using virtual functions.

#include <iostream>
#include <memory>
using namespace std;

int main()
{
    unique_ptr<int>unPtr = make_unique<int>(25);
    /*
    make_unique<int>(25) -> dynalically allocates an int with value 25, ans returns
    unique_ptr<int> managing that memory
    unique_ptr<int> unPtr = ... -> unPtr is a unique_ptr<int> that now owns the allocates int
    
    */
    cout << unPtr.get() << endl; //prints memory address
    cout << *unPtr << endl; //dereferences unique pointer
    /*
    properties of unique_ptr
    -> only one unique_ptr can own a resource at a time.
    -> when unique_ptr goes out of scope, it deletes the object
    ->  Copying a unique_ptr is not allowed (unique_ptr can't be shared).
    -> Ownership can be transferred using std::move().
    */

    return 0;
}