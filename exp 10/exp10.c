#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define PRIME 101  // Prime number for Rabin-Karp hashing

// Rabin-Karp algorithm for string matching
void rabinKarp(char *text, char *pattern) {
    int n = strlen(text);
    int m = strlen(pattern);
    int i, j;
    int patternHash = 0, textHash = 0, h = 1;

    // The value of h would be "pow(d, m-1)%q"
    for (i = 0; i < m - 1; i++) {
        h = (h * 256) % PRIME;
    }

    // Calculate the hash value of pattern and first window of text
    for (i = 0; i < m; i++) {
        patternHash = (256 * patternHash + pattern[i]) % PRIME;
        textHash = (256 * textHash + text[i]) % PRIME;
    }

    // Slide the pattern over text one by one
    for (i = 0; i <= n - m; i++) {
        // Check the hash values of current window of text and pattern
        if (patternHash == textHash) {
            // Check characters one by one
            for (j = 0; j < m; j++) {
                if (text[i + j] != pattern[j])
                    break;
            }
            if (j == m)
                printf("Pattern found at index %d (Rabin-Karp)\n", i);
        }

        // Calculate hash value for next window of text
        if (i < n - m) {
            textHash = (256 * (textHash - text[i] * h) + text[i + m]) % PRIME;
            if (textHash < 0)
                textHash = (textHash + PRIME);
        }
    }
}

// Knuth-Morris-Pratt (KMP) algorithm for string matching
void computeLPSArray(char *pattern, int m, int *lps) {
    int length = 0;
    lps[0] = 0;
    int i = 1;
    while (i < m) {
        if (pattern[i] == pattern[length]) {
            length++;
            lps[i] = length;
            i++;
        } else {
            if (length != 0) {
                length = lps[length - 1];
            } else {
                lps[i] = 0;
                i++;
            }
        }
    }
}

void kmpSearch(char *text, char *pattern) {
    int n = strlen(text);
    int m = strlen(pattern);
    int lps[m];

    computeLPSArray(pattern, m, lps);

    int i = 0, j = 0;
    while (i < n) {
        if (pattern[j] == text[i]) {
            i++;
            j++;
        }
        if (j == m) {
            printf("Pattern found at index %d (KMP)\n", i - j);
            j = lps[j - 1];
        } else if (i < n && pattern[j] != text[i]) {
            if (j != 0)
                j = lps[j - 1];
            else
                i++;
        }
    }
}

// Naive string-matching algorithm
void naiveSearch(char *text, char *pattern) {
    int n = strlen(text);
    int m = strlen(pattern);

    for (int i = 0; i <= n - m; i++) {
        int j;
        for (j = 0; j < m; j++) {
            if (text[i + j] != pattern[j])
                break;
        }
        if (j == m)
            printf("Pattern found at index %d (Naive)\n", i);
    }
}

int main() {
    char text[1000];
    char pattern[100];

    // Input the text and pattern
    printf("Enter the text: ");
    fgets(text, 1000, stdin);
    text[strcspn(text, "\n")] = 0; // Remove newline character

    printf("Enter the pattern: ");
    fgets(pattern, 100, stdin);
    pattern[strcspn(pattern, "\n")] = 0; // Remove newline character

    // Measure time for Naive Search
    clock_t start = clock();
    naiveSearch(text, pattern);
    clock_t end = clock();
    double timeNaive = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Time taken by Naive Search: %.6f seconds\n\n", timeNaive);

    // Measure time for Rabin-Karp Search
    start = clock();
    rabinKarp(text, pattern);
    end = clock();
    double timeRabinKarp = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Time taken by Rabin-Karp Search: %.6f seconds\n\n", timeRabinKarp);

    // Measure time for KMP Search
    start = clock();
    kmpSearch(text, pattern);
    end = clock();
    double timeKMP = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Time taken by KMP Search: %.6f seconds\n", timeKMP);

    return 0;
}