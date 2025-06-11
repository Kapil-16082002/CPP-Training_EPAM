
🧠 What is std::condition_variable?
A condition_variable is used to block(wait) a thread until a specific condition is met — typically used with a mutex.

Think of it like:
🧍‍♂️ "Wait here until someone gives you a signal to go."

🧾 Why Do We Need It?
When one thread have to wait for a condition to be true (like “data is available”), and another thread will notify it once that condition is ready — using a condition_variable makes it safe, efficient, and avoids busy waiting.
It’s mainly used in Producer-Consumer problems, thread-safe queues, and any time threads must wait for some event or coordinate access.


🚫 Without condition_variable — Busy Waiting (Bad)

while (!data_ready) {
    // keep checking
}
This is called busy-waiting: it wastes CPU cycles.

✅ With condition_variable — Efficient Waiting
The thread sleeps until notified — no CPU waste!

//---------------------------------------------------------------------------------------------------------------
Example: 
#include <iostream>
#include <thread>
#include <condition_variable>
#include <mutex>
 
std::mutex mtx;
std::condition_variable cv;
bool ready = false;
 
//bool GetReadyStatus() { return ready; }
 
void worker() {
	std::cout << "Worker thread is started\n";
	std::unique_lock<std::mutex> lock(mtx);
	cv.wait(lock, [] { return ready; });//This line unlocks the mutex and puts the thread to sleep until cv.notify_one() is called and the lambda returns true.
	//cv.wait(lock, GetReadyStatus);
	std::cout << "Worker thread is end\n";
}
int main() {
	std::cout << "Main thread is started\n";
	std::thread t(worker);
	std::this_thread::sleep_for(std::chrono::seconds(1));
	{
		std::lock_guard<std::mutex> lock(mtx);
		ready = true;
		std::cout << "global variable change\n";
	}
	cv.notify_one();
	std::cout << "cv notified\n";
 
	t.join();
	std::cout << "Main thread is end\n";
}
//----------------------------------------------------------------------------------------------------------------

🧪 Example: Producer-Consumer using condition_variable
👷 Scenario:
Thread A: Produces data
Thread B: Waits for data and consumes it
✅ Full Working Code:

#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <chrono>

std::mutex mtx;      // We’ll use this to protect data_ready.
std::condition_variable cv;// A condition variable lets one thread wait until another thread notifies it.Here, the consumer will wait, and the producer will notify.
bool data_ready = false;

void producer() {          //A thread function that simulates work and notifies the consumer.
    //std::this_thread::sleep_for(std::chrono::seconds(2));  // simulate work
    std::lock_guard<std::mutex> lock(mtx);
    std::cout << "[Producer] Producing data...\n";
    data_ready = true;                      //producer is done.
    cv.notify_one();  // Notifies one waiting thread (in this case, signal the consumer) that something has changed
}
void consumer() {                // A thread function that waits for the producer's signal.
    std::unique_lock<std::mutex> lock(mtx);
    std::cout << "[Consumer] Waiting for data...\n";

    // Wait until data_ready becomes true
    cv.wait(lock, [] { return data_ready; });
    //This line unlocks the mutex and puts the thread to sleep until cv.notify_one() is called and the lambda returns true.

    std::cout << "[Consumer] Data received and processed!\n";
}
int main() {
    std::thread t1(producer);
    std::thread t2(consumer);

    t1.join();
    t2.join();
    return 0;
}
🔁 Output Order (Typical)
[Consumer] Waiting for data...
[Producer] Producing data...
[Consumer] Data received and processed!
🔍 Whats Happening?
Producer:
1.Waits 2 seconds (simulates data preparation)
2.Sets data_ready = true
3.Calls cv.notify_one() to wake the consumer

Consumer:
1.Acquires lock
2.Calls cv.wait(lock, condition)
    Automatically unlocks mutex while waiting
    Reacquires mutex once condition is met
3.When notified and data_ready == true, proceeds

🧠 Why Use wait(lock, condition) Form?
This version:

cv.wait(lock, [] { return data_ready; }) is safer than cv.wait(lock);
Because:
It automatically checks the condition after waking up
Handles spurious wakeups (thread wakes up without being notified)
Prevents bugs

🛠 Summary of Functions
Function	           Description
cv.wait(lock)	       Waits until notified (must hold the mutex)
cv.wait(lock, pred)	   Waits and checks a predicate
cv.notify_one()	       Wakes up one waiting thread
cv.notify_all()	       Wakes up all waiting threads

