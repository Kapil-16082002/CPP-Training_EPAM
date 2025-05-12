Operator overloading allows giving additional meanings to the operators when they are used with user-defined data types (like objects).
For example, we can make use of the addition operator (+) for string class to concatenate two strings.
We know that the task of this operator is to add two operands. 
So a single operator ‘+’, when placed between integer operands, adds them and when placed between string operands, concatenates them.

For example, using + to add two objects of a class.
Complex c1(3, 4), c2(2, 5);
Complex c3 = c1 + c2;  // Calls overloaded operator+

✅🔹 Why Use Operator Overloading?
Increases Reusability - Operators can be defined for multiple data types.
Enhances Code Readability - Allows natural syntax for objects.
Encapsulates Behavior - Ensures proper data handling inside the class.

✅Why Use Operator Overloading? 
It makes your custom objects interact more naturally. For example, if you define a Vector class:
Vector v1(1, 2), v2(3, 4);
Vector result = v1 + v2;  // Overloaded 'operator+'
Such operations improve code readability and allows developers to use objects much like primitive data types.


✅Rules for Operator Overloading

You cannot create new operators. You can only overload existing ones.
Certain operators cannot be overloaded (::, .*, ., sizeof, typeid, etc.).
At least one operand should be a user-defined type.
Overloaded operators must comply with their usual precedence and associativity.

