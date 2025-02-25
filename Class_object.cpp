# CLASS
1. A Class is a user-defined data type that has data members and member functions.
Data members are the data variables and member functions are the functions.
2. A class is a blueprint or template for creating objects. 

# OBJECTS
1. An object is an instance of a class. It holds the actual data and can use the methods defined by the class.
2. Multiple objects can be created from the same class, each with different data.

#Note: When a class is defined, no memory is allocated 
but when it is instantiated (i.e. an object is created) memory is allocated.

class Car {
public:
    string brand = "Toyota";  // Compile-time input/////////////
    int speed = 120;
    void display() {
        cout << "Brand: " << brand << ", Speed: " << speed << " km/h" << endl;
    }
};
int main() {
    Car car1;  // Object creation
    car1.display();
    return 0;
}
Output:
Brand: Toyota, Speed: 120 km/h

2.2 Run-time Input (User Input)////////////////////////

class Car {
public:
    string brand;
    int speed;
    ~Car(){
       cout<<"Distructor Called!" << endl;
    }
    void input() {
        cout << "Enter brand: ";
        cin >> brand;
        cout << "Enter speed: ";
        cin >> speed;
    }
    void display() {
        cout << "Brand: " << brand << ", Speed: " << speed << " km/h" << endl;
    }
    Car(){
        cout<<"Constructor Called!" << endl;
    }
    Car(int x){
        cout<<"x " <<x<< endl;
    }
};
int main() {
    Car car1(10);
    Car car1;
    car1.input();
    car1.display();
    return 0;
}
Output:
x 10
Constructor Called!
Enter brand: 76
Enter speed: 987
Brand: 76, Speed: 987 km/h
Distructor Called!
Distructor Called!
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Run-time Constructor (User Input)

class Car {
public:
    string brand;
    int speed;
    Car(string b, int s) {  // Parameterized Constructor
        brand = b;
        speed = s;
    }
    void display() {
        cout << "Brand: " << brand << ", Speed: " << speed << " km/h" << endl;
    }
};
int main() {
    string b;
    int s;
    cout << "Enter brand: ";
    cin >> b;
    cout << "Enter speed: ";
    cin >> s;

    Car car1(b, s);  // Run-time input passed to constructor
    car1.display();
    return 0;
}
Input:
Enter brand: Ford
Enter speed: 160
Output:
Brand: Ford, Speed: 160 km/h
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
4. Object Creation Methods
4.1 Stack Allocation (Compile-time)

Car car1("Tesla", 200);  // Allocated on the stack

4.2 Heap Allocation (Run-time)
Car* car2 = new Car("Audi", 220);  // Allocated on the heap
delete car2;  // Free memory manually
////////////////////////////////////////////////////////////////////////////////////////////////////////////////

6. Static Data Members & Static Member Functions
1. What are Static Data Members?
A static data member is a class variable that is shared by all objects of the class.
It belongs to the class, not individual objects.
It is declared using the static keyword inside the class but must be defined outside the class.
It gets memory allocation only once and retains its value across all objects.

6.1 Compile-time Input
class Car {
public:
    static int totalCars;
    Car() { totalCars++; }
    static void showTotal() {
        cout << "Total Cars: " << totalCars << endl;
    }
};
int Car::totalCars = 0;
int main() {
    Car c1, c2, c3;
    Car::showTotal();
    return 0;
}
Output:
Total Cars: 3
6.2 Run-time Input
class Car {
    public:
        static int totalCars; 
        Car() { totalCars++; }   
        static void showTotal() {
            cout << "Total Cars: " << totalCars << endl;
        }
    };   
    int Car::totalCars = 0;
    int main() {
        Car c1, c2, c3;       
        c1.showTotal();         
        cout << "Total Cars (using class name): " << Car::totalCars << endl;// Accessing static member via class name (recommended)      
        return 0;
    }
Input:
Enter number of cars to create: 5
Output:
Total Cars: 5
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

