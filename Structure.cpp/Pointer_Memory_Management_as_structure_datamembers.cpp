Structure with a Pointer Member - 
When a structure has a pointer member, memory allocation must be done explicitly using malloc() or calloc().

Example: Allocating Memory for a Structure with a Pointer
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct Student {
    char *name;  // Pointer for dynamic memory allocation
    int age;
};
int main() {
    struct Student s1;
    s1.name = (char *)malloc(50 * sizeof(char)); // Allocate memory for the name pointer
    if (s1.name == NULL) {
        printf("Memory allocation failed\n");
        return 1;
    }
    strcpy(s1.name, "Kapil"); // Assign values
    s1.age = 22;
    printf("Name: %s, Age: %d\n", s1.name, s1.age);

    free(s1.name); // Free allocated memory
    return 0;
}
✅ Output:
Name: Kapil, Age: 22
📌 Key Points:
s1.name is dynamically allocated using malloc().
free(s1.name) is called to avoid memory leaks.
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
🔹 2. Structure Array with Pointer Members - 
When dealing with multiple objects, memory must be allocated for each pointer member separately.
Example: Allocating Memory for an Array of Structures
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct Student {
    char *name;
    int age;
};
int main() {
    int n;
    printf("Enter number of students: ");
    scanf("%d", &n);
    // Allocate memory for an array of structures
    struct Student *students = (struct Student *)malloc(n * sizeof(struct Student));
    if (students == NULL) {
        printf("Memory allocation failed\n");
        return 1;
    }
    // Allocate memory for each student's name and input data
    for (int i = 0; i < n; i++) {
        students[i].name = (char *)malloc(50 * sizeof(char));
        if (students[i].name == NULL) {
            printf("Memory allocation failed\n");
            return 1;
        }
        printf("Enter name and age of student %d: ", i + 1);
        scanf("%s %d", students[i].name, &students[i].age);
    }
    printf("\nStudent Details:\n"); // Print student details
    for (int i = 0; i < n; i++) {
        printf("Name: %s, Age: %d\n", students[i].name, students[i].age);
    }

    for (int i = 0; i < n; i++) {
        free(students[i].name);    // Free allocated memory
    }
    free(students);
    return 0;
}
✅ Sample Output:

Enter number of students: 2
Enter name and age of student 1: Kapil 22
Enter name and age of student 2: Aman 21

Student Details:
Name: Kapil, Age: 22
Name: Aman, Age: 21
📌 Key Points:

Allocates array of structures dynamically.
Each pointer member (name) requires separate memory allocation.
Memory deallocated using free().
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

🔹 3. Nested Structures with Dynamic Memory
   A nested structure is a structure containing another structure as a pointer member.

Example: Nested Structure with Dynamic Allocation
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct Address {
    char *city;
    int pincode;
};
struct Student {
    char *name;
    int age;
    struct Address *addr;  // Pointer to another structure
};

int main() {
    struct Student s1;
    s1.name = (char *)malloc(50 * sizeof(char)); // Allocate memory for name 
    s1.addr = (struct Address *)malloc(sizeof(struct Address)); // Allocate memory for address
    s1.addr->city = (char *)malloc(50 * sizeof(char));

    if (s1.name == NULL || s1.addr == NULL || s1.addr->city == NULL) {
        printf("Memory allocation failed\n");
        return 1;
    }
    strcpy(s1.name, "Kapil"); // Assign values
    s1.age = 22;
    strcpy(s1.addr->city, "Delhi");
    s1.addr->pincode = 110001;

    printf("Name: %s, Age: %d, City: %s, Pincode: %d\n",
           s1.name, s1.age, s1.addr->city, s1.addr->pincode);

    free(s1.name);
    free(s1.addr->city);
    free(s1.addr);
    return 0;
}
✅ Output:
Name: Kapil, Age: 22, City: Delhi, Pincode: 110001
📌 Key Points:

Both structures (Student and Address) require dynamic allocation.
Nested pointers (s1.addr->city) also need malloc().
All dynamically allocated memory must be freed properly.
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
4. Structure with Pointer to Another Structure
A structure can contain a pointer to another structure for linked lists, trees, graphs, etc.

Example: Creating a Linked List
#include <stdio.h>
#include <stdlib.h>
struct Node {
    int data;
    struct Node *next;  // Pointer to the next node
};

int main() {
    struct Node *head = NULL, *second = NULL, *third = NULL;

    // Allocate memory for nodes
    head = (struct Node *)malloc(sizeof(struct Node));
    second = (struct Node *)malloc(sizeof(struct Node));
    third = (struct Node *)malloc(sizeof(struct Node));

    if (head == NULL || second == NULL || third == NULL) {
        printf("Memory allocation failed\n");
        return 1;
    }

    // Assign data and link nodes
    head->data = 10;
    head->next = second;

    second->data = 20;
    second->next = third;

    third->data = 30;
    third->next = NULL;

    // Print the linked list
    struct Node *temp = head;
    while (temp != NULL) {
        printf("%d -> ", temp->data);
        temp = temp->next;
    }
    printf("NULL\n");
    free(head);
    free(second);
    free(third);
    return 0;
}
✅ Output:
10 -> 20 -> 30 -> NULL

