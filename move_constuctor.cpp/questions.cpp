// why put noExcept in move constructor?
// if don't put noexcept in move constructor then what??
//what if throw exception in constructor then object will create or not?



1. What is a move constructor? How is it different from a copy constructor?
Answer: A move constructor transfers ownership of resources from one object to another without making a deep copy. It is more efficient when dealing with temporary or large objects.

MyClass(MyClass&& other) noexcept;  // move constructor
Copy constructor:

MyClass(const MyClass& other);  // deep copy

Key difference:
Copy duplicates the resource.
Move transfers the resource and leaves the source in a valid but empty state.

//---------------------------------------------------------------------------------------------------------------

2. When does the compiler automatically generate a move constructor for a class?
Answer: The compiler generates a move constructor automatically if:
You haven't declared any of these:
Copy constructor
Copy assignment
Move constructor
Move assignment
Destructor
All members are moveable
But if you declare a copy constructor or destructor, the compiler will not generate a move constructor.

//---------------------------------------------------------------------------------------------------------------

3. What is std::move() and what does it do exactly?
Answer: std::move() casts an object to an rvalue reference (T&&). It does not actually move anything — it just tells the compiler:

"You are allowed to move from this object now."

MyClass a;
MyClass b = std::move(a);  // move constructor is called

//---------------------------------------------------------------------------------------------------------------

4. Can a move constructor throw an exception? What’s the effect on STL containers if it does?
Answer: Yes, it can throw — but it should not. STL containers prefer move constructors marked noexcept.
If the move constructor might throw, containers will fall back to using the copy constructor (if available) during operations like resize, push_back, etc.
Best practice: always mark move constructors and move assignment operators as noexcept.


//--------------------------------------------------------------------------------------------------------
5. Why should move constructors be marked noexcept?
Answer: STL containers (like std::vector) rely on noexcept guarantees.
If a move constructor is not noexcept, the STL might choose to copy instead of move for exception safety.
Also, some optimizations like emplacement, reallocation, and sorting assume moves don’t throw.


//-------------------------------------------------------------------------------------------------------------
6. What happens when you try to move a const object?
Answer: You cannot move from a const object because a move constructor takes a non-const rvalue reference:

MyClass(MyClass&& other);        // not allowed for const
MyClass(const MyClass&& other);  // rare and discouraged
So, copy constructor will be used instead.


//---------------------------------------------------------------------------------------------------------------

7. Write a class with copy/move constructors and print statements.

class Example {
public:
    Example() { std::cout << "Default\n"; }
    Example(const Example&) { std::cout << "Copy Constructor\n"; }
    Example(Example&&) noexcept { std::cout << "Move Constructor\n"; }
};

🔴 Hard-Level Questions with Answers

1. How do move semantics work under RVO / copy elision in C++17+?
Answer: In C++17, compilers are required to use copy elision for returned local objects — even if a move constructor exists.

MyClass create() {
    MyClass x;
    return x;  // no move/copy, RVO applies
}
No move/copy constructor is called — the object is constructed directly in the caller context.
In C++14 and earlier, the move constructor might still be called.


//---------------------------------------------------------------------------------------------------------------

2. Given code:
LogBuffer getBuffer() {
    LogBuffer b("hello");
    return b;
}
LogBuffer a = getBuffer();
Answer:

In C++17, copy elision happens — constructor is called once.
In C++11/14, move constructor may be called when returning b.
You can check this by printing constructor calls.

//---------------------------------------------------------------------------------------------------------------
3. Explain Rule of Five in the context of move semantics.
Answer: If a class manages resources (e.g., heap memory), you should define:

Copy constructor
Copy assignment
Move constructor
Move assignment
Destructor
If you define any one of these, you should consider defining all 5, to avoid unexpected behavior.

//---------------------------------------------------------------------------------------------------------------

4. What are the dangers of using a moved-from object?
Answer: Moved-from objects are in a valid but unspecified state. You can:

Call member functions
Reassign or destroy it
But you should not use their internal state unless reinitialized.

Safe: obj = something_new;
Not safe: obj.use_resource(); (if resource was moved)


//---------------------------------------------------------------------------------------------------------------

5. Can a class that disables copy operations still support move operations?
Answer: Yes! You can delete copy functions and define only move ones.

class OnlyMove {
public:
    OnlyMove(const OnlyMove&) = delete;
    OnlyMove& operator=(const OnlyMove&) = delete;

    OnlyMove(OnlyMove&&) = default;
    OnlyMove& operator=(OnlyMove&&) = default;
};
Useful for unique ownership scenarios like std::unique_ptr.


//---------------------------------------------------------------------------------------------------------------

6. How would you implement move semantics in a class with raw pointers?
Answer:

class Buffer {
    char* data;
public:
    Buffer(size_t size) : data(new char[size]) {}
    ~Buffer() { delete[] data; }

    // Move constructor
    Buffer(Buffer&& other) noexcept : data(other.data) {
        other.data = nullptr;
    }

    // Move assignment
    Buffer& operator=(Buffer&& other) noexcept {
        if (this != &other) {
            delete[] data;
            data = other.data;
            other.data = nullptr;
        }
        return *this;
    }
    // Disable copy
    Buffer(const Buffer&) = delete;
    Buffer& operator=(const Buffer&) = delete;
};

//---------------------------------------------------------------------------------------------------------------

7. How does std::vector use move semantics for performance?
Answer: std::vector uses move semantics:

When resizing (e.g., doubling size)
When elements are inserted/emplaced
When returning a vector from a function
Instead of copying every element, it moves them — this is fast and reduces allocations.

std::vector<std::string> vec;
vec.push_back("hello");  // move constructor used

