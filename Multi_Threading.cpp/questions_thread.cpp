
🧨 When is a thread destroyed in C++?
A thread is destroyed (i.e., the std::thread object gets cleaned up) in C++ when:

✅ Case 1: You call join()
The main thread waits for the thread to finish.

Once the thread finishes its work and returns, it is cleaned up properly.
std::thread t(myFunction);
t.join();  // Thread is destroyed after finishing work


✅ Case 2: You call detach()
The thread runs in the background, and the main thread doesn’t wait.
Once the thread finishes its work on its own, it is also cleaned up automatically.
BUT: you are no longer managing that thread after detach().

std::thread t(myFunction);
t.detach();  // Thread is destroyed after work finishes (on its own)


❌ Thread object destroyed without join() or detach()?
This causes a crash or exception! 🚨

void myFunction() {}
int main() {
    std::thread t(myFunction);
    // ❌ No join or detach!
    return 0;
}
🧨 This results in std::terminate() being called because the thread is still active when the std::thread object is destroyed.
/* Explanation of above line:
🔹 "the thread is still active"
The thread t is running (or ready to run), doing the work inside myFunction().

🔹 "the std::thread object is destroyed"
When main() ends, the variable t (of type std::thread) goes out of scope.

In C++, when an object goes out of scope, its destructor runs to clean it up.

🔹 "std::terminate() is called"
If the std::thread object is still connected to a running thread when it is destroyed, C++ throws an error.

That error immediately calls a special function called std::terminate() → it stops the entire program 💥
*/

📌 So, Remember:
Action	           Thread Status	          Thread is Destroyed When
.join()	           Main waits	           After thread finishes
.detach()	       Runs independently	   After thread finishes
No join or detach	❌ Undefined behavior	Program may crash

//---------------------------------------------------------------------------------------------------------------
why "C++ does not allow std::thread objects to be destroyed while still joinable."??

🧠 Short Answer:
Because if the thread is still joinable and the std::thread object is destroyed, it would lead to undefined behavior, like:
memory access to destroyed variables,
corruption of data,
crashes,
or hard-to-find bugs.

So C++ forces programmer to make a conscious decision:
👉 "Either you wait for this thread to finish (join()), or you let it go on its own (detach()). But you MUST do one of these before the thread object is destroyed."

If a std::thread is still running and the std::thread object is destroyed without calling join() or detach(), the std::thread destructor terminates the program immediately by calling std::terminate().

The destructor of std::thread checks if the thread is joinable.
If it is joinable, it means:
1.The thread is still running, or
2.It’s finished, but you haven’t taken responsibility for it (join or detach).

So to force programmer to make an explicit decision, the destructor throws std::terminate() if you didn’t handle it.


⚠️ What Would Happen If It Did Allow It?
Lets say C++ allowed you to destroy a thread object without calling join() or detach():

Scenario:
void task() {
    std::cout << "Doing work..." << std::endl;
}

int main() {
    std::thread t(task); // thread starts running
    // Thread t is running independently now

    // Thread object is destroyed here (no join/detach)
    return 0;
}
Possible dangers:
The thread t is still running, but the main thread is exiting.
Any local variables or resources used by task() might get destroyed.
Thread t might access memory that no longer exists.
You’ll face crashes, data races, and undefined behavior.

/*
📌 1. What is a joinable thread?
A std::thread is joinable when:
1.It has started a thread, AND
2.You haven’t called join() or detach() on it yet.

Example:
std::thread t(myFunction); // ✅ joinable
// Now t is a running thread, and no one is managing it yet
So, this thread is considered joinable (i.e., "waiting for someone to manage it"). */

//---------------------------------------------------------------------------------------------------------------




 