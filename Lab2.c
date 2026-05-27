#include <stdio.h>
#include <string.h>
#include <stdbool.h>

bool checkValid(char str[]) {
    int len = strlen(str);

    if (len < 2)
        return false; // cannot satisfy start/end different

    char start = str[0];
    char end = str[len - 1];

    if ((start == 'a' && end == 'b') ||
        (start == 'b' && end == 'a')) {
        return true;
    }

    return false;
}

int main() {
    char str[100];

    printf("Enter string: ");
    scanf("%s", str);

    if (checkValid(str))
        printf("VALID\n");
    else
        printf("INVALID\n");

    return 0;
}