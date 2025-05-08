\
🧠 What is std::atomic?
std::atomic is a template class in C++ that ensures atomic (indivisible) operations on a variable.
That means no two threads can interfere with each other during a read-modify-write operation.

std::atomic<T> ensures that reads and writes to a variable are atomic — i.e., they happen completely or not at all. 
It prevents race conditions on simple types without needing locks.

⚙️ Why Use std::atomic?
✅ Thread-safe operations
✅ No need to manually lock/unlock like std::mutex
✅ Better performance (no kernel-level context switching)
❌ Only works well for simple data types like int, bool, pointers  

🔥 Example Without Atomic (Race Condition)
#include <iostream>
#include <thread>

int counter = 0;

void increment() {
    for (int i = 0; i < 10; ++i) {
        ++counter;  // Not safe!
    }
}
int main() {
    std::thread t1(increment);
    std::thread t2(increment);

    t1.join();
    t2.join();

    std::cout << "Counter: " << counter << std::endl;
    return 0;
}
❌ Output: Unreliable due to race condition.
/* 
Because both threads are accessing and modifying counter at the same time without any synchronization, you may get unexpected results like:
Counter: 14
Counter: 17
Counter: 19
Counter: 20  ✅ (but rare)
The final value of counter could be anywhere between 10 and 20, depending on how the instructions from both threads interleave.
*/
//------------------------------------------------------------------------------------------------------------
✅ Fixed with std::atomic
#include <iostream>
#include <thread>
#include <atomic>

std::atomic<int> counter(0);  // atomic variable
void increment() {
    for (int i = 0; i < 10; ++i) {
        ++counter;  // safe atomic operation
    }
}
int main() {
    std::thread t1(increment);
    std::thread t2(increment);

    t1.join();
    t2.join();

    std::cout << "Counter: " << counter << std::endl;
    return 0;
}
✅ Output:
Counter: 20
No race condition. Atomic operations ensure thread safety for basic types.

✍️ Other Useful Atomic Operations
If you use std::atomic<int> a;, you can also do:
a.store(10);        // set value
int x = a.load();   // get value
a.fetch_add(1);     // atomic increment
a.fetch_sub(1);     // atomic decrement

//----------------------------------------------------------------------------------------------------------------
#include <iostream>
#include <thread>
#include <mutex>
#include <atomic>

std::atomic<int> g=0;

void fun(){
    for(int i=1;i<=10;i++,g=i) std::cout<<g<<std::endl;
}
int main() {

    std::thread t(fun);
    {
    for(int i=100;i<=110;i++,g=i) std::cout<<g<<std::endl;
    }
   t.join();
   return 0;
}
⚠️ Expected Behavior:
What output might look like (one of many possibilities):
100
101
1
2
3
102
103
4
5
6
7
104
105
8
9
106
10
107
108
109
110

/*   Explanation:
🔥 Key Things Happening:
1. g is atomic ✅
This means:
Reading and writing g is safe from tearing or corruption.
But: It does NOT guarantee overall correctness or print order.

2. No Synchronization for std::cout ❌
std::cout is not thread-safe by default.
If both threads print at the same time, output lines can get interleaved or jumbled.

3. Two Threads Are Updating and Printing g at the Same Time
fun() writes 1..10 to g and prints it.
main() writes 100..110 to g and prints it.

These loops are running in parallel.
*/