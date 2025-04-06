
A move constructor allows the resources of an rvalue (temporary object) to be transferred to a new object instead of performing a deep copy.
The move constructor is designed to improve performance by eliminating unnecessary deep copies of objects.

🧠 Syntax of Move Constructor
ClassName(ClassName&& other);
The parameter is an rvalue reference (&&) to another object of the same type.
It usually steals the resources from the source object and nullifies the source.

💼 Use Cases
1.Returning large objects from functions
2.Passing large objects to functions by value
3.Storing objects in STL containers (e.g., std::vector)
        STL containers like std::vector make use of move semantics:
        std::vector<MyString> vec;
        vec.push_back(MyString("Temp"));  // move constructor used
STL containers like std::vector, std::map, etc., use move semantics to improve performance when resizing or returning large objects.
4.Transferring ownership (like std::unique_ptr)
5. Used when Object is an rvalue or std::move is applied


#include <iostream>
#include <cstring>
class MyString {
private:
    char* data;
public:
    // Constructor
    MyString(const char* str) {
        std::cout << "Simple Constructor called\n";
        data = new char[strlen(str) + 1];
        strcpy(data, str);
    }
    // Copy Constructor                  //Copy constructor duplicates the resource
    MyString(const MyString& other) {
        std::cout << "Copy constructor called\n";
        data = new char[strlen(other.data) + 1];
        strcpy(data, other.data);
    }
    // Move Constructor                  //Move constructor just takes the pointer and sets the original’s pointer to nullptr.
    MyString(MyString&& other) noexcept {
        std::cout << "Move constructor called\n";
        data = other.data;
        other.data = nullptr;
    }
    // Destructor
    ~MyString() {
        delete[] data;
    }
    void print() const {
        std::cout << (data ? data : "NULL") << "\n";
    }
};
MyString createString() {  //This is a function named createString that takes no arguments and returns a MyString object.
    MyString temp("Hello");   // This line calls the regular constructor, 
    return temp;  // Temp will be moved, not copied
    /*
Why This Is a Move and Not a Copy? Reason;
Reason:1
     temp in createString() is a temporary object (a local variable).
     When returning temp, the compiler can treat it as an rvalue.
     The move constructor takes an rvalue reference (MyString&&), which matches this temporary.
     So, data is moved (just a pointer assignment), and temp.data is set to nullptr to avoid double deletion.

Reason2:
Since temp is a local object and is being returned by value, C++ has the opportunity to optimize the return:
            1.In C++11 and later, this often uses move semantics instead of copy.
            2.So, the move constructor is invoked here to construct s1 from temp, rather than copying it.
            3.If the move constructor were not defined, then the copy constructor would be used instead.
    */
}
int main() {
     MyString s1 = createString();  // Uses move constructor
    s1.print();
}
Output:
Simple Constructor called
Hello


/*---------- why not Output:  Constructor called
                              Move constructor called
                              Hello??                  */
Explanation: Return Value Optimization (RVO)
Modern C++ compilers (like GCC, Clang, MSVC) apply an optimization called RVO (Return Value Optimization) or copy elision, where:
Instead of creating temp and then moving it to s1, the compiler constructs temp directly into s1's memory location.
So the move constructor is not called at all.
This is allowed and encouraged in the C++ standard (especially since C++17, where copy elision in some cases is mandatory).

👇✅ Want to force the move constructor?
You can disable RVO by doing something like:
int main() {
    MyString s1 = std::move(createString());  // Force move
    s1.print();
}
Output:
Constructor called
Move constructor called
Hello


Why mark a move constructor as noexcept?

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Move Semantics?
Move semantics is a C++ feature (introduced in C++11) that allows the resources of one object to be transferred (moved) to another, instead of copying them.

Why Use Move Semantics?
Faster: No need to duplicate resources (e.g., memory, files, sockets).
Safer: Avoids expensive deep copies.
Essential for modern C++: Used in std::vector, std::string, smart pointers, etc.

✅ 1. Move Semantics with std::vector
🔧 Code Example:
cpp
Copy
Edit
#include <iostream>
#include <vector>
#include <string>

int main() {
    std::vector<std::string> vec1;

    vec1.push_back("Apple");
    vec1.push_back("Banana");
    vec1.push_back("Cherry");

    std::vector<std::string> vec2 = std::move(vec1);  // Move vec1 into vec2

    std::cout << "vec1 size: " << vec1.size() << "\n";  // Should be 0 or unspecified
    std::cout << "vec2 contents:\n";
    for (const auto& fruit : vec2) {
        std::cout << fruit << "\n";
    }
}
🔍 What's Happening:
vec1's internal data is moved into vec2.

vec1 is now empty (but valid).

This avoids a deep copy of all strings.

✅ 2. Move Semantics in a Class Containing std::vector
Let’s say you have a custom class that holds a vector:

class FruitBasket {
public:
    std::vector<std::string> fruits;

