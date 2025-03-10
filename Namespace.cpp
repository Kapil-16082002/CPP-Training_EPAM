Namespace in C++?
A namespace in C++ is a declarative region that allows grouping of identifiers (such as classes, functions, variables, and objects) under a unique name.
It prevents name conflicts in large programs, especially when working with multiple libraries.

Why Use Namespaces?
Avoids Naming Conflicts: When multiple libraries or modules define the same function or variable name, namespaces help differentiate them.
Better Code Organization: Groups related functions, classes, and objects under a logical name.
Prevents Name Pollution: Without namespaces, every identifier exists in the global scope, which can cause unintended conflicts.

#include <iostream>
using namespace std;
namespace MyNamespace {
    int x = 10;
    void display() {
        cout << "Inside MyNamespace: x = " << x << endl;
    }
}
int main() {
    MyNamespace::display();  // Accessing function inside the namespace
    return 0;
}
Output:
Inside MyNamespace: x = 10

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include <iostream>
using namespace std;

namespace MathOperations {
    int add(int a, int b) { return a + b; } // Addition
    int multiply(int a, int b) { return a * b; }
}
int add(int a, int b) { return a - b; } // Subtraction

int main() {
    // way:1
    cout << "Sum (Global add): " << add(10, 50) << endl;  // Accessing global `add`
    cout << "Sum (Namespace add): " << MathOperations::add(10, 5) << endl;  // Calls namespace `add`
    cout << "Product: " << MathOperations::multiply(4, 5) << endl;  // Calls namespace `multiply`
    
    /* will give error: call of overloaded ‘add(int, int)’ is ambiguous
    cout << "Sum (Global add): " << add(10, 50) << endl;  // Accessing global `add`

    using namespace MathOperations;  // Brings MathOperations::add into scope
    cout << "Sum (Namespace add): " << add(10, 5) << endl;  // Calls MathOperations::add
    cout << "Product: " << multiply(4, 5) << endl;          // Calls MathOperations::multiply  */
    
    //way2:
    using namespace MathOperations;  // Brings MathOperations::add into scope
    cout << "Sum (Namespace add): " << add(10, 5) << endl;  // Calls MathOperations::add
    cout << "Product: " << multiply(4, 5) << endl;          // Calls MathOperations::multiply  
    return 0;
}

/*#include <iostream>
using namespace std;

namespace {
    void greet(int a,int b) { cout << "Hello from an unnamed namespace! " <<a+b<< endl; }
}

int main() {
    greet(4,5);  // No need to use namespace prefix
    return 0;*/
//}
