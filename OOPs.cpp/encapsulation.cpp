#Encapsulation
Encapsulation is defined as the wrapping up of data and information in a single unit. 
Encapsulation is the process of hiding internal data by making variables private and exposing controlled access through public methods.

Example
/*
In a company, there are different sections like the accounts section, finance section, sales section, etc. Now,
1.The finance section handles all the financial related transactions and keeps records of all the data related to finance.
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


#include <iostream>
using namespace std;
class Employee {
private:
    int employeeID;    // // Hidden Data
    string employeeName;
public:   
    // Controlled Access, Setter method for employeeID
    void setEmployeeID(int id) {
        if (id > 0) {
            employeeID = id;
        } 
        else {
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

1.how to access private members of a class without getter,setter method??
2.why encapsulation principle, still private members can be access??  

✅ 1. Using a Friend Function (Most Common Trick)

A friend function can access private members without getters/setters.

class Test {
private:
    int x = 10;
public:
    friend void show(Test t);   // friend function
};

void show(Test t) {
    cout << t.x;
}
int main() {
    Test obj;
    show(obj);
}
//===============================================================================================================

✅ 2. Using a Friend Class:

A class can become a friend of another class.

class A {
private:
    int x = 20;
    friend class B;  // B can access private part of A
};
class B {
public:
    void print(A obj) {
        cout << obj.x;
    }
};
//================================================================================================================

✅ 3. Using Pointer-to-Member Trick (Hack, But Valid C++)

Even if a member is private, the pointer-to-member can be declared outside.

class A {
private:
    int x = 30;
};

int A::* ptr = &A::x;   // ALLOWED!
int main() {
    A obj;
    cout << obj.*ptr;   // Access private member
}


✔ This actually compiles
✔ Because access control applies when accessing the member, not declaring pointer
✔ But many compilers allow it as a loophole