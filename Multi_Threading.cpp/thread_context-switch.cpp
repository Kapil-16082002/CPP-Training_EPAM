✅A thread is a smallest (lightweight) unit of execution inside a process.
Multiple threads can run concurrently within a single process and share memory (like global variables or heap memory). 
This makes threading fast but also risky due to race conditions.
🔹 Thread Example:
Suppose there is one employee in the office:
That employee is doing multiple tasks at the same time:

1.Writing a report 📝
2.Responding to emails 📧
3.Attending a call 📞
Each of these tasks is a THREAD.


Multithreading in C++ refers to the ability of a program to execute multiple threads concurrently.
| Term            | Meaning                                               |
| --------------- | ----------------------------------------------------- |
| **Concurrency** | Tasks are in progress at the same time (interleaving) |
| **Parallelism** | Tasks run at the exact same time on multiple cores    |


| Aspect           | **Program**                                                                      | **Process**                                                                   |
| ---------------- | -------------------------------------------------------------------------------- | ----------------------------------------------------------------------------- |
| **Definition**   | A **program** is a passive set of instructions stored on disk (executable file). | A **process** is an active instance of a program that is currently executing. |
| **State**        | Static (not running).                                                            | Dynamic (running or ready to run).                                            |
| **Existence**    | Exists as a file (e.g., `.exe`, binary).                                         | Exists in main memory (RAM) while executing.                                  |
| **Execution**    | Cannot execute by itself.                                                        | Executes instructions of a program.                                           |
| **Memory**       | No memory allocated for execution.                                               | Has its own memory (code, stack, heap, data).                                 |
| **Resources**    | Does not use CPU, memory, or I/O.                                                | Uses CPU time, memory, files, and I/O resources.                              |
| **Multiplicity** | One program file can exist only once on disk.                                    | Multiple processes can be created from the same program.                      |
| **Lifetime**     | Permanent until deleted.                                                         | Temporary (created → executed → terminated).                                  |




In C++ (OOPs approach), we create threads using std::thread (from the <thread> library), which enables multi-threading in C++.

✅Process:  A process is an independent program in execution.
Multiple processes can run concurrently on a system, but they generally operate independently of one another.
Key Features of a Process:
1.Independent Memory Space: Each process has its own separate memory space (address space).
2.Inter-process Communication (IPC):
Since processes run in separate memory spaces, they must communicate via mechanisms such as pipes, sockets, shared memory, or message queues.

🔹Real-Life Example: Office Workspace
Think of a computer system as an office building 🏢.
Programs → Job descriptions or task manuals
Processes → Employees working on those jobs

🔹 Multiple Processes Running Concurrently
Imagine an office where many employees are working at the same time:
One employee is writing a report ✍️
Another is attending an online meeting 🎧
Another is checking emails 📧


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


//=================================================================================================================

✅What is a Race Condition?
A race condition occurs in multithreaded programming when two or more threads manipulate(access) shared data simultaneously, and the outcome of the program depends on the order in which the threads execute. 
This unpredictability can lead to inconsistent or unintended results.
Example of a Race Condition
Imagine two threads incrementing a shared counter variable without any synchronization. 
Since both threads run concurrently without coordination, they may interrupt each other, leading to incorrect results.
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

//==================       std::thread t(workerFunction)        =================================================


std::thread t(workerFunction);
What happens internally:

🧩 Step 1: std::thread object creation
std::thread t(...);
A C++ thread object (t) is created on the current thread’s stack
At this moment, t is just a handle / wrapper, not the actual OS thread


🧩 Step 2: Callable is stored
workerFunction
The function pointer / callable is:
Copied or moved
Stored inside the std::thread object

Arguments (if any) are decayed and copied
Example:
std::thread t(func, x, y);
➡ x and y are copied into internal storage


🧩 Step 3: OS thread is requested
std::thread internally calls platform-specific APIs
| OS      | Internal call      |
| ------- | ------------------ |
| Linux   | `pthread_create()` |
| Windows | `CreateThread()`   |
| macOS   | `pthread_create()` |


