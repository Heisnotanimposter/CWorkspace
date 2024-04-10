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
int stack[MAX], sp = -1;

void push(int item) {
    if (sp < MAX - 1) {
        stack[++sp] = item;
    } else {
        printf("Stack full.\n");
    }
}

int pop(void) {
    if (sp >= 0) {
        return stack[sp--];
    } else {
        printf("Stack empty.\n");
        return -1; 
    }
}

int top_of_stack(void) {
    if (sp >= 0) {
        return stack[sp];
    } else {
        printf("Stack empty.\n");
        return -1; 
    }
}

char lhs[] = {' ', 'E', 'E', 'T', 'T', 'F', 'F'}; 
int rhs_len[] = {0, 3, 1, 3, 1, 3, 1}; 
char token[] = {'d', '+', '*', '(', ')', '$'};
char NT[] = {' ', 'E', 'T', 'F'}; 

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
    push(0); // Initial state
    int inputIndex = 0, symbol, state, action, len, nextState;
    char currentInput;

    while (input[inputIndex] != '\0') {
        if (input[inputIndex] == '$' && top_of_stack() == 1) { // Assuming state 1 is an acceptable state before $
            printf("Parsing successful.\n");
            return;
        }

        currentInput = input[inputIndex];
        symbol = strchr(token, currentInput) - token;
        if (symbol < 0 || symbol >= sizeof(token)) { // Check for valid symbol
            printf("Unrecognized token.\n");
            return;
        }

        state = top_of_stack();
        action = action_tbl[state][symbol];

        if (action > 0) {
            printf("Shift %d\n", action);
            push(action);
            inputIndex++;
        } else if (action < 0) {
            printf("Reduce by rule: %d\n", -action);
            len = rhs_len[-action];
            while (len--) pop(); 

            state = top_of_stack(); 
            nextState = goto_tbl[state][strchr(NT, lhs[-action]) - NT - 1];
            printf("Transition to state: %d\n", nextState);
            push(nextState);
        } else {
            printf("Syntax error.\n");
            return;
        }
    }

    if (input[inputIndex] == '\0' && top_of_stack() == 1) {
        printf("Parsing successful.\n");
    } else {
        printf("Incomplete input or syntax error at the end.\n");
    }
}