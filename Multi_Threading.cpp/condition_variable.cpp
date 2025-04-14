
🧠 What is std::condition_variable?
A condition_variable is used to block(wait) a thread until a specific condition is met — typically used with a mutex.

Think of it like:
🧍‍♂️ "Wait here until someone gives you a signal to go."

It’s mainly used in Producer-Consumer problems, thread-safe queues, and any time threads must wait for some event or coordinate access.

🧾 Why Do We Need It?
When one thread needs to wait for a condition to be true (like “data is available”), and another thread will notify it once that condition is ready — using a condition_variable makes it safe, efficient, and avoids busy waiting.

🚫 Without condition_variable — Busy Waiting (Bad)

while (!data_ready) {
    // keep checking
}
This is called busy-waiting: it wastes CPU cycles.

✅ With condition_variable — Efficient Waiting
The thread sleeps until notified — no CPU waste!

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
    std::this_thread::sleep_for(std::chrono::seconds(2));  // simulate work
    std::lock_guard<std::mutex> lock(mtx);
    std::cout << "[Producer] Producing data...\n";
    data_ready = true;                         //producer is done.
    cv.notify_one();  // Notifies one waiting thread (in this case, signal the consumer) that something has changed
}

void consumer() {                 // A thread function that waits for the producer's signal.
    std::unique_lock<std::mutex> lock(mtx);
    std::cout << "[Consumer] Waiting for data...\n";

    // Wait until data_ready becomes true
    cv.wait(lock, [] { return data_ready; });

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

cv.wait(lock, [] { return data_ready; });
is safer than just:

cv.wait(lock);
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