✅Operators can be overloaded as a member function or as a friend function.
   🔸 Member Function Overloading-
   1.Used when first operand is the calling object (this pointer).
   2.Requires only one parameter for binary operators.
   class ClassName {
   public:
       ReturnType operatorOp(ParameterType obj) {
           // Custom operation
       }
   };
   🔸 Friend Function Overloading-
   1.Used when first operand is NOT the calling object.
   2.Requires two parameters for binary operators.
   class ClassName {
   public:
       friend ReturnType operatorOp(ParameterType obj1, ParameterType obj2);
   };  

   ✅🔹 Types of Operators That Can Be Overloaded
   Operator Type	   Examples	            Overloadable?
   Arithmetic	       + - * / %	         ✅ Yes
   Relational	       == != < > <= >=	     ✅ Yes
   Logical	            `&&	
   Bitwise	           `&	^ ~ << >>`
   Assignment	        = += -= *= /=	    ✅ Yes
   Unary	            ++ -- - +	        ✅ Yes 
   Function Call	     ()	                ✅ Yes
   Subscript	         []              	✅ Yes
   Pointer Dereference	 *	                ✅ Yes
   Pointer Member Access  ->	            ✅ Yes
   Stream Insertion/Extraction	<< >>	    ✅ Yes
   New/Delete	              new delete	✅ Yes

   🚫 Operators that CANNOT be overloaded:
   :: (Scope resolution)
   .* (Pointer to member access)
   sizeof (Size of object)
   ?: (Ternary/Conditional)
   typeid (Type information)
   const_cast, static_cast, etc.
 /////////////////////////////////////////////////////////////////////////////////////////////////////////////////
 
 1️⃣ Arithmetic Operator Overloading (+, -, *, /)->

1.The operator+ function is used to overload the + operator.
2.You can overload binary operators for adding:
  Two objects of the same class.
  An object and a basic datatype (e.g., int).
  An object and a user-defined class.

#include <iostream>
using namespace std;
class Complex {
private:
    int real, imag;
public:
    Complex(int r = 0, int i = 0) : real(r), imag(i) {}
    // Overloading + using a member function
    Complex operator+(const Complex& other) {
        return Complex(real + other.real, imag + other.imag);
    }
    void display() { cout << real << " + " << imag << "i" << endl; }
};
int main() {
    Complex c1(3, 4), c2(2, 5);
    Complex c3 = c1 + c2;  // interpretd as, Complex c3 = c1.operator+(c2) ;
    c3.display();  // Output: 5 + 9i
    return 0;
}
Final Summary->
Member function operator+ is called with c1 as the calling object and c2 as the argument.
The function returns a new Complex object containing the sum of c1 and c2.
The returned object is assigned to c3 using the copy constructor.

////////////////////////////////////////////////////////////////////////////////////////////////////////////////
2️⃣ Relational Operator Overloading (==, !=, <, >)
👉 Example: Overloading == for Comparing Objects
class Complex {
public:
    int real, imag;
    Complex(int r, int i) : real(r), imag(i) {}
    bool operator==(const Complex& other) {          // Overloading ==
        return (real == other.real && imag == other.imag);
    }
};
int main() {
    Complex c1(2, 3), c2(2, 3);
    if (c1 == c2) cout << "Equal" << endl; // interpreted as, if (c1.operator==(c2))
    else cout << "Not Equal" << endl;
    return 0;
}
Final Summary->
c1 calls the overloaded operator== function.
c2 is passed as an argument to the function.
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
Overloading the Assignment (=) Operator ->
the assignment operator (=) is used to copy the values from one object to another. 
By default, C++ provides a shallow copy for the assignment operator, which can cause issues when dealing with dynamic memory allocation.
To solve this, we overload the assignment operator to perform deep copies and handle special cases like self-assignment.

🔹 Syntax for Overloading = Operator
The assignment operator (=) must be overloaded as a member function, and its prototype is:
ClassName& operator=(const ClassName& other);
✅ It takes a const reference to another object to prevent unnecessary copying.
✅ Returns *this to allow chained assignment (a = b = c).

🔹 Example: Default vs. Overloaded Assignment Operator
🔸 Default Assignment Operator (Shallow Copy Issue)
#include <iostream>
#include <cstring>
using namespace std;
class String {
private:
    char* str;
public:
    String(const char* s) {   // Constructor
        str = new char[strlen(s) + 1];
        strcpy(str, s);
    }
    
    void display() { cout << str << endl; }

    ~String() { delete[] str; }  // Destructor
};

int main() {
    String s1("Hello");
    String s2("World");
    
    s2 = s1;  // Default assignment (shallow copy)
    
    s1.display();  // Hello
    s2.display();  // Hello (but shares same memory!)

    return 0;
}
🔹 Problem:
The default = operator does a shallow copy, meaning s1 and s2 share the same memory.
When s2 goes out of scope, it deletes the shared memory, causing dangling pointers.
✅ Solution: We must overload = to create a deep copy.

🔹 Overloading Assignment Operator (=)
✅ Corrected Example with Deep Copy
#include <iostream>
#include <cstring>
using namespace std;

class String {
private:
    char* str;
public:
    String(const char* s) {   // Constructor
        str = new char[strlen(s) + 1];
        strcpy(str, s);
    }

    // Overloading Assignment Operator
    String& operator=(const String& other) {
        if (this != &other) {  // Prevent self-assignment
            delete[] str;  // Free existing memory
            
            str = new char[strlen(other.str) + 1];  // Allocate new memory
            strcpy(str, other.str);  // Copy data
        }
        return *this;  // Return current object for chaining
    }

    void display() { cout << str << endl; }

    ~String() { delete[] str; }  // Destructor
};

int main() {
    String s1("Hello");
    String s2("World");

    s2 = s1;  // Calls overloaded assignment operator

    s1.display();  // Hello
    s2.display();  // Hello (Separate memory now!)

    return 0;
}
🔹 Key Fixes
✅ Self-assignment check: if (this != &other)
✅ Deallocate existing memory before assigning new one.
✅ Deep copy by allocating new memory.

🔹 Assignment Operator in Derived Classes (Inheritance)
If a class is derived from another, we must ensure proper copying of base class members.

📌 Example: Overloading = in an Inherited Class
#include <iostream>
using namespace std;

class Base {
protected:
    int x;
public:
    Base(int val) : x(val) {}
    Base& operator=(const Base& other) {
        if (this != &other) {
            x = other.x;
        }
        return *this;
    }
};

class Derived : public Base {
private:
    int y;
public:
    Derived(int val1, int val2) : Base(val1), y(val2) {}
    // Overloading assignment operator
    Derived& operator=(const Derived& other) {
        if (this != &other) {
            Base::operator=(other);  // Call base class assignment operator
            y = other.y;
        }
        return *this;
    }
    void display() { cout << "x: " << x << ", y: " << y << endl; }
};

int main() {
    Derived d1(10, 20), d2(30, 40);
    d2 = d1;  // Calls overloaded assignment operator
    d2.display();  // x: 10, y: 20
    return 0;
}
✅ Ensures base class members are copied correctly.


////////////////////////////////////////////////////////////////////////////////////////////////////////////////

3️⃣ Unary Operator Overloading (++, --)
👉 Example: Overloading Prefix (++obj) & Postfix (obj++)

class Counter {
private:
    int value;
public:
    Counter(int v) : value(v) {}
    Counter& operator++() {     // Prefix increment (++obj)
        ++value;
        return *this;
    }
    Counter operator++(int) {   // Postfix increment (obj++)
        Counter temp = *this;
        value++;
        return temp;
    }
    void display() { cout << "Value: " << value << endl; }
};
int main() {
    Counter c(5);
    ++c;  // Calls prefix
    c.display();  // Value: 6

    Counter c2 = c++;  // Calls postfix
    c.display();  // Value: 7
    c2.display(); // Value: 6
    return 0;
}
🔹 What If You Return *this Instead of temp in Postfix ??????????
If you modify operator++(int) like this:
Counter operator++(int) {
    ++value;
    return *this;  // ⚠️ Wrong! Returns updated value, not old value
}
Corrected Version:
Counter operator++(int) {
    Counter temp = *this;  // Save old value
    value++;  // Increment current object
    return temp;  // Return old value
}
🔹 Key Difference Between Prefix & Postfix
Type	            Function Signature	                         Execution Order
Prefix (++obj)	    Counter& operator++()	                    Increment first, then return
Postfix (obj++)   	Counter operator++(int)	                    Return old value first, then increment
👉 Important Observations:
✔ Prefix (++obj) is faster because it modifies and returns the object directly.
✔ Postfix (obj++) is slower because it creates a temporary object to hold the previous value.
✔ Postfix function must take an int dummy parameter to differentiate from the prefix.

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
3️⃣ Unary Operator Overloading ( --)

🔹 Overloading -- Operator (Prefix & Postfix)
We can overload the decrement operator (--) in two ways:
  Prefix Decrement (--obj): First decreases the value, then returns the object.
  Postfix Decrement (obj--): First returns the original value, then decreases it.
🔸 Syntax for Overloading Unary --
ReturnType operator--();      // Prefix Decrement
ReturnType operator--(int);   // Postfix Decrement (int is a dummy parameter)
🔹 Example: Overloading -- (Prefix and Postfix)

class Counter {
private:
    int value;
public:
    Counter(int v) : value(v) {}
    Counter& operator--() {   
        --value;  // Decrease value first
        return *this;
    }
    Counter operator--(int) {   
        Counter temp = *this;  // Save original state
        value--;  // Decrease value
        return temp;  // Return old state
    }
    void display() { cout << "Value: " << value << endl; }
};
int main() {
    Counter c(5);
    --c;   // Prefix Decrement
    c.display();  // Value: 4

    Counter c2 = c--;   // Postfix Decrement
    c.display();  // Value: 3
    c2.display(); // Value: 4 (old state)

    return 0;
}
🔹 Explanation
Operator	Syntax	Behavior
Prefix (--obj)	--c;	Decrements first, then returns updated value.
Postfix (obj--)	c--;	Returns original value first, then decrements.

