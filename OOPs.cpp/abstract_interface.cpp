Abstract Class:
Can have both pure virtual functions (like an interface) and non-pure (regular) virtual functions with default implementations.
Can also have member variables and shared code that subclasses can inherit.
Used when you want to enforce certain shared behavior along with a common interface.

Interface (Pure Abstract Class):
Contains only pure virtual functions (no implementation or state variables are allowed).
Derived class must implement all the methods of base class.
Used when all you need is a contract or protocol for communication without any behavior or implementation.



✅Abstract Base Class and Pure Virtual Functions
A virtual function can be made a pure virtual function by assigning = 0. 
This makes the class abstract, meaning it cannot be instantiated directly:

class AbstractClass {
    public:
        virtual void pureVirtual() = 0;  // Pure virtual function
    };
Derived classes must override all pure virtual functions to be instantiable.



✅Virtual Destructors
If a class has virtual functions, it is generally a good idea to make its destructor virtual. 
This avoids undefined behavior when deleting derived class objects via a base class pointer:

class Base {
public:
    virtual ~Base() { std::cout << "Base destructor" << std::endl; }
};
class Derived : public Base {
public:
    ~Derived() { std::cout << "Derived destructor" << std::endl; }
};
int main() {
    Base* obj = new Derived();
    delete obj;
    // Output:
    // Derived destructor
    // Base destructor
}.

Note:
final: Indicates that a virtual function cannot be overridden in derived classes.
virtual void display() final;




✅Syntax of Virtual Functions:
To declare a virtual function in a base class, use the virtual keyword before the function definition:

class Base {
public:
    virtual void display() { 
        std::cout << "Base display function" << std::endl;
    }
};
class Derived : public Base {
public:
    void display() override {  
        std::cout << "Derived display function" << std::endl;
    }
};
int main() {
    Base* obj = new Derived();
    obj->display();  // Output: "Derived display function"
}

//----------------------------------------------------------------------------------------------------------------

✅When to Use an Abstract Class:
You want to provide default implementations for some methods.
You want to share data or behavior between derived classes.
You want the ability to store state (member variables) or other common data.
A class hierarchy makes sense and there's a "parent-child" relationship.

Abstract Class Example
Here, we use an abstract class because we provide some default behavior.
#include <iostream>
#include <string>

// Abstract base class
class Animal {
public:
    virtual void makeSound() = 0; // Pure virtual function (must be implemented by derived classes)
    // Default implementation for common behavior
    void eat() {
        std::cout << "This animal is eating." << std::endl;
    }
    virtual ~Animal() = default; // Virtual destructor for proper cleanup
};
// Derived class implementing specific behavior
class Dog : public Animal {
public:
    void makeSound() override {
        std::cout << "Dog barks" << std::endl;
    }
};
// Derived class implementing specific behavior
class Cat : public Animal {
public:
    void makeSound() override {
        std::cout << "Cat meows" << std::endl;
    }
};

int main() {
    Animal* dog = new Dog();
    dog->makeSound();
    dog->eat(); // Reuses the default implementation

    Animal* cat = new Cat();
    cat->makeSound();
    cat->eat(); // Reuses the default implementation

    delete dog;
    delete cat;

    return 0;
}
Output:
Dog barks
This animal is eating.
Cat meows
This animal is eating.
Here, the eat() method is part of the shared behavior provided by the Animal class, 
so it makes sense to use an abstract class that both Dog and Cat can inherit from.

//-----------------------------------------------------------------------------------------------------------------

✅Use an Interface (Pure Abstract Class) When:
You don't need to provide any implementation—you only want the method signatures (definitions).
You don't need want to share data or behavior between derived classes.

#include <iostream>
// Pure abstract class (interface)
class Drawable {
public:
    virtual void draw() const = 0; // Pure virtual function (must be implemented)
    virtual ~Drawable() = default; // Virtual destructor
};
// Derived class implementing the contract
class Circle : public Drawable {
public:
    void draw() const override {
        std::cout << "Drawing a Circle." << std::endl;
    }
};
// Derived class implementing the contract
class Rectangle : public Drawable {
public:
    void draw() const override {
        std::cout << "Drawing a Rectangle." << std::endl;
    }
};
int main() {
    Drawable* circle = new Circle();
    Drawable* rectangle = new Rectangle();

    circle->draw();     // Circle must implement draw()
    rectangle->draw();  // Rectangle must implement draw()

    delete circle;
    delete rectangle;

    return 0;
}
//=================================================================================================================

✅can we have pure virtual function outside class?
we can define a pure virtual function outside the class, BUT only its definition, not the “pure = 0 part”.
👉 The pure part must be inside the class.
👉 The definition (body) can be outside.
#include <iostream>
using namespace std;

class Shape {
public:
    virtual void draw() = 0;  // pure virtual function
};
// Definition of pure virtual function outside class
void Shape::draw() {
    cout << "Shape default draw()" << endl;
}
class Circle : public Shape {
public:
    void draw() override {
        cout << "Circle Draw" << endl;
    }
};
int main() {
    Shape *s = new Circle();
    s->draw();   // Calls Circle::draw()
    return 0;
}
