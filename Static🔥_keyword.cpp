✅Static Keyword:
👉 static is a keyword used to control lifetime and visibility of variables/functions.


✅🔥Memory Behavior (VERY IMPORTANT)
void func() {
    static int x = 0;
}
👉 x is NOT stored on stack
👉 It is stored in Data Segment (Static Memory)
📌 Memory Types:
| Type                  | Stored In    | Lifetime           |
| --------------------- | ------------ | ------------------ |
| Normal local variable | Stack        | Function call only | 
| Static local variable | Data Segment | Entire program     |


✅🔥Initialization Happens Only Once
void func() {
    static int x = 10;
    cout << x << endl;
    x++;
}
Output:
10
11
12
👉 Initialization runs only first time function is called


✅🔥 3. Default Initialization = 0
👉 Static variables are automatically initialized to 0
void func() {
    static int x;  // no initialization
    cout << x << endl;
    x++;
}
Output:
0
1
2


//==============================    Static Local Variable   ===================================================

✅🔥 1. Static Local Variable (Inside Function)
#include <iostream>
using namespace std;
void counter() {
    static int count = 0;
    count++;
    cout << "Called: " << count << " times" << endl;
}
int main() {
    counter();
    counter();
    counter();
}
Called: 1 times
Called: 2 times
Called: 3 times
👉 Normal variable hota toh har baar 1 print hota
✅👉 Used for:
Counting function calls
Tracking state


🔥 Static vs Auto (Default)
void func() {
    int a = 0;        // auto (default)
    static int b = 0;
    a++;
    b++;
    cout << a << " " << b << endl;
}
Output:
1 1
1 2
1 3
👉 a resets every time
👉 b remembers value


✅Difference:
| Feature       | Global         | Static Local         |
| ------------- | -------------- | -------------------- |
| Scope         | Entire file    | Only inside function |
| Lifetime      | Entire program | Entire program       |
| Encapsulation | ❌ Poor        | ✅ Better           |


| Feature  | Static Global    | Static Local    |
| -------- | ---------------- | --------------- |
| Lifetime | Entire program   | Entire program  |
| Scope    | File only        | Function only   |
| Location | Outside function | Inside function |


==================================================================================================================

✅Static Global Variable
🔥 1. What is Static Global Variable ?
static int x = 10;

💡 Meaning:
1. Global variable (declared outside all functions)
2. But with static → scope limited to current file/program only
3. 
Internal Linkage (CORE CONCEPT):
int x = 10;  ✔ Accessible from other files using extern
static int x = 10;
❌ NOT accessible outside file
❌ extern will NOT work


🔥Why Use Static Global Variable ?
✅ 1. Data Hiding (Encapsulation)
    Prevent accidental modification from other files

✅ 2. Avoid Name Conflicts
// file1.cpp
static int count = 0;

// file2.cpp
static int count = 100;
👉 No conflict ✅
👉 Each file has its own copy

===================================================================================================================

✅ Static Data Members & Static Member Functions:
1. What are Static Data Members?
A static data member is a class variable that is shared among all objects of the class.
It belongs to the class, not individual objects.
It is declared using the static keyword inside the class but must be defined outside the class.
It gets memory allocation only once and retains(persists) its value across all objects.

Compile-time Input
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
