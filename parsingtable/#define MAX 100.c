#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAX 100
int action_tbl[12][6] = {
    {5, 0, 0, 4, 0, 0},
    {0, 6, 0, 0, 0, 999},
    {0, -2, 7, 0, -2, -2},
    {0, -4, -4, 0, -4, -4},
    {5, 0, 0, 4, 0, 0},
    {0, -6, -6, 0, -6, -6},
    {5, 0, 0, 4, 0, 0},
    {5, 0, 0, 4, 0, 0},
    {0, 6, 0, 0, 11, 0},
    {0, -1, 7, 0, -1, -1},
    {0, -3, -3, 0, -3, -3},
    {0, -5, -5, 0, -5, -5}
};
int goto_tbl[12][4] = {
    {0, 1, 2, 3},
    {0, 0, 0, 0},
    {0, 0, 0, 0},
    {0, 0, 0, 0},
    {0, 8, 2, 3},
    {0, 0, 0, 0},
    {0, 0, 9, 3},
    {0, 0, 0, 10},
    {0, 0, 0, 0},
    {0, 0, 0, 0},
    {0, 0, 0, 0},
    {0, 0, 0, 0}
};

char lhs[] = {' ', 'E', 'E', 'T', 'T', 'F', 'F'}; 
int rhs_len[] = {0, 3, 1, 3, 1, 3, 1}; 
char token[] = {'d', '+', '*', '(', ')', '$'};
char NT[] = {' ', 'E', 'T', 'F'}; 
int stack[MAX], sp = -1;

void LR_Parser(char *input);
void push(int item);
int pop(void);
int top_of_stack(void);

int main() {
    char input[MAX];
    while (1) {
        printf("\nInput: ");
        scanf("%s", input);
        if (input[0] == '$')
            break;
        LR_Parser(input);
    }
    return 0;
}

void LR_Parser(char *input) {
    push(0); // Initial state is pushed onto the stack
    int inputIndex = 0, symbol, state, action, len;
    char currentInput;

    while (input[inputIndex] != '\0' && input[inputIndex] != '$') {
        currentInput = input[inputIndex];

        if (currentInput == 'd') {
            // Assuming 'd' is at index 0 in the 'token' array and represents 'id'
            symbol = 0; // This index should match where 'id' (or 'd' treated as 'id') is in your action and goto tables
        } else {
            symbol = strchr(token, currentInput) - token;
            if(symbol < 0 || symbol >= sizeof(token)) {
                printf("Invalid token encountered.\n");
                return;
           }
        }
        // Determine the symbol's index within the 'token' array
        symbol = strchr(token, currentInput) - token;
        if(symbol < 0) {
            printf("Invalid token encountered.\n");
            return;
        }
        state = top_of_stack();
        action = action_tbl[state][symbol];

        // Shift action
        if (action > 0) {
            printf("Shift %d\n", action);
            push(action); // Push the new state onto the stack
            inputIndex++; // Move to the next character in the input
        }
        // Reduce action
        else if (action < 0) {
            printf("Reduce by rule %d\n", -action);
            len = rhs_len[-action]; // Determine how many symbols to pop based on the RHS of the production rule
            while (len--) pop(); // Pop the stack
            state = top_of_stack(); // Get the new top state
            // Push the state determined by the goto table, based on the LHS of the rule reduced by
            push(goto_tbl[state][lhs[-action] - 'E' - 1]); // Adjust for indexing, assuming 'E' represents the start
        }
        // Accept action
        else if (action == 999) {
            printf("Parsing successful.\n");
            return;
        }
        // Error handling
        else {
            printf("Syntax error or unexpected action.\n");
            return;
        }
    }

    // Handling for when the entire input string has been processed but not successfully parsed
    if(input[inputIndex] == '$' && top_of_stack() == 1) { // Assuming state 1 is the only valid ending state
        printf("Parsing successful.\n");
    } else {
        printf("Incomplete input or parsing error at the end.\n");
    }
}


void push(int item) {
    if (sp < MAX - 1)
        stack[++sp] = item;
    else
        printf("Stack full.\n");
}

int pop(void) {
    return (sp >= 0) ? stack[sp--] : -1;
}

int top_of_stack(void) {
    return (sp >= 0) ? stack[sp] : -1;
}
