Accessing 1D and 2D Static Arrays Using Pointers in C++

1️⃣ One-Dimensional (1D) Array Using Pointers
A 1D array is stored contiguously in memory. 

🔹/////////////////// Method 1: Using Array Indexing (arr[i])
#include <iostream>
using namespace std;
int main() {
    int arr[5] = {10, 20, 30, 40, 50};
    cout << "Accessing using array indexing:\n";
    for (int i = 0; i < 5; i++) {
        cout << arr[i] << " ";
    }
    return 0;
}
✅ Output:
Accessing using array indexing:
10 20 30 40 50 

🔹 //////////////////////////Method 2: Using Pointer Arithmetic (*(ptr + i))
#include <iostream>
using namespace std;

int main() {
    int arr[5] = {10, 20, 30, 40, 50};
    int *ptr = arr;  // Pointer to first element

    cout << "Accessing using pointer arithmetic:\n";
    for (int i = 0; i < 5; i++) {
        cout << *(ptr + i) << " ";
    }
    return 0;
}
✅ Output:
Accessing using pointer arithmetic:
10 20 30 40 50 
📌 Key Takeaways:
ptr + i moves to the next integer in memory.
*(ptr + i) accesses the value at that location.
🔹////////////////////////////////////////////// Method 3: Using Pointer Incrementation (ptr++)
#include <iostream>
using namespace std;
int main() {
    int arr[5] = {10, 20, 30, 40, 50};
    int *ptr = arr;  // Pointer to first element

    cout << "Accessing using pointer incrementation:\n";
    for (int i = 0; i < 5; i++) {
        cout << *ptr << " ";
        ptr++;  // Move to the next element
    }

    return 0;
}
✅ Output:
Accessing using pointer incrementation:
10 20 30 40 50 
📌 Key Takeaways:

ptr++ moves to the next integer in memory.
*ptr accesses the current element.
2️⃣ Two-Dimensional (2D) Array Using Pointers
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

A 2D static array is stored in row-major order,elements are stored row by row in contiguous memory.

🔹/////////////////// Method 1: Using Array Indexing (arr[i][j])
#include <iostream>
using namespace std;
int main() {
    int arr[2][3] = {{1, 2, 3}, {4, 5, 6}};
    cout << "Accessing using array indexing:\n";
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 3; j++) {
            cout << arr[i][j] << " ";
        }
        cout << endl;
    }
    return 0;
}
✅ Output:
Accessing using array indexing:
1 2 3 
4 5 6 
🔹////////////////////////////////Method 2: Using Pointer to 2D Array (int (*ptr)[cols])
#include <iostream>
using namespace std;
int main() {
    int arr[2][3] = {{1, 2, 3}, {4, 5, 6}};
    int (*ptr)[3] = arr;  // means Pointer to an array of 3 integers(column size is 3)
  
    cout<<arr;// first block address
    cout<<*arr;// first block address
    cout<<arr[0];//first block address
    cout<<arr[0][0];//first block address

    cout << "Accessing using pointer to an array:\n";
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 3; j++) {
            cout << *(*(ptr + i) + j) << " "; // Equivalent to arr[i][j] == *(ptr[i]+j)==*(*(ptr + i) + j)
        }
        cout << endl;
    }
    /* Explanation of Methods
 
/*    
ptr - This is a pointer to a pointer (int** ptr), representing a dynamically allocated 2D array.*/

/*    
ptr + i - Moves to the i-th row. Since ptr is an array of pointers (each pointing to a row), ptr + i gives the address of row i.*/

/*     
 *(ptr + i) - Dereferencing ptr + i gives the base address of the i-th row (i.e., the first element of that row).*/

 /* 
*(ptr + i) + j - Moves to the j-th column within the i-th row. Since *(ptr + i) is a pointer to the first element of the row, adding j moves j positions forward in that row.*/

/*  
 *(*(ptr + i) + j)  - Finally, dereferencing this expression gives the actual value stored at the i-th row and j-th column.*/
1️⃣ Using arr[i][j] (Normal Indexing)

Directly accesses the element at row i and column j.
arr[1][2] gives 6.
2️⃣ Using *(ptr[i] + j)

ptr[i] stores the base address of row i.
ptr[i] + j moves j columns ahead in row i.
*(ptr[1] + 2) is 6.
3️⃣ Using *(*(ptr + i) + j)

ptr is a pointer array storing row addresses.
*(ptr + i) gives pointer to row i.
*(*(ptr + i) + j) accesses element at arr[i][j].
Summary Table
Method	                          Formula	                    Description
Indexing	                      arr[i][j]	                    Directly accesses the element
Pointer with row indexing	      *(ptr[i] + j)	                ptr[i] points to row i, moves j columns forward
Pointer arithmetic	            *(*(ptr + i) + j)	   ptr + i moves to row i, *(ptr + i) + j moves j columns forward */
    return 0;
}
✅ Output:
Accessing using pointer to an array:
1 2 3 
4 5 6 
📌 Key Takeaways:
ptr is a pointer to a row (array of 3 integers).
*(*(ptr + i) + j) is equivalent to arr[i][j].
🔹////////////////////////////// Method 3: Using a Simple Integer Pointer (int* ptr)
Since a 2D array is stored contiguously, we can treat it as a 1D array.
#include <iostream>
using namespace std;

