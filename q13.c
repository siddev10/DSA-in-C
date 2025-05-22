// 13.	WAP to generate single source shortest path using Dijkstra’s algorithm when graph is represented by Adjacency matrix and list.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>
int minDistance(int dist[], bool sptSet[], int V) {
    int min = INT_MAX, min_index;
    
    for (int v = 0; v < V; v++)
        if (sptSet[v] == false && dist[v] <= min)
            min = dist[v], min_index = v;
    
    return min_index;
}

void dijkstra(int** graph, int src, int V) {
    int* dist = (int*)malloc(V * sizeof(int));
    bool* sptSet = (bool*)malloc(V * sizeof(bool));
    
    for (int i = 0; i < V; i++)
        dist[i] = INT_MAX, sptSet[i] = false;
    
    dist[src] = 0;
    
    for (int count = 0; count < V - 1; count++) {
        int u = minDistance(dist, sptSet, V);
        sptSet[u] = true;
        
        for (int v = 0; v < V; v++)
            if (!sptSet[v] && graph[u][v] && dist[u] != INT_MAX
                && dist[u] + graph[u][v] < dist[v])
                dist[v] = dist[u] + graph[u][v];
    }
    
    printf("Vertex \t Distance from Source %d\n", src);
    for (int i = 0; i < V; i++)
        printf("%d \t\t %d\n", i, dist[i]);
    
    free(dist);
    free(sptSet);
}

int main() {
    printf("=== QUESTION 13: Dijkstra's Algorithm ===\n");
    
    int V, src;
    printf("Enter number of vertices: ");
    scanf("%d", &V);
    
    // Allocate memory for adjacency matrix
    int** graph = (int**)malloc(V * sizeof(int*));
    for (int i = 0; i < V; i++) {
        graph[i] = (int*)malloc(V * sizeof(int));
    }
    
    printf("Enter adjacency matrix (%dx%d):\n", V, V);
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            scanf("%d", &graph[i][j]);
        }
    }
    
    printf("Enter source vertex: ");
    scanf("%d", &src);
    
    dijkstra(graph, src, V);
    
    // Free memory
    for (int i = 0; i < V; i++) {
        free(graph[i]);
    }
    free(graph);
    
    return 0;
}
