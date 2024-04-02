#include <stdio.h>
#include <stdlib.h>

#define MAX 32
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

char lhs[] = {'E', 'E', 'T', 'T', 'F', 'F'};
int rhs_len[] = {3, 1, 3, 1, 3, 1};
char tokens[] = {'+', '*', '(', ')', 'd', '$'}; 
int stack[MAX], sp = -1;

int get_token_index(char symbol) {
    for (int i = 0; i < sizeof(tokens) / sizeof(char); ++i) {
        if (tokens[i] == symbol) return i;
    }
    return -1; // Symbol not found
}

void push(int state) {
    if (sp < MAX - 1) {
        stack[++sp] = state;
    } else {
        printf("Error: Stack overflow.\n");
        exit(EXIT_FAILURE);
    }
}

// Updated reduce function to correctly calculate the goto index
void reduce(int rule) {
    sp -= rhs_len[rule - 1];
    int lhs_index = (lhs[rule - 1] == 'E') ? 1 : (lhs[rule - 1] == 'T') ? 2 : 3; // Adjusted for zero-based index
    int goto_state = goto_tbl[stack[sp]][lhs_index - 1]; // Adjust for zero-based index in goto_tbl
    push(goto_state);
}

void LR_Parser(char *input) {
    sp = 0;
    stack[sp] = 0;
    int i = 0, action, symbolIndex, state;
    char symbol = input[i];

    // Adjust loop condition to handle end-of-input correctly
    while (symbol != '\0') {
        state = stack[sp];
        symbolIndex = get_token_index(symbol);
        if (symbolIndex == -1) {
            printf("Syntax Error: Unknown symbol '%c'.\n", symbol);
            return;
        }

        action = action_tbl[state][symbolIndex];
        
        if (action > 0) { // Shift
            push(action);
            symbol = input[++i]; // Advance to the next symbol
        } else if (action < 0) { // Reduce
            reduce(-action);
            // No input advancement here
        } else if (action == 999) { // Accept
            printf("Parsing successful.\n");
            return;
        } else { // Error
            printf("Syntax Error.\n");
            return;
        }

        // Handle case where reduction leads to acceptance
        if (symbol == '$') {
            action = action_tbl[stack[sp]][5]; // Index for '$'
            if (action == 999) {
                printf("Parsing successful.\n");
                return;
            }
        }
    }
}

int main() {
    char input[MAX];
    printf("Enter: ");
    scanf("%99s", input); // Read input
    LR_Parser(input);
    return 0;
}

