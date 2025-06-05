
✅Opening Files:
1. Basic File Opening with Default Modes
Each file stream class (ifstream, ofstream, fstream) opens files in a default mode:

ifstream: Opens the file in ios::in mode (read-only).
ofstream: Opens the file in ios::out mode (write-only and truncates the file if it exists).
fstream: No default mode—must explicitly specify one such as ios::in, ios::out, or both.

#include <fstream>
#include <iostream>
using namespace std;
int main() {
    // Open a file for reading (default for ifstream)
    ifstream inputFile("example.txt");
    //std::ifstream: This is used to create an object(inputFile) file that allows reading from a file.

    // Open a file for writing (default for ofstream)
    ofstream outputFile("output.txt");
    //std::ofstream: This is used to create an object(outputFile) file that allows writing to a file.

    // Open a file for both reading and writing (you need to specify modes for fstream)
    fstream file("file.txt", ios::in | ios::out);
}

//---------------------------------------------------------------------------------------------------------------

✅2.Custom File Modes

1. Open File for Writing (Create or Overwrite): ios::out
Behavior of std::ios::out
When std::ios::out is used without any additional flags (like ios::app), the file will be opened in "overwrite mode."

Existing File: If the file already exists, any existing content will be erased (truncated), and writing will start from the beginning of the file.
Non-Existing File: If the file does not exist, it will be created.
// Opens a file for writing.
// If the file already exists, it overwrites the content.
// If the file doesn’t exist, it creates a new file.

#include <fstream>
#include <iostream>
int main() {
    // Create and write to the file for the first time
    {
        std::ofstream file("example.txt", std::ios::out);  // Default is ios::out
        file << "Hello, World!";
    }  // 'file' is closed automatically here
    //the file object is destroyed after the scope ends  and the file is closed automatically.

    // Overwrite the file
    {
        std::ofstream file("example.txt", std::ios::out);  // Truncates the file
        file << "Overwritten content!";
    }
    //the file object is destroyed after the scope ends  and the file is closed automatically.

    return 0;
}
Output:
After Execution:
Step 1: First writing creates a file example.txt with the content:
Hello, World!

Step 2: The second writing completely overwrites the content:
Overwritten content!

//----------------------------------------------------------------------------------------------------------------

✅2. Open File for Reading: ios::in
If the file exists or can be opened, the stream becomes ready, and you can read from it.
If the file does not exist or cannot be opened, the file stream (file) will be in a fail state (checked with file.fail() or file.is_open()).
// Opens a file for reading.
// File must exist; otherwise the open operation fails.

#include <iostream>
#include <fstream>
using namespace std;
int main() {
    ifstream file("example.txt", ios::in);  // when using std::ifstream, by default File opened in read mode, so explicitly specifying std::ios::in is optional.

    if (!file.is_open()) {
        cout << "Error: File not found!" << endl;
        return 1;
    }
    string line;
    while (getline(file, line)) {
        cout << line << endl;  // Print line by line
    }
    file.close();
    return 0;
}
/*  
getline(file, line)
getline() reads characters from the specified input stream (input_stream) until:
1.It stops when a newline (\n) or the end of the file (EOF) is encountered.
3.It then stores the read characters (excluding the newline \n) into the line variable.
The function stops reading at the newline character (or EOF) but does not store the newline in the result.

The while condition works because std::getline() returns true if it successfully reads a line, and false if it encounters EOF or an error.

*/
✅3. Open File for Appending: ios::app
Opens a file for writing at the end of the file.
Preserves existing content and adds new data at the end.
If the file doesn’t exist, it creates a new file.

#include <iostream>
#include <fstream>
using namespace std;
int main() {
    ofstream file("example.txt", ios::app);  // File opened in append mode
    if (!file.is_open()) {
        cout << "Error opening file!" << endl;
        return 1;
    }
    file << "This is an appended line.\n";
    cout << "File opened in append mode (content preserved).\n";
    file.close();
    return 0;
}
//---------------------------------------------------------------------------------------------------------------

✅ ios::ate  (meaning: At The End)
When you open a file with the ios::ate mode in C++, it opens the file and moves the file pointer to the end of the file, allowing you to append more data after the existing content.
#include <iostream>
#include <fstream>
#include <string>

int main() {
    // File name
    std::string fileName = "example.txt";

    // Open the file in output mode with `ios::ate`
    std::ofstream outFile(fileName, std::ios::out | std::ios::ate);

    // Check if the file is open
    if (!outFile.is_open()) {
        std::cerr << "Failed to open file: " << fileName << std::endl;
        return 1; // Error
    }

    // Write to the file (append since the pointer is at the end due to `ios::ate`)
    outFile << "Adding new data to the end of the file.\n";

    // Close the file
    outFile.close();

    std::cout << "Data successfully added to the file." << std::endl;
    return 0;
}

