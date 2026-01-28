#ifndef __INTEGER_LIST_H__
#define __INTEGER_LIST_H__

#include "../prog1lib/lib/base.h"

// Represents a single list node.
typedef struct Node {
    int value; // points to an Int
    struct Node* next; // self-reference
} Node;

// Creates a list node.
Node* new_node(int value, Node* next);

// Prints the elements of the given list.
void print_list(Node* list);

// Prints list followed by a line break.
void println_list(Node* list);

// Frees all nodes of the list.
void free_list(Node* list);

// Computes the number of elements of the list.
int length_list(Node* list);

// Checks whether list contains x.
bool contains_list(Node* list, int x);

// Removes element at position index from list.
Node* remove_list(Node* list, int index);

// Prepends an element in front of the list.
Node* prepend_list(int value, Node* list);

// Adds an element to the end of the list. Modifies the existing list.
Node* append_list(Node* list, int value);

// Copies the list.
Node* copy_list(Node* list);

// Inserts value in list at index.
Node* insert_list(Node* list, int index, int value);

// Inserts value at the right position.
Node* insert_ordered(Node* list, int value);

// Reverses the origial (!) list.
Node* reverse_list(Node* list);

// Checks whether x satisfies a predicate.
typedef bool (*FilterFun)(int element, void* x);

// Finds the index of the first element in list for which pred(element, i, x) is true, 
// or -1 of no element satisfies pred.
int index_list(Node* list, FilterFun pred, void* x);

///////////////////////////////////////////////////////////////////////////////

// Transforms element into something else.
typedef int (*MapFun)(int element, void* x);

// Maps each list element to f(element, index, x).
Node* map_list(Node* list, MapFun f, void* x);

// Produces a list of those elements of list that satisfy the predicate.
Node* filter_list(Node* list, FilterFun predicate, void* x);

// First filters list using predicate and then maps the filtered elements using map.
Node* filter_map_list(Node* list, FilterFun predicate, void* x, MapFun map, void* y);

// Aggregates a list: state is the intermediary aggregation result, element is the current element.
typedef int (*ReduceFun)(int state, int element);

// Aggregates the values of the tree by sequentally applying state = f(state, element).
void reduce_list(Node* list, ReduceFun f, int state);

#endif
