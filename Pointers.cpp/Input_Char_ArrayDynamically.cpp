
Taking Input for a Single String (char*)
If we want to take a single string input dynamically, 
we can allocate memory using new char[size].

Code Example:
#include <iostream>
using namespace std;
int main() {
    int size;
    cout << "Enter the length of the string: ";
    cin >> size;

    // Allocate memory for the string (size + 1 for null terminator '\0')
    char *str = new char[size + 1];

    cout << "Enter the string: ";
    cin.ignore(); // Ignore newline left in buffer
    cin.getline(str, size + 1); // Read string with spaces

    cout << "Stored String: " << str << endl;
    delete[] str;  // Free allocated memory
    return 0;
}
🔹 Output:
Enter the length of the string: 10
Enter the string: Hello C++
Stored String: Hello C++
📌 cin.getline(str, size+1) is used instead of cin >> str to read the entire line, including spaces.
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
2️⃣ Taking Input for Multiple Strings (char**)
To store multiple dynamically allocated strings, 
we use a double pointer (char**).

Code Example:
#include <iostream>
using namespace std;
int main() {
    int n, maxLen;
    cout << "Enter the number of strings: ";
    cin >> n;
    cout << "Enter the maximum length of each string: ";
    cin >> maxLen;
    char **strArray = new char*[n]; // Allocate memory for array of character pointers

    // Allocate memory for each string
    cin.ignore(); // Ignore newline left in buffer
    cout << "Enter " << n << " strings:\n";
    for (int i = 0; i < n; i++) {
        strArray[i] = new char[maxLen + 1];
        cin.getline(strArray[i], maxLen + 1); // Read string
    }
    cout << "\nStored Strings:\n";
    for (int i = 0; i < n; i++) {
        cout << strArray[i] << endl;  // Display stored string
    }

    // Deallocate memory
    for (int i = 0; i < n; i++) {
        delete[] strArray[i];  // Free each string
    }
    delete[] strArray;  // Free array of pointers
    return 0;
}
🔹 Output Example:
Enter the number of strings: 3
Enter the maximum length of each string: 20
Enter 3 strings:
Hello World
Dynamic Allocation
C++ Programming

Stored Strings:
Hello World
Dynamic Allocation
C++ Programming
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
📌 Key Points:

new char*[n] → Allocates an array of pointers.
new char[maxLen + 1] → Allocates space for each string.
cin.ignore() → Clears input buffer to prevent skipping inputs.
cin.getline() → Reads strings with spaces.
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
3️⃣ Using vector<string> for Simplicity
Instead of manually managing memory, vector<string> simplifies things.
#include <iostream>
#include <vector>
using namespace std;
int main() {
    int n;
    cout << "Enter number of strings: ";
    cin >> n;
    cin.ignore(); // Ignore newline left in buffer
    vector<string> words(n);

    cout << "Enter " << n << " strings:\n";
    for (int i = 0; i < n; i++) {
        getline(cin, words[i]); // Directly read string
    }

    cout << "\nStored Strings:\n";
    for (const string &word : words) {
        cout << word << endl;
    }
    return 0;
}
 // vector<string> automatically manages memory, avoiding manual allocation and deallocation.

🔹 Summary Table
Method	                           Pros                                            	Cons
Single char*	              Simple, dynamic input	                             Needs manual delete[]
char** (Array of Strings)	  Flexible, stores multiple strings	                Requires careful memory management
vector<string>	              No manual memory handling, easy to use	        Requires STL (C++ only)
🔹 Key Takeaways
✅ char* dynamically stores a single string.
✅ char** dynamically stores multiple strings (array of pointers).
✅ vector<string> is easier and safer for handling dynamic strings.
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

1️⃣ vector<string>: Pros & Cons
✅ Advantages:
Automatic Memory Management → No need to manually allocate and deallocate memory (avoids memory leaks).
Easy to Use → Provides built-in functions like push_back(), size(), sort(), etc.
Safe → No risk of dangling pointers or buffer overflows.
Efficient Resizing → Automatically grows and shrinks as needed.
String Manipulation → Supports operations like +=, substr(), find(), etc.
❌ Disadvantages:
More Overhead → Internally manages memory using dynamic allocation.
Less Control Over Memory → Can't manually allocate fixed-size memory for optimization.
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
2️⃣ char**: Pros & Cons
✅ Advantages:
Fine Control Over Memory → You can allocate exact memory needed (more optimized).
Lower Overhead → Avoids vector<string>'s additional memory allocations.
Can Be Used in Low-Level Programming → Useful for embedded systems.
❌ Disadvantages:
Manual Memory Management → You must use new and delete[], or risk memory leaks.
More Complex to Use → Requires explicit allocation for each string.
Unsafe Operations → Easy to cause segmentation faults due to improper memory handling.
Limited String Manipulation → No direct functions like +=, substr(), etc.