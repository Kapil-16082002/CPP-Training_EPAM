
✅Liskov Substitution Principle (LSP):
Objects of a superclass should be replaceable with objects of a subclass without changing the correctness of the program.

✅Objects of a superclass should be replaceable with objects of their subclass??
it means: objects of their subclass can maintain superclass members.
Subclass inherits all behaviors of the superclass:


✅Why is LSP Important?
Improves Code Reusability: Derived classes can be substituted wherever a base class is expected, reducing redundancy.
Enhances Code Maintainability: Code that depends on abstractions (e.g., base classes) works seamlessly with new derived types.
Promotes Polymorphism: Allows polymorphic behavior without violating program correctness.


Example of LSP Violation
/*A rectangle is a shape.A square is also a rectangle, but if you replace a rectangle with a square, 
certain calculations(like area) might behave unexpectedly if assumptions about width / height change.*/

#include <iostream>
#include <string>
// Base class
class Rectangle {
protected:
    float length;
    float width;
public:
    Rectangle(float l, float w) : length(l), width(w) {}

    virtual void setLength(float l) {
        length = l;
    }
    virtual void setWidth(float w) {
        width = w;
    }
    virtual float getArea() const {
        return length * width;
    }
};
// Derived class
class Square : public Rectangle {
public:
    Square(float side) : Rectangle(side, side) {}

    // Overrides base class methods but violates the behavior contract
    void setLength(float l) override {
        length = l;
        width = l; // Square requires length == width
    }
    void setWidth(float w) override {
        length = w;
        width = w; // Square requires length == width
    }
};
int main() {
    // Example of violation of LSP
    Rectangle* rect = new Square(5); // Use a Square where a Rectangle is expected

    rect->setLength(10);             // Modifies only the length in the Rectangle context
    std::cout << "Area: " << rect->getArea() << std::endl; // Unexpected behavior!

    delete rect;
    return 0;
}

✅Step-by-Step Explanation of Violation
Step 1: Rectangle* rect = new Square(5);
A Square object is created, and the Rectangle* pointer rect points to it.
Initial values for the Square object:

length = 5
width = 5

Step 2: rect->setLength(10);
rect is a Rectangle*, so the program assumes it obeys the Rectangle behavior.
However, since rect actually points to a Square (polymorphic behavior), the overridden method Square::setLength is executed.
What happens inside Square::setLength:
Both length and width are set to 10:

length = 10;
width = 10;
This breaks the expectation of the Rectangle interface that setLength modifies only the length.
From the perspective of a Rectangle, width should remain unchanged, but in this case, width has also been modified unexpectedly.

Step 3: std::cout << "Area: " << rect->getArea() << std::endl;
The program calls Rectangle::getArea, which calculates the area using:
return length * width;

✅Expected Behavior for a Rectangle:
After calling setLength(10), the program assumes:
length = 10
width = 5  // Unchanged
area = 10 * 5 = 50


⚠️Actual Behavior (due to Square overriding behavior):
Both length and width are 10, so:
area = 10 * 10 = 100
Unexpected Behavior: The program expects the area to be 50, but it is actually 100 because the Square class violated the behavioral contract of Rectangle.

//-----------------------------------------------------------------------------------------------------------------

✅Compliant Example (Fixing the Violation)
To comply with LSP, we need to acknowledge that a Square is not a true subtype of Rectangle because their behaviors are fundamentally different. 
Instead, we can design Square as a separate class that does not derive from Rectangle but still adheres to a common base class Shape.

#include <iostream>
#include <string>
#include <vector>
#include <memory>

// Abstract Base Class
class Shape {
public:
    virtual float getArea() const = 0; // Pure virtual function
    virtual ~Shape() {}
};

// Rectangle Class
class Rectangle : public Shape {
protected:
    float length;
    float width;
public:
    Rectangle(float l, float w) : length(l), width(w) {}

    void setLength(float l) {
        length = l;
    }
    void setWidth(float w) {
        width = w;
    }
    float getArea() const override {
        return length * width;
    }
};
// Square Class (Separate from Rectangle)
class Square : public Shape {
private:
    float side;
public:
    Square(float s) : side(s) {}
    void setSide(float s) {
        side = s;
    }
    float getArea() const override {
        return side * side;
    }
};
int main() {
    // A vector of shapes using polymorphism
    std::vector<std::shared_ptr<Shape>> shapes;

    // Add different shapes
    shapes.push_back(std::make_shared<Rectangle>(10, 20));
    shapes.push_back(std::make_shared<Square>(15));

    // Calculate and print the area of all shapes
    for (const auto& shape : shapes) {
        std::cout << "Area: " << shape->getArea() << std::endl;
    }
    return 0;
}
✅How LSP Applies in the Code

1.Objects of Rectangle and Square are Replaced by Shape References:

std::vector<std::shared_ptr<Shape>> shapes; // A collection of Shape pointers (base class)
shapes.push_back(std::make_shared<Rectangle>(10, 20)); // Derived class Rectangle stored as Shape
shapes.push_back(std::make_shared<Square>(15));       // Derived class Square stored as Shape
The vector std::vector<std::shared_ptr<Shape>> stores derived class objects (Rectangle and Square) but refers to them through the common base class Shape.
This demonstrates that subclasses can replace the base class without causing issues (a core idea of LSP).

2.Polymorphism in Action:

for (const auto& it : shapes) {
    std::cout << "Area: " <<it->getArea() << std::endl; // Calls correct implementation
}
This loop calls the getArea() method from the Shape interface.
However, based on the actual object type being pointed to (Rectangle or Square), the correct implementation of getArea() is called at runtime.
The program functionality does not break, as each subtype maintains the expected behavior of the Shape interface.