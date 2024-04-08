#include <stdio.h>
#include <stdlib.h>

#define MAX 100

int action_tbl[12][6] = {
    { 5, 0, 0, 4, 0, 0 },
    { 0, 6, 0, 0, 0, 999 },
    { 0, -2, 7, 0, -2, -2 },
    { 0, -4, -4, 0, -4, -4 },
    { 5, 0, 0, 4, 0, 0 },
    { 0, -6, -6, 0, -6, -6},
    { 5, 0, 0, 4, 0, 0 },
    { 5, 0, 0, 4, 0, 0 },
    { 0, 6, 0, 0, 11, 0 },
    { 0, -1, 7, 0, -1, -1 },
    { 0, -3, -3, 0, -3, -3 },
    { 0, -5, -5, 0, -5, -5 }
};

int goto_tbl[12][3] = {
    { 1, 2, 3 },
    { 0, 0, 0 },
    { 0, 0, 0 },
    { 0, 0, 0 },
    { 8, 2, 3 },
    { 0, 0, 0 },
    { 0, 9, 3 },
    { 0, 0, 10 },
    { 0, 0, 0 },
    { 0, 0, 0 },
    { 0, 0, 0 },
    { 0, 0, 0 }
};

char token_symbols[] = { 'd', '+', '*', '(', ')', '$' };

int stack[MAX], sp = 0;

int get_token_index(char token) {
    for (int i = 0; i < sizeof(token_symbols) / sizeof(token_symbols[0]); i++) {
        if (token_symbols[i] == token) return i;
    }
    return -1;
}

void push(int state) {
    if (sp < MAX - 1) {
        stack[++sp] = state;
    } else {
        printf("Error: Stack overflow.\n");
        exit(EXIT_FAILURE);
    }
}

int pop() {
    if (sp > 0) {
        return stack[sp--];
    } else {
        printf("Error: Stack underflow.\n");
        exit(EXIT_FAILURE);
    }
}

void LR_Parser(char *input) {
    int len = strlen(input), currentState, action, symbolIndex;
    char currentSymbol;
    stack[0] = 0; // Initial state

    for (int i = 0; i < len; i++) {
        currentSymbol = input[i];
        symbolIndex = get_token_index(currentSymbol);

        if (symbolIndex == -1) {
            printf("Syntax Error: Invalid symbol '%c'.\n", currentSymbol);
            return;
        }

        currentState = stack[sp];
        action = action_tbl[currentState][symbolIndex];

        if (action > 0) { // Shift
            push(action);
        } else if (action < 0) { // Reduce
            int rule = -action;
            // This part needs more information about the grammar to implement correctly
            printf("Reduce using rule %d.\n", rule);
            // A reduce action would typically involve popping the stack
            // and pushing a state based on the GOTO table.
            // Example for demonstration purposes:
            // pop(); // Pop the stack based on the rule's RHS length.
            // int gotoState = goto_tbl[stack[sp]][rule]; // Get the goto state.
            // push(gotoState); // Push the goto state onto the stack.
        } else if (action == 999) { // Accept
            printf("Parsing successful.\n");
            return;
        } else { // Error
            printf("Syntax Error.\n");
            return;
        }
    }
}

int main() {
    char input[MAX];
    printf("\nInput: ");
    scanf("%s", input);
    if (input[0] != '$') {
        LR_Parser(input);
    }
    return 0;
}