✅Key Differences Between ios::ate and ios::app
ios::ate/ios::app
ios::ate Opens the file and immediately moves the read/write pointer to the end of the file, but writing can occur anywhere (e.g., overwrite or random write).
ios::app Opens the file and forces all write operations to occur only at the end of the file; you cannot overwrite existing content.

ios::ate allows repositioning the write pointer anywhere in the file using seekp.	
ios::app ignores pointer repositioning and always appends to the file's end.

ios::ate Can be used for both reading and writing when combined with modes like ios::in or ios::out.	
ios::app Typically used for writing only when opening the file.

//-----------------------------------------------------------------------------------------------------------------

✅Open File for Truncating: ios::trunc

Used to truncate(delete) the contents of a file upon opening.
This means that if the file already exists, its contents are erased and the file starts with a size of zero. 
If the file does not exist, it is created—but without any contents.

The ios::trunc mode is implied by default when opening a file for writing with std::ofstream. 
That is:
std::ofstream file("filename.txt");
This statement already truncates the file by default, even if you don’t explicitly specify ios::trunc.

#include <iostream>
#include <fstream>  // For file handling
using namespace std;
int main() {
    string filename = "example.txt";  // Name of the file to truncate

    // Open the file in truncation mode
    ofstream file(filename, ios::out | ios::trunc);  // Combine out and trunc
    if (!file.is_open()) {
        cout << "Error: Could not open the file \"" << filename << "\" for truncation!" << endl;
        return 1;  // Exit if the file could not be opened
    }

    // Write new content after truncating the file
    file << "This file has been truncated.\n";
    file << "New content begins here.\n";

    // Close the file stream after writing
    file.close();
    cout << "New content has been written and the file is closed." << endl;
}
//===============================================================================================================

✅seekp and seekg:
✅1. file.seekg(pos, dir):
This is used to move the input (read) pointer, which determines where the next read operation will take place. 

The arguments specify:
pos: Offset from a reference point.
dir: Reference point for seeking (ios::beg, ios::cur, or ios::end):

ios::beg: Start of the file.
ios::cur: Current position of the file pointer.
ios::end: End of the file.
Example: file.seekg(0, ios::beg):
Moves the read pointer to the beginning of the file.

Example: file.seekg(1, ios::beg):
Move the read pointer to position 1 (second byte or 1st character) from the start (beginning) of the file.



✅2. file.seekp(pos, dir):
This is used to move the output (write) pointer, which determines where the next write operation will take place. 
Its arguments work the same way as seekg.
Example: file.seekp(0, ios::end):
Moves the write pointer to the end of the file, allowing you to append data.

Time Complexity:
O(1):The pointer directly moves to the desired location based on the offset and reference point.

#include <iostream>
#include <fstream>
using namespace std;
int main() {
    string filename = "example.txt";
    ofstream outFile(filename, ios::out | ios::trunc);  // Truncate and open the file for writing
    outFile << "Hello, world!" << endl;
    outFile << "This is a test file." << endl;
    outFile << "C++ file operations are powerful!" << endl;
    outFile.close();  // Close the file after writing


    fstream file(filename, ios::in | ios::out);  // Open the file for both input and output
    if (!file.is_open()) {
        cout << "Error: Could not open the file!" << endl;
        return 1;
    }

    file.seekg(0, ios::beg);  // Move read pointer to the beginning of the file
    cout << "Reading file content from the beginning:" << endl;
    string line;
    while (getline(file, line)) {
        cout << line << endl;
    }
    cout << endl;


    file.seekp(0, ios::end);  // Move write pointer to the end of the file
    file << "Appending a new line using seekp." << endl;  // Write new data at the end
    file.close();

    // Verify new content
    cout << "Updated file content:" << endl;

    // Reopen file for reading to display updated content
    ifstream inFile(filename, ios::in);
    while (getline(inFile, line)) {
        cout << line << endl;
    }
    inFile.close();

    return 0;
}

✅Difference Between tellg and tellp in C++:
Both tellg and tellp are functions used to retrieve the current position of a file pointer in bytes when working with file streams in C++. 

✅tellg (Get Position of the "Get" Pointer)
Meaning:
tellg stands for "tell get".
It returns the current position of the read pointer in bytes within the file.
Pointer Name:	Get pointer.

Use Case:
You can use tellg to know where the next read operation will occur when reading a file.
Syntax:
stream.tellg();
Returns the position (offset from the beginning of the file) of the get pointer as a std::streampos object.


