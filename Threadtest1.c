#include <stdio.h>   // Provides standard input/output functions like printf
#include <stdlib.h>  // Provides utility functions like atoi (conversion) 
#include <pthread.h> // Provides functions to work with threads in C

void* factorial(void* arg);
void* sum(void* arg);

int main(int argc, char** argv) {
    if (argc != 2) {             // * Check if the correct number of arguments is provided
        fprintf(stderr, "Usage: %s <number>\n", argv[0]); // * Print error if not
        exit(1);                 // * Exit the program with an error code 
    }

    int N = atoi(argv[1]);       // * Convert the command-line argument to an integer
    pthread_t threads[N];        // * Create an array to hold thread identifiers
    int i;                       

    // Create one thread for factorial
    pthread_create(&threads[0], NULL, factorial, &N);  // * Create a factorial thread

    // Create the rest for sum calculation
    for (i = 1; i < N; i++) {
        pthread_create(&threads[i], NULL, sum, &N);   // * Create multiple sum threads
    }

    // Join threads
    for (i = 0; i < N; i++) {
        pthread_join(threads[i], NULL);               // * Wait for each thread to finish
    }

    return 0;                                         // * Indicate successful program exit 
}

void* factorial(void* arg) {
    int n = *(int*)arg;         // 1. Retrieve the passed-in 'N' value
    long long fact = 1;          // 2. Initialize factorial variable (long long to support larger numbers)
    for (int i = 1; i <= n; i++) { 
        fact *= i;               // 3. Calculate the factorial
    }
    printf("sumfact : factorial = %lld\n", fact); // 4. Print the factorial result
    return NULL;                 // 5. Threads conventionally return NULL 
}

void* sum(void* arg) {
    int n = *(int*)arg;          // 1. Retrieve the passed-in 'N' value
    int total = 0;               // 2. Initialize a variable to store the sum
    for (int i = 1; i <= n; i++) {
        total += i;              // 3. Calculate the sum
    }
    printf("sumfact : sum = %d\n", total);  // 4. Print the sum result
    return NULL;                  // 5. Threads conventionally return NULL 
}
