
🔍 What is the Future-Promise Mechanism?
std::promise<T> class allows one thread to set a value (or an exception) that will be made available to another thread through a shared state, which further can be accessed using a std::future<T>.
std::future<T> class allows another thread to wait for that value. ✅ Future reads value from the shared state
Its like a single-use channel from one thread (producer) to another (consumer).

🧠 Real-world Analogy
Think of a food delivery:
🧑‍🍳 The chef (promise) prepares food.
🚶 The customer (future) waits for food to arrive.
Until the chef delivers the food, the customer just waits.


2️⃣ What Is This “Shared State”?
The shared state is an internal object that holds:
1. The return value (or exception)
2. flag_variable(ready_status)
3. Synchronization primitives (mutex / condition variable)
4. Reference count (how many objects share it)

struct shared_state {
    mutex m;
    condition_variable cv;
    bool ready;
    int value;
    atomic<int> ref_count;
};
⚠️ You never see it directly — it’s invisible.
Both objects refer to the same shared state:
std::promise<T>  ---> shared state <--- std::future<T>

--------------------------------------------------------------------------------------------------------------------

👉 The shared state of std::promise and std::future is created on the HEAP.
🔹 Why NOT on the stack?
❌ Stack memory problems
std::future<int> foo() {
    std::promise<int> p;
    return p.get_future();   // ❌
}
If shared state were on stack:
p goes out of scope
Stack memory is destroyed
future would point to dangling memory
💥 Undefined behavior


-------------------------------------------------------------------------------------------------------------------

3️⃣When is the Shared State created?
Before get_future() → no shared state
After get_future() → shared state exists
The shared state is created when std::promise::get_future() is called.

Step 1️⃣ Promise is created
std::promise<int> p;
No value
No shared state yet

Step 2️⃣ Future is requested
std::future<int> f = p.get_future();
[promise] ----+
              |---- [shared state]
[future ] ----+

✔ Shared state is created
✔ Both p and f now point to it

-------------------------------------------------------------------------------------------------------------------

3️⃣ How does set_value() put data into shared state?
Step 1️⃣ Code
std::promise<int> p;
std::future<int> f = p.get_future(); // shared state created
Internally:
Shared state contains:
int value;
bool ready = false;
sync primitives


Step 2️⃣ Producer calls set_value()
p.set_value(42);
What happens internally?
Think of promise as holding a pointer to the shared state.
Internal steps (conceptual):
void promise::set_value(int v) {
    shared_state->value = v;   // 🔹 store value
    shared_state->ready = true;// 🔹 mark ready
    shared_state->notify();    // 🔹 wake waiting futures
}
✔ Value is copied/moved into shared state
✔ Promise does NOT store the value itself

-----------------------------------------------------------------------------------------------------------------
4️⃣ Where is the value actually stored?

📍 Inside the shared state, not inside:
the promise ❌
the future ❌
✅shared_state {
    int stored_value = 42;
    bool ready = true;
}
----------------------------------------------------------------------------------------------------------------

5️⃣ How does future get the value?
int x = f.get();
Internally:
void future::get() {
    wait until shared_state->ready == true;
    return shared_state->value;
}
✔ Future reads from shared state
✔ Promise writes to shared state



6️⃣ Why is this thread-safe?

Because:
Shared state has internal synchronization
set_value() and get() are synchronized
No data race is possible

You don’t need:
mutex ❌
condition variable ❌

-----------------------------------------------------------------------------------------------------------------


8️⃣ What if set_value() is called before get_future()?

❌ Invalid:
std::promise<int> p;
p.set_value(10); // ❌ no shared state
Reason:
No place to store value
Throws std::future_error


//===============================================================================================================
#include <iostream>
#include <thread>
#include <future>// there is no <promise> header in the C++ Standard Library. The std::promise class is part of the <future> header. To use std::promise, you need to include the <future> header in your code.
#include <chrono>

void producer(std::promise<int> p) {
    std::this_thread::sleep_for(std::chrono::seconds(2)); // simulate delay
    std::cout << "🧑‍🍳 [Producer] Preparing value...\n";
    p.set_value(42); // send value to the future
}
void consumer(std::future<int> f) {
    std::cout << "🙋 [Consumer] Waiting for value...\n";
    int value = f.get(); // blocks until value is available
    std::cout << "✅ [Consumer] Got the value: " << value << "\n";
}
int main() {
    std::promise<int> p;
    std::future<int> f = p.get_future(); // link future with promise. 👉 Without this line, the consumer thread has no way to receive the result.

    std::thread t1(producer, std::move(p));
    std::thread t2(consumer, std::move(f));

    t1.join();
    t2.join();

    return 0;
}
/* 
✅ std::promise<int> ->
This is a 'type' — specifically, the class template instantiation of std::promise for type int. 
it doesn’t declare anything, just refers to the type itself.

std::promise<int> p;
it declares a promise object p that can store an int value to be delivered to another thread.
✅ Definition:
A std::promise<int> is a one-time communication channel used to send an int value from one thread (producer) to another thread (consumer) via a future.

✅ What is std::future<int>?
A std::future<int> is an object that allows one thread to wait for a result (an int in this case) that will be set by another thread — using the associated std::promise<int>.

🔄 What does get_future() do?
It creates a linked pair between the promise and the future.
Once this link is made:
1.The promise (p) sets the value using p.set_value(42);
2.The future (f) receives it when you call f.get();

*/
❌ Why std::promise CANNOT be copied  ??
std::thread t1(producer, p); // ❌ copy attempt
OR
std::promise<int> p1;
std::promise<int> p2 = p1;   // COPY (imaginary)
auto f = p1.get_future();

