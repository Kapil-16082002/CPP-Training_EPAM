
The PIMPL (stands Pointer to Implementation) idiom is a design pattern used to hide implementation details of a class, reduces compilation time and improves encapsulation.
🔹 Also known as: "Opaque Pointer Idiom".
🔹 Used for:  1. Hide implementation details of a class
              2.  Reducing compilation time
              3.  improving encapsulation
           
✅ Why Use PIMPL?
🔹 Encapsulation: Hides implementation details from the header file.
🔹 Reduced Compilation Dependencies: Changes to the implementation do not require recompiling dependent files.
🔹 Faster Compilation: Since the header contains only a pointer, less code needs recompilation when changes occur.

/* 
✅Compilation Time Example
Imagine a project with the following files:

PublicInterface.h
PublicInterface.cpp
FileA.cpp (includes PublicInterface.h)
FileB.cpp (includes PublicInterface.h)
main.cpp
If you change something in Impl (e.g., std::string data becomes int data), only PublicInterface.cpp needs to be recompiled. FileA.cpp, FileB.cpp, main.cpp don’t need recompilation because PublicInterface.h is unaffected.

✅File Involvement in Recompilation:
Case 1: No Changes
None of the files need recompilation if no changes are made.

Case 2: Change in PublicInterface.cpp
If you change only the implementation of methods in PublicInterface.cpp (e.g., logic within getData() or setData()), only PublicInterface.cpp will be recompiled.
main.cpp is not affected, as it depends only on the API declared in PublicInterface.h, which remains unchanged.

Case 3: Change in PublicInterface.h
If you change the contents of PublicInterface.h:
Both PublicInterface.cpp and main.cpp will need to be recompiled because both include the header file.
This happens because the compiler "copies" the contents of the header file into both PublicInterface.cpp and main.cpp.

Case 4: Change in main.cpp
If you change only main.cpp, only it will need to be recompiled. PublicInterface.cpp remains unaffected.



*/

1️⃣ PublicInterface.h (Header File - Interface)
This is the public-interface that the user interacts with.
It only declares methods and uses a forward declaration to hide implementation details.

#ifndef PUBLIC_INTERFACE_H
#define PUBLIC_INTERFACE_H
#include <memory>  // For std::unique_ptr

class Impl;  // Forward declaration of the hidden implementation class

class PublicInterface {
private:
    std::unique_ptr<Impl> pImpl;  // Owning pointer to the implementation class
public:
    PublicInterface();   // Constructor
    ~PublicInterface();  // Destructor

    void getData();  // Public method for getting data
    void setData();  // Public method for setting data
};
#endif
🔹 What’s happening here?
✅ Encapsulation: The implementation details are hidden from the user.
✅ Forward Declaration: class Impl; prevents including unnecessary headers in the header file, reducing dependencies.
✅ unique_ptr: Used for automatic memory management of Impl without needing explicit delete.

//--------------------------------------------------------------------------------------------------------------

2️⃣ PublicInterface.cpp
The implementation file provides the actual functionality of methods and defines the hidden implementation (Impl).

#include "PublicInterface.h"
#include <iostream>
#include <string>

// Define the hidden class - `Impl`
class Impl {
private:
    std::string data;  // Internal data tracked by implementation
public:
    Impl() : data("Default Data") {
        std::cout << "Impl Constructor: Initialized with default data.\n";
    }
    ~Impl() {
        std::cout << "Impl Destructor: Cleaning up resources.\n";
    }
    void getData() const {
        std::cout << "Impl: Retrieving data --> " << data << std::endl;
    }
    void setData(const std::string& newData) {
        data = newData;  // Update internal data
        std::cout << "Impl: Data has been set to --> " << data << std::endl;
    }
};

// Constructor initializes the private implementation (`pImpl`)
PublicInterface::PublicInterface() : pImpl(std::make_unique<Impl>()) {}  // Using `std::make_unique`

// Destructor (defaulted, automatically destroys `pImpl`)
PublicInterface::~PublicInterface() = default;

// Public method to delegate retrieval of data to `Impl`
void PublicInterface::getData() {
    pImpl->getData();  // Forward call to the hidden `Impl` class
}

// Public method to delegate updating data to `Impl`
void PublicInterface::setData() {
    std::string userInput;
    std::cout << "PublicInterface: Please enter new data: ";
    std::getline(std::cin, userInput);  // Get user input from the terminal

    pImpl->setData(userInput);  // Forward the new data to `Impl`
}


//-------------------------------------------------------------------------------------------------------------------

3️⃣ main.cpp (User Code - Uses the Interface)
This is the entry point where the PublicInterface is used.

#include <iostream>
#include "PublicInterface.h"
int main() {
    PublicInterface obj;
    obj.getData();  // Calls `Impl::getData` indirectly and retrieves the default data
    obj.setData();  // Calls `Impl::setData` indirectly to set new data
    obj.getData();  // Calls `Impl::getData` again to confirm the updated data
    return 0;
}
🔹 What’s happening here?
✅ The user interacts only with PublicInterface, without knowing the actual implementation.
✅ Calls to getData() and setData() are forwarded to the hidden Impl class.

🔍 How the Implementation Works Step-by-Step
The user includes PublicInterface.h and creates a PublicInterface object in main.cpp.

When PublicInterface is instantiated:
It creates a std::unique_ptr<Impl> in PublicInterface.cpp, which internally creates an Impl object.

Calling obj.getData():
getData() in PublicInterface delegates to pImpl->getData(), which executes Impl::getData().

Calling obj.setData():
Similarly, setData() is forwarded to pImpl->setData(), which runs Impl::setData().

When obj goes out of scope:
PublicInterface's destructor is called.

std::unique_ptr<Impl> automatically deletes the Impl instance.