🧩 Step 4: New call stack is allocated

For the new thread:
Separate stack memory is allocated
Separate instruction pointer
Separate register set

💡 Each thread has:
Same code section
Same heap
Same global/static variables
Different stack


🧩 Step 5: Thread starts execution

OS scheduler decides when the new thread runs
Execution begins at an internal wrapper function

Wrapper calls:
workerFunction();
📌 Execution order is NOT guaranteed

🧩 Step 6: t becomes joinable

After successful creation:
t.joinable() == true

Meaning:
The thread is running or ready to run
Must call:
t.join() OR  t.detach()
Otherwise → ❌ std::terminate()



//=================================================================================================================

Declaration of std:: thread

1️⃣ Local (stack allocation) — MOST COMMON
void func() {
    std::thread t(workerFunction);
}
📍 t is allocated on the STACK of the calling thread (usually main).
Lifetime = scope of t
Destructor runs when t goes out of scope

Main Thread Stack
└── std::thread t   ← allocated here



2️⃣ Dynamic (heap allocation)
std::thread* t = new std::thread(workerFunction);

📍 t object is on the HEAP
You must call delete t
Still must call join() or detach() before 

Heap
└── std::thread object



3️⃣ Global / static allocation
std::thread t(workerFunction);   // global

📍 Allocated in static / global memory
Constructed before main()
Dangerous if not managed carefully


//================================================================================================================

Parameters of std::thread t(workerFunction)

1️⃣ First Parameter – Callable Object
✅ What can be passed as func
| Type                          | Example                            | How to pass to `std::thread`                         |
| ----------------------------- | ---------------------------------- | ---------------------------------------------------- |
| **Normal function**           | `void func(int, int);`             | `std::thread t(func, 10, 20);`                       |
| **Lambda**                    | `[](int a, int b){}`               | `std::thread t([](int a,int b){ /*...*/ }, 10, 20);` |
| **Function pointer**          | `&func`                            | `std::thread t(&func, 10, 20);`                      |
| **Functor (operator())**      | `struct F { void operator()(); };` | `std::thread t(F{});`                                |
| **Static member function**    | `Class::staticFunc`                | `std::thread t(Class::staticFunc, 10);`              |
| **Member function (special)** | `&Class::method`                   | `std::thread t(&Class::method, obj, 10);`            |


✅Example:
void func(int a, int b);
int main(){
std::thread t(func, 1, 2);
std::thread t([](int x){ std::cout << x; }, 10);
}
-------------------------------------------------------------------------------------------------------------------

✅ Example: Member Function with std::thread
Case 1️⃣: Passing object by value
#include <iostream>
#include <thread>
class Worker {
public:
    void doWork(int x) {
        std::cout << "Doing work with value: " << x << std::endl;
    }
};
int main() {
    Worker obj;
    // Member function thread
    std::thread t(&Worker::doWork, obj, 10);
    t.join();
    return 0;
}
🔍 What happens here?
&Worker::doWork → pointer to member function
obj → copied into the thread
10 → argument to doWork(int)

❌ Problems  1️⃣ By value — obj ❌ (Usually BAD)
Object is copied
Changes inside thread do NOT affect original object
Copy constructor must exist
Expensive for large objects

---------------------------------------------------------------------------------------------------------------

✅ Case 2️⃣Using pointer to object

int main() {
    Worker obj;
    std::thread t(&Worker::doWork, &obj, 10);
    t.join();
    return 0;
}
2️⃣ By pointer — &obj ⚠️ (Works, but risky)
⚠️ Issues:
Changes inside thread affects original object because thread works on the same object in memory.
No ownership semantics
Easy to create dangling pointer
Less expressive
Manual lifetime responsibility

💥 Dangerous case:
void startThread() {
    Worker obj;
    std::thread t(&Worker::doWork, &obj, 10);
    t.detach();   // 💥 obj destroyed, thread still running
}
→ Undefined Behavior

