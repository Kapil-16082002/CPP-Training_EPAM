✅The queue in the C++ Standard Template Library (STL) is a container adapter that works on the principle of FIFO (First-In-First-Out).

Characteristics of Queue:
Elements are inserted at the back (tail) and removed from the front (head).
Works on FIFO (First-In-First-Out) principle.
It is an adapter container, which means it uses an underlying container (like deque or list) to store the data.

✅Syntax:
std::queue<T,Container>q;
T: Type of the elements.
Container: Type of the underlying container used to store data (default is std::deque<T>).

std::queue<int> q;  // default underlying container:  std::deque<int>q;
std::queue<int,std::list<int>>q;

std::deque (Default): The double-ended queue (std::deque) is the default container for std::queue. 
Because It provides efficient insertion and removal at both ends.

✅you cannot use std::vector as an underlying container for std::queue in C++ STL 
because std::vector does not fulfill all the necessary requirements of the underlying container expected by std::queue.
Requirements like:
push_back() - To add an element to the end (used in queue::push()).
pop_front() - To remove an element from the front (used in queue::pop()).
While std::deque provides both push_back() and pop_front(), the std::vector does not implement a pop_front() function efficiently 
because removing an element from the front of the vector requires shifting all the subsequent elements, which can be costly (O(n) in time complexity).


✅Function	   Description
push()	        q.push(10); // Adds 10 to the back of the queue
emplace()	    q.emplace(20); // Constructs 20 at the back of the queue
pop()	        q.pop(); // Removes the front element
front()	        cout << q.front(); // Prints the front element
back()	        cout << q.back(); // Prints the back element
empty()	        cout << (q.empty() ? "Empty" : "Not empty"); // Checks if queue is empty
size()	        cout << q.size(); // Prints the size of the queue
swap()	        q2.swap(q1); // Exchanges contents of q1 and q2

Time Complexity of Queue Operations
Function	Underlying Container: std::deque	Underlying Container: std::list	  Notes
push()	Best: O(1), Avg: O(1), Worst: O(1)	 Best: O(1), Avg: O(1), Worst: O(1)	Adds an element at the back of the queue. Both containers provide constant-time insertion at the back.
emplace()Best: O(1), Avg: O(1), Worst: O(1)	Best: O(1), Avg: O(1), Worst: O(1)	Similar to push(), constructs and inserts an element at the back in constant time.
pop()	Best: O(1), Avg: O(1), Worst: O(1)	Best: O(1), Avg: O(1), Worst: O(1)	Removes the front element in constant time. No shifting/rearranging is needed.
front()	Best: O(1), Avg: O(1), Worst: O(1)	Best: O(1), Avg: O(1), Worst: O(1)	Accessing the front element is always constant time.
back()	Best: O(1), Avg: O(1), Worst: O(1)	Best: O(1), Avg: O(1), Worst: O(1)	Accessing the back element is constant time for both containers.
empty()	Best: O(1), Avg: O(1), Worst: O(1)	Best: O(1), Avg: O(1), Worst: O(1)	Checking if the queue is empty is constant time since size is directly available.
size()	Best: O(1), Avg: O(1), Worst: O(1)	Best: O(1), Avg: O(1), Worst: O(1)	Retrieving size is always constant time. Both containers maintain an internal size counter.
swap()	Best: O(1), Avg: O(1), Worst: O(1)	Best: O(1), Avg: O(1), Worst: O(1)	Swapping two queues is constant time as it exchanges their internal storage references/pointers.


✅Use Cases of Queue:
1.Task Scheduling (CPU or OS):
In an operating system, tasks are scheduled based on their arrival time (FIFO) or priority. 

2.Printing Jobs (Print Spooler):
Printers queue incoming print jobs so that documents are printed in the order they were received.

3.Customer Service / Call Center Systems:
Customer requests are handled in the order they are received, whether via phone calls or chat.

4.Waiting Lines (Queues in Real Life):
Scenario: People lining up in a supermarket or at a bank for service form a queue

5.Breadth-First Search (BFS) in Graphs or Trees:
Queue is used for exploring nodes level by level in problems like shortest path, social network connections, etc.

6.Job/Resource Allocation in Multi-Threaded Applications:
Workers or threads in an application take tasks from a queue to execute them sequentially.




