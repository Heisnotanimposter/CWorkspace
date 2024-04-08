#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define MAX 1000

char NT[] = {' ', 'E', 'E', 'T', 'T', 'F', 'F'}; // Only if single chars were intended
int NT_len[] = {0, 1, 1, 1, 1, 1, 1};

char *rhs[] = {" ", "E+T", "T", "T*F", "F", "(E)", "d"};
int rhs_len[] = {0, 3, 1, 3, 1, 3, 1};

char T[] = {' ', '+', '*', '(', ')', 'd', '$'};
int T_len[] = {0, 1, 1, 1, 1, 1, 1};

int stack[MAX], sp;
int ruleNTIndex[] = {0, , , };
int NTIndex = ruleNTIndex[rule];


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


void printStack(int *stack, int sp) {
    for (int i = 0; i <= sp; i++) {
        printf("%d ", stack[i]);
    }
}

void printInput(char *input, int pos) {
    printf("%s\n", input+pos);
}

void LR_Parser(char *input) {
    sp = 0; 
    stack[sp] = 0; 
    
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

        if (action >= 1 && action <= MAX) { 
            printf("shift %d: ", action);
            printStack(stack, sp);
            stack[++sp] = goto_tbl[stack[sp-1]][rhs[rule]];
            inputPos++; 

        } else if (action <= -1 && action >= -MAX) { 
            rule = -action;
            printf("reduce %d: ", rule);
            printStack(stack, sp);
            sp -= rhs_len[rule];
            stack[++sp] = goto_tbl[stack[sp-1]][rhs[rule]]; 

        } else if (action == 999) { 
            printf("accept\n");
            accepted = true;

        } else {
            printf("error\n");
            break;

        }
    }
}

int main() {
    char input[MAX];

    strcpy(input, "d*d+d$");
    LR_Parser(input);

    strcpy(input, "d-d+d$");
    LR_Parser(input);

    strcpy(input, "dd+d$");
    LR_Parser(input);

    strcpy(input, "dd-d$");
    LR_Parser(input);

    strcpy(input, "d*dd$");
    LR_Parser(input);


    return 0;
}