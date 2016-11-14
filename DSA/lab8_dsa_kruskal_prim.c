/**
 * 
 * Kruskal algorithm
 * Master 01 - Computer Engineering - Data Structures and Algorithms
 * By: Issam
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#define INF 999

int a,b,u,v,n,i,j,ne=1,choice;
int visited[10]={0},min,mincost=0,cost2[10][10],cost[10][10],parent[10];

void prim() {
    printf("\n\tImplementation of Prim's algorithm\n");
    printf("The edges of Minimum Cost Spanning Tree are:\n");
    visited[1]=1;
    printf("\n");
    while(ne < n) {
        for(i=1,min=999;i<=n;i++)
            for(j=1;j<=n;j++)
		if(cost[i][j]< min)
                    if(visited[i]!=0) {
			min=cost[i][j];
			a=u=i;
			b=v=j;
                    }
                if(visited[u]==0 || visited[v]==0) {
                    printf("\n Edge %d:(%d %d) cost:%d",ne++,a,b,min);
                    mincost+=min;
                    visited[b]=1;
                }
		cost[a][b]=cost[b][a]=999;
    }
    printf("\n Minimun cost=%d",mincost);
}

int find(int i) {
    while(parent[i])
	i=parent[i];
    return i;
}

int uni(int i,int j) {
    if(i!=j) {
        parent[j]=i;
        return 1;
    }
    return 0;
}

void kruskall() {
    printf("\n\tImplementation of Kruskal's algorithm\n");
    printf("The edges of Minimum Cost Spanning Tree are:\n");
    while(ne < n) {
        for(i=1,min=999;i<=n;i++) {
            for(j=1;j<= n;j++) {
                if(cost2[i][j] < min) {
                    min=cost2[i][j];
                    a=u=i;
                    b=v=j;
                }
            }
        }
        u=find(u);
        v=find(v);
        if(uni(u,v)) {
            printf("%d edge (%d,%d) =%d\n",ne++,a,b,min);
            mincost +=min;
        }
        cost2[a][b]=cost2[b][a]=999;
    }
    printf("\n\tMinimum cost = %d\n",mincost);
}

int main() {
  ne=1, mincost=0;
  for(i=0;i<10;i++)
      visited[i]=0;
    printf("Enter the number of nodes:");
    scanf("%d",&n);
    printf("Enter the adjacency matrix:\n");
    for(i=1;i<=n;i++)
        for(j=1;j<=n;j++) {
            if(cost[i][j]==0) {
                cost[i][j]=INF;
                cost2[i][j]=INF;
            }
            if(i!=j) {
                printf("<%d, %d>", i, j);
                scanf("%d",&cost[i][j]);
                cost2[i][j]=cost[i][j];
            }
	}
    printf("\n1)Prim's Algorithm\n2)Kruskall's Algorithm\n");
    scanf("%d",&choice);
    while(choice < 3) {
        ne=1;
        mincost=0;
        if (choice==1)
            prim();
        else if (choice==2)
            kruskall();
        else
            printf("No such choice");
        printf("\n1)Prim's Algorithm\n2)Kruskall's Algorithm\n");
        scanf("%d",&choice);
    }
    return 0;
}
