✅The Rule of 0 in C++:
The Rule of 0 is a design principle that encourages you to rely on automatic resource management (primarily through the use of RAII – Resource Acquisition Is Initialization) 
and does not explicitly define special member functions such as constructors, destructors, and assignment operators.

✅What Are the "Special Member Functions"?
When you create a class, the compiler generates these 6 special member functions if not explicitly defined:

1.Default constructor (MyClass())
2.Destructor (~MyClass())
3.Copy constructor (MyClass(const MyClass&))
4.Copy assignment operator (MyClass& operator=(const MyClass&))
5.Move constructor (MyClass(MyClass&&) noexcept)
6.Move assignment operator (MyClass& operator=(MyClass&&) noexcept)

Rule of Zero says that you should not define any of the six special member functions manually.
This is made easier by using library utilities like smart pointers or containers to manage resources.

✅when to use:If your class doesn’t manage resources and depnd on default implementations ( then Rule of Zero).


✅Why Use the Rule of 0?
1. C++ Standard Library: Modern C++ provides tools like std::unique_ptr, std::shared_ptr, std::vector, and std::map, which handle memory management and resource allocation safely.
2.Prevent Errors: Incorrect management of resources (e.g., improper copying, memory leaks, or dangling pointers) is a common source of bugs. 
                  Using standard components ensures exception safety and reduces resource leakage.

✅Advantages:
1.Prevent Errors: Since there is no manual memory management:
                No risks of memory leaks, 
                No dangling pointers, and 
                shallow copies are dramatically reduced.
2.Reduced Boilerplate: Developers do not need to implement repetitive and error-prone code like copy constructors or destructors.
3.Exception-Safe Code: RAII-based resource management (e.g., using std::unique_ptr, std::vector) ensures proper cleanup even when exceptions are thrown.




