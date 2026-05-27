#include <stdio.h>
#include <ctype.h>
#include <string.h>

int isOperator2(char a, char b) {
    char op[3] = {a, b, '\0'};

    return (!strcmp(op, "==") ||
            !strcmp(op, "!=") ||
            !strcmp(op, "<=") ||
            !strcmp(op, ">=") ||
            !strcmp(op, "&&") ||
            !strcmp(op, "||") ||
            !strcmp(op, "++") ||
            !strcmp(op, "--"));
}

int main() {

    FILE *fp;
    char ch, next;
    char buffer[100];
    int i;

    fp = fopen("File.txt", "r");

    if(fp == NULL) {
        printf("File not found\n");
        return 0;
    }

    printf("\n---------------------------------\n");
    printf("| %-15s | %-12s |\n", "LEXEME", "TOKEN");
    printf("---------------------------------\n");

    while((ch = fgetc(fp)) != EOF) {

        if(ch == ' ' || ch == '\n' || ch == '\t')
            continue;

        if(isalpha(ch)) {

            i = 0;

            do {
                buffer[i++] = ch;
                ch = fgetc(fp);
            } while(isalpha(ch) || isdigit(ch));

            buffer[i] = '\0';

            if(ch != EOF)
                ungetc(ch, fp);

            if(strcmp(buffer, "int") == 0 ||
               strcmp(buffer, "float") == 0 ||
               strcmp(buffer, "char") == 0)
            {
                printf("| %-15s | %-12s |\n", buffer, "KEYWORD");
            }
            else {
                printf("| %-15s | %-12s |\n", buffer, "IDENTIFIER");
            }
        }

        else if(isdigit(ch)) {

            i = 0;

            do {
                buffer[i++] = ch;
                ch = fgetc(fp);
            } while(isdigit(ch));

            buffer[i] = '\0';

            if(ch != EOF)
                ungetc(ch, fp);

            printf("| %-15s | %-12s |\n", buffer, "NUMBER");
        }

       else if(strchr("+-*/%=<>!&|^", ch)) {

            next = fgetc(fp);

            char op[3];

            if(isOperator2(ch, next)) {
                op[0] = ch;
                op[1] = next;
                op[2] = '\0';
            }
            else {
                op[0] = ch;
                op[1] = '\0';

                if(next != EOF)
                    ungetc(next, fp);
            }

            printf("| %-15s | %-15s |\n", op, "OPERATOR");
        }

        else if(ch == '=') {

            printf("| %-15c | %-12s |\n", ch, "ASSIGNMENT");
        }

        else if(ch == ';' || ch == ',' || ch == '(' || ch == ')') {

            printf("| %-15c | %-12s |\n", ch, "DELIMITER");
        }
    }

    printf("---------------------------------\n");

    fclose(fp);

    return 0;
}