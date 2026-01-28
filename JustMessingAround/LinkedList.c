#include <stdio.h>
#include <stdlib.h>
#include "../prog1lib/lib/base.h"
#include "list.h"
#include <limits.h>

List* createList(void) {
    return xcalloc(1,sizeof(List));
}


/**
 * @brief Creates a new node with a given value.
 * @param value Integer value to store.
 * @param next Pointer to next node (can be NULL).
 * @return Pointer to the newly created Node.
 */
Node* createNode(int value, Node* next) {
    Node* node = xcalloc(1,sizeof(Node));
    node->value = value;
    node->next = next;
    return node;
}


/**
 * @brief Prepends a value to the beginning of a list.
 * @param value Value to prepend.
 * @param list Pointer to the head node of the list.
 * @return New head of the list.
 */
Node* prependList(int value, Node* list) {
   return createNode(value, list);
}

int listLengthRecursively(Node* list) {
    if (list == NULL)
        return 0;
    else {
        return 1 + listLengthRecursively(list->next);
    }
}

int listLengthIterative(Node* list) {
    int result = 0;
    for (Node* node = list ; node != NULL ; node = node->next)  // Or instead of for loop  while (list != NULL) { result++; list = list->next; }
        result++;
    return result;
}

int listLengthIt(List* list) {
    int result = 0;
    for ( Node* node = list->first; node != NULL; node = node->next)
        result++;
    return result;
}

int listLengthRec(List* list) {
    return listLengthRecursively(list->first);
}

int listSum(Node* list) {
    if (list == NULL)
        return 0;
    else {
        return list->value + listSum(list->next);
    } 
}

int listAddValues(List* list) {
    return listSum(list->first);
}

/**
 * @brief Prints the linked list in a "1 -> 2 -> 3" style.
 * @param list Pointer to the head node.
 */
void printElements(Node* list) {
    if (list == NULL)
        return;
    else if (list->next == NULL)
        printf("%d", list->value);
    else {
        printf("%d -> ", list->value);
        printElements(list->next);
    }
}

void printList(Node* list) {
    prints("[");
    printElements(list);
    prints("]\n");
}

void printLis(List* list) {
    printList(list->first);
}

Node* lastNode(Node* list) {
    require_not_null(list);
    if (list->next == NULL)
        return list;
    else
        return lastNode(list->next);
}

Node* appendList(Node* list, int value) {
    if(list == NULL)
        return createNode(value, NULL);
    else {
        lastNode(list)->next = createNode(value, NULL);
        return list;
    }
}

Node* appendListIter(Node* list, int value) {
    if (list == NULL)
        return createNode(value, NULL);
    else {
        Node* n = list;  // You are copying the address stored in list into n. So both point to the same node.
        while (n->next != NULL) n = n->next;
        assert("on last element", n !=NULL && n->next == NULL);
        n->next = createNode(value, NULL);
        return list;
    }
}

Node* appendListRecurs(Node* list, int value) {
    if (list == NULL)
        return createNode(value, NULL);
    else {
        list->next = appendListRecurs(list->next, value);
        return list;
    }
}

void efficientAppending(List* list, int value) {
    require("list head exists", list != NULL);
    Node* node = createNode(value, NULL);
    if (list->first == NULL){
        list->first = node;
        list->last = node;
    } else  {
        list->last->next = node;
        list->last = node;
    }  
}

void checkSorted(Node* list) {
    bool sorted = 
    forall_x(Node* n = list,
         n != NULL && n->next != NULL,
         n= n->next,
         n->value <= n->next->value
    ); 
    if(!sorted)
        prints("Array not sorted in asceding order.");
}

Node* insertOrdered(Node* list, int value) {
    require("Array not sorted in asceding order.", forall_x(Node* n = list, n != NULL && n->next != NULL,n= n->next,n->value <= n->next->value));
    if (list == NULL)
        return createNode(value, NULL);
    else if (value <list->value)
        return prependList(value, list);
    else {
        for (Node* n = list; n != NULL; n = n->next) {
            if (n->next == NULL){
                n->next = createNode(value, NULL); 
                break; 
            } else if (value < n->next->value) {
                n->next =createNode(value, n->next);
                break;
            }
        }
        return list;
    }
}

