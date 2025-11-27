
The word “polymorphism” means having many forms.
we can define polymorphism as the ability of a message to be displayed in more than one form.
  A real-life example of polymorphism is a person who at the same time can have different characteristics. 
  A man at the same time is a father, a husband, and an employee. 
  So the same person exhibits different behavior in different situations. This is called polymorphism. 

Polymorphism in C++ is mainly divided into two types:

1.Compile-time Polymorphism (also known as Static Polymorphism) or (Static or early Binding)
In compile-time polymorphism, the function to be called is determined at compile time. 
This is achieved by function overloading and operator overloading.

    1.Function Overloading
    2.Operator Overloading,

2.Run-time Polymorphism (also known as Dynamic Polymorphism)    or (Dynamic or late Binding)
In Run-time polymorphism, the function to be called is determined at run time. 
    1.Function Overriding
    2.Virtual Function

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#1. Compile-Time Polymorphism
(a) Function Overloading
Function overloading allows multiple functions with the same name but different parameter lists.
The compiler determines which function to call based on the arguments passed.

Why Use Function Overloading?
Code Clarity: Using the same name for closely related functions makes the code more readable and logical.
Improved Modularity: It avoids the need for creating multiple uniquely named functions that perform similar operations.
Ease of Maintenance: Changes or updates are easier to manage with overloaded function.

Rules for Function Overloading:
The function names must be the same.
The functions must differ in terms of:
Number of parameters.
Type of parameters.
Order of parameters.


#include <iostream>
using namespace std;
class Math {
public:
    // Function to add two integers
    int add(int a, int b) {
        return a + b;
    }
    // Function to add two doubles
    double add(double a, double b) {
        return a + b;
    }
    // Function to add three integers
    int add(int a, int b, int c) {
        return a + b + c;
    }
};
int main() {
    Math math;
    cout << "Sum of 5 and 10: " << math.add(5, 10) << endl;       // Calls the first add()
    cout << "Sum of 2.5 and 3.7: " << math.add(2.5, 3.7) << endl; // Calls the second add()
    cout << "Sum of 3, 4, and 5: " << math.add(3, 4, 5) << endl;  // Calls the third add()

    return 0;
}
Output:
Sum of 5 and 10: 15
Sum of 2.5 and 3.7: 6.2
Sum of 3, 4, and 5: 12

/*
NOTE: Constructors in C++ can also be overloaded in a similar way to functions.

#include <iostream>
using namespace std;

class Rectangle {
private:
    int length;
    int width;
public:
    // Default constructor (no parameters)
    Rectangle() {
        length = 0;
        width = 0;
        cout << "Default constructor called." << endl;
    }
    // Parameterized constructor with one parameter
    Rectangle(int l) {
        length = l;
        width = l; // Assuming square if only one side is provided
        cout << "Constructor with one parameter called." << endl;
    }
    // Parameterized constructor with two parameters
    Rectangle(int l, int w) {
        length = l;
        width = w;
        cout << "Constructor with two parameters called." << endl;
    }
    // A member function to display the rectangle's dimensions
    void display() {
        cout << "Length: " << length << ", Width: " << width << endl;
    }
};

int main() {
    // Creating objects using different constructors
    Rectangle r1;             // Calls the default constructor
    Rectangle r2(5);          // Calls the constructor with one parameter
    Rectangle r3(5, 10);      // Calls the constructor with two parameters

    // Display the rectangle dimensions
    cout << "Rectangle 1: ";
    r1.display();

    cout << "Rectangle 2: ";
    r2.display();

    cout << "Rectangle 3: ";
    r3.display();

    return 0;
}*/
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
(b) Operator Overloading:
   Operator overloading allows giving additional meanings to the operators when they are used with 
   user-defined data types (like objects).
For example, we can make use of the addition operator (+) for string class to concatenate two strings.
 We know that the task of this operator is to add two operands. 
 So a single operator ‘+’, when placed between integer operands, adds them and 
 when placed between string operands, concatenates them. 

Example of Operator Overloading:
#include <iostream>
using namespace std;
class Complex {
private:
    int real, imag;
public:
    Complex(int r = 0, int i = 0)
    {
        real = r;
        imag = i;
    }
    // This is automatically called
    // when '+' is used with between
    // two Complex objects
    Complex operator+(Complex const& obj)
    {
        Complex res;
        res.real = real + obj.real;
        res.imag = imag + obj.imag;
        return res;
    }
    void print() { cout << real << " + i" << imag << endl; }
};
int main(){
    Complex c1(10, 5), c2(2, 4);
    Complex c3 = c1 + c2; // An example call to "operator+"
    c3.print();
}
Output
12 + i9

/* 
#include <iostream>
using namespace std;

class Box {
private:
    int length;
    int breadth;
public:
    // Constructor to initialize length and breadth
    Box(int l = 0, int b = 0) : length(l), breadth(b) {}

    // Function to overload the '+' operator
    Box operator+(const Box& b) {
        Box temp;
        temp.length = length + b.length; 
        temp.breadth = breadth + b.breadth; 
        return temp; // Returning the result as a new object
    }

    // Function to display the dimensions of the box
    void display() {
        cout << "Length: " << length << ", Breadth: " << breadth << endl;
    }
};

int main() {
    Box box1(5, 10); // Create first box
    Box box2(3, 7);  // Create second box

    Box box3 = box1 + box2; // Add two boxes using overloaded '+' operator

    cout << "Box 1: ";
    box1.display(); // Display Box 1

    cout << "Box 2: ";
    box2.display(); // Display Box 2

    cout << "Resultant Box (Box1 + Box2): ";
    box3.display(); // Display the result of the addition

    return 0;
}

*/
#Difference between Operator Functions and Normal Functions
Operator functions are the same as normal functions. 
The only differences are, that the name of an operator function is always the operator keyword followed
by the symbol of the operator,and operator functions are called when the corresponding operator is used. 

