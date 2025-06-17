
🧠Composite Design Pattern:

The Composite Design Pattern is a structural design pattern that allow you treat a group of objects in the same way as a single object. 
It allows you to represent tree-like structures where individual objects and groups of objects are treated uniformly.
The Composite Pattern is particularly useful when working with hierarchical structures such as file systems, GUI frameworks, or menus.


✅Example Scenario: File System
Let’s create a FileSystem where:
1.Files are individual objects (leaves).
2.Directories (which can contain files and/or other directories) form the structure (composite).
The Composite Pattern ensures that both files and directories are treated uniformly via a common FileSystemComponent interface.



+-----------------+
| FileSystemComponent |
| (Abstract Component)|
+-----------------+
        ▲
+-------------------+---------------------+
|                                         |
+---------------+                       +-----------------+
|     File      |                       |    Directory    |
| (Leaf)        |                       | (Composite)     |
+---------------+                       +-----------------+
*                                      *
| addChild()                           | addChild(FileSystemComponent*)
| removeChild() // Do Nothing          | removeChild(FileSystemComponent*)
| showDetails()                        | showDetails()
                           /       \
                          /         \
            +----------------+   +-----------------+
            system ) )) output 
)
### where real formatate tools copying**.

#include <iostream>
#include <vector>
#include <string>
using namespace std;

// ============================================================
// *** Component: FileSystemComponent ***
// ============================================================
// This is the **base interface (Component)** for both `File` (Leaf) and `Directory` (Composite). 
//It declares operations that will either be implemented directly by the leaf or recursively handled by the composite.
// The `showDetails` method prints details of files and directories.
// Optionally, `add` and `remove` methods for managing children are defined but provide default (empty) behavior in the base class.
class FileSystemComponent {
public:
    virtual void showDetails() const = 0; // Prints the component details
    virtual void add(FileSystemComponent* component) {}        // Default: No operation
    virtual void remove(FileSystemComponent* component) {}     // Default: No operation
    virtual ~FileSystemComponent() {}                          // Virtual destructor
};
// ============================================================
// *** Leaf: File ***
// ============================================================
// The `File` class is the **Leaf** in the Composite Pattern. It
// represents individual (end-point) objects within the tree structure.
// Since files do not have any children, the `add` and `remove` methods are unused.
//
// The `showDetails` method prints the name of the file.
class File : public FileSystemComponent {
private:
    string name; // Name of the file
public:
    File(const string& fileName) : name(fileName) {}  // Constructor to initialize the file name
    void showDetails() const override {
        cout << "File: " << name << endl; // Basic output: Just the file name
    }
};
// ============================================================
// *** Composite: Directory ***
// ============================================================
// The `Directory` class is the **Composite** in the Composite Pattern.
// It can **contain child components**, which can be either `File` (leaves)
// or other `Directory` objects (composites).
//
// It manages these child components through a vector. The `add` and
// `remove` methods allow modification of the child components, while
// `showDetails` recursively prints all children.
//
// The destructor ensures proper cleanup of all child components.
class Directory : public FileSystemComponent {
private:
    string name;                              // Name of the directory
    vector<FileSystemComponent*> components; // List of child components (files/directories)
public:
    // Constructor to initialize the directory name
    Directory(const string& dirName) : name(dirName) {}
    // Adds a child component (either a File or another Directory)
    void add(FileSystemComponent* component) override {
        components.push_back(component);
    }
    // Removes a child component from the directory
    void remove(FileSystemComponent* component) override {
        components.erase(
            remove(components.begin(), components.end(), component),
            components.end()
        );
    }
    // Prints the directory name and recursively calls `showDetails`
    // on all child components
    void showDetails() const override {
        cout << "Directory: " << name << endl;

        // Iterate over all children and call their showDetails method
        for (const auto& component : components) {
            component->showDetails();
        }
    }
    // Destructor: Cleans up all child components
    ~Directory() {
        for (auto& component : components) {
            delete component; // Safely delete each child component
        }
    }
};
// ============================================================
// *** Client Code ***
// ============================================================
// The client interactively uses the `FileSystemComponent` interface
// to work with both `File` and `Directory` objects. This ensures that
// the client does not need to differentiate between leaf and composite nodes.
//
// Operations:
// 1. Files and directories are dynamically created.
// 2. A hierarchical file system is built (directories within directories).
// 3. The entire structure is displayed using `showDetails`.
//
// After use, the memory for the entire structure is freed automatically.
int main() {
    // Create individual files (Leaves)
    FileSystemComponent* file1 = new File("file1.txt");
    FileSystemComponent* file2 = new File("file2.txt");
    FileSystemComponent* file3 = new File("file3.txt");
    FileSystemComponent* file4 = new File("file4.txt");

    // Create directories (Composites)
    Directory* dir1 = new Directory("Documents");
    Directory* dir2 = new Directory("Downloads");
    Directory* dir3 = new Directory("Photos");

    // Build the tree structure
    dir1->add(file1);              // Add files to Documents
    dir1->add(file2);
    dir2->add(file3);              // Add file to Downloads
    dir2->add(dir1);               // Add Documents as a subdirectory of Downloads
    dir3->add(file4);              // Add file to Photos

    // Top-level structure: Downloads and Photos
    Directory* root = new Directory("Root");
    root->add(dir2);               // Add Downloads to Root
    root->add(dir3);               // Add Photos to Root

    // Display the full file system structure
    cout << "File System Structure:\n";
    root->showDetails();

    // Clean up the entire file system tree
    delete root;

    return 0;
}