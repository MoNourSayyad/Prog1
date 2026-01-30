/*
Compile: make dyn_queue
Run: ./dyn_queue
make dyn_queue && ./dyn_queue
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
    Node* head; // front of queue (first to be served)
    Node* tail; // back of queue (last to be served)
} Queue;

Queue* new_queue(void) {
    Queue* q = xcalloc(1, sizeof(Queue));
    q->head = NULL; // not necessary if using xcalloc  // 
    q->tail = NULL; // not necessary if using xcalloc
    return q;
}

void free_queue(Queue* q) {
    Node* next;
    for (Node* n = q->head; n != NULL; n = next) {
        next = n->next;
        free(n);
    }
    free(q);
}

void put_queue(Queue* q, int x) {
    require_not_null(q);
    Node* t = new_node(x, NULL); // Sets t->next = NULL because it will be the last element of the queue.
    if (q->tail != NULL) q->tail->next = t;  // Connects the current last node to the new node.
    q->tail = t; // Updates the queue’s tail pointer.
    if (q->head == NULL) q->head = t; // The new node is both the first (head) and last (tail) element.
}

int get_queue(Queue* q) {
    require_not_null(q);
    Node* h = q->head; // Stores the current head node
    if (h == NULL) {
        printsln("Error: underflow"); 
        return 0;
    } else {
        int x = h->value; // Stores its value
        q->head = h->next;
        if (q->head == NULL) q->tail = NULL; // If the queue becomes empty: Sets tail to NULL
        free(h);
        return x;
    }
}

bool empty_queue(Queue* q) {
    return q->head == NULL;
}

int main(void) {
    report_memory_leaks(true);
    
    Queue* q = new_queue();
    put_queue(q, 3);
    put_queue(q, 6);
    printiln(get_queue(q)); // 3
    printiln(get_queue(q)); // 6
    
    for (int i = 0; i < 20; i++) {
//        put_queue(q, i_rnd(100));
        put_queue(q, i);
    }

    while (!empty_queue(q)) {
        printf("%d, ", get_queue(q));
    }
    printf("\n");
    
    free_queue(q);
    
    return 0;
}