🧠 Real-Life Examples
A downloader thread signals when a file is downloaded
A logging thread waits for new log messages
UI thread waits for background task to finish
/*
🔁 Quick Recap: What does the mutex (mtx) do here?
It synchronizes access to the shared variable data_ready.
It coordinates producer() and consumer() using the condition_variable cv.

The key part is below line in consumer():
cv.wait(lock, [] { return data_ready; });
This line unlocks the mutex and puts the thread to sleep until cv.notify_one() is called and the lambda returns true.

❌ What if we remove the mutex?
Let’s walk through what might break:

1. Race Condition on data_ready
data_ready is a shared boolean variable accessed by both threads.
Without the mutex:
    1.producer() writes to data_ready.
    2.consumer() reads from it.
If both threads access data_ready at the same time, there's no guarantee about memory consistency:
The consumer might not see the update from the producer.
This leads to undefined behavior (may crash, may hang, or may seem fine — until it doesn't).

2. Condition Variable Misuse
A condition_variable must always be used with a mutex:
It’s designed to work by atomically unlocking the mutex and putting the thread to sleep.

If you don't provide a mutex, the wait() call can't safely coordinate with notify_one().

So if you just do:
cv.wait(// no mutex) ;
💥 That’s a logic bug — your program may crash or behave unpredictably.

🔧 Imagine This Scenario:
Without the mutex:
void consumer() {
    std::cout << "[Consumer] Waiting for data...\n";
    cv.wait( no lock , [] { return data_ready; });  // 🚫 Unsafe!
    std::cout << "[Consumer] Data received and processed!\n";
}
Even if data_ready = true happens in the producer, the consumer thread might:
Miss the signal
Wake up too early
Or never wake up at all
Because wait() won’t behave correctly without the mutex-guarded coordination.

*/
//-------------------------------------------------------------------------------------------------------------
✅ Producer-Consumer without condition_variable and mutex
We'll use a std::atomic<bool> to coordinate safely between threads without locks or condition variables.

#include <iostream>
#include <thread>
#include <atomic>
#include <chrono>

std::atomic<bool> data_ready(false); // atomic = thread-safe read/write

void producer() {
    std::this_thread::sleep_for(std::chrono::seconds(2)); // simulate work
    std::cout << "[Producer] Producing data...\n";
    data_ready.store(true); // set flag
}

void consumer() {
    std::cout << "[Consumer] Waiting for data...\n";

    // Busy-wait loop (not efficient!)
    while (!data_ready.load()) {
        std::this_thread::sleep_for(std::chrono::milliseconds(10)); // avoid CPU overuse
    }

    std::cout << "[Consumer] Data received and processed!\n";
}

int main() {
    std::thread t1(producer);
    std::thread t2(consumer);

    t1.join();
    t2.join();

    return 0;
}
🔍 Explanation:
std::atomic<bool> data_ready ensures that producer and consumer can access the flag safely without needing a mutex.

The consumer loops until data_ready == true.

This is called busy-waiting and is generally avoided because:

It wastes CPU cycles.

It is not scalable for real systems with many producers/consumers or large data volumes.

⚠️ Drawbacks of this approach:
Not efficient (even with sleep_for(10ms), it is still polling).
Hard to scale or extend (e.g., multiple producers/consumers, queues).
Wastes resources when there's nothing to consume.

//----------------------------------------------------------------------------------------------------------------
✅ Code: Producer-Consumer with only mutex (no condition_variable)
#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>

int buffer = 0;
bool data_ready = false;
std::mutex mtx;

void producer() {
    std::this_thread::sleep_for(std::chrono::seconds(2)); // Simulate work

    std::lock_guard<std::mutex> lock(mtx);
    buffer = 42;
    data_ready = true;
    std::cout << "[Producer] Produced data: " << buffer << std::endl;
}

void consumer() {
    std::cout << "[Consumer] Waiting for data...\n";

    while (true) {
        std::lock_guard<std::mutex> lock(mtx);
        if (data_ready) {
            std::cout << "[Consumer] Consumed data: " << buffer << std::endl;
            break;
        }
        // Unlocks automatically, then retries in next loop
        std::this_thread::sleep_for(std::chrono::milliseconds(10)); // avoid tight loop
    }
}
int main() {
    std::thread t1(producer);
    std::thread t2(consumer);

    t1.join();
    t2.join();

    return 0;
}
🔍 Explanation
No condition variable: Instead, the consumer keeps checking data_ready.
std::mutex ensures that data_ready and buffer are accessed safely.
To prevent high CPU usage, the consumer sleeps for a short time between checks.
This method is simple but still technically a form of polling (with delay).

⚠️ Downsides
It’s better than pure busy-waiting, but still inefficient compared to using condition_variable or semaphores.
CPU usage increases with multiple consumers or a tight loop.