-------------------------------------------------------------------------------------------------------------
✅ Case 3️⃣: : Passing object by reference
int main() {
    Worker obj;
    // Pass object by reference
    std::thread t(&Worker::doWork, std::ref(obj), 10);
    t.join();
    return 0;
}
🔍 Why std::ref(obj)?
By default, std::thread copies arguments,std::ref() ensures no copy, real object is used

3️⃣ By reference — std::ref(obj) ✅ (BEST PRACTICE)
✅ Advantages
No copy
Same object shared
Safer than raw pointer
Works naturally with RAII + join()


✅ With std::cref
std::thread t(func, std::cref(value));  // no copy, read-only object.

Difference:
std::ref passes an object as a non-const reference allowing modification, 
whereas std::cref passes it as a const reference enforcing read-only access. 
Both prevent copying when used with std::thread, but neither provides thread safety.
------------------------------------------------------------------------------------------------------------------




2️⃣ Remaining Parameters – Arguments to Callable
All parameters after the callable are passed to the function.

std::thread t(func, x, y);
means internally:  func(x, y);


3️⃣ How Arguments Are Passed (VERY IMPORTANT)

🔹 By value (default)
int x = 5;
std::thread t(func, x);   // copy of x
Changes inside thread ❌ do NOT affect x.


🔹 By reference (use std::ref)
int x = 5;
std::thread t(func, std::ref(x));
Changes inside thread ✅ affect x.


🔹 By const reference, use  std::cref(x)
void func(const int& x);
std::thread t(func, std::cref(x));

//===================================================================================================================

✅Mutex:
A mutex (mutual exclusion) 
Mutual Exclusion  -> only one thread can access a shared resource (critical section) at a time.
-> This prevents race conditions and ensures data consistency.
-> used to prevent multiple threads from accessing a shared resource simultaneously.

🔒 Mutex Lock:
When a thread locks a mutex, it gains exclusive access to a shared resource (like a variable, file, or database). 
While the mutex is locked:
   No other thread can access that resource.
   If another thread tries to lock the same mutex, it will wait (block) until the mutex is unlocked.
Purpose: Prevent race conditions, where multiple threads try to modify the same resource at the same time, which could lead to inconsistent or unpredictable results.

🔓 Mutex Unlock:
When a thread no longer using the shared resource, it unlocks the mutex:
This releases the lock, allowing other waiting threads to acquire it and access the resource.
Failing to unlock a mutex can cause deadlocks, where threads are stuck waiting forever.

//---------------------------------------------------------------------------------------------------------------

🔧  thread.join()?
join() is a function you call on a std::thread object to wait for that thread to finish execution.
join() ensures that the child thread will finish execution before main program ends.

std::thread t(worker);
t.join();  // wait for thread t to finish execution before continuing

🔹 What happens to the main thread ? When t.join() is called:
✅ Main thread gets BLOCKED
The main thread stops executing and waits until workerFunction finishes execution.

🕓 Timeline:
Main Thread:  |------wait for t------|----continue after t---->
Thread t:     |--- running worker() ---|

🔑 Meaning:
"Hey, main thread — pause here and wait until this thread is running."

The main thread pauses at t.join() and waits until thread t finishes.
Ensures the thread completes before the program continues.


🧠✅ Advantages of using join():

1️⃣ Ensures thread completion
join() ensures that the child thread will finish execution before main program ends.
📌 Without join():
Program may terminate early.
Threads may be abruptly stopped.


