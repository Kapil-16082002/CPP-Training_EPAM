🔹1. Structure in C -
A structure (struct) is a collection of variables (of different types) stored at different memory locations.
✅ Syntax of Structure
struct StructName {
    dataType member1;
    dataType member2;
    ...
};
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
    struct Student s1; // Declare and initialize structure
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
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
#Copy Structure

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

#Nested STRUCTURE-
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



