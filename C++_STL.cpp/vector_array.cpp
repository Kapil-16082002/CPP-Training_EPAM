C-style Array ->
Data struture that store elements at  contiguous memory block.

📌 Key Differences
Feature	               std::array<T, size>	                      C-style Array (T array[size])
Size	                Fixed at compile-time	                  Fixed at compile-time
Memory Location	         Stack (faster)	                          Stack (faster)
Bound Checking	     .at(index) checks bounds	                  ❌ No bounds checking (arr[index] can cause undefined behavior)
Copy & Assignment	  ✅ Supports assignment and copy operations	❌ Cannot be directly assigned
STL Support	          ✅ Supports STL functions (iteration, algorithms, etc.)	❌ No built-in STL support
Size Retrieval	      ✅ .size() gives array size	             ❌ sizeof(arr)/sizeof(arr[0]) (error-prone)
Compatibility with Algorithms	✅ Works with STL algorithms	     ❌ Needs manual handling
Swap Elements	       ✅ .swap() available	                     ❌ Requires manual swapping

1️⃣ Bound Checking (std::array is Safer)

std::array<int, 3> arr = {1, 2, 3};
int c_arr[3] = {1, 2, 3};
std::cout << arr.at(5) << std::endl;  // ❌ Throws std::out_of_range Exception
std::cout << c_arr[5] << std::endl;   // ❌ Undefined Behavior (May crash)

✅ Use .at() with std::array to avoid accessing invalid indexes.

//---------------------------------------------------------------------------------------------------------------

3️⃣ Getting Array Size
✅ std::array
std::array<int, 3> arr = {1, 2, 3};
std::cout << arr.size() << std::endl;  // Output: 3

❌ C-Style Array (Error-prone)
int c_arr[3] = {1, 2, 3};
std::cout << sizeof(c_arr) / sizeof(c_arr[0]) << std::endl; // Output: 3
❌ This method fails if the array is passed to a function, as the array decays to a pointer.SEE below example

Passing to Functions
✅ std::array (Preserves Size)
void printArray(const std::array<int, 3>& arr) {
    std::cout << arr.size(); // ✅ Correct size
}

❌ C-Style Array (Decays to Pointer)
void printArray(int c_arr[]) {
    std::cout << sizeof(c_arr) / sizeof(c_arr[0]); // ❌ Incorrect size
}
✅ std::array maintains size, whereas C-style arrays decay to pointers.

//-------------------------------------------------------------------------------------------------------------

4️⃣ Copy and Assignment

✅ std::array (Allowed)
std::array<int, 3> arr1 = {1, 2, 3};
std::array<int, 3> arr2;
arr2 = arr1; // ✅ Works fine

❌ C-Style Array (Not Allowed)
int c_arr1[3] = {1, 2, 3};
int c_arr2[3];

// c_arr2 = c_arr1;  ❌ Error: Arrays cannot be assigned directly
C-style arrays cannot be assigned directly; instead, you must use memcpy() or a loop.



/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