2️⃣ Prevents undefined behavior:
/*
if main() thraed ends before child thread, then
Before main() ends:
1. Local objects are destroyed
2. t (std::thread object) destructor is called
std::thread destructor checks:

~thread() {
    if (joinable()) {
        std::terminate();
    }
}
❌ t is still joinable
💥 std::terminate() is called immediately
*/
If a thread object is destroyed without join() or detach(), the program calls std::terminate().
std::thread t(task);
// No join() or detach()
❌ Program crashes
✅ Using join() avoids this.
/*
🧠 Why does std::terminate() get called ?
According to the C++ standard:
If a std::thread object is destroyed while it is still joinable, the program calls std::terminate().

🔍 Internally (conceptual view)
~thread() {
    if (joinable()) {
        std::terminate();
    }
}
🚫 IMPORTANT CONSEQUENCE
The program never reaches a state where main() ends while the child thread keeps running.
The program is terminated immediately by std::terminate().

✅ Correct Comparison Table:
| Situation                      | Result                      |
| ------------------------------ | --------------------------- |
| No `join()` & no `detach()`    | 💥 `std::terminate()`       |
| `detach()` + destroyed objects | ❌ Undefined Behavior        |
| `join()`                       | ✅ Safe                      |
| `main()` returns               | Process exits, threads stop |

*/
3️⃣ Enables safe access to shared resources:
Ensures worker threads complete their updates
Main thread can safely read results after join()
t.join();
// Safe to use shared data now

4️⃣ Provides synchronization

join() acts as a synchronization point
Helps coordinate execution order between threads
🧠 Example:
Thread A finishes → join() → Thread B continues



//--------------------------------------------------------------------------------------------------------------

🧠 What is detach() in C++?
detach() is a member function of the std::thread class in C++.
When a thread is detached using std::thread::detach(), it means the thread is separated from the main thread and run independently in the background. 
.detach() is used when you don’t want to wait — the thread runs independently, in the background.
It tells the system:
"Let this thread run on its own, I don’t want to wait for it or manage it anymore."

std::thread::~thread() {
    if (joinable()) {   // false after t.detach(), this conditon always false for detach()
        std::terminate();
    }
    // destructor exits normally
}
std::thread t(myFunction);
t.detach();  // Now runs independently

🕓 Timeline:
Main Thread:  |---continues immediately--->
Thread t:     |--- running in background ---|

🧠 Explanation:
The main thread doesn’t wait for thread t at all.
thread t runs in the background — this is fire-and-forget style.

/* 
The destructor of std::thread simply checks joinable() and calls std::terminate() if true. 
After detach(), the thread is no longer joinable, so the destructor does nothing. 
Any undefined behavior after detach() is due to accessing objects whose lifetime has ended, not because of the destructor itself.
*/


Limitations:
If the main thread finishes execution (i.e., the main() function returns) too quickly, the entire program will terminate, also will not check whether the thread running in background has completed its work or not. 
Once the program terminates, the operating system cleans up all resources, including resources occupied by detached threads that have not completed yet.


//-------- difference between detach() and join()  -----------------------------------------------------------

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
➡️ Only one thread modifies counter at a time.
mtx is acting like a traffic light:
It lets only one thread at a time into the critical section (the part modifying shared data).
Other threads wait until the mutex is available.

mtx ensures that only one thread at a time can access or modify shared data (counter, in this case), preventing bugs due to race conditions. 
Without it, your program might behave unpredictably when run on multiple threads.

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


//========================  ✅std::lock_guard<std::mutex>  =======================================================


🔴Problems with Manual lock() / unlock() (BAD Practice)
❌ Problem 1: Exception Safety
mtx.lock();
throw std::runtime_error("oops"); //🔴 Mutex will stay locked forever → deadlock
mtx.unlock();


❌ Problem 2: Early Return
mtx.lock();
if (condition) return;  // unlock skipped ❌
mtx.unlock();



✅ std::lock_guard<std::mutex>:
1.Automatic Resource Management:(No Explicit Lock/Unlock):
std::lock_guard is a RAII (Resource Acquisition Is Initialization) wrapper around a mutex. 
When the lock_guard object is created, it automatically locks the mutex, and when the object goes out of scope, it automatically unlocks the mutex.

2.Exception Safety:
RAII guarantees the mutex will be unlocked when the lock_guard object goes out of scope, even if an exception is thrown.

3.Deadlock Prevention:
Because the unlocking is guaranteed, it minimizes the risk of programmer error leading to deadlocks.

4.Non-Movable:
Objects of std::lock_guard cannot be moved or assigned.

//-------------------------------------------------------------------------------------------------------------------

2️⃣ What Happens Internally:
std::lock_guard<std::mutex> lock(mtx);

