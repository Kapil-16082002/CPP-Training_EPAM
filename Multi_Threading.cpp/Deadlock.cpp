
🚫 What is Deadlock?
Deadlock happens when two or more threads are waiting for each other to release resources, but none of them do this, so they are all stuck forever.

In simple words:
Thread A locks Resource 1 and waits for Resource 2.
Thread B locks Resource 2 and waits for Resource 1.
Both threads  are waiting for each other forever.
→ Neither can proceed. They are blocked forever.

😖 What Happens if a Deadlock Occurs?
Threads are waiting for each other in a cycle and no one can move forward.
The program gets stuck or hang forever.
CPU usage may drop to zero for the deadlocked threads.
The program appears frozen (it’s not crashing, it’s just waiting forever).

In short:
👉 The program hangs.
👉 No output. No progress. No errors (unless you manually detect it).

🔥 Deadlock Conditions (All must be true):
There are 4 necessary conditions for deadlock to happen:

Condition	        Meaning
1. Mutual Exclusion	Resources cannot be shared; only one thread at a time can use a resource.
2. Hold and Wait	Thread should holds one resource and waits for another resource.
3. No Preemption	Resources cannot be forcibly taken from a thread.
4. Circular Wait	Threads are waiting for each other in a circle.
✅ If all 4 happen → Deadlock can occur!

//------------------------------------------------------------------------------------------------------------------
🧩 Example to Understand:
Imagine:
Thread 1 locks Mutex A and wants Mutex B.
Thread 2 locks Mutex B and wants Mutex A.
Both are waiting for each other → Deadlock!

🧪 C++ Code Example Causing Deadlock:
#include <iostream>
#include <thread>
#include <mutex>

std::mutex mutexA;
std::mutex mutexB;

void task1() {
    std::lock_guard<std::mutex> lockA(mutexA);
    std::lock_guard<std::mutex> lockB(mutexB);  // attempts to acquire the lock on mutexB
    std::cout << "Task 1 acquired both mutexes\n";
}
void task2() {
    std::lock_guard<std::mutex> lockB(mutexB);
    std::lock_guard<std::mutex> lockA(mutexA);    // attempts to acquire the lock on mutexA
    std::cout << "Task 2 acquired both mutexes\n";
}
int main() {
    std::thread t1(task1);
    std::thread t2(task2);

    t1.join();
    t2.join();

    return 0;
}
📊 What Happens Here?
t1 locks mutexA, then tries to lock mutexB.
t2 locks mutexB, then tries to lock mutexA.
Both are stuck forever waiting for each other ➔ Deadlock happens!

Thread T1 (continuing the execution):
After completing its simulated work, attempts to acquire the lock on mutexB (std::lock_guard<std::mutex> lockB(mutexB);) but fails, because Thread T2 already holds the lock on mutexB.

Thread T2 (continuing the execution):
After completing its simulated work, attempts to acquire the lock on mutexA (std::lock_guard<std::mutex> lockA(mutexA);) but fails, because Thread T1 already holds the lock on mutexA.

🛡️ How to Prevent Deadlock?
Method	               Description
1. Lock ordering	   Always acquire locks in a fixed global order.
2. Try lock	           Use std::try_lock instead of blocking lock() — if it fails, retry.
3. Timeout lock	       Use timed locks that timeout if locking fails.
4. Avoid hold-and-wait	Request all resources at once.



//=================================================================================================================

✅Resolving Deadlock Using std::lock
1.std::lock is used to lock multiple mutexes in a deadlock-free manner.

Drawbacks of std::lock 
std::lock does NOT provide: automatic resource management or unlocking.
std::lock does NOT handle exception safety. 

#include <iostream>
#include <thread>
#include <mutex>

std::mutex mutex1, mutex2;

void thread1() {
    std::lock(mutex1, mutex2); // Lock both mutexes at once, to avoid deadlock!

    // Use std::lock_guard to lock the mutexes safely
    std::lock_guard<std::mutex> lock1(mutex1, std::adopt_lock);
    std::lock_guard<std::mutex> lock2(mutex2, std::adopt_lock);

    std::cout << "Thread 1 acquired both locks\n";
}
void thread2() {
    std::lock(mutex1, mutex2); // Same lock order as thread1

    // Use std::lock_guard to lock the mutexes safely
    std::lock_guard<std::mutex> lock1(mutex1, std::adopt_lock);
    std::lock_guard<std::mutex> lock2(mutex2, std::adopt_lock);

    std::cout << "Thread 2 acquired both locks\n";
}
int main() {
    std::thread t1(thread1);
    std::thread t2(thread2);

    t1.join();
    t2.join();

    return 0;
}
Explanation of the Fix:
1.std::lock: Safely locks two or more mutexes without risking deadlock. It locks all specified mutexes atomically.
2.std::lock_guard is used to create RAII (Resource Acquisition Is Initialization) objects that handle automatic unlocking of mutexes(Automatic resource management) when the scope of the std::lock_guard objects ends or exception is thrown
3.std::adopt_lock: tells to the lock_guard() that the mutex is already locked by the current thread (because std::lock did it), so std::lock_guard does not try to lock it again.


