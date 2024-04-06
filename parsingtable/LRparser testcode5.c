#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 32

char NT[] = {' ', 'E', 'E', 'T', 'T', 'F', 'F'};
int NT_len[] = {0, 1, 1, 1, 1, 1, 1};

char *GR[] = {' ', 'E+T', 'T', 'T*F' , 'F' ,'(E)' ,'d'};
int GR_len[] = {0, 3, 1, 3, 1, 3, 1};

char tokens[] = {' ', '+', '*', '(', ')', 'd', '$'}; 
int tokens_len[] = {0, 1, 1, 1, 1, 1, 1};

int stack[MAX], sp;

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

int read_token(char symbol) {
    for (int i = 0; i < sizeof(tokens) / sizeof(char); ++i) {
        if (tokens[i] == symbol) return i;
    }
    return 0;
}

void SHIFT(int shifting) {
    if (sp < MAX - 1) {
        stack[++sp] = shifting;
    } else {
        printf("Error: Stack overflow.\n");
        exit(EXIT_FAILURE);
    }
}

void REDUCE(int reducing) {
    sp -= GR_len[reducing - 1];
    int NT_index = (NT[reducing - 1] == 'E') ? 1 : (NT[reducing - 1] == 'T') ? 2 : 3; 
    int goto_shifting = goto_tbl[stack[sp]][NT_index - 1]; 
    SHIFT(goto_shifting);
}

void LR_Parser(char* w) {
    int ip = 0; 
    stack[++sp] = 0; 

    while (w[ip] != '\0' && w[ip] != '$') { 
        int s = stack[sp]; 
        char a = w[ip]; 
        int action = action_tbl[s][read_token(a)];

        if (action > 0) { 
            SHIFT(action); 
            ip++; 
        } else if (action < 0) { 
            int reducing = -action;
            int b_len = GR_len[reducing - 1]; 
            sp -= 2 * b_len; 
            int s_prime = stack[sp];
            int A_index = NT[reducing] - 'E'; 
            int goto_shifting = goto_tbl[s_prime][A_index - 1];
            SHIFT(goto_shifting);
            printf("ACCEPT:REDUCE: %s\n", GR[reducing - 1]); 
        } else if (action == 999) { 
            printf("ACCEPT.\n");
            return;
        } else { 
            printf("error.\n");
            return;
        }
    }
}


int main() {
    char input[MAX];
    while (1) {
        printf("Input: ");
        if (fgets(input, MAX, stdin) != NULL) {
            input[strcspn(input, "\n")] = '\0';
            if (strcmp(input, "exit") == 0) {
                break;
            }
            int len = strlen(input);
            if (input[len - 1] == '$') {
                input[len - 1] = '\0'; 
            }

            LR_Parser(input);
        } else {
            printf("Error\n");
            break;
        }

        }
    return 0;
}


//    " ", 
//    "E" -> "E + T",
//    "E" -> "T",
//    "T" -> "T * F",
//    "T" -> "F",
//    "F" -> "(E)",
//    "F" -> "d" 
//};