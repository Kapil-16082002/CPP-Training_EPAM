✅The C++ STL provides a std::sort() function that is widely used for sorting containers like arrays and vectors. 

std::sort      Sorts a range in ascending order:                   std::sort(v.begin(), v.end());
std::partial_sort Partially sorts the first k elements in a range.	std::partial_sort(v.begin(), v.begin() + k, v.end());
is_sorted	Checks if a range is sorted.	bool sorted = std::is_sorted(v.begin(), v.end());
stable_sort	Sorts a range in ascending order while maintaining the relative order of equivalent elements. std::stable_sort(v.begin(), v.end());
nth_element	 Partitions the range such that the n-th element is in its correct position and all smaller elements are before it.	std::nth_element(v.begin(), v.begin() + n, v.end());

The sorting algorithm used in std::sort() is generally a combination of:
1. Introsort (introspective sort)
2. Heap sort 
3. Insertion sort.

✅1. Introduction to Introsort:
std::sort() in C++ uses introsort, which is a hybrid sorting algorithm that combines:

Quicksort: For fast average-case performance.
Heap sort: For guaranteed worst-case performance.
Insertion sort: For sorting small partitions efficiently.

Step-by-Step Internals of std::sort() Algorithm:
STEP:1  Begin with Quicksort
Introsort starts with quicksort, which is a divide-and-conquer algorithm.
The array is divided into smaller partitions based on a selected pivot element. 
Elements less than the pivot go to one partition, and elements greater go to another partition.

STEP:2  Switch to Heap Sort for Deep Recursion
When the recursion depth of Quicksort exceeds a certain limit (usually proportional to log(n)), introsort switches to heap sort. 
This is done to prevent :
  1.stack overflows caused by deep recursion 
  2.worst-case time complexity of quicksort (O(n²)).
  Why switch to heap sort()->
Heap sort gives time complexity of  O(n log n)in the worst case scenerios. 
A max-heap is constructed, and elements are swapped repeatedly to ensure sorting.

Step 3: Use Insertion Sort for Small Partitions:
For small sizes of partitions (usually ≤16 elements), introsort switches to insertion sort. 
Insertion sort becomes more efficient than quicksort or heap sort for small inputs.


Summary of Workflow:
1.Use Quicksort initially.
2.Switch to Heap Sort if recursion depth gets too high (to prevent O(n²) complexity).
3.Switch to Insertion Sort for small partitions (to maximize efficiency for small data sets).

//================================================================================================================

✅std::binary_search() 
The std::binary_search() algorithm in the C++ Standard Template Library (STL) is used to perform efficient binary searches on sorted data. 
It determines whether a given value is present in a sorted range and returns a bool indicating the result (true if the value exists, false otherwise).
bool ans=std::binary_search(numbers.begin(), numbers.end(), target)

//================================================================================================================
✅std::lower_bound
std::lower_bound returns an iterator pointing to the first element in a range that greater than or equal to a target value.

auto it = std::lower_bound(vec.begin(), vec.end(), value);
int idx= it - vec.begin();
int value_at_idx = *it;

std::upper_bound
std::upper_bound returns an iterator pointing to the first element in a range that is greater than a target value.

auto it = std::upper_bound(vec.begin(), vec.end(), value);
int idx= it - vec.begin();
int value_at_idx = *it;

//================================================================================================================
✅std::equal_range()  combination of  lower_bound() and upper_bound()
It is used to find the range of elements in a sorted container that are equal to a given value. 
It is especially useful when the container contains duplicates and you want to find all occurrences of a particular value.


std::equal_range() returns a std::pair of iterators:
first: Iterator to the first element in the range not less than (>=) the given value (similar to std::lower_bound()).
second: Iterator to the first element in the range greater than (>) the given value (similar to std::upper_bound()).

std::vector<int> nums = {1, 2, 4, 4, 4, 6, 7, 8};

auto result = std::equal_range(nums.begin(), nums.end(), 4); // Find the range of elements equal to 4.

// Print the range of matching elements.
std::cout << "Lower bound index: " << (result.first - nums.begin()) << "\n";
std::cout << "Upper bound index: " << (result.second - nums.begin()) << "\n";

