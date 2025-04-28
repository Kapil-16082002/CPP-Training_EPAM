Dependency Inversion Principle:
High-level modules should not depend on low-level modules. Both should depend on abstractions.
And:
Abstractions should not depend on details. Details should depend on abstractions.
In simple ternms, class should rely on abstractions(e.g abstract classes or interfaces ) rather than concrete implementations.


Scenario: Notification System
We need to design a system that can send notifications to customers. 
Notifications can be sent via Email, SMS, or other mediums. 
The High-level module here is a Notification class responsible for notifying customers.
The Low-level modules are specific implementations like EmailNotifier or SMSNotifier.

⚠️Example Without DIP (Violation)
#include <iostream>
#include <string>

// Low-level module: EmailNotifier
class EmailNotifier {
public:
    void sendEmail(const std::string& message) {
        std::cout << "Sending Email: " << message << std::endl;
    }
};
// High-level module depends directly on the low-level module
class Notification {
private:
    EmailNotifier emailNotifier; // Tight coupling with EmailNotifier(sending notifications via Email)
public:
    void send(const std::string& message) {
        emailNotifier.sendEmail(message); // Direct dependency on email
    }
};
int main() {
    Notification notification;
    notification.send("Dependency Inversion Principle Violated!");

    return 0;
}
What’s the Problem?
1.Tight Coupling:
The Notification class is tightly coupled to the EmailNotifier class.
If we want to send notifications via SMS or any other medium in the future, we would have to modify the Notification class.

2.Hard to Extend:
Any new notification functionality (e.g., SMSNotifier) requires changes to the high-level module (Notification).
This violates the Open/Closed Principle as well.

3.Not Testable:
We cannot easily replace or mock EmailNotifier during testing, making the Notification class tightly dependent on a specific implementation.
Refactored Code (DIP-Compliant)


✅To make the system follow the Dependency Inversion Principle:
Create an abstraction for notification INotifier.
Have all notifiers (Email, SMS, etc.) implement this interface.
Make the Notification class depend on the interface (INotifier), not the specific implementations.
Achieve loose coupling and flexibility via Dependency Injection.
DIP-Compliant Code
#include <iostream>
#include <string>
#include <memory>

/* 
✅What Is the Abstract Interface?
Definition: An abstract class like INotifier is an interface with a pure virtual method (send(const std::string&)) that defines a contract.

virtual void send(const std::string& message) = 0; // Pure virtual method

Subclasses that inherit this abstraction must implement the send() method. The class itself cannot be instantiated directly because it is incomplete (virtual functions are pure).
Key Idea: This abstracts what needs to be done (sending a message), while hiding how it is done (Email, SMS, Push notifications, etc.).

✅What It Does:
Ensures that all notifier classes (EmailNotifier, SMSNotifier, etc.) follow the same contract (they all must implement send()).
The INotifier interface decouples the higher-level logic from the low-level details, such as the specifics of how notifications are sent.


✅Benefits of Using the Abstract Class (INotifier)
1. Promotes Loose Coupling
Without an abstraction, the high-level module (Notification) would have to depend directly on concrete implementations (EmailNotifier, SMSNotifier, etc.).
By using INotifier, the high-level module only depends on an abstraction, not specific implementations.

Why is this important?
It allows you to change or extend low-level implementations (add new notifiers like PushNotifier) without modifying the high-level module (Notification).
This keeps the system flexible and reduces the impact of changes in one part of the code.
Example:
If you want to introduce a new notifier for "Push Notifications," you don't need to modify the Notification class. Just create a new class:
class PushNotifier : public INotifier {
public:
    void send(const std::string& message) override {
        std::cout << "Sending Push Notification: " << message << std::endl;
    }
};
*/
// Abstract Interface (Abstraction)
//we use this abstract class to decouple the high-level module from the low-level implementations.
class INotifier {
public:
    virtual void send(const std::string& message) = 0; // Pure virtual method
    virtual ~INotifier() {}
};

// Low-level module: EmailNotifier
class EmailNotifier : public INotifier {
public:
    void send(const std::string& message) override {
        std::cout << "Sending Email: " << message << std::endl;
    }
};

// Low-level module: SMSNotifier
class SMSNotifier : public INotifier {
public:
    void send(const std::string& message) override {
        std::cout << "Sending SMS: " << message << std::endl;
    }
};

// High-level module depends on abstraction (INotifier)
class Notification {
private:
    std::shared_ptr<INotifier> notifier;
public:
    // Dependency injection via constructor
    Notification(std::shared_ptr<INotifier> notifier) : notifier(notifier) {}

    void notify(const std::string& message) {
        notifier->send(message); // Depend on abstraction
    }
};

int main() {
    // Use EmailNotifier
    std::shared_ptr<INotifier> emailNotifier = std::make_shared<EmailNotifier>();
    Notification emailNotification(emailNotifier);
    emailNotification.notify("Dependency Inversion Principle Implemented!");

    std::cout << "-----------------------" << std::endl;

    // Use SMSNotifier
    std::shared_ptr<INotifier> smsNotifier = std::make_shared<SMSNotifier>();
    Notification smsNotification(smsNotifier);
    smsNotification.notify("Sending via SMS!");

    return 0;
}
Output
Sending Email: Dependency Inversion Principle Implemented!
-----------------------
Sending SMS: Sending via SMS!
How This Code Follows Dependency Inversion Principle
1. High-Level Module Depends on Abstractions
The Notification class depends on the INotifier interface, not on specific implementations like EmailNotifier or SMSNotifier.
2. Abstractions Do Not Depend on Details
The high-level abstraction (INotifier) is independent of how the notification is sent. Low-level modules (EmailNotifier, SMSNotifier) depend on this abstraction, not vice versa.
3. Flexibility
Adding a new notifier (e.g., PushNotifier for push notifications) doesn’t require modifying the Notification class—it works seamlessly via polymorphism.
Example:
class PushNotifier : public INotifier {
public:
    void send(const std::string& message) override {
        std::cout << "Sending Push Notification: " << message << std::endl;
    }
};

int main() {
    // Use PushNotifier
    std::shared_ptr<INotifier> pushNotifier = std::make_shared<PushNotifier>();
    Notification pushNotification(pushNotifier);
    pushNotification.notify("This is a Push Notification!");
}
Output:
Sending Push Notification: This is a Push Notification!

4. Ease of Testing
For testing, we can inject a mock implementation of INotifier, such as:
class MockNotifier : public INotifier {
public:
    void send(const std::string& message) override {
        std::cout << "[MockNotifier] Simulating sending: " << message << std::endl;
    }
};
This lets us test the Notification class without relying on specific implementations like EmailNotifier or SMSNotifier.

Side-by-Side Comparison
Without DIP (Violation)	                                             With DIP (DIP-Compliant)
Notification depends directly on EmailNotifier.	                     Notification depends on INotifier (abstraction).
Hard to extend. Adding SMSNotifier requires modifying Notification.	 Easy to extend. Just create a new implementation of INotifier.
Tight coupling between Notification and low-level modules.	         Decoupled. High-level and low-level modules communicate via abstraction.
Not testable without real implementations.	                         Testable by injecting mock objects for INotifier.



Key Takeaways:

Abstractions Over Details:
The Notification class depends on the INotifier interface (abstraction), not specific implementations.

Dependency Injection:
Low-level functionality (EmailNotifier, SMSNotifier) is injected into the Notification class via constructor injection.

Maintainability and Flexibility:
Adding or modifying INotifier implementations requires no changes to the Notification class; it’s fully decoupled.
You can easily swap implementations (e.g., mock objects for testing).

