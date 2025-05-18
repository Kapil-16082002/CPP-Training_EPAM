#Encapsulation
Encapsulation is defined as the wrapping up of data and information in a single unit. 
Encapsulation is defined as binding together the data and the functions that manipulate them.

It refers to bundling the data (variables) and the methods (functions) within a single entity (a class), and controlling access to the internal details of that entity(class).

Example
/*
In a company, there are different sections like the accounts section, finance section, sales section, etc. Now,
1.The finance section handles all the financial transactions and keeps records of all the data related to finance.
2.Similarly, the sales section handles all the sales-related activities and keeps records of all the sales.

Now there may arise a situation when for some reason an official from the finance section needs 
all the data about sales in a particular month.
In this case, he is not allowed to directly access the data of the sales section. 
He will first have to contact some other officer in the sales section and then request him to give the particular data.
This is what Encapsulation is. Here the data of the sales section and the employees that can manipulate them are wrapped under a single name “sales section”. 
*/

Key Features of Encapsulation:
1.Data Hiding: The internal state of an object is hidden from outside interference and misuse. 
  Only the class's own methods can directly access and modify its fields.
2.Access Control: Access to the class members is controlled through access modifiers: private, public, and protected.
                   Private: Members declared as private are only accessible within the class itself.
                   Public: Members declared as public are accessible from outside the class.
                   Protected: Members declared as protected are accessible within the class and its derived classes

1.how to access private members of a class without getter,setter method??
2.why encapsulation principle, still private members can be access??                 
#include <iostream>
using namespace std;
class Employee {
private:
    int employeeID;    // private data member
    string employeeName;
public:
    // Setter method for employeeID
    void setEmployeeID(int id) {
        if (id > 0) {
            employeeID = id;
        } else {
            cout << "Invalid Employee ID" << endl;
        }
    }
    // Getter method for employeeID
    int getEmployeeID() {
        return employeeID;
    }
    // Setter method for employeeName
    void setEmployeeName(string name) {
        employeeName = name;
    }
    // Getter method for employeeName
    string getEmployeeName() {
        return employeeName;
    }
    // Display employee information
    void displayEmployeeInfo() {
        cout << "Employee ID: " << employeeID << ", Name: " << employeeName << endl;
    }
};
int main() {
    Employee emp;
    // Setting the employee details using setter methods
    emp.setEmployeeID(101);
    emp.setEmployeeName("John Doe");
    // Accessing employee details using getter methods
    cout << "Employee ID: " << emp.getEmployeeID() << endl;
    cout << "Employee Name: " << emp.getEmployeeName() << endl;
    // Displaying employee information
    emp.displayEmployeeInfo();
    return 0;
}
Output:
Employee ID: 101
Employee Name: John Doe
Employee ID: 101, Name: John Doe
