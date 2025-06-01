✅Iterator Invalidations in std::deque
std::deque is a double-ended queue container in C++, implemented as a sequence of memory segments (usually arrays). 
Because of this segmented memory structure, its iterator invalidation rules are different from those of linear containers like std::vector.

✅When Does Iterator Invalidation Occur in std::deque?
1.Insertion at the Front (push_front) or Back (push_back):
If the underlying memory needs to be reallocated (e.g., due to resizing), all iterators are invalidated because the sequence of memory segments changes.
If there is no reallocation (e.g., sufficient capacity for the new element), iterators pointing to unaffected elements remain valid.

int main() {
    std::cout << "\n--- Iterator Invalidations in std::deque ---\n";

    // Problem: Iterator invalidation on `push_back` and `push_front`
    std::cout << "\n--- Problem 1: Invalidating Iterators on Insertions ---\n";
    {
        std::deque<int> dq = {1, 2, 3};

        // Get an iterator pointing to the second element
        auto it = dq.begin() + 1; // Points to element 2

        // Insert elements at the back and front to trigger resizing
        dq.push_back(4);  // Insert at the end
        dq.push_front(0); // Insert at the front

        // Dereferencing the iterator after resizing causes undefined behavior
        // std::cout << "Iterator value: " << *it << "\n"; // Undefined behavior!

        // SOLUTION: Avoid using iterators after insertion unless re-validated
        it = dq.begin() + 1; // Refresh iterator to point to the updated position
        std::cout << "Safe iterator value after insertion: " << *it << "\n";
    }
}


2.Insertion within the Container (insert):
If elements are shifted (e.g., by inserting into the middle), all iterators are invalidated or iterators pointing to shifted elements become invalid.
Insertion near the ends generally does not cause shifts unless resizing occurs.


int main() {
    std::cout << "\n--- Iterator Invalidations in std::deque on Middle Insertion ---\n";

    std::deque<int> dq = {1, 2, 3, 4, 5};

    // Get an iterator pointing to the second element
    auto it = dq.begin() + 2; // Points to the element at index 2 (value = 3)

    std::cout << "Before insertion: Iterator points to: " << *it << "\n";

    // Insert a new element in the middle
    dq.insert(dq.begin() + 1, 10); // Insert value 10 at index 1

    // After insertion, the iterator `it` may be invalid because internal memory shifts in `std::deque`
    // Dereferencing the old iterator causes undefined behavior
    // std::cout << "After insertion: Iterator points to: " << *it << "\n"; // Undefined behavior!

    // SOLUTION: Always refresh the iterator to the intended element after insertion
    it = dq.begin() + 3; // Recompute iterator to point to element after the shift
    std::cout << "After insertion: Iterator points to: " << *it << "\n";

    // Print the contents of the deque
    std::cout << "Deque contents: ";
    for (const auto& val : dq) {
        std::cout << val << " ";
    }
    std::cout << "\n";

    return 0;
}


3.Element Removal (erase):
Removing elements invalidates only iterators referring to the removed elements. Iterators pointing to other elements remain valid.


int main() {
    std::cout << "\n--- Iterator Invalidations in std::deque ---\n";

    // Problem: Iterator invalidation on `erase`
    std::cout << "\n--- Problem 2: Invalidating Iterators on Erase ---\n";
    {
        std::deque<int> dq = {1, 2, 3, 4, 5};

        // Get an iterator pointing to the second element
        auto it = dq.begin() + 1; // Points to element 2

        // Erase the second element
        dq.erase(it);

        // Dereferencing the iterator after erase causes undefined behavior
        // std::cout << "Iterator value: " << *it << "\n"; // Undefined behavior!

        // SOLUTION: Avoid using iterators after erase; find the next valid one or revalidate
        it = dq.begin(); // Refresh iterator to point to a valid element
        std::cout << "Safe iterator value after erase: " << *it << "\n";
    }
}


4.Operations like resize:
Resizing the std::deque invalidates all iterators.


int main() {

    // Problem: Iterator invalidation on `resize`
    std::cout << "\n--- Problem 3: Invalidating Iterators on Resize ---\n";
    {
        std::deque<int> dq = {1, 2, 3, 4, 5};

        // Get an iterator pointing to the second element
        auto it = dq.begin() + 1; // Points to element 2

        // Resize the deque (e.g., to remove or add elements)
        dq.resize(3); // Resize to keep only the first 3 elements

        // Dereferencing the iterator causes undefined behavior
        // std::cout << "Iterator value: " << *it << "\n"; // Undefined behavior!

        // SOLUTION: Avoid using iterators after resize; acquire valid ones
        for (const auto& val : dq) {
            std::cout << val << " ";
        }
        std::cout << "\n";
    }

    return 0;
}