int main() {
    int arr[2][3] = {{1, 2, 3}, {4, 5, 6}};
    
    int *ptr = &arr[0][0]; // Pointer to the first element

    cout << "Accessing using a simple pointer:\n";
    for (int i = 0; i < 2 * 3; i++) { // 2 rows * 3 columns = 6 elements
        cout << *(ptr + i) << " ";
    }

    return 0;
}
✅ Output:
Accessing using a simple pointer:
1 2 3 4 5 6 
📌 Key Takeaways:
ptr points to the first element (&arr[0][0]).
We access elements in row-major order using *(ptr + i).
🔹 /////////////////////////////////  Method 4: Using an Array of Pointers
We can store row addresses in an array of pointers.
#include <iostream>
using namespace std;
int main() {
    int arr[2][3] = {{1, 2, 3}, {4, 5, 6}};
    int *rowPtrs[2]; // Array of pointers to rows
    for (int i = 0; i < 2; i++) {
        rowPtrs[i] = arr[i]; // Point to each row
    }
    cout << "Accessing using an array of row pointers:\n";
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 3; j++) {
            cout << rowPtrs[i][j] << " "; // Equivalent to arr[i][j]
        }
        cout << endl;
    }

    return 0;
}
✅ Output:
Accessing using an array of row pointers:
1 2 3 
4 5 6 
📌 Key Takeaways:

rowPtrs[i] stores the address of the ith row.
rowPtrs[i][j] is equivalent to arr[i][j].
🚀 Summary Table
Method	Pointer Type	     Access            Notation	                Usage
1D - Indexing	            int arr[]	        arr[i]	                Normal access
1D - Pointer Arithmetic	    int* ptr	        *(ptr + i)	            Pointer-based access
1D - Pointer Incrementation	int* ptr	        *ptr, ptr++	            Iterative pointer movement
2D - Indexing	            int arr[][cols]	    arr[i][j]	            Normal access
2D - Pointer to Array	    int (*ptr)[cols]	*(*(ptr + i) + j)	    Full array pointer
2D - Simple Pointer	        int* ptr	        *(ptr + index)	        Treats 2D as 1D
2D - Array of Pointers	    int* rowPtrs[rows]	rowPtrs[i][j]	         Stores row addresses
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
 
Methods to Access a 3D Array
1️⃣ Using Normal Indexing (arr[i][j][k])
#include <iostream>
using namespace std;
int main() {
    int arr[2][3][4] = {
        {{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}},
        {{13, 14, 15, 16}, {17, 18, 19, 20}, {21, 22, 23, 24}}
    };
    cout << "Accessing using normal indexing:\n";
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 3; j++) {
            for (int k = 0; k < 4; k++) {   
                cout << arr[i][j][k] << " ";//cout << *(*(*(ptr + i) + j) + k) << " "; all same
            }                               // cout << *(ptr[i][j] + k) << " ";
            cout << endl;
        }
        cout << endl;
    }
    return 0;
}
✅ Output:
Accessing using normal indexing:
1 2 3 4 
5 6 7 8 
9 10 11 12 

13 14 15 16 
17 18 19 20 
21 22 23 24 
////////////////////////////
#METHOD 2️⃣ Using Pointer to a 2D Array (int (*ptr)[cols][depth])
Since arr is an array of 2D arrays, we can use a pointer to a 2D array.
#include <iostream>
using namespace std;
int main() {
    int arr[2][3][4] = {
        {{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}},
        {{13, 14, 15, 16}, {17, 18, 19, 20}, {21, 22, 23, 24}}
    };
    int (*ptr)[3][4] = arr; // Pointer to a 2D array
    cout << "Accessing using pointer to 2D array:\n";
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 3; j++) {
            for (int k = 0; k < 4; k++) {
                cout << *(*(*(ptr + i) + j) + k) << " ";
                cout << *(ptr[i][j] + k) << " "; //Equivalent to arr[i][j][k] == *(*(*(ptr + i) + j) + k)==*(*(ptr[i]+j) + k)==*(ptr[i][j] + k)
            }
            cout << endl;
        }
        cout << endl;
    }
    return 0;
}
✅ Output (Same as above)
Explanation:
ptr[i][j] stores the address of row j in block i.
*(ptr[i][j] + k) accesses column k.
📌 Explanation:
ptr is a pointer to a 2D array ([3][4]).
*(ptr + i) moves to block i.
*(*(ptr + i) + j) moves to row j.
*(*(*(ptr + i) + j) + k) accesses column k.
////////////////////////////////////////////METHOD:4

#include <iostream>
using namespace std;
int main() {
    int arr[2][3][4] = {
        {{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}},
        {{13, 14, 15, 16}, {17, 18, 19, 20}, {21, 22, 23, 24}}
    };

    int (*ptr)[3][4] = arr; // Pointer to a 2D array

    cout << "Accessing using pointer to 2D array:\n";
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 3; j++) {
            for (int k = 0; k < 4; k++) {
                cout << *(*(*(ptr + i) + j) + k) << "__";
                cout << *(ptr[i][j] + k) << " "; // Equivalent to arr[i][j][k]
            }
            cout << endl;
        }
        cout << endl;
    }

    return 0;
}


