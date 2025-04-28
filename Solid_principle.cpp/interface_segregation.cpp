Interface Segregation Principle:
A client should not be forced to depend on methods it does not use.
/*"Classes should not be forced to implement  unnecessarily / irrelevant methods that they do not use.*/
// Main aim removing fat interfaces

⚠️Example of ISP Violation
Here is  an example where the Interface Segregation Principle is violated:
#include <iostream>
#include <string>

// Fat Interface (Violates ISP)
class Vehicle {
public:
    virtual void drive() = 0;
    virtual void fly() = 0;
    virtual void sail() = 0;
    virtual ~Vehicle() {}
};
// Car class
class Car : public Vehicle {
public:
    void drive() override {
        std::cout << "Car is driving!" << std::endl;
    }
    void fly() override {
        // Car cannot fly!
        std::cout << "Car cannot fly!" << std::endl;
    }
    void sail() override {
        // Car cannot sail!
        std::cout << "Car cannot sail!" << std::endl;
    }
};
// Airplane class
class Airplane : public Vehicle {
public:
    void drive() override {
        // Airplane does not drive!
        std::cout << "Airplane cannot drive!" << std::endl;
    }
    void fly() override {
        std::cout << "Airplane is flying!" << std::endl;
    }
    void sail() override {
        // Airplane does not sail!
        std::cout << "Airplane cannot sail!" << std::endl;
    }
};

// Boat class
class Boat : public Vehicle {
public:
    void drive() override {
        // Boat does not drive!
        std::cout << "Boat cannot drive!" << std::endl;
    }
    void fly() override {
        // Boat does not fly!
        std::cout << "Boat cannot fly!" << std::endl;
    }
    void sail() override {
        std::cout << "Boat is sailing!" << std::endl;
    }
};
int main() {
    Vehicle* car = new Car();
    car->drive();
    car->fly();
    car->sail();

    delete car;

    Vehicle* airplane = new Airplane();
    airplane->fly();
    airplane->drive();
    airplane->sail();

    delete airplane;

    return 0;
}
What Goes Wrong in the Above Code?
1.Fat Interface:
The Vehicle interface includes unrelated methods (drive(), fly(), sail()), forcing all implementing classes to provide concrete implementations for methods they don’t need, often with fake or placeholder code.
Each class (Car, Airplane, Boat) has redundant, meaningless implementations for methods it doesn’t actually use.

2.Breaks ISP:
The classes Car, Airplane, and Boat depend on methods they don’t use, violating the principle.

3.Difficult to Maintain:
If the Vehicle interface changes (e.g., adding a swim() method), all derived classes will need to update their implementation—even if the new method is irrelevant.

4.Client Confusion:
A Car client could mistakenly call fly() and sail() since they appear on the interface, leading to runtime confusion.
Compliant Version (Fixing ISP)
To comply with ISP, break down the Vehicle interface into smaller, specific interfaces related to driving, flying, and sailing. Each implementing class will only depend on the methods it actually needs.

✅ISP Compliant: Divide into Specific Interfaces

#include <iostream>
#include <string>
#include <memory>

// Driving interface (Driving vehicles)
class Drivable {
public:
    virtual void drive() = 0;
    virtual ~Drivable() {}
};

// Flying interface (Flying vehicles)
class Flyable {
public:
    virtual void fly() = 0;
    virtual ~Flyable() {}
};

// Sailing interface (Sailing vehicles)
class Sailable {
public:
    virtual void sail() = 0;
    virtual ~Sailable() {}
};

// Car class (implements Drivable)
class Car : public Drivable {
public:
    void drive() override {
        std::cout << "Car is driving!" << std::endl;
    }
};

// Airplane class (implements Flyable)
class Airplane : public Flyable {
public:
    void fly() override {
        std::cout << "Airplane is flying!" << std::endl;
    }
};

// Boat class (implements Sailable)
class Boat : public Sailable {
public:
    void sail() override {
        std::cout << "Boat is sailing!" << std::endl;
    }
};

int main() {
    std::shared_ptr<Drivable> car = std::make_shared<Car>();
    car->drive();

    std::shared_ptr<Flyable> airplane = std::make_shared<Airplane>();
    airplane->fly();

    std::shared_ptr<Sailable> boat = std::make_shared<Boat>();
    boat->sail();

    return 0;
}
Output:
Car is driving!
Airplane is flying!
Boat is sailing!

What’s Different Now?
1.Smaller, Focused Interfaces:
The monolithic Vehicle interface is split into smaller, more specific interfaces: Drivable, Flyable, and Sailable.
Each interface represents one specific capability.

2.Classes Depend Only on Relevant Methods:
Car only implements the drive() method from the Drivable interface.
Airplane only implements the fly() method from the Flyable interface.
Boat only implements the sail() method from the Sailable interface.

3.ISP Compliance:
Classes depend only on the methods they actually use.
No more meaningless or placeholder implementations for methods that are irrelevant to a particular class.

4.Modular Design:
New functionality can be added without forcing unrelated classes to implement irrelevant methods.
For example, if we added a new interface Swimmable, only classes that swim need to implement it.

Advantages of Complying with ISP
Smaller, Focused Interfaces:
Interfaces remain easy to work with, and classes don’t depend on unrelated methods.

Code Maintainability:
Changes to one interface (e.g., adding a new method to Drivable) won’t impact classes that depend on other interfaces (Flyable, Sailable).

Avoids Confusion for Clients:
A client interacting only with a Car doesn’t see irrelevant methods like fly() or sail().

Flexible Design:
Subsystems remain decoupled, making the design extensible and modular.

When ISP Applies
The ISP comes into play when:
You notice large interfaces with many unrelated methods.
Different implementing classes require only subsets of the interface's methods.
New features or methods are being added to the interface, impacting all implementing classes unnecessarily
