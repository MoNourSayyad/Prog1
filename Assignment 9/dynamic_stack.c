/*
    Compile: make dynamic_stack
    Run: ./dynamic_stack
    make dynamic_stack && ./dynamic_stack
*/

#include "../prog1lib/lib/base.h"


typedef struct dynamic_stack_s {
    // TODO: a)
    int* values;
    int size;
    int capacity;
} DynamicStack;

DynamicStack* stack_new() {
    // TODO: b) 
    DynamicStack* stack = xmalloc(sizeof(DynamicStack));
    stack->values = NULL;
    stack->size = 0;
    stack->capacity = 0;
    return stack;
}

void stack_free(DynamicStack* stack) {
    // TODO: e)
    if (stack == NULL)
        return;
    if (stack->values != NULL)
        free(stack->values);
    free(stack);
    
}

void stack_push(DynamicStack* stack, int value) {
    // TODO: c)
    if (stack->size == stack->capacity) {
        int newCapacity = (stack->capacity == 0) ? 1 : stack->capacity * 2;  // A new format i learned recently :) 
    // and I find that it's a good practice to double the capactity when it's full.
    int* newValues = xrealloc(stack->values, newCapacity * sizeof(int)); // I also recently learned that realloc is a func that's used for Increasing the spaced of allocated area. (xrealloc is in Proglib)
    stack->values = newValues;
    stack->capacity = newCapacity;
    }
    stack->values[stack->size] = value;
    stack->size++;
}

int stack_pop(DynamicStack* stack) {
    // TODO: d)
    if (stack->size == 0)
        return 0;
    stack->size--; // Cuz its an array from 0 to n-1
    return stack->values[stack->size]; 
}

void test_stack_ops(DynamicStack* stack) {
    stack_push(stack, 42);
    stack_push(stack, 1);
    stack_push(stack, 13);
    test_equal_i(stack_pop(stack), 13);
    test_equal_i(stack_pop(stack), 1);
    stack_push(stack, 400);
    stack_push(stack, 500);
    stack_push(stack, 600);
    stack_push(stack, 700);
    test_equal_i(stack_pop(stack), 700);
    test_equal_i(stack_pop(stack), 600);
    test_equal_i(stack_pop(stack), 500);
    test_equal_i(stack_pop(stack), 400);
    test_equal_i(stack_pop(stack), 42);
    test_equal_i(stack_pop(stack), 0);
}

int main(void) {
    DynamicStack* stack = stack_new();
    test_stack_ops(stack);
    stack_free(stack);
    DynamicStack* stack2 = stack_new();
    stack_free(stack2);
}