void insertedOrderList(List* list, int value) {
    checkSorted(list->first);
    Node* newNode = createNode(value, NULL);
    require("list head exists", list != NULL);
    if (list->first == NULL) {
        list->first = list->last = newNode;
        return;
    } else if (value < list->first->value) {
        newNode->next = list->first;
        list->first = newNode;
        return;
    }
    Node* current = list->first;
    while (current->next != NULL && value > current->next->value) 
        current = current->next;
    
    newNode->next = current->next;
    current->next = newNode;

    if (current == list->last)
        list->last = newNode; 
}

void freeList(List* list) {
    if (list == NULL)
        return;

    Node* current = list->first;
    while (current != NULL) {
        Node* next = current->next;
        free(current);
        current = next;
    }

    free(list);
}

void freeNodeList(Node* list) {
    while (list) {
        Node* next = list->next;
        free(list);
        list = next;
    }
}

typedef bool (*FilterFunc) (void* elemment,int i, void* x);

void* findList(GenericNode* list, FilterFunc pred, void* x) {
    if(!pred) return NULL;
    int i = 0;

    for (GenericNode* node = list; node != NULL; node = node->next,i++) {
        if(pred(node->value, i, x))
            return node->value;
    }
    return NULL;    
}

bool equalsTarget(void* element, int i, void* x) {
    int value = *(int*) element;
    int target = *(int*) x;
    return value == target;
}

bool even_index(void* element, int i, void* x) {
    (void)element; // unused
    (void)x;       // unused
    return i % 2 == 0;
}

/**
 * @brief Creates a generic node with a copy of the given value.
 *
 * @param value Pointer to the data to store.
 * @param size Size of the data in bytes.
 * @param next Pointer to the next generic node (can be NULL).
 * @return Pointer to the newly allocated GenericNode.
 */
GenericNode* createGenericNode(void* value, size_t size, GenericNode* next) {
    GenericNode* genericNode = xmalloc(sizeof(GenericNode));
    genericNode->size = size;
    genericNode->value = xmalloc(size);
    memcpy(genericNode->value, value, size);
    genericNode->next = next;
    return genericNode;
}

typedef bool (*EqualFunc)(void* a, void* b);

bool contains_list(GenericNode* list, void* element, EqualFunc equal) {
    if (equal == NULL) { // identity-based equality
        for (GenericNode* node = list; node != NULL; node = node->next) {
            if (node->value == element) return true; // compare pointers
        }
    } else { // content-based equality
        for (GenericNode* node = list; node != NULL; node = node->next) {
            if (equal(node->value, element)) return true; // compare content
        }
    }
    return false;
}

bool int_equal(void* a, void* b) {
    return *(int*)a == *(int*)b;
}

bool str_equal(void* a, void* b) {
    return strcmp((char*)a, (char*)b) == 0;
}

void freeGenericList(GenericNode* list) {
    while (list) {
        GenericNode* next = list->next;
        free(list->value); // works cuz of previous memcpy
        free(list);         
        list = next;
    }
}

Node* reverse_list(Node* head) {
    Node* prev = NULL;
    Node* curr = head;

    while (curr != NULL) {
        Node* next = curr->next;  // don’t lose the rest
        curr->next = prev;        // flip arrow
        prev = curr;              // move prev
        curr = next;              // move curr
    }

    return prev;
}

GenericNode* reverseGenericList(GenericNode* head) {
    GenericNode* prev = NULL;
    GenericNode* curr = head;

    while (curr != NULL) {
        GenericNode* next = curr->next;  // don’t lose the rest
        curr->next = prev;        // flip arrow
        prev = curr;              // move prev
        curr = next;              // move curr
    }

    return prev;
}

typedef bool (*FilterFunc)(void* element, int index, void* extra);

bool evenNum(void* element, int index, void* extra __attribute__((__unused__))) {
    (void) index;
    int* intElement = (int*) element;
    return *(intElement) % 2 == 0;
}

GenericNode* filteringList(GenericNode* list, FilterFunc filtering, void* extra) {
    GenericNode* result = NULL;
    int i = 0;
    for (GenericNode* node = list; node != NULL; node = node->next, i++){
        if (filtering(node->value, i, extra))
            result = createGenericNode(node->value, node->size, result);
    }
    return reverseGenericList(result);
}

