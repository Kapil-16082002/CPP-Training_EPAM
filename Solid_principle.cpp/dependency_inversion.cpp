✅Dependency Inversion Principle:
High-level modules should not depend on low-level modules. Both should depend on abstractions.
And:
Abstractions should not depend on details. Details should depend on abstractions.
In simple ternms, class should rely on abstractions(e.g abstract classes or interfaces ) rather than concrete implementations.


✅Without Dependency Inversion (DIP Violation)
In this example, AreaCalculator (the high-level module) directly depends on low-level classes (Square and Rectangle). This violates DIP because:

The AreaCalculator logic is tightly coupled to the specific shape implementations.
Adding a new shape or changing implementations will require modifying AreaCalculator.

#include <iostream>

// Low-level module: Rectangle
class Rectangle {
private:
    double width, height;
public:
    Rectangle(double width, double height) : width(width), height(height) {}
    double getArea() const {
        return width * height; // Rectangle-specific area calculation
    }
};

// Low-level module: Square
class Square {
private:
    double side;
public:
    Square(double side) : side(side) {}
    double getArea() const {
        return side * side; // Square-specific area calculation
    }
};

// High-level module: Directly depends on Rectangle and Square
class AreaCalculator {
public:
    double calculateRectangleArea(Rectangle& rectangle) {
        return rectangle.getArea();
    }

    double calculateSquareArea(Square& square) {
        return square.getArea();
    }
};

int main() {
    Rectangle rectangle(5.0, 10.0);
    Square square(4.0);

    AreaCalculator calculator;
    std::cout << "Rectangle area: " << calculator.calculateRectangleArea(rectangle) << std::endl;
    std::cout << "Square area: " << calculator.calculateSquareArea(square) << std::endl;

    return 0;
}
Output:
Rectangle area: 50
Square area: 16

✅Whats wrong here?
1.Violation of DIP:
AreaCalculator directly depends on specific classes (Rectangle, Square) instead of an abstraction. 
If a new shape is added (e.g., Circle), the AreaCalculator would need to change, violating the Open/Closed Principle (OCP).
2.Tight Coupling:
The AreaCalculator class cannot work with other shapes unless explicitly modified for each new shape. 
This makes the program inflexible and hard to extend.


✅With Dependency Inversion Principle
To fix the design, we'll:

Introduce an abstraction (Shape) that defines a common contract (getArea()) for all shapes.
Make both Rectangle and Square inherit from the Shape abstraction.
Modify the AreaCalculator to depend on Shape, making it operate on any shape rather than specific implementations.
Code with DIP
cpp


#include <iostream>
#include <vector>
#include <memory>

// Abstraction: Shape interface (high-level and low-level depend on this)
class Shape {
public:
    virtual ~Shape() = default; // Virtual destructor is necessary for polymorphism
    virtual double getArea() const = 0; // Pure virtual method for area calculation
};

// Low-level module: Rectangle implementing Shape
class Rectangle : public Shape {
public:
    Rectangle(double width, double height) : width(width), height(height) {}
    double getArea() const override {
        return width * height; // Rectangle-specific area calculation
    }
};
// Low-level module: Square implementing Shape
class Square : public Shape {
private:
    double side;
public:
    Square(double side) : side(side) {}
    double getArea() const override {
        return side * side; // Square-specific area calculation
    }
};

// High-level module: Depends on Shape abstraction, not concrete classes
class AreaCalculator {
public:
    double calculateTotalArea(const std::vector<std::shared_ptr<Shape>>& shapes) const {
        double totalArea = 0.0;
        for (const auto& shape : shapes) {
            totalArea += shape->getArea(); // Work with Shape abstraction
        }
        return totalArea;
    }
};

int main() {
    // Create shapes
    std::shared_ptr<Shape> rectangle = std::make_shared<Rectangle>(5.0, 10.0);
    std::shared_ptr<Shape> square = std::make_shared<Square>(4.0);

    // Store shapes in a vector (Shape abstraction)
    std::vector<std::shared_ptr<Shape>> shapes = {rectangle, square};

    // High-level module
    AreaCalculator calculator;
    std::cout << "Total area: " << calculator.calculateTotalArea(shapes) << std::endl;

    return 0;
}
Output:
Total area: 66
Explanation
Abstraction Introduced:

Shape is an abstract base class that defines the contract (getArea()) to calculate the area. 
All shapes (Rectangle and Square) implement this interface, ensuring polymorphism.

1.High-level Module Decoupled:
The AreaCalculator now depends on the Shape abstraction and operates on a set of Shape objects. 
It no longer depends directly on Rectangle, Square, or any other specific shape.

2.Flexible and Scalable:
Adding a new shape (e.g., Circle, Triangle) requires just implementing the Shape interface. No changes are needed in the AreaCalculator.
Adding a New Shape (Circle)
If we want to add support for Circle, we just need to implement the Shape interface. The rest of the code remains unchanged.

// Low-level module: Circle implementing Shape
class Circle : public Shape {
public:
    Circle(double radius) : radius(radius) {}
    double getArea() const override {
        return 3.14159 * radius * radius; // Circle-specific area calculation
    }

private:
    double radius;
};

int main() {
    // Create shapes
    std::shared_ptr<Shape> rectangle = std::make_shared<Rectangle>(5.0, 10.0);
    std::shared_ptr<Shape> square = std::make_shared<Square>(4.0);
    std::shared_ptr<Shape> circle = std::make_shared<Circle>(3.0);

    // Store shapes in a vector (Shape abstraction)
    std::vector<std::shared_ptr<Shape>> shapes = {rectangle, square, circle};

    // High-level module
    AreaCalculator calculator;
    std::cout << "Total area: " << calculator.calculateTotalArea(shapes) << std::endl;

    return 0;
}
Output:
Total area: 94.27431
