The const keyword in C++ is used to define read-only variables, functions, pointers, and objects. 
It helps enforce immutability and improve code safety.

//----------------------------------------------------------------------------------------------------------------
1️⃣ const with Variables
A const variable must be initialized when declared.
It cannot be modified after initialization.
✅ Example:

const int x = 10;   // ✅ Correct
// x = 20;          // ❌ Error! Cannot modify a `const` variable.

//------------------------------------------------------------------------------------------------------------
2️⃣ const with Pointers
const can be applied in three different ways with pointers.

(a) Pointer to const Data (const int* ptr)
The data cannot be modified, but the pointer can point to a different address.

const int a = 10;
const int b = 20;
const int* ptr = &a;  // ✅ Allowed
// *ptr = 50;        // ❌ Error: Cannot modify `a` via `ptr`
ptr = &b;            // ✅ Allowed: Changing pointer location

(b) const Pointer to Non-const Data (int* const ptr)
The pointer is fixed, but the data it points to can be modified.

int a = 10;
int* const ptr = &a;  // ✅ Must be initialized
*ptr = 50;            // ✅ Allowed: Modifying value of `a`
// ptr = &b;         // ❌ Error: Cannot change the pointer
(c) const Pointer to const Data (const int* const ptr)
Neither the pointer nor the data can be modified.

const int a = 10;
const int* const ptr = &a;  // ✅ Must be initialized
// *ptr = 50;              // ❌ Error: Cannot modify `a`
// ptr = &b;               // ❌ Error: Cannot change the pointer

//--------------------------------------------------------------------------------------------------------------
3️⃣ const in Function Parameters
Ensures that function arguments are not modified inside the function.

✅ Example:
void display(const int x) {
    // x = 20;  ❌ Error: Cannot modify `const` parameter
    cout << "Value: " << x << endl;
}

//-----------------------------------------------------------------------------------------------------------------
4️⃣ const Reference Parameters
Prevents unnecessary copying and ensures the original object remains unchanged.

✅ Example:
void show(const string& str) {
    // str += "World"; ❌ Error: Cannot modify `const` reference
    cout << str << endl;
}
int main() {
    string text = "Hello";
    show(text);
}
✔ Efficient for large objects
✔ Prevents accidental modifications

//---------------------------------------------------------------------------------------------------------------

5️⃣ const in Return Types
Ensures that the return value cannot be modified.

✅ Returning a const Value
const int getNumber() {
    return 100;
}
int main() {
    int x = getNumber();
    // getNumber() = 200;  ❌ Error: Return value is `const`
}
✅ Returning a const Reference
const string& getMessage() {
    static string msg = "Hello, World!";
    return msg;
}

int main() {
    const string& text = getMessage();
    // text += "!!!"; ❌ Error: Cannot modify `const` reference
}
✔ Prevents unnecessary copying
✔ Ensures read-only access
//---------------------------------------------------------------------------------------------------------------
1. const Member Function
A const member function does not modify any member variables of the class.
When a function is marked const, the this pointer inside the function is implicitly treated as a pointer to a const object.
this pointer inside the function becomes const ClassName*.

When a member function is declared as const
The const keyword ensures that:
The function cannot modify non-mutable member variables.
The function cannot call non-const member functions.

#include <iostream>
using namespace std;
class Test {
public:
    int x;
    Test(int val) : x(val) {}
    void show() const {  // `const` function
        cout << "Value: " << x << endl;
        // x = 20;  // ❌ ERROR: Cannot modify member variables inside a `const` function
    }
};
int main() {
    Test obj(10);
    obj.show();
    return 0;
}
🔹 Why Can not a const Member Function Modify Member Variables?
When a function is marked const, the this pointer inside the function is implicitly treated as a pointer to a const object.

