#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

typedef struct Node Node;
struct Node {
    Node* next; // Last element points back to head
    int value;
};

typedef struct {
    Node* head; // NULL if LinkedList is empty
} LinkedList;

void init(LinkedList* linkedList) {
    // NULL head means empty list
    linkedList->head = NULL;
}

LinkedList* create() {
    LinkedList* linkedList = (LinkedList*) malloc(sizeof(LinkedList));

    // NOTE Find out why is this if here
    if (linkedList == NULL) { 
        return NULL;
    }

    init(linkedList);
    return linkedList;
}

bool isEmpty(LinkedList* linkedList) {
    return linkedList->head == NULL;
}

void append(LinkedList* linkedList, int value) {

    // Create new node
    Node* newNode = (Node*) malloc(sizeof(Node));
    newNode->value = value;

    // Edge case
    if (isEmpty(linkedList)) {
        linkedList->head = newNode;
        newNode->next = linkedList->head;
        return;
    }

    // Find last node
    Node* lastNode = linkedList->head;
    while (lastNode->next != linkedList->head) {
      lastNode = lastNode->next;
    }

    // Insert it
    lastNode->next = newNode;
    newNode->next = linkedList->head;

}

int popLast(LinkedList* linkedList) {
    // if linkedList is empty, program crashes with dereferencing NULL pointer

    // Only one node left
    if (linkedList->head->next == linkedList->head) {
        int returnValue = linkedList->head->value;
        free(linkedList->head);
        linkedList->head = NULL;
        return returnValue;
    }

    // Find second to last node
    Node* secondToLastNode = linkedList->head;
    while (secondToLastNode->next->next != linkedList->head) {
        secondToLastNode = secondToLastNode->next;
    }

    // Relink
    int returnValue = secondToLastNode->next->value;
    free(secondToLastNode->next);
    secondToLastNode->next = linkedList->head;
    return returnValue;
}

void prepend(LinkedList* linkedList, int value) {

    // Create new node
    Node* newNode = (Node*) malloc(sizeof(Node));
    newNode->value = value;

    // Edge case
    if (isEmpty(linkedList)) {
        linkedList->head = newNode;
        newNode->next = linkedList->head;
        return;
    }

    // Find last node
    Node* lastNode = linkedList->head;
    while (lastNode->next != linkedList->head) {
      lastNode = lastNode->next;
    }

    // Insert
    lastNode->next = newNode;
    newNode->next = linkedList->head; //Old head
    linkedList->head = newNode;
}

int popFirst(LinkedList* linkedList) {
    // if linkedList is empty, program crashes with dereferencing NULL pointer
    
    // Only one node left
    if (linkedList->head->next == linkedList->head) {
        int returnValue = linkedList->head->value;
        free(linkedList->head);
        linkedList->head = NULL;
        return returnValue;
    }

    // Find last node
    Node* lastNode = linkedList->head;
    while (lastNode->next != linkedList->head) {
      lastNode = lastNode->next;
    }

    // Relink
    lastNode->next = linkedList->head->next;
    int returnValue = linkedList->head->value;
    free(linkedList->head);
    linkedList->head = lastNode->next;
    return returnValue;
}

void print(LinkedList* linkedList) {

    // Edge case 
    if (isEmpty(linkedList)) {
        printf("EMPTY\n");
        return;
    }

    // Print every node
    Node* iterator = linkedList->head;
    while (iterator->next != linkedList->head) {
        printf("[%p] value: %d next: %p\n", iterator, iterator->value, iterator->next);
        iterator = iterator->next;
    }
    printf("[%p] value: %d next: %p\n", iterator, iterator->value, iterator->next);
}

void destroy(LinkedList* linkedList) {
    if (!isEmpty(linkedList)) {
        Node* iterator = linkedList->head;
        while (iterator->next != linkedList->head) {
            Node* toBeFreed = iterator;
            iterator = iterator->next;
            free(toBeFreed);
        }
        free(iterator);
    }
}

int main () {
    LinkedList linkedList;
    init(&linkedList);
    append(&linkedList, 1);
    append(&linkedList, 2);
    append(&linkedList, 3);
    prepend(&linkedList, 0);
    while (!isEmpty(&linkedList)) {
        printf("%d\n", popLast(&linkedList)); 
    }
    prepend(&linkedList, 99);
    prepend(&linkedList, 98);
    prepend(&linkedList, 97);
    append(&linkedList, 100);
    print(&linkedList);
    popFirst(&linkedList);
    destroy(&linkedList);
}

