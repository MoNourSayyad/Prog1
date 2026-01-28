
/*
Compile: make loops
Run: ./loops
make loops && ./loops
*/

#include <stdio.h>
#include "../prog1lib/lib/base.h"

int n;

// 3a)
void loops_a(int n) {
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= i; j++) {
            printf("%d ", j);
        }
        printf("\n");
    }
    printf("\n");
}

// 3b)
void loops_b(int n) {
    for (int i = 1; i <= n; i++) {
        for (int s = 0; s < n - i; s++) {
            printf("  "); 
        }
        for (int j = 1; j <= i; j++) {
            printf("%d ", j);
        }
        printf("\n");
    }
    printf("\n");
}

// 3c)
void loops_c(int n) {
    for (int i = 1; i <= n; i++) {
        for (int s = 0; s < n - i; s++) { 
            printf(" ");
        }
        for (int j = 1; j <= i; j++) {
            printf("%d ", j);
        }
        printf("\n");
    }
    printf("\n");
}

// 3d)
void loops_d(int n) {
    int mid = n / 2;

    for (int i = 0; i < n; i++) {
        int value;
        if (i <= mid)
            value = i;
        else
            value = n - 1 - i;
            
        for (int s = 0; s < value; s++) {
            printf("   ");
        }

        printf("%d", value);

        int innere_bereiche = 2 * (mid - value);

        for (int s = 0; s < innere_bereiche; s++) {
            printf("   ");
        }

        if (innere_bereiche > 0)
            printf("%d", value);

        printf("\n");
    }
    printf("\n");
}

// 3e)
void loops_e(int n) {

    printf("    ");
    printf("+");
    for (int i = 0; i < n - 2; i++)
        printf("--");
    printf("+\n");

    for (int Zeile = 1; Zeile < 4; Zeile++) {
        for (int s = 0; s < 4 - Zeile; s++)
            printf(" ");
        printf("/");

        for (int i = 0; i < n - 2; i++)
            printf("  ");

        printf("/");
        printf("\n");
    }

    printf("+");
    for (int i = 0; i < n - 2; i++)
        printf("--");
    printf("+\n");
}

int main() {
    loops_a(5);
    loops_b(5);
    loops_c(5);
    loops_d(5);
    loops_a(9);
    loops_b(9);
    loops_c(9);
    loops_d(9);
    loops_e(3);
    loops_e(4);
    loops_e(5);
    loops_e(9);
    loops_e(12);
    return 0;
}