#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct {
    int weight;
    int value;
} Item;

// Function to sort items by value-to-weight ratio in descending order (for Greedy approach)
int compare(const void *a, const void *b) {
    Item *itemA = (Item *)a;
    Item *itemB = (Item *)b;
    double ratioA = (double)itemA->value / itemA->weight;
    double ratioB = (double)itemB->value / itemB->weight;
    return (ratioA < ratioB) - (ratioA > ratioB);
}

// Greedy approach for 0/1 Knapsack based on value-to-weight ratio
int knapsackGreedy(Item items[], int n, int capacity) {
    qsort(items, n, sizeof(Item), compare); // Sort items by value-to-weight ratio
    int totalValue = 0, currentWeight = 0;

    for (int i = 0; i < n; i++) {
        if (currentWeight + items[i].weight <= capacity) {
            currentWeight += items[i].weight;
            totalValue += items[i].value;
        }
    }
    return totalValue;
}

// Dynamic Programming approach for 0/1 Knapsack
int knapsackDP(Item items[], int n, int capacity) {
    int dp[n + 1][capacity + 1];

    // Initialize DP table
    for (int i = 0; i <= n; i++) {
        for (int w = 0; w <= capacity; w++) {
            if (i == 0 || w == 0)
                dp[i][w] = 0;
            else if (items[i - 1].weight <= w)
                dp[i][w] = (items[i - 1].value + dp[i - 1][w - items[i - 1].weight] > dp[i - 1][w]) ?
                            items[i - 1].value + dp[i - 1][w - items[i - 1].weight] : dp[i - 1][w];
            else
                dp[i][w] = dp[i - 1][w];
        }
    }
    return dp[n][capacity];
}

int main() {
    // Predefined input
    int n = 4;  // Number of items
    int capacity = 5;  // Knapsack capacity

    // Predefined items with weights and values
    Item items[] = {
        {2, 12},  // Item 1: weight = 2, value = 12
        {1, 10},  // Item 2: weight = 1, value = 10
        {3, 20},  // Item 3: weight = 3, value = 20
        {4, 25}   // Item 4: weight = 4, value = 25
    };

    // Measure time taken by Greedy approach
    clock_t startGreedy = clock();
    int greedyResult = knapsackGreedy(items, n, capacity);
    clock_t endGreedy = clock();
    double timeGreedy = ((double)(endGreedy - startGreedy)) / CLOCKS_PER_SEC;

    // Measure time taken by Dynamic Programming approach
    clock_t startDP = clock();
    int dpResult = knapsackDP(items, n, capacity);
    clock_t endDP = clock();
    double timeDP = ((double)(endDP - startDP)) / CLOCKS_PER_SEC;

    // Output results
    printf("Total value with Greedy approach: %d\n", greedyResult);
    printf("Time taken by Greedy approach: %.6f seconds\n", timeGreedy);

    printf("Total value with Dynamic Programming approach: %d\n", dpResult);
    printf("Time taken by Dynamic Programming approach: %.6f seconds\n", timeDP);

    return 0;
}
