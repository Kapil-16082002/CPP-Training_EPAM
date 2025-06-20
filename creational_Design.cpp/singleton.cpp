
//what are design principles?? why design principle??
Design Pattren are guidelines or principles that help developers to write clean, readable, maintainable, scalable, and efficient software solutions.
These basically are foundation for designing software that are modular, well-structured, and easy to understand, modify, and extend over time.

Why Design Principles?
Design principles are important because they:

✅Improve Code Quality: Encourage writing readable, reusable, and maintainable code.
Reduce Complexity: Help manage and reduce codebase complexity.
Enable Scalability: Ensure systems can adapt and grow with changing requirements.
Promote Reusability: Help avoid duplication and enable effective use of software components.
Prevent Bugs: Minimize errors by adhering to proven architectural guidelines.

//================================================================================================================

✅What is Creational Design Pattern?
Creational design patterns are a category of design patterns in software development that generally focus on the process of object creation. 
They ensure that the creation of objects is flexible, reusable, and scalable while hiding the object creation logic from the client code.


✅Key Benefits of Creational Design Patterns:
Encapsulation of Object Creation: Hides the details of how objects are created, providing flexibility to change the creation process later.
Decoupling: Decouples the client code from the specific classes it uses, allowing the code to work with abstractions rather than concrete implementations.
Scalability: Enables the system to handle complex object creation logic efficiently.
Code Reusability: Promotes reusable and modular object creation logic.

Singleton Design Pattern :
The Singleton Design Pattern ensure that there is only one instance of the class that is shared throughout the program. 

Steps to Implement Singleton :
Private Constructor: The constructor is private so that new objects cannot be created from outside the class.
Static Instance: A static member variable is used to store the sole instance of the class.
Public Access Method: Provide a public static method that returns the instance of the class.
Deleted Copy Constructor and Assignment Operator to prevent copying or assigning the Singleton instance.

//------------------------------------------------------------------------------------------------------------------

✅Basic Implementation (Lazy Initialization - Non Thread-Safe)
#include <iostream>

class Singleton {
private:                        //instance is pointer to a Singleton object.
    static Singleton* instance; // Static pointer to the Singleton instance. instance is private to ensure that no external code or class can directly access or modify it.
    Singleton() {}              // Private constructor to prevent direct instantiation
public:
    // Public static method to access the Singleton instance
    static Singleton* getInstance() {
        if (instance == nullptr) {        // Instance created when needed (lazy initialization)
            instance = new Singleton();
        }
        return instance;
    }
    void showMessage() {
        std::cout << "Singleton Instance!" << std::endl;
    }
    // Delete the copy constructor and assignment operator to prevent cloning
    Singleton(const Singleton&) = delete; //  explicitly deletes the copy constructor functionality for the Singleton class.
    Singleton& operator=(const Singleton&) = delete;//  explicitly deletes the copy assignment operator functionality for the Singleton class.
};

// static member  must Initialize outside the class
Singleton* Singleton::instance = nullptr;// Singleton* indicates the type of the instance variable, which is a pointer to a Singleton object.
                                        //Singleton::instance specifies that this instance variable belongs to the Singleton class.
int main() {
    Singleton* singleton = Singleton::getInstance();
    singleton->showMessage();
    /* 
    Singleton* singleton1 = Singleton::getInstance();
    Singleton* singleton2 = Singleton::getInstance();
    std::cout << "Address of singleton1: " << singleton1 << std::endl;
    std::cout << "Address of singleton2: " << singleton2 << std::endl;
    Output:
    Address of singleton1: 0x5588444b3e80
    Address of singleton2: 0x5588444b3e80
    Both pointers have the same memory address, proving that they refer to the same singleton instance.
    Variables singleton1 and singleton2 are just pointers (references) to the single instance; they are not creating new instances. 
    */

    return 0;
}
✅Explanation:
Singleton::instance is a static member, initialized as nullptr.
getInstance() checks if instance is nullptr. If true, it creates the instance.
By making the constructor private, clients cannot instantiate objects directly.
Copy constructor and assignment operator are deleted to avoid cloning of the instance.
This implementation is lazy-initialized, i.e., the instance is created only when getInstance() is called for the first time.

Drawback:
Not Thread-Safe: In a multithreaded environment, two threads might create multiple instances simultaneously when accessing getInstance() at the same time.


✅Question 1: Why is Singleton* instance static and private?
Answer:
instance is declared as static because a singleton ensure that  there is only one instance of the class that is shared throughout the program. 
By making instance static, it exists globally for the entire lifetime of the program and is shared across all calls to Singleton::getInstance().
Without the static keyword, instance would be an instance variable, and each instance of the Singleton class would have its own copy of instance, thereby defeating the singleton purpose.
Private:
instance is private to ensure that no external code or class can directly access or modify it. 
This enforces controlled access to the singleton instance via the public getInstance() method.
This is a core principle of encapsulation, ensuring that the management of the singleton instance remains within the Singleton class.


