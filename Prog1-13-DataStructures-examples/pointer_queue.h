/** @file
A queue that points to elements of arbitrary type.
@author Michael Rohs
@date 20.1.2018
*/

#ifndef __POINTER_QUEUE_H__
#define __POINTER_QUEUE_H__

#include "../prog1lib/lib/base.h"

// Opaque type. Actual components specified in .c-file.
typedef struct Queue Queue;

/** 
Creates an empty stack.
@return the dynamically allocated queue
*/
Queue* new_queue(void);

/** 
Free the queue itself, but not the elements.
@param q the queue
*/
void free_queue(Queue* q);

/** 
Adds element x to the back of the queue.
@param[in,out] q the queue
@param[in] x element to enqueue
*/
void put_queue(Queue* q, void* x);

/** 
Gets the next element from the front of the queue.
@param[in,out] q the queue
@return the element at the front of the queue
*/
void* get_queue(Queue* q);

/**
Checks if the queue is empty.
@param[in] q the queue
@return true if the queue is empty, false otherwise
*/
bool is_empty_queue(Queue* q);

#endif
