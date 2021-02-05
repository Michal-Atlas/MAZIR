#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

typedef struct Node Node;
struct Node {
    Node* next; // Last element points back to head
    Node *last;
    int value;
};

typedef struct {
    Node *head; // NULL if LinkedList is empty
} LinkedList;

void init(LinkedList* linkedList) {
    // NULL head means empty list
    linkedList->head = NULL;
}

LinkedList* create() {
    LinkedList *linkedList = (LinkedList *) malloc(sizeof(LinkedList));

    // NOTE Find out why is this if here
    // Memory allocation can fail, either from insufficient memory or high latency
    // Compiling with incorrect specifications seems to also be a thing, as some systems reserve certain memory
    // A 0 pointer may even sometimes be valid apparently
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
        newNode->last = linkedList->head;
        return;
    }

    // Insert it
    newNode->next = linkedList->head;
    newNode->last = linkedList->head->last;
    linkedList->head->last = newNode;
    linkedList->head->last->last->next = newNode;
}

Node *find(LinkedList *linkedList, int target) {
    Node *cursor = linkedList->head;

    while (cursor->value != target) {
        if (cursor->next == NULL) { return NULL; }
        cursor = cursor->next;
    }
    return cursor;
}

bool member(LinkedList *linkedList, int target) {
    return find(linkedList, target) != NULL;
}

int popLast(LinkedList *linkedList) {
    // if linkedList is empty, program crashes with dereferencing NULL pointer

    // Only one node left
    if (linkedList->head->next == linkedList->head) {
        int returnValue = linkedList->head->value;
        free(linkedList->head);
        linkedList->head = NULL;
        return returnValue;
    }

    // Relink
    Node *new_tail = linkedList->head->last->last;
    int returnValue = linkedList->head->last->value;

    free(linkedList->head->last);
    new_tail->next = linkedList->head;
    linkedList->head->last = new_tail;

    return returnValue;
}

void prepend(LinkedList* linkedList, int value) {

    /*// Create new node
    Node* newNode = (Node*) malloc(sizeof(Node));
    newNode->value = value;

    // Edge case
    if (isEmpty(linkedList)) {
        linkedList->head = newNode;
        newNode->next = linkedList->head;
        return;
    }*/

    // Insert
    append(linkedList, value);
    linkedList->head = linkedList->head->last;
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

    // Relink
    linkedList->head = linkedList->head->last;
    int returnValue = popLast(linkedList);
    linkedList->head = linkedList->head->next;
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

LinkedList* createSequenceInLInkedList() {
    LinkedList *linkedList = malloc(sizeof(LinkedList));
    init(linkedList);
    for(int i = 1; i <= 100; i++) {
        append(linkedList, i);
    }
    return linkedList;
}

int main () {
    LinkedList *a = createSequenceInLInkedList();
    destroy(a);
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

