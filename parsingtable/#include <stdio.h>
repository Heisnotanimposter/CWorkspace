#include <stdio.h>
#include <string.h>

#define MAX 100

// Define the action table and the goto table according to your LR parsing table screenshot.
// Assume we have action_tbl and goto_tbl initialized properly.

// Function to print the stack for visualization.
void print_stack(int stack[], int sp) {
    for (int i = 0; i <= sp; i++) {
        printf("%d", stack[i]);
        if(i < sp) {
            printf(" ");
        }
    }
}

// Function to simulate the LR parsing process.
void LR_Parser(char *input) {
    int stack[MAX];
    int sp = 0; // Stack pointer initialization
    stack[sp] = 0; // Starting with state 0 in the stack

    // Initialize other variables to store the current state, action, etc.

    // Main parsing loop
    int i = 0;
    while (input[i] != '\0') {
        // Visualization of the stack and input before each action
        printf("(");
        print_stack(stack, sp);
        printf(") ");
        // ... rest of the input visualization code ...

        // Determine the action based on the current state and input symbol
        // using the action_tbl.

        // Perform shift or reduce actions accordingly.
        // For a shift, push the symbol and the new state onto the stack.
        // For a reduce, pop the handle from the stack and push the resulting state from goto_tbl.

        // After each action, print the details of the action.
        // Example: printf("shift 5: %s\n", remaining_input);
        // or printf("reduce 3: E -> E + T\n");

        // Acceptance or error handling
        // if (action is accept) { ... }
        // else if (action is error) { ... }

        i++; // Move to the next input symbol
    }
}

int main() {
    char input[MAX];
    printf("\nInput: ");
    fgets(input, MAX, stdin); // Read a line of input from the user
    input[strcspn(input, "\n")] = '\0'; // Strip the newline character

    if (input[0] != '\0' && strchr(input, '$')) { // Ensure input ends with '$'
        LR_Parser(input);
    } else {
        printf("Input error: Input should end with '$'.\n");
    }

    return 0;
}
