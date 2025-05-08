
✅Structural Design Patterns in C++:
Structural Design Patterns are design patterns that deal with the composition of objects and classes to form larger and more functional structures. 
Their purpose is to simplify relationships between entities and make the code more maintainable, reusable, and organized.

List of Common Structural Design Patterns:
Adapter Pattern
Bridge Pattern
Composite Pattern
Decorator Pattern
Facade Pattern
Flyweight Pattern
Proxy Pattern

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

✅Decorator Design Pattern in C++:
The Decorator Design Pattern is a structural design pattern that allows behavior or responsibilities to be dynamically added to an object, without altering its structure, by wrapping it in decorator objects. 
The decorator pattern follows the principle of composition instead of inheritance for extending functionality.

When to Use the Decorator Pattern:
1.When you want to add or modify behavior dynamically to individual objects without affecting other objects of the same class.
2.To extend functionality without modifying existing classes, following the Open/Closed Principle.
3.When inheritance is not practical (e.g., you want to add multiple unrelated behaviors).

✅Advantages of the Decorator Pattern
1.Flexible Behavior Extension:
Behavior can be added to individual objects dynamically, without modifying the base class.

2.Open/Closed Principle:
Extends functionality without modifying existing code.

3.Combinatorial Flexibility:
Decorators can be combined in various configurations, allowing a variety of runtime behaviors.
//---------------------------------------------------------------------------------------------------------------
✅Disadvantages of the Decorator Pattern
1.Complexity:
The Decorator pattern introduces additional classes and complexity for simple feature extensions.

2.Chained Decorators:
Excessive chaining of decorators might result in harder-to-track execution flows.

3.Dependency on Base Component:
All decorators must follow the same interface as the component being decorated.



✅Components of the Decorator Pattern
Component (Interface): Defines the interface that all concrete components and decorators implement.
Concrete Component: The actual object that needs behavior to be added/modified.
Decorator: An abstract class or base interface that wraps the Concrete Component and implements the same Component interface.
Concrete Decorators: Subclasses of the Decorator that add specific behaviors or modify the behavior of the wrapped object.

Scenario
Imagine we have:
A base pizza (PlainPizza) with no toppings.
Customers can choose various toppings such as cheese, pepperoni, and olives.
Each topping adds a description and cost to the pizza dynamically.

The Decorator Pattern is a perfect choice for this scenario because:
Toppings can be added dynamically at runtime.
We can offer a flexible combination of toppings without modifying the Pizza class directly.


#include <iostream>
#include <string>
using namespace std;
//Step 1: Component (Interface)
//The Pizza interface defines the base structure. All concrete pizzas and decorators implement this interface.
class Pizza {
public:
    virtual string getDescription() const = 0; // Abstract method to get pizza description
    virtual double getCost() const = 0;       // Abstract method to get pizza costs
    virtual ~Pizza() {}
};

// *** STEP 2: Concrete Component ***
class PlainPizza : public Pizza {
public:
    string getDescription() const override {
        return "Plain Pizza";
    }
    double getCost() const override {
        return 5.0; // Base cost
    }
};

// *** STEP 3: Decorator (Abstract Base Class) ***
class PizzaDecorator : public Pizza {
protected:
    Pizza* decoratedPizza; // Wrapped Pizza object
public:
    PizzaDecorator(Pizza* decorated_Pizza) : decoratedPizza(decorated_Pizza) {}

    virtual ~PizzaDecorator() {
        delete decoratedPizza; // Proper cleanup of wrapped pizza object
    }
    string getDescription() const override {
        return decoratedPizza->getDescription(); // Forward getDescription
    }
    double getCost() const override {
        return decoratedPizza->getCost(); // Forward getCost
    }
};
// *** STEP 4: Concrete Decorators ***

// Decorator for Cheese
class CheeseDecorator : public PizzaDecorator {
public:
    CheeseDecorator(Pizza* decorated_Pizza) : PizzaDecorator(decorated_Pizza) {}

    string getDescription() const override {
        return decoratedPizza->getDescription() + " + Cheese"; // Add "Cheese" to description
    }

    double getCost() const override {
        return decoratedPizza->getCost() + 1.5; // Add cost of Cheese
    }
};

// Decorator for Pepperoni
class PepperoniDecorator : public PizzaDecorator {
public:
    PepperoniDecorator(Pizza* decoratedPizza) : PizzaDecorator(decoratedPizza) {}

    string getDescription() const override {
        return decoratedPizza->getDescription() + " + Pepperoni"; // Add "Pepperoni" to description
    }

    double getCost() const override {
        return decoratedPizza->getCost() + 2.0; // Add cost of Pepperoni
    }
};

// Decorator for Olives
class OlivesDecorator : public PizzaDecorator {
public:
    OlivesDecorator(Pizza* decoratedPizza) : PizzaDecorator(decoratedPizza) {}

    string getDescription() const override {
        return decoratedPizza->getDescription() + " + Olives"; // Add "Olives" to description
    }

    double getCost() const override {
        return decoratedPizza->getCost() + 1.0; // Add cost of Olives
    }
};

