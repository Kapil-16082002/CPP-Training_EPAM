✅When Does Iterator Invalidation Occur in std::list?
1. Insertion (insert or emplace):
The std::list insertion operation (insert) does NOT invalidate iterators pointing to other elements.

int main() {

    std::list<int> myList = {1, 2, 3};

    // Get an iterator pointing to the second element
    auto it = myList.begin();
    ++it; // Points to the element 2

    std::cout << "Before insertion: Iterator points to: " << *it << "\n"; // output:   2 

    // Insert a new element after the second element
    myList.insert(it, 10); // Inserts 10 before element 2,    output: 1 10 2 3

    // The iterator to element 2 remains valid because of `std::list`'s properties
    std::cout << "After insertion: Iterator points to: " << *it << "\n";  // output:   2

}
✅🔥 Why Is Iterator Still Valid?
Because std::list is a doubly linked list, not a contiguous container, 
where each element is stored in the form of nodes and each node is connected to each other by pointers.

So memory looks like:
NodeA (1)  -->  NodeB (2)  -->  NodeC (3)
Your iterator it stores pointer to: NodeB


🔹 What Happens During insert(it, 10)?
myList.insert(it, 10);

Internally:
New node is allocated (NodeX)
Pointers are adjusted

After insertion:
[1] <-> [10] <-> [2] <-> [3]

Important:
👉 NodeB (which stores 2) is NOT moved
👉 NodeB is NOT destroyed
👉 Its memory address does NOT change
So iterator still points to same NodeB.


🔥 That’s Why It’s Valid
Because:
No elements are shifted
No reallocation happens, nomemory address does NOT change
Existing nodes remain untouched
Only pointers are changed

=================================================================================================================

✅2. Removal (erase):
Only iterators pointing to the erased element are invalidated.
Iterators pointing to the remaining elements remain valid.

int main() {
    std::cout << "\n--- Iterator Invalidation on Erase in std::list ---\n";

    std::list<int> myList = {1, 2, 3, 4, 5};

    auto it = myList.begin();
    ++it; // Points to the element 2

    std::cout << "Before erase: Iterator points to: " << *it << "\n";

    // Erase the second element
    myList.erase(it);

    // Dereferencing `it` after erase causes undefined behavior
    // std::cout << "After erase: Iterator points to: " << *it << "\n"; // Undefined behavior!

    // SOLUTION: Use a valid iterator after erase
    it = myList.begin(); // Re-acquire a valid iterator
    std::cout << "Valid iterator after erase points to: " << *it << "\n";

    // Print the updated list
    std::cout << "List contents: ";
    for (const auto& val : myList) {
        std::cout << val << " ";
    }
}


3. Splice (splice):
Splicing elements from one list to another invalidates iterators to the spliced elements in the source list. 
The destination list’s iterators remain valid.


4. Container Destruction:
Destroying the list invalidates all iterators, as the memory backing the nodes is freed.
