
std::weak_ptr ->
std::weak_ptr is a type of smart pointer that does not participate in the reference count. 
std::weak_ptr is a smart pointers to break circular references between std::shared_ptr objects.
std::weak_ptr is designed to be used in situations where you want a reference to an object but do not want to extend the objects lifetime.

✅How std::weak_ptr Works ->
A std::weak_ptr does not increase the reference count of the object it observes.
If you try to access the object from a std::weak_ptr, you need to convert it to a std::shared_ptr using the lock() method.
If the object has been deleted (i.e., no more std::shared_ptr manage it), the lock() method will return a null std::shared_ptr.

Important Functions of std::weak_ptr
✅lock():   Converts a std::weak_ptr to a std::shared_ptr. 
            If the object is still alive (i.e., if there is at least one std::shared_ptr), lock() returns a valid std::shared_ptr. Otherwise, it returns a null std::shared_ptr.
✅expired(): Checks if the object managed by the std::weak_ptr has been destroyed (i.e., all std::shared_ptr to the object are gone). 
            Returns true if the object is expired (deleted), otherwise false.
✅use_count(): Returns the number of std::shared_ptr instances managing the object. 
This is useful for debugging and checking how many shared pointers still manage the object.
#include <iostream>
#include <memory>

class MyClass {
public:
    MyClass() { std::cout << "MyClass Constructor\n"; }
    ~MyClass() { std::cout << "MyClass Destructor\n"; }

    void show() { std::cout << "Hello from MyClass\n"; }
};
int main() {
    std::shared_ptr<MyClass> sp1 = std::make_shared<MyClass>();
    std::weak_ptr<MyClass> wp1 = sp1;
    if (auto sp2 = wp1.lock()) {     // Convert weak_ptr to shared_ptr to access object
        sp2->show();
    } 
    else {
        std::cout << "Object no longer exists\n";
    }
    sp1.reset();        // Reset sp1 to allow MyClass object to be destroyed
    if (wp1.expired()) {  // Check if object has expired
        std::cout << "Object has been deleted.\n";
    }
    return 0;
}
Output:
MyClass Constructor
Hello from MyClass
MyClass Destructor
Object has been deleted.

Key Points:
weak_ptr does not extend the lifetime of the object it points to.
lock() returns std::shared_ptr only if the object is still alive (i.e., there are shared pointers managing it).
expired() tells if the object has been destroyed.
use_count() returns the number of std::shared_ptr objects managing the object.


// Custom deleter-> you allocate memory using malloc and share this to shared_ptr, then how to delete??
//why custom deleter?? if already managed by smart pointer 






































