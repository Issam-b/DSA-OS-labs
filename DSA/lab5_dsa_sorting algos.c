/**
 * 
 * Sorting algorithms implementation
 * Master 01 - Computer Engineering - Data Structures and Algorithms
 * By: Issam
 * 
 */

#include <stdio.h>
#include <time.h>

// print result
void print(int list[], int n) {
    printf("The result is:\n");
    for (int i = 0; i < n; i++)
        printf("%d ", list[i]);
    printf("\n");
}

// bubble sort
void bubble_sort (int list[],int n){
    int swap;
    for(int c=0;c<n-1;c++)
     {
      for(int d=0;d<n-c-1;d++)
        {
         if(list[d] > list[d+1])
            {
            swap=list[d];
            list[d]=list[d+1];
            list[d+1]=swap;
            }
        }
    }
    //print(list, n);
}

// merge sort
// function to merge lower and higher parts of list
void merge(int list[], int low, int mid, int high) {
    int b[100000];
    int i = low, j = mid + 1, k = 0;
    while (i <= mid && j <= high) {
        if (list[i] <= list[j])
            b[k++] = list[i++];
        else
            b[k++] = list[j++];
    }
    while (i <= mid)
        b[k++] = list[i++];
    while (j <= high)
        b[k++] = list[j++];
    k--;
    while (k >= 0) {
        list[low + k] = b[k];
        k--;
    }
}

void merge_sort(int list[], int low, int high) {
    if (low < high) {
        int m = (high + low)/2;
        merge_sort(list, low, m);
        merge_sort(list, m + 1, high);
        merge(list, low, m, high);
    }
}

// bin sort (Bucket sort)
void bin_sort(int list[], int n) {
    int i, j;
    int count[n];
    for (i = 0; i < n; i++)
        count[i] = 0;
    for (i = 0; i < n; i++)
        (count[list[i]])++;
    for (i = 0, j = 0; i < n; i++)
        for(; count[i] > 0; (count[i])--)
            list[j++] = i;
    //print(list, n);
}

// heap sort
int max (int *list, int n, int i, int j, int k) {
    int m = i;
    if (j < n && list[j] > list[m]) {
        m = j;
    }
    if (k < n && list[k] > list[m]) {
        m = k;
    }
    return m;
}
 
void downheap (int *list, int n, int i) {
    while (1) {
        int j = max(list, n, i, 2 * i + 1, 2 * i + 2);
        if (j == i) {
            break;
        }
        int t = list[i];
        list[i] = list[j];
        list[j] = t;
        i = j;
    }
}
 
void heap_sort (int *list, int n) {
    int i;
    for (i = (n - 2) / 2; i >= 0; i--) {
        downheap(list, n, i);
    }
    for (i = 0; i < n; i++) {
        int t = list[n - i - 1];
        list[n - i - 1] = list[0];
        list[0] = t;
        downheap(list, n - i - 1, 0);
    }
    //print(list, n);
}

// reset list
void reset(int list[], int n) {
    int k = 0;
    for(int i=n-1; i>=0; i--) {
        list[k] = i+1;
        k++;
    }
}

int main() {
    int n;
    int list[100000];
    int i, k = 0;
    time_t start,end; // used to calculate execution time
    double exectime; // execution time variable
    int choice;
    printf("number of elements:");
    scanf("%d",&n);
    for(i=n-1; i>=0; i--) {
        list[k] = i+1;
        k++;
    }
    while(1) {
        printf("\nChoose the Algorithm:\n1 - bubble sort\n2 - Merge sort\n3 - Heap sort\n4 - Bin (Bucket) sort\n");
        scanf("%d", &choice);
        switch (choice) {
            case 1 :

                start=clock();  // start time
                bubble_sort(list, n);
                end=clock();    // finish time
                exectime=(difftime(end,start)/CLOCKS_PER_SEC);
                printf("Execution time is %lf\n",exectime);
                reset(list, n);

                break;
            case 2 :

                start=clock();
                merge_sort(list, 0, n-1);
                end=clock();
                exectime=(difftime(end,start)/CLOCKS_PER_SEC);
                printf("Execution time is %lf\n",exectime);
                reset(list, n);

                break;
            case 3 :
                start=clock();
                heap_sort(list, n);
                end=clock();
                exectime=(difftime(end,start)/CLOCKS_PER_SEC);
                printf("Execution time is %lf\n",exectime);
                reset(list, n);
                break;
            case 4 :
                start=clock();
                bin_sort(list, n);
                end=clock();
                exectime=(difftime(end,start)/CLOCKS_PER_SEC);
                printf("Execution time is %lf\n",exectime);
                reset(list, n);
                break;
            default: printf("wrong choice!");
        }
    }
}
