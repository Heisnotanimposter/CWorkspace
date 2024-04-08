#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include "goto_tbl.h"
#include "action_tbl.h"
#include "RHS.h"
#include "NT.h"

#define MAX 100


void LR_Parser(const char *input);

int main() {
    char input[MAX];

    while (1) {
        printf("\nEnter input string (start with $ to end): ");
        
        // Using fgets to prevent buffer overflow
        if (!fgets(input, MAX, stdin)) {
            // Handle error
            continue;
        }
        
        // Remove the newline character if present
        input[strcspn(input, "\n")] = '\0';
        
        // Break the loop if the input string starts with '$'
        if (input[0] == '$') {
            break;
        }

        // Call the parsing function with the input
        LR_Parser(input);
    }


    return 0;
}


//gcc -o LRParser main.c grammar.c tables.c lr_parser.c
//./LRParser
