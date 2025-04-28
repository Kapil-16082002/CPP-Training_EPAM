
The SOLID principles are a set of five design principles in software development, proposed by Robert C. Martin (a.k.a. Uncle Bob). 
They aim to improve code maintainability, flexibility, readability, and scalability in object-oriented programming (OOP). 
These principles are guidelines for developers to write cleaner, more modular, and robust software systems.

✅SOLID is an acronym that stands for:

S - Single Responsibility Principle (SRP):
A class should have one and only one reason to change, meaning it should have only one responsibility or function.
Example: A User class should not handle database operations. A separate UserRepository class can manage that responsibility.

O - Open/Closed Principle (OCP):
Software entities (classes, modules, functions) should be open for extension but closed for modification.
Example: When adding new functionality, instead of modifying existing code, you can create new classes or methods that extend existing behavior.

L - Liskov Substitution Principle (LSP):
Subtypes must be substitutable for their base types without altering the correctness of the program.
Example: If Rectangle is a base class, and Square is a derived class, using a Square in the place of a Rectangle should not break the application.

I - Interface Segregation Principle (ISP):
A class should not be forced to implement interfaces it does not use.
Example: Instead of having one large Worker interface with unrelated methods (work(), eat()), split it into smaller interfaces (e.g., Workable and Eatable).

D - Dependency Inversion Principle (DIP):
High-level modules should not depend on low-level modules. Both should depend on abstractions (interfaces). Abstractions should not depend on details; details should depend on abstractions.
Example: Instead of a class directly instantiating a MySQLDatabase, it should depend on an abstraction, like a DatabaseInterface.


✅Why SOLID Principles?
SOLID principles are important to achieve the following goals in software development:

Maintainability: Code shoul be easier to debug, understand, and maintain.
Scalability and Extensibility: Adding new features or modifying existing ones becomes simpler, as changes in one part of the application won't affect other parts significantly.
Modularity: Breaking the system into smaller, independent modules reduces coupling and increases cohesion. This makes the codebase more reusable.
Code Testing: Following SOLID principles improves testability. Code broken into smaller parts with clear responsibilities makes creating unit tests easier and more effective.
Flexibility: Adhering to these principles allows for more adaptable systems that can handle changes without major rewrites.
Team Collaboration: Clean and well-structured code ensures that teams can work together more effectively, as it’s easier for multiple developers to understand and collaborate on the codebase.


//-----------------------------------------------------------------------------------------------------------------
✅
"A class should have only one reason to change."
This means that a class should perform a single, well-defined task or responsibility. 
When a class has more than one responsibility, it becomes harder to maintain, debug, and extend because changes in one part of the class may effects on other parts.

Why SRP is Important?
Maintainability: A class that handles a single responsibility is easier to understand and modify.
Extensibility: Changes and new features can be added without affecting unrelated parts of the application.
Testability: Small, focused classes are easier to test.
Separation of Concerns: Each class has a specific purpose, which makes the design cleaner and modular.



⚠️Code That Violates SRP
Here is an example where a single class does multiple things, violating the SRP:
#include <iostream>
#include <string>
using namespace std;

class User {
private:
    string name;
    string email;
public:
    User(string name, string email) : name(name), email(email) {}

    void saveToDatabase() {
        // Code logic for saving user to database
        cout << "Saving user '" << name << "' to the database.\n";
    }
    void sendEmail(string message) {
        // Code logic for sending email
        cout << "Sending email to '" << email << "': " << message << endl;
    }
};
int main() {
    User user("John Doe", "john.doe@example.com");
    // Violating SRP: One class handles both database and email responsibilities
    user.saveToDatabase();
    user.sendEmail("Welcome to our platform!");
    return 0;
}
Whats Wrong with This Code?
1.Multiple Responsibilities in One Class:
The User class is responsible for storing user information, saving the user to the database, and sending emails.
These are unrelated tasks bundled together, violating SRP.

2.Hard to Maintain:
If we modify the database logic, the chances of accidentally breaking email functionality increase.

3.Scalability or extensibility Issue:
If we want to later add SMS notifications or change user persistence to a different database, we will have to edit this single, cluttered class.

✅Solution:
Refactored Code Following SRP
To adhere to SRP, let's refactor the above code by splitting the responsibilities of the User class into separate classes, each with its own distinct responsibility:
#include <iostream>
#include <string>
using namespace std;

// Class responsible for storing user data
class User {
private:
    string name;
    string email;
public:
    User(string name, string email) : name(name), email(email) {}

    string getName() const { return name; }
    string getEmail() const { return email; }
};
// Class responsible for handling database operations
class UserRepository {
public:
    void saveToDatabase(const User &user) {
        // Logic for saving user to database
        cout << "Saving user '" << user.getName() << "' to the database.\n";
    }
};
// Class responsible for sending emails
class EmailService {
public:
    void sendEmail(const User &user, string message) {
        // Logic for sending email
        cout << "Sending email to '" << user.getEmail() << "': " << message << endl;
    }
};
int main() {
    // Create a new user
    User user("John Doe", "john.doe@example.com");

    // Create UserRepository for database operations
    UserRepository repository;
    repository.saveToDatabase(user);

    // Create EmailService for email-related operations
    EmailService emailService;
    emailService.sendEmail(user, "Welcome to our platform!");

    return 0;
}
How SRP is Followed in the Refactored Code?

✅Each Class Has a Single Responsibility:
1.User handles user information (name, email).
2.UserRepository handles database-related logic (saving user).
3.EmailService handles email functionality (sending emails).

✅Scalability and Extensibility:
If you want to introduce new features (like sending SMS notifications or using a different database), you simply create new classes without modifying existing code.


✅Modular Design:
1.If you need to change the database logic, you only update the UserRepository class.
2.If you need to modify email functionality or add SMS functionality, you only update the EmailService class.
3.Changes in one part of the system do not affect unrelated parts.

✅Improved Testability:
1.Each class can be tested independently:
2.UserRepository for database persistence.
3.EmailService for email functionality.
4.User class for its ability to store and retrieve user data.

✅Clean Separation of Concerns:
1.Each class now performs a single, focused task.


✅Advantages of This Approach
Maintainability: Code is much easier to modify and debug since responsibilities are isolated.
Extensibility: Adding new functionality becomes simpler since modifications are isolated within specific classes.
Team Collaboration: Developers can work on different classes independently.
Testability: Each class can be tested without depending on other classes, ensuring reliability.