Operators that can be overloaded           	Examples
Binary Arithmetic	                         +, -, *, /, %
Unary Arithmetic 	                         +, -, ++, —
Assignment                                   =, +=,*=, /=,-=, %=
Bitwise	                                     & , | , << , >> , ~ , ^

De-referencing	                               (->)
Dynamic memory allocation,

De-allocation                           	New, delete 
Subscript                                   	[ ]
Function call 	                                 ()
Logical 	                                &,  | |, !
Relational	                             >, < , = =, <=, >=

But, among them, there are some operators that cannot be overloaded. They are

1.Scope resolution operator (::)                           
2.Class member access operators i.e  *(pointer)  .(dot)
3.Conditional operator(?:)
4.Sizeof operator  sizeof()
5.typeid Operator
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#2. Run-Time Polymorphism:

Run-time polymorphism is achieved by using inheritance and function overriding.

a) Function Overriding:
Function overriding occurs when a derived class defines a function that already exists in the base class 
with the same signature.

#include <iostream>
using namespace std;
// Base class
class Animal {
public:
    virtual void sound() { // Use of virtual function to achieve run-time polymorphism
        cout << "Animal makes a sound" << endl;
    }
};
// Derived class 1
class Dog : public Animal {
public:
    void sound() override { // Overriding the base class method
        cout << "Dog barks" << endl;
    }
};
// Derived class 2
class Cat : public Animal {
public:
    void sound() override { // Overriding the base class method
        cout << "Cat meows" << endl;
    }
};
int main() {
    Animal *animal; // Pointer of type Animal

    Dog dog;
    Cat cat;

    animal = &dog;
    animal->sound(); // Calls Dog's version of sound()

    animal = &cat;
    animal->sound(); // Calls Cat's version of sound()

    return 0;
}
Output:
Dog barks
Cat meows
Explanation:
Virtual function: The sound() method in the Animal class is declared virtual, which allows dynamic binding.
Override: The Dog and Cat classes override the sound() method of the Animal class.
The function call is resolved at runtime based on the actual object (i.e., whether the object is Dog or Cat).

// C++ program for function overriding with data members
#include <bits/stdc++.h>
using namespace std;
//  base class declaration.
class Animal {
public:
    string color = "Black";
};
// inheriting Animal class.
class Dog : public Animal {
public:
    string color = "Grey";
};
int main(void)
{
    Animal d = Dog(); // accessing the field by reference
                      // variable which refers to derived
    cout << d.color;
}
Output:
Black
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#B. Virtual Function
A virtual function is a member function that is declared in the base class using the keyword virtual 
and is re-defined (Overridden) in the derived class.

Some Key Points About Virtual Functions:
1.Virtual functions are Dynamic in nature. 
2.They are defined by inserting the keyword “virtual” inside a base class 
   and are always declared with a base class and overridden in a child class
3. A virtual function is called during Runtime

#include <iostream>
using namespace std;
// Declaring a Base class
class GFG_Base {
public:
    // virtual function
    virtual void display()
    {
        cout << "Called virtual Base Class function"<< "\n\n";
    }
    void print()
    {
        cout << "Called GFG_Base print function"
             << "\n\n";
    }
};
// Declaring a Child Class
class GFG_Child : public GFG_Base {
public:
    void display()
    {
        cout << "Called GFG_Child Display Function"<< "\n\n";
    }
    void print()
    {
        cout << "Called GFG_Child print Function"<< "\n\n";
    }
};
int main()
{
    // Create a reference of class GFG_Base
    GFG_Base* base;
    GFG_Child child;
    base = &child;
    // This will call the virtual function
    base->display();
    // This will call the non-virtual function
    base->print();
}
Output:
Called GFG_Child Display Function
Called GFG_Base print function
// C++ program for virtual function overriding
#include <bits/stdc++.h>
using namespace std;
class base {
public:
    virtual void print()
    {
        cout << "print base class" << endl;
    }
    void show() { cout << "show base class" << endl; }
};
class derived : public base {
public:
    // print () is already virtual function in
    // derived class, we could also declared as
    // virtual void print () explicitly
    void print() { cout << "print derived class" << endl; }
    void show() { cout << "show derived class" << endl; }
};
// Driver code
int main()
{
    base* bptr;
    derived d;
    bptr = &d;
    // Virtual function, binded at
    // runtime (Runtime polymorphism)
    bptr->print();
    // Non-virtual function, binded
    // at compile time
    bptr->show();
    return 0;
}
Output:
print derived class
show base class

Key Points of Polymorphism:
Compile-time Polymorphism:
Function Overloading: Multiple functions with the same name but different argument lists.
Operator Overloading: Changing the functionality of operators for user-defined data types.

Run-time Polymorphism:
Function Overriding: Derived class redefines a base class function.
Virtual Functions: Enable function overriding by telling the compiler to bind the function call at runtime.