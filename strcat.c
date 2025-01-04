#include <stdio.h>


#define S_LENGTH 100
#define T_LENGTH 50

void strcat_custom(char s[], char t[]) {
    /*
        example s: [1, 2, 3, 4]; t: [5, 6, 7]
        final s: [1, 2, 3, 4, 5, 6, 7]
    */

    int i, j;
    i = j = 0;

    for (i = 0; t[j] != '\0'; i++) {
        if (s[i] == '\0') {
            s[i] = t[j++];
            s[i + 1] = '\0';
        }
    }
}

void print_arrays(char s[], char t[]) {
    for (int i = 0; s[i] != '\0'; i++) {
        printf("%c ", s[i]);
    }
    printf("\n");

    for (int i = 0; t[i] != '\0'; i++) {
        printf("%c ", t[i]);
    }
    printf("\n");
}

int main() {
    char s[S_LENGTH];
    char t[T_LENGTH];
    int i, j;

    for (i = 0; i < 10; i++) {
        s[i] = 'a';
    }
    for (j = 0; j < 5; j++) {
        t[j] = 'b';
    }

    s[i] = t[j] = '\0';

    print_arrays(s, t);
    strcat_custom(s, t);
    print_arrays(s, t);

    return 0;
}