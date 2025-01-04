#include <stdio.h>


#define MAX_BUFFER_LENGTH 1000

void squeeze(char s[], int c) {
    /*
        example char s[] = [1, c, 3, 1, 4]; c = 1
        final char s[] = [c, 3, 4]
        in the end, s[j] = \0
    */

    int i, j;
    i = j = 0;

    for (i = 0; s[i] != '\0'; i++) {
        if (s[i] != c) {
            s[j++] = s[i];
        }
    }

    s[j] = '\0';
}

void print_buffer(char s[]) {
    for (int i = 0; s[i] != '\0'; i++) {
        printf("%c ", s[i]);
    }
    printf("\n");
}

int main() {
    int i, c;

    i = 0;

    char s[MAX_BUFFER_LENGTH];

    while ((c = getchar()) != EOF && c != '\n') {
        if (i >= MAX_BUFFER_LENGTH - 1) {
            printf("ERROR: ran out of buffer space to hold more characters");
            return 1;
        }
        if (c != ' ') {
            s[i++] = c;
        }
    }

    s[i] = '\0';

    printf("Enter the number/char you want to delete:\n");
    int d = getchar();
    
    print_buffer(s);
    squeeze(s, d);
    print_buffer(s);


    return 0;
}