/*
Compile: make queue
Run: ./queue
make queue && ./queue
*/

#include "../prog1lib/lib/base.h"

typedef struct {
    int* data; // array of int
    int length; // capacity of the data array (number of ints)
    int head; // next position to read
    int tail; // next position to write
    int n; // number of items in the queue
} Queue;

Queue* new_queue(int length) {
    Queue* q = xcalloc(1, sizeof(Queue));
    q->data = xcalloc(length, sizeof(int));
    q->length = length;
    q->head = 0;
    q->tail = 0;
    q->n = 0;
    return q;
}

void free_queue(Queue* q) {
    free(q->data);
    free(q);
}

void put_queue(Queue* q, int x) {
    require_not_null(q);
    if (q->n == q->length) {  // if circular buffer is full
        printsln("error: overflow");
    } else {
        q->data[q->tail] = x; 
        q->n++;
        q->tail = (q->tail + 1) % q->length; // increment tail and find rest
    }
}

int get_queue(Queue* q) {
    require_not_null(q);
    if (q->n == 0) {
        printsln("error: underflow");
        return 0;
    } else {
        int x = q->data[q->head]; 
        q->n--;
        q->head = (q->head + 1) % q->length;
        return x;
    }   
}



int main(void) {
    report_memory_leaks(true);
    
    Queue* q = new_queue(8);
    put_queue(q, 3);
    put_queue(q, 6);
    printiln(get_queue(q)); // 3
    printiln(get_queue(q)); // 6
    
    free_queue(q);
    
    return 0;
}
