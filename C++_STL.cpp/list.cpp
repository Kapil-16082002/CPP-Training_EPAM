The C++ STL provides two types of linked list containers:

std::list - Doubly Linked List
std::forward_list - Singly Linked List
Both of these are part of the <list> header. 
These containers are used when frequent insertion or deletion at arbitrary positions in a sequence is required, with less concern for random access.


✅1. std::list (Doubly Linked List)
The std::list container represents a doubly linked list, 
where:
Each node contains a value and pointers to both its previous and next elements.
This enables efficient bidirectional traversal of the container and supports iterators for forward and reverse directions.
Key Points About std::list:

Dynamic size: Can grow and shrink as elements are inserted/removed.
Maintains order: Elements are stored in the order you insert them.
Efficient insertion and deletion: Insertion, removal, and moving elements are constant-time operations, regardless of position.
No random access: Unlike std::vector, elements cannot be accessed directly via indexing (list[i] is not possible).
Bidirectional iterators: Supports both forward and reverse iteration (begin(), end(), rbegin(), and rend()).


✅2. std::forward_list (Singly Linked List)
The std::forward_list container represents a singly linked list, with:

Each node pointing only to the next element (no previous pointer).
This is a lightweight container compared to std::list.
Key Points About std::forward_list:

Lightweight: It requires less memory as it only stores the "next" pointer.
Efficient insertion/removal: Ideal for scenarios where frequent addition/removal of elements occurs but traversal is mostly unidirectional.
Single-direction traversal: You can only traverse the list forward.
Supports forward iterators only, making operations like reverse iteration impossible.

/*  
✅Internal Structure of std::list
1.Doubly Linked List:
   A pointer to the data (the value stored in the list node).
   A pointer to the next node.
   A pointer to the previous node.
The list itself maintains two additional pointers:
   A pointer to the head of the list (the first element).
   A pointer to the tail of the list (the last element).
The memory for the nodes in a std::list is non-contiguous and allocated dynamically on a per-node basis.
2.Node Representation:
struct ListNode {
    T data;           // The data stored in the node
    ListNode* next;   // Pointer to the next node
    ListNode* prev;   // Pointer to the previous node
};

✅Memory Allocation in Insertion
1. Dynamic Memory Allocation:
When an element is inserted into the std::list, a new node is created dynamically using std::allocator (or the default dynamic memory system, typically via operator new).
Memory for the new node's data field, along with the prev and next pointers, is allocated dynamically.

2.Performance & Complexity:
The insertion operation has a complexity of O(1) if performed at a known position (e.g., using an iterator pointing to the desired location).
Unlike std::vector, std::list does not require shifting elements or reallocation of the entire container when inserting.

✅Memory Deallocation in Deletion:
1.Dynamic Memory Deallocation:
During deletion, the node to be removed is first detached from the list by updating the pointers in the surrounding nodes.
The memory allocated to the node is then deallocated using std::allocator::deallocate (or the default delete operator internally).

2.Performance & Complexity:
Like insertion, deletion is also an O(1) operation as the node to be removed can be located using an iterator, and no shifting or reallocation of other elements is necessary.


✅Advantages:
Efficient O(1) insertion and deletion at arbitrary positions.
Iterators remain valid even after inserting or deleting elements (except for iterators pointing to deleted elements).
No need to shift or copy elements when modifying the list.

✅Disadvantages:
Memory overhead per node is high due to the storage of two pointers (prev and next).
Non-contiguous memory allocation may cause poor cache performance and memory fragmentation.
Greater memory usage compared to std::vector or std::deque due to dynamic allocation of nodes.

*/

✅inbuilt functions:

1. Constructors std::list

std::list<int> lst;                        // Default constructor
std::list<int> lst2(5);                    // Creates a list with 5 default-initialized elements, value=0 default
std::list<int> lst3(5, 100);               // Creates a list with 5 elements, each of value 100
std::list<int> lst4 = {1, 2, 3, 4};        // List initialization with initializer list
std::list<int> lst5(lst4.begin(), lst4.end()); // Range constructor

2.std::forward_list Constructors:

std::forward_list<int> flst;                  // Default constructor
std::forward_list<int> flst2(5);              // Creates a forward list with 5 default-initialized elements
std::forward_list<int> flst3(5, 100);         // Creates a forward list with 5 elements of value 100
std::forward_list<int> flst4 = {1, 2, 3, 4};  // Forward list initialization with initializer list
std::forward_list<int> flst5(flst4.begin(), flst4.end()); // Range constructor


✅2. Size
1.std::list
List has built-in support for size():
lst.size(); // Returns the number of elements in the list

2.std::forward_list
No direct size() support. Use this instead:
std::distance(flst.begin(), flst.end()); // Calculate the size manually


✅3. Modifiers - Adding and Removing Elements
1.std::listInsertion and Removal API:

lst.push_front(1);  // Inserts 1 at the front
lst.push_back(2);   // Inserts 2 at the back
lst.pop_front();    // Removes the first element
lst.pop_back();     // Removes the last element

2.std::forward_list
Only supports operations on the front:

flst.push_front(1);  // Inserts 1 at the front
flst.pop_front();    // Removes the first element


✅4. Element Access
1.std::list Access first and last elements:

lst.front(); // Accesses the first element
lst.back();  // Accesses the last element

2.std::forward_list Only supports accessing the front:

flst.front(); // Accesses the first element
// Doesn't support accessing the last element


✅5. Iterators
std::list Supports bidirectional iterators, including reverse iterators:

lst.begin();        // Iterator to first element
lst.end();          // Iterator to "past the last" element
lst.rbegin();       // Reverse iterator to last element
lst.rend();         // Reverse iterator to "past the first" element

std::forward_list Supports forward iterators only:

flst.begin();       // Iterator to first element
flst.end();         // Iterator to "past the last" element


✅6. Sorting
std::list Supports sorting of elements directly:
lst.sort(); // Sorts the list in ascending order

std::forward_list Also supports sorting:
flst.sort(); // Sorts the forward list in ascending order

✅std::erase()
The erase function in the C++(STL) is particularly useful for removing elements from a std::list.
Return Value::
1.When erasing a single element:
Returns an iterator pointing to the next element after the erased one.
If the erased element is the last in the list, it returns list.end() (an iterator that represents "past-the-end").

2.When erasing a range:
Returns an iterator pointing to last (the element right after the range being erased), or list.end() if the erased range includes the end of the list.


✅8. Removal of Elements
std::list Multiple element removal functions:

lst.remove(5); // Remove all elements with the value 5
lst.remove_if([](int x) { return x % 2 == 0; }); // Remove elements matching a predicate
lst.clear();   // Clears all elements

std::forward_list Removal functions:

flst.remove(5); // Remove all elements with the value 5
flst.remove_if([](int x) { return x % 2 == 0; }); // Remove elements matching a predicate
flst.clear();    // Clears all elements


✅10. Unique
std::list Removes consecutive duplicate values:

lst.unique(); // Removes consecutive duplicate elements
lst.unique([](int a, int b) { return a == b; }); // With custom predicate

std::forward_list Similarly supports unique():

flst.unique(); // Removes consecutive duplicate elements
flst.unique([](int a, int b) { return a == b; }); // With custom predicate


✅9. Reverse
std::list Directly supports reversing the order of elements:
lst.reverse(); // Reverses the list in-place

std::forward_list
No reverse() function. You must manually reverse a forward_list.

void reverseForwardList(std::forward_list<int>& flist) {
    std::forward_list<int> reversedList;
    // Iterate through the original list
    for (int val : flist) {
        // Insert each element at the front of the new list
        reversedList.push_front(val);
    }
    // Assign the reversed list back to the original forward list
    flist = reversedList;
}



✅11. Merge
std::list Supports merging two sorted lists:
lst1.merge(lst2); // Merges lst2 into lst1. Both lists must be sorted.

std::forward_list Also supports merging operation:
flst1.merge(flst2); // Merges flst2 into flst1. Both lists must be sorted.


✅7. Splicing
std::list Directly supports splitting and moving elements between lists:
lst.splice(iteratorPos, lst2); // Transfers all elements from lst2 into lst at position iteratorPos