✅tellp (Get Position of the "Put" Pointer)
Meaning:
tellp stands for "tell put".
It returns the current position of the write pointer in bytes within the file.
Pointer Name:	Put pointer.

Use Case:
You can use tellp to know where the next write operation will occur when writing to a file.

Syntax:
stream.tellp();
Returns the position (offset from the beginning of the file) of the put pointer as a std::streampos object.

#include <iostream>
#include <fstream>  // For file handling
using namespace std;
int main() {
    // Open the file for both reading and writing
    fstream file("example.txt", ios::in | ios::out | ios::trunc); // Open in read/write mode, truncate existing content.
    if (!file.is_open()) {
        cout << "Error: Could not open the file!" << endl;
        return 1;
    }

    // Writing content to the file
    cout << "Writing to the file..." << endl;
    file << "Hello, world!";
    cout << "Write pointer after writing 'Hello, world!': " << file.tellp() << endl; // 13

    file.seekg(0, ios::beg);  // Move read pointer to the start
    cout << "Read pointer after seekg(0, ios::beg): " << file.tellg() << endl;      // 0


    cout << "Reading the content from the file..." << endl;
    char ch;
    while (file.get(ch)) { // Read one character at a time
        cout << ch;
        cout << " (Read pointer at: " << file.tellg() << ")" << endl;
        // Output during loop:
        /*
        H (Read pointer at: 1)
        e (Read pointer at: 2)
        l (Read pointer at: 3)
        l (Read pointer at: 4)
        o (Read pointer at: 5)
        , (Read pointer at: 6)
        (Read pointer at: 7)
        w (Read pointer at: 8)
        o (Read pointer at: 9)
        r (Read pointer at: 10)
        l (Read pointer at: 11)
        d (Read pointer at: 12)
        ! (Read pointer at: 13)
        */
    }

    // Move the write pointer to the end of the file
    file.seekp(0, ios::end);  // Move write pointer to the end
    cout << "Write pointer after seekp(0, ios::end): " << file.tellp() << endl; // 13

    // Appending new content to the file
    file << " Appending this text.";
    cout << "Write pointer after appending: " << file.tellp() << endl; //   33


    // Move read pointer back to the start to read the updated content
    file.seekg(0, ios::beg);
    cout << "Read pointer reset to beginning: " << file.tellg() << endl;  //  0


    cout << "Updated file content:" << endl;
    string line;
    while (getline(file, line)) {   // Hello, world! Appending this text.
        cout << line << endl;
    }
    file.close();
    return 0;
}

//=====================================================================================================================================

4. Open File for Reading and Writing: ios::in | ios::out
Opens a file for both reading and writing.
File must exist; otherwise the operation fails.
You can both read from and write to the file by seeking the respective positions.

#include <iostream>
#include <fstream>
using namespace std;
int main() {
    fstream file("example.txt", ios::in | ios::out);  // Open file for reading & writing

    if (!file.is_open()) {
        cout << "Error opening file. File might not exist!" << endl;
        return 1;
    }
    string content;
    file.seekg(0, ios::beg);  // Move read pointer to beginning
    while (getline(file, content)) {
        cout << content << endl;  // Read and print content
    }
    file.clear();  // Clear eof flag to perform write operations
    file.seekp(0, ios::end);  // Move write pointer to end
    file << "Adding more content to this file.\n";

    file.close();
    return 0;
}
//----------------------------------------------------------------------------------------------------------------

6. Open File in Binary Mode: ios::binary
Opens a file in binary mode.
Useful for reading or writing raw data like images, videos, or binary file formats (rather than text).
Writing in Binary Mode:
#include <iostream>
#include <fstream>
using namespace std;

int main() {
    ofstream file("binary_file.dat", ios::out | ios::binary);  // File opened in binary mode

    if (!file.is_open()) {
        cout << "Error opening file for binary write!" << endl;
        return 1;
    }
    int data[] = {10, 20, 30};
    file.write((char*)data, sizeof(data));  // Write raw binary data
    file.close();

    cout << "Binary data written to file.\n";
    return 0;
}

Reading in Binary Mode:
#include <iostream>
#include <fstream>
using namespace std;
int main() {
    ifstream file("binary_file.dat", ios::in | ios::binary);  // File opened for binary read

    if (!file.is_open()) {
        cout << "Error opening binary file for read!" << endl;
        return 1;
    }
    int data[3];
    file.read((char*)data, sizeof(data));  // Read raw binary data
    for (int i = 0; i < 3; ++i) {
        cout << data[i] << " ";  // Output: 10 20 30
    }
    cout << endl;

    file.close();
    return 0;
}
//-----------------------------------------------------------------------------------------------------------------