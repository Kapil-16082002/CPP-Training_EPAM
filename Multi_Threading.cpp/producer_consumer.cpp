Producer-Consumer Problem(or  bounded buffer problem) using Semaphores — a classic synchronization problem where:

The Producer generates data and puts it in a buffer.
The Consumer takes data from the buffer and processes it.
You have a bounded buffer (e.g., size 5), so Producer must wait if it’s full, and Consumer must wait if it’s empty.

🧑‍💻 C++ Code: Producer-Consumer Using Semaphores
#include <iostream>
#include <thread>
#include <semaphore>
#include <vector>
#include <queue>
#include <chrono>

const int BUFFER_SIZE = 5;
std::queue<int> buffer;
// Semaphores
std::counting_semaphore<BUFFER_SIZE> empty_slots(BUFFER_SIZE); // initially, all slots are empty
std::counting_semaphore<BUFFER_SIZE> full_slots(0);            // initially, no full slots
std::binary_semaphore mutex(1);                                // binary semaphore as mutex

void producer(int id) {
    for (int i = 0; i < 5; ++i) {
        int item = id * 100 + i; // create a unique item
        empty_slots.acquire();   // wait for an empty slot
        mutex.acquire();         // lock access to buffer

        buffer.push(item);
        std::cout << "🟢 Producer " << id << " produced item: " << item << "\n";

        mutex.release();         // unlock buffer
        full_slots.release();    // signal full slot

        std::this_thread::sleep_for(std::chrono::milliseconds(500)); // simulate work
    }
}
void consumer(int id) {
    for (int i = 0; i < 5; ++i) {
        full_slots.acquire();    // wait for a full slot
        mutex.acquire();         // lock access to buffer

        int item = buffer.front();
        buffer.pop();
        std::cout << "🔴 Consumer " << id << " consumed item: " << item << "\n";

        mutex.release();         // unlock buffer
        empty_slots.release();   // signal empty slot

        std::this_thread::sleep_for(std::chrono::milliseconds(8)); // simulate processing
    }
}
int main() {
    std::thread p1(producer, 1);  // Produces 5 items
    std::thread p2(producer, 2);  // Produces 5 items
    std::thread c1(consumer, 1);  // Consumes 5 items
    std::thread c2(consumer, 2);  // Consumes 5 items

    p1.join();
    p2.join();
    c1.join();
    c2.join();

    std::cout << "✅ All items produced and consumed.\n";
    return 0;
}
📦 Sample Output: 🧠 The Actual Output Can Vary! but total output lines will be (5+5+5+5+1)=21 lines of output
🟢 Producer 1 produced item: 100
🟢 Producer 2 produced item: 200
🔴 Consumer 1 consumed item: 100
🔴 Consumer 2 consumed item: 200
✅ All items produced and consumed.

🧠 How It Works:
🔄 For Each Producer:
1.Wait for an empty slot (empty_slots.acquire()).
2.Lock buffer (mutex.acquire()).
3.Push item.
4.Unlock buffer.
5.Signal that a new full slot is available (full_slots.release()).

🔄 For Each Consumer:
1.Wait for a full slot (full_slots.acquire()).
2.Lock buffer (mutex.acquire()).
3.Pop item.
4.Unlock buffer.
5.Signal that a new empty slot is available (empty_slots.release()).

💡 Real-World Use Cases:
Thread-safe job queues or event pipelines
Task schedulers with bounded workers
Streaming buffers for audio/video processing

/* 
Let’s now create a flexible version of the Producer-Consumer Problem using semaphores, where you can easily adjust:

The number of producers
The number of consumers
The number of items each producer produces
The buffer size

✅ Full Flexible Version in C++

#include <iostream>
#include <thread>
#include <semaphore>
#include <queue>
#include <vector>
#include <chrono>

const int BUFFER_SIZE = 5;
const int NUM_PRODUCERS = 2;
const int NUM_CONSUMERS = 3;
const int ITEMS_PER_PRODUCER = 4;

std::queue<int> buffer;

// Semaphores
std::counting_semaphore<BUFFER_SIZE> empty_slots(BUFFER_SIZE); // start with all empty
std::counting_semaphore<BUFFER_SIZE> full_slots(0);            // start with no full slots
std::binary_semaphore mutex(1);                                // binary lock

void producer(int id) {
    for (int i = 0; i < ITEMS_PER_PRODUCER; ++i) {
        int item = id * 100 + i;  // Unique item
        empty_slots.acquire();
        mutex.acquire();

        buffer.push(item);
        std::cout << "🟢 Producer " << id << " produced item: " << item << "\n";

        mutex.release();
        full_slots.release();

        std::this_thread::sleep_for(std::chrono::milliseconds(300)); // Simulate work
    }
}

void consumer(int id, int total_items_to_consume) {
    for (int i = 0; i < total_items_to_consume; ++i) {
        full_slots.acquire();
        mutex.acquire();

        int item = buffer.front();
        buffer.pop();
        std::cout << "🔴 Consumer " << id << " consumed item: " << item << "\n";

        mutex.release();
        empty_slots.release();

        std::this_thread::sleep_for(std::chrono::milliseconds(500)); // Simulate processing
    }
}

int main() {
    int total_items = NUM_PRODUCERS * ITEMS_PER_PRODUCER;
    int base_consume = total_items / NUM_CONSUMERS;
    int extra = total_items % NUM_CONSUMERS;

    std::vector<std::thread> producers;
    std::vector<std::thread> consumers;

    // Launch producers
    for (int i = 1; i <= NUM_PRODUCERS; ++i) {
        producers.emplace_back(producer, i);
    }

    // Launch consumers with load balancing
    for (int i = 1; i <= NUM_CONSUMERS; ++i) {
        int items_to_consume = base_consume + (i <= extra ? 1 : 0);
        consumers.emplace_back(consumer, i, items_to_consume);
    }

    for (auto& p : producers) p.join();
    for (auto& c : consumers) c.join();

    std::cout << "✅ All items produced and consumed.\n";
    return 0;
}
*/