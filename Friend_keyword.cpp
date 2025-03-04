
The friend keyword in C++ allows non-member functions and other classes to access private and protected members of a class.
📌 2️⃣ Types of friend in C++
Type	                          Description
Friend Function	    ->              A non-member function that can access private/protected members.
Friend Class	    ->               A class that can access private members of another class.
Friend Member Function of Another Class->   A specific function of another class that gets access.

📌 3️⃣ friend Function (Non-Member Function Access)
✅ A standalone function (outside the class) is given access to private members.
🔹 Example: Accessing Private Members
#include <iostream>
using namespace std;
class Box {
private:
    int width;
public:
    Box(int w) : width(w) {} 
    friend void printWidth(Box b); // Friend function declaration
};
void printWidth(Box b) {                   // Friend function definition (outside class)
    cout << "Width: " << b.width << endl;  // ✅ Accessing private member
    cout<<" x "<<b.x<<endl; // Public members Can be accessed directly without Friend function definition 
}
int main() {
    Box box1(50);
    printWidth(box1);  // ✅ Works due to friend function
    return 0;
}
🔹 Output
Width: 50
✅ Even though width is private, printWidth can access it.

//////////////////////////////////////////////////////////////////////////////////////////////////////////////

📌 4️⃣ friend Class (One Class Accessing Private Members of Another)
✅ A whole class can be made a friend, giving all its member functions access.

🔹 Example: One Class as Friend
#include <iostream>
using namespace std;
class Engine {
private:
    int horsepower;
public:
    Engine(int hp) : horsepower(hp) {}
    friend class Car;  // Declare Car as a friend class
};
class Car {
public:
    void showEnginePower(Engine e) {
        cout << "Engine Power: " << e.horsepower << " HP" << endl;  // ✅ Accessing private data
    }
};
int main() {
    Engine engine(250);
    Car car;
    car.showEnginePower(engine);  // ✅ Works due to friend class
    return 0;
}
🔹 Output
Engine Power: 250 HP
✅ Class Car can access horsepower of Engine, even though it is private!

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

📌 5️⃣ friend Member Function of Another Class
✅ Instead of making the entire class a friend, we can make only a specific function of another class a friend.

🔹 Example: Friend Function in Another Class
#include <iostream>
using namespace std;
class Car;  // Forward declaration
class Engine {
private:
    int horsepower;
public:
    Engine(int hp) : horsepower(hp) {}
    friend void Car::showPower(Engine e); // Friend member function of Car
};

class Car {
public:
    void showPower(Engine e) {
        cout << "Car's Engine Power: " << e.horsepower << " HP" << endl;  // ✅ Accessing private data
    }
};
int main() {
    Engine engine(300);
    Car car;
    car.showPower(engine);  // ✅ Works due to friend function
    return 0;
}
🔹 Output
Car Engine Power: 300 HP
✅ Only showPower() is a friend function of Engine, not the whole Car class!
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

📌 6️⃣ friend Function for Operator Overloading
✅ friend is used when overloading operators that need access to private data.
🔹 Example: Overloading + Operator
#include <iostream>
using namespace std;
class Complex {
private:
    int real, imag;
public:
    Complex(int r, int i) : real(r), imag(i) {}
    friend Complex operator+(Complex c1, Complex c2); // Friend function for operator overloading
    void display() {
        cout << real << " + " << imag << "i" << endl;
    }
};
Complex operator+(Complex c1, Complex c2) {        // Friend function definition
    return Complex(c1.real + c2.real, c1.imag + c2.imag);
}
int main() {
    Complex c1(2, 3), c2(4, 5);
    Complex c3 = c1 + c2;  // ✅ Using overloaded + operator
    c3.display();
    return 0;
}
🔹 Output
6 + 8i
✅ The + operator can access private real and imag because it’s a friend function.

