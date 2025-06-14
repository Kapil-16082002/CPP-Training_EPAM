✅Namespace in C++?
A namespace in C++ is a declarative region that allows grouping of identifiers (such as classes, functions, variables, and objects)to give a unique name.
It prevents name conflicts in large programs, especially when working with multiple libraries.

✅Why Use Namespaces?
Avoids Naming Conflicts: When multiple libraries or modules define the same function or variable name, namespaces help differentiate them.
Grouping same functionality: Groups related functions, classes, and objects under a logical name.

✅Namespace Syntax:
Namespaces are declared using the namespace keyword, followed by the namespace name and its enclosing scope {}.

#include <iostream>
using namespace std;
namespace MathOperations {
    int add(int a, int b) { return a + b; } // Addition
    int multiply(int a, int b) { return a * b; }
}
int add(int a, int b) { return a - b; } // Subtraction

int main() {
    // way:1
    cout << "Sum (Global add): " << add(10, 50) << endl;   // Accessing global `add`
    cout << "Sum (Namespace add): " << MathOperations::add(10, 5) << endl;  // Calls namespace `add`
    cout << "Product: " << MathOperations::multiply(4, 5) << endl;  // Calls namespace `multiply`
    
    //way:2 work fine
    cout << "Sum (Global add): " << add(10, 50) << endl;  // Accessing global `add`
    using namespace MathOperations;                   // Brings MathOperations::add into scope
    cout << "Product: " << multiply(4, 5) << endl;   // Calls MathOperations::multiply  

    
    /*  will give error: call of overloaded ‘add(int, int)’ is ambiguous
    using namespace MathOperations;  // Brings MathOperations::add into scope
    cout << "Sum (Namespace add): " << add(10, 5) << endl;  // Calls MathOperations::add
    cout << "Product: " << multiply(4, 5) << endl;          // Calls MathOperations::multiply  
    */
    return 0;
}

//==================================================================================================================

✅using Keyword
The using keyword bring specific identifiers or entire namespaces into the current scope.

Example: Bringing Specific Identifiers into Scope
namespace Math {
    int square(int x) {
        return x * x;
    }
}
int main() {
    using Math::square; // Bring specific identifier into scope
    std::cout << "Square: " << square(4) << std::endl;
    return 0;
}


Bringing the Entire Namespace into Scope
namespace Math {
    int square(int x) {
        return x * x;
    }
    int cube(int x) {
        return x * x * x;
    }
}
int main() {
    using namespace Math; // Bring the entire namespace into scope
    std::cout << "Square: " << square(4) << std::endl;
    std::cout << "Cube: " << cube(3) << std::endl;
    return 0;
}


//==================================================================================================================

✅Nested Namespaces
You can nest namespaces to create logical hierarchies.
namespace Company {
    namespace Department {
        void employeeTask() {
            std::cout << "Employee task handled by Department." << std::endl;
        }
    }
}
int main() {
    Company::Department::employeeTask(); // Access the nested namespace
    return 0;
}

//==================================================================================================================

✅Anonymous Namespace
An anonymous namespace is used to restrict identifiers to the current file. 
Identifiers in an anonymous namespace are implicitly treated as having static linkage (internal linkage).

namespace {
    void internalFunction() {
        std::cout << "This is an internal function." << std::endl;
    }
}
int main() {
    internalFunction();  // No need to use namespace prefix
    return 0;
}
Here, internalFunction() cannot be accessed from other files in the program.

//================================================================================================================

✅Common Namespace Use Cases:
✅1.Grouping same functionality:
#include <iostream>
#include <string>
using namespace std;

namespace Maths_operations {  // Namespace for mathematical operations
    int add(int a, int b) {
        return a + b;
    }
    int multiply(int a,int b){
        return a*b;
    }
}
namespace String_operations {  // Namespace for string operations
    void print_string(string s){
        for(auto it:s){
            cout<<it;
        }
        cout<<endl;
    }
    string combine_same_string(string s){
        return s+s;
    }

}
int main() {
  
   // using Namespace for mathematical operations
    String_operations::print_string("kapil");
    String_operations::combine_same_string("kapil");
    
    // Using Maths_operations namespace
    std::cout<<Maths_operations::add(6,7)<<endl;
    std::cout<<Maths_operations::multiply(6,7)<<endl;
    
}
//=================================================================================================================

2. Handling Name Conflicts
Namespaces avoid name collisions between identifiers with the same name.

#include <iostream>

