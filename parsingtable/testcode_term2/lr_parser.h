#define LR_PARSER_H

#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include "goto_tbl.h"
#include "action_tbl.h"
#include "RHS.h"
#include "NT.h"

void LR_Parser(char *input) {
    sp = 0; // Stack pointer initialization
    stack[sp] = 0; // Initial state
    
    int inputPos = 0;
    bool accepted = false;
    char currentToken;
    int currentState, action, rule;

    while (!accepted) {
        currentToken = input[inputPos];
        currentState = stack[sp];
        action = action_tbl[currentState][currentToken];

        printf("Input: ");
        printInput(input, inputPos);

        // Assuming token 'd' corresponds to an identifier and '$' is the end marker.
        if (action >= 1 && action <= MAX) { // Shift action
            printf("shift %d: ", action);
            printStack(stack, sp);
            // Shift action would push the new state onto the stack
            stack[++sp] = action;
            inputPos++; // Move to the next character in the input
        } else if (action <= -1 && action >= -MAX) { // Reduce action
            rule = -action;
            printf("reduce %d: ", rule);
            printStack(stack, sp);
            // The reduce action would involve popping the stack and performing a goto
            sp -= rhs_len[rule];
            stack[++sp] = goto_tbl[stack[sp-1]][lhs[rule]]; // Not shown in output, assumed behavior
        } else if (action == 999) { // Accept action
            printf("accept\n");
            accepted = true;
        } else {
            printf("error\n");
            break;
        }
    }
}