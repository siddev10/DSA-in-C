// 14.	WAP to implement DFS traversal on graph using Adjacency Matrix and adjacency lists.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>

void DFSUtil(int** graph, int v, bool visited[], int V) {
    visited[v] = true;
    printf("%d ", v);
    
    for (int i = 0; i < V; i++)
        if (graph[v][i] && !visited[i])
            DFSUtil(graph, i, visited, V);
}

void DFS(int** graph, int V, int start) {
    bool* visited = (bool*)malloc(V * sizeof(bool));
    for (int i = 0; i < V; i++)
        visited[i] = false;
    
    printf("DFS Traversal starting from vertex %d: ", start);
    DFSUtil(graph, start, visited, V);
    printf("\n");
    
    free(visited);
}


int main() {
    printf("=== QUESTION 14: DFS Traversal ===\n");
    
    int V, start;
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
    
    printf("Enter starting vertex: ");
    scanf("%d", &start);
    
    DFS(graph, V, start);
    
    // Free memory
    for (int i = 0; i < V; i++) {
        free(graph[i]);
    }
    free(graph);
    
    return 0;
}