🔹 Understanding this Pointer in const Functions
Inside a non-const function:
void modify() {
    this->value = 10;  // ✅ Allowed (non-const `this` pointer)
}
Inside a const function:
void show() const {
    this->value = 10;  // ❌ Error! Cannot modify `value`
}
🔹 Why?
In a non-const function, this is of type     Demo* const //constant pointer to a non-constant object.
In a const function, this is of type         const Demo* const.//constant pointer to a constant object.
➝ This means that the object itself is treated as const, preventing modification of any member variables.
/*
Demo* const Explanation 🚀
Demo* const is called a constant pointer to a non-constant object. This means:
✅ The pointer itself is constant (cannot point to another object).
❌ The object it points to is NOT constant (its members can be modified).

🔹 Syntax & Meaning
class Demo {
public:
    int value;
    Demo(int v) : value(v) {}
};
int main() {
    Demo obj1(10), obj2(20);
    Demo* const ptr = &obj1;  // ✅ Pointer is constant

    ptr->value = 50;   // ✅ Allowed: Can modify object
    // ptr = &obj2;    // ❌ Error: Cannot change pointer

    return 0;
}
🔹 Key Properties
Declaration	          Pointer	          Pointed Object  
Demo* ptr	          Can change	       Can modify
const Demo* ptr	      Can change	       ❌ Cannot modify
Demo* const ptr	      ❌ Cannot change	 Can modify
const Demo* const ptr	❌ Cannot change	 ❌ Cannot modify
*/

//-----------------------------------------------------------------------------------------------------------------
2. const Member Function with mutable Variables
If a member variable is declared mutable, it can be modified inside a const function.
#include <iostream>
using namespace std;
class Test {
public:
    mutable int x;  // `mutable` allows modification inside `const` function
    Test(int val) : x(val) {}
    void modify() const {  
        x = 20;  // ✅ Allowed because `x` is `mutable`
    }
    void show() const {
        cout << "Value: " << x << endl;
    }
};
int main() {
    Test obj(10);
    obj.modify(); // Modify mutable member
    obj.show();   // Output: 20
    return 0;
}
✅ Use When: You need to modify some members (like caching/logging) but keep the function const.
//-----------------------------------------------------------------------------------------------------------------

3. const Function Returning const Value
A const member function can return a const value to prevent modifications after return.
#include <iostream>
using namespace std;
class Test {
public:
    int x;
    Test(int val) : x(val) {}
    const int getValue() const {  
        return x;  // ✅ Return is `const`
    }
};
int main() {
    Test obj(10);
    int value = obj.getValue();
    // obj.getValue() = 30;  // ❌ ERROR: Cannot modify a `const` return value
    // value = 20;  // ✅ Allowed (copy of const value)
    // obj.getValue() = 30;  // ❌ ERROR: Cannot modify a `const` return value
    return 0;
}
✅ Use When: You want to prevent modifications on return values.

//------------------------------------------------------------------------------------------------------------------
4. const Function Returning const Reference
Prevents modification of returned reference.
#include <iostream>
using namespace std;
class Test {
public:
    int x;
    Test(int val) : x(val) {}
    const int& getRef() const {  
        return x;  // ✅ Return a `const` reference
    }
};
int main() {
    Test obj(10);
    const int& ref = obj.getRef();
    // ref = 30;  // ❌ ERROR: Cannot modify `const` reference
    return 0;
}
✅ Use When: Returning a large object as a read-only reference to avoid copying.
//-----------------------------------------------------------------------------------------------------------------
2.4. const Function Returning a const Pointer
class Test {
public:
    int x;
    Test(int val) : x(val) {}
    const int* getPointer() const {  
        return &x;
    }
};
int main() {
    Test obj(10);
    const int* ptr = obj.getPointer();
    // *ptr = 20;  // ❌ ERROR: Cannot modify `const` pointer value
    return 0;
}
✅ Use When: You need a pointer to read-only data.

//----------------------------------------------------------------------------------------------------------------

2.5. const Function Returning a const Pointer to const Value
class Test {
public:
    int x;
    Test(int val) : x(val) {}
    const int* const getConstPointer() const {  
        return &x;
    }
};
int main() {
    Test obj(10);
    const int* const ptr = obj.getConstPointer();
    // *ptr = 30;  // ❌ ERROR: Cannot modify value
    // ptr = nullptr;  // ❌ ERROR: Cannot change pointer address
    return 0;
}
✅ Use When: Neither the pointer nor the value should be modified.

