/*
    Compile: make wolf_goat_cabbage
    Run: ./wolf_goat_cabbage
    make wolf_goat_cabbage && ./wolf_goat_cabbage
*/

#include <stdio.h>
#include "../prog1lib/lib/base.h"
#include <math.h>

// Represents a single list node. The value is dynamically allocated. The node 
// is the owner of the value and has to free it when itself is released.
struct Node {
    String value; // dynamically allocated string, release memory!
    struct Node* next; // self-reference
};
typedef struct Node Node;

// Create a list node. Copies the value (into dynamically allocated storage).
Node* new_node(String value, Node* next) {
    Node* node = xcalloc(1, sizeof(Node));
    node->value = s_copy(value); // s_copy performs dynamic allocation
    node->next = next;
    return node;
}

// Prints the components of the given list.
void print_list(Node* list) {
    if (list == NULL) {
        printf("[]");
    } else {
        printf("[%s", list->value);
        for (Node* n = list->next; n != NULL; n = n->next) {
            printf(" %s", n->value);
        }
        printf("]");
    }
}

// Print list followed by a newline.
void println_list(Node* list) {
    print_list(list);
    printsln("");
}

// Free all nodes of the list, including the values it contains.
void free_list(Node* list) {
    // TODO: 3a)
    Node* current = list;
    while (current != NULL) {
        Node* next_node = current->next;

        free(current->value);

        free(current);

        current = next_node;
    }
}


bool test_equal_lists(int line, Node* list1, Node* list2);

/*
Example calls for test_equal_lists.
Expected output (line numbers may differ):
Line 63: The lists are equal.
Line 66: The lists are equal.
Line 70: The lists are equal.
Line 74: The values at node 0 differ: hello <-> you.
Line 78: The lists are equal.
Line 82: The values at node 1 differ: second <-> hello.
Line 86: list1 is shorter than list2.
Line 90: list1 is longer than list2.
*/
void test_equal_lists_test(void) {
    Node* list1 = NULL;
    Node* list2 = NULL;
    test_equal_lists(__LINE__, list1, list2);
    list1 = new_node("hello", NULL);
    list2 = list1;
    test_equal_lists(__LINE__, list1, list2);
    free_list(list1);
    list1 = new_node("hello", NULL);
    list2 = new_node("hello", NULL);
    test_equal_lists(__LINE__, list1, list2);
    free_list(list1); free_list(list2);
    list1 = new_node("hello", NULL);
    list2 = new_node("you", NULL);
    test_equal_lists(__LINE__, list1, list2);
    free_list(list1); free_list(list2);
    list1 = new_node("first", new_node("second", NULL));
    list2 = new_node("first", new_node("second", NULL));
    test_equal_lists(__LINE__, list1, list2);
    free_list(list1); free_list(list2);
    list1 = new_node("first", new_node("second", NULL));
    list2 = new_node("first", new_node("hello", NULL));
    test_equal_lists(__LINE__, list1, list2);
    free_list(list1); free_list(list2);
    list1 = new_node("first", new_node("second", NULL));
    list2 = new_node("first", new_node("second", new_node("third", NULL)));
    test_equal_lists(__LINE__, list1, list2);
    free_list(list1); free_list(list2);
    list1 = new_node("first", new_node("second", new_node("third", NULL)));
    list2 = new_node("first", new_node("second", NULL));
    test_equal_lists(__LINE__, list1, list2);
    free_list(list1); free_list(list2);
}

// Checking whether two string lists are equal.
bool test_equal_lists(int line, Node* list1, Node* list2) {
    // TODO: 3b)
    Node* n1 = list1;
    Node* n2 = list2;
    int index = 0;

    while (n1 != NULL && n2 != NULL) {
        if (!s_equals(n1->value, n2->value)) {
            printf("Line %d: The values at node %d differ: %s <-> %s.\n",
                   line, index, n1->value, n2->value);
            return false;
        }
        n1 = n1->next;
        n2 = n2->next;
        index++;
    }

    if (n1 == NULL && n2 != NULL) {
        printf("Line %d: list1 is shorter than list2.\n", line);
        return false;
    }
    if (n1 != NULL && n2 == NULL) {
        printf("Line %d: list1 is longer than list2.\n", line);
        return false;
    }

    printf("Line %d: The lists are equal.\n", line);
    return true;
}

int length_list(Node* list);

// Example calls for length_list (below).
void length_list_test(void) {
    // TODO: 3c)
     Node* list1 = NULL;
    test_equal_i(length_list(list1), 0);
    free_list(list1);

    Node* list2 = new_node("Amjad", NULL);
    test_equal_i(length_list(list2), 1);
    free_list(list2);

    Node* list3 = new_node("Amjad", new_node("Nouri", new_node("Ali", NULL)));
    test_equal_i(length_list(list3), 3);
    free_list(list3);
}

// Number of elements of the list.
int length_list(Node* list) {
    int n = 0;
    for (Node* node = list; node != NULL; node = node->next) n++;
    return n;
}

int index_list(Node* list, String s);

// Example calls for index_list (below).
void index_list_test(void) {
    // TODO: 3d)
    Node* list = new_node("Amjad", new_node("Nouri", new_node("Ali", NULL)));

    test_equal_i(index_list(list, "Amjad"), 0);
    test_equal_i(index_list(list, "Nouri"), 1);
    test_equal_i(index_list(list, "Ali"), 2);
 
    free_list(list);
}

// Return index of s in list, or -1 if s is not in list.
int index_list(Node* list, String s) {
    // TODO: 3d)
    require_not_null(s);

    int index = 0;

    for (Node* node = list; node != NULL; node = node->next) {
        if (s_equals(node->value, s)) {
            return index;
        }
        index++;
    }

    return -1;
}

