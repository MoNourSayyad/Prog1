/*
Compile: make vector
Run: ./vector
make vector && ./vector
*/

#include "../prog1lib/lib/base.h"

typedef struct {
    int* data;
    int capacity; // capacity of the data array (number of ints)
    int n; // number of items in the vector
} Vector;

Vector* vector_new(int capacity) {
    require("capacity must be positive", capacity > 0);
    Vector* v = xcalloc(1, sizeof(Vector));
    v->capacity = capacity;
    v->data = xcalloc(v->capacity, sizeof(int));
    v->n = 0;
    return v;
}

Vector* new_vector(void) {
    Vector* v = xcalloc(1, sizeof(Vector));
    v->capacity = 2; // initial capacity
    v->data = xcalloc(v->capacity, sizeof(int));
    v->n = 0;
    return v;
}

void free_vector(Vector* v) {
    require_not_null(v);
    free(v->data);
    free(v);
}

void add_vector(Vector* v, int x) {
    require_not_null(v);
    if (v->n >= v->capacity) { // need a larger array, reallocate
        v->capacity *= 2; // duplicate capacity
        printf("reallocating, new capacity: %d ints\n", v->capacity);
        int* data_new = xcalloc(v->capacity, sizeof(int)); // allocate larger array
        memcpy(data_new, v->data, v->n * sizeof(int)); // copy elements  // void* memcpy(void* dst, const void* src, size_t n)
        free(v->data); // delete old array
        v->data = data_new; // set new array
    }
    v->data[v->n++] = x; // store value
}

int count_vector(Vector* v) {
    require_not_null(v);
    return v->n;
}

int get_vector(Vector* v, int i) {
    require_not_null(v);
    if (i < 0 || i >= v->n) {   // require("valid index", i >= 0 && i < v->count);
        printsln("error: index out of bounds");
        return 0;
    }
    return v->data[i];
}

typedef struct {
    int capacity;  // maximum number of items
    int count;  // current number of items
    int data[]; // flexible array member must be last
} FlexVector;

FlexVector* new_flexVector(int capacity) {
    require("Capacity must be pos", capacity > 0);
    int n = sizeof(FlexVector) + capacity * sizeof(int);
    FlexVector* flexVector = xmalloc(n);
    memset(flexVector, 0, n);  // set each byte to 0
    flexVector->capacity = capacity;
    return flexVector;
}

void free_flexVector(FlexVector* flexVector) {
    free(flexVector);
}

FlexVector* add_flexVector(FlexVector* flexVector, int x) {
    require_not_null(flexVector);
    if (flexVector->count >= flexVector->capacity) { // if full, reallocate
        FlexVector* flexNew = vector_new(2 * flexVector->capacity); // duplicate capacity
        fprintf(stderr, "reallocating new capacity: %d ints\n", flexNew->capacity);
        memcpy(flexNew->data, flexVector->data, flexVector->count * sizeof(int));
        flexNew->count = flexVector->count;
        free(flexVector); // delete old vector
        flexVector = flexNew; // set new array
    }
    flexVector->data[flexVector->count++] = x;
    return flexVector;
}

int main(void) {
    report_memory_leaks(true);
    
    Vector* v = new_vector();
    for (int i = 0; i < 100; i++) {
        add_vector(v, i_rnd(100)); // add random numbers in range 0..99
    }
    printf("count = %d\n", count_vector(v));
    for (int i = 0; i < 100; i++) {
        printf("%d, ", get_vector(v, i));
    }
    printf("\n");
    
    free_vector(v);
    
    return 0;
}
