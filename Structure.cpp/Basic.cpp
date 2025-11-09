🔹1. Structure in C - user-defined data type
A structure (struct) is a user-defined data that allows storing different types of data, at different memory locations.
✅ Syntax of Structure
struct StructName {
    dataType member1;
    dataType member2;
    ...
};
Example:
struct Student {
    char name[50];
    int age;
    float marks;
};
✅ What happens here:
The compiler creates a new user-defined data type named struct Student.
It only defines the blueprint or layout of memory (like a class definition in C++).
No memory is allocated at this point.
📘 Think of it like this:
“I’ve told the compiler what a Student looks like, but I haven’t created one yet.”


🔹 Why Use Structures?
    Helps organize and manage related data efficiently.
    Supports multiple data types within one unit.
    Allows passing complex data to functions.
    Helps in memory-efficient and modular programming.
✅ Example: 
#include <stdio.h>
#include <string.h>
// Define a structure
struct Student {
    char name[50];
    int age;
    float marks;
};
int main() {
    // Declare and initialize structure : Memory allocated in stack
    struct Student s1;//    A variable s1 of type struct Student is created inside main().
    strcpy(s1.name, "Kapil");  // Assign values
    s1.age = 22;
    s1.marks = 90.5;

    // Display values
    printf("Name: %s\n", s1.name);
    printf("Age: %d\n", s1.age);
    printf("Marks: %.2f\n", s1.marks);

    return 0;
}
✅ Output:
Name: Kapil
Age: 22
Marks: 90.50
📌 Key Features of Structure
   Each member has a unique memory location.
   Size of structure = sum of all member sizes (may include padding).
   Can hold multiple values at the same time.


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Student {
    char name[50];
    int age;
    float marks;
};
int main() {
    struct Student *ptr = malloc(sizeof(struct Student));

    strcpy(ptr->name, "Kapil");
    ptr->age = 22;
    ptr->marks = 90.5;

    printf("Name: %s\n", ptr->name);
    printf("Age: %d\n", ptr->age);
    printf("Marks: %.2f\n", ptr->marks);

    free(ptr); // manually release heap memory
    return 0;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////

✅#Copy Structure

Copying structure is simple as copying any other variables. 
#include <stdio.h>
#include <stdlib.h>
struct Student {
    int id;
    char grade;
};
int main() {
    struct Student s1 = {1, 'A'};
    struct Student s1c = s1; // Create a copy of student s1
    printf("Student 1 ID: %d\n", s1c.id);
    printf("Student 1 Grade: %c", s1c.grade);
    return 0;
}
Output:
Student 1 ID: 1
Student 1 Grade: A
////////////////////////////////////////////////////////////////////////////////////////////////////////////

✅#Nested STRUCTURE-
In C, a nested structure refers to a structure that contains another structure as one of its members.
#include <stdio.h>
struct child {  // Child structure declaration
    int x;
    char c;
};
struct parent {  // Parent structure declaration
    int a;
    struct child b;
};
int main() {
    struct parent p = { 25, 195, 'A' };  // Accessing and printing nested members
    printf("p.a = %d\n", p.a);
    printf("p.b.x = %d\n", p.b.x);
    printf("p.b.c = %c", p.b.c);
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////

✅Array of Structures

When you need to store details of multiple entities (like multiple students or multiple employees), you can use an array of structures.
#include <stdio.h>
#include <string.h>

struct Student {
    char name[50];
    int age;
    float marks;
};
int main() {
    struct Student students[3];  // Array of 3 students

    // Assign values
    strcpy(students[0].name, "Kapil");
    students[0].age = 22;
    students[0].marks = 89.5;

    strcpy(students[1].name, "Riya");
    students[1].age = 21;
    students[1].marks = 92.0;

    strcpy(students[2].name, "Aman");
    students[2].age = 23;
    students[2].marks = 85.5;

    // Display all students
    for (int i = 0; i < 3; i++) {
        printf("Student %d:\n", i + 1);
        printf(" Name: %s\n", students[i].name);
        printf(" Age: %d\n", students[i].age);
        printf(" Marks: %.2f\n\n", students[i].marks);
    }

    return 0;
}
output:
Student 1:
 Name: Kapil
 Age: 22
 Marks: 89.50

Student 2:
 Name: Riya
 Age: 21
 Marks: 92.00

Student 3:
 Name: Aman
 Age: 23
 Marks: 85.50

✅ Advantages:
Easier to manage and scale (add/remove students).
Works well with loops, functions, and file handling.
Cleaner and less repetitive.
Ideal when you have many students or when the number may change.

❌ (2) Multiple Separate Structure Variables
struct Student {
    char name[50];
    int age;
    float marks;
};

int main() {
    struct Student s1, s2, s3;

    strcpy(s1.name, "Kapil");
    s1.age = 22;
    s1.marks = 89.5;

    strcpy(s2.name, "Riya");
    s2.age = 21;
    s2.marks = 92.0;

    strcpy(s3.name, "Aman");
    s3.age = 23;
    s3.marks = 85.5;

    // Display (manual for each)
    printf("%s %d %.2f\n", s1.name, s1.age, s1.marks);
    printf("%s %d %.2f\n", s2.name, s2.age, s2.marks);
    printf("%s %d %.2f\n", s3.name, s3.age, s3.marks);
}
⚠️ Disadvantages:
Not scalable — you must manually handle each variable.
Hard to use in loops or functions.
Tedious if you have many students.
More memory management effort if number changes dynamically.

🏁 Conclusion
| Approach                    | Best When                                             | Advantages                     | Disadvantages                               |
| --------------------------- | ----------------------------------------------------- | ------------------------------ | ------------------------------------------- |
| **Array of Structures**     | You have multiple records (students, employees, etc.) | Scalable, loop-friendly, clean | Need to know or allocate number of students |
| **Separate Struct Objects** | Only 1–2 fixed students                               | Simple for very small data     | Not scalable, repetitive code               |





