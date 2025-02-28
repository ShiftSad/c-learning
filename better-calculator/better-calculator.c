#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Thanks to https://stackoverflow.com/questions/71369018/using-c-to-determine-if-a-string-contains-any-imbalanced-brackets
const char *check_brace(const char str[], int endc) {
    while (str) {
        int c = *str++;
        switch (c) {
          case '(': str = check_brace(str, ')'); break;
          case '[': str = check_brace(str, ']'); break;
          case '{': str = check_brace(str, '}'); break;
          case ')':
          case ']':
          case '}':
          case '\0': return (c == endc) ? str : NULL;
        }
    }
    return NULL;
}

int balanced(const char *line) {
    return check_brace(line, '\0') != NULL;
}

int main() {
    char input[128];
    printf("Type operation: ");

    fgets(input, sizeof(input), stdin);
    input[strlen(input) - 1] = '\0'; // Remove \n at the last character

    // Remove spaces
    int temp = 0;
    char operation[sizeof(input)];
    for (int i = 0; i < strlen(input); i++) {
        // 32 is the unicode for space
        if (input[i] != 32) operation[temp++] = input[i];
    }

    // Check if braces are valid
    printf("Are braces valid? %i\n", balanced(operation));

    return 0;
}