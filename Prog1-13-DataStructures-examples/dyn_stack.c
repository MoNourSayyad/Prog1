/*
Compile: make dyn_stack
Run: ./dyn_stack
make dyn_stack && ./dyn_stack
*/

#include "../prog1lib/lib/base.h"

typedef struct Node {
    int value;
    struct Node* next;
} Node;

Node* new_node(int value, Node* next) {
    Node* n = xcalloc(1, sizeof(Node));
    n->value = value;
    n->next = next;
    return n;
}

typedef struct {
    Node* top;
} Stack;

Stack* new_stack(void) {
    Stack* s = xcalloc(1, sizeof(Stack));
    s->top = NULL; // not necessary if using xcalloc
    return s;
}

void free_stack(Stack* s) {
    require_not_null(s);
    Node* next; // This will temporarily store the next node in the linked list before freeing the current node.
    for (Node* n = s->top; n != NULL; n = next) {
        next = n->next;
        free(n);
    }
    free(s);
}

void push(Stack* s, int x) {
    require_not_null(s);
    s->top = new_node(x, s->top); // next = s->top (points to the current top node)  s->top = ... sets this new node as the new top of the stack.
} // ✅ Effect: last-in, first-out (LIFO) behavior.

int pop(Stack* s) {
    require_not_null(s);
    if (s->top == NULL) {
        printsln("Error: underflow"); 
        return 0;
    } else {
        Node* t = s->top; // Temporary pointer to the top node.
        int x = t->value; // Store the value to return later.
        s->top = t->next; // Move the stack top pointer down one node.  Effectively removes the top node from the stack.
        free(t);  // Free the memory of the old top node.
        return x;
    }
}

bool empty_stack(Stack* s) {
    require_not_null(s);
    return s->top == NULL;
}

int main(void) {
    report_memory_leaks(true);  // 1️⃣ like base_init();  Purpose: Initializes the base library. 2️⃣ base_set_memory_check(true); Purpose: Turns on memory leak detection.
    
    Stack* s = new_stack();
    push(s, 3);
    push(s, 6);
    printiln(pop(s)); // 6
    printiln(pop(s)); // 3
    printbln(empty_stack(s)); // true

    free_stack(s);
    
    return 0;
}
