/*
    Compile: make pointer_list_ext
    Run: ./pointer_list_ext
    make pointer_list_ext && ./pointer_list_ext
    gcc pointer_list_ext.c ../prog1lib/lib/base.c -o pointer_list_ext  
*/
/*
gcc pointer_list_ext.c ../prog1lib/lib/base.c -I../prog1lib/lib -o pointer_list_ext
./pointer_list_ext
*/
#include "../prog1lib/lib/base.h"
#include "pointer_list.h"

// String -> String
// Copies a string for printing (and later release).
String string_to_string(void* x) {
    return s_copy(x);
}

// String -> voidtake_list
// Releases a string.
void free_string(void* x) {
    free(x);
}

// Create a list consisting of the first n nodes of list.
Node* take_list(Node* list, int n) {
    // TODO: a)
    if (n <= 0 || list == NULL) {
        return NULL;
    }
    Node* newlist=new_node(list-> value, NULL);
    Node* current_new = newlist;
    Node* current_orginal = list->next;
     for (int i = 1; i < n && current_orginal != NULL; i++) {
        current_new->next = new_node(current_orginal->value, NULL);
        current_new = current_new->next;
        current_orginal = current_orginal->next;
    }
    return newlist;
}

// Create a list consisting of nodes of list, except the first n.
Node* drop_list(Node* list, int n) {
    // TODO: b)
    Node* current = list;
    for (int i = 0; i < n && current != NULL; i++) {
        current = current->next; 
    }


    if (current == NULL) {
        return NULL;
    }

    return copy_list(current, NULL);
}


// Take alternatingly from list1 and list2 until all data is collected in the result.
Node* interleave(Node* list1, Node* list2) {
    // TODO: c)
    if (list1 == NULL) return copy_list(list2, NULL);
    if (list2 == NULL) return copy_list(list1, NULL);

    Node* result = new_node(list1->value, NULL);
    Node* current_new = result;
    Node* p1 = list1->next; 
    Node* p2 = list2;

    while (p1 != NULL || p2 != NULL) {
        if (p2 != NULL) {
            current_new->next = new_node(p2->value, NULL);
            current_new = current_new->next;
            p2 = p2->next;
        }
        if (p1 != NULL) { 
            current_new->next = new_node(p1->value, NULL);
            current_new = current_new->next;
            p1 = p1->next;
        }
    }
    return result;
}

// typedef bool (*EqualFun)(void* element1, void* element2);

bool group_by_length(void* element1, void* element2) {
    String s1 = element1;
    String s2 = element2;
    return s_length(s1) == s_length(s2);
}

// Group elements in list. Equivalent elements (for which equivalent is true) are put
// in the same group. The result is a list of groups. Each group is itself a list.
// Each group contains items that are equivalent.
Node* group_list(Node* list, EqualFun equivalent) {
    // TODO: d)

if (list == NULL) return NULL;

    Node* groups = NULL; 
    Node* current = list;

    while (current != NULL) {
        void* val = current->value;

     
        Node* group_node = groups;
        bool found = false;

        while (group_node != NULL) {
            Node* sub_list = group_node->value;
            if (equivalent(val, sub_list->value)) {
                group_node->value = append_list(sub_list, val);
                found = true;
                break;
            }
            group_node = group_node->next;
        }

      
        if (!found) {
            Node* new_sub_list = new_node(val, NULL);
            groups = append_list(groups, new_sub_list);
        }

        current = current->next;
    }

    return groups;
}

void free_group(void* x) {
    Node* list = x;
    free_list(list, NULL);
}

int main(void) {
    report_memory_leaks(true);

    Node* list = new_node("a", new_node("bb", new_node("ccc", new_node("dd", new_node("e", NULL)))));
    println_list(list, string_to_string);

    prints("take_list: ");
    Node* list2 = take_list(list, 3);
    println_list(list2, string_to_string);

    prints("drop_list: ");
    Node* list3 = drop_list(list, 3);
    println_list(list3, string_to_string);

    prints("interleave: ");
    Node* list4 = interleave(list2, list3);
    println_list(list4, string_to_string);
    free_list(list2, NULL);
    free_list(list3, NULL);
    free_list(list4, NULL);

    Node* groups = group_list(list, group_by_length);
    printf("%d groups:\n", length_list(groups));
    for (Node* n = groups; n != NULL; n = n->next) {
        println_list(n->value, string_to_string);
    }

    free_list(groups, free_group);
    free_list(list, NULL);

    return 0;
}
/*
gcc pointer_list_ext.c ../prog1lib/lib/base.c -I../prog1lib/lib -o pointer_list_ext
./pointer_list_ext
*/