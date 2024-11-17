#include <stdio.h>
#include <time.h>

#define MAX 20

// Global variables
int solution[MAX], found = 0;

// Function to print the current solution subset
void printSubset(int solution[], int n, int set[]) {
    printf("{ ");
    for (int i = 0; i < n; i++) {
        if (solution[i]) {
            printf("%d ", set[i]);
        }
    }
    printf("}\n");
}

// Recursive function to find subsets that sum to the target
void sumOfSubsets(int set[], int size, int index, int sum, int target) {
    // Base case: if subset sum is equal to target, print it
    if (sum == target) {
        printSubset(solution, size, set);
        found = 1;
        return;
    }

    // If the subset sum exceeds the target or we reach the end, return
    if (sum > target || index == size) {
        return;
    }

    // Include the current element and recurse
    solution[index] = 1;
    sumOfSubsets(set, size, index + 1, sum + set[index], target);

    // Exclude the current element and recurse
    solution[index] = 0;
    sumOfSubsets(set, size, index + 1, sum, target);
}

int main() {
    // Predefined input
    int n = 5;  // Number of elements in the set
    int set[] = {3, 4, 6, 7, 8};  // Elements of the set
    int target = 9;  // Target sum

    // Initialize solution array to zero
    for (int i = 0; i < n; i++) {
        solution[i] = 0;
    }

    // Start timing
    clock_t start = clock();

    // Find and print all subsets
    printf("Subsets with the sum %d are:\n", target);
    sumOfSubsets(set, n, 0, 0, target);

    if (!found) {
        printf("No subset found with the given sum.\n");
    }

    // Stop timing
    clock_t end = clock();

    // Calculate and display elapsed time
    double time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Time taken to find subsets: %.6f seconds\n", time_taken);

    return 0;
}
