✅File Programming in C++
File programming in C++ refers to the ability to perform operations on files—such as creating, reading, writing, appending, modifying, and deleting files—using the C++ file I/O (Input/Output) library. 
Files are used to store data permanently, unlike variables that lose their values when a program ends.

✅File streams:
File Streams are used to read data from files or write data to files. 
They are part of the <fstream> header and are provided by the C++ Standard Library. 
Essentially, File Streams in C++ allow you to perform file I/O (Input/Output) operations efficiently, and they work similarly to standard I/O streams like cin and cout.

File Stream Classes:
ifstream (Input Stream for File): Used for reading data from files (input file stream).
ofstream (Output Stream for File): Used for writing data to files (output file stream).
fstream (File Stream):  A more general class that supports both reading from and writing to files (input/output file stream).

✅1. ifstream (Input File Stream)
This class allows you to read data from a file.
#include <iostream>
#include <fstream>
using namespace std;

int main() {
    ifstream inputFile("example.txt"); // Open the file for reading
    string line;

    if (inputFile.is_open()) { // Check if the file was successfully opened
        while (getline(inputFile, line)) { // Read line-by-line from the file
            cout << line << endl; // Print the content to the console
        }
        inputFile.close(); // Close the file after reading
    } 
    else {
        cout << "Failed to open the file!" << endl;
    }
    return 0;
}

✅2. ofstream (Output File Stream)
This class allows you to write data to a file.

#include <iostream>
#include <fstream>
using namespace std;
int main() {
    ofstream outputFile("example.txt"); // Open the file for writing

    if (outputFile.is_open()) { // Check if the file was successfully opened
        outputFile << "Hello, File Streams!\n";
        outputFile << "C++ makes it easy to handle files.\n";
        outputFile.close(); // Close the file after writing
        cout << "Data written to file successfully!" << endl;
    } 
    else {
        cout << "Failed to open the file!" << endl;
    }
    return 0;
}

✅3. fstream (General File Stream)
This class allows you to perform both read and write operations on the same file.

#include <iostream>
#include <fstream>
using namespace std;

int main() {
    //ofstream outFile("example.txt"); 
    fstream file("example.txt", ios::in | ios::out | ios::app); // Open in read/write/append mode

    if (file.is_open()) {
        // Append to the file
        file << "Appending this line to the file.\n";

        // Move the read pointer to the beginning of the file
        file.seekg(0, ios::beg);
        string line;

        // Read and display the file contents
        cout << "Reading from file:" << endl;
        while (getline(file, line)) {
            cout << line << endl;
        }
        file.close(); // Close the file
    } else {
        cout << "Failed to open the file!" << endl;
    }

    return 0;
}

Types of File Operations in C++:
Opening a file (open()).
Closing a file (close()).
Reading data from a file (>>, .getline(), .read()).
Writing data to a file (<<, .write()).
Checking state of file stream (e.g., fail(), eof()).


✅File Opening Modes (ios Flags)
When working with files, you need to specify the mode of operation using flags:

ios::in: Open file for reading.
ios::out: Open file for writing (creates file if it doesn’t exist).
ios::app: Append data at the end of a file.
ios::binary: Open the file in binary mode.
ios::trunc: Truncate (delete) the file content if it exists.
ios::ate: Open the file and move the file pointer to the end.
You can combine multiple modes using the bitwise OR operator (|), e.g., ios::in | ios::out.

//==================================================================================================================

✅Opening Files
Files can be opened/existing in two ways:

1. During declaration (Constructor).
2. Using the .open() function. Files must be closed after use to release resources, which is done manually using the .close() function.









