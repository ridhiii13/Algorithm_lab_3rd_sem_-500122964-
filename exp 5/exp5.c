#include <stdio.h>
#include <limits.h>
#include <time.h>

// Function to print the optimal parenthesis order
void printOptimalParenthesis(int i, int j, int n, int* bracket, char* name) {
    if (i == j) {
        printf("%c", *name);
        (*name)++;
        return;
    }

    printf("(");

    // Print the left part of the parenthesis
    printOptimalParenthesis(i, *((bracket + i * n) + j), n, bracket, name);

    // Print the right part of the parenthesis
    printOptimalParenthesis(*((bracket + i * n) + j) + 1, j, n, bracket, name);

    printf(")");
}

// Function to compute the minimum cost of matrix multiplication
int matrixChainOrder(int p[], int n) {
    int m[n][n];
    int bracket[n][n];

    // Cost is zero when multiplying one matrix
    for (int i = 1; i < n; i++) {
        m[i][i] = 0;
    }

    for (int len = 2; len < n; len++) {
        for (int i = 1; i < n - len + 1; i++) {
            int j = i + len - 1;
            m[i][j] = INT_MAX;
            for (int k = i; k <= j - 1; k++) {
                int cost = m[i][k] + m[k + 1][j] + p[i - 1] * p[k] * p[j];
                if (cost < m[i][j]) {
                    m[i][j] = cost;
                    bracket[i][j] = k;
                }
            }
        }
    }

    char matrixName = 'A';
    printf("Optimal Parenthesization: ");
    printOptimalParenthesis(1, n - 1, n, (int*)bracket, &matrixName);
    printf("\n");

    return m[1][n - 1];
}

int main() {
    int arr[] = {5,6,8,4,5};
    int n = sizeof(arr) / sizeof(arr[0]);

    clock_t start = clock();
    int minCost = matrixChainOrder(arr, n);
    clock_t end = clock();

    double timeTaken = ((double)(end - start)) * 1000.0 / CLOCKS_PER_SEC;

    printf("Minimum number of multiplications: %d\n", minCost);
    printf("Time taken: %.2f milliseconds\n", timeTaken);

    return 0;
}
