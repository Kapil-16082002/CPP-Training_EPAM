
The PIMPL (Pointer to Implementation) idiom is a design pattern used to hide implementation details of a class, reducing compilation dependencies and improving encapsulation.
🔹 Also known as: "Opaque Pointer Idiom"
🔹 Used for: Hide implementation details of a class
             Reducing compilation time
             improving encapsulation
             improving binary compatibility, and maintaining API stability
✅ Why Use PIMPL?
🔹 Encapsulation: Hides implementation details from the header file.
🔹 Reduced Compilation Dependencies: Changes to the implementation do not require recompiling dependent files.
🔹 Faster Compilation: Since the header contains only a pointer, less code needs recompilation when changes occur.
🔹 Binary Compatibility: Changes to private members do not affect clients using the class.

🔹 Example: Using PIMPL in C++
Step 1: Person.h (Header File - Interface)

#ifndef PERSON_H
#define PERSON_H

#include <memory>
#include <string>

class Person {
public:
    Person(const std::string& name, int age);
    ~Person();  // Destructor needed for PIMPL

    void displayInfo() const;

private:
    class PersonImpl;              // Forward declaration
    std::unique_ptr<PersonImpl> pImpl;  // Pointer to implementation
};
#endif  // PERSON_H

✔ Only a forward-declared class PersonImpl; is present in the header
✔ std::unique_ptr<PersonImpl> is used for automatic memory management
✔ No private data members are exposed in the header

Step 2: Person.cpp (Implementation File)

#include "Person.h"
#include <iostream>

class Person::PersonImpl {  // Actual implementation hidden in .cpp
public:
    std::string name;
    int age;

    PersonImpl(const std::string& name, int age) : name(name), age(age) {}

    void displayInfo() const {
        std::cout << "Name: " << name << ", Age: " << age << std::endl;
    }
};

// Constructor (delegates creation to pImpl)
Person::Person(const std::string& name, int age)
    : pImpl(std::make_unique<PersonImpl>(name, age)) {}

// Destructor (automatically deletes pImpl)
Person::~Person() = default;

// Public function calls the hidden implementation
void Person::displayInfo() const {
    pImpl->displayInfo();
}
✔ PersonImpl is defined only in the .cpp file (not exposed in the header).
✔ std::make_unique<PersonImpl> is used for efficient memory allocation.
✔ Memory is automatically released when Person is destroyed.

Step 3: main.cpp (Client Code)

#include "Person.h"
int main() {
    Person p("Alice", 25);
    p.displayInfo();

    return 0;
}
✔ The client code does not see implementation details.
✔ Only the public API (displayInfo) is exposed.

✅ Output
Name: Alice, Age: 25
