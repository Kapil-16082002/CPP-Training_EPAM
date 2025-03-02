 Topics Covered: 
         Shallow copy 
          Deep copy
          Handling Assignment Operator(=)
          chaining Assignment

What is Copying in C++?
When an object is copied to another, its data members (variables) are also copied.
There are two types of copying in C++ Object-Oriented Programming (OOP):

1️⃣ Shallow Copy
Copies only the memory address (pointer reference).
Both objects share the same memory.
If one object modifies or deletes memory, the other object is affected.
Leads to dangling pointers and memory corruption.

2️⃣ Deep Copy
Allocates new memory and copies the actual data.
Each object has its own independent memory.
Prevents memory corruption and dangling pointer issues.
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
1️⃣ Shallow Copy (Problem Example)
❌ Problem: Shared Memory Leads to Double Delete Error
#include<bits/stdc++.h>
using namespace std;
class myClass{
    int x;
    int*ptr;
public: 
    myClass(){
        x=20;
        ptr=new int(100);
        cout<<"Inside Default Constructor"<<endl;
    }
    void printX(){
        cout<<" Value of x: "<<x<<endl;
        cout<<" Value ptr is pointing to: "<<*ptr<<endl;
    }
    myClass(const myClass &obj){
        x=obj.x;
        ptr=obj.ptr; // ❌ Shallow Copy (Both objects share the same memory)
        /*
        This does not allocate new memory for ptr.
        Instead, it copies the memory address, making both obj1 and obj2 point to the same memory.
        When the destructor is called for obj2, it deletes the memory that obj1 is still using.
        ❌ Deleting obj1.data makes obj2.data a dangling pointer.
        ❌ Double delete error when the second object is destroyed.
        When obj1's destructor runs, it tries to delete the same memory again, causing undefined behavior (double delete error).
        */
    }
    ~myClass(){
        delete ptr;       // ❌ Double delete issue when copied object is destroyed
        cout<<" Inside Destructor "<<endl;
    }
};

int main(){
    myClass obj1;
    obj1.printX();
    
    myClass obj2(obj1);
    obj2.printX();
    return 0;  ❌ Both destructors will try to delete the same memory
}
Output:  (Undefined Behavior)
Inside Default Constructor
 Value of x: 20
 Value ptr is pointing to: 100
 Value of x: 20
 Value ptr is pointing to: 100
 Inside Destructor

