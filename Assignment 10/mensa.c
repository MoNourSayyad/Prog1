

/*
    Compile: make mensa
    Run: ./mensa
    Compile & run: make mensa && ./mensa
*/

#include "../prog1lib/lib/base.h"

/**
Represents a single list node. The string value is dynamically allocated. 
The node is the owner of the value and has to free it when released.
*/
struct Node {
    String value; // dynamically allocated string, release memory!
    struct Node* next; // self-reference
};
typedef struct Node Node;

/**
Create a list node. Copies the value (into dynamically allocated storage).
*/
Node* new_node(String value, Node* next) {
    Node* node = xcalloc(1, sizeof(Node));
    node->value = s_copy(value); // s_copy performs dynamic allocation
    node->next = next;
    return node;
}

/**
Prints the components of the given list.
*/
void print_list(Node* list) {
    if (list == NULL) {
        printf("[]");
    } else {
        printf("[%s", list->value);
        for (Node* n = list->next; n != NULL; n = n->next) {
            printf(", %s", n->value);
        }
        printf("]");
    }
}

/**
Print list followed by a newline.
*/
void println_list(Node* list) {
    print_list(list);
    printsln("");
}

/**
Return the number of elements in the list.
*/
int length_list(Node* list) {
    // TODO: implement (a)
    int n = 0;
    for (Node* node = list; node != NULL; node = node->next){
      n++;
    }
    return n;
}

/**
Return the element at position.
*/
String get_list(Node* list, int position) {
    // TODO: implement (b)
    int current = 0;
    for (Node* node = list; node != NULL; node = node->next) {
        if (current == position) {
            return node->value;
        }
        current++;
    }
    return NULL;
}

/**
Free all nodes of the list, including the values it contains.
*/
void free_list(Node* list) {
    // TODO: implement (c)
    Node* current = list;
    while (current != NULL) {
        Node* next = current->next;
        free(current->value); 
        free(current);        
        current = next;
    }
}

/**
Adds an element to the end of the list. Modifies the existing list.
*/
Node* append_list(Node* list, String value) {
    // TODO: implement (d)
   Node* new_el = new_node(value, NULL); 
   
    if (list == NULL) {
        return new_el; 
    }
   
    Node* current = list;
    while (current->next != NULL) {
        current = current->next;
    }

    current->next = new_el;
    return list;
}

// Remove element at position index from list. The element at index has to be deleted.
Node* remove_list(Node* list, int index) {
    if (list == NULL || index < 0) return list;
    if (index == 0) { // remove first element of non-empty list
        Node* n = list->next;
        free(list->value);
        free(list);
        return n;
    }
    // return second or later element of non-empty list
    int i = 0;
    for (Node* node = list; node != NULL; node = node->next) {
        if (i + 1 == index) {
            Node* to_remove = node->next;
            if (to_remove == NULL) return list;
            Node* n = to_remove->next;
            free(to_remove->value);
            free(to_remove);
            node->next = n;
            return list;
        }
        i++;
    }
    return list;
}

/**
Today's menu.
*/
const String menu[] = { "Schnitzel", "Pasta", "Veggie", "Dessert", "Salat" };

/**
The number of items on the menu.
*/
const int menu_count = sizeof(menu) / sizeof(char*);

/**
The list of completed food from the kitchen, waiting to be served. Each time a food item is served, the kitchen prepares a new food item randomly from the menu.
*/
Node* food; // List(String)

/**
The list of students standing in line and waiting for food. Each entry contains a string for the food that this student wants.
*/
Node* students; // List(String)

/**
The reputation of the mensa. The player is a staff member of the mensa. The goal of the player is to maximize the reputation of the mensa. Actually serving a dish that was asked for increases the reputation of the mensa by 1. Serving the wrong dish decreases the reputation by 1. If a student asks for a dish that is on the menu but not ready to be served, the reputation of the mensa decreases by 2.
*/
int reputation = 0;

