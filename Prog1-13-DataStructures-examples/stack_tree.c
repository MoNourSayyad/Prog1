/*
Compile: make stack_tree
Run: ./stack_tree
make stack_tree && ./stack_tree
*/

#include "../prog1lib/lib/base.h"
#include "integer_tree.h"

typedef struct PointerNode {
    void* value;
    struct PointerNode* next;
} PointerNode;

PointerNode* new_pointer_node(void* value, PointerNode* next) {
    PointerNode* n = xcalloc(1, sizeof(PointerNode));
    n->value = value;
    n->next = next;
    return n;
}

typedef struct {
    PointerNode* top;
} Stack;

Stack* new_stack(void) {
    Stack* s = xcalloc(1, sizeof(Stack));
    s->top = NULL; // not necessary if using xcalloc
    return s;
}

void free_stack(Stack* s) {
    PointerNode* next;
    for (PointerNode* n = s->top; n != NULL; n = next) {
        next = n->next;
        free(n);
    }
    free(s);
}

void push(Stack* s, void* x) {
    s->top = new_pointer_node(x, s->top);
}

void* pop(Stack* s) {
    if (s->top == NULL) {
        printsln("Error: underflow"); 
        return 0;
    } else {
        PointerNode* t = s->top;
        void* x = t->value;
        s->top = t->next;
        free(t);
        return x;
    }
}

bool empty_stack(Stack* s) {
    return s->top == NULL;
}

int sum(BTNode* tree) { // DFS
    int sum = 0;
    Stack* stack = new_stack();
    push(stack, tree);
    while (!empty_stack(stack)) {
        BTNode* n = pop(stack);
        printiln(n->value);
        sum += n->value;
        if (n->right != NULL) push(stack, n->right);
        if (n->left != NULL) push(stack, n->left);
    }
    free_stack(stack);
    return sum;
}

int main(void) {
    base_init();
    report_memory_leaks(true);
    
    BTNode* t = new_btnode(1, 
                    new_btnode(2, 
                        new_btnode(3, 
                            new_leaf(4), 
                            new_leaf(5)), 
                        new_btnode(6, 
                            new_leaf(7), 
                            new_leaf(8))),  
                    new_btnode(9, 
                        new_btnode(10, 
                            new_leaf(11), 
                            new_leaf(12)), 
                        new_btnode(13, 
                            new_leaf(14), 
                            new_leaf(15))));
    println_tree(t);

#if 0
    int sum = 0;
    Stack* s = new_stack();
    push(s, t);
    while (!empty_stack(s)) {
        BTNode* n = pop(s);
        printiln(n->value);
        sum += n->value;
        if (n->right != NULL) push(s, n->right);
        if (n->left != NULL) push(s, n->left);
    }
    free_stack(s);
    printiln(sum);
#endif
    printiln(sum(t));

    free_tree(t);
    
    return 0;
}
