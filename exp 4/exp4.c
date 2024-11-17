#include <stdio.h>

// Structure to store start and finish times of activities
typedef struct {
    int start;
    int finish;
} Activity;

// Function to sort activities based on their finish time
void sortActivities(Activity activities[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (activities[j].finish > activities[j + 1].finish) {
                // Swap activities[j] and activities[j + 1]
                Activity temp = activities[j];
                activities[j] = activities[j + 1];
                activities[j + 1] = temp;
            }
        }
    }
}

// Function to perform activity selection using a greedy approach
void activitySelection(Activity activities[], int n) {
    // Sort activities by their finish times
    sortActivities(activities, n);
    
    printf("Selected activities are:\n");
    
    // The first activity is always selected
    int lastSelected = 0;
    printf("Activity 1 (Start: %d, Finish: %d)\n", activities[0].start, activities[0].finish);
    
    // Consider the rest of the activities
    for (int i = 1; i < n; i++) {
        // If this activity's start time is greater than or equal to
        // the finish time of the last selected activity, select it
        if (activities[i].start >= activities[lastSelected].finish) {
            printf("Activity %d (Start: %d, Finish: %d)\n", i + 1, activities[i].start, activities[i].finish);
            lastSelected = i;
        }
    }
}

int main() {
    // The input data as per your request:
    int n = 6;
    
    // Initialize the activities array with given start and finish times
    Activity activities[6] = {
        {1, 3}, // Activity 1
        {2, 4}, // Activity 2
        {4, 6}, // Activity 3
        {5, 7}, // Activity 4
        {7, 9}, // Activity 5
        {3, 6}  // Activity 6
    };
    
    // Perform activity selection
    activitySelection(activities, n);
    
    return 0;
}