/**
Example output:
fertige Essen: [Pasta, Veggie, Salat, Salat, Veggie]
nächster Essenswunsch: Schnitzel (3 hungrige Studierende warten)
Reputation der Mensa: 0
> 
*/
void print_situation(void) {
    // TODO: implement (e)
    printf("fertige Essen: ");
    print_list(food);
    printf("\n");

    if (students != NULL) {
        printf("next Essenswunsch: %s (%d hungrige Studierende warten)\n", 
               students->value, length_list(students));
    }
    printf("Reputation: %d\n> ", reputation);
}

/**
Print final message, release all dynamically allocated memory, and exit the program.
Fertig für heute. Die Mensa schließt.
Finale Reputation der Mensa: 3
*/
void finish(void) {
    // TODO: implement (f)
    printf("Done for today. THe Mensa is closing.\n");
    printf("Final Reputation: %d\n", reputation);

    free_list(food);
    free_list(students);
    exit(0);
}

/**
Run the mensa simulation.

The mensa person then enters the (0-based) index from the list of food. -1 stands for "not available". -2 ends the program. 

Here is an example dialog:

fertige Essen: [Salat, Veggie, Veggie, Pasta, Dessert]
nächster Essenswunsch: Pasta (3 hungrige Studierende warten)
Reputation der Mensa: 0
> 3
Vielen Dank! Ich liebe die Mensa!
fertige Essen: [Salat, Veggie, Veggie, Dessert, Dessert]
nächster Essenswunsch: Pasta (3 hungrige Studierende warten)
Reputation der Mensa: 1
> -1
Pasta ist nicht da? Schade.
fertige Essen: [Salat, Veggie, Veggie, Dessert, Dessert]
nächster Essenswunsch: Salat (2 hungrige Studierende warten)
Reputation der Mensa: -1
> 0
Vielen Dank! Ich liebe die Mensa!
fertige Essen: [Veggie, Veggie, Dessert, Dessert, Dessert]
nächster Essenswunsch: Dessert (2 hungrige Studierende warten)
Reputation der Mensa: 0
> 1
Veggie möchte ich nicht! Ich möchte Dessert!
fertige Essen: [Veggie, Veggie, Dessert, Dessert, Dessert]
nächster Essenswunsch: Schnitzel (1 hungrige Studierende warten)
Reputation der Mensa: -1
> 1
Veggie möchte ich nicht! Ich möchte Schnitzel!
Fertig für heute. Die Mensa schließt.
Reputation der Mensa: -2
*/


void run_mensa(void) {
    // TODO: implement
    // create 5 random food items from the menu
    // ...

    // create 3 random food wishes from the menu (each wish from one student)
    // ...
   
     for (int i = 0; i < 5; i++) {
        food = append_list(food, menu[i_rnd(menu_count)]);
        
    }
    for (int i = 0; i < 3; i++) {
        students = append_list(students, menu[i_rnd(menu_count)]);
    }
    
    print_situation();
    
    int i;
    while ((i = i_input()) >= -1) {
        // process input
        // distinguish different cases, update lists
        // use get_list, remove_list, append_list, length_list
        // use i_rnd to select random food items and random food wishes
        // use s_equals or strcmp to compare strings

       
        if (i == -1) {
            if (students != NULL) {
                printf("%s ist nicht da? Schade.\n", students->value);
                
                reputation -= 2;
                students = remove_list(students, 0); 
            }
            } else if (i >= 0 && i < length_list(food)) {
                String served = get_list(food, i);
                String wish = students->value;

                if (s_equals(served, wish)) {
                    printf("Vielen Dank! Ich liebe di Mensa!\n");

                    reputation += 1;
                        food = remove_list(food, i);
                        food = append_list(food, menu[i_rnd(menu_count)]);

                        students = remove_list(students, 0);
                        students = append_list(students, menu[i_rnd(menu_count)]); 
                } else {
                    printf("%s moechte ich nicht! Ich moechte %s!!!!\n", served, wish);
                    
                    reputation -= 1;
                    
                }
        }
        print_situation();
    }
finish();
}

int main(void) {
    report_memory_leaks(true);
    run_mensa();
    return 0;
}

/*
gcc mensa.c ../prog1lib/lib/base.c -o amja

./amja
*/