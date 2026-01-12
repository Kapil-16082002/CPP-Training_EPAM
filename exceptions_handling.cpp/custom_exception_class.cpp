Custom Exception Handling:
Custom exception handling allow creating user-defined exceptions  and if user is getting its own defined exception ,user can handle that error scenarios in a program. 
By defining our own exception classes, we can handle errors and can provide meaningful feedback(can provide more functionality) and would not dpend on standard library exceptions. 
This allows developers to handle domain-specific errors based on their application logic.

#include <iostream>
#include <exception>
using namespace std;

// Custom exception for division by zero
class DivisionByZeroException : public exception {
    const char* error_msg;
public:
    DivisionByZeroException(const char* msg) : error_msg{msg} {}  // Constructor initializes the error message
    const char* what() const throw() { //This is a member function that overrides the what() function from the std::exception class.
        return error_msg;
    }
};
/*  
Overriding: When a function in a derived class has the same name, return type, and parameters as a function in its base class, the derived class's function is replaced by the base class's function when object of the derived type is called.
The what() function overrides the what() function from the base class std::exception. This is where overriding is used to provide custom functionality (i.e., returning the error message error_msg).

Base Class (std::exception) Definition for what():
In the standard library, the base class std::exception declares the what() method like this:

virtual const char* what() const throw();
*/
/*If an exception is thrown, the catch block catches the exception.
Inside the catch block, the what() method of the thrown exception object is called automatically when e.what() is written.*/

int main() {
    double numerator = 10.0;  // Replace with desired numerator
    double denominator = 0.0; // Replace with desired denominator
    try {
        // Perform division directly in the main function
        if (denominator == 0) {
            throw DivisionByZeroException("Error: Division by zero is not allowed.");//
        }
        double result = numerator / denominator;
        cout << "Result: " << result << endl;

    } catch (const DivisionByZeroException& e) {//The reference variable (e) refers to the temporary exception object created by the throw statement.e is a reference to the thrown exception object.
        // Catch DivisionByZeroException and display error message
        cout << e.what() << endl;

    } catch (const exception& e) {
        // Catch any other unexpected exceptions
        cout << "An unexpected error occurred: " << e.what() << endl;
    }
    return 0;
}
/*  
Analysis of the throw Line:
1.What Does It Do?
The throw keyword:
Dynamically constructs a temporary object of the specified exception type(here  DivisionByZeroException).
Passes this object to the corresponding catch block.

2.Why Temporary?
The exception object (created by throw) exists until it is caught by a catch block. Once caught:
If caught by value (e.g., catch (DivisionByZeroException e)), the temporary object is copied.
If caught by reference (e.g., catch (DivisionByZeroException& e)), no copy is created, and the temporary object is directly accessed.


*/