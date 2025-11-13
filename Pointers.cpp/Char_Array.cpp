

🧩 1D Character Array in C++
| **Type**                           | **Declaration / Allocation**  | **Function Definition**                        | **Function Call**  |
| ---------------------------------- | ----------------------------- | ---------------------------------------------- | ------------------ |
| **Static Initialization**          | `char str[6] = "Hello";`      | `void func(char str[], int size)`              | `func(str, 6);`    |
| **Pass by Reference (Fixed Size)** | `char str[6] = "Hello";`      | `void func(char (&str)[6])`                    | `func(str);`       |
| **Template Reference (Any Size)**  | `char str[] = "Hello";`       | `template<size_t N> void func(char (&str)[N])` | `func(str);`       |
| **Dynamic Allocation**             | `char *str = new char[size];` | `void func(char *str, int size)`               | `func(str, size);` |
| **C-String (const char*)**         | `const char *str = "Hello";`  | `void func(const char *str)`                   | `func(str);`       |


🧩 2D Character Array in C++
| **Type**                                  | **Declaration / Allocation**                                                   | **Function Definition**                                     | **Function Call**        |
| ----------------------------------------- | ------------------------------------------------------------------------------ | ----------------------------------------------------------- | ------------------------ |
| **Static Fixed Columns**                  | `char names[3][10] = {"Ram", "Shyam", "Kapil"};`                               | `void func(char arr[][10], int rows)`                       | `func(names, 3);`        |
| **Static Fixed Size (Reference)**         | `char names[3][10];`                                                           | `void func(char (&arr)[3][10])`                             | `func(names);`           |
| **Template Reference (Any Size)**         | `char names[3][10];`                                                           | `template<size_t R, size_t C> void func(char (&arr)[R][C])` | `func(names);`           |
| **Pointer to 2D Array (Fixed Columns)**   | `char names[3][10];`                                                           | `void func(char (*arr)[10], int rows)`                      | `func(names, 3);`        |
| **Dynamic 2D Array (Pointer to Pointer)** | `char **arr = new char*[rows]; for(int i=0;i<rows;i++) arr[i]=new char[cols];` | `void func(char **arr, int rows, int cols)`                 | `func(arr, rows, cols);` |


/* 
char arr[] = "Hello";   // Stored in stack (modifiable)
char *ptr = "World";    // String literal (read-only in most compilers)
*/

A character array is a sequence of characters stored in contiguous memory, ending with a null character (\0)
Example:
int main() {
    char str[] = "Hello";  // Character array
    char *ptr = str;       // Pointer to first character of array

    cout << "String using pointer: " << ptr << endl;
    cout << "First character: " << *ptr << endl;
    return 0;
}
Output:
String using pointer: Hello
First character: H
✅ Explanation:
char *ptr = str; makes ptr point to the first character ('H').
cout << ptr; prints the entire string (because character pointers print until \0 is reached).
*ptr gives the first character of the string.

