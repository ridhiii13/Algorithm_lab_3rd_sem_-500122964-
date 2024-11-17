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
    int n;
    printf("Enter the number of activities: ");
    scanf("%d", &n);
    
    // Dynamically allocate memory for the activities array based on input size
    Activity activities[n];
    
    // Input start and finish times of each activity
    printf("Enter start and finish times of each activity:\n");
    for (int i = 0; i < n; i++) {
        printf("Activity %d:\n", i + 1);
        printf("Start time: ");
        scanf("%d", &activities[i].start);
        printf("Finish time: ");
        scanf("%d", &activities[i].finish);
    }
    
    // Perform activity selection
    activitySelection(activities, n);
    
    return 0;
}
