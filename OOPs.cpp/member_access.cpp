
⭐ MEMBER ACCESS OPERATORS
| Operator | Works on                              | Usage                        | Example       |
| -------- | ------------------------------------- | ---------------------------- | ------------- |
| `.`      | object                                | direct member access         | `obj.x`       |
| `->`     | pointer-to-object                     | access through pointer       | `ptr->x`      |
| `::*`    | class                                 | declare pointer-to-member    | `int A::* p;` |
| `.*`     | object + pointer-to-member            | access via pointer-to-member | `obj.*p`      |
| `->*`    | pointer-to-object + pointer-to-member | access via pointer-to-member | `ptr->*p`     |


🟦 1) . — Member access through object
Meaning:
Use the . operator when you have a normal object, NOT a pointer.

Syntax:
🟦 1) . — Member access through object
Meaning:
Use the . operator when you have a normal object, NOT a pointer.
Example:
A obj;
obj.x;
obj.show();

Why it works?
obj directly contains the data.
No dereferencing required.

//==============================================================================================================
🟦 2) -> — Member access through pointer-to-object
Meaning:
Used when you have a pointer pointing to an object.
//  -> = dereference + dot operator together.

Example:
A* ptr = &obj;
ptr->x;
ptr->show();


Why ->?
Because:
ptr->x  is same as  (*ptr).x

//==============================================================================================================

🟦 3) ::* — Pointer-to-member declaration (NOT an operator for access)
Meaning:
::* is used only to store the address of a data member or function member inside a class.
It is NOT used to access members.
Example:
int A::* ptrToData;         // pointer to data member
void (A::* ptrToFunc)();    // pointer to function member

Why needed?
Because class members are not normal variables in memory —
Their address depends on the specific object, so C++ gives a special type for this.

//==============================================================================================================

🟦 4) .* — Access member using object + pointer-to-member
Meaning:
Use .* when:

You have a normal object
AND you have a pointer-to-member
Example:
class A {
public:
    int x = 10;
};
int A::* ptr = &A::x;  // pointer to member

A obj;
cout << obj.*ptr;      // Access member through pointer-to-member


How it works internally?
ptr does NOT contain an actual memory address
It contains an offset inside the object
C++ combines obj + offset to access the element

This is why . or -> cannot be used for pointer-to-member.

//================================================================================================================

🟦 5) ->* — Access member using pointer-to-object + pointer-to-member
Meaning:
Use ->* when BOTH are pointers:
pointer to object
pointer to member

Example:
A obj;
A* p = &obj;

int A::* ptr = &A::x;

cout << p->*ptr;  // Same as p->x


Why required?
Because:
.* works with object
->* works with pointer to object
//===============================================================================================================

#include <iostream>
using namespace std;

class A {
public:
    int x = 10;
    int y = 20;

    void display() { cout << "Display function\n"; }
};
int main() {

    A obj;
    A* ptrObj = &obj;

    // 1) .
    cout << obj.x << endl;          // prints 10

    // 2) ->
    cout << ptrObj->y << endl;      // prints 20

    // 3) Declare pointer to member
    int A::* ptrX = &A::x;
    void (A::*ptrFn)() = &A::display;

    // 4) .*
    cout << obj.*ptrX << endl;      // prints 10
    (obj.*ptrFn)();                 // calls display()

    // 5) ->*
    cout << ptrObj->*ptrX << endl;  // prints 10
    (ptrObj->*ptrFn)();             // calls display()
}