#include <bits/stdc++.h>
using namespace std;
int main()
{
    /*char ch[4]={'a','b','c','d'}; // way:1
    char ch[]="abcd";   // way:2
    char ch[10];          // way:3
    ch[0]='a'; 
    ch[1]='b';
    ch[2]='c';
    ch[3]='d';*/
    char ch[4]={'a','b','c','d'};
    char *ptr=ch;
    for(int i=0;i<strlen(ch);i++){    // way:1
        cout<<ptr[i]<<" ";
    }
    cout<<endl;
    for(int i=0;i<strlen(ch);i++){  // way:2
        cout<<*(ptr+i)<<" ";
    }
    return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

2.Pointer Arithmetic with Character Arrays
Since each character is 1 byte, pointer arithmetic moves one character at a time.
int main() {
    char str[] = "World";
    char *ptr = str;  // Pointer to first character
    cout << "Characters using pointer: ";
    while (*ptr != '\0') {  // Loop till null terminator
        cout << *ptr << " ";
        ptr++;  // Move pointer to next character
    }
    return 0;
}
Output:
Characters using pointer: W o r l d
✅ Explanation:
while (*ptr != '\0') iterates through the string.
ptr++ moves the pointer to the next character.

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

3. Passing a Character Array to a Function
Strings are passed as pointers to functions.
Example:
#include <iostream>
using namespace std;
void printString(char *str) {  // Function receives pointer
    cout << "Received String: " << str << endl;
}
int main() {
    char message[] = "Pointers in C++";
    printString(message);  // Pass character array
    return 0;
}
Output:
Received String: Pointers in C++
✅ Explanation:
printString(char *str) takes a character pointer as input.
printString(message); passes the address of the first character.
The function prints the entire string because it stops at \0.

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

4. Using const with Character Pointers
If we want to prevent modification of the string, we use const char *.

Example:
#include <iostream>
using namespace std;

void display(const char *str) {  // Prevents modification
    cout << "String: " << str << endl;
}

int main() {
    const char *message = "Hello, World!";
    display(message);
    return 0;
}
✅ Explanation:
const char *str ensures that str cannot be modified.
Useful for read-only string literals.

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

char str[] = "Hello";	char *ptr = "Hello";
int main() {
    char arr[] = "Hello";   // Stored in stack (modifiable)
    char *ptr = "World";    // String literal (read-only in most compilers)
    arr[0] = 'M';  // ✅ Allowed
    // ptr[0] = 'M';  // ❌ May cause segmentation fault
    //"World" is a string literal, which is stored in a read-only section of memory.
    //ptr is a pointer to that string literal, meaning it points to read-only memory.
    //Modifying this string through ptr is undefined behavior and may cause a segmentation fault.
    cout << "Array: " << arr << endl;
    cout << "Pointer: " << ptr << endl;
    return 0;
}
✅ Explanation:
arr[] is a modifiable character array.
ptr points to a string literal, which is often stored in read-only memory.

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

6. Dynamically Allocating Character Arrays
For dynamic strings, we use new.
Example:
#include <iostream>
#include <cstring>  // For strcpy()
using namespace std;
int main() {
    char *str = new char[20];  // Allocate memory dynamically
    strcpy(str, "Dynamic Memory"); // Copy string
    cout << "Dynamically allocated string: " << str << endl;
    delete[] str;  // Free memory
    return 0;
}
Output: Dynamically allocated string: Dynamic Memory
✅ Explanation:
new char[20] allocates 20 bytes dynamically.
delete[] str; prevents memory leaks.
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
7. Modifying Strings Using Pointers
Pointers can be used to modify strings.
void modifyString(char *str) {
    str[0] = 'M';  // Modify first character
}
int main() {
    char str[] = "Hello";
    modifyString(str);
    cout << "Modified String: " << str << endl;
    return 0;
}
Output:
Modified String: Mello
✅ Explanation:
char *str allows modification.
The first character changes from 'H' to 'M'.

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

8. (Double Pointers) - 
A double pointer (char**) is commonly used to handle arrays of strings (character arrays) in C++. 
This is useful when working with dynamic memory allocation, command-line arguments, and lists of strings.

A single pointer (char*) can store the address of a single string (character array).
A double pointer (char**) can store the address of multiple strings (array of character pointers).
A pointer to a pointer (char **) is useful for handling arrays of strings.
int main() {
    const char *arr[] = {"C++", "Pointers", "Arrays"};
    cout << "Using array of pointers: \n";
    for (int i = 0; i < 3; i++) {
        cout << arr[i] << endl;
    }
    return 0;
}
Output:
Using array of pointers: 
C++
Pointers
Arrays
✅ Explanation:
const char *arr[] is an array of string literals.
Each arr[i] is a pointer to a string.
Final Summary:
Pointer to Character Array	char *ptr = str; stores address of first character
Pointer Arithmetic	ptr++ moves to next character
Passing Strings to Functions	Use char *str as function argument
const with Pointers	const char *ptr prevents modification
Dynamic Allocation	char *str = new char[size]; for dynamic strings
Pointer to Pointer	Used for handling multiple strings (char **)

#include <iostream>
using namespace std;
int main() {
    char *words[] = {"Hello", "World", "C++"}; // Array of character pointers (Each pointing to a string)
    // Double pointer pointing to the array of character pointers
    char **ptr = words;
    // Printing using a double pointer
    cout << "First word: " << *ptr << endl; 
    cout << "First word: " << words[0] << endl;
    cout << "Second word: " << *(ptr + 1) << endl; 
    cout << "First word: " << words[1] << endl;    
    cout << "Third word: " << *(ptr + 2) << endl; 
    cout << "First word: " << words[2] << endl;
    return 0;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Traversing an Array of Strings Using char**
#include <iostream>
using namespace std;
void printStrings(char **ptr, int size) {
    for (int i = 0; i < size; i++) {
        cout << ptr[i] << endl;  // ptr[i] is equivalent to *(ptr + i)
    }
}
int main() {
    char *fruits[] = {"Apple", "Banana", "Cherry"};
    int size = sizeof(fruits) / sizeof(fruits[0]);
    printStrings(fruits, size);
    return 0;
}
🔹 Output:
Apple
Banana
Cherry
📌 ptr[i] gives the entire string, while ptr[i][j] gives individual characters.
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Modifying Strings Using char**
A double pointer allows modifying the original string pointers.
#include <iostream>
using namespace std;

void modifyStrings(char **ptr) {
    ptr[0] = "Modified";  // Changing first string
}
int main() {
    char *words[] = {"Hello", "World", "C++"};

    modifyStrings(words);

    // Print modified array
    cout << "After modification: " << words[0] << endl;

    return 0;
}
🔹 Output:
After modification: Modified
📌 Double pointers allow modifying pointer assignments inside functions.
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
Command-Line Arguments (char** argv)
When using int main(int argc, char **argv), argv is a double pointer holding command-line arguments.
#include <iostream>
using namespace std;
int main(int argc, char **argv) {
    cout << "Number of arguments: " << argc << endl;
    for (int i = 0; i < argc; i++) {
        cout << "Argument " << i << ": " << argv[i] << endl;
    }
    return 0;
}
Run command:   ./a.out Hello World
🔹 Output:
Number of arguments: 3
Argument 0: ./a.out
Argument 1: Hello
Argument 2: World
📌 argv stores arguments as an array of strings (char*), making it a char**.
////////////////////////////////////////////////////////////////////////////////////////////////////////////////

🔹 Summary Table
Concept                                           Explanation
char* (Single Pointer)	                          Stores the address of a single string
char** (Double Pointer)	                          Stores the address of multiple strings (array of strings)
Traversing char**	                              Use ptr[i] to get the string and ptr[i][j] for characters
Dynamic Memory Allocation	                      char** can store strings dynamically using new
Modify Strings in Function	                      char** allows modifying an array of strings in a function
Command-Line Arguments	                          char** argv stores arguments passed to main()
