Types of Constructors in C++ - 
Default Constructor
Parameterized Constructor
Copy Constructor
Move Constructor (C++11)
1. Default Constructor
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
2. Parameterized Constructor
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
3. Copy Constructor
A copy constructor is used to create a new object as a copy of an existing object.
#include <iostream>
using namespace std;
class Number {
    int value;
public:
    Number(int v) {  // Parameterized Constructor
        value = v;
    }
    Number(const Number &obj) {  // Copy Constructor
        value = obj.value;
    }
    void display() {
        cout << "Value: " << value << endl;
    }
};
int main() {
    Number num1(10);  // Normal object creation
    Number num2 = num1;  // Copy constructor is called

    num1.display();
    num2.display();

    return 0;
}
Output:
Value: 10
Value: 10