typedef void (*ReduceFunc)(void* state, void* element, int index);

void reduceList(GenericNode* list, ReduceFunc reduce, void* state) {
    int i = 0;
    for (GenericNode* node =list; node != NULL; node = node->next, i++)
        reduce(state, node->value, i);
}

void maxReduce(void* state, void* element, int index __attribute__((__unused__))) {
    int value = *(int*)element;
    int* max = (int*)state;
    if (value > *max)
        *max = value;
}

GenericNode* buildGenericList(int* arr, int size) {
    GenericNode* head = NULL;
    GenericNode* last = NULL;

    for (int i = 0; i < size; i++) {
        GenericNode* node = createGenericNode(&arr[i], sizeof(int), NULL);
        if (head == NULL) {
            head = last = node;
        } else {
            last->next = node;
            last = node;
        }
    }
    return head;
}


int main(void){
    List* linkedList = createList();
    Node* n0 = createNode(7,NULL);
    linkedList->first = n0;
    linkedList->first = prependList(5,linkedList->first);
    printi(listAddValues(linkedList));
    puts("");
    linkedList->last = n0; // Only once, appendning does the rest autocmatically.
    efficientAppending(linkedList, 9);
    insertedOrderList(linkedList,8);
    printLis(linkedList);
    
    Node* rest = prependList(5,prependList(7,NULL));
    Node* list123 = createNode(4,rest);
    printi(listLengthRecursively(list123));
    puts("");
    printi(listSum(list123));
    puts("");
    printList(list123);
    insertOrdered(list123, 12);
    printList(list123);
    report_memory_leaks(true);

     // Create some integers
    int a = 10, b = 20, c = 30, d = 40;

    // Build the list: d -> c -> b -> a
    GenericNode* list = NULL;
    list = createGenericNode(&d, sizeof(int), list);
    list = createGenericNode(&c, sizeof(int), list);
    list = createGenericNode(&b, sizeof(int), list);
    list = createGenericNode(&a, sizeof(int), list);

    /*
    // Example 1: find value == 30
    int target = 30;
    int* result1 = find_list(list, equalsTarget, &target);
    if (result1)
        printf("Found target: %d\n", *result1);
    else
        printf("Target not found\n");

    // Example 2: find first element at even index
    int* result2 = find_list(list, even_index, NULL);
    if (result2)
        printf("First element at even index: %d\n", *result2);
    else
        printf("No element at even index\n");

    // Free list (nodes only, pointer-only version)
    Node* node_next;
    for (Node* node = list; node != NULL; node = node_next) {
        node_next = node->next;
        free(node);
    }


    // ---------- Identity-based example ----------
    int a = 10, b = 20, c = 30;
    Node* list1 = NULL;
    list1 = createNode(&c, list1);
    list1 = createNode(&b, list1);
    list1 = createNode(&a, list1);

    int* ptr = &b; // pointer we want to check
    if (contains_list(list1, ptr, NULL)) {
        printf("Identity: List contains pointer to %d\n", *ptr);
    } else {
        printf("Identity: Not found\n");
    }

    // ---------- Content-based example ----------
    char* s1 = "apple";
    char* s2 = "banana";
    char* s3 = "cherry";

    Node* list2 = NULL;
    list2 = createNode(s3, list2);
    list2 = createNode(s2, list2);
    list2 = createNode(s1, list2);

    char* target = "banana";
    if (contains_list(list2, target, str_equal)) {
        printf("Content: List contains \"%s\"\n", target);
    } else {
        printf("Content: Not found\n");
    }

    // Free nodes (pointer-only)
    Node* next;
    for (Node* n = list1; n != NULL; n = next) {
        next = n->next;
        free(n);
    }
    for (Node* n = list2; n != NULL; n = next) {
        next = n->next;
        free(n);
    }
    
    */


    GenericNode* genericList = NULL;
    int values[] = {5,6,7,83,2,1,6,-122,70};
    int arraySize = sizeof(values) / sizeof(values[0]);
    for (int i = 0; i < arraySize; i++)
        genericList = createGenericNode(&values[i], sizeof(int), genericList);
    int max = INT_MIN;
    reduceList(genericList, maxReduce, &max);
    printf("Maximum value in list = %d\n", max);

    return 0;
}