////////////////////////////////////////////////////////////////////////////////////////////////////////////////
✅  Why Does a Member Function Contain Only One Argument in Operator Overloading, 
    While a Non-Member Function (Friend Function) Contains Two ??

1️⃣ Member Function Operator Overloading
When overloading an operator as a member function, the left-hand operand of the operator (i.e., the object before the operator) 
 is implicitly passed as this, so we only need to pass the right-hand operand explicitly.

Example: Overloading + as a Member Function
#include <iostream>
using namespace std;
class Complex {
private:
    int real, imag;
public:
    Complex(int r, int i) : real(r), imag(i) {}

    // Overloading + as a member function
    Complex operator+(const Complex& other) {
        return Complex(real + other.real, imag + other.imag);
    }
    void display() {
        cout << real << " + " << imag << "i" << endl;
    }
};
int main() {
    Complex c1(2, 3), c2(4, 5);
    Complex c3 = c1 + c2;  // c1 calls operator+, c2 is passed as argument
    c3.display();
    return 0;
}
📌 What Happens in c1 + c2?
c1.operator+(c2) is called.
The left operand (c1) is implicitly passed as this.
c2 is explicitly passed as other.

Inside the function:->
return Complex(real + other.real, imag + other.imag);
real is actually this->real (i.e., c1.real).
other.real refers to c2.real.

✅ Why Does It Have Only One Argument?
Because the left-hand operand (c1) is already known inside the member function via this, we only need to pass the right-hand operand (c2) explicitly.

2️⃣ Friend Function (Non-Member Function) Operator Overloading
If we overload an operator as a friend function, it is not a member of the class. Therefore, it does not have access to this, and both operands must be passed explicitly.

Example: Overloading + as a Friend Function
#include <iostream>
using namespace std;

class Complex {
private:
    int real, imag;
public:
    Complex(int r, int i) : real(r), imag(i) {}

    // Friend function for operator overloading
    friend Complex operator+(const Complex& c1, const Complex& c2);

    void display() {
        cout << real << " + " << imag << "i" << endl;
    }
};

// Overloading + as a non-member function
Complex operator+(const Complex& c1, const Complex& c2) {
    return Complex(c1.real + c2.real, c1.imag + c2.imag);
}

int main() {
    Complex c1(2, 3), c2(4, 5);
    Complex c3 = c1 + c2;  // Calls the friend function
    c3.display();
    return 0;
}
📌 What Happens in c1 + c2?
The function operator+(c1, c2) is called.
Both c1 and c2 are explicitly passed to the function.
Inside the function:
cpp
Copy
Edit
return Complex(c1.real + c2.real, c1.imag + c2.imag);
c1.real refers to the real part of c1.
c2.real refers to the real part of c2.
✅ Why Does It Have Two Arguments?
Because it is not a member function, it does not have access to this. So, it needs both operands explicitly to perform the operation.

🔍 Key Differences Between Member and Friend Function Overloading
Feature	                  Member Function	                          Friend Function (Non-Member)
Number of Arguments	      1	                                          2
Why?	Left operand is passed implicitly as this, 
so only the right operand needs to be passed explicitly.	No implicit this, so both operands must be explicitly passed.

Access to Private Members?	Yes (directly, since it's a member).	Yes (only if declared as friend).
How It's Called?	     c1 + c2 → c1.operator+(c2)             	c1 + c2 → operator+(c1, c2)

🚀 When to Use Which?
Use a Member Function When:
The left-hand operand must be an instance of the class.
You only need one explicit argument.
Example: c1 + c2 where c1 is the calling object.
Use a Friend Function When:
You need both operands explicitly (e.g., when the left operand is not an instance of the class).
You need to allow implicit type conversion on the left operand.
Example: 5 + c1 (integer + complex) would not  work with a member function but works with a friend function.

🎯 Final Summary
Member function: Uses only one argument because the left-hand operand is implicitly this.
Friend function: Uses two arguments because both operands must be passed explicitly.