✅Question 2: Why is static Singleton* getInstance() static?
Answer:
Static method requirement:
The getInstance() method is static because it is called without requiring an existing instance of the Singleton class. 
For example:
Singleton* singleton = Singleton::getInstance();
If getInstance() were not static, you would need an instance of Singleton to call this method, defeating the purpose of lazy initialization since you would need an instance to retrieve another instance.

Design requirement:
The Singleton pattern is designed to ensure that all parts of the program access the same instance of the Singleton class. 
Making getInstance() static allows it to be available globally and ensures that it controls access to the single shared instance


Question 3: What Happens Without delete? 
Singleton(const Singleton&) = delete;   
Singleton& operator=(const Singleton&) = delete;
If you do not include these delete statements, the compiler automatically generates the following functions:

A default copy constructor: Performs a shallow copy.
A default copy assignment operator: Copies the content of one object into another.


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////


✅Thread-Safe Singleton (with Mutex Lock)
To make the Singleton thread-safe, we can use a mutex to synchronize access to the getInstance() method.
#include <iostream>
#include <mutex>

class Singleton {
private:
    static Singleton* instance; // Static pointer to the Singleton instance
    static std::mutex mtx;      // Mutex to ensure thread safety
    Singleton() {}              // Private constructor
public:
    // Public static method to access the Singleton instance
    static Singleton* getInstance() {
        std::lock_guard<std::mutex> lock(mtx); // Lock to synchronize access
        if (instance == nullptr) {            // Instance created lazily
            instance = new Singleton();
        }
        return instance;
    }
    void showMessage() {
        std::cout << "Thread-Safe Singleton Instance!" << std::endl;
    }
    // Delete the copy constructor and assignment operator
    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;
};
// Initialize static members
Singleton* Singleton::instance = nullptr;
std::mutex Singleton::mtx;

int main() {
    Singleton* singleton = Singleton::getInstance();
    singleton->showMessage();
    return 0;
}
Key Points:
std::mutex: A mutex (mtx) is used to synchronize access to the getInstance() method.
std::lock_guard: Ensures automatic locking and unlocking of the mutex during the execution of getInstance().
This implementation works safely in multithreaded environments.

Drawback:
The overhead of locking and unlocking the mutex can hurt performance, even after the instance is initialized.

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

✅Double-Checked Locking for Performance Optimization
To reduce the overhead of locking after the instance has been created, the Double-Checked Locking technique can be used.

#include <iostream>
#include <mutex>

class Singleton {
private:
    static Singleton* instance;
    static std::mutex mtx;
    Singleton() {} // Private constructor
public:
    static Singleton* getInstance() {
        if (instance == nullptr) {           // First check (without locking)
            std::lock_guard<std::mutex> lock(mtx);
            if (instance == nullptr) {       // Second check (with locking)
                instance = new Singleton();
            }
        }
        return instance;
    }
    void showMessage() {
        std::cout << "Singleton Instance with Double-Checked Locking!" << std::endl;
    }
    // Delete the copy constructor and assignment operator
    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;
};
// Initialize static members
Singleton* Singleton::instance = nullptr;
std::mutex Singleton::mtx;

int main() {
    Singleton* singleton = Singleton::getInstance();
    singleton->showMessage();

    return 0;
}
Key Points:
The instance is checked twice:
First without locking to avoid the overhead of acquiring a lock.
Second with locking to ensure the instance is created safely.
Prevents unnecessary locking and improves runtime performance.

////////////////////////////////////////////////////////////////////////////////////////////////////////////////

✅Eager Initialization Singleton
//In an eager singleton implementation, the instance is created at the time of class loading, avoiding the need for lazy initialization.
An eager singleton is a variation of the Singleton pattern where the instance of the Singleton class is created immediately, at the time when the class is loaded into memory. 
This happens before the program or application explicitly accesses the singleton instance via getInstance().

This is the opposite of a lazy singleton, where the instance is only created when it is first requested (using lazy initialization).

Advantages:
1.Thread Safety by Default: The instance is created once, at class loading, and is never re-created.
2.Performance: Accessing the instance is slightly faster because it doesn’t require checking or creating it on demand.

Disadvantages:
1.Memory Used Even When Not Needed: If the singleton is never actually used, memory will still be allocated for it, which can waste resources.

When to Use an Eager Singleton: 
1.You are confident the singleton will definitely be required.
2.You want a simple, thread-safe, and low-maintenance design.


#include <iostream>
class Singleton {
private:
    static Singleton* instance;
    Singleton() {} // Private constructor to prevent direct instantiation
public:
    static Singleton* getInstance() {
        return instance; // Instance is created eagerly
    }
    void showMessage() {
        std::cout << "Eagerly Initialized Singleton Instance!" << std::endl;
    }
    // Delete the copy constructor and assignment operator
    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;
};
// Initialize the static instance eagerly
//when this line executes, an instance of the Singleton is created.
Singleton* Singleton::instance = new Singleton();//The key part making it "eager" is this line:

