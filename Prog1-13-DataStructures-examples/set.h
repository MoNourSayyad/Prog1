#ifndef __SET_H__
#define __SET_H__

#include "../prog1lib/lib/base.h"

typedef int (*HashFun)(void*);
typedef bool (*EqualFun)(void* object1, void* object2);
typedef void (*FreeFun)(void* object);


typedef struct Set Set; 

Set* new_set(int n_buckets, HashFun hash, EqualFun equal);

void add_set(Set* s, void* element);

bool is_empty_set(Set* s);

int size_set(Set* s);

bool contains_set(Set* s, void* element);

Set* intersect_set(Set* a, Set* b);

void free_set(Set* s, FreeFun free_element);


typedef struct Iterator Iterator;

Iterator* new_iterator(Set* s);

bool has_next(Iterator* iter);

void* next(Iterator* iter);

void free_iterator(Iterator* iter);

#endif