✅ Fix: Implement Deep Copy in the Copy Constructor
To properly copy objects without sharing memory, use Deep Copy:
myClass(const myClass &obj){
    x = obj.x;
    ptr = new int(*(obj.ptr)); // ✅ Deep Copy (Allocates new memory)
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////
2️⃣ Deep Copy (Solution to Shallow Copy Problem)
✅ Corrected Code (Destructor Will Be Called Twice)
#include <bits/stdc++.h>
using namespace std;
class myClass {
    int x;
    int* ptr;
public:
    myClass() {
        x = 20;
        ptr = new int(100);
        cout << "Inside Default Constructor" << endl;
    }
    void printX() {
        cout << "Value of x: " << x << endl;
        cout << "Value ptr is pointing to: " << *ptr << endl;
    }
    // Deep Copy Constructor
    myClass(const myClass& obj) {
        x = obj.x;
        ptr = new int(*(obj.ptr)); // ✅ Allocating new memory
    }
    ~myClass() {
        delete ptr;                // ✅ Safe deletion (Each object has its own memory)
        cout << "Inside Destructor" << endl;
    }
};

int main() {
    myClass obj1;
    obj1.printX();
    
    myClass obj2(obj1);  // Calls Deep Copy Constructor
    obj2.printX();
    
    return 0;  // ✅ Both destructors will be called
}
Output:  (No Double Delete Error)
Inside Default Constructor
 Value of x: 20
 Value ptr is pointing to: 100
 Value of x: 20
 Value ptr is pointing to: 100
 Inside Destructor             ✅ (obj2 destroyed)
 Inside Destructor             ✅ (obj1 destroyed)

 📌 Why is Deep Copy Safe?
✅ Each object has its own separate memory.
✅ No memory corruption or dangling pointers.
✅ No double delete errors.

🎯 Key Takeaways
  ✔ Shallow Copy: Causes double delete errors when using dynamic memory.
  ✔ Deep Copy: Allocates new memory for each object, preventing memory issues.
  ✔ Always use a Deep Copy Constructor when dealing with new or heap memory.

3️⃣ Difference Between Shallow Copy and Deep Copy
Feature	                 Shallow Copy	                              Deep Copy
Memory Allocation	    Copies pointer (shared memory)	           Allocates new memory
Data Independence	    Changes in one object affect the other	   Each object has its own copy
Destructor Issue	    Can cause double delete errors	           No memory issues
Performance	            Faster (only copies address)	           Slightly slower (allocates new memory)
Best for?	          Non-pointer members, simple classes	        Classes with pointers or dynamic memory

///////////////////////////////////////////////////////////////////////////
🔹 Handling Assignment Operator (Deep Copy) for Integers in C++ OOPs - 
For integers, we generally don’t face deep copy issues because integers are primitive types stored directly inside objects. 
However, if we use dynamically allocated integers (int*), we must handle deep copy manually.

1️⃣ Why Do We Need a Deep Copy for Integers?
If an object contains a pointer to an integer (int*), then:

A default assignment operator will copy only the pointer, leading to shallow copy issues.
When the destructor runs, it frees memory twice (double delete error).
Changing the value in one object will affect the other, since both share the same memory.
2️⃣ Example: Shallow Copy Issue (Incorrect)
#include <iostream>
using namespace std;
class Shallow {
public:
    int* data;
    Shallow(int val) {
        data = new int(val);
    }
    // Default Copy Assignment (Shallow Copy) ❌
    void operator=(const Shallow& obj) {
        data = obj.data;  // ❌ Copies only pointer, not actual data
    }
    void show() {
        cout << "Value: " << *data << " | Address: " << data << endl;
    }
    ~Shallow() {
        delete data;  // ❌ Double delete issue if assigned
    }
};
int main() {
    Shallow obj1(10);
    Shallow obj2(20);

    obj1.show();  // 10
    obj2.show();  // 20

    obj2 = obj1;  // ❌ Copies pointer, not actual integer

    obj2.show();  // 10 (but both share same memory)

    return 0;  // ❌ Both objects try to delete the same memory
}
❌ Problems
obj2 = obj1; copies only the pointer, so both objects point to the same integer in memory.
When obj2 is destroyed, it deletes the shared memory.
When obj1 is destroyed, it tries to delete the same memory again (double delete error).
3️⃣ Correct Deep Copy Assignment Operator
To fix this, we must: ✔ Check for self-assignment (if (this != &obj)).
✔ Delete old memory before assigning new memory.
✔ Allocate new memory and copy the integer value.

✅ Correct Deep Copy Implementation
#include <iostream>
using namespace std;
class Deep {
public:
    int* data;
    Deep(int val) {
        data = new int(val);
    }
    // ✅ Deep Copy Assignment Operator
    Deep& operator=(const Deep& obj) {
        if (this != &obj) {  // Step 1: Prevent self-assignment
            delete data;  // Step 2: Free old memory
            data = new int(*obj.data);  // Step 3: Allocate new memory and copy value
        }
        return *this;  // Step 4: Return reference for assignment chaining
    }
    void show() {
        cout << "Value: " << *data << " | Address: " << data << endl;
    }
    ~Deep() {
        delete data;  // Free allocated memory
        cout << "Destructor called for " << data << endl;
    }
};
int main() {
    Deep obj1(10);
    Deep obj2(20);

    obj1.show();
    obj2.show();

    obj2 = obj1;  // Calls deep copy assignment operator
    obj2.show();  // Value copied, different memory allocated

    return 0;  // No double delete issues
}
🔹 Output
Value: 10 | Address: 0x61ff08
Value: 20 | Address: 0x61ff04
Value: 10 | Address: 0x61ff0C  ✅ (Different address than obj1)
Destructor called for 0x61ff0C
Destructor called for 0x61ff08

5️⃣ Key Takeaways
✔ Deep copy is needed only when dealing with pointers (int*).
✔ Check for self-assignment (if (this != &obj)) before deleting memory.
✔ Always return *this from the assignment operator to support chaining (a = b = c).
✔ Use delete before allocating new memory to prevent memory leaks.

/*
Deep& operator=(const Deep& obj) {
    if (this != &obj) {  // Avoid self-assignment
        delete[] str;  // Free old memory
        str = new char[strlen(obj.str) + 1];  // Allocate new memory
        strcpy(str, obj.str);
    }
    return *this;
}
1️⃣ What is this?
this is a pointer to the current object inside a member function.
It allows an object to refer to itself.
this stores the memory address of the calling object.
Example: Understanding this
class Example {
public:
    void show() {
        cout << "Address of this object: " << this << endl;
    }
};
int main() {
    Example obj1, obj2;
    obj1.show();  // Prints obj1's address
    obj2.show();  // Prints obj2's address
}
🔹 Output:
Address of this object: 0x61ff08
Address of this object: 0x61ff04
✔ Each object has a different this address.

2️⃣ What is *this?
*this is the dereferenced version of this, meaning it represents the actual object itself.
Since this is a pointer, *this gives us the object.

Use in Copy Assignment Operator
Deep& operator=(const Deep& obj) {
    if (this != &obj) {  // Check if assigning to itself
        delete[] str;  // Free old memory
        str = new char[strlen(obj.str) + 1];  // Allocate new memory
        strcpy(str, obj.str);
    }
    return *this;  // Return the current object
}
Why Use *this in return *this?
Allows assignment chaining (e.g., a = b = c;).
Ensures the function returns a reference to the current object.
3️⃣ Example: this and *this in Action
#include <iostream>
#include <cstring>
using namespace std;

class Deep {
public:
    char* str;
    Deep(const char* s) {
        str = new char[strlen(s) + 1];
        strcpy(str, s);
    }

    // Copy Assignment Operator
    Deep& operator=(const Deep& obj) {
        if (this != &obj) {  // Self-assignment check
            delete[] str;
            str = new char[strlen(obj.str) + 1];
            strcpy(str, obj.str);
        }
        return *this;  // ✅ Returning a reference to the current object
    }

    void show() {
        cout << "String: " << str << " | Address: " << this << endl;
    }

    ~Deep() {
        delete[] str;
    }
};
int main() {
    Deep obj1("Hello");
    Deep obj2("World");

    obj1.show();
    obj2.show();

    obj1 = obj2;  // Calls copy assignment operator
    obj1.show();

    return 0;
}
🔹 Output
String: Hello | Address: 0x61ff08
String: World | Address: 0x61ff04
String: World | Address: 0x61ff08  ✅ (obj1 is now same as obj2 but at its own address)
4️⃣ Summary
Feature	          this	                                     *this
Type	          Pointer to current object(Deep*)	          Actual object (Deep&)
Stores	          Address of current object	                  The current object itself
Usage	         this->var for accessing members	          return *this; for returning object reference
Needed in?	    Member functions, to refer to current object	Copy assignment operator, chaining
✅ Best Practices
✔ Always use this != &obj in copy assignment to prevent self-assignment issues.
✔ Return *this in assignment operators for assignment chaining.
✔ Use this-> explicitly if there is a naming conflict (e.g., parameter and member have the same name).
*/


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
✅ Deep Copy vs Shallow Copy for Character Arrays in C++ - 

1️⃣ Shallow Copy Problem (Character Arrays)
❌ Issue: Double Delete & Shared Memory
#include <iostream>
#include <cstring>  // For strcpy and strlen
using namespace std;
class Shallow {
public:
    char* str;

    Shallow(const char* s) {    // Constructor
        str = new char[strlen(s) + 1]; // Allocating memory
        strcpy(str, s);  // Copying string
    }

    // ❌ Shallow Copy Constructor (Copying pointer)
    Shallow(const Shallow& obj) {
        str = obj.str;  // ❌ Both objects share the same memory
    }
    // Destructor
    ~Shallow() {
        delete[] str;  // ❌ Double delete issue
        cout << "Destructor called\n";
    }
};

int main() {
    Shallow obj1("Hello");
    Shallow obj2 = obj1;  // Calls Shallow Copy Constructor

    cout << "obj1: " << obj1.str << endl;
    cout << "obj2: " << obj2.str << endl;

    return 0;  // ❌ Both destructors will try to delete the same memory
}
🔹 Output (Undefined Behavior)
obj1: Hello
obj2: Hello
Destructor called
// Destructor called  ❌ (Double delete error)
📌 Issues with Shallow Copy
❌ obj1.str and obj2.str point to the same memory.
❌ When obj2 is destroyed, it deletes str, making obj1.str a dangling pointer.
❌ When obj1 is destroyed, it tries to delete the same memory again, causing a double delete error.

2️⃣ Deep Copy Solution for Character Arrays
To prevent shared memory problems, we allocate new memory and copy the data in the deep copy constructor.
✅ Deep Copy Fix
#include <iostream>
#include <cstring>  // For strcpy and strlen
using namespace std;
class Deep {
public:
    char* str;
    // Constructor
    Deep(const char* s) {
        str = new char[strlen(s) + 1];  // Allocate memory
        strcpy(str, s);  
    }
    // ✅ Deep Copy Constructor (Allocates new memory)
    Deep(const Deep& obj) {
        str = new char[strlen(obj.str) + 1];  // Allocate new memory
        strcpy(str, obj.str);  // Copy content
    }
    ~Deep() {
        delete[] str;  // Safe deletion
        cout << "Destructor called\n";
    }
};
int main() {
    Deep obj1("Hello");
    Deep obj2 = obj1;  // Calls Deep Copy Constructor

    cout << "obj1: " << obj1.str << endl;
    cout << "obj2: " << obj2.str << endl;

    return 0;  // ✅ Each destructor deletes its own memory safely
}
🔹 Output (No Double Delete Error)
obj1: Hello
obj2: Hello
Destructor called  ✅ (obj2 destroyed)
Destructor called  ✅ (obj1 destroyed)
📌 Why is Deep Copy Safe?
✔ Each object has its own separate memory.
✔ No memory corruption or dangling pointers.
✔ No double delete errors.
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
3️⃣ Handling Assignment Operator (Deep Copy)
If we use assignment (=) after object creation, we also need to override the copy assignment operator.

✅ Deep Copy Constructor + Copy Assignment Operator
#include <iostream>
#include <cstring>
using namespace std;
class Deep {
public:
    char* str;
    Deep(const char* s) {
        str = new char[strlen(s) + 1];
        strcpy(str, s);
    }
    // ✅ Deep Copy Constructor
    Deep(const Deep& obj) {
        str = new char[strlen(obj.str) + 1];
        strcpy(str, obj.str);
    }
    // ✅ Deep Copy Assignment Operator
    Deep& operator=(const Deep& obj) {
        if (this != &obj) {  // Avoid self-assignment
            delete[] str;  // Free old memory
            str = new char[strlen(obj.str) + 1];  // Allocate new memory
            strcpy(str, obj.str);
        }
        return *this; // ✅ Returning a reference to the current object
    }
    ~Deep() {
        delete[] str;
        cout << "Destructor called\n";
    }
};
int main() {
    Deep obj1("Hello");
    Deep obj2 = obj1;  // Calls Deep Copy Constructor

    Deep obj3("World");
    obj3 = obj1;  // Calls Deep Copy Assignment Operator
    return 0;  // ✅ All objects clean up their own memory safely
}
🔹 Output
Destructor called  ✅ (obj3 destroyed)
Destructor called  ✅ (obj2 destroyed)
Destructor called  ✅ (obj1 destroyed)

📌 Why Implement Copy Assignment Operator?
✔ Avoids self-assignment issues.
✔ Prevents memory leaks by deleting old memory before copying.
✔ Ensures each object has its own memory.

5️⃣ Best Practices
✔ If your class has dynamically allocated memory (new), always implement a deep copy constructor.
✔ Use std::string instead of char* whenever possible to avoid manual memory management.
✔ Use smart pointers (std::unique_ptr, std::shared_ptr) for automatic memory handling.
////////////////////////////////////////////////////////////////////////////////////////////////////////////////

🔹 Implementing Assignment Operator with Chained Assignment in C++ OOPs
Chained assignment allows expressions like a = b = c;, where values are assigned from right to left. 
To enable this, our operator= function must return a reference (*this).

1️⃣ What is Assignment Chaining?
In expressions like:
A a, b, c;
a = b = c;  // Chain of assignment
b = c is evaluated first.
The result (b itself) is then assigned to a.
For this to work, operator= must return a reference to the current object (*this).

2️⃣ Simple Example with Integers
#include <iostream>
using namespace std;
class Number {
    int value;
public:
    Number(int val = 0) : value(val) {}
    // ✅ Assignment Operator Overloading
    Number& operator=(const Number& obj) {
        if (this != &obj) {  // Prevent self-assignment
            value = obj.value;
        }
        return *this;  // Returning *this allows assignment chaining
    }
    void show() {
        cout << "Value: " << value << endl;
    }
};
int main() {
    Number a(10), b(20), c(30);
    a = b = c;  // Chained assignment
    a.show();  // 30
    b.show();  // 30
    c.show();  // 30

    return 0;
}
🔹 Output
Value: 30
Value: 30
Value: 30
✅ Chaining works correctly because operator= returns *this.

3️⃣ Chained Assignment with Pointers (Deep Copy)
For dynamically allocated memory (e.g., int*), deep copy is required.

✅ Correct Deep Copy Implementation
#include <iostream>
using namespace std;
class Deep {
    int* data;
public:
    // Constructor
    Deep(int val) {
        data = new int(val);
    }
    // ✅ Deep Copy Assignment Operator
    Deep& operator=(const Deep& obj) {
        if (this != &obj) {  // Prevent self-assignment
            delete data;  // Free old memory
            data = new int(*obj.data);  // Allocate new memory and copy value
        }
        return *this;  // Returning *this allows assignment chaining
    }
    void show() {
        cout << "Value: " << *data << " | Address: " << data << endl;
    }
    ~Deep() {
        delete data;
        cout << "Destructor called for " << data << endl;
    }
};
int main() {
    Deep a(10), b(20), c(30);
    a = b = c;  // Chained assignment
    a.show();  // 30
    b.show();  // 30
    c.show();  // 30
    return 0;
}
🔹 Output
Value: 30 | Address: 0x61ff08
Value: 30 | Address: 0x61ff0C
Value: 30 | Address: 0x61ff10
Destructor called for 0x61ff0C
Destructor called for 0x61ff08
Destructor called for 0x61ff10
✅ Each object gets its own memory, preventing shared memory issues.

4️⃣ Key Takeaways
✔ Returning *this from operator= allows assignment chaining (a = b = c).
✔ For pointers (int*), use deep copy to prevent memory leaks or double delete errors.
✔ Always check for self-assignment (if (this != &obj)).