int main() {
    Singleton* singleton = Singleton::getInstance();
    singleton->showMessage();

    return 0;
}
Key Points:
The instance is created at the time of class initialization.
Simple and thread-safe, as there’s no need for synchronization mechanisms.
May lead to wasted resources if the instance is never used.

Eager vs. Lazy Singleton
Aspect	               Eager Singleton	                                        Lazy Singleton
Instance Creation	  Happens as soon as the class is loaded.	                 Happens only when getInstance() is called for the first time.
Initialization Code	  No condition (direct initialization).	                     Uses a condition to check if an instance exists (e.g., if (instance == nullptr)).
Performance at Start  Slightly higher startup time due to early creation.	     More efficient at startup since no instance is created unless needed.
Thread Safety	     Thread-safe by design (single instance is created eagerly and globally).	Requires thread-safety mechanisms (e.g., mutex or std::call_once) to avoid race conditions during lazy initialization.
Memory Usage	     The singleton instance always occupies memory, even if unused.	         Memory is used only when the singleton is actually needed.
Use Case	         Ideal for use cases where the singleton instance will definitely be needed, such as logging services or configuration managers.	Ideal for cases where the singleton may not always be required, optimizing memory and performance.


Improving Your Eager Singleton Code
Though your code works fine, here’s a slightly better version with best practices (using std::unique_ptr for better resource management)
#include <iostream>
#include <memory> // For std::unique_ptr

class Singleton {
private:
    static std::unique_ptr<Singleton> instance;
    Singleton() {} // Private constructor to prevent direct instantiation
public:
    static Singleton* getInstance() {
        return instance.get(); // returns a raw pointer (Singleton*),Return the pre-created instance
    }
    void showMessage() {
        std::cout << "Eagerly Initialized Singleton Instance!" << std::endl;
    }
    // Delete the copy constructor and assignment operator
    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;
};
// Initialize the static instance eagerly
std::unique_ptr<Singleton> Singleton::instance = std::make_unique<Singleton>();

int main() {
    Singleton* singleton = Singleton::getInstance();
    singleton->showMessage();
    return 0;
}
Output:
Eagerly Initialized Singleton Instance!

Benefits of the Updated Code:
Memory-Safe: The use of std::unique_ptr ensures the singleton instance is automatically destroyed when the program exits.
Modern C++ Features: Following modern C++ conventions.




///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

C++11 Static Local Variable (Thread-Safe by Default)
Since C++11, the initialization of static local variables is thread-safe. 

In C++11 and beyond, the initialization of static local variables is guaranteed to be thread-safe. 
This means:
If two or more threads call getInstance() at the same time, only one thread will initialize the instance. 
Other threads will wait until the initialization is complete.

#include <iostream>
class Singleton {
private:
    Singleton() {} // Private constructor to prevent direct instantiation
public:
    static Singleton& getInstance() {
        static Singleton instance; // Thread-safe static local variable (C++11)
        return instance;       //  instance is a static local object (Singleton), not a pointer.
    }
    /* 
    Why Return Singleton& Instead of Singleton*?
    Returning a reference (Singleton&) offers the following advantages in this specific implementation:
1. No Need for Dynamic Allocation
In the getInstance() method, the singleton instance is created as a static local variable:
static Singleton instance;
Static local variables are allocated automatically on the stack (or as part of static memory) and do not require dynamic memory allocation (new).
Since there is no need to manage memory manually, you don't need to return a pointer. 
Instead, you can simply return a reference to the stack-allocated object.
    */
    void showMessage() {
        std::cout << "C++11 Singleton Instance!" << std::endl;
    }
    // Delete the copy constructor and assignment operator
    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;
};
int main() {
    Singleton& singleton = Singleton::getInstance();
    singleton.showMessage();

    /* you can also do like this:
    static Singleton* getInstance() {
        static Singleton instance; // Thread-safe static local variable (C++11)
        return &instance;          // Return the address of the static instance
    }
    Singleton* singleton = Singleton::getInstance(); // Get singleton instance as a pointer
    singleton->showMessage();                        // Use pointer to call the method 
    */
    return 0;
}
Key Points:
The instance is declared as a static local variable, which is thread-safe in C++11 and later.
This is the recommended implementation in modern C++ due to its simplicity and thread-safety advantages.

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

C++11 Static Local Variable (Thread-Safe by Default):
static local variables are thread-safe by default because the compiler guarantees that their initialization is done exactly once.
If multiple threads try to initialize the variable simultaneously, only one thread can initialization the static Local Variable , while other threads wait until its complete. 

Static Local Variable Behavior in C++11:
A static local variable is created only once and persists for the entire duration of the program.
After the instance is initialized the first time, if we call getInstance() multiple times, simply return the already-created instance.

In C++11 and beyond, the initialization of static local variables is guaranteed to be thread-safe. 
This means:
If two or more threads call getInstance() at the same time, only one thread will initialize the instance. 
Other threads will wait until the initialization is complete.