🔹 Step 1: Object Creation (Stack Allocation)
lock is a local object
Allocated on the stack
Constructor is called immediately


🔹 Step 2: Mutex is Locked:
Inside lock_guard constructor:
explicit lock_guard(Mutex& m) : mutex(m) {
    mutex.lock();
}
✔ Mutex is locked
✔ Thread now owns the critical section
✔ Other threads trying to lock the same mutex will block


🔹 Step 3: Scope-Based Ownership
The mutex remains locked as long as lock exists
Lock lifetime = scope lifetime
Example:
{
    std::lock_guard<std::mutex> lock(mtx);
    // critical section
} // scope ends → destructor called


🔹 Step 4: Destructor Automatically Unlocks
When scope ends (even due to exception):
~lock_guard() {
    mutex.unlock();
}
✔ Mutex is always unlocked
✔ No chance of forgetting to unlock


3️⃣ Simplified Internal Implementation:
template <typename Mutex>
class lock_guard {
    Mutex& mtx;
public:
    explicit lock_guard(Mutex& m) : mtx(m) {
        mtx.lock();
    }
    ~lock_guard() {
        mtx.unlock();
    }
    // Copying is disabled
    lock_guard(const lock_guard&) = delete;
    lock_guard& operator=(const lock_guard&) = delete;
};
4️⃣ Why Copy is Disabled?
lock_guard(const lock_guard&) = delete;
Reason:
Two objects unlocking the same mutex = ❌ disaster
Mutex ownership must be unique


//======================  ✅3.std::unique_lock<std::mutex>  ======================================================

1.std::unique_lock is also a RAII (Resource Acquisition Is Initialization) wrapper around a mutex.
When a std::unique_lock object is created, it will not lock the mutex immediately upon creation but if desired it can automatically lock the mutex upon creation
means it provide defered locking(flexibility of locking) upon object creation.

2.Unlocking allows:
You can manually relock and unlock the mutex while the unique_lock object is in scope.

2.Exception Safety:
RAII guarantees the mutex will be unlocked when the lock_guard object goes out of scope, even if an exception is thrown.

3.Deadlock Prevention:
Because the unlocking is guaranteed, it minimizes the risk of programmer error leading to deadlocks.
4..Movable:
std::unique_lock objects can be moved, making it possible to transfer ownership of the lock between different scopes or threads.

5. ❌ std::unique_lock is not copyable

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
/*
1️⃣What is std::defer_lock Doing?
🔹 Meaning of std::defer_lock
std::defer_lock tells std::unique_lock: “Associate with this mutex, but do NOT lock it in the constructor.”

2️⃣ What If You DON’T Use std::defer_lock?

std::unique_lock<std::mutex> lock(mtx); // locks immediately
What happens internally?
Constructor locks the mutex immediately
Thread owns the mutex right away
lock.owns_lock() == true

*/

✅Internal Working of unique_lock with defer_lock :    
template<typename Mutex>
class unique_lock {
    Mutex* mtx;
    bool owns;
public:
    unique_lock(Mutex& m, std::defer_lock_t)  : mtx(&m), owns(false) {
        // mutex NOT locked
    }
    void lock() {
        mtx->lock();
        owns = true;
    }
    void unlock() {
        mtx->unlock();
        owns = false;
    }
    ~unique_lock() {
        if (owns)
            mtx->unlock();
    }
};


//================== std::mutex::try_lock() =============================================================


✅What is std::mutex::try_lock()?
try_lock() is a method(member function) of std::mutex class and works with only single mutex.
if the mutex is already locked by another thread, It allows a thread to lock a mutex without blocking (i.e., waiting).
If the mutex is:
unlocked: try_lock() locks it and returns true.
locked (already locked by another thread): try_lock() immediately returns false without blocking the thread.

Usecase:
This is especially useful in scenarios where you want your thread to continue doing other task if a resource is already being used by another thread, instead of waiting indefinitely for the mutex.

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

//============================  std::try_lock()  =====================================================================

