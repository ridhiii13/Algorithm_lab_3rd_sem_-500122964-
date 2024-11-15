#include <stdio.h>
#include <stdlib.h>

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
    int n, capacity;

    // Input number of items and knapsack capacity
    printf("Enter the number of items: ");
    scanf("%d", &n);
    printf("Enter the capacity of the knapsack: ");
    scanf("%d", &capacity);

    Item items[n];

    // Input weights and values of items
    printf("Enter weight and value of each item:\n");
    for (int i = 0; i < n; i++) {
        printf("Item %d - Weight: ", i + 1);
        scanf("%d", &items[i].weight);
        printf("Item %d - Value: ", i + 1);
        scanf("%d", &items[i].value);
    }

    // Solve using Greedy approach
    int greedyResult = knapsackGreedy(items, n, capacity);
    printf("Total value with Greedy approach: %d\n", greedyResult);

    // Solve using Dynamic Programming approach
    int dpResult = knapsackDP(items, n, capacity);
    printf("Total value with Dynamic Programming approach: %d\n", dpResult);

    return 0;
}