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
    q->head = NULL; // not necessary if using xcalloc
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
    Node* t = new_node(x, NULL);
    if (q->tail != NULL) q->tail->next = t;
    q->tail = t;
    if (q->head == NULL) q->head = t;
}

int get_queue(Queue* q) {
    Node* h = q->head;
    if (h == NULL) {
        printsln("Error: underflow"); 
        return 0;
    } else {
        int x = h->value;
        q->head = h->next;
        if (q->head == NULL) q->tail = NULL;
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
