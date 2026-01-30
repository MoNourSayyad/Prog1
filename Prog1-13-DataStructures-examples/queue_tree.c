/*
Compile: make queue_tree
Run: ./queue_tree
make queue_tree && ./queue_tree
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
    PointerNode* head; // front of queue (first to be served)
    PointerNode* tail; // back of queue (last to be served)
} Queue;

Queue* new_queue(void) {
    Queue* q = xcalloc(1, sizeof(Queue));
    q->head = NULL; // not necessary if using xcalloc
    q->tail = NULL; // not necessary if using xcalloc
    return q;
}

void free_queue(Queue* q) {
    PointerNode* next;
    for (PointerNode* n = q->head; n != NULL; n = next) {
        next = n->next;
        free(n);
    }
    free(q);
}

void put_queue(Queue* q, void* x) {
    PointerNode* t = new_pointer_node(x, NULL);
    if (q->tail != NULL) q->tail->next = t;
    q->tail = t;
    if (q->head == NULL) q->head = t;
}

void* get_queue(Queue* q) {
    PointerNode* h = q->head;
    if (h == NULL) {
        printsln("Error: underflow"); 
        return 0;
    } else {
        void* x = h->value;
        q->head = h->next;
        if (q->head == NULL) q->tail = NULL;
        free(h);
        return x;
    }
}

bool empty_queue(Queue* q) {
    return q->head == NULL;
}

int sum(BTNode* tree) {  // BFS
    int sum = 0;
    Queue* q = new_queue();
    put_queue(q, tree);
    while (!empty_queue(q)) {
        BTNode* n = get_queue(q);
        printiln(n->value);
        sum += n->value;
        if (n->left != NULL) put_queue(q, n->left);
        if (n->right != NULL) put_queue(q, n->right);
    }
    free_queue(q);
    return sum;
}

int main(void) {
    report_memory_leaks(true);
    
    BTNode* t = new_btnode(1, 
                    new_btnode(2, 
                        new_btnode(4, 
                            new_leaf(8), 
                            new_leaf(9)), 
                        new_btnode(5, 
                            new_leaf(10), 
                            new_leaf(11))),  
                    new_btnode(3, 
                        new_btnode(6, 
                            new_leaf(12), 
                            new_leaf(13)), 
                        new_btnode(7, 
                            new_leaf(14), 
                            new_leaf(15))));
    println_tree(t);

    printiln(sum(t));

    free_tree(t);
    
    return 0;
}
