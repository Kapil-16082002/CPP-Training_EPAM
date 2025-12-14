✅Key notes:

1.unique_ptr<T[]> supports arrays and calls delete[] automatically.
2.Nested allocations (triple new e.g. int*** with inner new[]) require manual deletion of each inner block — you can wrap inner pointers with smart pointers, 
but there's no single smart pointer that magically deletes nested allocations unless you write custom wrappers.

4.weak_ptr does not own memory — it observes a shared_ptr and becomes invalid once no shared_ptr owners remain.


✅NOTE:
//or if C++17:
auto sarr = std::make_shared<int[]>(n);   // Not support array
std::shared_ptr<int[]> sarr(new int[n]); 
// <- automatically calls delete[] here


// C++20 and above
auto sarr = std::make_shared<int[]>(n);   // will support array



//=================================================================================================================
// ---------- 1D examples ----------


void demo1D_raw(int n) {

    int* arr = new int[n];
    for (int i = 0; i < n; ++i) arr[i] = i + 1;
    for (int i = 0; i < n; ++i) cout << arr[i] << ' ';

    delete[] arr; // must delete[]
}
void demo1D_unique(int n) {

    auto arr = std::make_unique<int[]>(n); // allocate contiguous block  //always allocates memory dynamically (on the heap).
    for (int i = 0; i < n; ++i) arr[i] = (i + 1) * 10;
    for (int i = 0; i < n; ++i) cout << arr[i] << ' ';

    // arr is freed automatically when function returns
}

void demo1D_shared_weak(int n) {

    // NOTE: std::make_shared<T[]> is not part of the language (no make_shared for arrays),
    // but shared_ptr<T[]> can be constructed from new T[n]. shared_ptr will call delete[].
    std::shared_ptr<int[]> sarr(new int[n]); //  shared_ptr<T[]> specialization calls delete[] automatically
    for (int i = 0; i < n; ++i) sarr[i] = (i + 1) * 100;
    cout << "sarr: ";
    for (int i = 0; i < n; ++i) cout << sarr[i] << ' ';


    std::weak_ptr<int[]> warr = sarr; // observe
    cout << "\nweak_ptr.lock() checks owner: " << (warr.lock() ? "alive" : "expired") << '\n';
    sarr.reset(); // drop the shared owner; array will be freed now
    cout << "After sarr.reset(), weak_ptr.lock() => " << (warr.lock() ? "alive" : "expired") << '\n';
}

// ========================    2D examples   ======================================================================

void demo2D_raw_rows(int R, int C) {
    cout << "\n--- 2D raw (rows separate) R=" << R << " C=" << C << " ---\n";
    int** mat = new int*[R];
    for (int r = 0; r < R; ++r) {
        mat[r] = new int[C];            // allocate each row separately
        for (int c = 0; c < C; ++c) mat[r][c] = r * 10 + c;
    }
    cout << "mat:\n";
    for (int r = 0; r < R; ++r) {
        for (int c = 0; c < C; ++c) cout << mat[r][c] << ' ';
        cout << '\n';
    }
    // delete rows then the array of pointers
    cout << "Deleting rows and pointer-array...\n";
    for (int r = 0; r < R; ++r) delete[] mat[r];
    delete[] mat;
}

// 2D best practice: single contiguous block + unique_ptr
void demo2D_unique_block(int R, int C) {
    cout << "\n--- 2D single-block unique_ptr (R=" << R << " C=" << C << ") ---\n";
  

    // Step 1: allocate array of row pointers
    unique_ptr<int*[]> arr(new int*[rows]);

    // Step 2: allocate each row
    for (int i = 0; i < rows; i++)
        arr[i] = new int[cols];   // allocate row

    // Fill values
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            arr[i][j] = i + j;

    // Print
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++)
            cout << arr[i][j] << " ";
        cout << endl;
    }
    // Destructor of unique_ptr will:
    // 1. call delete[] on each row
    // 2. call delete[] on arr itself
}

}

// 2D using shared_ptr single block
void demo2D_shared_block(int R, int C) {

    shared_ptr<int*[]> arr(new int*[rows]); // outer array of row pointers (will be deleted automatically with delete[])
    for (int i = 0; i < rows; ++i) {   // allocate each row (raw new)
        arr[i] = new int[cols];
    }

    // Fill values
    for (int i = 0; i < rows; ++i)
        for (int j = 0; j < cols; ++j)
            arr[i][j] = i + j;

    // Print
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j)
            cout << arr[i][j] << " ";
        cout << endl;
    }

    // delete each row manually (because rows were allocated with new[])
    for (int i = 0; i < rows; ++i) {
        cout << "Deleting row " << i << endl;
        delete[] arr[i];
    }

    // arr (outer array) will be deleted automatically when arr goes out of scope
    return 0;
}