// Namespace A
namespace LibraryA {
    void print() {
        std::cout << "Print from LibraryA" << std::endl;
    }
}
// Namespace B
namespace LibraryB {
    void print() {
        std::cout << "Print from LibraryB" << std::endl;
    }
}
int main() {
    LibraryA::print(); // Specify which namespace to use
    LibraryB::print();

    return 0;
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

✅using namespace std;
1. using namespace std;  instructs the compiler that the program is using all the names in the std(standard) namespace by default.
   meaning you don't have to prefix std:: before standard library names
2. std (short for "standard") is the default namespace in the C++ Standard Library.
3. All standard functions, objects, classes, and variables in C++ are defined inside the std namespace.
Examples include:
   Objects: cout, cin, endl
   Functions: getline, sort, max, min
   Classes: string, vector, map
4.When you use using namespace std;, all functions, classes, and variables from the std namespace are brought into the global scope.
#include <iostream>
using namespace std;
int main() {
    cout << "Hello, World!" << endl;  // No need to write std::cout or std::endl
    return 0;
}

Without using namespace std;:
#include <iostream>
int main() {
    std::cout << "Hello, World!" << std::endl;  // Must explicitly add std::
    return 0;
}

✅Advantages of Using using namespace std;

1.Readability:
For simple programs with no naming conflicts, skipping the std:: prefix can make the code cleaner and easier to read.
For Example:
using namespace std;
cout << "Hello" << endl;

is shorter and easier to read compared to:

std::cout << "Hello" << std::endl;

✅Disadvantages or Risks of Using using namespace std;
1. Naming Conflicts:

using namespace std;
int count = 10;  // User-defined variable
// If std::count (from `<algorithm>`) is also used, conflicts may arise.

using namespace std;
void vector() { 
    // Your own function
}
int main() {
    vector<int> nums = {1, 2, 3}; // Ambiguity: std::vector vs user-defined vector
    return 0;
}

2.Unpredictable Behavior in Headers:
NEVER use using namespace std; inside a header file.
Header files are meant to be included by multiple source files. 
If a header contains using namespace std;, it automatically imports all symbols from the std namespace into every file that includes it. 
This can lead to unpredictable conflicts.

//Header File.1 (myheader.h)
#ifndef MYHEADER_H
#define MYHEADER_H

#include <iostream>
#include <algorithm> // For std::count

// Introducing `using namespace std;` in the header
using namespace std;
#endif

//Source File.2 (main.cpp)
#include "myheader.h"

int count = 42; // User-defined variable named "count"

int main() {
    vector<int> nums = {1, 2, 3, 1, 1};
    // Using std::count from the algorithm library, but conflicts with user-defined "count"
    std::cout << "Count of 1s: " << count(nums.begin(), nums.end(), 1) << std::endl;
    return 0;
}
Outcome:
The compiler gets confused when resolving count(nums.begin(), nums.end(), 1) because it cannot decide whether to use the user-defined count or the std::count function. 
This leads to compilation errors or unintended behavior.

The inclusion of using namespace std; in the header file introduces ambiguity.
The program has two conflicting definitions for count:
std::count from <algorithm> (a function to count elements in a range).
int count = 42; (a user-defined variable).


//==================================================================================================================
✅Questions:

✅What happens if you do not use using namespace std; in a program that uses cout, cin, or other standard library components?
Answer:
Without using namespace std;, you must explicitly use std:: prefix.
Example:

std::cout << "Hello World!" << std::endl;  // Must use `std::`
Without the std:: prefix or using namespace std;, the program will not compile.

//----------------------------------------------------------------------------------------------------------------

✅. Is it necessary to use using namespace std; in every program?
Answer:
No, it’s not necessary. Instead of using namespace std;, you can explicitly qualify standard library names with std::.
Example:
std::vector<int> vec;  // Instead of writing `using namespace std;` and then `vector<int> vec;`

//-----------------------------------------------------------------------------------------------------------------

✅Can you use using namespace std; selectively for specific components instead of the entire namespace?
Yes, you can use the using directive selectively for specific entities to avoid importing the entire std namespace.
Example:
using std::cout;
using std::endl;

cout << "Hello World!" << endl;

//----------------------------------------------------------------------------------------------------------------

✅Why should we avoid writing using namespace std; in header files?
Including using namespace std; in header files pollutes the global namespace for all files that include the header, leading to potential naming conflicts and ambiguous behavior.
Instead, explicitly qualify standard library names (e.g., std::vector, std::string) within the header file.