std::forward_list Supports splicing, but only with efficient front operations:
flst.splice_after(iteratorPos, flst2); // Transfers all elements from flst2 after iteratorPos



✅12. Emplace Functions (Modern Additions)
std::list Allows in-place construction of elements:

lst.emplace_front(1); // Constructs element at the front
lst.emplace_back(2);  // Constructs element at the back
lst.emplace(iteratorPos, 3); // Constructs and inserts element at iteratorPos

std::forward_list Only supports in-place construction at the front:
flst.emplace_front(1); // Constructs element at the front


// advance()

Comparison Table: Functions and Time Complexity
Category	      Function	                          Time Complexity (Best, Avg, Worst)
Constructors	  std::list<int> lst;                     O(1), O(1), O(1)
                 std::list<int> lst2(5);	              O(n), O(n), O(n)
                 std::list<int> lst3(5, 100);	          O(n), O(n), O(n)
                 std::list<int> lst4 = {1, 2, 3, 4};	  O(n), O(n), O(n)
                std::list<int> lst5(lst4.begin(), lst4.end());	O(n), O(n), O(n)
                  std::forward_list<int> flst;	         O(1), O(1), O(1)
                  std::forward_list<int> flst2(5)	     O(n), O(n), O(n)
                  std::forward_list<int> flst3(5, 100)	 O(n), O(n), O(n)
                  std::forward_list<int> flst4 = {1, 2, 3, 4};	O(n), O(n), O(n)

	           
size               lst.size()	                              O(1), O(1), O(1)
                   std::distance(flst.begin(), flst.end())	  O(n), O(n), O(n)
Modifiers	
                   lst.push_front(1)	                      O(1), O(1), O(1)
                   lst.push_back(2)	                          O(1), O(1), O(1)
                   lst.pop_front()	                          O(1), O(1), O(1)
                   lst.pop_back()	                          O(1), O(1), O(1)
                   flst.push_front(1)	                      O(1), O(1), O(1)
                   flst.pop_front()	                          O(1), O(1), O(1)
Element Access	
                   lst.front()	                             O(1), O(1), O(1)
                   lst.back()	                             O(1), O(1), O(1)
                   flst.front()	                             O(1), O(1), O(1)
Iterators	
                   lst.begin() / lst.end()	                  O(1), O(1), O(1)
                   lst.rbegin() / lst.rend()	             O(1), O(1), O(1)
                   flst.begin() / flst.end()	              O(1), O(1), O(1)
Sorting	
                    lst.sort()	                           O(n log n), O(n log n), O(n log n)
                  flst.sort()	O(n log n), O(n log n), O(n log n)
Removing	
                  lst.remove(5)	                          O(n), O(n), O(n)
                  lst.remove_if(predicate)	              O(n), O(n), O(n)
                  lst.clear()	                          O(n), O(n), O(n)
                 flst.remove(5)	                          O(n), O(n), O(n)
                flst.remove_if(predicate)	               O(n), O(n), O(n)
                flst.clear()	                            O(n), O(n), O(n)
Reverse	
                lst.reverse()	                            O(n), O(n), O(n)
                reverseForwardList() (custom function)	    O(n), O(n), O(n)

                
Unique	        
                lst.unique()	                         O(n), O(n), O(n)
                flst.unique()	                         O(n), O(n), O(n)
Merge	
                 lst1.merge(lst2)	                    O(n + m), O(n + m), O(n + m)
                 flst1.merge(flst2)	                    O(n + m), O(n + m), O(n + m)
Splicing	
                 lst.splice(iteratorPos, lst2)	         O(1), O(1), O(1)
                 flst.splice_after(iteratorPos, flst2)	 O(1), O(1), O(1)
Emplace	
                lst.emplace_front(1)	                 O(1), O(1), O(1)
                lst.emplace_back(2)	                     O(1), O(1), O(1)
                lst.emplace(iteratorPos, 3)	             O(1), O(1), O(1)
                flst.emplace_front(1)	                 O(1), O(1), O(1)