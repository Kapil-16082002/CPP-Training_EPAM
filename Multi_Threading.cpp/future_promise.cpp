
🔍 What is the Future-Promise Mechanism?
std::promise<T> allows one thread to produce a value (or an exception) at some point in the future.
std::future<T> allows another thread to wait for that value.
Its like a single-use channel from one thread (producer) to another (consumer).

🧠 Real-world Analogy
Think of a food delivery:
🧑‍🍳 The chef (promise) prepares food.
🚶 The customer (future) waits for food to arrive.
Until the chef delivers the food, the customer just waits.

#include <iostream>
#include <thread>
#include <future>
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
    std::future<int> f = p.get_future(); // link future with promise

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
//-----------------------------------------------------------------------------------------------------------------
😬 What Happens if You Forget to Set the Promise?
std::promise<int> p;
std::future<int> f = p.get_future();

// But p.set_value(...) is never called!
int value = f.get();  // ❌ DEADLOCK: consumer waits forever!
🛑 This is a common bug — if the promise is not  fulfilled, the future waits indefinitely!


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

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
    throw std::runtime_error("Oops! uncaught exception in unsafe_producer");
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


