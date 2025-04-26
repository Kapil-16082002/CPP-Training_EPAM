🚫 What is Deadlock?
Deadlock happens when two or more threads are waiting for each other to release resources, but none of them ever does, so they are all stuck forever.

In simple words:
Thread A locks Resource 1 and waits for Resource 2.
Thread B locks Resource 2 and waits for Resource 1.
Both threads  are waiting for each other forever.
→ Neither can proceed. They are blocked forever.

😖 What Happens if a Deadlock Occurs?
The program gets stuck forever.
Threads are waiting for each other in a cycle and no one can move forward.
CPU usage may drop to zero for the deadlocked threads.
The program appears frozen (it’s not crashing, it’s just waiting forever).

In short:
👉 The program hangs.
👉 No output. No progress. No errors (unless you manually detect it).

🔥 Deadlock Conditions (All must be true):
There are 4 necessary conditions for deadlock to occur:

Condition	        Meaning
1. Mutual Exclusion	Resources cannot be shared; only one thread at a time can use a resource.
2. Hold and Wait	Thread holds one resource and waits for another.
3. No Preemption	Resources cannot be forcibly taken from a thread.
4. Circular Wait	Threads are waiting for each other in a circle.
✅ If all 4 happen → Deadlock can occur!

//------------------------------------------------------------------------------------------------------------------
🧩 Example to Understand:
Imagine:

Thread 1 locks Mutex A and wants Mutex B.
Thread 2 locks Mutex B and wants Mutex A.
Both are waiting for each other → Deadlock!

🧪 C++ Code Example Causing Deadlock
#include <iostream>
#include <thread>
#include <mutex>

std::mutex mutexA;
std::mutex mutexB;

void task1() {
    std::lock_guard<std::mutex> lockA(mutexA);
    std::this_thread::sleep_for(std::chrono::milliseconds(100)); // Simulate work
    std::lock_guard<std::mutex> lockB(mutexB);
    std::cout << "Task 1 acquired both mutexes\n";
}

void task2() {
    std::lock_guard<std::mutex> lockB(mutexB);
    std::this_thread::sleep_for(std::chrono::milliseconds(100)); // Simulate work
    std::lock_guard<std::mutex> lockA(mutexA);
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

🛡️ How to Prevent Deadlock?
Method	               Description
1. Lock ordering	   Always acquire locks in a fixed global order.
2. Try lock	           Use std::try_lock instead of blocking lock() — if it fails, retry.
3. Timeout lock	       Use timed locks that timeout if locking fails.
4. Avoid hold-and-wait	Request all resources at once.

🌟 Corrected Code (Avoiding Deadlock Using Lock Ordering)
#include <iostream>
#include <thread>
#include <mutex>

std::mutex mutexA;
std::mutex mutexB;

void task1() {
    std::scoped_lock lock(mutexA, mutexB); // lock both mutexes together safely
    std::cout << "Task 1 acquired both mutexes\n";
}

void task2() {
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
✅ std::scoped_lock locks multiple mutexes atomically in deadlock-free order internally.

🚀 Summary Table:
Concept	Meaning
Deadlock	Threads wait forever because of resource conflict.
Cause	Circular waiting for locks.
Prevention	Lock ordering, try-locks, timeout-locks.
C++ Safe way	std::scoped_lock or std::lock

