✅Functors in C++:

A functor (short for function object) in C++ is an object that acts like a function. 
This is achieved by overloading the operator() (the function call operator) in a class or struct. 
Functors encapsulate behavior and can store state, making them much more flexible and powerful than regular functions or function pointers.


The Execution of Functors Happens at Runtime:

1.When you call a functor using the overloaded operator() (e.g., functorObject()), that function-like behavior is executed at runtime.
Functors are just objects, and the invocation is resolved like any other function call during the execution of the program.

2.Functors Are Defined at Compile-Time:
The creation of the functor object and its type must be known at compile-time, as the compiler needs to instantiate the class and ensure type safety. For example:
struct Multiply {
    int operator()(int x, int y) const {
        return x * y;
    }
};
Multiply multiply;  // The functor is defined at compile-time
int result = multiply(3, 4);  // Runtime call
Static (Compile-Time) vs Dynamic (Run-Time) Behavior:



✅Why Functors?
Functors are a natural mechanism to emulate function behavior while offering several additional advantages:

1.Encapsulation:
Functors are a way to encapsulate both data (state) and behavior (logic) in a single reusable unit (the object).

2.Flexibility:
Unlike functions, functors can hold state (stored inside the class instance). This allows dynamic configuration and reusable logic.

3.Code Reusability:
Functors enable clean, reusable code by allowing customizable and parameterizable behavior to be passed around in algorithms (e.g., custom sorting).

4.Better Than Function Pointers:
Unlike function pointers, functors benefit from type safety and the ability to carry internal state.

5.Integration with STL:
Functors are heavily used in the Standard Template Library (STL) to customize algorithms like std::sort, std::for_each, etc.

6.Cleaner Callback Design:
Functors are a good alternative for callbacks, especially in modern C++.


✅Basic Example of Functors
#include <iostream>
using namespace std;
class Print {
public:
    void operator()(int x) const {  // Overloading the () operator
        cout << "Printing value: " << x << endl;
    }
};
int main() {
    Print printObj;  // Create a functor object
    printObj(10);    // translated by the compiler to: printObj.operator()(10);

    return 0;
}
Output:
Printing value: 10
Here, printObj(10) looks like a function call, but behind the scenes, the operator() of the Print class is invoked.

/*  
✅Internal Working:
1.Overloading operator():
The operator() is called the function call operator in C++.
By overloading this operator, the object of the Print class can behave like a function.
Whenever the object is used with parentheses, () (e.g., printObj(10)), the overloaded operator() member function will be invoked.

2.When printObj(10) is invoked, the object printObj calls the overloaded operator(). 
This means:
printObj(10); is internally equivalent to:  printObj.operator()(10);


*/
#include <iostream>
using namespace std;

class Print {
public:
    // First operator() - Single integer
    void operator()(int x) const {
        cout << "Printing single value: " << x << endl;
    }
    // Second operator() - Two integers, prints their sum
    void operator()(int x, int y) const {
        cout << "Printing sum of values: " << (x + y) << endl;
    }
};
int main() {
    Print printObj;  // Create a functor object (function object)
    printObj(10);  // Calls operator()(int x)
    printObj(15, 25);  // Calls operator()(int x, int y)
    return 0;
}

//-----------------------------------------------------------------------------------------------------------------

#include <iostream>
using namespace std;

class Multiplier {
    int factor;  // Internal state (factor to multiply by)
public:
    Multiplier(int f) : factor(f) {}
    int operator()(int x) const {
        return x * factor;
    }
};
int main() {
    Multiplier multiplyBy2(2);  // Set factor = 2
    Multiplier multiplyBy3(3);  // Set factor = 3

    cout << multiplyBy2(5) << endl;  // Output: 10
    cout << multiplyBy3(5) << endl;  // Output: 15

    return 0;
}

//=================================================================================================================

✅Use Cases of Functors:
1. Custom Sorting in STL
Functors can be used as custom comparator objects to define sorting behavior for STL algorithms like std::sort.

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Compare {
public:
    // Custom comparison logic for sorting
    bool operator()(int a, int b) const {
        return a > b;  // Sort in descending order
    }
};

int main() {
    vector<int> nums = {5, 3, 8, 1, 7};
    sort(nums.begin(), nums.end(), Compare()); // Use functor for custom sorting
}
Output:
8 7 5 3 1

✅2. Passing Parameters to STL Algorithms
Functors allow state to be maintained, so they are convenient for tasks like accumulating data, printing elements, etc.

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// Functor to accumulate the sum of elements
class Accumulate {
    int sum;
public:
    Accumulate() : sum(0) {}
    void operator()(int x) {
        sum += x;
        cout << "Adding: " << x << ", Current Sum: " << sum << endl;
    }
    int getSum() const { return sum; }
};
int main() {
    vector<int> nums = {1, 2, 3, 4, 5};

    Accumulate acc;  // Create functor object

    // Use for_each (applies functor to each element)
    for_each(nums.begin(), nums.end(), acc);

    cout << "Total Sum: " << acc.getSum() << endl;
}
Output:
Adding: 1, Current Sum: 1
Adding: 2, Current Sum: 3
Adding: 3, Current Sum: 6
Adding: 4, Current Sum: 10
Adding: 5, Current Sum: 15
Total Sum: 15


✅3. Callback Mechanisms
Functors can also serve as callback functions where dynamic behavior is needed.
#include <iostream>
using namespace std;
class Callback {
public:
    void operator()(const string& msg) {
        cout << "Callback executed with message: " << msg << endl;
    }
};
// Function that accepts a functor-like callback
void executeCallback(const string& message, Callback callback) {
    callback(message);
}
int main() {
    Callback callbackObj;
    executeCallback("Hello from callback!", callbackObj);
    
    return 0;
}
Output:
Callback executed with message: Hello from callback!


✅4. Stateful Generators
Functors are useful for generating stateful sequences.

#include <iostream>
using namespace std;

class Counter {
    int start;
public:
    Counter(int s) : start(s) {}

    int operator()() {
        return start++;
    }
};
int main() {
    Counter countFrom10(10);
    // Generate the next 5 numbers
    for (int i = 0; i < 5; ++i) {
        cout << countFrom10() << " ";
    }
    return 0;
}
Output:
10 11 12 13 14

✅Advantages of Functors:
1.Statefulness:
Unlike regular functions, functors can maintain internal state variables across calls.

2.Reusability:
Reusable components with customized behavior, such as passing to STL algorithms.

3.Efficient Integration with STL:
Built to seamlessly work with STL algorithms like std::sort, std::find_if, std::transform, std::for_each, etc.

4.Type Safety:
Functors are type-checked during compilation, ensuring safer code than function pointers.

5.Encapsulation:
Code logic and state can be beautifully encapsulated into a single object.
Disadvantages of Functors

6.More Boilerplate Code:

Requires defining classes and overloading operator () for even simple tasks, which can increase verbosity.

7.Readability:
For simple tasks, functors can make the code more complex and less intuitive compared to inline lambdas.

8.Runtime Overhead:
Using functors can generally have slightly more memory usage compared to function pointers (because of object state).
Functors vs. Lambdas