✅What is std::try_lock()?
std::try_lock() is a standard library function (free function) and works with multiple mutexes simultaneously.
Try to lock multiple mutexes in a deadlock-free manner without blocking.

std::try_lock is a non-blocking locking algorithm ,try to lock multiple mutexes in a deadlock-free manner without blocking.
Useful for deadlock prevention when trying to lock multiple mutexes at once.

✅ Function Signature:
template<class Mutex1, class Mutex2, class... Mutexes>
int std::try_lock(Mutex1& m1, Mutex2& m2, Mutexes&... ms);
/* 
template<class... MutexTypes>
int std::try_lock(MutexTypes&... m);

*/

Returns:
| Return value | Meaning                             |
| ------------ | ---------------------------------   |
| `-1`         | ✅ All mutexes locked successfully  |

| `0`          | ❌ Failed to lock first mutex      |
| `1`          | ❌ Failed to lock second mutex     |
| `N`          | ❌ Failed to lock Nth mutex        |
// 0-based Indexing
All mutexes before index n are:
      🔓 automatically unlocked
      Mutexes after index i were never attempted

-------------------------------------------------------------------------------------------------------------------

❌Why Do We Need std::try_lock ?
❌ Problem with naive locking (deadlock)

std::mutex m1, m2;
// Thread 1
m1.lock();
m2.lock();   // waits here

// Thread 2
m2.lock();
m1.lock();   // waits here
💥 Deadlock!
🔴 What happens?
Thread 1 holds m1, waits for m2
Thread 2 holds m2, waits for m1
Neither releases → 💥 DEADLOCK
This happens because each thread holds one lock while waiting for the other.



✅Simple Example:
#include <iostream>
#include <mutex>

std::mutex m1, m2;
void task() {
    int result = std::try_lock(m1, m2);

    if (result == -1) {
        std::cout << "Both mutexes locked\n";

        // critical section
        m1.unlock();
        m2.unlock();
    } 
    else {
        std::cout << "Failed to lock mutex index: " << result << "\n";
    }
}
int main() {
    task();
}

✅Step-by-step logic (simplified):
try {
    lock m1 (non-blocking)
    if fails → return 0

    lock m2
    if fails → unlock m1 → return 1

    lock m3
    if fails → unlock m1, m2 → return 2

    ...
    return -1
}


🔐 How std::try_lock Removes Deadlock

1️⃣ First: What Causes Deadlock?
Deadlock happens when all 4 Coffman conditions are satisfied:
Mutual exclusion – mutexes allow only one owner
Hold and wait – thread holds one lock and waits for another
No preemption – locks can’t be forcibly taken
Circular wait – thread A waits for B, B waits for A

👉 The real killer is #2 + #4 (hold-and-wait + circular wait).


2️⃣Core Idea Behind std::try_lock

📌Important rule:
If it cannot lock all mutexes, it releases everything it already locked.

std::try_lock never allows “hold one and wait for another”.
This is the key deadlock prevention rule.

3️⃣ How This Prevents Deadlock?
🔑 Deadlock needs: “Thread holds A and waits for B”
❌ std::try_lock behavior: “If B isn’t available, release A and back off”
👉 So hold-and-wait is broken.





















//================================================================================================================

✅ std::try_lock vs mutex::try_lock()

| Feature                 | `mutex::try_lock()` | `std::try_lock()` |
| ----------------------- | ------------------- | ----------------- |
| Locks how many mutexes? | One                 | Multiple          |
| Return type             | `bool`              | `int`             |
| Deadlock prevention     | ❌ No                | ✅ Yes          |
| Auto unlock on failure  | ❌ No                | ✅ Yes          |


✅Difference: try_lock vs lock

| Feature         | `std::lock` | `std::try_lock` |
| --------------- | ----------- | --------------- |
| Blocking        | ✅ Yes       | ❌ No            |
| Deadlock-safe   | ✅ Yes       | ✅ Yes           |
| Returns status  | ❌ No        | ✅ Yes           |
| CPU usage       | Efficient   | Can spin        |
| Waits for mutex | Yes         | Never           |
