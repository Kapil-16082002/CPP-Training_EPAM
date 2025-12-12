✅Custom Deleter in C++ Smart Pointers
A custom deleter is a function (either a function object, a lambda, or a function pointer) that tells how to clean up resources when a smart pointer (std::unique_ptr or std::shared_ptr) goes out of scope. 
By default, smart pointers call delete on the managed object.
However, a custom deleter allows you to override the default delete behavior for special cleanup tasks (such as freeing arrays, closing file handles, or releasing custom resources).

✅Why Use Custom Deleters?
1.Non-standard resource cleanup: Sometimes resources (other than memory) require specific cleanup.
For example: closing files, deallocating via a pool allocator, releasing sockets, etc.
2.Debugging and logging: You can log or track resource destruction for debugging purposes.
3.Special memory management: When managing arrays, or if delete is not suitable for an object (e.g., it needs a special library function to free memory).


✅1. std::shared_ptr for arrays
Unlike std::unique_ptr, std::shared_ptr does not have direct support for managing arrays (prior to C++20). 
However, you can use it with arrays by providing a custom deleter during its creation.
#include <memory>
#include <iostream>
int main() {
    // Create a shared_ptr for a dynamically allocated array with a custom deleter
    std::shared_ptr<int> arr(new int[5]{1, 2, 3, 4, 5}, [](int* p) {
        delete[] p;  // Custom deleter to release the array memory
    });

    // Access the array elements using standard pointer arithmetic
    for (int i = 0; i < 5; ++i) {
        std::cout << "arr[" << i << "] = " << arr.get()[i] << "\n";
    }
    // No need to delete[] manually; the custom deleter will handle this
    return 0;
}
Key Points:
std::shared_ptr requires a custom deleter if managing arrays, as it does not provide built-in support for arrays (before C++20).
The deleter ensures that the array is deallocated properly using delete[].

✅Why make_shared Does Not Support Arrays:
Unfortunately, std::make_shared does not support directly creating dynamically allocated arrays, even with a custom deleter. 
This is because std::make_shared is designed for single objects that can be easily deleted by 'delete' keyword 
but arrays require  delete[] instead of delete which make_shared  does not support.

OR
The main reasons std::make_shared does not support arrays are:
1.Memory Safety and Reference Counting:
std::make_shared combines the object and its reference control block in a single memory allocation for better performance. This design is incompatible with arrays.


✅Why Use std::vector Instead of std::shared_ptr for Arrays
While std::shared_ptr can manage an array of class objects, std::vector is often a better choice because:
It automatically manages memory without requiring delete[].
It supports dynamic resizing.
It provides a higher-level interface that's safer and easier to use.



✅Example with Custom Deleter (using Lambda):
#include <memory>
#include <iostream>
int main() {
    // Custom deleter using a lambda function
    auto customDeleter = [](int* ptr) {
        std::cout << "Deleting memory using custom deleter\n";
        delete ptr;
    };
    // Create a unique_ptr with the lambda custom deleter
    std::unique_ptr<int, decltype(customDeleter)> ptr(new int(42), customDeleter);
    std::cout << "Value: " << *ptr << std::endl;
    // The custom deleter is automatically called when the pointer goes out of scope
    return 0;
}
✅Example with Custom Deleter (using Function Pointer):
#include <memory>
#include <iostream>

// Custom deleter as a regular function
void customDeleter(int* ptr) {
    std::cout << "Deleting memory using custom deleter\n";
    delete ptr;
}
int main() {
    // Create a shared_ptr with the custom deleter
    std::shared_ptr<int> ptr(new int(42), customDeleter);
    std::cout << "Value: " << *ptr << std::endl;

    // The custom deleter is automatically invoked when no shared_ptr owns the resource
    return 0;
}
✅Functor as a custom deleter
#include <memory>
#include <iostream>
// Functor as a custom deleter
struct CustomDeleter {
    void operator()(int* ptr) {
        std::cout << "Deleting memory using functor deleter\n";
        delete ptr;
    }
};
int main() {
    // Create a shared_ptr using the functor custom deleter
    std::shared_ptr<int> ptr(new int(42), CustomDeleter());

    std::cout << "Value: " << *ptr << std::endl;
    // Automatically calls functor deleter when the shared_ptr is destroyed
    return 0;
}



//==================================================================================================================


✅2. std::unique_ptr for arrays:

std::unique_ptr has special support for arrays thanks to its ability to manage objects with custom deleters. 
When the std::unique_ptr goes out of scope, it automatically calls delete[].
#include <memory>
#include <iostream>
int main() {
    // Create a unique_ptr for a dynamically allocated array
    std::unique_ptr<int[]> arr(new int[5]{1, 2, 3, 4, 5});

    // Access the array elements using []
    for (int i = 0; i < 5; ++i) {
        std::cout << "arr[" << i << "] = " << arr[i] << "\n";
    }
    // No need to call delete[]; unique_ptr will automatically free the memory
    return 0;
}

#include <memory>
#include <iostream>
int main() {
    auto arr = std::make_unique<int[]>(5); // std::make_unique does not provide an initializer list directly for arrays. 
    //Default-initialized array (all elements are 0)
    // Initialize the array elements
    arr[0] = 1;
    arr[1] = 2;
    arr[2] = 3;
    arr[3] = 4;
    arr[4] = 5;
    for (int i = 0; i < 5; ++i) {
        std::cout << "arr[" << i << "] = " << arr[i] << "\n";
    }
    // No need to call delete[]; unique_ptr will automatically free the memory
    return 0;
}


✅1. Custom Deleter Using a Functor
#include <memory>
#include <iostream>
// Custom deleter as a functor
struct CustomDeleter {
    void operator()(int* ptr) {
        std::cout << "Deleting memory using CustomDeleter\n";
        delete ptr;  // Free memory
    }
};
int main() {
    // Creating a unique_ptr with the custom functor deleter
    std::unique_ptr<int, CustomDeleter> ptr(new int(42));
    std::cout << "Value: " << *ptr << std::endl;
    // Custom deleter automatically called when the pointer goes out of scope
    return 0;
}
✅2. Custom Deleter Using a Function Pointer
#include <memory>
#include <iostream>
// Custom deleter as a function
void customDeleter(int* ptr) {
    std::cout << "Deleting memory using function pointer custom deleter\n";
    delete ptr;  // Free memory
}
int main() {
    // Creating a unique_ptr with the custom deleter as a function pointer
    std::unique_ptr<int, decltype(&customDeleter)> ptr(new int(42), customDeleter);
    std::cout << "Value: " << *ptr << std::endl;
    // Custom deleter automatically called when the pointer goes out of scope
    return 0;
}

✅2. Custom Deleter Using a Lambda
#include <memory>
#include <iostream>
int main() {
    // Custom deleter as a lambda function
    auto customDeleter = [](int* ptr) {
        std::cout << "Deleting memory using lambda custom deleter\n";
        delete ptr;  // Free memory
    };
    std::unique_ptr<int, decltype(customDeleter)> ptr(new int(42), customDeleter);

    // Accessing the value
    std::cout << "Value: " << *ptr << std::endl;

    // Custom deleter automatically called when the pointer goes out of scope
    return 0;
}



//================================================================================================================

✅3. std::weak_ptr for arrays
std::weak_ptr is a non-owning smart pointer, often used alongside std::shared_ptr. 
It cannot directly manage arrays or any dynamic memory but serves as a reference to a std::shared_ptr managing an array. 
If the std::shared_ptr is destroyed (and the array deallocated), the std::weak_ptr automatically becomes invalid.
#include <memory>
#include <iostream>
int main() {
    // Create a shared_ptr managing a dynamically allocated array
    std::shared_ptr<int> sharedArr(new int[5]{1, 2, 3, 4, 5}, [](int* p) {
        delete[] p;
    });

    // Create a weak_ptr referring to the shared_ptr
    std::weak_ptr<int> weakArr = sharedArr;

    // Access the array through shared_ptr
    if (auto sp = weakArr.lock()) { // Check if the shared pointer is still valid
        for (int i = 0; i < 5; ++i) {
            std::cout << "sp[" << i << "] = " << sp.get()[i] << "\n";
        }
    } else {
        std::cout << "The shared pointer has been destroyed.\n";
    }

    sharedArr.reset(); // Destroy the shared_ptr (and the array)
    
    if (auto sp = weakArr.lock()) {
        std::cout << "Still valid\n";
    } 
    else {
        std::cout << "Shared pointer is now invalid (expired)\n";
    }
}
Key Points:
std::weak_ptr works alongside std::shared_ptr and becomes invalid if the std::shared_ptr managing the memory is destroyed.
It does not directly manage memory but provides a way to check whether the memory managed by a std::shared_ptr still exists.
