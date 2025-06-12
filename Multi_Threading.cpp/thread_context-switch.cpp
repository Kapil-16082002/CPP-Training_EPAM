✅A thread is a smallest (lightweight) unit of execution inside a process. 
 Multiple threads can run concurrently within a single process and share memory (like global variables or heap memory). 
 This makes threading fast but also risky due to race conditions.
Multithreading in C++ refers to the ability of a program to execute multiple threads concurrently.

In C++ (OOPs approach), we create threads using std::thread (from the <thread> library), which enables multi-threading in C++.

✅Process:  A process is an independent program in execution.
Multiple processes can run concurrently on a system, but they generally operate independently of one another.
Key Features of a Process:
1.Independent Memory Space: Each process has its own separate memory space (address space).
2.Inter-process Communication (IPC):
Since processes run in separate memory spaces, they must communicate via mechanisms such as pipes, sockets, shared memory, or message queues.

1. Synchronous Programming
In synchronous programming, tasks are executed sequentially, one after the other. 
The program waits for a task to finish before moving on to the next. 
If a task takes a long time (e.g., a file download or database query), the thread executing it is blocked, stopping the programs progression until the task is complete.

2. Asynchronous Programming
In asynchronous programming, tasks can be executed concurrently or in parallel, depending on the system, without waiting for each task to finish before starting the next one. 
When a task is initiated (e.g., downloading a file), it runs in the background, and the program can proceed without being blocked.



✅Types of thread
1. Based on Purpose:
Threads can be categorized based on their purpose or functionality in the application:
    1.Worker Threads: Perform background tasks or heavy computations in parallel with the main programs execution.
    2.Event Listener/Watcher Threads: Monitor and respond to external events or I/O, such as incoming network messages or file changes.
    3.UI Threads: In GUI applications, threads responsible for managing user interface updates.
    4.Real-Time Threads: Threads assigned to handle time-critical operations with strict deadlines.
    5.Main Thread: The thread that starts when the program begins execution.

2. Based on Thread Lifecycle :
  1.Joinable Threads: A thread that can be joined with the join() function, meaning the parent thread waits for its completion before proceeding. 
  2.Detached Threads: A thread that runs independently in the background, and its resources are automatically cleaned up when it completes. 
    You use the detach() method to make a thread detached:

3.
  1.OS-Level Threads: These are platform-native threads, managed and scheduled by the operating system. The std::thread in C++ maps directly to OS-level threads.
  2.User-Level Threads (Fibers): Threads implemented at the user space (not directly managed by OS). These are lightweight and may be used in libraries or frameworks for cooperative multitasking (like coroutines).

4. Based on Synchronization and Asynchronous Tasks: 
  1.Mutex-Protected Threads: Threads using std::mutex, std::lock_guard, or std::unique_lock to coordinate access to shared resources.
  2.Condition Variable Threads: Threads that use std::condition_variable to wait or notify each other about specific conditions.
  3.std::async Threads: Launch a task asynchronously, returning a std::future to retrieve the result:


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

✅What is a Race Condition?
A race condition occurs in multithreaded programming when two or more threads manipulate(access) shared data simultaneously, and the outcome of the program depends on the order in which the threads execute. 
This unpredictability can lead to inconsistent or unintended results.
Example of a Race Condition
Imagine two threads incrementing a shared counter variable without any synchronization. Since both threads run concurrently without coordination, they may interrupt each other, leading to incorrect results.
#include <iostream>
#include <thread>

int counter = 0; // Shared resource
void incrementCounter() {
    for (int i = 0; i < 10; i++) {
        counter++; // Critical section
    }
}
int main() {
    std::thread t1(incrementCounter);
    std::thread t2(incrementCounter);

    t1.join();
    t2.join();

    std::cout << "Final Counter Value: " << counter << std::endl; // May not be 2000

    return 0;
}
Expected Output:
Final Counter Value: 20

Possible Output (due to a race condition):
Final Counter Value: 17

✅Whats happening here?
counter is a shared resource.
Two threads (t1, t2) are incrementing it.
Without the mutex, both threads could try to update counter at the same time, causing incorrect results (like skipped increments).