//-------------------------------------------------------------------------------------------------------------------- 


✅Avoiding Deadlock Using std::scoped_lock lock ,  introduced in C++17

std::scoped_lock locks multiple mutexes atomically in safe and deadlock-free order internally.
It is part of the C++17 Standard Library, and the class std::scoped_lock is defined in the <mutex> header.
To overcome the drawbacks of std::lock() of automatic resource management or unlocking and exception safety.

Key Features of std::scoped_lock:

1.Automatic Resource Management:
When a std::scoped_lock object is created, it locks the given mutexes.
When the std::scoped_lock object goes out of scope, it automatically unlocks the mutexes.

2.Exception Safety:
Ensures the mutexes are unlocked even if an exception is thrown in the critical section.

3.Supports Multiple Mutexes:
You can lock multiple mutexes simultaneously in a deadlock-free manner without explicitly calling std::lock.

4.RAII (Resource Acquisition Is Initialization):
Automatically manages the locking and unlocking of mutexes.

5.Deadlock Avoidance:
Like std::lock, std::scoped_lock ensures that multiple mutexes are locked in a consistent way to avoid deadlock.


#include <iostream>
#include <thread>
#include <mutex>

std::mutex mutexA;
std::mutex mutexB;

void task1() {
    // Lock both mutexes at once, to avoid deadlock!
    std::scoped_lock lock(mutexA, mutexB); // std::scoped_lock locks multiple mutexes atomically in safe and deadlock-free order internally.
    std::cout << "Task 1 acquired both mutexes\n";
}
void task2() {
    // Lock both mutexes at once, to avoid deadlock!
    std::scoped_lock lock(mutexA, mutexB); // lock both mutexes together safely
    std::cout << "Task 2 acquired both mutexes\n";
}
int main() {
    std::thread t1(task1);
    std::thread t2(task2);

    t1.join();
    t2.join();

    return 0;
}


//==================================================================================================================

✅Deadlock with std::try_lock

✅What is std::try_lock()?
std::try_lock() is a standard library function (free function) and works with multiple mutexes simultaneously.
Try to lock multiple mutexes in a deadlock-free manner without blocking(eliminating any circular wait conditions.)
Returns:
-1 , if all mutexes were successfully locked.
The index of the first mutex that could not be locked (0-based index) if locking fails.

If any mutex fails to lock, it will automatically unlock all previously locked mutexes.
Useful for deadlock prevention when trying to lock multiple mutexes at once.

Drawbacks of std::try_lock 
std::try_lock does NOT provide: automatic resource management or unlocking.
std::try_lock does NOT handle exception safety. 

#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>

std::mutex mutex1;
std::mutex mutex2;

void threadFunction1() {
    while (true) {
        if (std::try_lock(mutex1, mutex2) == -1) { // Let std::try_lock lock both mutexes atomically
            std::cout << "Thread 1 locked both mutexes" << std::endl;
            mutex1.unlock();   // unlock() locks manually after use 
            mutex2.unlock();   // unlock() locks manually after use
            break;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(10)); // Retry after a brief pause
    }
}
void threadFunction2() {
    while (true) {
        if (std::try_lock(mutex1, mutex2) == -1) { // The locking order remains consistent with Thread 1
            std::cout << "Thread 2 locked both mutexes" << std::endl;
            mutex1.unlock();   // unlock() locks manually after use
            mutex2.unlock();   // unlock() locks manually after use
            break;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(10)); // Retry after a brief pause
    }
}
int main() {
    std::thread t1(threadFunction1);
    std::thread t2(threadFunction2);

    t1.join();
    t2.join();

    return 0;
}
/* 
simple version of above  std::try_lock(mutex1, mutex2)

// void threadFunction1() {
//     while (true) {
//         if (mutex1.try_lock()) { // Thread1 tries to lock mutex1 first
            
//             if (mutex2.try_lock()) { // tries to lock mutex2, but if Thread 2 has already locked mutex2, it fails.
//                 std::cout << "Thread 1 locked both mutexes" << std::endl;
//                 mutex2.unlock();
//                 mutex1.unlock();
//                 break;
//             } else {
//                 // If mutex2 can't be locked, release mutex1 and retry
//                 mutex1.unlock();
//             }
//         }
//     }
// }
// void threadFunction2() {
//     while (true) {
//         if (mutex2.try_lock()) { // Thread2 tries to lock mutex2 first
            
//             if (mutex1.try_lock()) {  // tries to lock mutex1, but if Thread 2 has already locked mutex1, it fails.
//                 std::cout << "Thread 2 locked both mutexes" << std::endl;
//                 mutex1.unlock();
//                 mutex2.unlock();
//                 break;
//             } else {
//                 // If mutex1 can't be locked, release mutex2 and retry
//                 mutex2.unlock();
//             }
//         }
//     }
// }

*/