//----------------------------------------------------------------------------------------------------------------

2.6. const Function Overloading
class Test {
public:
    int x;
    Test(int val) : x(val) {}

    void show() {  
        cout << "Non-const function" << endl;
    }
    void show() const {  
        cout << "Const function" << endl;
    }
};
int main() {
    Test obj(10);
    obj.show();  // Calls non-const version

    const Test obj2(20);
    obj2.show();  // Calls const version

    return 0;
}
✅ Use When: Behavior should change based on object const-ness.

2.7. static Function (Not Const)
Static functions cannot be const because they don’t operate on object state.
class Test {
public:
    static void show() {
        cout << "Static function called!" << endl;
    }
};
int main() {
    Test::show();
    return 0;
}
✅ Use When: Function doesn’t depend on object state.

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Trying to Call a Non-const Function Inside a const Function->
const member function CANNOT call a non-const function directly. 
This is because a const function treats the object as read-only, whereas a non-const function might modify it.

class Demo {
public:
    void nonConstFunction() {  
        cout << "Non-const function called!" << endl;
    }
    void constFunction() const {  
        // nonConstFunction(); // ❌ ERROR: Cannot call non-const function inside const function
        cout << "Const function called!" << endl;
        //const_cast<Demo*>(this)->nonConstFunction();  // ✅ Removes const and allows function call
    }
};
int main() {
    Demo obj;
    obj.constFunction();
    return 0;
}
🔴 Compiler Error:
error: passing ‘const Demo’ as ‘this’ argument discards qualifiers

🔹 All Possible const Function Combinations
Function Type	    	  	                  Allowed?
const → const	     	                     ✅ Allowed
const → non-const	 	                     ❌ Not Allowed
non-const → const	 	                     ✅ Allowed
non-const → non-const	                     ✅ Allowed



// 🔹 Full Code with All const Variations
// #include <iostream>
// using namespace std;
// class Demo {
// public:
//     void nonConstFunction() { 
//         cout << "Non-const function called!" << endl; 
//     }
//     void show() const { 
//         cout << "Const function called!" << endl; 
//     }
//     void setValue(const int x) { 
//         cout << "Received: " << x << endl; 
//     }
//     const int getValue() { 
//         return 42; 
//     }
//     const int& getConstRef() const {
//         static int value = 50;
//         return value;
//     }
//     const int* getPointer() const {
//         static int num = 100;
//         return &num;
//     }
//     void display(const int* ptr) {
//         cout << "Value: " << *ptr << endl;
//     }
//     void print(const string& str) { 
//         cout << "String: " << str << endl; 
//     }
//     void process(const Demo& obj) {
//         obj.show();
//     }
//     void callNonConst() const {
//         const_cast<Demo*>(this)->nonConstFunction();
//     }
// };
// int main() {
//     Demo obj;
//     obj.nonConstFunction();
//     obj.show();
//     obj.setValue(10);
//     cout << "getValue: " << obj.getValue() << endl;
//     cout << "getConstRef: " << obj.getConstRef() << endl;
    
//     int val = 30;
//     obj.display(&val);
    
//     string text = "Hello";
//     obj.print(text);

//     obj.callNonConst();  // Calling a function that removes const

//     return 0;
// }
// 🛠 Summary Table
// Function Type	             Syntax	                            Effect
// Non-const function	         void f();	                     Modifies object state
// Const function	             void f() const;	             Cannot modify object state
// Const parameter	             void f(const int x);	         Prevents modifying parameter
// Const return value	         const int f();	                 Returned value cannot be modified
// Const reference return	     const int& f() const;	         Efficient, prevents modification
// Const pointer return	     const int* f() const;	         Cannot modify pointed-to value
// Const reference parameter	 void f(const string& s);	     Avoids copying, prevents modification
// Const object parameter	     void f(const Demo& obj);	     Cannot modify obj
// Removing  const	             const_cast<Demo*>(this)->f();	 Breaks const-correctness

// 🚀 Conclusion
// ✅ Use const for safety, optimization, and code clarity.
// ✅ Use const_cast only if necessary (e.g., modifying cached values).
// ✅ mutable can be an alternative to const_cast.