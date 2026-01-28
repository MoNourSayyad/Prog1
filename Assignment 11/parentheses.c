/*
    Compile: make parentheses
    Run: ./parentheses
    make parentheses && ./parentheses
*/

#include "../prog1lib/lib/base.h"
#include "dynamic_stack.h"

bool verify_parentheses(String text) {
    require("String shouldnt be empty", text != NULL);
    DynamicStack* stack = stack_new();
    char* p = text;
    while (*p != '\0') {
        char c = *p;
        if (c == '{' || c == '[' || c == '(' || c == '<') 
            stack_push(stack, c);
        else if (c == '}' || c == ']' || c == ')' || c == '>') {
            if (stack->size == 0) {
                stack_free(stack);
                return false;
            }
            char top = stack_pop(stack);
            if (c == '}' && top != '{' ||
                c == ']' && top != '[' ||
                c == ')' && top != '(' ||
                c == '>' && top != '<') {
                    stack_free(stack);
                    return false;
                }
        }
        p++;
    }
    bool weValidOrNah = (stack->size == 0);
    stack_free(stack);
    return weValidOrNah;
}

int main(void) {
    report_memory_leaks(true);

    test_equal_i(verify_parentheses(""), true);
    test_equal_i(verify_parentheses("Hello World"), true);
    test_equal_i(verify_parentheses("()"), true);
    test_equal_i(verify_parentheses("<{[()]}>"), true);
    test_equal_i(verify_parentheses("<{[)]}>"), false);
    test_equal_i(verify_parentheses("( Test ) "), true);
    test_equal_i(verify_parentheses("(1+2)*[2+3+(1 + 6/5)]"), true);
    test_equal_i(verify_parentheses("(an unmatched left parenthesis creates an unresolved tension that will stay with you all day"), false);
    test_equal_i(verify_parentheses("< [ > ]"), false);
    test_equal_i(verify_parentheses("<{[()]}"), false);
    test_equal_i(verify_parentheses("(<<({[({<{<({<([[[<[{(<{(<{{<[{<{{{<<{([<<<{{[{<<[[(([{[[[([(({()}))])]]]}]))]]>>}]}}>>>])}>>}}}>}]>}}>)}>)}]>]]])>})>}>})]})>>)"), true);

    return 0;
}