    FruitBasket(std::vector<std::string> f) : fruits(std::move(f)) {
        std::cout << "Constructor with move\n";
    }
    FruitBasket(const FruitBasket& other) : fruits(other.fruits) {
        std::cout << "Copy constructor\n";
    }
    FruitBasket(FruitBasket&& other) noexcept : fruits(std::move(other.fruits)) {
        std::cout << "Move constructor\n";
    }
    void show() const {
        for (const auto& fruit : fruits)
            std::cout << fruit << " ";
        std::cout << "\n";
    }
};
int main() {
    std::vector<std::string> temp = {"Mango", "Peach", "Guava"};
    FruitBasket fb1(std::move(temp));  // Move vector into class
    FruitBasket fb2 = std::move(fb1);  // Move class

    fb2.show();  // Outputs the fruits
}
✅ Output:
Constructor with move
Move constructor
Mango Peach Guava 

💥 What You Learn Here:
std::move doesn’t actually move — it casts to rvalue so the move constructor/assignment can be invoked.
Containers like std::vector, std::string, std::map — all support efficient move operations.


//-------------------------------------------------------------------------------------------------------------------
🔹 1. Move Assignment Operator (operator=)

#include <iostream>
#include <string>

class LogBuffer {
public:
    std::string data;
    LogBuffer(const std::string& str) : data(str) {
        std::cout << "Constructor\n";
    }
    // Copy assignment
    LogBuffer& operator=(const LogBuffer& other) {
        std::cout << "Copy assignment\n";
        data = other.data;
        return *this;
    }
    // Move assignment
    LogBuffer& operator=(LogBuffer&& other) noexcept {
        std::cout << "Move assignment\n";
        data = std::move(other.data);
        return *this;
    }
    void print() {
        std::cout << "Data: " << data << "\n";
    }
};
int main() {
    LogBuffer a("Initial"); //✅ Constructor is called. Because you’re initializing a with a string literal → it implicitly converts to std::string, which binds to the constructor.
    LogBuffer b("Another");  //✅ Constructor is called again for b

    a = std::move(b);  // ✅ Move assignment operator is called
                       //   std::move(b) casts b to an rvalue → triggers the move assignment.
   //a = b; // if used a=b, before move then: Copy assignment operator is called
    a.print();  // a now holds "Another" because we moved it from b
    b.print();  // Might be empty
}
❗Bonus: What If You Did a = b; Instead?
If you replaced the move with:

a = b;
Then 
Copy assignment
Because b is an lvalue → triggers the copy assignment.


#include <iostream>
#include <string>
class LogBuffer {
public:
    std::string data;
    // Constructor
    LogBuffer(const std::string& str) : data(str) {
        std::cout << "Constructor\n";
    }
    // Copy constructor
    LogBuffer(const LogBuffer& other) : data(other.data) {
        std::cout << "Copy constructor\n";
    }
    // Move constructor
    LogBuffer(LogBuffer&& other) noexcept : data(std::move(other.data)) {
        std::cout << "Move constructor\n";
    }
    // Copy assignment
    LogBuffer& operator=(const LogBuffer& other) {
        std::cout << "Copy assignment\n";
        data = other.data;
        return *this;
    }
    // Move assignment
    LogBuffer& operator=(LogBuffer&& other) noexcept {
        std::cout << "Move assignment\n";
        data = std::move(other.data);
        return *this;
    }
    // Destructor
    ~LogBuffer() {
        std::cout << "Destructor: " << data << "\n";
    }
    void print() {
        std::cout << "Data: " << data << "\n";
    }
};
int main() {
    std::cout << "--- Original Construction ---\n";
    LogBuffer a("Alpha");

    std::cout << "--- Copy Construction ---\n";
    LogBuffer b = a;  // Calls copy constructor

    std::cout << "--- Move Construction ---\n";
    LogBuffer c = std::move(a);  // Calls move constructor

    std::cout << "--- Copy Assignment ---\n";
    LogBuffer d("Delta");
    d = b;  // Calls copy assignment

    std::cout << "--- Move Assignment ---\n";
    LogBuffer e("Echo");
    e = std::move(c);  // Calls move assignment

    std::cout << "--- Final States ---\n";
    a.print();
    b.print();
    c.print();
    d.print();
    e.print();
}
Output:
--- Original Construction ---
Constructor

--- Copy Construction ---
Copy constructor

--- Move Construction ---
Move constructor

--- Copy Assignment ---
Constructor
Copy assignment

--- Move Assignment ---
Constructor
Move assignment

--- Final States ---
Data:         ← moved-from (likely empty)
Data: Alpha
Data:         ← moved-from (likely empty)
Data: Alpha
Data: Alpha

--- Destructors (called in reverse order) ---
Destructor: Alpha
Destructor: Alpha
Destructor: Alpha
Destructor: Alpha
Destructor: 

⚠️ Notice:
Moved-from objects like a and c have empty data when destructed.
Destructors are called in reverse order of construction (e, d, c, b, a).

✅ Summary: When Each One Is Called
Code	                 What’s Called	            Reason
LogBuffer x("text")	     Constructor	          Direct construction from string
LogBuffer y = x;	     Copy constructor	      x is an lvalue
LogBuffer z = std::move(x);	Move constructor	  x is cast to rvalue
y = x;	                   Copy assignment	      x is lvalue
y = std::move(x);	      Move assignment	     x is rvalue

