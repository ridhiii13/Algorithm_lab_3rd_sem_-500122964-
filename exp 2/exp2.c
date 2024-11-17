#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Function to merge two halves of the array
void merge(int arr[], int left, int mid, int right) {
    int n1 = mid - left + 1;          // Size of left subarray
    int n2 = right - mid;             // Size of right subarray
    int* leftArr = (int*)malloc(n1 * sizeof(int));  // Dynamic array for left half
    int* rightArr = (int*)malloc(n2 * sizeof(int)); // Dynamic array for right half

    for (int i = 0; i < n1; i++)      // Copy data to left subarray
        leftArr[i] = arr[left + i];
    for (int i = 0; i < n2; i++)      // Copy data to right subarray
        rightArr[i] = arr[mid + 1 + i];

    int i = 0, j = 0, k = left;       // Initial indexes of subarrays and merged array
    while (i < n1 && j < n2) {        // Merge subarrays back into arr
        if (leftArr[i] <= rightArr[j])
            arr[k++] = leftArr[i++];
        else
            arr[k++] = rightArr[j++];
    }
    while (i < n1)                    // Copy any remaining elements of leftArr
        arr[k++] = leftArr[i++];
    while (j < n2)                    // Copy any remaining elements of rightArr
        arr[k++] = rightArr[j++];

    free(leftArr);                    // Free dynamically allocated memory
    free(rightArr);
}

// Merge sort algorithm: recursively sorts halves of the array
void mergeSort(int arr[], int left, int right) {
    if (left < right) {               // Base case: stop if the segment has one or no elements
        int mid = left + (right - left) / 2;
        mergeSort(arr, left, mid);    // Sort the left half
        mergeSort(arr, mid + 1, right); // Sort the right half
        merge(arr, left, mid, right); // Merge the sorted halves
    }
}

// Partition function for quicksort
int partition(int arr[], int low, int high) {
    int pivot = arr[high];            // Choose pivot element
    int i = low - 1;                  // Index of smaller element
    for (int j = low; j < high; j++) {
        if (arr[j] < pivot) {         // If current element is smaller than pivot
            i++;
            int temp = arr[i];        // Swap arr[i] and arr[j]
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }
    int temp = arr[i + 1];            // Place the pivot in its correct position
    arr[i + 1] = arr[high];
    arr[high] = temp;
    return i + 1;                     // Return pivot index
}

// Quicksort algorithm: recursively sorts segments of the array
void quickSort(int arr[], int low, int high) {
    if (low < high) {                 // Base case: stop if segment has one or no elements
        int pi = partition(arr, low, high);  // Partition the array
        quickSort(arr, low, pi - 1);  // Sort elements before partition
        quickSort(arr, pi + 1, high); // Sort elements after partition
    }
}

// Function to print an array
void printArray(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

// Function to compare the performance of Merge Sort and Quick Sort
void compareSortPerformance(int arr[], int size) {
    int* arrMergeSort = (int*)malloc(size * sizeof(int)); // Duplicate array for Merge Sort
    int* arrQuickSort = (int*)malloc(size * sizeof(int)); // Duplicate array for Quick Sort
    for (int i = 0; i < size; i++) {      // Copy original array to both duplicates
        arrMergeSort[i] = arr[i];
        arrQuickSort[i] = arr[i];
    }

    // Measure time for Merge Sort
    clock_t startMerge = clock();
    mergeSort(arrMergeSort, 0, size - 1);
    clock_t endMerge = clock();
    double durationMerge = (double)(endMerge - startMerge) * 1000000 / CLOCKS_PER_SEC;

    // Measure time for Quick Sort
    clock_t startQuick = clock();
    quickSort(arrQuickSort, 0, size - 1);
    clock_t endQuick = clock();
    double durationQuick = (double)(endQuick - startQuick) * 1000000 / CLOCKS_PER_SEC;

    // Display sorted arrays and execution times
    printf("Merge Sort result: ");
    printArray(arrMergeSort, size);
    printf("Time taken for Merge Sort: %.2f microseconds\n", durationMerge);

    printf("Quick Sort result: ");
    printArray(arrQuickSort, size);
    printf("Time taken for Quick Sort: %.2f microseconds\n", durationQuick);

    // Free dynamically allocated memory
    free(arrMergeSort);
    free(arrQuickSort);
}

// Main function
int main() {
    int arr[] = {38, 27, 43, 3, 9, 82, 10}; // Sample array
    int size = sizeof(arr) / sizeof(arr[0]); // Calculate size of the array

    compareSortPerformance(arr, size);       // Call function to compare sorting algorithms

    return 0;
}
