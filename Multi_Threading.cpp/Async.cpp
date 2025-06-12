
🔍 What is std::async?
std::async is a high-level way to run a function asynchronously and get the result later using a std::future.
It’s simpler and safer than manually using std::thread, std::promise, and std::future.

(run a function asynchronously means:)-> 
Execute a function in a separate thread so the main program can continue doing other things without waiting for that function to finish immediately.

Advantages of std::async:
Automatic Thread Management: You don’t need to manage thread creation or joining manually.
Exception Handling: If a thread throws an exception, it can be caught via the future.get() method.


✨ Syntax
std::future<ReturnType> future = std::async(std::launch::async, your_function, args...);
std::launch::async → forces the function to run in a new thread
future.get() blocks until the function returns
You don’t need to create or join threads manually


🧪 Example: Sum of Numbers Asynchronously
#include <iostream>
#include <future>
#include <chrono>

int calculateSum(int a, int b) {
    std::this_thread::sleep_for(std::chrono::seconds(2)); // simulate delay
    std::cout << "🧠 [Worker] Calculating " << a << " + " << b << "\n";
    return a + b;
}
int main() {
    std::cout << "🚀 Starting async task...\n";

    std::future<int> result = std::async(std::launch::async, calculateSum, 10, 20);
    /* 
    Async with Lambda
auto future = std::async(std::launch::async, [] {
    std::this_thread::sleep_for(std::chrono::seconds(1));
    return 99;
});
std::cout << "Result: " << future.get() << "\n";
    */

    std::cout << "⏳ Doing other work while waiting...\n";
    cout<<"✅Hlo Kapil"<<std::endl;

    // Wait for result
    int sum = result.get();  // blocks until done

    std::cout << "✅ Result is: " << sum << "\n";

    return 0;
}
🧾 Output:
🚀 Starting async task...
⏳ Doing other work while waiting...
✅ Hlo Kapil
🧠 [Worker] Calculating 10 + 20
✅ Result is: 30


🧠 What's Happening Internally?
std::async spawns a new thread (if std::launch::async is used).
That thread runs calculateSum(10, 20).
The result is stored in a shared state.
future.get() blocks until that result is ready.

✅ Advantages Over Promise

Feature	              std::async	                            promise/future
Easy to use	         ✅	                                      ❌ Manual setup
Manages thread	     ✅ (auto)	                              ❌ (manual)
Exception forwarding ✅ Built-in	                              ✅ Manual
One-liner usage	     ✅	                                      ❌

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Producer-Consumer Problem Using std::async
Overview:
Producer: Generates data and places it in a shared buffer (queue).
Consumer: Takes data from the shared buffer and processes it.
We’ll use std::future to communicate between the producer and consumer.

Key points:
std::async is used to launch tasks asynchronously (in the background).
The producer and consumer will run concurrently, and std::future will allow us to get the result or handle exceptions.

Code Example:
#include <iostream>
#include <thread>
#include <future>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <chrono>

std::queue<int> buffer;           // Shared buffer between producer and consumer
std::mutex mtx;       //A mutex to ensure that only one thread (either producer or consumer) accesses the buffer at a time.
std::condition_variable cv;       // Condition variable to signal between threads

// Producer function: adds data to the buffer
void producer(int id) {
    for (int i = 0; i < 5; ++i) {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        
        // Locking the buffer before inserting data
        std::lock_guard<std::mutex> lock(mtx);
        
        buffer.push(i);
        std::cout << "Producer " << id << " produced: " << i << "\n";
        
        // Notify consumer that data is available
        cv.notify_all();
    }
}
// Consumer function: takes data from the buffer
void consumer(int id) {
    for (int i = 0; i < 5; ++i) {
        std::unique_lock<std::mutex> lock(mtx);
        
        // Wait until there is data in the buffer
        cv.wait(lock, []{ return !buffer.empty(); });
        
        int value = buffer.front();
        buffer.pop();
        
        std::cout << "Consumer " << id << " consumed: " << value << "\n";
        
        // Simulate processing time
        std::this_thread::sleep_for(std::chrono::milliseconds(150));
    }
}

int main() {

    auto producer_future = std::async(std::launch::async, producer, 1);//starts the producer function asynchronously in the background.
    auto consumer_future = std::async(std::launch::async, consumer, 1);
    
    // Wait for both producer and consumer to finish
    producer_future.get();
    consumer_future.get();
    
    return 0;
}