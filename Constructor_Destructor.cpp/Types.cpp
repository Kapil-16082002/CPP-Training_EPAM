✅Types of Constructors in C++ - 
Default Constructor
Parameterized Constructor
Copy Constructor
Move Constructor (C++11)

✅1. Default Constructor
A default constructor is a constructor that takes no parameters. 
If no constructor is defined, C++ provides a default constructor automatically.
#include <iostream>
using namespace std;
class Demo {
public:
    Demo() {  // Default Constructor
        cout << "Default Constructor Called!" << endl;
    }
};
int main() {
    Demo obj;  // Object creation calls the default constructor
    return 0;
}
Output:
Default Constructor Called!
//////////////////////////////////////////////////////////////////////////////////////////////////////////////

✅2. Parameterized Constructor
A parameterized constructor allows passing arguments to initialize an object with specific values.
#include <iostream>
using namespace std;
class Student {
    string name;
    int age;
public:
    Student(string n, int a) {  // Parameterized Constructor
        name = n;
        age = a;
    }
    void display() {
        cout << "Name: " << name << ", Age: " << age << endl;
    }
};
int main() {
    Student s1("Alice", 20);  // Constructor called with parameters
    s1.display();
    return 0;
}
Output:
Name: Alice, Age: 20

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

✅3. Copy Constructor
A copy constructor is used to create a new object as a copy of an existing object.

Does C++ Provide a Default Copy Constructor?
Yes.
If you do not explicitly declare a copy constructor, the compiler automatically generates a default copy constructor for you.
The default copy constructor performs a shallow copy of each member of the class.


#include <iostream>
using namespace std;
class Number {
    int value;
public:
    Number(int v) {  // Parameterized Constructor
        value = v;
    }
    Number(const Number &obj) { // The const ensures that the source object (other) cannot be modified during the copy process
        value = obj.value;
    }
    void display() {
        cout << "Value: " << value << endl;
    }
};
int main() {
    Number num1(10);  // Normal object creation
    Number num2 = num1;  //also  Number num2(num1);   
/*
✅ Number num2 = num1; → Copy Initialization
This syntax implicitly calls the copy constructor.
The compiler treats it as Number num2(num1);
Slightly less efficient
Use Cases: Used when object creation involves implicit conversions

✅ Number num2(num1); → Direct Initialization
This syntax is called direct initialization.
It explicitly calls the copy constructor.
More efficient
More efficient than Number num2 = num1; since no implicit conversion is involved.
*/
    num1.display();
    num2.display();

    return 0;
}
Output:
Value: 10
Value: 10