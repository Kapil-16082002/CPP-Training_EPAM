//what is synchronization
// what is concurrency

🔐 What is a Semaphore?
A semaphore is a synchronization primitive used to control access to a shared resource by multiple threads.

Semaphore is simply a variable which is non-negative and shared between threads. 
This variable is used to solve the critical section problem and to achieve process synchronization in the multiprocessing environment.
Think of it like a counter:
It allows a certain number of threads to acquire (enter).
When a thread is done, it releases (exits), increasing the counter.

📌 Use Case:
A counting semaphore is ideal when:
1.There is a pool of identical(same) resources (e.g., database connections, network ports, parking slots).
2.You want to allow N threads to enter a region or access a resource simultaneously, where N is the initial semaphore count.

Semaphore is accessed only through two standard atomic operations wait() and signal();
When one process modifies the semaphore value no other process modifies it.
🔧 Key Operations:
1. wait() / P() / acquire():
Decreases the semaphore count by 1.
If the count becomes negative, the calling thread blocks until a resource is available.

2. signal() / V() / release():
Increases the semaphore count by 1.
If threads are blocked, one is unblocked.

Definition of wait():              Definition of signal()     P(semaphore S){
    P(semaphore S){
    while(S<=0){                                               while(S<=0){
                                                                    S++;
        // no operation                                         }
        
    }
    S--;
}

//-----------------------------------------------------------------------------------------------------------------
🧠 Types of Semaphores
There are mainly two types of semaphores:
1.Binary Semaphore (Mutex)
2.Counting Semaphore

✅1.Binary Semaphore:

A binary_semaphore is a synchronization primitive that maintains an internal counter with a maximum value of 1.
It allows threads to signal and wait, enabling controlled access or communication between threads.

acquire(): Waits until the counter is > 0, then decrements it.
release(): Increments the counter (up to 1), signaling another waiting thread.

💡 Concept:
Can take only 0 or 1 as value.
Only one thread can enter the critical section at a time.

Purpose:
🎯 Main Use Case: Thread Signaling / Coordination
1.Use std::binary_semaphore when one thread needs to signal another thread to proceed, rather than protect shared data.
2.Used for mutual exclusion, like a lock.


#include <iostream>
#include <thread>
#include <semaphore>
#include <chrono>

std::binary_semaphore bin_sem(1); // initialized with 1 (binary semaphore)

void critical_task(int id) {
    bin_sem.acquire(); // lock
    std::cout << "🔒 Thread " << id << " entered critical section\n";
    std::this_thread::sleep_for(std::chrono::seconds(1)); // simulate work
    std::cout << "🔓 Thread " << id << " leaving critical section\n";
    bin_sem.release(); // unlock
}
int main() {
    std::thread t1(critical_task, 1);
    std::thread t2(critical_task, 2);
    std::thread t3(critical_task, 3);

    t1.join();
    t2.join();
    t3.join();

    return 0;
}
🔍 Output Behavior:
Only one thread can enter the critical section at a time.
Others wait until the semaphore is released.

/*🔍  What does std::binary_semaphore bin_sem(1); mean?

This semaphore works like a lock that can only be acquired by one thread at a time.
The initial value 1 means the semaphore is available.
The first thread calling acquire() succeeds immediately, and the value becomes 0 (unavailable).
If another thread calls acquire() while its 0, it waits (blocks) until the semaphore is release()d.
🟢 So with (1), one thread can enter the critical section at a time. 


❓ What happens if you do:

std::binary_semaphore bin_sem(0);
That means the semaphore is initialized with value 0, which means it is not available at the start.

🔴 Behavior:
The first thread calling acquire() will block immediately because the count is 0.
It will stay blocked until another thread calls release().
So, if no one calls release() before acquire(), the thread will never proceed → it will be stuck.

🧪 Example:
std::binary_semaphore bin_sem(0); // Not available initially

void threadA() {
    std::cout << "Thread A waiting...\n";
    bin_sem.acquire(); // This will block
    std::cout << "Thread A entered\n";
}

void threadB() {
    std::this_thread::sleep_for(std::chrono::seconds(2));
    std::cout << "Thread B releasing semaphore\n";
    bin_sem.release(); // Now Thread A can proceed
}
Thread A will wait until Thread B releases the semaphore after 2 seconds.

✅ Summary:

Initialization	Behavior
bin_sem(1)	Starts as available. First acquire() succeeds.
bin_sem(0)	Starts as unavailable. First acquire() blocks.


*/

//--------------------------------------      Question         ------------------------------------------
"Why not just use std::mutex with lock_guard or unique_lock?" instead of std::binary_semaphore in above code??
✅ Reason for binary_semaphore:
Use std::mutex for mutual exclusion (protecting critical sections). 
Use std::binary_semaphore when you want explicit control over signaling, such as thread coordination or communication (like Thread A signaling Thread B).
/* 
look at a real scenario where mutex will fail or behave incorrectly, but binary_semaphore works perfectly.

🚨 Problem Statement:
Thread A must perform some work and then signal Thread B to continue.

This is one-way signaling (like a gate that Thread B must wait behind until Thread A opens it).

❌ Fails with mutex:
🔒 Attempt with mutex (INCORRECT way):
#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>

std::mutex mtx;

void workerA() {
    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::cout << "[A] Work done. Unlocking...\n";
    mtx.unlock();  // ❌ BAD! Crashes if mutex wasn’t locked by this thread
}
void workerB() {
    std::cout << "[B] Waiting for signal...\n";
    mtx.lock(); // Will block here
    std::cout << "[B] Received signal!\n";
}
int main() {
    mtx.lock();  // Pre-lock so B will block
    std::thread t1(workerA);
    std::thread t2(workerB);

    t1.join();
    t2.join();
}
❌ Why This is Wrong:
mutex is thread-owned — only the thread that locked it can unlock.
Here, main() locks it, workerB waits, and workerA tries to unlock — boom 💥 = undefined behavior / crash.

🔧 Example Scenario Where binary_semaphore Shines
🔔 Thread A signals Thread B:
✅ Correct Version with binary_semaphore
#include <iostream>
#include <thread>
#include <semaphore>  // C++20
#include <chrono>

std::binary_semaphore signal(0);  // start locked

void workerA() {
    std::cout << "Thread A: Doing work...\n";
    std::this_thread::sleep_for(std::chrono::seconds(1)); // simulate work
    std::cout << "[A] Work done. Signaling B...\n";
    signal.release();  // ✅ any thread can call release
}
void workerB() {
    std::cout << "Thread B: Waiting for signal from Thread A...\n";
    signal.acquire();  // ✅ block until signaled
    std::cout << "Thread B: Received signal from Thread A, continuing work\n";
}
int main() {
    std::thread t1(workerA);
    std::thread t2(workerB);

    t1.join();
    t2.join();
}
✅Output:
Thread B: Waiting for signal from Thread A...
Thread A: Doing work...
[A] Work done. Signaling B...
Thread B: Received signal from Thread A, continuing work

binary_semaphore is not thread-owned
Any thread can acquire or release
Acts like a notification gate (like condition_variable, but simpler)
*/
🔧 Example Scenario Where binary_semaphore Shines
🔔 Thread A signals Thread B:
#include <iostream>
#include <thread>
#include <semaphore>  // Requires C++20

std::binary_semaphore sem(0);  // Initially locked (count = 0)

void threadA() {
    std::cout << "Thread A: Doing work...\n";
    // Simulate work
    std::this_thread::sleep_for(std::chrono::seconds(2));
    std::cout << "Thread A: Work done, signaling Thread B\n";
    sem.release();  // Signal Thread B
}
void threadB() {
    std::cout << "Thread B: Waiting for signal from Thread A...\n";
    sem.acquire();  // Wait until signaled by A
    std::cout << "Thread B: Received signal, continuing work\n";
}
int main() {
    std::thread a(threadA);
    std::thread b(threadB);

    a.join();
    b.join();

    return 0;
}
This ensures that Thread B waits until Thread A finishes its work and signals it.
release() increments the semaphore count (up to 1 for binary semaphore). 
acquire() blocks until the count is positive, then decrements it.

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

✅2. Counting Semaphore:
Purpose:
Used when there are multiple instances of a resource.

A counting semaphore is a synchronization primitive that allows multiple threads to access a limited number of resources concurrently.
It’s like a gate with multiple passes — only N threads can go through at a time.

It differs from:
🔐 mutex: which allows only one thread at a time.
🚦 binary_semaphore: which only allows one permit (0 or 1).
🎯 counting_semaphore: allows N permits.

It maintains an internal counter representing the number of available resources.
It is initialized with a non-negative integer value.
The value represents the number of available units of the resource.
Threads decrement the counter when acquiring a resource and increment it when releasing.

✅ Code Example: Allow Only 2 Threads in Critical Section....
#include <iostream>
#include <thread>
#include <semaphore>
#include <vector>
#include <chrono>

std::counting_semaphore<2> sem(2);  // max 2 threads at a time

void worker(int id) {
    std::cout << "🔃 Thread " << id << " waiting to enter...\n";
    sem.acquire();  // wait for permit
    std::cout << "✅ Thread " << id << " entered critical section\n";

    std::this_thread::sleep_for(std::chrono::seconds(2)); // simulate work

    std::cout << "🚪 Thread " << id << " leaving\n";
    sem.release();  // give back permit
}
int main() {
    std::vector<std::thread> threads;

    for (int i = 1; i <= 5; ++i) {
        threads.emplace_back(worker, i);
    }
    for (auto& t : threads) {
        t.join();
    }

    return 0;
}
🧾 Output Example (Formatted for clarity)
🔃 Thread 1 waiting to enter...
✅ Thread 1 entered critical section
🔃 Thread 2 waiting to enter...
✅ Thread 2 entered critical section
🔃 Thread 3 waiting to enter...
🔃 Thread 4 waiting to enter...
🔃 Thread 5 waiting to enter...
🚪 Thread 1 leaving
✅ Thread 3 entered critical section
🚪 Thread 2 leaving
✅ Thread 4 entered critical section
🚪 Thread 3 leaving
✅ Thread 5 entered critical section
🚪 Thread 4 leaving
🚪 Thread 5 leaving
🔢 You can see: Only 2 threads were allowed in at a time — the rest had to wait.

/*  
“How does the program know whether the shared resource is available or not? Where is the count maintained?”

std::counting_semaphore<2> sem(2);
We are doing two things:

1. 2 is the maximum number of permits (set by <2>)
This tells the semaphore: "At most, I can allow 2 threads at a time."

2. The constructor sem(2) sets the initial count to 2.
This means: "Right now, I have 2 permits available for threads to acquire."
2 is both:
The maximum count (capacity).
The initial count (permits currently available).

📌 What acquire() Does:

sem.acquire();
If semaphore_count > 0:
It decreases the count by 1.
Allows the thread to proceed.

If semaphore_count == 0:
The thread blocks (waits).
It’s automatically resumed when another thread does release().

🔁 Internally:
Think of it like this:

if (semaphore_count > 0) {
    semaphore_count--;  // grab a slot
    proceed;
} else {
    wait in line;
}
📌 What release() Does:

sem.release();
Increases the count by 1 (unless it's already at max()).

Unblocks one waiting thread if there is one.
The semaphore internally tracks this count.
*/
Use Case-	Parking lot, DB connection pool, printer queue, etc.

🏪 Real-Life Example: Limited Parking Lot
Imagine a parking lot that has only 3 parking spots.
Each car can enter only if a spot is available.
If no spots are free, the car must wait.
When a car leaves, a spot becomes available for another.
This is exactly how a counting semaphore works!

🔧 Mapping to Code

Real-world Concept	Code Equivalent
Parking spots	Semaphore permits (count = 3)
Car arriving	Thread trying to acquire()
Car parked	Thread enters critical section
Car leaving	Thread calls release()

🧑‍💻 C++ Code: Parking Lot with 3 Spots
#include <iostream>
#include <thread>
#include <semaphore>
#include <vector>
#include <chrono>

// Semaphore with max 3 permits (3 parking spots)
std::counting_semaphore<3> parking_spots(3);

void car(int id) {
    std::cout << "🚗 Car " << id << " is trying to park...\n";
    
    parking_spots.acquire();  // Try to enter parking lot
    std::cout << "✅ Car " << id << " has parked.\n";

    std::this_thread::sleep_for(std::chrono::seconds(2)); // Simulate time spent parked

    std::cout << "🅿️ Car " << id << " is leaving the parking lot.\n";
    parking_spots.release();  // Free up the spot
}

int main() {
    const int total_cars = 6;
    std::vector<std::thread> cars;

    // Launch 6 car threads
    for (int i = 1; i <= total_cars; ++i) {
        cars.emplace_back(car, i);
    }

    // Wait for all cars to finish
    for (auto& t : cars) {
        t.join();
    }

    std::cout << "🚦 All cars have parked and left.\n";
    return 0;
}
🧾 Example Output
🚗 Car 1 is trying to park...
✅ Car 1 has parked.
🚗 Car 2 is trying to park...
✅ Car 2 has parked.
🚗 Car 3 is trying to park...
✅ Car 3 has parked.
🚗 Car 4 is trying to park...
🚗 Car 5 is trying to park...
🚗 Car 6 is trying to park...
🅿️ Car 1 is leaving the parking lot.
✅ Car 4 has parked.
🅿️ Car 2 is leaving the parking lot.
✅ Car 5 has parked.
🅿️ Car 3 is leaving the parking lot.
✅ Car 6 has parked.
🅿️ Car 4 is leaving the parking lot.
🅿️ Car 5 is leaving the parking lot.
🅿️ Car 6 is leaving the parking lot.
🚦 All cars have parked and left.





/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

🧠 Example Use Cases
Situation	                                                       Preferred
Protecting critical section (e.g. updating shared variable)	       std::mutex
Thread A must signal Thread B to proceed(Signaling between threads)std::binary_semaphore
Need RAII-style auto-lock	                                       std::mutex
Decouple who waits and who signals	                               std::binary_semaphore
Replacing condition_variable	                                   std::binary_semaphore
Wait/Notify-like patterns	                                       ats::binary_semaphore or std::condition_variable
One thread produces, other consumes	                               std::binary_semaphore

Lock must be released by same thread	                           std::mutex
Lock can be released by a different thread	                       std::binary_semaphore


🧠 When to Use counting_semaphore
Scenario	                                 Why it works

Connection pools	                         Only N clients can use DB at once
Resource pools (threads, printers, etc.)	 Control max concurrent usage
Rate limiting	                             Limit how often a resource is accessed
Bounded buffer problems	                     Classic producer-consumer
Multi-lane processing	                     Like only 3 checkout counters open





