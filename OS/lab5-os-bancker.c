/**
 * 
 * Bancker algorithm
 * Master 01 - Computer Engineering - Data Structures and Algorithms
 * By: Issam
 * 
 */

#include <stdio.h>
#include <stdbool.h>
#define max 5

int main() {
    int curr[max][max];
    int max_claim[max][max];
    int avl[max];
    int max_res[max];
    int running[max];
    int alloc[max];
    int order[max];
 
    int i, j, exec, r, p;
    int count = 0;
    bool safe = false;
    for(i = 0; i < max; i++)
        alloc[i] = 0;
 
    printf("Enter the number of resources: ");
    scanf("%d", &r);
 
    printf("\nEnter the number of processes: ");
    scanf("%d", &p);
    for (i = 0; i < p; i++) {
        running[i] = 1;
        count++;
    }
 
    printf("\nEnter Claim Vector: ");
    for (i = 0; i < r; i++)
        scanf("%d", &max_res[i]);
 
    printf("\nEnter Allocated Resource Table:\n");
    for (i = 0; i < p; i++) {
        printf("proc %d: ", i+1);
        for (j = 0; j < r; j++)
            scanf("%d", &curr[i][j]);
    }
 
    printf("\nEnter Maximum Claim table:\n");
    for (i = 0; i < p; i++) {
        printf("proc %d: ", i+1);
        for (j = 0; j < r; j++)
            scanf("%d", &max_claim[i][j]);
    }
 
    // calculate currently allocated resources
    for (i = 0; i < p; i++)
        for (j = 0; j < r; j++)
            alloc[j] += curr[i][j];
    // print currently allocated resources
    printf("\nAllocated resources: ");
    for (i = 0; i < r; i++)
        printf("%d ", alloc[i]);
 
    // calculate available allocated resources
    for (i = 0; i < r; i++)
        avl[i] = max_res[i] - alloc[i];
    // print available allocated resources
    printf("\nAvailable resources: ");
    for (i = 0; i < r; i++)
        printf("%d ", avl[i]);
    printf("\n");
 
    while (count != 0) {
        safe = false;
        for (i = 0; i < p; i++) {
            if (running[i]) {
                exec = 1;
                for (j = 0; j < r; j++) {
                    // test if R < A
                    if (max_claim[i][j] - curr[i][j] > avl[j]) {
                        exec = 0;
                        break;
                    }
                }
                // if R < A then run the process and recalculate available resources and omit process from list
                if (exec) {
                    printf("\nProcess %d is executing.\n", i);
                    running[i] = 0;
                    count--;
                    safe = true;
                    order[count] = i;
                    for (j = 0; j < r; j++)
                        avl[j] += curr[i][j];
                    break;
                }
            }
        }
        // processes are deadlocked
        if (!safe) {
            printf("\nThe processes are in unsafe state.");
            break;
        }
        // processes are safe
        if (safe)
            printf("\nThe process is in safe state.");
 
    }
    // print execution order to avoid deadlocks
    printf("\nOrder of execution: ");
        for (i = p-1; i >= 0; i--)
            printf("P%d, ", order[i]);
    printf("\n");
 
    return 0;
}
