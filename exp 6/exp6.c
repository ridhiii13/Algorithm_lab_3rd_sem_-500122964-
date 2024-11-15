#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>

#define V 5  // Number of vertices in the graph
#define INF INT_MAX

void dijkstra(int graph[V][V], int src);
void bellmanFord(int graph[V][V], int src);

int minDistance(int dist[], int sptSet[]);
void printSolution(int dist[], int n);

int main() {
    // Adjacency matrix representation of a weighted graph
    int graph[V][V] = {
        {0, 4, INF, INF, INF},
        {4, 0, 8, INF, INF},
        {INF, 8, 0, 7, INF},
        {INF, INF, 7, 0, 9},
        {INF, INF, INF, 9, 0}
    };

    int src = 0;  // Starting vertex

    // Measure performance of Dijkstra's Algorithm
    clock_t start = clock();
    printf("Dijkstra's Algorithm:\n");
    dijkstra(graph, src);
    clock_t end = clock();
    double time_dijkstra = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Time taken by Dijkstra's Algorithm: %.6f seconds\n\n", time_dijkstra);

    // Measure performance of Bellman-Ford Algorithm
    start = clock();
    printf("Bellman-Ford Algorithm:\n");
    bellmanFord(graph, src);
    end = clock();
    double time_bellman = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Time taken by Bellman-Ford Algorithm: %.6f seconds\n", time_bellman);

    return 0;
}

// Function for Dijkstra's Algorithm
void dijkstra(int graph[V][V], int src) {
    int dist[V];   // Distance array to hold the shortest path tree
    int sptSet[V]; // Shortest path tree set

    // Initialize all distances to infinity and sptSet[] as false
    for (int i = 0; i < V; i++) {
        dist[i] = INF;
        sptSet[i] = 0;
    }
    dist[src] = 0;

    // Find shortest path for all vertices
    for (int count = 0; count < V - 1; count++) {
        int u = minDistance(dist, sptSet);
        sptSet[u] = 1;

        // Update distance value of adjacent vertices
        for (int v = 0; v < V; v++) {
            if (!sptSet[v] && graph[u][v] && dist[u] != INF && dist[u] + graph[u][v] < dist[v]) {
                dist[v] = dist[u] + graph[u][v];
            }
        }
    }

    printSolution(dist, V);
}

// Helper function for Dijkstra's Algorithm to find the vertex with minimum distance
int minDistance(int dist[], int sptSet[]) {
    int min = INF, min_index;
    for (int v = 0; v < V; v++) {
        if (sptSet[v] == 0 && dist[v] <= min) {
            min = dist[v];
            min_index = v;
        }
    }
    return min_index;
}

// Function for Bellman-Ford Algorithm
void bellmanFord(int graph[V][V], int src) {
    int dist[V];

    // Initialize distances from src to all other vertices as INFINITE
    for (int i = 0; i < V; i++) {
        dist[i] = INF;
    }
    dist[src] = 0;

    // Relax all edges |V| - 1 times
    for (int i = 1; i < V; i++) {
        for (int u = 0; u < V; u++) {
            for (int v = 0; v < V; v++) {
                if (graph[u][v] != INF && dist[u] != INF && dist[u] + graph[u][v] < dist[v]) {
                    dist[v] = dist[u] + graph[u][v];
                }
            }
        }
    }

    // Check for negative-weight cycles
    for (int u = 0; u < V; u++) {
        for (int v = 0; v < V; v++) {
            if (graph[u][v] != INF && dist[u] != INF && dist[u] + graph[u][v] < dist[v]) {
                printf("Graph contains negative weight cycle\n");
                return;
            }
        }
    }

    printSolution(dist, V);
}

// Function to print the final distances
void printSolution(int dist[], int n) {
    printf("Vertex \t Distance from Source\n");
    for (int i = 0; i < n; i++) {
        if (dist[i] == INF) {
            printf("%d \t\t INF\n", i);
        } else {
            printf("%d \t\t %d\n", i, dist[i]);
        }
    }
    printf("\n");
}