#include "set.h"
#include "../prog1lib/lib/base.h"

typedef struct SetNode {
    void* element;
    struct SetNode* next;
} SetNode;

static SetNode* new_element(void* element, SetNode* next) {
    SetNode* node = xcalloc(1, sizeof(SetNode));
    node->element = element;
    node->next = next;
    return node;
}

struct Set {
    int n_buckets; // number of buckets
    SetNode** buckets; // array of buckets, length n (each element is a pointer to an element)
    int n_elements; // number of elements currently in the set
    HashFun hash;  // function for hashing
    EqualFun equal;  // function for equality checking
}; 

Set* new_set(int n_buckets, HashFun hash, EqualFun equal) {
    Set* s = xcalloc(1, sizeof(Set));
    s->n_buckets = n_buckets;
    s->buckets = xcalloc(n_buckets, sizeof(SetNode*));
    s->n_elements = 0;
    s->hash = hash;
    s->equal = equal;
    return s;
}

bool contains_set(Set* s, void* element) {
    int h = s->hash(element) % s->n_buckets;
    // walk through the list of bucket h
    for (SetNode* node = s->buckets[h]; node != NULL; node = node->next) {
        if (s->equal(element, node->element)) { // use equals method to compare elements
            return true; // found element
        }
    }
    return false; // element not found
}

void add_set(Set* s, void* element) {
    if (!contains_set(s, element)) { // do not allow multiple membership
        int h = s->hash(element) % s->n_buckets;
        // add element-value association to front of list in bucket h
        // (does not check whether element is already in set!)
        s->buckets[h] = new_element(element, s->buckets[h]);
        s->n_elements++; // one more element
    }
}

bool is_empty_set(Set* s) { 
    return s->n_elements == 0; 
}

int size_set(Set* s) { 
    return s->n_elements;
}

void free_set(Set* s, FreeFun free_element) {
    SetNode* next;
    for (int i = 0; i < s->n_buckets; i++) {
        for (SetNode* node = s->buckets[i]; node != NULL; node = next) {
            next = node->next;
            if (free_element != NULL) free_element(node->element);
            free(node); // SetNode structure
        }
    }
    free(s->buckets); // buckets array
    free(s); // Set structure
}

//////////////////////////////////////////////////////////////
// Iterator

struct Iterator {
    Set* s; // the set over which this iterator iterates
    int bucket_index; // current bucket list index
    SetNode* node; // current element in list
};

Iterator* new_iterator(Set* s) {
    Iterator* i = xcalloc(1, sizeof(Iterator));
    i->s = s;
    i->bucket_index = -1;
    i->node = NULL;
    return i;
}

bool has_next(Iterator* iter) { // does not change state of iterator
    if (iter->node != NULL && iter->node->next != NULL) { // in bucket list
        return true; // there is another element in this bucket list
    } else { // try next bucket lists // iteration hasn’t started yet (node == NULL), or we are at the end of a bucket’s list
        Set* s = iter->s;
        for (int i = iter->bucket_index + 1; i < s->n_buckets; i++) {
            if (s->buckets[i] != NULL) return true; // bucket i is not empty
        }
    }
    return false; // no more elements
}

void* next(Iterator* iter) { // modifies state of iterator
    if (iter->node != NULL && iter->node->next != NULL) {
        iter->node = iter->node->next; // advance to next pair
        return iter->node->element;
    } else {
        Set* s = iter->s;
        for (int i = iter->bucket_index + 1; i < s->n_buckets; i++) {
            if (s->buckets[i] != NULL) {
                iter->bucket_index = i; 
                iter->node = s->buckets[i]; // advance to next element
                return iter->node->element;
            }
        }
    }
    return NULL; // no more elements
}

void free_iterator(Iterator* iter) {
    free(iter);
}

//////////////////////////////////////////////////////////////
// a ∩ b
Set* intersect_set(Set* a, Set* b) { // takes two sets a and b, returns a new set, that new set will contain elements common to both a and b.
    if (a->hash != b->hash || a->equal != b->equal) { // both sets use the same hash and equality func. This ensures: both sets store the same type of elements
        printsln("Error: a and b have elements of different types"); // If not, comparing elements would be meaningless or unsafe.
        exit(1);
    }
    Set* result = new_set(a->n_buckets, a->hash, a->equal); // Ensures compatibility
    Iterator* iter = new_iterator(a); // traverse every element in set a
    while (has_next(iter)) { // continues as long as there is another element in a
        void* e = next(iter); // stores the current element in e. Here: e is one element from set a
        if (contains_set(b, e)) add_set(result, e); // whether the same element e also exists in set b 
    }
    free_iterator(iter);
    return result;
} 