// Print the actual elements in the matching range
std::cout << "Matching elements: ";
for (auto it = result.first; it != result.second; ++it) {
    std::cout << *it << " ";
}
//=================================================================================================================

✅ std::insert() 
Return type:
Returned an iterator pointing to the index where new element is inserted

int main() {
    std::vector<int> vec = {1, 2, 3};
    
    vec.insert(vec.begin(), 0); // Insert single element  0 1 2 3
    auto it = vec.insert(vec.end(), 2, 5); // Insert 2 elements with value 5     0 1 2 3 5 5
 
    std::cout<< it - vec.begin()<<endl; 

    std::vector<int> other = {7, 8, 9};
    vec.insert(vec.begin(), other.begin(), other.end()); // Insert range
    vec.insert(vec.end(), {10, 11}); // Insert initializer list
     // Output: 7 8 9 0 1 2 3 5 5 10 11
}
same as vector also for std::deque, std::list

int main() {
    std::set<int> s;
    s.insert(5); // Insert single element
    auto it = s.insert(s.begin(), 10); // Insert with hint
    s.insert({20, 30, 40}); // Insert initializer list

    for (int n : s) std::cout << n << " "; // Output: 5 10 20 30 40
}


//=================================================================================================================
✅std::erase in C++ STL

1. vec.erase(start_iterator, end_iterator);
vec.erase(vec.begin() + 1); // erase only index 1 element
vec.erase(vec.begin() + 1, vec.begin() + 5); // Erases all elements from at index [1 to 5)


2. Remove Elements by Value (std::erase)
Return Value:
Both std::erase and std::erase_if return the number of elements removed from the container.

Time Complexity:
Depends on the container:
For std::vector, std::deque, std::string, etc.: O(n) (as the operation involves shifting).
For std::list, std::forward_list, and other linked-list containers: O(k) (where k is the number of removed elements, as no shifting is required).
For associative containers (e.g., std::set, std::map): O(k * log(n)) (due to element lookup and rebalancing).

int main(){
std::vector<int> v = {1, 2, 3, 4, 3, 5, 3, 6};

    // Remove all occurrences of 3
    size_t count = std::erase(v, 3);
    std::cout << "Removed " << count << " elements.\n";
}
Output:
Removed 3 elements.
Updated vector: 1 2 4 5 6

Example 2: Remove Elements Based on a Condition (std::erase_if)

int main() {
    std::vector<int> v = {10, 15, 20, 25, 30, 35};

    // Remove all elements greater than 20
    size_t count = std::erase_if(v, [](int n) { return n > 20; });

    std::cout << "Removed " << count << " elements.\n";
}
Output:
Removed 3 elements.
Updated vector: 10 15 20


//===============================================================================================================

✅std::remove in C++ STL
std::remove is an algorithm in the C++ (STL) that removes all instances of a specific value from a range by rearranging elements in-place. 

Return Value:
std::remove returns an iterator pointing to the new logical end of the range (i.e., past the last remaining element).

The range [first, new_end) contains the elements that are not equal to value.
The range [new_end, last) is left in an unspecified but valid state.

