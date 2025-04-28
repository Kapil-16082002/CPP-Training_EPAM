
O - Open/Closed Principle (OCP):
Software entities (classes, modules, functions) should be open for extension but closed for modification.
Example: When adding new functionality, instead of modifying existing code, you can create new classes or methods that extend existing behavior.

This means:
Open for extension:    Adding new functionality to the class/module without changing its existing code.
Closed for modification: You should not modify the existing code to avoid introducing bugs into the system.
The idea is to design your system in such a way that it’s easy to extend with new features without altering existing functionality. 
This is often achieved using abstraction, polymorphism, and interfaces.

✅Benefits of OCP:
Improved Maintainability: Reduces the risk of introducing errors into existing functionality.
Enhances Extensibility: New features or behaviors can be added without requiring modifications to the already tested code.
Promotes Reusability: Existing code remains reusable without the need for changes.

Anti-OCP Example (Code That Violates OCP)
#include <iostream>
#include <vector>
#include <typeinfo>

class Rectangle {
public:
    float length;
    float width;

    Rectangle(float l, float w) : length(l), width(w) {}
};
class Circle {
public:
    float radius;

    Circle(float r) : radius(r) {}
};
class AreaCalculator {
public:
    float calculateArea(const std::vector<void*>& shapes) {
        float totalArea = 0;
        
        for (const auto& shape : shapes) {//shape is a void* pointer, which can point to any arbitrary object in memory (in this case, either a Rectangle or a Circle)  but doesn’t itself contain any type information.
            
            if (typeid(*((Rectangle*)shape)) == typeid(Rectangle)) {// If true, this indicates that the object being pointed to by shape is actually a Rectangle.
                auto* rectangle = (Rectangle*)shape;
                totalArea += rectangle->length * rectangle->width;
                /* 
        (Rectangle*)shape ->This code casts shape to Rectangle*.This is a reinterpret cast, forcing the void* pointer into the type Rectangle*
        *((Rectangle*)shape)-> This code dereferences this casted pointer: Dereferencing retrieves the underlying Rectangle object (or accesses it incorrectly if the cast is invalid)
         typeid(*((Rectangle*)shape)) -> It uses the typeid operator to get the runtime type information of the dereferenced object.
        */
            } 
            else if (typeid(*((Circle*)shape)) == typeid(Circle)) {
                auto* circle = (Circle*)shape;
                totalArea += 3.14 * circle->radius * circle->radius;
            }
        }

        return totalArea;
    }
};

int main() {
    Rectangle rectangle(10, 20);
    Circle circle(10);

    std::vector<void*> shapes = {&rectangle, &circle};

    AreaCalculator calculator;
    std::cout << "Total Area: " << calculator.calculateArea(shapes) << std::endl;

    return 0;
}
What’s wrong with the above code?
Violation of OCP:
1.If we add a new shape (e.g., Triangle), we would need to modify the AreaCalculator class to add additional if-else conditions.

2.Tight Coupling:
The AreaCalculator logic is tied to specific shape types. Adding a new shape requires knowing its type and extending the logic.

3.Hard to Maintain:
Adding new shapes significantly increases the complexity and fragility of the code.

/* 
vector<void*> is a container that stores pointers of type void*, means the pointers in this vector can point to objects of any type (e.g., pointers to a Rectangle, a Circle, or any other object).
The objects stored in this vector (via their addresses) are the actual shapes (Rectangle and Circle) that you have created in your main() function.


Rectangle rectangle(10, 20);
Circle circle(10);
std::vector<void*> shapes = {&rectangle, &circle};

shapes[0] holds the memory address of the rectangle object (void* pointing to the rectangle object).
shapes[1] holds the memory address of the circle object (void* pointing to the circle object).

since std::vector<void*> is a container for raw pointers (void*), the compiler does not know the actual types of the objects being pointed to. 
You lose type information when you store an object’s address as a void*.

When you want to use the objects, you need to cast the void* pointer back to the original type. For example:
Rectangle* rect = (Rectangle*)shapes[0];
Circle* circ = (Circle*)shapes[1];
These casts tell the compiler the actual type of objects being pointed to by the pointers.

Without casting, you cannot directly access the object’s members because void* does not store any type information.


Why Is It Problematic?
Using std::vector<void*> works, but it introduces several problems:

1. Safety:
The major problem is that void* pointers are type-unsafe. The compiler cannot verify that you're casting the void* back to the correct type. If you accidentally cast to the wrong type, behavior is undefined and may lead to crashes or corruption.

Example:
Rectangle rectangle(10, 20);
Circle circle(10);
// Create vector and assign void pointers
std::vector<void*> shapes = {&rectangle, &circle};

// Cast void* back to the wrong type (unsafe)
Rectangle* rect = (Rectangle*)shapes[1]; // Casting Circle as Rectangle
std::cout << "Rectangle Area: " << rect->length * rect->width << std::endl;
This code will likely crash or produce incorrect results because shapes[1] is not a Rectangle.

2. Code Complexity:
Using void* requires manual casting and type checking (e.g., through typeid or dynamic_cast) to ensure you're accessing the correct type of object, as seen in your original code. This approach is complex and error-prone.

3. Losing Type Information:
When you use void*, the type of the object is completely lost. This causes you to depend on external means (like typeid or other type markers) to determine the type at runtime, which violates the principles of modern, type-safe C++ programming.
*/

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/* 
Problem: if shape is not actually rectangle object but circle object and do like  if (typeid(*((Rectangle*)shape)) == typeid(Rectangle))
when you try to cast a Circle to a Rectangle*:

1. Undefined Behavior During Casting
The cast (Rectangle*)shape:

Does not verify that shape actually points to a Rectangle.
It trusts the programmer and blindly reinterprets the bytes at the memory address stored in shape as a Rectangle.
If shape really points to a Circle, then:

The memory layout of Circle is interpreted incorrectly as if it's a Rectangle.
Accessing the members (length, width) of this incorrectly casted object leads to undefined behavior, because those fields don’t exist in Circle.
2. Invalid Dereferencing
The line *((Rectangle*)shape) dereferences the pointer after the invalid cast:

This attempts to access the memory incorrectly, assuming the memory structure corresponds to a Rectangle.
Since the actual memory layout is that of Circle, the dereferencing operation may:
Access garbage values (because the fields expected by Rectangle are not present in Circle).
Cause segmentation faults or crashes if the access violates memory bounds.
Example of a Potential Problem:
If Circle has only one member (radius), but Rectangle expects two members (length and width), reading those nonexistent length or width members from the memory of a Circle will result in garbage values or runtime crashes.

What You Should Do
The proper way to handle mixed types in a std::vector is to avoid raw void* altogether and use either:

Polymorphism with a base class (Shape) containing a virtual method for area().
Each derived class (Rectangle, Circle) implements area().
You store pointers (Shape*) safely without manual type-checking and casting.
Modern Alternatives like std::variant, which allows type-safe storage of multiple types in a container.


*/

