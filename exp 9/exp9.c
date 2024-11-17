#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Define an Item structure
typedef struct {
    int weight;
    int value;
} Item;

int max(int a, int b) {
    return (a > b) ? a : b;
}

// Dynamic Programming Approach
int knapsackDP(Item items[], int n, int capacity) {
    int dp[n + 1][capacity + 1];
    for (int i = 0; i <= n; i++) {
        for (int w = 0; w <= capacity; w++) {
            if (i == 0 || w == 0)
                dp[i][w] = 0;
            else if (items[i - 1].weight <= w)
                dp[i][w] = max(items[i - 1].value + dp[i - 1][w - items[i - 1].weight], dp[i - 1][w]);
            else
                dp[i][w] = dp[i - 1][w];
        }
    }
    return dp[n][capacity];
}

// Backtracking Approach
void knapsackBacktracking(Item items[], int n, int capacity, int i, int currentWeight, int currentValue, int *maxValue) {
    if (i == n) {
        *maxValue = max(*maxValue, currentValue);
        return;
    }
    if (currentWeight + items[i].weight <= capacity)
        knapsackBacktracking(items, n, capacity, i + 1, currentWeight + items[i].weight, currentValue + items[i].value, maxValue);
    knapsackBacktracking(items, n, capacity, i + 1, currentWeight, currentValue, maxValue);
}

// Branch and Bound Node structure
typedef struct Node {
    int level;
    int profit;
    int weight;
    float bound;
} Node;

float bound(Node u, int n, int capacity, Item items[]) {
    if (u.weight >= capacity) return 0;
    float result = u.profit;
    int j = u.level + 1;
    int totalWeight = u.weight;
    while ((j < n) && (totalWeight + items[j].weight <= capacity)) {
        totalWeight += items[j].weight;
        result += items[j].value;
        j++;
    }
    if (j < n) result += (capacity - totalWeight) * ((float) items[j].value / items[j].weight);
    return result;
}

// Branch and Bound Knapsack Solver
int knapsackBranchAndBound(Item items[], int n, int capacity) {
    Node u, v;
    int maxProfit = 0;
    u.level = -1;
    u.profit = 0;
    u.weight = 0;
    u.bound = bound(u, n, capacity, items);
    
    Node queue[1000];
    int front = 0, rear = 0;
    queue[rear++] = u;
    
    while (front < rear) {
        u = queue[front++];
        if (u.level == -1) v.level = 0;
        if (u.level == n - 1) continue;
        
        v.level = u.level + 1;
        
        v.weight = u.weight + items[v.level].weight;
        v.profit = u.profit + items[v.level].value;
        
        if (v.weight <= capacity && v.profit > maxProfit)
            maxProfit = v.profit;
        
        v.bound = bound(v, n, capacity, items);
        if (v.bound > maxProfit) queue[rear++] = v;
        
        v.weight = u.weight;
        v.profit = u.profit;
        v.bound = bound(v, n, capacity, items);
        if (v.bound > maxProfit) queue[rear++] = v;
    }
    return maxProfit;
}

int main() {
    int n = 4, capacity = 5; // Predefined input
    Item items[] = {
        {2, 12},
        {1, 10},
        {3, 20},
        {2, 15}
    };
    
    // Time measurement for Dynamic Programming
    clock_t start, end;
    double time_taken;

    start = clock();
    int dpResult = knapsackDP(items, n, capacity);
    end = clock();
    time_taken = ((double)end - start) / CLOCKS_PER_SEC;
    printf("Max value (Dynamic Programming): %d\n", dpResult);
    printf("Time taken (Dynamic Programming): %f seconds\n", time_taken);
    
    // Time measurement for Backtracking
    start = clock();
    int backtrackResult = 0;
    knapsackBacktracking(items, n, capacity, 0, 0, 0, &backtrackResult);
    end = clock();
    time_taken = ((double)end - start) / CLOCKS_PER_SEC;
    printf("Max value (Backtracking): %d\n", backtrackResult);
    printf("Time taken (Backtracking): %f seconds\n", time_taken);
    
    // Time measurement for Branch and Bound
    start = clock();
    int branchBoundResult = knapsackBranchAndBound(items, n, capacity);
    end = clock();
    time_taken = ((double)end - start) / CLOCKS_PER_SEC;
    printf("Max value (Branch and Bound): %d\n", branchBoundResult);
    printf("Time taken (Branch and Bound): %f seconds\n", time_taken);
    
    return 0;
}
