//what are design principles?? why design principle??

✅What is Creational Design Pattern?
Creational design patterns are a category of design patterns in software development that generally focus on the process of object creation. 
They ensure that the creation of objects is flexible, reusable, and scalable while hiding the object creation logic from the client code.


✅Key Benefits of Creational Design Patterns:
Encapsulation of Object Creation: Hides the details of how objects are created, providing flexibility to change the creation process later.
Decoupling: Decouples the client code from the specific classes it uses, allowing the code to work with abstractions rather than concrete implementations.
Scalability: Enables the system to handle complex object creation logic efficiently.
Code Reusability: Promotes reusable and modular object creation logic.

///-------------------------    Factory Method Design Pattern   ------------------------------------------------


✅The Factory Method Design Pattern is part of the Creational Design Patterns family. 
It provides an interface for creating objects but allows subclasses to alter(change) the type of objects that will be created. 
This promotes loose coupling between the creator code and the objects it uses.

✅Why Use the Factory Method?
To decouple object creation from the client code.
To follow the Open/Closed Principle: New types of products can be added without modifying existing code.
When the object type to be instantiated isn’t known at compile-time and should be determined dynamically at runtime.


Factory Method Pattern: C++ Implementation
Example: Transportation Example
Scenario: Suppose we need to create a transportation system where we might use a Car for road transport or a Boat for water transport.
Problem: The client code shouldn’t directly instantiate Car or Boat but instead rely on the Factory Method to create the required object.


#include <iostream>
#include <memory> // For std::unique_ptr
#include <string>

// Step 1: Define the Product Interface
class Transport {
public:
    virtual ~Transport() {}
    virtual void deliver() const = 0; // Pure virtual method
};
// Step 2: Implement Concrete Products
class Car : public Transport {
public:
    void deliver() const override {
        std::cout << "Delivering by road using a Car." << std::endl;
    }
};
class Boat : public Transport {
public:
    void deliver() const override {
        std::cout << "Delivering by water using a Boat." << std::endl;
    }
};
// Step 3: Define the Creator (Factory) Interface
class TransportFactory {
public:
    virtual ~TransportFactory() {}
    virtual std::unique_ptr<Transport> createTransport() const = 0; // Factory Method
};
// Step 4: Implement Concrete Creators (Factories)
class CarFactory : public TransportFactory {
public:
    std::unique_ptr<Transport> createTransport() const override {
        return std::make_unique<Car>(); // Creates a Car
    }
};
class BoatFactory : public TransportFactory {
public:
    std::unique_ptr<Transport> createTransport() const override {
        return std::make_unique<Boat>(); // Creates a Boat
    }
};
// Step 5: Client Code
void clientCode(const TransportFactory& factory) {
    // The client does not know which specific transport it deals with.
    // It uses the factory to create the product.
    auto transport = factory.createTransport();
    transport->deliver();
}
// Main Function
int main() {
    // Use CarFactory
    CarFactory carFactory;
    std::cout << "Client: Using CarFactory:" << std::endl;
    clientCode(carFactory);

    // Use BoatFactory
    BoatFactory boatFactory;
    std::cout << "Client: Using BoatFactory:" << std::endl;
    clientCode(boatFactory);

    return 0;
}
Output:
Client: Using CarFactory:
Delivering by road using a Car.
Client: Using BoatFactory:
Delivering by water using a Boat.


✅Explanation of the Code:
Transport Interface (Product Interface):
Transport is the base class/interface that defines the deliver() method, which must be implemented by all concrete products (Car and Boat).

Concrete Products (Car and Boat):
These are the specific implementations of the Transport interface. They provide custom behavior for the deliver() method.

TransportFactory (Creator):
This is an abstract base class defining the factory method createTransport, which returns an object of type Transport.

Concrete Factories (CarFactory and BoatFactory):
These are specific implementations of the factory method, each creating a specific product (Car or Boat) that implements the Transport interface.

Client Code (clientCode function):
Calls the factory method to obtain a Transport object without knowing the exact class of the object (Car or Boat).
This keeps the client code decoupled from the specific logic of creating or managing objects.