/* 
Synchronization in threading in C++ refers to the coordination of multiple threads to ensure that they operate correctly and do not interfere with one another, particularly when they access shared resources or critical sections of code. 
Without synchronization, race conditions, data corruption, or unexpected behavior could occur.
*/
✅Synchronization Techniques to Prevent Race Conditions:
To prevent race conditions in multithreaded programs, synchronization mechanisms are used. 
These techniques ensure that only one thread accesses the critical section (shared data) at a time.

1. Using std::mutex
2. Using std::unique_lock
3. Using std::atomic
4. Using std::condition_variable
5. Using Reader-Writer Locks (Shared Mutex)



//===================================================================================================================
✅Mutex:
A mutex (mutual exclusion) 
Mutual Exclusion  -> only one thread can access a shared resource (critical section) at a time. 
-> This prevents race conditions and ensures data consistency.
-> used to prevent multiple threads from accessing a shared resource simultaneously.

🔒 Mutex Lock
When a thread locks a mutex, it gains exclusive access to a shared resource (like a variable, file, or database). 
While the mutex is locked:
   No other thread can access that resource.
   If another thread tries to lock the same mutex, it will wait (block) until the mutex is unlocked.
Purpose: Prevent race conditions, where multiple threads try to modify the same resource at the same time, which could lead to inconsistent or unpredictable results.

🔓 Mutex Unlock
When a thread no longer using the shared resource, it unlocks the mutex:
This releases the lock, allowing other waiting threads to acquire it and access the resource.
Failing to unlock a mutex can cause deadlocks, where threads are stuck waiting forever.

//-----------------------------------------------------------------------------------------------------------

🔧  thread.join()?
join() is a function you call on a std::thread object to wait for that thread to finish execution.

std::thread t(worker);
t.join();  // wait for thread t to finish before continuing

🕓 Timeline:
Main Thread:  |------wait for t------|----continue after t---->
Thread t:     |--- running worker() ---|

🔑 Meaning:
"Hey, main thread — pause here and wait until this thread is running."

The main thread pauses at t.join() and waits until thread t finishes.
Ensures the thread completes before the program continues.

🧠 Why use join()?
✅ Ensures the thread finishes before the program moves forward.
✅ Prevents the program from exiting while a thread is still running.
✅ Helps avoid undefined behavior (like destructing a thread object that’s still running)

//--------------------------------------------------------------------------------------------------------------

🧠 What is detach() in C++?
detach() is a member function of the std::thread class in C++.
When a thread is detached using std::thread::detach(), it means the thread is separated from the main thread and run independently in the background. 
.detach() is used when you don’t want to wait — the thread runs independently, in the background.
It tells the system:
"Let this thread run on its own, I don’t want to wait for it or manage it anymore."

std::thread t(myFunction);
t.detach();  // Now runs independently

🕓 Timeline:
Main Thread:  |---continues immediately--->
Thread t:     |--- running in background ---|

🧠 Explanation:
The main thread doesn’t wait for thread t at all.
thread t runs in the background — this is fire-and-forget style.

Limitations:
If the main thread finishes execution (i.e., the main() function returns) too quickly, the entire program will terminate, also will not check whether the thread running in background has completed its work or not. 
Once the program terminates, the operating system cleans up all resources, including resources occupied by detached threads that have not completed yet.


//-------- difference between detach() and join()  -----------------------------------------------------------====

🧍‍♂️ Real-Life Analogy:
Imagine you give your friend a task:

✅ join() = You wait until your friend finishes the task.
You: "Hey, clean the room, and I’ll wait here until you're done."

✅ detach() = You tell your friend to do the task whenever they want and you leave.
You: "Hey, clean the room whenever. I’ve got other things to do."

📊 Summary Table
Feature	                      join()	                             detach()
Waits for thread	          ✅ Yes	                                ❌ No
Blocking	                  ✅ Yes (main stops and waits)	        ❌ No (main keeps going)
Control                    	  ✅ You manage the thread	            ❌ You lose control after detach
Use case	                  When result matters / must wait	      For background tasks (logging, etc.)
Risk	                      Very low	                              Risky if main ends too early
Reusable?	               ❌ Can't call again after join	        ❌ Can't call join after detach

⚠️ Important Note:
You cannot call both join() and detach() on the same thread. You must choose one.

//---------------------------------------------------------------------------------------------------------------

Common Example

#include <iostream>
#include <thread>
#include <mutex>

int counter = 0;
std::mutex mtx;