// ---------- 3D examples ----------
// 3D raw triple pointer (very verbose; demonstrates deletion requirements)
void demo3D_raw_triple(int X, int Y, int Z) {
    cout << "\n--- 3D raw triple-pointer (X=" << X << " Y=" << Y << " Z=" << Z << ") ---\n";
    int*** a = new int**[X];
    for (int x = 0; x < X; ++x) {
        a[x] = new int*[Y];
        for (int y = 0; y < Y; ++y) {
            a[x][y] = new int[Z];
            for (int z = 0; z < Z; ++z) a[x][y][z] = x*100 + y*10 + z;
        }
    }
    cout << "a[1][1][1] = " << a[1][1][1] << '\n';
    // Must delete in reverse order: inner arrays, then rows, then top-level
    cout << "Deleting triple-pointer structure (many deletes)...\n";
    for (int x = 0; x < X; ++x) {
        for (int y = 0; y < Y; ++y) delete[] a[x][y];
        delete[] a[x];
    }
    delete[] a;
}

// 3D best practice: single contiguous block managed by unique_ptr
void demo3D_unique_block(int X, int Y, int Z) {
    
    int X = 2, Y = 3, Z = 4;  // 3D dimensions
    unique_ptr<int**[]> arr(new int**[X]);  // Step 1: allocate outer array of int** pointers
   
    // Step 2 & 3: allocate second and third level
    for (int i = 0; i < X; ++i) {
        arr[i] = new int*[Y];     // allocate Y pointers
        for (int j = 0; j < Y; ++j) {
            arr[i][j] = new int[Z];  // allocate Z integers
        }
    }

    // Fill values
    for (int i = 0; i < X; ++i)
        for (int j = 0; j < Y; ++j)
            for (int k = 0; k < Z; ++k)
                arr[i][j][k] = i + j + k;

    // Print 3D Array
    for (int i = 0; i < X; ++i) {
        cout << "Layer " << i << ":\n";
        for (int j = 0; j < Y; ++j) {
            for (int k = 0; k < Z; ++k)
                cout << arr[i][j][k] << " ";
            cout << endl;
        }
        cout << endl;
    }

    // DELETE all allocated memory manually (unique_ptr can't do inner deletes)
    for (int i = 0; i < X; ++i) {
        for (int j = 0; j < Y; ++j) {
            cout << "Deleting arr[" << i << "][" << j << "]\n";
            delete[] arr[i][j];  // delete Z-level
        }
        cout << "Deleting arr[" << i << "]\n";
        delete[] arr[i];  // delete Y-level
    }
    // Outer array (X level) deleted automatically by unique_ptr

    return 0;
}

// 3D using shared_ptr single block
void demo3D_shared_block(int X, int Y, int Z) {
 
    int X = 2, Y = 3, Z = 4;  // 3D dimensions

    shared_ptr<int**[]> arr(new int**[X]); // Step 1: allocate outer array of int** pointers

    for (int i = 0; i < X; ++i) {   // Step 3: allocate third level (actual int arrays of size Z)
        arr[i] = new int*[Y];        // Step 2: allocate second level (int* pointers for each Y)
        for (int j = 0; j < Y; ++j) {
            arr[i][j] = new int[Z];
        }
    }

    // Fill values
    for (int i = 0; i < X; ++i)
        for (int j = 0; j < Y; ++j)
            for (int k = 0; k < Z; ++k)
                arr[i][j][k] = i + j + k;

    // Print 3D Array
    for (int i = 0; i < X; ++i) {
        cout << "Layer " << i << ":\n";
        for (int j = 0; j < Y; ++j) {
            for (int k = 0; k < Z; ++k)
                cout << arr[i][j][k] << " ";
            cout << endl;
        }
        cout << endl;
    }

    // DELETE all allocated memory manually
    for (int i = 0; i < X; ++i) {
        for (int j = 0; j < Y; ++j) {
            cout << "Deleting arr[" << i << "][" << j << "]\n";
            delete[] arr[i][j];  // delete Z level
        }
        cout << "Deleting arr[" << i << "]\n";
        delete[] arr[i];  // delete Y level
    }
    // Outer array (X level) is deleted automatically by shared_ptr
    return 0;

}

// ---------- Explanation output function ----------
void explainUnsupported() {
    cout << "\n--- Notes / Explanations ---\n";
    cout << "1) make_shared<T[]> is NOT provided by the standard; you must use shared_ptr<T[]> with new T[n].\n";
    cout << "   Reason: make_shared stores control block + object together; array-specialization complicates element construction/destruction.\n";
    cout << "2) nested allocations (like int*** with inner new[] per row) require manual delete[] for each inner allocation.\n";
    cout << "   There is no single standard smart pointer that automatically deletes nested separate allocations unless you wrap each level in a smart pointer.\n";
    cout << "3) Preferred patterns: (a) use single contiguous block (fast, simple) or (b) use std::vector (easier) for dynamic multi-dim arrays.\n";
}

// ---------- main runs all demos ----------
int main() {
    cout << ">>> Arrays demo (raw, unique_ptr, shared_ptr/weak_ptr)\n";

    // 1D
    demo1D_raw(5);
    demo1D_unique(5);
    demo1D_shared_weak(5);

    // 2D
    demo2D_raw_rows(3, 4);
    demo2D_unique_block(3, 4);
    demo2D_shared_block(3, 4);

    // 3D
    demo3D_raw_triple(2, 3, 4);
    demo3D_unique_block(2, 3, 4);
    demo3D_shared_block(2, 3, 4);

    explainUnsupported();

    cout << "\n>>> Demo finished\n";
    return 0;
}
