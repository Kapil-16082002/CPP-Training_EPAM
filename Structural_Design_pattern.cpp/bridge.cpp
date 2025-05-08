
🧠Bridge Method Design Pattern:
The Bridge Design Pattern is a structural design pattern that separates an abstraction (what an object does) from its implementation (how it does it). 
This separation is achieved by placing them in different class hierarchies and connecting them using a bridge (an interface or composition).

✅When to Use the Bridge Design Pattern:
When you have multiple hierarchies (e.g., an abstraction hierarchy and an implementation hierarchy) that must work together.
When inheritance isn't ideal, as it tightly couples different hierarchies.
When abstraction and implementation should work independently—you don't want changes in one hierarchy affecting the other hierarchy.

✅Key Concepts in Bridge Design Pattern:
Abstraction:
Represents the high-level interface.  //Shapes (Circle, Rectangle) are the abstraction.
Depends on the abstract implementation part.

Implementor:
Represents the interface of the implementation.      //Colors (Red, Blue) are the implementation.
Various concrete implementations implement this interface.

Refined Abstraction:
Extends the abstraction and adds more functionality.

Concrete Implementor:
Implements the implementor interface to provide specific behavior.

//--------------------------------------------------------------------------------------------------------------

✅Example Scenario: Shapes and Colors
Imagine you need to represent different shapes (like Circle and Rectangle) that can have different colors (like Red and Blue). 
The Shape class hierarchy represents the abstraction, and the Color interface represents the implementor.

A Bridge Pattern works well here:
Shapes (Circle, Rectangle) are the abstraction.
Colors (Red, Blue) are the implementation.
The abstraction and implementation communicate via the bridge.

#include <iostream>
#include <string>
using namespace std;
// Implementor: Interface for Color Implementations
// This interface defines the behavior (functionality) that all Concrete Implementors (Colors) must provide.
// It allows the abstraction (Shape) to invoke behavior without knowing the specific implementation details of the color.
class Color {
public:
    virtual void applyColor() const = 0;  // Apply the color
    virtual ~Color() {}
};
// Concrete Implementors: Specific Colors
// Concrete Implementor: Red Color
// Implements the Color interface and provides the behavior to apply the "Red" color.
class Red : public Color {
public:
    void applyColor() const override {
        cout << "Applying Red Color." << endl;
    }
};
// Concrete Implementor: Blue Color
// Implements the Color interface and provides the behavior
// to apply the "Blue" color.
class Blue : public Color {
public:
    void applyColor() const override {
        cout << "Applying Blue Color." << endl;
    }
};
// Abstraction: Shape Interface
// The Abstraction defines a high-level interface that is independent of the underlying implementor (Color). 
// It works with the implementor using composition (has-a relationship via a reference to the Color interface).
// The Abstraction is decoupled from the Concrete Implementors,which are injected into it at runtime.
class Shape {
protected:
    Color* color;  // Stores a reference to the Color Implementor
public:
    // Constructor initializes the Shape with a specific Color Implementor
    Shape(Color* c) : color(c) {}

    virtual void draw() const = 0;  // Draw the shape (abstract method)
    virtual ~Shape() {}
};
// Refined Abstraction: Circle
// This is a concrete implementation of the Shape abstraction.
// It adds more specific behavior (drawing a circle),while delegating the color application to the underlying color implementor.
class Circle : public Shape {
public:
    // Pass the Color Implementor to the constructor
    Circle(Color* c) : Shape(c) {}

    void draw() const override {
        cout << "Drawing Circle." << endl;
        color->applyColor();  // Delegate color application to the implementor
    }
};
// Refined Abstraction: Rectangle
// This is another concrete implementation of the Shape abstraction.
// It adds specific behavior (drawing a rectangle),while relying on the implementor for color application.
class Rectangle : public Shape {
public:
    // Pass the Color Implementor to the constructor
    Rectangle(Color* c) : Shape(c) {}

    void draw() const override {
        cout << "Drawing Rectangle." << endl;
        color->applyColor();  // Delegate color application to the implementor
    }
};
// Client Code
// -----------------------------------------------
// The client interacts only with the high-level Abstraction (Shape).
// It doesn't know or care about the specific implementors (Color) or how the color is applied to the shapes.
// By using composition, the client can mix and match different Shapes and Colors dynamically at runtime.

int main() {
    // Create Color Implementors
    Color* red = new Red();  // Red color implementor
    Color* blue = new Blue();  // Blue color implementor

    // Create Shape objects with specific colors
    Shape* redCircle = new Circle(red);      // Circle with Red color
    Shape* blueRectangle = new Rectangle(blue); // Rectangle with Blue color

    // Draw the shapes
    // The Abstraction (Shape) delegates the "color application"
    // responsibility to the Implementor (Color).
    redCircle->draw();
    blueRectangle->draw();

    delete redCircle;      // This also destroys the associated Red implementor
    delete blueRectangle;  // This also destroys the associated Blue implementor
    delete red;            // Destroy Red color
    delete blue;           // Destroy Blue color

    return 0;
}