OCP-Compliant Refactored Code
To follow the Open/Closed Principle, we can refactor the code by introducing abstraction and polymorphism.

Step-by-step Refactoring:
Define a common interface or abstract class for shapes.
Let each shape implement its own area computation logic.
Use abstraction to decouple AreaCalculator from specific shape types.
Here’s the refactored code that adheres to OCP:


#include <iostream>
#include <vector>
#include <memory> // For smart pointers

// Abstract Base Class representing a Shape
class Shape {
public:
    // Pure virtual method for calculating area
    virtual float calculateArea() const = 0;

    // Virtual destructor for safe deletion of derived objects
    virtual ~Shape() {}
};

// Rectangle class implementing Shape
class Rectangle : public Shape {
private:
    float length;
    float width;
public:
    Rectangle(float l, float w) : length(l), width(w) {}

    float calculateArea() const override {
        return length * width;
    }
};
// Circle class implementing Shape
class Circle : public Shape {
private:
    float radius;
public:
    Circle(float r) : radius(r) {}

    float calculateArea() const override {
        return 3.14 * radius * radius;
    }
};
// New shape: Triangle (can be added without modifying existing code)
class Triangle : public Shape {
private:
    float base;
    float height;
public:
    Triangle(float b, float h) : base(b), height(h) {}

    float calculateArea() const override {
        return 0.5 * base * height;
    }
};
// AreaCalculator class (open for extension, closed for modification)
class AreaCalculator {
public:
    float calculateTotalArea(const std::vector<std::shared_ptr<Shape>>& shapes) const {
        float totalArea = 0;

        for (const auto& shape : shapes) {
            totalArea += shape->calculateArea(); // Polymorphism in action
        }
        return totalArea;
    }
};
int main() {
    // Create shapes
    auto rectangle = std::make_shared<Rectangle>(10, 20);// This line creates an object of type Rectangle on the heap using std::make_shared, and stores it in a smart pointer (std::shared_ptr) named rectangle
    auto circle = std::make_shared<Circle>(10);
    auto triangle = std::make_shared<Triangle>(10, 5);

    // Store shapes in a vector (using polymorphism)
    std::vector<std::shared_ptr<Shape>> shapes = {rectangle, circle, triangle};

    // Use the AreaCalculator to calculate the total area
    AreaCalculator calculator;
    std::cout << "Total Area: " << calculator.calculateTotalArea(shapes) << std::endl;

    return 0;
}
✅How Does the Refactored Code Follow OCP?
1.Open for Extension:
To add a new shape (e.g., Square), all we need to do is create a new class (Square) derived from the Shape interface. We don't modify AreaCalculator or its existing logic.
This makes the code easily extensible.

2.Closed for Modification:
The AreaCalculator class and the existing shape classes (Rectangle, Circle) remain unchanged when new shapes are introduced.
This reduces the risk of breaking existing functionality when adding new features.

3.Polymorphism:
The AreaCalculator expects a vector of Shape pointers. It calls the calculateArea() method polymorphically without needing to know the specific type of shape.

4.Reusable and Maintainable:
Each shape encapsulates its own area-calculation logic. This makes the code modular and easier to test.

✅Benefits of the OCP-Compliant Code
Extensibility: Adding new shapes does not require modifying existing tested code.
Scalability: Works well as the application grows and more shapes are added.
Reusability: The AreaCalculator can calculate areas for any shape (existing or future) as long as they inherit from Shape.

✅Key Takeaways
By using abstraction (interface) and polymorphism, the code adheres to the Open/Closed Principle.
Decoupling the AreaCalculator from specific shape implementations ensures flexibility and extensibility.
Applying OCP results in clean, modular, and maintainable code.
