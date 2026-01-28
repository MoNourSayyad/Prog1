/*
Compile: make integer_list
Run: ./integer_list
make integer_list && ./integer_list
*/

#include "integer_list.h"

// Creates a list node.
Node* new_node(int value, Node* next) {
    Node* node = xcalloc(1, sizeof(Node));
    node->value = value;
    node->next = next;
    return node;
}

// Prints the elements of the given list.
void print_list(Node* list) {
    if (list == NULL) {
        printf("[]");
    } else {
        printf("[%d", list->value);
        for (Node* n = list->next; n != NULL; n = n->next) {
            printf(", %d", n->value);
        }
        printf("]");
    }
}

// Prints list followed by a line break.
void println_list(Node* list) {
    print_list(list);
    printsln("");
}

// Frees all nodes of the list.
void free_list(Node* list) {
    Node* node_next = NULL;
    for (Node* node = list; node != NULL; node = node_next) {
        node_next = node->next;
        free(node);
    }
}

// Computes the number of elements of the list.
int length_list(Node* list) {
    int n = 0;
    for (Node* node = list; node != NULL; node = node->next) n++;
    return n;
}

// Checks whether list contains x.
bool contains_list(Node* list, int x) {
    for (Node* node = list; node != NULL; node = node->next) {
        if (node->value == x) { // compare ints
            return true;
        }
    }
    return false;
}

// Removes element at position index from list.
Node* remove_list(Node* list, int index) {
    if (list == NULL || index < 0) return list;
    if (index == 0) { // remove first element of non-empty list
        Node* n = list->next;
        free(list);
        return n;
    }
    // return second or later element of non-empty list
    int i = 0;
    for (Node* node = list; node != NULL; node = node->next) {
        if (i + 1 == index) {
            Node* to_remove = node->next;
            if (to_remove == NULL) return list;
            Node* n = to_remove->next;
            free(to_remove);
            node->next = n;
            return list;
        }
        i++;
    }
    return list;
}

// Prepends an element in front of the list.
Node* prepend_list(int value, Node* list) {
    return new_node(value, list);
}

// Adds an element to the end of the list. Modifies the existing list.
Node* append_list(Node* list, int value) {
    if (list == NULL) { // empty list
        return new_node(value, NULL);
    } else { // non-empty list
        Node* n = list;
        while (n->next != NULL) n = n->next; // find last element
        // assert: n != NULL && n->next == NULL
        n->next = new_node(value, NULL);
        return list;
    }
}

// Copies the list.
Node* copy_list(Node* list) {
    if (list == NULL) {
        return NULL;
    } else {
        Node* result = new_node(list->value, NULL);
        for (Node* n = result; list->next != NULL; n = n->next) {
            list = list->next;
            n->next = new_node(list->value, NULL);
        }
        return result;
    }
}

// Inserts value in list at index.
Node* insert_list(Node* list, int index, int value) {
    if (index < 0) return list; // invalid index, no change
    if (index == 0) { // insert at front
        return new_node(value, list);
    }
    // insert after first element
    Node *node = list;
    int i = 1;
    while (node != NULL && i < index) { // skip index - 1 nodes
        node = node->next;
        i++;
    }
    if (node != NULL) {
        node->next = new_node(value, node->next);
    }
    return list;
}


// Inserts value at the right position.
Node* insert_ordered(Node* list, int value) {
    if (list == NULL) { // empty list
        return new_node(value, NULL);
    } else if (value < list->value) { // insert before first
        return new_node(value, list);
    } else { // non-empty list, find insertion position after first node
        for (Node* n = list; n != NULL; n = n->next) {
            if (n->next == NULL) { // end of list?
                n->next = new_node(value, n->next);
                break;
            } else if (value < n->next->value) { // found position?
                n->next = new_node(value, n->next);
                break;
            }
        }
        return list;
    }
}

// Reverse the origial (!) list.
Node* reverse_list(Node* list) {
    if (list == NULL) {
        return NULL;
    } else {
        Node* first = list;
        Node* last = list;
        Node* next;
        for (Node* n = list->next; n != NULL; n = next) {
            next = n->next;
            n->next = first;
            first = n;
        }
        last->next = NULL;
        return first;
    }
}

// Finds the index of the first element in list for which pred(element, i, x) is true, 
// or -1 of no element satisfies pred.
int index_list(Node* list, FilterFun pred, void* x) {
    int i = 0;
    for (Node* node = list; node != NULL; node = node->next, i++) {
        if (pred(node->value, x)) {
            return i;
        }
    }
    return -1;
}

///////////////////////////////////////////////////////////////////////////

#if 0
// Maps each list element to f(element, index, x).
Node* map_list(Node* list, MapFun f, void* x) {
    Node* result = NULL;
    int i = 0;
    for (Node* node = list; node != NULL; node = node->next, i++) {
        result = new_node(f(node->value, i, x), result);
    }
    return reverse_list(result);
}
#else
// Maps each list element to f(element, index, x).
Node* map_list(Node* list, MapFun f, void* x) {
    if (list == NULL) return NULL;
    Node* first = new_node(f(list->value, x), NULL);
    Node* last = first;
    for (Node* node = list->next; node != NULL; node = node->next) {
        last->next = new_node(f(node->value, x), NULL);
        last = last->next;
    }
    return first;
}
#endif

#if 0
// Produces a list of those elements of list that satisfy the predicate.
Node* filter_list(Node* list, FilterFun pred, void* x) {
    Node* result = NULL;
    int i = 0;
    for (Node* node = list; node != NULL; node = node->next, i++) {
        if (pred(node->value, i, x)) {
            result = new_node(node->value, result);
        }
    }
    return reverse_list(result);
}
#else
// Produces a list of those elements of list that satisfy the predicate.
Node* filter_list(Node* list, FilterFun pred, void* x) {
    Node* first = NULL;
    Node* last = NULL;
    for (Node* node = list; node != NULL; node = node->next) {
        if (pred(node->value, x)) {
            if (first == NULL) {
                first = new_node(node->value, NULL);
                last = first;
            } else {
                last->next = new_node(node->value, NULL);
                last = last->next;
            }
        }
    }
    return first;
}
#endif

// First filters list using predicate and then maps the filtered elements using map.
Node* filter_map_list(Node* list, FilterFun pred, void* x, MapFun map, void* y) {
    Node* result = NULL;
    for (Node* node = list; node != NULL; node = node->next) {
        if (pred(node->value, x)) {
            result = new_node(map(node->value, y), result);
        }
    }
    return reverse_list(result);
}

// Aggregates the values of the tree by sequentally applying state = f(state, element).
void reduce_list(Node* list, ReduceFun f, int state) {
    for (Node* node = list; node != NULL; node = node->next) {
        f(state, node->value);
    }
}

int mainx(void) {
    printsln("test");
    return 0;
}
