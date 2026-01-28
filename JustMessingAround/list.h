#ifndef LIST_H
#define LIST_H
#include <stdbool.h>

/* ===== Data structures ===== */

typedef struct Node {
    int value;
    struct Node* next;
} Node;

typedef struct List {
    Node* first;
    Node* last;
} List;

typedef struct GenericNode {
    void* value;
    size_t size;
    struct GenericNode* next;
} GenericNode;

/* ===== Creation ===== */

List* createList(void);
Node* createNode(int value, Node* next);

/* ===== Basic operations ===== */

Node* prependList(int value, Node* list);
Node* appendList(Node* list, int value);
Node* appendListIter(Node* list, int value);
Node* appendListRecurs(Node* list, int value);
void  efficientAppending(List* list, int value);

/* ===== Length ===== */

int listLengthRecursively(Node* list);
int listLengthIterative(Node* list);
int listLengthIt(List* list);
int listLengthRec(List* list);

/* ===== Sum ===== */

int listSum(Node* list);
int listAddValues(List* list);

/* ===== Printing ===== */

void printElements(Node* list);
void printList(Node* list);
void printLis(List* list);

/* ===== Ordered list ===== */

void checkSorted(Node* list);
Node* insertOrdered(Node* list, int value);
void insertedOrderList(List* list, int value);

#endif /* LIST_H */