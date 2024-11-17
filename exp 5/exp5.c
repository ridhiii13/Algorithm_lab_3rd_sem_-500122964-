#include <stdio.h>
#include <limits.h>

// Function to find the minimum number of multiplications needed to multiply matrices
void matrixChainOrder(int p[], int n) {
    int m[n][n];  // m[i][j] holds the minimum multiplication cost for matrices from i to j
    int s[n][n];  // s[i][j] holds the index of k at which the optimal split occurs

    // Initialize the cost of single matrices to zero
    for (int i = 1; i < n; i++) {
        m[i][i] = 0;
    }

    // L is chain length
    for (int L = 2; L < n; L++) {
        for (int i = 1; i < n - L + 1; i++) {
            int j = i + L - 1;
            m[i][j] = INT_MAX;  // Set initial cost to infinity

            // Find the minimum cost for this split point
            for (int k = i; k <= j - 1; k++) {
                int q = m[i][k] + m[k + 1][j] + p[i - 1] * p[k] * p[j];
                if (q < m[i][j]) {
                    m[i][j] = q;
                    s[i][j] = k;  // Record the split point
                }
            }
        }
    }

    // Display results
    printf("Minimum number of multiplications is %d\n", m[1][n - 1]);
    printf("Optimal Parenthesization:\n");
    printOptimalParenthesis(1, n - 1, s);
}

// Recursive function to print the optimal parenthesization
void printOptimalParenthesis(int i, int j, int s[][20]) {
    if (i == j) {
        printf("A%d", i);
    } else {
        printf("(");
        printOptimalParenthesis(i, s[i][j], s);
        printOptimalParenthesis(s[i][j] + 1, j, s);
        printf(")");
    }
}

int main() {
    int n;

    printf("Enter the number of matrices: ");
    scanf("%d", &n);

    int p[n + 1];
    printf("Enter dimensions of matrices (n+1 numbers):\n");
    for (int i = 0; i <= n; i++) {
        printf("Dimension %d: ", i + 1);
        scanf("%d", &p[i]);
    }

    matrixChainOrder(p, n + 1);

    return 0;
}
