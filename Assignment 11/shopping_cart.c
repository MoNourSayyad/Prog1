/*
    Compile: make shopping_cart
    Run: ./shopping_cart
    make shopping_cart && ./shopping_cart
*/

#include "pointer_list.h"
#include "../prog1lib/lib/base.h"


typedef enum {
    C_FOOD,
    C_BOOK,
    C_ELECTRONICS,
} Category;

// Data definition for a shopping list item
typedef struct {
    String name;
    Category cat;
    // The price is given in cents
    // E.g.: a value of 1000 indicates a price of 10.00€
    int price;
} Item;

// String, Category (enum), int -> Item *
// Create an item (constructor).
Item* new_item(String name, Category cat, int price) {
    Item* item = xmalloc(sizeof(Item));

    *item = (Item) {
        .name = s_copy(name),
        .cat = cat,
        .price = price,
    };

    return item;
}

// Item* -> Item*
// Create a copy of an Item.
void* copy_item(void* x) {
    // TODO: a)
    Item* item = (Item*) x;
    Item* copiedItem = xmalloc(sizeof(Item));
    *copiedItem = (Item) {
        .name = s_copy(item->name),
        .cat = item->cat,
        .price = item->price  
    };
    return copiedItem;
}

// Item* -> String
// String representation of a shopping cart Item.
String item_to_string(void* x) {
    Item* item = (Item *) x;
    size_t n = 100 + s_length(item->name);
    String text = xmalloc(n);

    String cat_string = "unknown";
    switch(item->cat) {
    case C_FOOD:
        cat_string = "Food";
        break;
    case C_BOOK:
        cat_string = "Book";
        break;
    case C_ELECTRONICS:
        cat_string = "Electronics";
        break;
    }

    snprintf(text, n - 1, "\"%s\" (%s) %d.%0.2d EUR", item->name, cat_string, item->price / 100, item->price % 100);
    return text;
}

// Item* -> void
// Releases memory of an Item.
void free_item(void* x) {
    // TODO: a)
    Item* item = (Item*) x;
    free(item->name);
    free(item);
}

// Item* -> bool
// Returns true if the item is an electronic device.
bool is_electronics(void* element, int i, void* x) {
    // TODO: b)
    (void) x;
    (void) i;
    Item* item = (Item*) element;
    return item->cat == C_ELECTRONICS;
}

// Item* -> String
// Maps an Item to its name.
void* item_name(void* element, int i __attribute__((__unused__)), void* x __attribute__((__unused__))) { // we can also use this, but its limited for GNU and GCC.
    // TODO: d)
    Item* item = (Item*) element;
    return item->name;
}

// Item* -> bool
// Returns true if the price is less than *x.
bool price_less_than(void* element, int i, void* x) {
    // TODO: c)
    (void) i; // I added this so that we dont get a warning of an unused parameter 
    Item* item = (Item *)element;  // first we should specify what the generic pointer (to void) points to (Item) and store it in item.
    int a = *(int *)x; // same as the previous line but for int + we derefrence it and store it in a.
    return item->price < a;  // now we access that item and check whether it's less than 10 cents or no. Returns true or false. 
}

String StringtoString(void* element) {
    return s_copy((String) element);
}

int main(void) {
    report_memory_leaks(true);

    Item* i1 = new_item("Algorithms and Data Structures", C_BOOK, 7500);
    Item* i2 = new_item("Game Console", C_ELECTRONICS, 55000);
    Item* i3 = new_item("Potatoes", C_FOOD, 250);
    Item* i4 = new_item("Headphones", C_ELECTRONICS, 8000);

    printsln("= shopping cart =");
    Node* list = new_node(i1, new_node(i2, new_node(i3, new_node(i4, NULL))));
    println_list(list, item_to_string);

    printsln("= first electronics item =");
    Item* found_item = find_list(list, is_electronics, NULL);
    if (found_item != NULL) {
        String s = item_to_string(found_item);
        printsln(s);
        free(s);
    }

    printsln("= first item cheaper than 10 EUR =");
    // TODO: c)
    int limit = 1000;
    Item* lessThan10 = find_list(list, price_less_than, &limit);
    if (lessThan10 != NULL) {
        String s = item_to_string(lessThan10);
        printsln(s);
        free(s);
    }
    
    // for d example.

    Node* names = map_list(list, item_name, NULL);
    println_list(names, StringtoString);

    free_list(names, NULL);
    free_list(list, free_item);

    return 0;
}
// TODO: e)

// Pointer Lists are generally a perfect idea to print and change the list generically with a pointer to a void. Each datatype can be altered, printed, removed. They just need a specific, easy to write function. 
// Unlike array, they dont have a specific size too, the size is dynamically allocated, which is perfect.
// We can make use of important functions too, like map, filter, and reduce, which takes a generic type.
// However, some people find casting and using specifc functions to alter it (like for Strings we need scopy() or so) complicated.