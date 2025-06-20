
L-values and R-values are fundamental concepts in C++ related to expressions and memory allocation.

1️⃣ L-Value (Left-Hand Side Value)
✅ Definition:
//An L-value is an expression that persists beyond a single expression (i.e., it has a memory address). 
L-values have a memory address, and they remain in memory even after an expression is executed.
It can appear on both left and right sides of an assignment.

✅ Characteristics:
Has an identifiable memory address.
Can be assigned a new value.
Can be referenced using l-value references (&).

✅ Example Code:
#include <iostream>
using namespace std;
int main() {
    int x = 10; // x is an L-value (has memory)
    x = 20;     // Allowed, as L-value can be modified

    int& ref = x; // L-value reference (allowed)
    ref = 30;     // Allowed, modifying x through reference
    cout << "x = " << x << endl; // Output: x = 30
    return 0;
}
Output:
x = 30
✅ x is an L-value because it has a memory location and can be modified.
🚨 Not Allowed:
int& ref = 10; // ERROR! 10 is an R-value, cannot bind to int&
/*  Explanation:
int& ref = x;
A reference is just another name (alias) for an existing variable.
declares ref as a reference to x, meaning ref is just another name (alias) for x. Any modification to ref will directly affect x.

Breaking it Down:

int& → This means ref is a reference to an int type variable.
ref = x; → ref is initialized to refer to the existing variable x.
Key Points:
✔ A reference (ref) is NOT a new variable; it's just another name for x.
✔ Changing ref modifies x directly.
✔ A reference must be initialized at the time of declaration.
✔ Once a reference is bound to a variable, it cannot be changed to refer to another variable.
✔ No need for dereferencing (*).

3️⃣ Difference Between Reference and Pointer
Feature	            Reference (&)	Pointer (*)
Can be null?	    ❌ No	      ✅ Yes (nullptr)
Can be reassigned?	❌ No	      ✅ Yes
Needs dereferencing?❌ No	      ✅ Yes (*ptr)
Must be initialized?✅ Yes	      ❌ No (can be nullptr)

Conclusion
Use references (&) when you don't need to change the variable reference.
Use pointers (*) when you need flexibility (e.g., dynamic memory, nullable variables).

*/
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

2️⃣ R-Value (Right-Hand Side Value)

R-values are temporary values that exist only during the execution of an expression and cannot be assigned to variables directly.

✅ Characteristics:
No identifiable memory address.
Cannot be assigned another value (because it is temporary).
Can be referenced using R-value references (&&).

✅ Example Code:
#include <iostream>
int main() {
    int x = 10;  // 'x' is an L-value (has a persistent memory address)
    int y = x + 5; // (x + 5) is an R-value (temporary result)
    // Invalid: R-value cannot be assigned to
    // (x + 5) = 20; ❌ ERROR! Temporary values cannot be assigned
    std::cout << "x: " << x << ", y: " << y << std::endl;
    return 0;
}

✅ Characteristics:
No identifiable memory address.
Cannot be assigned another value (because it is temporary).
Can be referenced using R-value references (&&).

✅ Example Code:
#include <iostream>
using namespace std;
int getNumber() {
    return 42; // 42 is an R-value (temporary)
}
int main() {
    int y = getNumber(); // getNumber() returns an R-value (temporary)
    cout << "y = " << y << endl; // Output: y = 42

    int&& rref = 100; // Allowed: R-value reference
    cout << "rref = " << rref << endl; // Output: rref = 100

    return 0;
}
🔹 Output:
y = 42
rref = 100
✅ 100 is an R-value because it is temporary.

🚨 Not Allowed:
int&& rref = y; // ERROR! y is an L-value, cannot bind to int&&

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

3️⃣ R-Value References (&&)

R-value references allow us to capture temporary values and extend their lifespan.
✅ Example Code
#include <iostream>
using namespace std;

void process(int&& num) { // R-value reference
    cout << "Processing: " << num << endl;
}
int main() {
    process(50); // 50 is an R-value
    // process(x); // ERROR: cannot bind rvalue reference of type ‘int&&’ to lvalue of type ‘int’ . Hrer x is an L-value

    int&& rref = 100; // R-value reference
    cout << "rref = " << rref << endl; // Output: rref = 100
    return 0;
}
🔹 Output
Processing: 50
rref = 100
✅ int&& num binds to R-values only.


📌 When to Use What?
✅ Use L-value references (&) when:
You need to modify the object.
You pass objects by reference to avoid copying.


✅ Use R-value references (&&) when:
You need to capture temporary values.
You implement move semantics.


✅ Use std::move() when:
You want to transfer ownership without copying.


✅ Use std::forward() when:
You are perfectly forwarding arguments in templates.

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

5️⃣ Move Semantics (std::move())
Move semantics allow efficient resource transfer without copying.

✅ Example Code
#include <iostream>
#include <vector>
using namespace std;

int main() {
    vector<int> v1 = {1, 2, 3};
    vector<int> v2 = std::move(v1); // Moves v1 to v2

    cout << "v1 size: " << v1.size() << endl; // v1 is now empty
    cout << "v2 size: " << v2.size() << endl; // v2 owns the data

    return 0;
}
🔹 Output:
v1 size: 0
v2 size: 3
✅ std::move() converts an L-value into an R-value for efficient move operations.

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
1️⃣ L-Value and R-Value Function Parameters

✅ Functions can accept L-values and R-values differently based on reference types (&, &&).
✅ Example: L-Value and R-Value Function Overloading
#include <iostream>
using namespace std;
void process(int& x) { 
    cout << "L-value reference function called: " << x << endl; 
}
void process(int&& x) { 
    cout << "R-value reference function called: " << x << endl; 
}

int main() {
    int a = 10;
    process(a);   // Calls L-value version
    process(20);  // Calls R-value version

    return 0;
}
🔹 Output
L-value reference function called: 10
R-value reference function called: 20
✅ Why?
a is an L-value, so process(int&) is called.
20 is an R-value, so process(int&&) is called.

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

2️⃣ Returning L-Values and R-Values from Functions
Functions can return L-values or R-values, affecting how they are used.

✅ Example: Returning L-Values
int& getLValue(int& x) { // Returns an L-value reference
    return x;
}
int main() {
    int a = 5;
    getLValue(a) = 100; // Modifies 'a' directly
    cout << "a = " << a << endl; // Output: a = 100
    return 0;
}
✅ getLValue(a) returns a reference to a, so modification is allowed.

//----------------------------------------------------------------------------------------------------------------
✅ Example: Returning R-Values
int getRValue() {
    return 42; // Temporary R-value
}
int main() {
    int x = getRValue(); // Works fine (copies value)
    // getRValue() = 50; // ERROR: Cannot assign to an R-value
    return 0;
}
🚨 Why is getRValue() = 50; an error?
getRValue() returns a temporary R-value, which cannot be modified.



