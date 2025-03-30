reinterpret_cast in C++
reinterpret_cast is a type of casting operator that is used for converting one type into another, even if they are completely unrelated. 
It is typically used for low-level memory manipulations, such as casting pointers to and from integer types, or converting one pointer type to another.

Syntax of reinterpret_cast:

reinterpret_cast<new_type>(expression)
new_type: The type to which the expression is being cast.
expression: The value or pointer being cast.

1. Using reinterpret_cast with Pointers
Example: Converting a Pointer to an Integer
#include <iostream>
using namespace std;

int main() {
    int x = 42;
    int* ptr = &x;

    // Convert pointer to integer (memory address representation)
    uintptr_t address = reinterpret_cast<uintptr_t>(ptr);
    cout << "Memory Address: " << address << endl;

    // Convert back to pointer
    int* newPtr = reinterpret_cast<int*>(address);
    cout << "Value at newPtr: " << *newPtr << endl;

    return 0;
}
Output:
Memory Address: 140732839865700 (example value)
Value at newPtr: 42
Explanation:
We convert ptr (which holds an address) into an uintptr_t (integer type).
This allows us to store, print, or manipulate the memory address.
We then reinterpret the integer back to a pointer and successfully access the original value.
/*
✅uintptr_t is an unsigned integer type that is guaranteed to be able to store a pointer without loss of data. 
✅It is defined in the <cstdint> header.
✅Allows conversion between pointers and integers safely.
✅Always use reinterpret_cast for safe conversions between pointers and uintptr_t.

🔹 Key Differences Between uintptr_t and size_t
Type	     Purpose
uintptr_t	 Used for storing pointer addresses safely in an integer.
size_t	     Represents the size of objects in memory (used for array indexing, memory allocation, etc.).
*/

//--------------------------------------------------------------------------------------------------------------

2. Using reinterpret_cast with Classes:
Example: Casting a Class Pointer to a Different Type
#include <iostream>
using namespace std;

class Base {
public:
    virtual void show() { cout << "Base class" << endl; }
};
class Derived {
public:
    void display() { cout << "Derived class" << endl; }
};
int main() {
    Base baseObj;             
    Base* basePtr = &baseObj; // Pointer to Object
    // Reinterpret Base pointer as Derived pointer
    Derived* derivedPtr = reinterpret_cast<Derived*>(basePtr);//This line forcibly converts basePtr (a pointer to Base) into a pointer of type Derived* without checking compatibility.
    derivedPtr->display();  // Unsafe access - may cause undefined behavior!
 
    /* 
    Understood below concept  
    Base baseObj;     ✅ Stack Allocation
    Base* basePtr = &baseObj;

    baseObj is created on the stack.
    basePtr is a pointer that stores the address of baseObj.
    No new keyword is used, so memory is automatically managed and released when the function exits.

    Base baseObj;  
    Base* basePtr = baseObj;  // ❌ ERROR: Cannot assign object to pointer //Incorrect Usage (Direct Assignment)

    baseObj is an object, but basePtr is a pointer.
    You cannot assign an object to a pointer directly.
   ✅ Always assign pointers to memory addresses, not objects.

    //----------------------------------------------------------------------------------------------------------
    Base* baseObj = new Base();
    ✅ Heap Allocation
     baseObj is a pointer pointing to a dynamically allocated Base object.
     The object is created on the heap using new.
     You must manually delete it using delete baseObj; to prevent memory leaks.
    */

   
    return 0;
}
Why is this Dangerous?
Base and Derived are not related through inheritance.
Calling derivedPtr->display() leads to undefined behavior because the memory layout of Base does not match Derived.

//--------------------------------------------------------------------------------------------------------------

3. Using reinterpret_cast in Functions :
Example: Converting a Function Pointer
#include <iostream>
using namespace std;

void functionA() {
    cout << "Function A called!" << endl;
}
int main() {
    void (*funcPtr)() = functionA;

    // Cast function pointer to void*
    void* rawPtr = reinterpret_cast<void*>(funcPtr);

    // Cast back to function pointer
    void (*newFuncPtr)() = reinterpret_cast<void(*)()>(rawPtr);

    // Call the function
    newFuncPtr();

    return 0;
}
Output:
Function A called!
Explanation:
We cast a function pointer to void* and then back to a function pointer.
This is generally safe but should be used cautiously because function pointers are implementation-dependent.

//--------------------------------------------------------------------------------------------------------------

4. Using reinterpret_cast for Bitwise Type-Punning
Example: Interpreting Data Differently

#include <iostream>
using namespace std;

struct Data {
    int a;
    float b;
};

int main() {
    Data obj = {10, 5.5f};

    // Interpret the object as a raw byte array
    unsigned char* bytePtr = reinterpret_cast<unsigned char*>(&obj);

    cout << "Raw memory representation of Data object: ";
    for (size_t i = 0; i < sizeof(Data); i++) {
        cout << static_cast<int>(bytePtr[i]) << " ";
    }
    cout << endl;

    return 0;
}
Output (varies by system):
Raw memory representation of Data object: 10 0 0 0 0 0 B4 40
Explanation:
reinterpret_cast allows us to treat the struct as a raw byte array.
This is useful for low-level operations like serialization, networking, and debugging memory contents.

//--------------------------------------------------------------------------------------------------------------

🔹 1. Converting float to int Using reinterpret_cast
#include <iostream>
using namespace std;
int main() {
    float f = 3.14f;
    
    // Reinterpret float as int
    int* intPtr = reinterpret_cast<int*>(&f);  
    int intValue = *intPtr;  // Dereferencing to get value

    cout << "Float: " << f << endl;
    cout << "Reinterpreted int: " << intValue << endl;

    return 0;
}
🔹 Output (Bit Representation of Float as Int):
Float: 3.14
Reinterpreted int: 1078523331  // Bit pattern of 3.14 in IEEE 754 format
✅ The result is not 3 because we did not convert float to int, we just reinterpreted the raw memory bits.

🚀 Summary
Method	                    Effect	                            Example Output (for 3.14f)
reinterpret_cast<int*>(&f)	Reinterprets bits as int	        1078523331 (raw IEEE 754 bits)
static_cast<int>(f)	        Numerically converts float → int	3 (proper integer conversion)

👉 reinterpret_cast is only for bit reinterpretation, not for actual numerical conversions! 🚀

//-------------------------------------------------------------------------------------------------------------
6. When to Use reinterpret_cast?
✅ Valid Use Cases:
Converting pointers to integers and back (e.g., for low-level memory handling).
Converting between function pointers.
Accessing raw memory (e.g., binary file handling, serialization).

❌ When NOT to Use reinterpret_cast?
Between unrelated classes (e.g., casting Base* to Derived* when they are not polymorphic).
When static_cast or dynamic_cast is sufficient.
For type-punning (use union or memcpy instead).

7. Summary
reinterpret_cast allows converting completely unrelated types, mostly used for low-level memory operations.

It is dangerous because it bypasses type safety and can cause undefined behavior.

It should be used only when necessary, and safer alternatives (static_cast, dynamic_cast, const_cast) should be preferred.