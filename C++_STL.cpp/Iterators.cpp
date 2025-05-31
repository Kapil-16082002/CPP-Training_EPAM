✅Iterators are objects that act as pointers used to iterate through containers. 
They provide a way to traverse elements in a container (like vector, list, map, etc.) without needing to know the internal structure of the container.

/*
✅Differences between  Pointer  &  Iterator

Iterators and pointers are both used for navigating and accessing elements in a container(e.g., arrays, STL containers like std::vector, std::list, etc.).

1.Pointer?
A pointer holds the memory address of a variable or object.
A pointer cannot traverse non-contiguous memory structures.
Pointers are not container-aware.
Works with raw arrays or contiguous memory.

int arr[] = {10, 20, 30};
int* p = arr; // Points to the first element of the array

2.Iterator?
An iterator is an abstraction provided by the C++ STL to allow traversal of elements in a container (e.g., std::vector, std::list, std::deque, etc.).
An iterator can traverse in non-contiguous containers like std::list.
Iterators are container-aware, meaning they "know" how to traverse specific containers.
Works with STL containers (e.g., std::list, std::vector).
*/

✅Common Iterator Member Functions
All standard iterators in STL containers support these basic functions. Below are the iterator-related functions available in most containers (std::vector, std::list, etc.):

Function	Description
begin()	Returns an iterator to the first element of the container.
end()	Returns an iterator pointing to past-the-last element in the container.
rbegin()	Returns a reverse iterator to the last element.
rend()	Returns a reverse iterator pointing before the first element.
cbegin()	Returns a const iterator to the first element (read-only).
cend()	Returns a const iterator pointing to past-the-last element (read-only).
crbegin()	Returns a const reverse iterator to the last element (read-only).
crend()	Returns a const reverse iterator pointing before the first element.


✅Types of Iterators:
1.Input Iterators:
Can only be used for reading values from a container.
Key Points:
They provide single-pass, read-only access to elements.
After an element is read, iterators cannot "go backward" or reread the element.
Example: Reading elements from std::istream_iterator.

#include <iterator>
int main() {
    std::cout << "Enter numbers (end with non-integer input): ";

    // Input iterator for reading from the standard input stream (std::cin)
    std::istream_iterator<int> inputIter(std::cin);// inputIt is an iterator pointing to the first int value read from std::cin.
    std::istream_iterator<int> endOfStream;
    //When you declare std::istream_iterator<int> endOfStream; (with no associated input stream), it creates a "default-constructed" iterator.
    //This default-constructed std::istream_iterator has no associated input stream and is interpreted as a special marker for the "end of the stream" while iterating

    std::vector<int> vec;
    // Read values into the vector
    while (inputIter != endOfStream) {
        vec.push_back(*inputIter); // Dereferencing to read the value
        ++inputIter;              // Move to the next input value
    }
    std::cout << "Numbers entered: ";
    for (int num : vec) {
        std::cout << num << " ";
    }
    return 0;
}
Output Example:
Input: 10 20 30 q k 2 3
Output: Numbers entered: 10 20 30
Explanation:
std::istream_iterator<int> links the iterator to std::cin.
Each dereference (*inputIter) reads the next integer input.
Once the input ends, the iterator reaches std::istream_iterator<int>() (denoted by endOfStream).
Key Limitation: Cannot rewind or access previous input values.

//--------------------------------------------------------------------------------------------------------------

✅2.Output Iterators:
Can only be used for writing values into a container.
Provide single-pass, write-only access.
The dereference operator (*) is used to write values.
Example: Writing to std::ostream_iterator.

#include <iterator>
int main() {
    std::vector<int> vec = {1, 2, 3, 4, 5};
    // Output iterator for writing to the standard output (std::cout)
    std::ostream_iterator<int> outputIter(std::cout, " ");
    for (int num : vec) {
        *outputIter = num; // Writing the value to the output stream
        ++outputIter;      // Move to the next output position
    }
}
Explanation:
std::ostream_iterator<int> is linked to std::cout (with a space delimiter " ").
Each dereference (*outputIter) sends data to the output stream.
Key Limitation: Output iterators do not allow reading or backtracking.

//----------------------------------------------------------------------------------------------------------------

✅3.Forward Iterators:
Can traverse the container in the forward direction.
Provide read and write access.
Example: std::forward_list.
int main() {
    std::forward_list<int> flist = {10, 20, 30, 40, 50};
    // Forward iterator
    std::forward_list<int>::iterator it;
    for (it = flist.begin(); it != flist.end(); ++it) {
        std::cout << *it << " "; // Access the element via dereference
        *it += 5;               // Modify the element
    }
    std::cout << "\nModified list: ";
    for (it = flist.begin(); it != flist.end(); ++it) {
        std::cout << *it << " ";
    }
    return 0;
}
//============================================================================================================

✅4.Bidirectional Iterators:
Can traverse the container in the forward and backward direction.
Example: std::list, std:: deque, std::set, std::map.

int main() {
    std::list<int> lst = {100, 200, 300};
    // Bidirectional iterator
    std::list<int>::iterator it;

    // Forward traversal
    for (it = lst.begin(); it != lst.end(); ++it) {
        std::cout << *it << " ";
    }
    // Backward traversal
    for (it = lst.end(); it != lst.begin();) {
        --it; // Move backward
        std::cout << *it << " ";
    }
    return 0;
}

//=================================================================================================================

5.Random-Access Iterators:
Provide random access to elements and support arithmetic operations like addition, subtraction, and indexing.
Random-access iterators, support pointer-like operations (+, -, []).
Example: std::vector, std::deque, std::array.
int main() {
    std::vector<int> vec = {10, 20, 30, 40, 50};

    // Random-access iterator
    std::vector<int>::iterator it = vec.begin();

    // Access elements via pointer-like arithmetic
    std::cout << "First element: " << *it << "\n";
    std::cout << "Third element: " << *(it + 2) << "\n"; // Move ahead by 2 steps

    // Modify an element
    *(it + 1) = 25;

    // Access via indexing (alternative to iterators)
    std::cout << "Modified second element: " << vec[1] << "\n";

    // Iterate like a loop
    std::cout << "All elements: ";
    for (it = vec.begin(); it != vec.end(); ++it)
        std::cout << *it << " ";

    return 0;
}
//================================================================================================================


✅Common Iterator Member Functions
All standard iterators in STL containers support these basic functions. Below are the iterator-related functions available in most containers (std::vector, std::list, etc.):

Function	Description
begin()	Returns an iterator to the first element of the container.
end()	Returns an iterator pointing to past-the-last element in the container.
rbegin()	Returns a reverse iterator to the last element.
rend()	Returns a reverse iterator pointing before the first element.
cbegin()	Returns a const iterator to the first element (read-only).
cend()	Returns a const iterator pointing to past-the-last element (read-only).
crbegin()	Returns a const reverse iterator to the last element (read-only).
crend()	Returns a const reverse iterator pointing before the first element.