void increment() {
    for (int i = 0; i < 10000; ++i) {
        std::lock_guard<std::mutex> lock(mtx); // Lock mutex
        ++counter;
        // mutex automatically released when lock goes out of scope
    }
}
int main() {
    std::thread t1(increment);
    std::thread t2(increment);

    t1.join();
    t2.join();

    std::cout << "Counter: " << counter << std::endl;
}
Whats happening here?
counter is a shared resource.
Two threads (t1, t2) are incrementing it.
Without the mutex, both threads could try to update counter at the same time, causing incorrect results (like skipped increments).
std::lock_guard<std::mutex> lock(mtx); locks the mutex before modifying the counter.
When the thread is done with the critical section (modifying counter), the mutex is automatically released.

So what is mtx doing?
mtx is acting like a traffic light:
It lets only one thread at a time into the critical section (the part modifying shared data).
Other threads wait until the mutex is available.

mtx ensures that only one thread at a time can access or modify shared data (counter, in this case), preventing bugs due to race conditions. Without it, your program might behave unpredictably when run on multiple threads.
//---------------------------------------------------------------------------------------------------------------

#include <bits/stdc++.h>
#include <thread>
using namespace std;

void sum(){

    for (int i=0;i<=10;i++) cout<<i<<endl;
}
void print(){
    
    for (int i=20;i<=29;i++) cout<<i<<endl;
}
int main() {
    std::thread th(sum);
    std::thread pr(print);

    for (int i=30;i<=39;i++) cout<<i<<endl;
    th.join();
    pr.join();
	return 0;
}
Output:
There are infinite possible valid outputs because:
   cout is a shared resource.
   You’re not using mtx.lock() and mtx.unlock() in print() or sum().
   So threads interleave their output unpredictably.


⚠️ Disadvantages of this Code
❌ Issue	            🧠 Explanation
Race Condition	      Multiple threads writing to cout at the same time. Output becomes interleaved or corrupted.
Unpredictable Output  Output order is non-deterministic, making debugging harder.
No Synchronization	  You are not using mutex.lock()/unlock() or std::lock_guard. There's no protection around shared resources.
No Thread Control	 You rely entirely on the system  thread scheduling, which can vary between runs or platforms.
Output May Be Garbled	Two threads could be halfway through a cout operation simultaneously, producing mixed or unreadable lines.

//-----------------------     How to Fix code   ----------------------------------------------------------------------
You should protect shared resources (like cout) using std::mutex or std::lock_guard:

✅ 1. Synchronized Version using mutex
This ensures that only one thread prints at a time, keeping the output clean:

#include <iostream>
#include <thread>
#include <mutex>
using namespace std;
std::mutex mtx;

void sum() {
    mtx.lock();
    for (int i = 0; i <= 10; i++)  cout << i << endl;
    mtx.unlock();
}

void print() {
    mtx.lock();
    for (int i = 20; i <= 29; i++)  cout << i << endl;
    mtx.unlock();
}

int main() {
    thread th(sum);
    thread pr(print);

    mtx.lock();
    for (int i = 30; i <= 39; i++)  cout << i << endl;
    mtx.unlock();

    th.join();
    pr.join();
    return 0;
}
🧾 Output (always clean):
The blocks won’t mix, though their order (sum, print, or main first) may still vary:

//------------------------------------------------------------------------------------------------------------
🚀 2. Detached Thread Version
Let’s say you want one thread to run in the background (fire-and-forget), like print():

#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>
using namespace std;
std::mutex mtx;

void sum() {
    mtx.lock();
    for (int i = 0; i <= 10; i++)  cout << i << endl;
    mtx.unlock();
}
void print() {
    mtx.lock();
    for (int i = 20; i <= 29; i++) cout << i << endl;
    mtx.unlock();
}
int main() {
    thread th(sum);
    thread pr(print);
    pr.detach();  // 🔥 Run print() in background

    mtx.lock();
    for (int i = 30; i <= 39; i++)  cout << i << endl;
    mtx.unlock();

    th.join();

    // Add sleep to give detached thread time to finish
    this_thread::sleep_for(chrono::seconds(1));

    return 0;
}
⚠️ Notes:
pr.detach() means you don’t wait for it — it runs in the background.
You must make sure the thread has enough time to finish (hence the sleep).
Don’t access local resources after detaching, or it may crash.


//=================================================================================================================

