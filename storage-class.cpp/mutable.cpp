✅The mutable storage class specifier in C++ allows a member of an object to be modified even if the object is declared as const. 
Normally, if an object is declared as const, the values of its data members cannot be altered. 
However, with the mutable keyword, an exception to this rule is created.

//mutable can only be used with non-static data members because static members are shared and not specific to a single object instance.

Example 1: Using mutable with Lambdas
In C++ lambdas, the mutable keyword allows modification of captured variables, which are otherwise immutable by default.
#include <iostream>
int main() {
    int x = 10;

    // Lambda captures 'x' by value, but mutable allows modifying its copy
    auto modifyX = [x]() mutable {
        x += 5; // Allowed due to 'mutable'
        std::cout << "Inside Lambda, Updated x: " << x << std::endl;
    };
    modifyX(); // Calls the lambda, modifies local x inside
    std::cout << "Outside Lambda, Original x: " << x << std::endl;

    return 0;
}
Output:
Inside Lambda, Updated x: 15
Outside Lambda, Original x: 10

Explanation:
x is captured by value, so the lambda works on its own copy of x.
The mutable keyword allows the modification of the captured copy inside the lambda expression.

//---------------------------------------------------------------------------------------------------------------

Example 2: Modifying Mutable Member in a Const Object
#include <iostream>
#include <string>

class Logger {
private:
    mutable int logCount; // logCount is mutable, so it can be modified in const methods
    std::string message;
public:
    Logger(const std::string& msg) : message(msg), logCount(0) {}

    void displayMessage() const {
        ++logCount;  // Modify mutable variable logCount even in a const function
        std::cout << "Message: " << message << " | Log Count: " << logCount << "\n";
    }
    int getLogCount() const {
        return logCount;
    }
};
int main() {
    const Logger logger("Hello, Mutable!");
    
    // Since logger is const, we cannot normally modify its state, but mutable allows exceptions
    logger.displayMessage();
    logger.displayMessage();

    std::cout << "Total Log Count: " << logger.getLogCount() << std::endl;
}
Output:
Message: Hello, Mutable! | Log Count: 1
Message: Hello, Mutable! | Log Count: 2
Total Log Count: 2

✅Explanation of the Code:
Mutable Member:
logCount is marked as mutable, meaning it can be modified in a const context.

Const Method:
The displayMessage function is a const method. While such methods cannot modify regular members, they are allowed to modify mutable members.

Const Object:
logger is declared as const, so you cannot modify regular members. However, the mutable member logCount can still be updated.

//------------------------------------------------------------------------------------------------------------------

Disadvantages:
1. Violation of Const-Correctness
2. Limited to Non-Static Members: not for non-static members
3.Multithreading and Concurrency Issues
In multi-threaded programs, the use of mutable can be dangerous 
Because it allows modifications of data members in what should otherwise be const, potentially leading to race conditions or undefined behavior.
#include <thread>
#include <iostream>

class Counter {
public:
    mutable int count = 0;
    void increment() const {
        ++count; // Mutable allows modification, but it's not thread-safe
    }
};
void threadFunction(const Counter& counter) {
    for (int i = 0; i < 100000; ++i) {
        counter.increment();
    }
}

int main() {
    Counter counter;

    std::thread t1(threadFunction, std::ref(counter));
    std::thread t2(threadFunction, std::ref(counter));

    t1.join();
    t2.join();

    std::cout << "Final Counter Value: " << counter.count << std::endl;

    return 0;
}
Output (Non-deterministic):
The final value of counter.count may not be as expected because the mutable member is not thread-safe, leading to undefined behavior.
