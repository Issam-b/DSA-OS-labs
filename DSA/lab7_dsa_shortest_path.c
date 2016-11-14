/**
 * 
 * Shortest path algorithm
 * Master 01 - Computer Engineering - Data Structures and Algorithms
 * By: Issam
 * 
 */

#include <stdio.h>
#include <limits.h>    //to use INT_MAX
#include <stdbool.h>   //to use boolean

#define V 6            // Number of vertices in the graph
#define INF 1000      // Define Infinite as a large enough value


//function to find the vertex with minimum distance
int minDistance(int dist[], bool sptSet[]) {
   int v = 0;
   int min = INT_MAX, min_index; // Initialize min value
   for ( v = 0; v < V; v++) 
       if(sptSet[v] == false && dist[v] <= min)
           min = dist[v], min_index = v;
   return min_index;
}

// Dijkstra's single source shortest path algorithm
void dijkstra(int graph[V][V], int src) {
     int i = 0,count = 0,v = 0, u;
     int dist[V];     // The output array. dist[i] will hold the shortest distance from src to i
     bool sptSet[V]; // sptSet[i] will true if vertex i is included in shortest path tree
     // Initialize all distances as INFINITE and stpSet[] as false
     for ( i = 0; i < V; i++)
         dist[i] = INT_MAX, sptSet[i] = false;
     // Distance of source vertex from itself is always 0
     dist[src] = 0;
     // Find shortest path for all vertices
     for ( count = 0; count < V-1; count++) {
       // Pick the minimum distance vertex from the set of vertices not
       // yet processed. u is always equal to src in first iteration.
       u = minDistance(dist, sptSet);
       // Mark the picked vertex as processed
       sptSet[u] = true;
       // Update dist value of the adjacent vertices of the picked vertex.
       for ( v = 0; v < V; v++)
         // Update dist[v] only if is not in sptSet, there is an edge from
         // u to v, and total weight of path from src to  v through u is
         // smaller than current value of dist[v]
         if (!sptSet[v] && graph[u][v] && dist[u] != INT_MAX && dist[u]+graph[u][v] < dist[v])
            dist[v] = dist[u] + graph[u][v];
     }
     // print the constructed distance array
      printf("Vertex\t\tDistance from Source\n");
      for ( i = 0; i < V; i++)
        printf("%d \t\t %d\n", i, dist[i]);
      printf("\n");
}

void floydWarshell (int graph[][V]) {
    int dist[V][V];//output matrix with shortest path
    int i, j, k;
    // Initialize the solution matrix same as input graph matrix
    for (i = 0; i < V; i++)
        for (j = 0; j < V; j++)
            dist[i][j] = graph[i][j];
    // Add all vertices one by one to the set of intermediate vertices.
    for (k = 0; k < V; k++) {
        // Pick all vertices as source one by one
        for (i = 0; i < V; i++) {
            // Pick all vertices as destination for the picked source
            for (j = 0; j < V; j++) {
                // If vertex k is on the shortest path from i to j, then update the value of dist[i][j]
                if (dist[i][k] + dist[k][j] < dist[i][j])
                    dist[i][j] = dist[i][k] + dist[k][j];
            }
        }
    }
    // Print the shortest distance matrix
    printf ("Shortest distances between every pair of vertices\n\n");
    for ( i = 0; i < V; i++) {
        for ( j = 0; j < V; j++) {
            if (dist[i][j] == INF)
                printf("%7s", "INF");
            else
                printf ("%7d", dist[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

int main() {
    int i=0,j=0,s,temp,choice;
    int graph [V][V];
    printf("**** MENU ****\n\n1)Floyd Warshell\n2)Dijkstra\n\n$ > Choice: ");
    scanf("%d",&choice);
    while(choice<3) {
        switch (choice) {
            case 1:
                printf("Note: infinity is 888\nEnter distance:\n");
                for(i=0;i<V;i++) {
                    for(j=0;j<V;j++) {
                        if (i==j) graph[i][j]=0;
                            else {
                            printf("<%d ,%d>:",i,j);
                            scanf("%d",&temp);
                            if (temp==888) 
                                graph[i][j]=INF;
                            else
                                graph[i][j]=temp;
                            }
                        }
                }
                printf("\n");
                floydWarshell(graph);
                break;
            case 2:
                printf("Enter distance:\n");
                for(i=0;i<V;i++) {
                    for(j=0;j<V;j++) {
                        if (i==j)
                            graph[i][j]=0;
                        else {
                            printf("<%d ,%d>:",i,j);
                            scanf("%d",&graph[i][j]);
                        }
                    }
                }
                do {
                    printf("Source:");
                    scanf("%d",&s);
                } while (s>=V);
                dijkstra(graph, s);
                break;
        }
        printf("**** MENU ****\n\n1)Floyd Warshell\n2)Dijkstra\n\n$ > Choice: ");
        scanf("%d",&choice);
    }
    return 0;
}
