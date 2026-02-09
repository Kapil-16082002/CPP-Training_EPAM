
// Linked list implementation in C++

#include <bits/stdc++.h>
#include <iostream>
using namespace std;

// Creating a node
class Node {
public:
  int value;
  Node* next;
};
int main() {
  Node* head;
  Node* one = NULL;
  one = new Node();

  Node* two = NULL;
  two = new Node();

  Node* three = NULL;
  three = new Node();


  // Assign value values
  one->value = 1;
  two->value = 2;
  three->value = 3;

  // Connect nodes
  one->next = two;
  two->next = three;
  three->next = NULL;

  // print the linked list value
  head = one;
  while (head != NULL) {
    cout << head->value;
    head = head->next;
  }
}
//=================================================================================================================

// Singly linked list Implementation

#include <iostream>
using namespace std;

class Node {
public:
    int data;
    Node* next;
    Node(int val) : data(val), next(nullptr) {}
};

class SinglyLinkedList {
private:
    Node* head;
public:
    // Constructor
    SinglyLinkedList() : head(nullptr) {}

    // ---------- INSERT AT END ----------
    void insertAtEnd(int val) {
        Node* newNode = new Node(val);

        if (!head) {
            head = newNode;
            return;
        }
        Node* temp = head;
        while (temp->next) {
            temp = temp->next;
        }
        temp->next = newNode;
    }
    // ---------- INSERT AT FRONT ----------
    void insertAtFront(int val) {
        Node* newNode = new Node(val);
        newNode->next = head;
        head = newNode;
    }

    // ---------- DELETE BY VALUE ----------
    void deleteValue(int val) {
        if (!head) return;

        // If head needs to be deleted
        if (head->data == val) {
            Node* temp = head;
            head = head->next;
            delete temp;
            return;
        }
        Node* curr = head;
        while (curr->next) {
            if (curr->next->data == val) {
                Node* toDelete = curr->next;
                curr->next = toDelete->next;
                delete toDelete;
                return;
            }
            curr = curr->next;
        }
    }
    // ---------- DISPLAY ----------
    void display() const {
        Node* temp = head;
        while (temp) {
            cout << temp->data << " ";
            temp = temp->next;
        }
        cout << endl;
    }
    // ---------- DESTRUCTOR ----------
    ~SinglyLinkedList() {
        while (head) {
            Node* next = head->next;
            delete head;
            head = next;
        }
    }
};
int main() {
    SinglyLinkedList list;

    list.insertAtEnd(10);
    list.insertAtEnd(20);
    list.insertAtFront(5);

    list.display();   // 5 10 20

    list.deleteValue(10);
    list.display();   // 5 20

    return 0;
}

//===============================================================================================================


// malloc singly linked list implementation
#include <iostream>
#include <cstdlib>
using namespace std;

class Node {
public:
    int data;
    Node* next;
};

class SinglyLinkedList {
private:
    Node* head;

public:
    SinglyLinkedList() : head(nullptr) {}

    Node* createNode(int val) {
        Node* newNode = (Node*)malloc(sizeof(Node));
        if (!newNode) {
            cout << "Memory allocation failed\n";
            return nullptr;
        }
        newNode->data = val;
        newNode->next = nullptr;
        return newNode;
    }

    void insertAtEnd(int val) {
        Node* newNode = createNode(val);
        if (!newNode) return;

        if (!head) {
            head = newNode;
            return;
        }

        Node* temp = head;
        while (temp->next) {
            temp = temp->next;
        }
        temp->next = newNode;
    }

    void insertAtFront(int val) {
        Node* newNode = createNode(val);
        if (!newNode) return;

        newNode->next = head;
        head = newNode;
    }

    void deleteValue(int val) {
        if (!head) return;

        if (head->data == val) {
            Node* temp = head;
            head = head->next;
            free(temp);
            return;
        }

        Node* curr = head;
        while (curr->next) {
            if (curr->next->data == val) {
                Node* toDelete = curr->next;
                curr->next = toDelete->next;
                free(toDelete);
                return;
            }
            curr = curr->next;
        }
    }

    void display() const {
        Node* temp = head;
        while (temp) {
            cout << temp->data << " ";
            temp = temp->next;
        }
        cout << endl;
    }

    ~SinglyLinkedList() {
        while (head) {
            Node* next = head->next;
            free(head);
            head = next;
        }
    }
};
int main() {
    SinglyLinkedList list;

    list.insertAtEnd(10);
    list.insertAtEnd(20);
    list.insertAtFront(5);

    list.display();   // 5 10 20

    list.deleteValue(10);
    list.display();   // 5 20

    return 0;
}

//================================================================================================================


// Doubly linked list Implementation:
#include <iostream>
using namespace std;

class Node {
public:
    int data;
    Node* prev;
    Node* next;

    Node(int val) : data(val), prev(nullptr), next(nullptr) {}
};
class DoublyLinkedList {
private:
    Node* head;
    Node* tail;
    /* 
    OR
    In-class initialization, Introduced in C++11
    Node* head = nullptr;
    Node* tail = nullptr;
    */
public:
    // Constructor
    DoublyLinkedList() : head(nullptr), tail(nullptr) {}

    // ---------- INSERT AT END ----------
    void insertAtEnd(int val) {
        Node* newNode = new Node(val);

        if (!head) {
            head = tail = newNode;
        } else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
    }
    // ---------- INSERT AT FRONT ----------
    void insertAtFront(int val) {
        Node* newNode = new Node(val);

        if (!head) {
            head = tail = newNode;
        } else {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }
    }
    // ---------- DELETE BY VALUE ----------
    void deleteValue(int val) {
        Node* curr = head;

        while (curr) {
            if (curr->data == val) {

                if (curr == head)
                    head = curr->next;

                if (curr == tail)
                    tail = curr->prev;

                if (curr->prev)
                    curr->prev->next = curr->next;

                if (curr->next)
                    curr->next->prev = curr->prev;

                delete curr;
                return;
            }
            curr = curr->next;
        }
    }
    // ---------- DISPLAY ----------
    void display() const {
        Node* temp = head;
        while (temp) {
            cout << temp->data << " ";
            temp = temp->next;
        }
        cout << endl;
    }

    // ---------- DESTRUCTOR ----------
    ~DoublyLinkedList() {
        while (head) {
            Node* next = head->next;
            delete head;
            head = next;
        }
    }
};
int main() {
    DoublyLinkedList dll;

    dll.insertAtEnd(10);
    dll.insertAtEnd(20);
    dll.insertAtFront(5);

    dll.display();   // 5 10 20

    dll.deleteValue(10);
    dll.display();   // 5 20

    return 0;
}
