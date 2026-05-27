#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX 10

int main() {
    char A;
    char prod[MAX][MAX];
    char alpha[MAX][MAX], beta[MAX][MAX];
    int n, i;

    int alphaCount = 0, betaCount = 0;
    bool hasLeftRecursion = false;

    printf("Enter non-terminal (e.g., A): ");
    scanf(" %c", &A);

    printf("Enter number of productions: ");
    scanf("%d", &n);

    printf("Enter productions (e.g., Aa or b):\n");

    for (i = 0; i < n; i++) {
        scanf("%s", prod[i]);

        // Check left recursion
        if (prod[i][0] == A) {
            hasLeftRecursion = true;
            strcpy(alpha[alphaCount++], prod[i] + 1); // remove A
        } else {
            strcpy(beta[betaCount++], prod[i]);
        }
    }

    // If no left recursion
    if (!hasLeftRecursion) {
        printf("\nNo left recursion found.\n");
        printf("%c -> ", A);
        for (i = 0; i < n; i++) {
            printf("%s", prod[i]);
            if (i < n - 1) printf(" | ");
        }
        return 0;
    }

    // Remove left recursion
    printf("\nAfter removing left recursion:\n");

    // A → βA'
    printf("%c -> ", A);
    for (i = 0; i < betaCount; i++) {
        printf("%s%c'", beta[i], A);
        if (i < betaCount - 1) printf(" | ");
    }

    // A' → αA' | ε
    printf("\n%c' -> ", A);
    for (i = 0; i < alphaCount; i++) {
        printf("%s%c' | ", alpha[i], A);
    }
    printf("ε\n");

    return 0;
}