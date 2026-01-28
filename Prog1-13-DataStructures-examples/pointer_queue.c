#include "pointer_queue.h"
#include "../prog1lib/lib/base.h"

typedef struct PointerNode {
    void* value;
    struct PointerNode* next;
} PointerNode;

static PointerNode* new_pointer_node(void* value, PointerNode* next) {
    PointerNode* n = xcalloc(1, sizeof(PointerNode));
    n->value = value;
    n->next = next;
    return n;
}

struct Queue {
    PointerNode* head; // front of queue (first to be served)
    PointerNode* tail; // back of queue (last to be served)
};

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

bool is_empty_queue(Queue* q) {
    return q->head == NULL;
}
