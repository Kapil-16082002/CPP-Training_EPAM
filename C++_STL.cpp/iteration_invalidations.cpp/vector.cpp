✅What is Iterator Invalidation?
Iterator invalidation occurs when the underlying container is modified such that iterators pointing to elements in the container become invalidated (i.e., they can no longer be safely used). 

When an iterator is invalidated:
Dereferencing the iterator results in undefined behavior.
Using the iterator in loops or other operations can lead to runtime errors, memory corruption, or unexpected results.

✅1. Iterator Invalidations in std::vector
The std::vector is a dynamic array, and its iterator invalidation depends on operations that modify the size or capacity of the vector.

int main() {
    // Problem 1: Invalidation due to Reallocation
    std::cout << "\n--- Problem 1: Invalidation due to Reallocation ---\n";
    {
        std::vector<int> vec = {1, 2, 3};

        // Get an iterator pointing to the first element
        auto it = vec.begin(); // Iterator points to 1

        // Add enough elements to cause reallocation
        vec.push_back(4);
        vec.push_back(5);

        // Dereferencing the old iterator after reallocation causes undefined behavior
        // SOLUTION: Update iterators after modifying the vector
        std::cout << "Before reallocation: Iterator value = " << *it << "\n"; // MAY cause undefined behavior!

        // Update the iterator to the new valid location
        it = vec.begin(); // Correctly update iterator after modification
        std::cout << "After reallocation: Iterator value = " << *it << "\n";
    }

    // Problem 2: Invalidation due to Element Removal
    std::cout << "\n--- Problem 2: Invalidation due to Element Removal ---\n";
    {
        std::vector<int> vec = {1, 2, 3, 4, 5};

        // Get an iterator pointing to the second element
        auto it = vec.begin() + 1; // Iterator points to 2

        // Remove the second element (and shift subsequent elements)
        vec.erase(vec.begin() + 1); // Removes '2'

        // Dereferencing the iterator now causes undefined behavior
        std::cout << "Before removal: Iterator value = " << *it << "\n"; // MAY cause undefined behavior!

        // SOLUTION: Update iterators after modifying the vector
        it = vec.begin() + 1; // Update to point to the new valid element
        std::cout << "After removal: Iterator value = " << *it << "\n"; // Correct safe usage
    }

    std::cout << "\n--- Problem 3: Invalidation due to Capacity Change ---\n";
    {
        std::vector<int> vec = {1, 2, 3};

        // Reserve a larger capacity than the current size
        vec.reserve(100); // No reallocation here; iterators remain valid

        // Add elements without exceeding reserved capacity
        vec.push_back(4);
        vec.push_back(5);

        // Get an iterator pointing to the first element
        auto it = vec.begin(); // Iterator valid as there's no reallocation

        // Shrink to fit may cause reallocation and invalidation
        vec.shrink_to_fit(); // Memory optimization

        // Dereferencing the iterator now is undefined if shrink_to_fit causes reallocation
        std::cout << "Invalid access: Iterator value = " << *it << "\n"; // MAY cause undefined behavior!

        // SOLUTION: Avoid relying on iterators after shrink_to_fit; re-acquire them
        it = vec.begin(); // Ensure iterator is properly acquired after shrink_to_fit
        std::cout << "Safe access: Iterator value = " << *it << "\n";
    }

    // Problem 4: Invalidation due to Assign
    std::cout << "\n--- Problem 4: Invalidation due to Assign ---\n";
    {
        std::vector<int> vec = {1, 2, 3};

        // Get an iterator pointing to the first element
        auto it = vec.begin();

        // Use assign to replace all elements in the vector
        vec.assign({10, 20, 30});

        // Old iterator is now invalid
        std::cout << "Invalid access: Iterator value = " << *it << "\n"; // MAY cause undefined behavior!

        // SOLUTION: Avoid using old iterators after assign; re-acquire iterators
        it = vec.begin(); // Update iterator after the operation
        std::cout << "Safe access: Iterator value = " << *it << "\n";
    }

    // Problem 5: Safe Usage with Reserve
    std::cout << "\n--- Problem 5: Safe Usage with Reserve ---\n";
    {
        std::vector<int> vec;

        // Reserve sufficient capacity upfront
        vec.reserve(10);

        // Get an iterator pointing to the first position (no reallocation yet)
        auto it = vec.begin();

        // Add multiple elements without exceeding reserved capacity
        vec.push_back(100);

        // Iterator remains valid
        std::cout << "Iterator valid: " << std::boolalpha << (it == vec.begin()) << "\n"; // True
    }

    std::cout << "\nCompleted all demonstrations successfully.\n";
    return 0;
}