int main() {
    std::vector<int> v = {1, 2, 3, 4, 5, 3, 6, 3};

    // Remove all occurrences of 3
    auto new_end = std::remove(v.begin(), v.end(), 3);

    std::cout << "Range that don't have 3 : ";
    for (auto it = v.begin(); it != new_end; ++it) {
        std::cout << *it << " ";
    }

    // Print the leftover elements
    std::cout << "Remaining elements beyond new_end: ";
    for (auto it = new_end; it != v.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
}


//================================================================================================================

✅std::fill()
The std::fill() algorithm assigns a given value to all elements in a specified range of iterators.
std::vector<int> nums(10);
std::fill(nums.begin(), nums.end(), 7); // Fill all elements of the vector with 7

std::fill_n()
The std::fill_n() algorithm is a variant of std::fill() that is used to fill n elements starting from a given iterator with a specific value.
std::vector<int> nums(10);
std::fill_n(nums.begin(), 5, 42);  // Fill the first 5 elements with the value 42


✅std::generate()
std::generate is used to fill a range with values generated by a callable (function, functor, or lambda).
It does not take input from an existing range— instead, it uses the output of a generator function to populate the elements.
Syntax:
std::generate(OutputIterator first, OutputIterator last, Generator gen);
first, last: Define the range where values should be filled(populated).
gen: A generator function (or callable) that provides new values.

Like std::fill(), std::generate() fills a range, but instead of assigning a single value, it assigns values generated by a callable function or functor.
std::vector<int> nums(10);
// Lambda to generate sequential numbers
int counter = 0;
std::generate(nums.begin(), nums.end(), [&counter]() { return counter++; });
//Output: 0 1 2 3 4 5 6 7 8 9

std::generate_n()
std::vector<int> nums(10);
// Lambda to generate multiples of 5
int multiplier = 1;
std::generate_n(nums.begin(), 5, [&multiplier]() { return multiplier++ * 5; });
//output: 5 10 15 20 25 0 0 0 0 0

✅std::transform()

The std::transform function is used to apply a given operation (in the form of a function, lambda, or functor) to elements from a container (or multiple containers) and store the result in another container (or to overwrite the original container).

The std::transform function comes in two forms:
Unary operation version: Applies a function to each element of a single input range.
Binary operation version: Applies a function to elements of two input ranges element-by-element.

1. Unary Operation (Single-Input Version):
Syntax:
std::transform(InputIterator1 first1, InputIterator1 last1, OutputIterator result, UnaryOperation op);
first1, last1: The range of the input container to transform.
result: The start of the destination range (output iterator or container).
op: A unary operation that will be applied to each element.

int main() {
    std::vector<int> nums = {1, 2, 3, 4, 5};
    std::vector<int> result(nums.size());

    // Transform: Multiply each number by 2
    std::transform(nums.begin(), nums.end(), result.begin(), [](int x) { return x * 2; });

    for (int x : result) {
        std::cout << x << " ";   // Output: 2 4 6 8 10
    }
}

2. Binary Operation (Two-Input Version):
Syntax:
std::transform(InputIterator1 first1, InputIterator1 last1,InputIterator2 first2, OutputIterator result,BinaryOperation op);

first1, last1: The range of the first input container.
first2: The start of the second input container.
result: The start of the destination range (output iterator or container).
op: A binary operation that will be applied to corresponding pairs of elements from the two input ranges.

int main() {
    std::vector<int> nums1 = {1, 2, 3, 4, 5};
    std::vector<int> nums2 = {10, 20, 30, 40, 50};
    std::vector<int> result(nums1.size());

    // Transform: Add corresponding elements of nums1 and nums2
    std::transform(nums1.begin(), nums1.end(), nums2.begin(), result.begin(),
                   [](int x, int y) { return x + y; });

    for (int x : result) {
        std::cout << x << " ";
    }
}


✅ std::generate	                                    std::transform
1.Initializing a container with values                1.Transforming data from one form to another
2.Use std::generate when you need to initialize or      2.Use std::transform when you already have an input range and need to transform/process its values into another form.
populate a range with generated values, without requiring any input data.                                            
//=================================================================================================================

✅std:: for_each()
The std::for_each() algorithm is a utility in the C++(STL) that allows you to apply a given function or callable object to each element in a range of data structures like arrays, vectors, or other STL containers. 
It is particularly useful when you want to take an operation on every element of a container without writing an explicit loop.

It is defined in the <algorithm> header file.
Example 1: Applying a Simple Function to Each Element
int main() {
    std::vector<int> v = {1, 2, 3, 4, 5};
    std::for_each(v.begin(), v.end(), [](int x) {  // Print each element using std::for_each
        std::cout << x << " ";
    });
    // Output: 1 2 3 4 5

Example 2: Modifying Elements in a Container
If the elements are not const, the callable object can modify them.
int main() {
    std::vector<int> v = {1, 2, 3, 4, 5};
    std::for_each(v.begin(), v.end(), [](int& x) {  // Increment each element by 10
        x += 10; // Modify the element
    });
    // Output: 11 12 13 14 15
}

Example 3: Using a Functor
You can also use a functor (a class with a callable operator operator()).

#include <iostream>
#include <vector>
#include <algorithm>

// Functor definition
struct Print {
    void operator()(int x) const {
        std::cout << x << " ";
    }
};
int main() {
    std::vector<int> v = {1, 2, 3, 4, 5};

    // Apply the functor to each element
    std::for_each(v.begin(), v.end(), Print());
    // Output: 1 2 3 4 5
}
Example 4: Capturing State in a Lambda Function
You can use lambda expressions to capture external variables and use them inside the std::for_each() body.
int main() {
    std::vector<int> v = {1, 2, 3, 4, 5};
    int sum = 0; // Variable to capture

    // Calculate the sum of all elements
    std::for_each(v.begin(), v.end(), [&sum](int x) {
        sum += x; // Capture sum by reference
    });
    std::cout << "Sum of elements: " << sum << std::endl;
    // Output: Sum of elements: 15
}
Example 5: Parallel Execution with C++17
For large data sets, we can use parallel execution policies to speed up the algorithm. You need to include <execution> for this feature.

#include <iostream>
#include <vector>
#include <algorithm>
#include <execution> // For parallel execution policies

int main() {
    std::vector<int> v(1'000'000, 1); // Large vector with 1 million elements, all initialized to 1

    int sum = 0;

    // Apply parallel execution policy to compute sum
    std::for_each(std::execution::par, v.begin(), v.end(), [&sum](int x) {
        sum += x; // Warning: Not thread-safe!
    });
    std::cout << "Sum of elements: " << sum << std::endl; // Output may not be consistent due to data race
    return 0;
}
Important Note: The above code has potential data race issues because multiple threads modify sum simultaneously. 
To avoid this, use a thread-safe approach (e.g., a mutex or atomic variables).

✅Differences from Other Algorithms
std::for_each() vs std::transform():

1.std::for_each() 
Purpose: Used to apply a function to each element in a range.
Return Value: Does not modify the input range or produce a new range; it merely performs an operation on each element as specified by the user.

2.std::transform()
Purpose: Used to apply a function to each element in a range and produce a new range.
Return Value: Modifies or creates a new range by applying the provided function to each element in the input range.

//================================================================================================================

✅std::count()

1.The count() function in the C++ STL is used to determine the number of occurrences of a specific value in a container. 
It is a non-modifying sequence operation provided as part of the <algorithm> header.
Syntax:
count(InputIterator first, InputIterator last, const T& value);

Parameters:
first, last: Input iterators defining the range of elements to process within a container. 
The range is [first, last), which means first is included but last is excluded.
value: The value to search for in the specified range of elements.

Return Value:
Returns the count (an integer) of elements in the range [first, last) that are equal to the specified value.

Time Complexity:
Linear, (O(n)), where (n) is the number of elements in the range [first, last).

How Does count() Work?
The count() function basically iterates over the specified range [first, last) and compares each element with the value using the equality operator (==).


2.std::count_if()
Unlike std::count(), which looks for a specific value, std::count_if() counts elements that satisfy a given condition (predicate).

std::vector<int> vec = {1, 2, 3, 4, 5, 6, 7, 8};
// Count numbers greater than 4
int count_gt_4 = std::count_if(vec.begin(), vec.end(), [](int x) { return x > 4; });

How it Works: Instead of comparing directly with a value, it applies the predicate to each element in the range [first, last) and increments the counter for each element satisfying the predicate.

//======================================================================================================================================

✅std::find()
1. std::find() is a non-member algorithm provided in the <algorithm> header.
It searches for a specific value and returns an iterator to the first occurrence found.

Return Value:
Return an iterator pointing to the first occurrence of the element that matches value. 
If the value is not found, the iterator returned is equal to last.

Time Complexity:
Linear, (O(n)), where (n) is the number of elements in the range.

std::vector<int> vec = {10, 20, 30, 40, 50};
auto it = std::find(vec.begin(), vec.end(), 30); // Search for the value 30 in the vector


// in string , Return type is Index not iterator..
std::string str = "Hello, world!";
int pos = str.find("world");  // Search for substring "world". pos = 7th index
  if (pos != std::string::npos) {
        std::cout << "Substring 'world' found at position " << pos << ".\n";
    } 
    else {
        std::cout << "Substring 'world' not found.\n";
  }
/* 
✅std::map::find() and std::unordered_map::find()
In associative containers like std::map and std::unordered_map, there is a member function find() that works differently from the non-member std::find(). 
This function is used to find an entry based on the unique key of the map.

Return Value:
An iterator to the element with the matching key if found.
If the key is not found, the iterator returned is equal to map.end().

Time Complexity:
(O(\log n)) for std::map (as it is backed by a balanced binary search tree).
(O(1)) average for std::unordered_map (as it uses hashing).

std::map<int, std::string> myMap = {{1, "one"}, {2, "two"}, {3, "three"}};
    auto it = myMap.find(2); // Search for the key '2'

    if (it != myMap.end()) {
      std::cout << "Key 2 found with value: " << it->second << "\n";
    } 
    else {
      std::cout << "Key 2 not found.\n";
    }
*/

2. std::find_if()
In cases where you want to find an element based on a condition (predicate) instead of equality to a specific value, you use std::find_if().

Return Type:
An iterator pointing to the first element that satisfies the predicate. If no such element is found, the result is last.

Time Complexity:
Linear, (O(n)).
std::vector<int> vec = {10, 20, 35, 40, 50};
auto it = std::find_if(vec.begin(), vec.end(), [](int x) { return x % 2 != 0; }); // Search for the first odd number in the vector

3.
std::find_if_not()
This function works like std::find_if(), but instead of finding the first element that satisfies a predicate, it finds the first element that does not satisfy the predicate.

Similar to std::find_if() but the logic is inverted.

Return Value:
An iterator to the first element that does not satisfy the predicate.

std::vector<int> vec = {2, 4, 6, 7, 8}; 
auto it = std::find_if_not(vec.begin(), vec.end(), [](int x) { return x % 2 == 0; }); // Find the first number that is not even


//========================================================================================================================================


//=======================================================================================================================================

✅The std::accumulate() function in C++ is part of the <numeric> header in the Standard Template Library (STL). 
Examples of std::accumulate()
1.. Simple Summation
std::vector<int> numbers = {1, 2, 3, 4, 5};
int sum = std::accumulate(numbers.begin(), numbers.end(), 0);  // Initial value is 0

2. Custom Initial Value
std::vector<int> numbers = {1, 2, 3, 4, 5};
int sum = std::accumulate(numbers.begin(), numbers.end(), 10);  // Initial value is 10

3. Custom Binary Operation
std::vector<int> numbers = {1, 2, 3, 4, 5};
int product = std::accumulate(numbers.begin(), numbers.end(), 1, std::multiplies<int>());
std::cout << "Product = " << product << "\n";  // Output: Product = 120
//Instead of summing, the custom operation (std::multiplies<int>()) computes the product of all elements.

4.Concatenating Strings
std::vector<std::string> words = {"Hello", " ", "World", "!"};
std::string sentence = std::accumulate(words.begin(), words.end(), std::string(""));
std::cout << "Concatenated string = " << sentence << "\n";  // Output: Hello World!

//======================================================================================================================================

✅std::reverse()
Used to reverse the order of elements in a given range. 
It is found in the <algorithm> header. 
std::reverse() reverses the elements in place, meaning the original sequence is modified, and no extra space is required for the new reversed sequence.
Return Value:
std::reverse() does not return a value (void).

The time complexity of std::reverse() is O(N).

1.Requirements for  std::reverse()
std::reverse() requires that the container supports bidirectional iterators. This means it works on containers like std::vector, std::deque, std::list, std::string, and std::array.
It does not work on containers like std::forward_list (which only has forward iterators).

2.In-place Operation:
std::reverse() modifies the input sequence directly.
If you do not want to modify the original container, you can use a separate container to store the reversed result.


1: Reversing a Vector
std::vector<int> numbers = {1, 2, 3, 4, 5};
std::reverse(numbers.begin(), numbers.end());  // Reverse the vector in-place

2.Partial Range Reversal
std::vector<int> vec = {10, 20, 30, 40, 50};
std::reverse(vec.begin() + 1, vec.end() - 1);  // Reverse only the middle segment (indices 1 to 4)
Output: 10 40 30 20 50 


3: Reversing an Array
You can reverse arrays (C-style or std::array) using std::reverse() because they have iterators.
int arr[] = {10, 20, 30, 40};
std::reverse(arr, arr + 4);  // Reverse the array
std::cout << "Reversed Array: ";
for (int num : arr) {
    std::cout << num << " ";
}
4. Range-based Reverse (C++20 and later)
From C++20 onwards, the range-based version of std::reverse() simplifies code.

std::vector<int> vec = {1, 2, 3, 4, 5};

// Reverse using range-based version
std::ranges::reverse(vec);
std::cout << "Reversed Vector: ";
for (int num : vec) {   // Output the reversed vector
    std::cout << num << " ";
}

//======================================================================================================================================
✅std::unique()

The unique() function is a part of the C++ Standard Template Library (STL) and is used to remove consecutive duplicate elements from a range or container. 
The function is present in the <algorithm> header file and primarily works on sorted ranges to provide meaningful results. 
However, it doesn’t remove all duplicates, only consecutive ones, and it operates in-place, modifying the input range.

Key Points of unique():
It removes only consecutive duplicates from the range.
It doesn’t actually change the size of the container (in the context of standard containers). Instead, it reorders the container and provides a pointer/iterator that marks the end of the unique range.
Works on both iterators and ranges.
It requires the input range to be sorted (or at least consecutive duplicates must be adjacent).

Return Value:
The unique() function returns an iterator pointing to the end of the "unique range" (the range where only unique elements are kept, and consecutive duplicates are removed). 
The remaining part of the container after returned iterator retains its original (but now invalid) values and is effectively ignored.
To resize a container based on the result of unique(), you typically use the erase() method along with the returned iterator.


/*Important Notes:
Usage without resizing the container:

Even though the unique() function moves duplicates out of the active portion of the container, it doesn’t resize the container. 
The "garbage values" remain in the container, and you need to manually remove them using erase() if necessary.
Effect on Unsorted Data:

If the input data isn’t sorted (or duplicates aren’t consecutive), the unique() function may produce incorrect results, as it only removes adjacent duplicates:
*/
Example 1: Basic Usage with a Sorted Range
int main() {
    std::vector<int> v = {1, 1, 2, 2, 3, 3, 4};
    
    auto it = std::unique(v.begin(), v.end());   // Remove consecutive duplicates
    
    v.erase(it, v.end()); // Resize the container to reflect the unique elements
    for (int num : v)
        std::cout << num << " "; // Output: 1 2 3 4
    return 0;
}

Example 2: Using a Custom Predicate
You can use the second version of unique() to define custom logic for determining duplicates.
 std::vector<int> v = {1, -1, 2, -2, 3, 3, 4};

    // Remove "duplicates" where absolute values are equal
    auto it = std::unique( v.begin(), v.end(),  [](int a, int b) { return std::abs(a) == std::abs(b); });
    v.erase(it, v.end());  // Resize the container to reflect the unique elements
    for (int num : v)
        std::cout << num << " "; // Output: 1 2 3 4

//=======================================================================================================================================
✅ std::set_union

It is used to compute the union of two sorted ranges or sets and store the result in a destination range.
Important Notes:
1.Both input ranges should be sorted in ascending order before calling std::set_union(). Unexpected behavior will occur if the ranges are not sorted.
2.The result will include each element only once, even if it appears in both ranges.

Return Value:
An output iterator pointing to the end of the destination range where the union is written.

Time Complexity:
Linear: (O(n1 + n2)), where (n1) is the size of range [first1, last1) and (n2) is the size of range [first2, last2).

std::vector<int> a = {1, 2, 3, 4, 5};
    std::vector<int> b = {3, 4, 5, 6, 7};
    std::vector<int> result;   // Destination range to hold the union

    // Compute the union of a and b
    std::set_union(a.begin(), a.end(),   b.begin(), b.end(),   std::back_inserter(result));
Output:
Union of a and b: 1 2 3 4 5 6 7 

✅How It Works:
1.The algorithm takes elements from both input ranges, compares them, and writes them to the output range in sorted order.
2.If duplicate values are found (i.e., values existing in both input ranges), only one copy of each value is written to the output.
3.To achieve this, it iterates over both ranges simultaneously:
    If an element in the first range is smaller, it adds it to the result.
    If an element in the second range is smaller, it adds it to the result.
    If both elements are equal, only one copy is added.


//===============================================================================================================

✅std::set_intersection
std::set_intersection is a function in the C++ (STL) that computes the intersection of two sorted ranges and stores the result in a destination range. 
The intersection of two sets is a set containing elements that are common to both sets.

Return Value:
The function returns an iterator to the element past the last element inserted into the destination range (result).

Key Points:
Both input ranges must be sorted according to the same criterion (either natural ordering or custom ordering specified by comp). 
If the sequences are not sorted, the results are undefined.
The order of elements in the resulting intersection range is preserved.
If an element appears multiple times in both ranges, it will appear in the result the minimum number of times it occurs in any of the ranges.


std::vector<int> v1 = {1, 2, 3, 4, 5};
    std::vector<int> v2 = {3, 4, 5, 6, 7};
    std::vector<int> intersection;

    // Compute intersection of v1 and v2
    std::set_intersection(v1.begin(), v1.end(), v2.begin(), v2.end(), std::back_inserter(intersection));

Output:
Intersection: 3 4 5

// customCompare because input vector in descending order
bool customCompare(int a, int b) {
    return a > b; // Sort in descending order
}
int main() {
    std::vector<int> v1 = {5, 4, 3, 2, 1};  // Sorted in descending order
    std::vector<int> v2 = {7, 6, 5, 4, 3};  // Sorted in descending order
    std::vector<int> intersection;

    // Compute intersection of v1 and v2 using custom comparator
    std::set_intersection(v1.begin(), v1.end(), v2.begin(), v2.end(),
                            std::back_inserter(intersection), customCompare);

Output:  Intersection: 5 4 3
//=================================================================================================================

✅std::set_difference

std::set_difference is a function in the C++ Standard Template Library (STL) that computes the difference between two sorted ranges. 
Specifically, it determines the elements that are present in the first range but not in the second one, and stores the result in a destination range.

Return Value:
The function returns an iterator to the element past the last element inserted into the destination range.

 std::vector<int> v1 = {1, 2, 3, 4, 5};
  std::vector<int> v2 = {4, 5, 6, 7};
  std::vector<int> difference;

  // Compute the difference: elements in v1 but not in v2
  std::set_difference(v1.begin(), v1.end(), v2.begin(), v2.end(), std::back_inserter(difference));
  
Output:
Difference (v1 - v2): 1 2 3


// Custom comparator for descending order
bool descendingOrder(int a, int b) {
    return a > b;  // Reverse order
}
int main() {
    std::vector<int> v1 = {5, 4, 3, 2, 1};  // Descending order
    std::vector<int> v2 = {5, 4, 0};        // Descending order
    std::vector<int> difference;

    // Compute the difference using custom comparator
    std::set_difference(v1.begin(), v1.end(),  v2.begin(), v2.end(), 
                        std::back_inserter(difference), descendingOrder);

Output:
Difference (v1 - v2): 3 2 1

//================================================================================================================

✅Finding Minimum and Maximum in a List

Return Value:
Both functions return an iterator to:
The smallest element in the range (std::min_element).
The largest element in the range (std::max_element).

If the range is empty, they return last (the past-the-end iterator).

std::vector<int> v = {3, 1, 4, 1, 5, 9, 2};

    // Find the minimum and maximum elements
    auto minIt = std::min_element(v.begin(), v.end());
    auto maxIt = std::max_element(v.begin(), v.end());

    cout<< minIt - v.begin(); // will give position

    if (minIt != v.end() && maxIt != v.end()) {
        std::cout << "Minimum element: " << *minIt << std::endl;
        std::cout << "Maximum element: " << *maxIt << std::endl;
    }


✅std::minmax_element in C++ STL

std::minmax_element is a function in the C++ Standard Template Library (STL) that finds both the smallest (minimum) and largest (maximum) elements in a range in a single pass. 
This is more efficient than calling std::min_element and std::max_element separately because it avoids iterating over the range twice.

Return Value:
Returns a std::pair of iterators:
first: An iterator pointing to the smallest element in the range.
second: An iterator pointing to the largest element in the range.
If the range is empty, both iterators in the returned pair equal last (indicating no valid elements).

Time Complexity:
(O(n)), single pass over the range.

int main() {
    std::vector<int> v = {3, 1, 4, 1, 5, 9};

    auto result = std::minmax_element(v.begin(), v.end());

   std::cout<<result.first-v.begin()<<std::endl; // will give position 
   std::cout<<result.second-v.begin()<<std::endl;  // will give position 

    if (result.first != v.end() && result.second != v.end()) {
        std::cout << "Minimum element: " << *result.first << std::endl;
        std::cout << "Maximum element: " << *result.second << std::endl;
    } else {
        std::cout << "Range is empty!" << std::endl;
    }
}



//================================================================================================================
✅std::next_permutation and std::prev_permutation in C++ STL

These functions are provided in the C++(STL) to generate lexicographically next and previous permutations of a range, respectively. 

Return Value
true: If a next/previous permutation was successfully generated.
false: If there are no more next/previous permutations and the range is reset to its lexicographically smallest (for std::next_permutation) or largest (for std::prev_permutation) arrangement.

1.std::next_permutation
std::next_permutation modifies the range to the lexicographically next greater permutation. 
1.If such a permutation exists:
    The function rearranges the elements in the range so that it represents the next permutation.

2.If the current arrangement is the largest permutation:
    The function returns false, and the range is rearranged into its smallest permutation (i.e., sorted in ascending order).


int main(){
std::vector<int> v = {1, 2, 3};

    std::cout << "Permutations in ascending order:\n";
    do {
        for (const auto& elem : v) {
            std::cout << elem << " ";
        }
        std::cout << std::endl;
    } while (std::next_permutation(v.begin(), v.end()));
  }

Output:
Permutations in ascending order:
1 2 3
1 3 2
2 1 3
2 3 1
3 1 2
3 2 1
//Once all permutations are generated, std::next_permutation returns false and resets the sequence to {1, 2, 3}.

2.std::prev_permutation
std::prev_permutation modifies the range to the lexicographically previous smaller permutation. 
If such a permutation exists:
    The function rearranges the elements in the range so that it represents the previous permutation.
If the current arrangement is the smallest permutation:
The function returns false, and the range is rearranged into its largest permutation (i.e., sorted in descending order).


int main() {
    std::vector<int> v = {3, 2, 1}; // Start with the largest permutation

    std::cout << "Permutations in descending order:\n";
    do {
        for (const auto& elem : v) {
            std::cout << elem << " ";
        }
        std::cout << std::endl;
    } while (std::prev_permutation(v.begin(), v.end()));

  }
Output:
Permutations in descending order:
3 2 1
3 1 2
2 3 1
2 1 3
1 3 2
1 2 3
//Once all permutations are generated, std::prev_permutation returns false and resets the sequence to {3, 2, 1}.

//================================================================================================================

✅std::is_permutation in C++ STL

std::is_permutation is a utility function in the C++(STL) that checks if two ranges are permutations of each other. 
Two ranges are permutations of each other if they contain the same elements (including duplicates) but potentially in a different order.

Return Value:
Returns true if the two ranges are permutations of each other.
Returns false otherwise.

Key Points:
The order of elements does not matter while checking permutations; 
it only considers whether the collections contain the same elements (with the same multiplicity).

int main() {
    std::vector<int> v1 = {1, 2, 3};
    std::vector<int> v2 = {3, 2, 1};

    // Check if v1 and v2 are permutations of each other
    if (std::is_permutation(v1.begin(), v1.end(), v2.begin())) {
        std::cout << "v1 and v2 are permutations of each other.\n";
    } else {
        std::cout << "v1 and v2 are NOT permutations of each other.\n";
    }
    return 0;
}



















