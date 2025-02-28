#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    char input[128];
    printf("Type operation: ");

    fgets(input, sizeof(input), stdin);
    input[strlen(input) - 1] = '\0'; // Remove \n at the last character

    // Remove spaces
    
    for (int i = 0; i < strlen(input); i++) {

    }

    return 0;
}