/**
 * 
 * Memory management
 * fixed memory
 * Master 01 - Computer Engineering - Data Structures and Algorithms
 * By: Issam
 * 
 */

#include <stdio.h>
#define max 25

int main() {
    int i,j;
    int xfrag = 0, frag[max],part[max],proc[max],npart,nproc,temp,lowest = 1000;
    static int used[max],alloc[max];
    int choice;
    printf("Enter the number of partitions:");
    scanf("%d",&npart);
    printf("Enter the number of processes:");
    scanf("%d",&nproc);
    printf("Enter the size of partitions:\n");
    for(i=1;i<=npart;i++) {
        printf("Partition %d: ",i);
        scanf("%d",&part[i]);
    }
    printf("Enter the size of processes:\n");
    for(i=1;i<=nproc;i++) {
        printf("Process %d: ",i);
        scanf("%d",&proc[i]);
    }

    // first fit
    for(i=1;i<=nproc;i++) {
        for(j=1;j<=npart;j++) {
            if(used[j]!=1) {
                temp=part[j]-proc[i];
                if(temp>=0) {
                    alloc[i]=j;
                    break;
                }
            }
        }
        frag[i]=temp;
        used[alloc[i]]=1;
    }
    // external frag
    for(i=1;i<=nproc;i++)
        if(used[i]!= 1)
            xfrag += part[i];
    printf("\n\t\t*** First Fit ***\n");
    printf("\nProc Nb\tMemory Required\tAllocated partition\tFragementation");
    for(i=1;i<=nproc;i++)
        printf("\n%d\t\t%d\t\t\t%d\t\t\t%d",i,proc[i],alloc[i],frag[i]);
    printf("\nExternal fragmentation is: %d\n", xfrag);

    // reset used array that keeps track of partition status
    for(i=1;i<=nproc;i++)
        used[i] = 0;

    // best fit
    for(i=1;i<=nproc;i++) {
        for(j=1;j<=npart;j++) {
            if(used[j]!=1) {
                temp=part[j]-proc[i];
                if(temp>=0)
                    if(lowest>temp) {
                        alloc[i]=j;
                        lowest=temp;
                    }
            }
        }
        frag[i]=lowest;
        used[alloc[i]]=1;
        lowest=1000;
    }
    // external frag
    xfrag = 0;
    for(i=1;i<=nproc;i++)
        if(used[i]!= 1)
            xfrag += part[i];
    printf("\n\t\t*** Best Fit ***\n");
    printf("\nProc Nb\tMemory Required\tAllocated partition\tFragementation");
    for(i=1;i<=nproc && alloc[i]!=0;i++)
        printf("\n%d\t\t%d\t\t\t%d\t\t\t%d",i,proc[i],alloc[i],frag[i]);
    printf("\nExternal fragmentation is: %d\n", xfrag);

    return 0;
}
