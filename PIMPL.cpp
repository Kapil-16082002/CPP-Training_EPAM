
The PIMPL (stands Pointer to Implementation) idiom is a design pattern used to hide implementation details of a class, reduces compilation time and improves encapsulation.
🔹 Also known as: "Opaque Pointer Idiom".
🔹 Used for:  1. Hide implementation details of a class
              2.  Reducing compilation time
              3.  improving encapsulation

The public class contains only a pointer (usually std::unique_ptr) to a private implementation class (Impl), which is defined in the .cpp file.
✅ Why Use PIMPL?
🔹 Encapsulation: Hides implementation details from the header file.
🔹 Reduced Compilation Dependencies: Changes to the implementation do not require recompiling dependent files.
🔹 Faster Compilation: Since the header contains only a pointer, less code needs recompilation when changes occur.



✅What problems does PIMPL solve?
PIMPL solves major problems:
1. Leaky encapsulation (private members visible in headers)
2. Long recompilation times due to header dependencies

How does PIMPL reduce compilation time?
Answer:
Because the header contains:
Only a forward declaration (class Impl;)
A pointer (std::unique_ptr<Impl>)
Changes inside Impl do not affect the header, so dependent files (like main.cpp) are not recompiled.


//================================================================================================================
/*
✅Compilation Time Example
Imagine a project with the following files:

PublicInterface.h
PublicInterface.cpp
main.cpp(includes PublicInterface.h)
If you change something in Impl (e.g., std::string data becomes int data), only PublicInterface.cpp needs to be recompiled. 
main.cpp don’t need recompilation because PublicInterface.h is unaffected.

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
It only declares methods and uses a Forward declaration of the hidden implementation class


#ifndef PUBLIC_INTERFACE_H
#define PUBLIC_INTERFACE_H
#include <memory>  // For std::unique_ptr

class Impl;  // Forward declaration of the hidden implementation class
/* 
Why do we forward-declare class Impl; in the header?
Answer:
Forward declaration avoids including heavy headers (<string>, <vector>, etc.) in the public header, reducing compilation dependencies.
*/

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

//=================================================================================================================
✅What problems does PIMPL solve?
PIMPL solves major problems:
1. Leaky encapsulation (private members visible in headers)
2. Long recompilation times due to header dependencies


❌ Without PIMPL
Leaky encapsulation (private members visible in headers)
Leaky encapsulation means: Even though data members are private, but implementation details are still leak through the header file, forcing users of the class to know things they shouldn’t care about.
/*Leaky encapsulation occurs when private data members are placed in the header file.
Although access members are not accessible but implementation details like data structures, libraries, and memory layout are still visible to users, causing tight coupling and recompilation.
PIMPL fixes this by hiding all private data behind an opaque pointer.*/


🔹 How do private members “leak” if they’re private?

private only controls ACCESS, not VISIBILITY ❌ It does not hide information
✅ It only prevents direct access from outside the class
Anyone who includes the header can still SEE everything written in it.
🔴 Because the header is PUBLIC TEXT: It is plain text that gets copied into every .cpp that includes it.
❌They still cannot access private members:
Widget w;
w.data;   // ❌ compile-time error


Header file (widget.h)
#include <vector>
#include <string>
#include <map>
class Widget {
private:
    std::vector<int> data;
    std::map<std::string, int> cache;
    std::string name;
};
When every .cpp that does:

#include "widget.h"
The compiler sees:
std::vector<int>
std::map<std::string, int>
std::string


🔴 What leaked here?
Even though members are private, the header reveals:
std::vector is used
std::map is used
std::string is used
Data structure choices
Performance implications

🔹 Why is this a PROBLEM?
If Widget internally changes:
std::map  →  std::unordered_map
➡️ Header changes
➡️ Every file including this header must recompile

--------------------------------------------------------------------------------------------------------------------
✅SOLUTION
🔹 How PIMPL fixes this
Header with PIMPL (NO LEAK)
// widget.h
class Widget {
public:
    Widget();
    ~Widget();
    void doWork();
private:
    struct Impl;          // forward declaration only
    Impl* pImpl;          // opaque pointer
};
🔒 What is hidden now?
No STL headers
No data structures
No algorithms
No third-party libraries
👉 True encapsulation

🔹 Implementation file (widget.cpp)
#include "widget.h"
#include <vector>
#include <map>
#include <string>
struct Widget::Impl {
    std::vector<int> data;
    std::map<std::string, int> cache;
    std::string name;
};


//================================================================================================================

✅👉 PIMPL reduces compilation
PIMPL reduces compilation time by removing heavy headers and implementation details from public headers, so changes in implementation no longer force recompilation of all dependent files.

1️⃣ What causes long compilation time in C++ ?
❌ Without PIMPL (problem)
// widget.h
#include <vector>
#include <map>
#include <string>
#include <regex>
#include <thread>
#include <mutex>
class Widget {
    std::vector<int> data;
    std::map<std::string,int> cache;
};
if anything change in this header file happened , ALL header including .cpp files must recompile 


3️⃣ How PIMPL fixes this
❌ No <vector>
❌ No <map>
❌ No <string>
❌ No heavy headers

Only:
Pointer size known (sizeof(void*))
Minimal parsing work
✅ Header with PIMPL (lightweight)
// widget.h
class Widget {
public:
    Widget();
    ~Widget();
    void doWork();
private:
    struct Impl;   // forward declaration
    Impl* pImpl;
};

Heavy headers move to .cpp
// widget.cpp
#include "widget.h"
#include <vector>
#include <map>
#include <string>
#include <regex>
#include <thread>
#include <mutex>

struct Widget::Impl {
    std::vector<int> data;
    std::map<std::string,int> cache;
};


Now:
