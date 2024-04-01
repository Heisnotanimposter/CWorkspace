#include <stdio.h>
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

int goto_tbl[12][3] = {
    {1, 2, 3},
    {0, 0, 0},
    {0, 0, 0},
    {0, 0, 0},
    {8, 2, 3},
    {0, 0, 0},
    {0, 9, 3},
    {0, 0, 10},
    {0, 0, 0},
    {0, 0, 0},
    {0, 0, 0},
    {0, 0, 0}
};

char lhs[] = {' ', 'E', 'E', 'T', 'T', 'F', 'F'}; 
int rhs_len[] = {0, 3, 1, 3, 1, 3, 1}; /
char token[] = {'d', '+', '*', '(', ')', '$'};
char NT[] = {' ', 'E', 'T', 'F'}; 
int stack[MAX], sp = -1; 

// Function to find the index of token in the token array
int get_token_index(char c) {
    for (int i = 0; i < 6; i++) {
        if (token[i] == c) return i;
    }
    return -1; // return -1 if token not found
}

// Function to find the index of a non-terminal in the NT array
int get_nt_index(char c) {
    for (int i = 0; i < 4; i++) {
        if (NT[i] == c) return i;
    }
    return -1; // return -1 if non-terminal not found
}

void perform_action(int action, int* sp, int* stack, char** input_ptr, int* ip) {
    if (action > 0) { // shift action
        printf("shift %d\n", action);
        stack[++(*sp)] = action;
        (*input_ptr)++;
        (*ip)++;
    } else if (action < 0) { // reduce action
        printf("reduce by rule %d\n", -action);
        int rule = -action;
        *sp -= rhs_len[rule];
        int goto_state = goto_tbl[stack[*sp]][get_nt_index(lhs[rule])];
        stack[++(*sp)] = goto_state;
    } else if (action == 999) { // accept
        printf("accept\n");
    } else { // error
        printf("error\n");
    }
}

void print_config(int* stack, int sp, char* input_ptr, int step) {
    printf("(%d) ", step);
    for (int i = 0; i <= sp; i++) {
        printf("%d", stack[i]);
    }
    printf(" %-10s\n", input_ptr);
}

void LR_Parser(char* input) {
    char* input_ptr = input; 
    int ip = 0; 
    int action, state;

    stack[++sp] = 0; 
    printf("Input: %s\n", input);
    printf("%-6s%-10s\n", "Stack", "Input");

    while (*input_ptr != '\0') {
        state = stack[sp]; 
        action = action_tbl[state][get_token_index(*input_ptr)];
        print_config(stack, sp, input_ptr, ip); // print current configuration
        perform_action(action, &sp, stack, &input_ptr, &ip); // perform the action

        if (action == 999) { // accept
            printf("The input \"%s\" is a valid expression.\n", input);
            return;
        } else if (action == 0) { // error
            printf("The input \"%s\" is not a valid expression.\n", input);
            return;
        }
    }
    // After the loop, check for remaining reduction or accept
    while (sp > 0) {
        state = stack[sp];
        action = action_tbl[state][5]; // 5 is the column index for '$'
        print_config(stack, sp, input_ptr, ip);
        perform_action(action, &sp, stack, &input_ptr, &ip);

        if (action == 999) {
            printf("The input \"%s\" is a valid expression.\n", input);
            return;
        } else if (action <= 0) { // error or reduce
            printf("The input \"%s\" is not a valid expression.\n", input);
            return;
        }
    }
}

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
