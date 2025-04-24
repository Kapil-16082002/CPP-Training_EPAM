A thread is a lightweight unit of execution inside a process. 
 Multiple threads can run concurrently within a single process and share memory (like global variables or heap memory). 
 This makes threading fast but also risky due to race conditions.
In C++ (OOPs approach), we create threads using std::thread (from the <thread> library), which enables multi-threading in C++.


// Types of thread
Mutex:
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
"Hey, main thread — pause here and wait until this thread is done running."

The main thread pauses at t.join() and waits until thread t finishes.
Ensures the thread completes before the program continues.

🧠 Why use join()?
✅ Ensures the thread finishes before the program moves forward.
✅ Prevents the program from exiting while a thread is still running.
✅ Helps avoid undefined behavior (like destructing a thread object that’s still running)

//--------------------------------------------------------------------------------------------------------------

🧠 What is detach() in C++?
detach() is a member function of the std::thread class in C++.
.detach() is used when you don’t want to wait — the thread runs independently, in the background.
It tells the system:
"Let this thread run on its own, I don’t want to wait for it or manage it anymore."
Once detached, the thread becomes a background thread, or a daemon thread, and runs independently of the main program.

std::thread t(myFunction);
t.detach();  // Now runs independently

🕓 Timeline:
Main Thread:  |---continues immediately--->
Thread t:     |--- running in background ---|

🧠 Explanation:
The main thread doesn’t wait for thread t at all.
thread t runs in the background — this is fire-and-forget style.
If the main thread finishes too quickly, thread t might get cut off (especially if it depends on local resources).


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

jkdsk

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


/* 

🧠 What is detach()?
detach() is a method you can call on a std::thread object to let the thread run independently in the background (i.e., detached from the main thread).

🔧 Syntax:

std::thread t(func);
t.detach();
After calling detach(), the thread:

Runs on its own, independently of the main thread.

Cannot be joined later.

Will continue running even if the main thread finishes (unless the process exits).

You no longer have control over that thread.

⚠️ Important: Detached Thread = No Control
Once detached:

You cannot call .join() on it.

You cannot check its status.

You must make sure the thread’s work doesn't depend on variables that might go out of scope.

💀 Dangers of detach()
If not used carefully, it can cause:

Undefined behavior, especially if the thread accesses resources that are deleted or go out of scope.

Program crash or memory corruption.

✅ Example:
#include <iostream>
#include <thread>

void run() {
    std::cout << "Running in background thread\n";
}

int main() {
    std::thread t(run);
    t.detach(); // Now t runs independently
    std::cout << "Main thread done\n";

    // Give the background thread time to finish (just for demo)
    std::this_thread::sleep_for(std::chrono::seconds(1));
    return 0;
}
🧾 Sample Output:
Main thread done
Running in background thread
(Depending on timing, order may vary.)

🚫 When NOT to use detach()
If you need to wait for the thread to finish, use .join() instead.

If the thread accesses local variables from main(), avoid detaching.

✅ When to use detach()
For fire-and-forget background tasks (like logging, notifications, etc.)

When you're sure the thread doesn’t depend on anything in the current scope.
*/