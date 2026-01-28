
/*
Compile: make weights
Run: ./weights
make weights && ./weights
*/

#include <stdio.h>
#include "../prog1lib/lib/base.h"

// 1 lb = 0.45359237 kg

typedef enum unit_e {
    G,
    KG,
    T,
    LB
} Unit;

typedef struct weight_s {
    double amount;
    Unit unit;
} Weight;

Weight make_weight(double amount, Unit unit) {
    Weight w;
    w.amount = amount;
    w.unit = unit;
    return w;
}

bool test_within_weight(int line, Weight a, Weight e, double tolerance) {
    bool x = base_test_within_d(__FILE__, line, a.amount, e.amount, tolerance);
    bool u = base_test_equal_i(__FILE__, line, a.unit, e.unit);
    return x && u;
}

void print_weight(Weight w) {
    printf("%.2f ", w.amount);

    switch (w.unit) {
        case G:
            printf("g\n");
            break;
        case KG:
            printf("kg\n");
            break;
        case T:
            printf("t\n");
            break;
        case LB:
            printf("lbs\n");
            break;
    }
}


void print_weight_test() {
    print_weight(make_weight(1234, G));
    print_weight(make_weight(4.749, KG));
    print_weight(make_weight(3.1001, T));
    print_weight(make_weight(5.40006, LB));
    printc('\n');
}

// Weight, Unit -> Weight
// Convert weight to the given target unit.
Weight to_unit(Weight w, Unit target_unit) {
    // Step 1: Convert to Kilograms (kg)
    double amount_in_kg = 0.0;
    
    switch (w.unit) {
        case G:
            amount_in_kg = w.amount / 1000.0;
            break;
        case KG:
            amount_in_kg = w.amount;
            break;
        case T:
            amount_in_kg = w.amount * 1000.0;
            break;
        case LB:
            // The conversion factor given in the file
            amount_in_kg = w.amount * 0.45359237; 
            break;
    }

    // Step 2: Convert from Kilograms to the target_unit
    double final_amount = 0.0;

    switch (target_unit) {
        case G:
            final_amount = amount_in_kg * 1000.0;
            break;
        case KG:
            final_amount = amount_in_kg;
            break;
        case T:
            final_amount = amount_in_kg / 1000.0;
            break;
        case LB:
            final_amount = amount_in_kg / 0.45359237;
            break;
    }

    // Step 3: Return the new Weight structure
    return make_weight(final_amount, target_unit);
}

void to_unit_test(void) {
    test_within_weight(__LINE__, to_unit(make_weight(1000, G), KG), make_weight(1, KG), 1e-6);
    test_within_weight(__LINE__, to_unit(make_weight(1.5, KG), G), make_weight(1500, G), 1e-6);
    test_within_weight(__LINE__, to_unit(make_weight(1, T), KG), make_weight(1000, KG), 1e-6);
    test_within_weight(__LINE__, to_unit(make_weight(1, LB), KG), make_weight(0.45359237, KG), 1e-6);
    test_within_weight(__LINE__, to_unit(make_weight(50, KG), KG), make_weight(50, KG), 1e-6);
}


// Weight, Weight -> int
// Compares two weights. Returns 0 if the two weights are equal, 
// -1 if w is smaller than v and +1 otherwise.
int compare(Weight w, Weight v) {
    double a = to_unit(w, KG).amount;
    double b = to_unit(v, KG).amount;

    double eps = 1e-8;

    if (a > b + eps) {
        return 1;
    } 
    else if (a < b - eps) {
        return -1;
    } 
    else {
        return 0;
    }
}

void compare_test(void) {
    test_equal_i(compare(make_weight(750, G), make_weight(1, KG)), -1);
    test_equal_i(compare(make_weight(3, KG), make_weight(2500, G)), 1);
    test_equal_i(compare(make_weight(0.2, T), make_weight(200, KG)), 0);
    test_equal_i(compare(make_weight(5, LB), make_weight(3, KG)), -1);
    test_equal_i(compare(make_weight(50, KG), make_weight(120, LB)), -1);
}


int main(void) {
    print_weight_test();
    to_unit_test();
    compare_test();
    return 0;
}

/* 
gcc Ex.c ../prog1lib/lib/base.c -o Ex 

./Ex
 
*/