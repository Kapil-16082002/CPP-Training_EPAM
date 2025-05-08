✅Adapter Design Pattern :
The Adapter Design Pattern is a structural pattern that allows two incompatible interfaces to work together. 
It acts as a bridge between two systems by converting one interface into another that the client expects. 
This pattern is often used when a class's interface is incompatible with what the client code requires.


When to Use It:
When you have two incompatible classes or systems that need to work together.
When you want to use an existing class's functionality, but its interface does not match the requirements of your current system or code.


✅key components:
Target: The standard interface expected by the client.
Adaptee: The existing class or functionality with an incompatible interface.
Adapter: The class that wraps the Adaptee and translates its interface to the Target.
Client: The code that interacts with the Target interface, unaware of the adapter's presence..


//In this code, the adapter allows charging a mobile using a laptop charger.
// i.e we have only laptop charger and want to charge mobile using laptop charger..
#include <iostream>
using namespace std;
// **********************************************
// Target Interface: MobileCharger
// This is the interface expected by the client (Mobile).
// Any charger that works with the mobile must implement this interface.
// **********************************************
class MobileCharger {
public:
    virtual void chargeMobile() = 0; // Abstract method to charge a mobile
    virtual ~MobileCharger() {}     // Virtual destructor for proper cleanup
};
// **********************************************
// Adaptee Class: LaptopCharger
// This is an incompatible class designed ONLY for laptops.
// It contains a method (chargeLaptop) that cannot directly work with MobileCharger.
// **********************************************
class LaptopCharger {
public:
    void chargeLaptop() {
        // Laptop-specific charging behavior
        cout << "Charging laptop using Laptop Charger.\n";
    }
};
// Adapter Class: ChargerAdapter
// This class bridges the gap between LaptopCharger (Adaptee) and MobileCharger (Target).
// It implements the MobileCharger interface and translates its method into the functionality provided by the LaptopCharger.
class ChargerAdapter : public MobileCharger {
private:
    LaptopCharger* laptopCharger; // Holds an instance of the Adaptee (LaptopCharger)
public:
    // Constructor takes a LaptopCharger object to adapt between interfaces
    ChargerAdapter(LaptopCharger* charger) : laptopCharger(charger) {}

    // Override the chargeMobile method from MobileCharger interface
    void chargeMobile() override {
        // Adapter translates the "chargeMobile" call into a "chargeLaptop" call
        cout << "Using adapter to allow Laptop Charger to charge a mobile.\n";
        laptopCharger->chargeLaptop(); // Calls LaptopCharger behavior
    }
};
// **********************************************
// Client Class: Mobile
// It does not know about LaptopCharger or ChargerAdapter.
// The client (Mobile) expects to use an object of type MobileCharger.
// **********************************************
class Client {
public:
    void plugIn(MobileCharger* charger) {
        // The mobile interacts ONLY with the MobileCharger interface
        cout << "Mobile is plugged into a charger.\n";
        charger->chargeMobile(); // Calls the appropriate MobileCharger method
    }
};
int main() {
    // Step 1: Create a LaptopCharger (Adaptee)
    // This is the incompatible laptop charger that we want to adapt.
    LaptopCharger* laptopCharger = new LaptopCharger();

    // Step 2: Use ChargerAdapter to adapt the LaptopCharger to the MobileCharger interface
    // The ChargerAdapter makes LaptopCharger usable for Mobile.
    MobileCharger* chargerAdapter = new ChargerAdapter(laptopCharger);

    // Step 3: Create a Mobile (Client) and use the adapter
    // The mobile interacts with the adapter, unaware that it's working with a LaptopCharger.
    Client mobile;
    mobile.plugIn(chargerAdapter);

    // Step 4: Clean up memory
    delete laptopCharger;
    delete chargerAdapter;

    return 0;
}
Output:
Mobile is plugged into a charger.
Using adapter to allow Laptop Charger to charge a mobile.
Charging laptop using Laptop Charger.



