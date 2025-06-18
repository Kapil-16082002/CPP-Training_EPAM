✅#Abstraction:
It is the process of hiding the complex implementation details and showing only the essential or necessary information of an object. 

how does abstraction differ from encapsulation?

Aspect	                    Abstraction	                                    Encapsulation
Description	 Hiding implementation(logic) details.	          Hiding internal  data details and restricting direct access to certain parts of data using access control (e.g., private, protected).
Purpose	    Focuses on defining WHAT an object does, rather than HOW it does it.	Focuses on controlling HOW the internal behavior or data of an object is accessed or modified.
Goal	To provide a simplified interface for the user and hide unnecessary details of the implementation.	To restrict unauthorized access and protect the internal state of an object.

✅#Key Features of Abstraction:
1.Security: Users do not need to know the implementation details of a function or method.
2.Focus on Essentials: It allows the programmer to focus on what an object does rather than how it does it.

✅why use abstrct class??
1.Give Common Interface:
An abstract class is useful when you want to define a common interface (behavior) that all derived classes must implement. 
It ensures that all derived classes follow the same rules and provide their specific implementations for the required method(s)

2.Enabling Polymorphism
Supports runtime polymorphism by defining a base class pointer/reference to call overridden methods in derived classes.
Use Case: A Transport class with virtual void move() = 0; enables polymorphic behavior for derived classes like Car, Airplane, etc.

3.Providing code extensibility:
derived class must implement abstract class methods.


✅How Abstraction Works in C++:
1.Abstract Class: A class that cannot be instantiated and is meant to be inherited by other classes. 
It has at least one pure virtual function (a function with no definition and declared with = 0).
2.Pure Virtual Function: A virtual function that must be implemented by derived classes.

Example 1: Abstraction Using Abstract Class
In this example, we'll create an abstract class Shape with a pure virtual function area().
 The derived classes (Circle and Rectangle) must provide their own implementation for the area() function.
#include <iostream>
#include <cmath> // for M_PI constant
using namespace std;
// Abstract class (contains at least one pure virtual function)
class Shape {
public:
    // Pure virtual function providing interface framework
    virtual double area() = 0; // This is an abstract method
};
class Circle : public Shape {
private:
    double radius;
public:
    Circle(double r) : radius(r) {}
    // Implementing the pure virtual function
    double area() override {
        return M_PI * radius * radius;
    }
};
class Rectangle : public Shape {
private:
    double length;
    double width;
public:
    Rectangle(double l, double w) : length(l), width(w) {}
    // Implementing the pure virtual function
    double area() override {
        return length * width;
    }
};
int main() {
    Shape *shape1 = new Circle(5.0);      // Creating an object of Circle
    Shape *shape2 = new Rectangle(4.0, 5.0); // Creating an object of Rectangle

    cout << "Area of Circle: " << shape1->area() << endl;    // Output: 78.5398
    cout << "Area of Rectangle: " << shape2->area() << endl; // Output: 20
    // Cleanup
    delete shape1;
    delete shape2;

    return 0;
}
Output:
Area of Circle: 78.5398
Area of Rectangle: 20
Explanation:
The class Shape is an abstract class because it has the pure virtual function area().
The derived classes (Circle and Rectangle) implement the area() function.
We don't need to know how the area is calculated in each shape; we just call the area() function and get the result.
 This is the essence of abstraction — showing only the necessary details.

1.Instead of using Shape* shape1 = new Triangle(...);, we simply create instances of Triangle and Square directly
 using Triangle triangle(...); and Square square(...);.
2.Calling Methods Without Pointers:
Since the objects are not created with pointers, we do not need to use the arrow operator (->). We can directly call the method using the dot operator (.), like triangle.area() and square.area().
3.Automatic Memory Management:
Since we're not using dynamic memory allocation (new), we do not need to manually delete the objects. 
Memory will be automatically managed, and the objects will be destroyed when they go out of scope (at the end of the main function).
 /*  Implementation of above code-> Object wihtout using pointer 
#include <iostream>
#include <cmath> // for M_PI constant
using namespace std;

// Abstract class (contains at least one pure virtual function)
class Shape {
public:
    // Pure virtual function providing interface framework
    virtual double area() = 0; // This is an abstract method
};
class Circle : public Shape {
private:
    double radius;
public:
    Circle(double r) : radius(r) {}
    // Implementing the pure virtual function
    double area() override {
        return M_PI * radius * radius;
    }
};
class Rectangle : public Shape {
private:
    double length;
    double width;
public:
    Rectangle(double l, double w) : length(l), width(w) {}
    // Implementing the pure virtual function
    double area() override {
        return length * width;
    }
};
int main() {
    // Creating objects directly (no pointers, no dynamic allocation)
    Circle circle(5.0);             // Circle object with radius 5.0
    Rectangle rectangle(4.0, 5.0);  // Rectangle object with length 4.0 and width 5.0

    // Calculating and displaying the area using dot operator
    cout << "Area of Circle: " << circle.area() << endl;      // Output: 78.5398
    cout << "Area of Rectangle: " << rectangle.area() << endl; // Output: 20

    return 0;
}
*/
// C++ Program to Demonstrate the
// working of Abstraction
#include <iostream>
using namespace std;

class implementAbstraction {
private:
    int a, b;
public:
    // method to set values of
    // private members
    void set(int x, int y)
    {
        a = x;
        b = y;
    }
    void display()
    {
        cout << "a = " << a << endl;
        cout << "b = " << b << endl;
    }
};
int main()
{
    implementAbstraction obj;
    obj.set(10, 20);
    obj.display();
    return 0;
}
Output:
a = 10
b = 20

Advantages of Data Abstraction:
1.Avoids code duplication and increases reusability.
2.Can change the internal implementation of the class independently without affecting the user.
3.Helps to increase the security of an application or program as only important details are provided to the user.
4.It reduces the complexity as well as the redundancy of the code, therefore increasing the readability.
7.New features or changes can be added to the system with minimal impact on existing code.