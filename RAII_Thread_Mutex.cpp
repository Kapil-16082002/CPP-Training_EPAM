✅Resource Acquisition Is Initialization (RAII) in C++ ->
RAII (Resource Acquisition Is Initialization) is a C++ programming technique(Idiom) where resource management (such as memory, file handles, or locks) is tied to object lifetime. 
Resources are occupied during construction of object and released during the destruction of the object and ensures automatic resource management.

RAII helps in prevention of resource leakage and makes code safer and more maintainable.
Resources are released when the object goes out of scope (stack unwinding).
Ensures proper cleanup even in case of exceptions.

Use Cases of RAII :
1.Automatic Memory Management (Smart Pointers)
2.Avoids Dangling Issues: using  Smart Pointers
3.Improved Exception Safety: using  Smart Pointers
4.File Handling
5.Mutex Locking
6.Database Connection Management
7.Network Socket Management

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

RAII with Smart Pointers (Memory Management)->:
C++ provides smart pointers to manage dynamically allocated memory safely.

Example: Using std::unique_ptr
#include <iostream>
#include <memory>
class Resource {
public:
    Resource() { std::cout << "Resource Acquired\n"; }
    ~Resource() { std::cout << "Resource Released\n"; }
    void use() { std::cout << "Using Resource\n"; }
};
void smartPointerExample() {
    std::unique_ptr<Resource> ptr = std::make_unique<Resource>();
    ptr->use();
} // ptr goes out of scope and resource is released automatically.
/*
std::make_unique<Resource>() dynamically allocates an object of Resource class and returns a std::unique_ptr managing it.
std::unique_ptr<Resource> is a smart pointer that owns the allocated object (Resource).
ptr->use(); calls the use() method of Resource.
When ptr goes out of scope at the end of smartPointerExample(), its destructor automatically deletes the Resource object.

*/
int main() {
    smartPointerExample();
    return 0;
}
Output
Resource Acquired
Using Resource
Resource Released
Significance: No need to explicitly delete memory; it is managed automatically.

//----------------------------------------------------------------------------------------------------------------

Another Example: Using std::shared_ptr for Shared Ownership
Unlike std::unique_ptr, std::shared_ptr allows multiple smart pointers to share ownership of the same resource.
#include <iostream>
#include <memory>
class SharedResource {
public:
    SharedResource() { std::cout << "SharedResource Acquired\n"; }
    ~SharedResource() { std::cout << "SharedResource Released\n"; }
    void use() { std::cout << "Using SharedResource\n"; }
};

void sharedPointerExample() {
    std::shared_ptr<SharedResource> ptr1 = std::make_shared<SharedResource>();
    {
        std::shared_ptr<SharedResource> ptr2 = ptr1;  // Shared ownership
        std::cout << "Inside Block: ";
        ptr2->use();
    } // ptr2 goes out of scope, but ptr1 still owns the resource

    std::cout << "Outside Block: ";
    ptr1->use();
} // ptr1 goes out of scope, and resource is released automatically

int main() {
    sharedPointerExample();
    return 0;
}
Output:
SharedResource Acquired
Inside Block: Using SharedResource
Outside Block: Using SharedResource
SharedResource Released

How std::shared_ptr Works:
std::shared_ptr keeps a reference count of how many pointers are pointing to the same resource.
The resource is only deleted when the last shared_ptr goes out of scope.
Useful when multiple parts of a program need to access the same resource.

Summary
Smart Pointer	Ownership	       Auto Deletion	                    Use Case
std::unique_ptr	Single Ownership   Yes (when out of scope)	            For managing exclusive resources like file handles, sockets, etc.
std::shared_ptr	Shared Ownership   Yes (when last owner is destroyed)	For shared resources, e.g., caches or graphs where multiple objects share nodes.

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
A thread in C++ is a separate execution path that allows a program to run multiple tasks concurrently, improving efficiency and performance.
In C++ (OOPs approach), we create threads using std::thread (from the <thread> library), which enables multi-threading in C++.
#include <iostream>
#include <thread>  // For using std::thread
#include <unistd.h> // For `sleep()` function (POSIX systems like Linux)
#include <mutex>     // For std::mutex to prevent data races in multithreading

std::mutex mut;

void Threadfunc(int num) {
    // mut.lock();
    std::lock_guard<std::mutex> lg(mut);  // Automatically locks and unlocks
    for(int i = 0; i < 5; i++) {  
        std::cout << "I am in Thread " << num << std::endl;  
    }
    sleep(5);  //  Pause execution for 5 seconds (POSIX function)
    //mut.unlock(); 
}
int main() {
    std::thread t1(Threadfunc, 1);// Creates a thread `t1` and runs `Threadfunc(1)`
    std::thread t2(Threadfunc, 2);// Creates a thread `t2` and runs `Threadfunc(2)`
    t1.join(); // Wait for thread `t1` to finish
    t2.join(); // Wait for thread `t2` to finish
    return 0;
}
Explanation:
1.Locks the mutex using std::lock_guard<std::mutex>
                 Ensures that only one thread at a time executes the for loop safely.
                 std::lock_guard automatically unlocks the mutex when the function scope ends.
2.Loops 5 times, printing which thread is running.
3.Sleeps for 5 seconds (sleep(5))

This delays execution artificially to simulate some processing time.
//--------------------------------------------------------------------------------------------------------------

Mutex in C++ (Meaning & Explanation)
A mutex (mutual exclusion) 
Mutual Exclusion  -> only one thread can access a shared resource (critical section) at a time. 
This prevents race conditions and ensures data consistency.
used to prevent multiple threads from accessing a shared resource simultaneously.

Example: Using std::mutex to Prevent Race Conditions
#include <iostream>
#include <thread>
#include <mutex>

std::mutex mtx; // Mutex declaration
int counter = 0;

void increment() {
    mtx.lock(); // Lock the mutex
    counter++;  // Critical section (shared resource)
    std::cout << "Counter: " << counter << std::endl;
    mtx.unlock(); // Unlock the mutex
}
int main() {
    std::thread t1(increment);
    std::thread t2(increment);

    t1.join();
    t2.join();

    return 0;
}
Output (order may vary):
Counter: 1
Counter: 2
✅ Key Points:
std::mutex ensures only one thread modifies counter at a time.
lock() locks the resource, and unlock() releases it.
Prevents data corruption in multi-threaded programs.

//---------------------------------------------------------------------------------------------------------------

Using std::lock_guard for Safer Mutex Handling
Instead of manually calling lock() and unlock(), we can use std::lock_guard, which automatically locks and unlocks the mutex.

✅ Example: std::lock_guard for Safer Mutex Handling
#include <iostream>
#include <thread>
#include <mutex>

std::mutex mtx; // Mutex for mutual exclusion
int counter = 0;

void increment() {
    std::lock_guard<std::mutex> lock(mtx); // Automatically locks the mutex
    counter++;  
    std::cout << "Counter: " << counter << std::endl;
} // Automatically unlocks when going out of scope
int main() {
    std::thread t1(increment);
    std::thread t2(increment);

    t1.join();
    t2.join();

    return 0;
}
✅ Output (Ensures Proper Synchronization)
Counter: 1
Counter: 2
✅ Why Use std::lock_guard?
Automatic Locking & Unlocking – No need to manually call lock() and unlock().
Exception Safety – Ensures the mutex is always released, even if an exception occurs.
Simplifies Code – Reduces the chance of forgetting to unlock.