int main() {
    // Start with a plain pizza
    Pizza* plainPizza = new PlainPizza();
    cout << "Pizza Description: " <<  plainPizza->getDescription() << endl;
    cout << "Pizza Cost: $" <<  plainPizza->getCost() << endl;

    // Decorate with Cheese
    Pizza* cheesePizza = new CheeseDecorator(plainPizza);
    cout << "Pizza Description: " << cheesePizza->getDescription() << endl;
    cout << "Pizza Cost: $" << cheesePizza->getCost() << endl;

    // Decorate with Pepperoni on top of Cheese
    Pizza* pepperoniCheesePizza = new PepperoniDecorator(cheesePizza);
    cout << "Pizza Description: " << pepperoniCheesePizza->getDescription() << endl;
    cout << "Pizza Cost: $" << pepperoniCheesePizza->getCost() << endl;

    // Decorate with Olives on top of Pepperoni and Cheese
    Pizza* fullyLoadedPizza = new OlivesDecorator(pepperoniCheesePizza);

    // Display the final pizza description and cost
    cout << "Pizza Description: " << fullyLoadedPizza->getDescription() << endl;
    cout << "Pizza Cost: $" << fullyLoadedPizza->getCost() << endl;
    // Clean up all dynamically allocated objects
    delete fullyLoadedPizza;
    return 0;

}
Output:
Pizza Description: Plain Pizza + Cheese + Pepperoni + Olives
Pizza Cost: $9.5
//--------------------------------------------------------------------------------------------------------------
Step 1: Component (Interface)
The Pizza interface defines the base structure. All concrete pizzas and decorators implement this interface.
#include <iostream>
#include <string>
using namespace std;

// Component: Base interface for Pizza and toppings
class Pizza {
public:
    virtual string getDescription() const = 0;
    virtual double getCost() const = 0;
    virtual ~Pizza() {}
};

Step 2: Concrete Component
The PlainPizza class is the basic pizza with no toppings.


// Concrete Component: Basic pizza with no toppings
class PlainPizza : public Pizza {
public:
    string getDescription() const override {
        return "Plain Pizza";
    }

    double getCost() const override {
        return 5.0; // Base price of plain pizza
    }
};

Step 3: Decorator (Abstract Base Class)
The base PizzaDecorator class wraps an existing pizza and forwards requests while allowing specific decorators to enhance the behavior.


// Decorator: Base class for topping decorators
class PizzaDecorator : public Pizza {
protected:
    Pizza* decoratedPizza; // The Pizza object being decorated

public:
    PizzaDecorator(Pizza* pizza) : decoratedPizza(pizza) {}

    virtual ~PizzaDecorator() {
        delete decoratedPizza; // Clean up the wrapped pizza object
    }

    string getDescription() const override {
        return decoratedPizza->getDescription(); // Forward description
    }

    double getCost() const override {
        return decoratedPizza->getCost(); // Forward cost
    }
};

Step 4: Concrete Decorators
These classes extend the functionality of the Pizza by adding toppings.

1.Cheese Topping

class CheeseDecorator : public PizzaDecorator {
public:
    CheeseDecorator(Pizza* pizza) : PizzaDecorator(pizza) {}

    string getDescription() const override {
        return decoratedPizza->getDescription() + " + Cheese";
    }

    double getCost() const override {
        return decoratedPizza->getCost() + 1.5; // Add cost of cheese
    }
};
2.Pepperoni Topping

class PepperoniDecorator : public PizzaDecorator {
public:
    PepperoniDecorator(Pizza* pizza) : PizzaDecorator(pizza) {}

    string getDescription() const override {
        return decoratedPizza->getDescription() + " + Pepperoni";
    }

    double getCost() const override {
        return decoratedPizza->getCost() + 2.0; // Add cost of pepperoni
    }
};
3.Olives Topping


class OlivesDecorator : public PizzaDecorator {
public:
    OlivesDecorator(Pizza* pizza) : PizzaDecorator(pizza) {}

    string getDescription() const override {
        return decoratedPizza->getDescription() + " + Olives";
    }

    double getCost() const override {
        return decoratedPizza->getCost() + 1.0; // Add cost of olives
    }
};

Step 5: Client Code
The client assembles the pizza dynamically by wrapping it in toppings.


int main() {
    // Step 1: Start with a plain pizza
    Pizza* plainPizza = new PlainPizza();

    // Step 2: Add Cheese
    Pizza* cheesePizza = new CheeseDecorator(plainPizza);

    // Step 3: Add Pepperoni on top of Cheese
    Pizza* pepperoniCheesePizza = new PepperoniDecorator(cheesePizza);

    // Step 4: Add Olives on top of Pepperoni and Cheese
    Pizza* fullyLoadedPizza = new OlivesDecorator(pepperoniCheesePizza);

    // Display the final pizza description and cost
    cout << "Pizza Description: " << fullyLoadedPizza->getDescription() << endl;
    cout << "Pizza Cost: $" << fullyLoadedPizza->getCost() << endl;

    // Clean up
    delete fullyLoadedPizza; // Automatically cleans up the chain of decorators

    return 0;
}

