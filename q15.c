// 15.	WAP to implement BFS traversal on graph using Adjacency Matrix and adjacency lists.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>

typedef struct Queue {
    int items[100];
    int front;
    int rear;
} Queue;

Queue* createQueue() {
    Queue* q = (Queue*)malloc(sizeof(Queue));
    q->front = -1;
    q->rear = -1;
    return q;
}

bool isQueueEmpty(Queue* q) {
    return q->rear == -1;
}

void enqueue(Queue* q, int value) {
    if (q->rear == 99) {
        printf("Queue is full\n");
    } else {
        if (q->front == -1)
            q->front = 0;
        q->rear++;
        q->items[q->rear] = value;
    }
}

int dequeue(Queue* q) {
    int item;
    if (isQueueEmpty(q)) {
        printf("Queue is empty\n");
        item = -1;
    } else {
        item = q->items[q->front];
        q->front++;
        if (q->front > q->rear) {
            q->front = q->rear = -1;
        }
    }
    return item;
}

void BFS(int** graph, int V, int start) {
    bool* visited = (bool*)malloc(V * sizeof(bool));
    for (int i = 0; i < V; i++)
        visited[i] = false;
    
    Queue* q = createQueue();
    
    visited[start] = true;
    enqueue(q, start);
    
    printf("BFS Traversal starting from vertex %d: ", start);
    
    while (!isQueueEmpty(q)) {
        int currentVertex = dequeue(q);
        printf("%d ", currentVertex);
        
        for (int i = 0; i < V; i++) {
            if (graph[currentVertex][i] == 1 && !visited[i]) {
                visited[i] = true;
                enqueue(q, i);
            }
        }
    }
    printf("\n");
    
    free(visited);
    free(q);
}

int main() {
    printf("=== QUESTION 15: BFS Traversal ===\n");
    
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
    
    BFS(graph, V, start);
    
    // Free memory
    for (int i = 0; i < V; i++) {
        free(graph[i]);
    }
    free(graph);
    
    return 0;
}
