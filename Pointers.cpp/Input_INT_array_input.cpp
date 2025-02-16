1️⃣ One-Dimensional (1D) Array Using Pointers
🔹 Static Allocation (Stack Memory)
#include <iostream>
using namespace std;
int main() {
    int n;
    cout << "Enter size of array: ";
    cin >> n;
    
    int arr[n]; // Static allocation
    cout << "Enter " << n << " elements:\n";
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }
    cout << "Stored Elements:\n";
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    } 
    return 0;
}
🔹 Dynamic Allocation (Heap Memory)     ///////////////////////////////////////////////////////////
#include <iostream>
using namespace std;

int main() {
    int n;
    cout << "Enter size of array: ";
    cin >> n;

    int *arr = new int[n]; // Dynamic allocation

    cout << "Enter " << n << " elements:\n";
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }

    cout << "Stored Elements:\n";
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }

    delete[] arr; // Free memory
    return 0;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
2️⃣ Two-Dimensional (2D) Array Using Pointers
🔹 Static Allocation (Stack Memory)
#include <iostream>
using namespace std;
int main() {
    int rows, cols;
    cout << "Enter rows and columns: ";
    cin >> rows >> cols;

    int arr[rows][cols]; // Static allocation

    cout << "Enter elements:\n";
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            cin >> arr[i][j];
        }
    }
    cout << "Stored Matrix:\n";
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            cout << arr[i][j] << " ";
        }
        cout << endl;
    }
    return 0;
}
🔹 Dynamic Allocation (int** - Array of Pointers) ////////////////////////////////////////////////////////////
#include <iostream>
using namespace std;
int main() {
    int rows, cols;
    cout << "Enter rows and columns: ";
    cin >> rows >> cols;
    int **arr = new int*[rows]; // Allocate an array of pointers
    for (int i = 0; i < rows; i++) {   
        arr[i] = new int[cols];    // Allocate memory for each row
    }
    cout << "Enter elements:\n";
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            cin >> arr[i][j];
        }
    }
    cout << "Stored Matrix:\n";
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            cout << arr[i][j] << " ";
        }
        cout << endl;
    }
    // Free allocated memory
    for (int i = 0; i < rows; i++) {
        delete[] arr[i]; // Free each row
    }
    delete[] arr;      // Free array of pointers
    return 0;
}
🔹 Dynamic Allocation (int* - Single Block Memory) // 2D array using single pointer
#include <iostream>
using namespace std;

int main() {
    int rows, cols;
    cout << "Enter rows and columns: ";
    cin >> rows >> cols;

    int *arr = new int[rows * cols]; // Single block allocation

    cout << "Enter elements:\n";
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            cin >> arr[i * cols + j]; // 1D index
        }
    }

    cout << "Stored Matrix:\n";
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            cout << arr[i * cols + j] << " ";
        }
        cout << endl;
    }

    delete[] arr; // Free memory

    return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
3️⃣ Three-Dimensional (3D) Array Using Pointers
🔹 Static Allocation (Stack Memory)
#include <iostream>
using namespace std;
int main() {
    int x, y, z;
    cout << "Enter dimensions (x y z): ";
    cin >> x >> y >> z;
    int arr[x][y][z]; // Static allocation
    cout << "Enter elements:\n";
    for (int i = 0; i < x; i++) {
        for (int j = 0; j < y; j++) {
            for (int k = 0; k < z; k++) {
                cin >> arr[i][j][k];
            }
        }
    }
    cout << "Stored 3D Array:\n";
    for (int i = 0; i < x; i++) {
        for (int j = 0; j < y; j++) {
            for (int k = 0; k < z; k++) {
                cout << arr[i][j][k] << " ";
            }
            cout << endl;
        }
        cout << endl;
    }
    return 0;
} 
🔹 Dynamic Allocation (int*** - Array of Pointers)///////////////////////////////////////////////////////////
#include <iostream>
using namespace std;
int main() {
    int x, y, z;
    cout << "Enter dimensions (x y z): ";
    cin >> x >> y >> z;
    int ***arr = new int**[x]; // Allocate memory for 3D array
    for (int i = 0; i < x; i++) {
        arr[i] = new int*[y];
        for (int j = 0; j < y; j++) {
            arr[i][j] = new int[z];
        }
    }

    cout << "Enter elements:\n";
    for (int i = 0; i < x; i++) {
        for (int j = 0; j < y; j++) {
            for (int k = 0; k < z; k++) {
                cin >> arr[i][j][k];
            }
        }
    }

    cout << "Stored 3D Array:\n";
    for (int i = 0; i < x; i++) {
        for (int j = 0; j < y; j++) {
            for (int k = 0; k < z; k++) {
                cout << arr[i][j][k] << " ";
            }
            cout << endl;
        }
        cout << endl;
    }

    // Free allocated memory
    for (int i = 0; i < x; i++) {
        for (int j = 0; j < y; j++) {
            delete[] arr[i][j];
        }
        delete[] arr[i];
    }
    delete[] arr;

    return 0;
}
Comparison of Methods
Method	                 Memory Allocation	         Flexibility	           Performance
Static (Stack)	         Fixed size, fast	         ❌ Not resizable	     ✅ Fastest
Dynamic (int**)	         Heap, row-wise allocation	 ✅ Resizable	         ⚠️ Moderate overhead
Dynamic (int*)	         Heap, single block	         ✅ Resizable	         ✅ Efficient
Dynamic (int***)	     Heap, pointer hierarchy	 ✅ Fully dynamic	     ⚠️ Higher memory overhead
🚀 Final Thoughts
✔ Use static allocation when size is known at compile time.
✔ Use int** (array of pointers) when flexibility is needed.
✔ Use int* (single block) for efficient 2D arrays.
✔ **Use int*** for complex 3D dynamic arrays, but only when necessary.