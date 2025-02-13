#Pointers with Arrays -  
An array name itself acts as a pointer to its first element.
Pointers provide efficient memory access and can be used to modify array elements.
#include <iostream>
using namespace std;

int main() {
    int arr[] = {10, 20, 30, 40, 50};
    int *ptr = arr;  // arr acts as a pointer to the first element

    cout << "First element: " << *ptr << endl;
    cout << "Second element: " << *(ptr + 1) << endl; // Moving pointer to next element
    cout << "Third element: " << *(ptr + 2) << endl;

    return 0;
}
Output:
First element: 10
Second element:20
Third element: 30
arr is a pointer to arr[0]
ptr + 1 moves the pointer to the next integer (increments by sizeof(int))
*(ptr + 1) gets the second element

#include <iostream>
using namespace std;
int main() {
    int arr[] = {5, 15, 25, 35, 45};
    int *ptr = arr; //   arr acts as a pointer to the first element
    for (int i = 0; i < 5; i++) {
        cout << "Element " << i << ": " << *(ptr + i) << endl;
    }
    return 0;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#Pointer to an ENTIRE ARRAY- 
A pointer can store the address of an entire array.
#include <iostream>
using namespace std;
int main() {
    int arr[5] = {2, 4, 6, 8, 10};
    int (*ptr)[5] = &arr;  // Pointer to an array
    cout << "First element: " << (*ptr)[0] << endl;
    cout << "Second element: " << (*ptr)[1] << endl;

    return 0;
}
Output:
First element: 2
Second element: 4
Explanation: int (*ptr)[5] = &arr; ----→ ptr points to the entire array.
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Dynamic Memory Allocation for Arrays- 1D Array

You can use new to allocate arrays dynamically.
#include <iostream>
using namespace std;
int main() {
    int *arr = new int[5];  // Dynamic array allocation
    for (int i = 0; i < 5; i++) {
        arr[i] = i +10 ;  // Assigning values dynamically
    }
    cout << "Dynamically allocated array: ";
    for (int i = 0; i < 5; i++) {
        cout << arr[i] << " ";
    }
    delete[] arr;  // Free allocated memory
    return 0;
}
Output:
Dynamically allocated array: 10 11 12 13 14
new int[5] dynamically allocates memory.
delete[] arr; releases the memory.
///////////////////////////////////////////////////////////////////////////////////////////////////
2D Array - 
#include <iostream>
using namespace std;
int main() {
    int rows, cols;
    cout << "Enter rows and columns: ";
    cin >> rows >> cols;

    int **arr = new int*[rows];// Allocate memory for row pointers
    for (int i = 0; i < rows; i++) {
        arr[i] = new int[cols];  // Allocate memory for each row
    }
    // Assign values
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            arr[i][j] = (i + 1) * (j + 1);
        }
    }
    // Deallocate memory
    for (int i = 0; i < rows; i++) {
        delete[] arr[i]; // Delete each row
    }
    delete[] arr; // Delete row pointers

    return 0;
}
new int*[rows] creates an array of pointers.
new int[cols] allocates memory for each row.
Memory is freed correctly using delete[].
////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#Array as Function Arguments:
#1.Passing an Array by Pointer (Recommended) 
Since arrays cannot be passed by value, we typically pass them by pointer.
#include <iostream>
using namespace std;
void printArray(int arr[] /*  or int *arr*/ , int size) {  // Equivalent to int *arr , int arr[]=int *arr
    cout << "Array elements: ";
    for (int i = 0; i < size; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}
int main() {
    int myArray[] = {10, 20, 30, 40, 50};
    int size = sizeof(myArray) / sizeof(myArray[0]);
    printArray(myArray, size);  // Pass array to function
    return 0;
}
Output: Array elements: 10 20 30 40 50
✅ Explanation:
arr[] in printArray(int arr[], int size) is actually a pointer (int *arr).
We must pass array size explicitly since sizeof(arr) inside the function will return the pointer size.
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#2.Passing an Array by Reference (Avoids Pointer Decay)
When an array is passed normally, it decays into a pointer. To prevent this and keep array size information, use reference to array (int (&arr)[size]).

Example:
#include <iostream>
using namespace std;
void printArray(int (&arr)[5]) { // Reference to an array of size 5
    cout << "Array elements: ";
    for (int i = 0; i < 5; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}
int main() {
    int myArray[] = {1, 2, 3, 4, 5};
    printArray(myArray);  // Array size is preserved
    return 0;
}
Output:
Array elements: 1 2 3 4 5
✅ Explanation:
int (&arr)[5] ensures only arrays of size 5 are accepted.
This prevents array decay and maintains size information.
//////////////////////////////////////////////////////////////////////////////////////////////////////////////3. Passing a Dynamically Allocated Array
#3Passing a Dynamically Allocated Array
If an array is created using new, we pass a pointer
#include <iostream>
using namespace std;

void printArray(int *arr, int size) {  
    for (int i = 0; i < size; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}
int main() {
    int size;
    cout << "Enter array size: ";
    cin >> size;
    int *arr = new int[size];  // Dynamically allocated array
    for (int i = 0; i < size; i++) {
        arr[i] = (i + 1) * 10;
    }
    printArray(arr, size);
    delete[] arr; // Free memory
    return 0;
}
Output:
Enter array size: 5
10 20 30 40 50
✅ Explanation:
new int[size] dynamically allocates an array.
printArray(arr, size); passes the pointer to the first element.

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#4.Passing a 2D Array (Fixed Columns)
Since 2D arrays are stored row-wise, we must pass the column size explicitly.
#include <iostream>
using namespace std;
void print2DArray(int arr[][3], int rows) {  // Column size must be known
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < 3; j++) {
            cout << arr[i][j] << " ";
        }
        cout << endl;
    }
}
int main() {
    int myArray[2][3] = {{1, 2, 3}, {4, 5, 6}};
    print2DArray(myArray, 2);
    return 0;
}
Output:
1 2 3
4 5 6
✅ Explanation:
int arr[][3] requires column size to be known at compile time.
Row size can be passed as an argument.

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#5. Passing a 2D Array Dynamically
To pass a 2D array with flexible dimensions, we use pointers.
#include <iostream>
using namespace std;
void print2DArray(int **arr, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            cout << arr[i][j] << " ";
        }
        cout << endl;
    }
}
int main() {
    int rows, cols;
    cout << "Enter rows and columns: ";
    cin >> rows >> cols;
    // Allocate memory for row pointers
    int **arr = new int*[rows];
    // Allocate memory for each row
    for (int i = 0; i < rows; i++) {
        arr[i] = new int[cols];
    }
    // Fill array
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            arr[i][j] = i * cols + j + 1;
        }
    }
    print2DArray(arr, rows, cols);
    // Free memory
    for (int i = 0; i < rows; i++) {
        delete[] arr[i];
    }
    delete[] arr;
    return 0;
}
Output:
Enter rows and columns: 3 3
1 2 3
4 5 6
7 8 9
✅ Explanation:
int **arr = new int*[rows]; creates an array of row pointers.
arr[i] = new int[cols]; dynamically allocates columns.

Method	                            Syntax	                           Use Case
Pass by Pointer	            void fun(int *arr, int size)	          Works for both static and dynamic arrays
Pass by Reference	        void fun(int (&arr)[size])	              Preserves array size information
Pass Dynamically Allocated	void fun(int *arr, int size)	          Works for arrays created with new
Pass 2D Array (Fixed Size)	void fun(int arr[][cols], int rows)	      Requires known column size
Pass Dynamic 2D Array	    void fun(int **arr, int rows, int cols)	  Supports flexible dimensions