// Check whether list contains s.
bool contains_list(Node* list, String s) {
    return index_list(list, s) >= 0;
}

Node* remove_list(Node* list, int index);

// Example calls for remove_list (below).
void remove_list_test(void) {
    // TODO: 3e)
     Node* list = new_node("Amjad", new_node("Nouri", new_node("Ali", NULL)));

    list = remove_list(list, 1);
    test_equal_i(length_list(list), 2);
    test_equal_s(list->value, "Amjad");
    test_equal_s(list->next->value, "Ali");

    list = remove_list(list, 0);
    test_equal_i(length_list(list), 1);
    test_equal_s(list->value, "Ali");

    list = remove_list(list, 0);
    test_equal_i(length_list(list), 0);

    free_list(list);
}

// Remove element at position index from list. The element at index has to be deleted.
Node* remove_list(Node* list, int index) {
    // TODO: 3e)
    require("index non-negative", index >= 0);
    require("index in range", index < length_list(list));
    
    ensure_code(int old_length = length_list(list));

    Node* result = list;

    if (index == 0) {
        Node* delete = list;
        result = list->next;
        
        free(delete->value);
        free(delete);
    } else {
        Node* prev = list;

        for (int i = 0; i < index - 1; i++) {
            prev = prev->next;
        }
        
        Node* delete = prev->next;
        prev->next = delete->next;
        
        free(delete->value);
        free(delete);
    }

    ensure("length decreased", length_list(result) == old_length - 1);
    
    return result;
}

///////////////////////////////////////////////////////////////////////////

// The boat may either be at the left or right river bank. 
// We don't care for the transition (boat crossing the river).
enum Position {
    LEFT, RIGHT
};

// The data that represents the state of the puzzle.
typedef struct {
    // List of objects on the left river bank.
    Node* left;

    // List of objects on the right river bank.
    Node* right;

    // List of objects in the boat. The boat has a capacity of one object only.
    Node* boat;

    // Current boat position.
    enum Position position;
} Puzzle;

// Initialize the state of the puzzle.
Puzzle make_puzzle(void) {
    return (Puzzle){ new_node("Wolf", new_node("Ziege", new_node("Kohl", NULL))), NULL, NULL, LEFT };
}

// Print the current state of the puzzle.
void print_puzzle(Puzzle* p) {
    print_list(p->left);
    if (p->position == RIGHT) prints("     ");
    print_list(p->boat);
    if (p->position == LEFT)  prints("     ");
    println_list(p->right);  
}

// Release memory and quit.
void finish_puzzle(Puzzle* p) {
    free_list(p->left);
    free_list(p->right);
    free_list(p->boat);
    exit(0);
}

void evaluate_puzzle(Puzzle* p) {
    // TODO: 2a)
    if (length_list(p->right) == 3) {
        prints("Congratulationssssssss! ");
        printsln("");
        finish_puzzle(p);
    }

    if (p->position == RIGHT) {
        if (contains_list(p->left, "Wolf") && contains_list(p->left, "Ziege")) {
            printsln("Game Over )):");
            finish_puzzle(p);
        } else if (contains_list(p->left, "Ziege") && contains_list(p->left, "Kohl")) {
            printsln("Game Over )):");
            finish_puzzle(p);
        }
    }

    if (p->position == LEFT) {
        if (contains_list(p->right, "Wolf") && contains_list(p->right, "Ziege")) {
            printsln("Game Over )):");
            finish_puzzle(p);
        } else if (contains_list(p->right, "Ziege") && contains_list(p->right, "Kohl")) {
            printsln("Game Over )):");
            finish_puzzle(p);
        }
    }
}

void play_puzzle(Puzzle* p) {
    // TODO: 2b)
       while (true) {
        print_puzzle(p);
        prints("> ");
        String input = s_input(100);

        if (s_equals(input, "q")) {
            free(input);
            finish_puzzle(p);
        } else if (s_equals(input, "l")) {
            p->position = LEFT;
        } else if (s_equals(input, "r")) {
            p->position = RIGHT;
        } else {
            String thing = NULL;
            if (s_equals(input, "w") || s_equals(input, "wolf")) thing = "Wolf";
            else if (s_equals(input, "g") || s_equals(input, "goat")) thing = "Ziege";
            else if (s_equals(input, "c") || s_equals(input, "cabbage")) thing = "Kohl";

            if (thing != NULL) {
                int boat_idx = index_list(p->boat, thing);
                if (boat_idx != -1) {
                    p->boat = remove_list(p->boat, boat_idx);
                    if (p->position == LEFT) p->left = new_node(thing, p->left);
                    else p->right = new_node(thing, p->right);
                } else {
                    if (length_list(p->boat) == 0) {
                        if (p->position == LEFT) {
                            int idx = index_list(p->left, thing);
                            if (idx != -1) {
                                p->left = remove_list(p->left, idx);
                                p->boat = new_node(thing, NULL);
                            }
                        } else {
                            int idx = index_list(p->right, thing);
                            if (idx != -1) {
                                p->right = remove_list(p->right, idx);
                                p->boat = new_node(thing, NULL);
                            }
                        }
                    }
                }
            }
        }
        free(input);
        evaluate_puzzle(p);
    }
}

///////////////////////////////////////////////////////////////////////////

int main(void) {
    report_memory_leaks(true);  // TODO: 2c)

    test_equal_lists_test();
    length_list_test();
    index_list_test();
    remove_list_test();
    
    Puzzle p = make_puzzle();
    play_puzzle(&p);
    return 0;
}

/* 
gcc wolf_goat_cabbage.c ../prog1lib/lib/base.c -o x
 
./x
 
*/