✅Key Differences:   std::lock_guard<std::mutex>:     Manual mtx.lock() and mtx.unlock():

✅1.std::lock_guard<std::mutex>:
1.Automatic Resource Management:(No Explicit Lock/Unlock):
std::lock_guard is a RAII (Resource Acquisition Is Initialization) wrapper around a mutex. 
When the lock_guard object is created, it automatically locks the mutex, and when the object goes out of scope, it automatically unlocks the mutex.

2.Exception Safety:
RAII guarantees the mutex will be unlocked when the lock_guard object goes out of scope, even if an exception is thrown.
3.Deadlock Prevention:
Because the unlocking is guaranteed, it minimizes the risk of programmer error leading to deadlocks.
4.Non-Movable:
Objects of std::lock_guard cannot be moved or assigned.



✅2. Manual mtx.lock() and mtx.unlock():
mtx.lock();
// Critical section
mtx.unlock();
1. Manual Management Required:
You are responsible for explicitly locking and unlocking the mutex. If exception is thrown, the mtx.unlock() may not be called, leading to a deadlock.
2.Error-Prone:
Forgetting to call mtx.unlock() after mtx.lock() can cause undefined behavior and hangs. 
Similarly, double-locking the mutex will result in undefined behavior.


✅3.std::unique_lock<std::mutex>
1.std::unique_lock is also a RAII (Resource Acquisition Is Initialization) wrapper around a mutex.
When a std::unique_lock object is created, it will not lock the mutex immediately upon creation but if desired it can automatically lock the mutex upon creation
means it provide defered locking(flexibility of locking) upon object creation.

2.Unlocking allows:
You can manually unlock and relock the mutex while the unique_lock object is in scope.

2.Exception Safety:
RAII guarantees the mutex will be unlocked when the lock_guard object goes out of scope, even if an exception is thrown.

3.Deadlock Prevention:
Because the unlocking is guaranteed, it minimizes the risk of programmer error leading to deadlocks.
4..Movable:
std::unique_lock objects can be moved, making it possible to transfer ownership of the lock between different scopes or threads.

Example:
std::lock_guard<std::mutex> guard(mtx); // Mutex locked for the critical section

Example: Deferred Locking
#include <mutex>
std::mutex mtx;
void process_data() {
    std::unique_lock<std::mutex> lock(mtx, std::defer_lock); // Mutex not locked yet
    // Perform some non-critical operations
    lock.lock(); // Lock the mutex later when needed
    // Critical operations
    lock.unlock(); // Unlock manually , not necessary
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////


✅What is std::mutex::try_lock()?
try_lock() is a method(member function) of std::mutex class and works with only single mutex.
It allows a thread to lock a mutex without blocking (i.e., waiting) if the mutex is already locked by another thread.
If the mutex is:
unlocked: try_lock() locks it and returns true.
locked (already locked by another thread): try_lock() immediately returns false without blocking the thread.

Usecase:
This is especially useful in scenarios where you want your thread to continue doing other work if a resource is already being used by another thread, instead of waiting indefinitely for the mutex.

#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>

std::mutex mtx;  // Shared mutex to protect a critical section

void critical_section(int thread_id) {
    if (mtx.try_lock()) {  // Try to lock the mutex
        // If successful:
        std::cout << "Thread " << thread_id << " has locked the mutex.\n";
    
        mtx.unlock(); // Unlock the mutex after work is done
        std::cout << "Thread " << thread_id << " has unlocked the mutex.\n";
    } 
    else {
        // If unable to lock:
        std::cout << "Thread " << thread_id << " could not lock the mutex. Doing other work.\n";
    }
}
int main() {
    // Launch two threads
    std::thread t1(critical_section, 1);
    std::thread t2(critical_section, 2);

    // Wait for threads to finish
    t1.join();
    t2.join();

    return 0;
}

//=================================================================================================================

✅What is std::try_lock()?
std::try_lock() is a standard library function (free function) and works with multiple mutexes simultaneously.
Try to lock multiple mutexes in a deadlock-free manner without blocking.
Returns:
-1 , if all mutexes were successfully locked.
The index of the first mutex that could not be locked (0-based index) if locking fails.
If any mutex fails to lock, it will automatically unlock all previously locked mutexes.
Useful for deadlock prevention when trying to lock multiple mutexes at once.