What would copying mean?
Two std::promise objects
Both pointing to the same shared state
Both allowed to call set_value()

Now we have:
p1 ─┐
    ├── shared state ── future
p2 ─┘
🚨 TWO promises, ONE shared state

Problem #1: Double set_value() (logical disaster)
p1.set_value(10);
p2.set_value(20);

❓ Which value should the future receive?
10?
20?
Last writer?
Undefined?

Problem #2: Race conditions (threading nightmare)
Imagine:
std::thread t1([&]{ p1.set_value(10); });
std::thread t2([&]{ p2.set_value(20); });
Now:
Two threads
Two promises
Writing simultaneously to the same shared state
❌ Data race
❌ Undefined behavior
❌ Broken synchronization guarantee

Problem #3: Who owns responsibility?
Promises represent responsibility, not just access.
If copied:
Who is responsible to call set_value()?
What if one forgets?
What if both call it?
This leads to:
unclear ownership
fragile code


-----------------------------------------------------------------------------------------------------------------
😬 What Happens if You Forget to Set the Promise?
std::promise<int> p;
std::future<int> f = p.get_future();

// But p.set_value(...) is never called!
int value = f.get();  // ❌ DEADLOCK: consumer waits forever!
🛑 This is a common bug — if the promise is not  fulfilled, the future waits indefinitely!


//================================================================================================================

😡 What If Producer Throws an Exception? ->> ✅  future.get() can also receive exceptions.
If a producer (the thread that sets the value on a std::promise) encounters an error:
-->  it can’t just throw and walk away — because the consumer (the thread waiting on std::future::get()) will be left hanging, expecting a value.

Thats where set_exception() comes in:
✅ Why std::current_exception()?
Because inside a catch block, std::current_exception() captures the currently active exception so it can be re-thrown later in another thread — through the future!

Method	                                    Meaning
p.set_value(x);	                            Passes a normal value to future
p.set_exception(std::current_exception());	Passes an error to future
f.get();	                                Either returns the value or rethrows the exception


🤯 Scenario: Uncaught Exception in Producer
void faulty_producer(std::promise<int> p) {
    // No try-catch block here
    throw std::runtime_error("Oops! Producer crashed!");
}
❗ What happens:
The exception is not caught, so the producer thread will terminate unexpectedly.
Since you never called set_value() or set_exception(), the std::future<int> is left hanging.
When the consumer calls f.get(), it will throw a std::future_error because the promise was broken.


❌ Scenario 1: Exception is NOT caught (broken promise)
#include <iostream>
#include <thread>
#include <future>
#include <stdexcept>

void unsafe_producer(std::promise<int> p) {
    // Uncaught exception — no set_exception() call!
    throw std::runtime_error("Oops! uncaught exception in unsafe_producer" ; 
}

int main() {
    std::promise<int> p;
    std::future<int> f = p.get_future();

    std::thread t;

    try {
        t = std::thread(unsafe_producer, std::move(p));
    } catch (...) {
        std::cerr << "Thread creation failed\n";
    }

    try {
        int value = f.get(); // Throws std::future_error
    } catch (const std::future_error& e) {
        std::cerr << "❌ Future error: " << e.what() << "\n";
    } catch (const std::exception& e) {
        std::cerr << "❌ General exception: " << e.what() << "\n";
    }

    if (t.joinable()) t.join();
    return 0;
}
🔴 Output:
❌ Future error: Broken promise

📌 Why "Broken Promise"?
Because:
The promise was moved into the producer thread.
But that thread threw an exception and exited.
So no value or exception was set — the promise was never fulfilled.
This causes f.get() to throw a std::future_error with broken_promise.

//---------------------------------------------------------------------------------------------------------------

✅ Scenario 2: Exception is handled with set_exception()
#include <iostream>
#include <thread>
#include <future>
#include <stdexcept>

void safe_producer(std::promise<int> p) {
    try {
        throw std::runtime_error("Something went wrong in safe_producer!");
    } catch (...) {
        p.set_exception(std::current_exception()); // Forward the exception
    }
}
int main() {
    std::promise<int> p;
    std::future<int> f = p.get_future();
    std::thread t(safe_producer, std::move(p));

    try {
        int value = f.get(); // This will rethrow the exception
    } catch (const std::exception& e) {
        std::cerr << "✅ Exception caught in main: " << e.what() << "\n";
    }
    t.join();
    return 0;
}
🟢 Output:
✅ Exception caught in main: Something went wrong in safe_producer!


