#include <stdio.h>
#include <stdlib.h>
#include "../prog1lib/lib/base.h"
#define STACK_SIZE 100 // stack implemented as array, fixed capacity

typedef struct {
    double data[STACK_SIZE];
    int index; // next free stack entry
}Stack;

// Removes all values from the stack.
void clearStack(Stack* stack) {
    require_not_null(stack);
    stack->index = 0;
}

// Pushes a value on top of the stack.
void push(Stack* stack, double value) {
    require_not_null(stack);
    require("Stack aint full", stack->index < STACK_SIZE);
    stack->data[stack->index++] = value;
}

// Removes and returns value on top of the stack.
double pop(Stack* stack) {
    require_not_null(stack);
    require("Stack aint empty", stack->index > 0); // If index represents the number of elements (which your index > 0 check suggests), 
    return stack->data[--stack->index];           //  then the top element is at index - 1, not index.
}

// Checks whether the stack is empty.
bool is_empty(Stack* s) {
require_not_null(s);
return s->index <= 0;
}

typedef enum {
    UNKNOWN,
    OPERATOR,
    OPERAND,
    END
}TokenType;

typedef struct {
    TokenType type;
    char* start; // inclusive
    char* end;  // exclusive
}Token;

Token makeToken(TokenType tokenType, char* start, char* end) {
    return (Token) {tokenType, start, end};  // It does not own memory. It’s just a view.
}

// Applies the operator to the operands.
double apply(char operator, double operand1, double operand2) {
    switch (operator) {
        case '+': return operand1 + operand2;
        case '-': return operand1 - operand2;
        case '*': return operand1 * operand2;
        case '/': return operand1 / operand2;
        default: { 
            printf("Unknown operator: %c\n", operator);
            exit(1);
        }
    }
    return 0;
}

// May c appear in an operator?
bool is_operator_character(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/';
}

// May c appear in a floating point number?
bool is_operand_character(char c) {
    return c == '.' || c == '-' || (c >= '0' && c <= '9');
}

// Is c whitespace?
bool is_whitespace(char c) {
    return c == ' ' || c == '\t' || c == '\r' || c == '\n';
}

// End of string reached?
bool eos(char c) {
    return c == '\0';
}

// May c appear in a token?
bool is_token_character(char c) {
    return !eos(c) && !is_whitespace(c);
}

// Skips whitespace and returns a pointer to next 
// non-whitespace character (or end of string).
char* skip_whitespace(char* s) {
    while (is_whitespace(*s)) s++;
    assert("end of string reached or on first char of token", !is_whitespace(*s));
    return s;
}

// Skips token (non-whitespace) and returns pointer 
// to next whitespace character (or to end of string).
char* skip_token(char* s) {
    while (is_token_character(*s)) s++;
    assert("end of string reached or on first whitespace char after token", !is_token_character(*s));
    return s;
}

// Checks whether the chars from s (inclusive) to t (exclusive) are an operator.
bool is_operator(char* s, char* t) {
    return is_operator_character(*s) && t == s + 1;
}

// Checks whether the chars from s (inclusive) to t (exclusive) are an operand.
bool is_operand(char* s, char* t) {
    while (s < t) {
        if (!is_operand_character(*s)) return false;
        s++;
    }
    return true;
}

// Returns the next token.
Token next_token(char* s) {
    s = skip_whitespace(s);
    if (eos(*s)) return makeToken(END, NULL, NULL);
    assert("before end of string and on first char of token", is_token_character(*s));
    char* t = skip_token(s);
    assert("end of string reached or on first whitespace char after token", !is_token_character(*t));
    if (is_operator(s, t)) 
        return makeToken(OPERATOR, s, t);
    
    if (is_operand(s, t)) 
        return makeToken(OPERAND, s, t);
    
    return makeToken(UNKNOWN, s, t);
}

double evaluate(Stack* stack, char* expression) { // Evaluates the given postfix expression.
    double operand, operand1, operand2;
    char operator;
    while (true) {
        Token token = next_token(expression);
        switch (token.type) {
        case OPERAND: operand = atof(token.start); // atof: ascii to float, stdlib.h
                    push(stack, operand);
                    break;
        case OPERATOR: operator = token.start[0]; // we only have single-character, binary operators
                    operand2 = pop(stack);  // right operand
                    operand1 = pop(stack);  // left operand
                    push(stack, apply(operator, operand1, operand2));
                    break;
        case END: return pop(stack);  // final result
        case UNKNOWN: exit(1);
        }
        expression = token.end;  // continue after the current token   // move to next token
    }
}

int main(void) {
    Stack stack;       // not a pointer
    clearStack(&stack); // initialize    
    while (true) {
        // read line from standard input (at most 100 characters)
        char* expression = s_input(100); 
        // finish if input contains “exit”
        if (s_contains(expression, "exit")) break;
        // evaluate postfix expression using stack
        printdln(evaluate(&stack, expression));
    }
    return 0;
}