std::array in C++ ->
std::array is a fixed-size array provided by the C++ Standard Library (#include <array>).
Unlike std::vector, it cannot change its size after declaration.
It provides better performance compared to std::vector since it does not involve dynamic memory allocation.
Safer than C-style arrays (int arr[]) since it provides bounds checking.

📌 Key Properties of std::array
Property	            Details
Fixed Size	            The size is defined at compile-time and cannot be changed.
Stack Allocation	    std::array is stored on the stack, making it faster than heap-based std::vector.
Supports STL Features	It supports iterators, .size(), .begin(), .end(), .at(), etc.
Bound Checking	        The .at() function provides bounds checking, while operator[] does not.
Faster Access	        Faster access than std::vector since no dynamic allocation is involved.

#include <iostream>
#include <array>
int main() {
    std::array<int, 5> arr = {1, 2, 3, 4, 5}; // Fixed-size array with 5 elements
    for (int num : arr) {
        std::cout << num << " ";
    }
    return 0;
}
Output:
1 2 3 4 5

📌 Methods and Functions of std::array //------------------------------------------------------------------------

1️⃣ Accessing Elements
std::array<int, 4> arr = {10, 20, 30, 40};
std::cout << arr[2] << std::endl;  // Output: 30
std::cout << arr.at(2) << std::endl; // Output: 30 (Bounds-checked)
✅ .at(index) throws an exception if the index is out of bounds, unlike operator[].

//--------------------------------------------------------------------------------------------------------------
3️⃣ First and Last Elements

✅ .front() returns the first element, .back() returns the last element.
std::cout << arr.front() << std::endl; // Output: 10 (First element)
std::cout << arr.back() << std::endl;  // Output: 40 (Last element)

//---------------------------------------------------------------------------------------------------------------
4️⃣ Iterating Over std::array

for (auto it = arr.begin(); it != arr.end(); ++it) {
    std::cout << *it << " ";
}
for (auto it : arr) {
    std::cout << it << " ";
}
✅ .begin() returns an iterator to the first element, .end() points to the position after the last element.
//-----------------------------------------------------------------------------------------------------------
5️⃣ Filling the Array (.fill())

std::array<int, 5> arr;
arr.fill(7);

for (int num : arr) {
    std::cout << num << " ";
}
// Output: 7 7 7 7 7
✅ .fill(value) sets all elements to the given value.

//-----------------------------------------------------------------------------------------------------------
6️⃣ Swapping Two std::array Objects

std::array<int, 3> arr1 = {1, 2, 3};
std::array<int, 3> arr2 = {4, 5, 6};

arr1.swap(arr2);

for (int num : arr1) std::cout << num << " "; // Output: 4 5 6
for (int num : arr2) std::cout << num << " "; // Output: 1 2 3

📌 Difference Between std::array and std::vector
Feature	            std::array	                 std::vector
Size	            Fixed at compile-time	        Can grow and shrink dynamically
Memory Location	    Stack (faster)	                Heap (slower due to dynamic allocation)
Performance	         Faster	                        Slower (due to dynamic allocation)
Bound Checking	    .at() (bounds-checked) and []	.at() (bounds-checked) and []
Flexibility	         Limited	                     More flexible (resizing allowed)

✅ Use std::array when:
The size is known at compile-time.
You need faster performance (stack allocation).
You want less memory overhead.

✅ Use std::vector when:
The size is unknown or changes dynamically.
You need dynamic resizing.


///////////////////////////////////////////////////////////////////////////////////////////////////////////////

std:: vector ->

A vector in C++ (std::vector<T>) is a dynamic array that is used to store elements and can automatically resize itself when elements are added or removed. 
It is part of the Standard Template Library (STL) and provides fast access, insertion, and deletion operations.

📌 Properties of std::vector
Dynamic Resizing – Can grow or shrink at runtime.
Contiguous Memory Allocation – Elements are stored in contiguous memory blocks.
Fast Random Access – Supports constant-time access using operator[] and .at().
Automatic Memory Management – Automatically handles memory allocation and deallocation.
STL Compatibility – Works seamlessly with STL algorithms.
Efficient Insertion & Deletion – .push_back() and .emplace_back() efficiently add elements at the end.

1️⃣ Declaring and Initializing a Vector

#include <iostream>
#include <vector>
int main() {
    std::vector<int> v1;                    // Empty vector
    std::vector<int> v2(5);                 // Vector of size 5, default initialized to 0
    std::vector<int> v3(5, 100);            // Vector of size 5, initialized with 100
    std::vector<int> v4 = {1, 2, 3, 4, 5};  // Initializer list
    std::vector<int> v5(v4);                // Copy constructor,(direct intialization)
    std::vector<int> v6 = v4;               // Copy Initialization
    //std::vector<int> v5(v4); directly invokes the copy constructor, while std::vector<int> v5 = v4; uses copy initialization, 

    for (int i : v4) std::cout << i << " "; // Output: 1 2 3 4 5
}
//-----------------------------------------------------------------------------------------------------------
2️⃣ Accessing Elements

std::vector<int> vec = {10, 20, 30};
std::cout << vec[1] << std::endl;  // ✅ Fast access (Output: 20)
std::cout << vec.at(1) << std::endl; // ✅ Safe access with bound checking
🚨 Note: vec.at(index) throws an exception if the index is out of range, while vec[index] may cause undefined behavior.

Iterating Over a Vector
✅ Using Index
for (size_t i = 0; i < vec.size(); i++)  std::cout << vec[i] << " ";

✅ Using Range-based Loop
for (int num : vec) std::cout << num << " ";

✅ Using Iterators
for (auto it = vec.begin(); it != vec.end(); ++it) std::cout << *it << " ";

✅ Using Reverse Iterators
for (auto rit = vec.rbegin(); rit != vec.rend(); ++rit) std::cout << *rit << " ";

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Difference between push_back() and emplace_back() in C++ STL

1️⃣ push_back() – Requires a Fully Constructed Object
push_back() creates a copy or moves an existing object into the vector.
If the object is not already created, it will first be constructed separately before being copied/moved into the vector.

#include <iostream>
#include <vector>
class Demo {
public:
    int x;
    Demo(int val) : x(val) { std::cout << "Constructor called\n"; }
};
int main() {
    std::vector<Demo> vec;
    
    Demo d(10);  // Object is created separately
    vec.push_back(d);  // Copy or move happens
    vec.push_back(Demo(20));  // Temporary object created, then moved

    return 0;
}
Output:
Constructor called  // Object `d` is created
Constructor called  // Copy/move into vector
Constructor called  // Temporary object `Demo(20)` created
Constructor called  // Copy/move into vector
🔹 Key Takeaways:
Requires an already constructed object.
Performs copy or move of the object into the vector.
More overhead when dealing with complex objects.

//-----------------------------------------------------------------------------------------------------------------

2️⃣ emplace_back() – Constructs Object In-Place
emplace_back() constructs the object directly in the vector, avoiding unnecessary copies or moves.
It forwards arguments to the constructor of the object.

#include <iostream>
#include <vector>
class Demo {
public:
    int x;
    Demo(int val) : x(val) { std::cout << "Constructor called\n"; }
};
int main() {
    std::vector<Demo> vec;
    vec.emplace_back(30);  // Object is constructed directly in the vector
    return 0;
}
Output:
Constructor called  // Only one constructor call, no extra copy/move
#include <iostream>
#include <vector>

class Demo {
public:
    int x, y;
    // Constructor taking both x and y
    Demo(int val1, int val2) : x(val1), y(val2) { 
        std::cout << "Constructor called with x = " << x << ", y = " << y << "\n";
    }
};
int main() {
    std::vector<Demo> vec;
    vec.emplace_back(30, 40);  // Directly constructs Demo(30, 40) in the vector
    return 0;
}

🔹 Key Takeaways:
Constructs object directly inside the vector.
Avoids unnecessary copies/moves.
Faster and more efficient, especially for large or complex objects.

⚡ Comparison Table
Feature	                              push_back()	                                  emplace_back()
Requires an existing object?	      ✅ Yes	                                       ❌ No, constructs in-place
Number of constructor calls	         More (extra copy/move)	                          Fewer (direct construction)
Performance	                         Slower due to extra copy/move	              Faster (avoids unnecessary copies)
Suitable for	  Simple objects or when an object is already created	 Large, complex objects that should be constructed in-place

3️⃣ When to Use What?
Use push_back() when you already have a created object.
Use emplace_back() when constructing a new object directly inside the vector (for performance benefits).

//-----------------------------------------------------------------------------------------------------------

🔹 size() vs capacity() in std::vector
Function	What it tells you	                                  Changes when...?
size()	    Number of elements currently stored	                  You add or remove elements
capacity()	Number of elements it can hold without reallocating	  It automatically increases when needed

#include <iostream>
#include <vector>
using namespace std;
int main() {
    vector<int> v;
    cout << "Initial size: " << v.size() << endl;
    cout << "Initial capacity: " << v.capacity() << endl;
    v.push_back(1);
    v.push_back(2);
    v.push_back(3);
    cout << "Size after 3 push_backs: " << v.size() << endl;
    cout << "Capacity after 3 push_backs: " << v.capacity() << endl;

    return 0;
}


//-----------------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------------
#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric> // for accumulate

int main() {
    std::cout << "--- Constructors ---\n";
    std::vector<int> v1; // Empty vector: default constructor, size = 0
    std::vector<int> v2(5); // 5 default-initialized elements (0s), size = 5 → [0, 0, 0, 0, 0]
    std::vector<int> v3(5, 10); // Initialize with 5 elements, each of value 10 → [10, 10, 10, 10, 10]
    std::vector<int> v4{1, 2, 3}; // List initialization → [1, 2, 3]
    std::vector<int> v5(v3); // Copy constructor → v5 = [10, 10, 10, 10, 10]
    std::vector<int> v6(std::move(v3)); // Move constructor, v6 = [10, 10, 10, 10, 10], v3 = []
/* 
✅ 1. Copy Constructor:

std::vector<int> v5(v3);
What happens: Creates a new vector v5 by making a deep copy of v3.
All elements of v3 are copied one by one into v5.
v3 remains unchanged after the copy.

Performance: More expensive in terms of time and memory (because each element is duplicated).

🧠 Think of it like cloning: v5 is a full duplicate of v3.
std::vector<int> v3 = {10, 10, 10, 10, 10};
std::vector<int> v5(v3); // v5 = [10, 10, 10, 10, 10], v3 = [10, 10, 10, 10, 10]

⚡ 2. Move Constructor:

std::vector<int> v6(std::move(v3));
What happens: 
Instead of copying the data, it "steals" the internal buffer (like a pointer) from v3.
After the move, v3 is left in a valid but unspecified state (usually empty).
v6 now owns the memory that originally belonged to v3.

Performance: Very fast! No element-by-element copy.

🧠 Think of it like handing over ownership: v6 takes over v3's resources, and v3 becomes empty.

std::vector<int> v6(std::move(v3)); // v6 = [10, 10, 10, 10, 10], v3 = []
*/
    std::cout << "--- Modifiers ---\n";
    v4.push_back(4); // Adds 4 at the end → [1, 2, 3, 4]
    v4.pop_back();   // Removes last element → [1, 2, 3]
    //std::vector does not have a pop_front()
    v4.insert(v4.begin() + 1, 9); // Inserts 9 at index 1 → [1, 9, 2, 3]
    v4.erase(v4.begin());         // Removes element at index 0 → [9, 2, 3]
    /*
    ✳️ 2. Erase a range of elements:
std::vector<int> v = {1, 2, 3, 4, 5};
v.erase(v.begin() + 1, v.begin() + 4); // removes elements at indices 1 to 3 (2, 3, 4)
 Output: [1, 5]
✳️ 3. Erase all elements (clear):
std::vector<int> v = {10, 20, 30};
v.erase(v.begin(), v.end()); // clears the vector
 Output: []
    */
    v4.emplace(v4.begin(), 8);    // Inserts 8 at index 0 → [8, 9, 2, 3]
    v4.emplace_back(7);           // Adds 7 at the end → [8, 9, 2, 3, 7]
    v4.resize(3);                 // Resizes to 3 elements → [8, 9, 2]
    /* 
    ✳️ 1. Reduce size:
std::vector<int> v = {1, 2, 3, 4, 5};
v.resize(3); // keep only first 3 elements
Output: [1, 2, 3]

✳️ 2. Increase size (default-initialize new elements to 0):
std::vector<int> v = {1, 2};
v.resize(5);
Output: [1, 2, 0, 0, 0]

✳️ 3. Increase size with specific value:
std::vector<int> v = {1, 2};
v.resize(5, 9); // new elements filled with 9
Output: [1, 2, 9, 9, 9]
    */


    v4.assign(4, 6);              // Replaces with 4 elements of 6 → [6, 6, 6, 6]
    /*
    ✅ assign() in std::vector
🔹 Purpose:
assign() replaces all existing elements in a vector with new ones.
It clears the current vector and inserts the new values.

🔧 Code Examples with Output & Comments:
#include <iostream>
#include <vector>
int main() {
    std::vector<int> v;

    // 1. Fill with n copies of a value
    v.assign(4, 10); // v = [10, 10, 10, 10]
    std::cout << "After assign(4, 10): ";
    for (int x : v) std::cout << x << " "; // Output: 10 10 10 10
    std::cout << "\n";

    // 2. Assign using iterator range from another vector
    std::vector<int> other = {1, 2, 3, 4, 5};
    v.assign(other.begin() + 1, other.begin() + 4); // v = [2, 3, 4]
    std::cout << "After assign from range (2 to 4): ";
    for (int x : v) std::cout << x << " "; // Output: 2 3 4
    std::cout << "\n";

    // 3. Assign using initializer list
    v.assign({7, 8, 9}); // v = [7, 8, 9]
    std::cout << "After assign({7,8,9}): ";
    for (int x : v) std::cout << x << " "; // Output: 7 8 9
    std::cout << "\n";

    return 0;
}
🔍 Internal Behavior:
assign() clears the vector before inserting new elements.
It may reallocate memory if the new size is larger than the current capacity.

⚠️ Important Notes:
If you use assign() with a range of iterators, ensure they are valid.
Assign is not the same as operator= for vectors — though both replace content, assign() gives more control.


    */

    std::vector<int> v7{1, 2, 3};
    std::vector<int> v8{4, 5};
    v7.swap(v8); // Now v7 = [4, 5], v8 = [1, 2, 3]

    std::cout << "--- Element Access ---\n";
    std::cout << "at(0): " << v8.at(0) << "\n"; // Output: 1
    std::cout << "operator[]: " << v8[1] << "\n"; // Output: 2
    std::cout << "front: " << v8.front() << "\n"; // Output: 1
    std::cout << "back: " << v8.back() << "\n";   // Output: 3
    int* ptr = v8.data(); // Pointer to first element
    std::cout << "data(): " << *ptr << "\n";       // Output: 1

    std::cout << "--- Size/Capacity ---\n";
    std::cout << "size: " << v8.size() << "\n";       // Output: 3
    std::cout << "capacity: " << v8.capacity() << "\n"; // Output varies
    std::cout << "empty: " << v8.empty() << "\n";     // Output: 0 (false)
    v8.shrink_to_fit();                              // Requests capacity reduction
    v8.reserve(10);                                  // Capacity >= 10

    std::cout << "--- Iterators ---\n";
    for (auto it = v8.begin(); it != v8.end(); ++it) {
        std::cout << *it << " "; // Output: 1 2 3
    }
    std::cout << "\n";
    for (auto rit = v8.rbegin(); rit != v8.rend(); ++rit) {
        std::cout << *rit << " "; // Output: 3 2 1
    }
    std::cout << "\n";

    std::cout << "--- Comparison Operators ---\n";
    std::vector<int> a{1, 2, 3}, b{1, 2, 3};
    std::cout << "a == b: " << (a == b) << "\n"; // Output: 1 (true)
    std::cout << "a < b: " << (a < b) << "\n";   // Output: 0 (false)

    std::cout << "--- Utilities ---\n";
    std::vector<int> util{4, 1, 3, 2, 1};
    std::sort(util.begin(), util.end());           // Sorted → [1, 1, 2, 3, 4]
    std::reverse(util.begin(), util.end());        // Reversed → [4, 3, 2, 1, 1]

    auto it = std::find(util.begin(), util.end(), 3); // Finds 3
    if (it != util.end()) std::cout << "Found 3 at index: " << (it - util.begin()) << "\n"; // Output: 1

    int count = std::count(util.begin(), util.end(), 1); // Occurrences of 1 → 2
    std::cout << "Count of 1: " << count << "\n";

    int sum = std::accumulate(util.begin(), util.end(), 0); // Sum = 11
    std::cout << "Sum: " << sum << "\n";

    auto last = std::unique(util.begin(), util.end()); // Remove consecutive duplicates → [4, 3, 2, 1]
    util.erase(last, util.end());
    std::cout << "After unique: ";
    for (int x : util) std::cout << x << " "; // Output: 4 3 2 1
    std::cout << "\n";

    std::cout << "--- Looping Examples ---\n";
    for (int x : util) std::cout << x << " "; // Output: 4 3 2 1
    std::cout << "\n";
    for (size_t i = 0; i < util.size(); ++i) std::cout << util[i] << " "; // Output: 4 3 2 1
    std::cout << "\n";
    std::for_each(util.begin(), util.end(), [](int x){ std::cout << x << " "; }); // Output: 4 3 2 1
    std::cout << "\n";

    return 0;
}
