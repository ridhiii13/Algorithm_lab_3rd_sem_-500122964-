#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>

#define INF INT_MAX

// Structure to represent an edge in a graph
struct Edge {
    int src, dest, weight;
};

// Structure to represent a graph with V vertices and E edges
struct Graph {
    int V, E;
    struct Edge* edge;
};

// Create a graph with V vertices and E edges
struct Graph* createGraph(int V, int E) {
    struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));
    graph->V = V;
    graph->E = E;
    graph->edge = (struct Edge*)malloc(E * sizeof(struct Edge));
    return graph;
}

// Bellman-Ford Algorithm
void BellmanFord(struct Graph* graph, int src) {
    int V = graph->V;
    int E = graph->E;
    int dist[V];

    // Initialize distances
    for (int i = 0; i < V; i++) {
        dist[i] = INF;
    }
    dist[src] = 0;

    // Relax edges |V| - 1 times
    for (int i = 1; i <= V - 1; i++) {
        for (int j = 0; j < E; j++) {
            int u = graph->edge[j].src;
            int v = graph->edge[j].dest;
            int weight = graph->edge[j].weight;
            if (dist[u] != INF && dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
            }
        }
    }

    // Print distances
    printf("Bellman-Ford distances from source %d:\n", src);
    for (int i = 0; i < V; i++) {
        if (dist[i] == INF)
            printf("Vertex %d: INF\n", i);
        else
            printf("Vertex %d: %d\n", i, dist[i]);
    }
}

// Dijkstra’s Algorithm using an adjacency matrix
void Dijkstra(int graph[100][100], int V, int src) {
    int dist[V];
    int visited[V];

    for (int i = 0; i < V; i++) {
        dist[i] = INF;
        visited[i] = 0;
    }
    dist[src] = 0;

    for (int count = 0; count < V - 1; count++) {
        int min = INF, min_index;
        for (int v = 0; v < V; v++) {
            if (!visited[v] && dist[v] <= min) {
                min = dist[v], min_index = v;
            }
        }
        int u = min_index;
        visited[u] = 1;

        for (int v = 0; v < V; v++) {
            if (!visited[v] && graph[u][v] && dist[u] != INF && dist[u] + graph[u][v] < dist[v]) {
                dist[v] = dist[u] + graph[u][v];
            }
        }
    }

    // Print distances
    printf("Dijkstra distances from source %d:\n", src);
    for (int i = 0; i < V; i++) {
        if (dist[i] == INF)
            printf("Vertex %d: INF\n", i);
        else
            printf("Vertex %d: %d\n", i, dist[i]);
    }
}

// Main function to compare the two algorithms
int main() {
    int V = 5, E = 8;
    struct Graph* graph = createGraph(V, E);

    // Sample graph with edges for Bellman-Ford
    graph->edge[0] = (struct Edge){0, 1, 1};
    graph->edge[1] = (struct Edge){0, 2, 2};
    graph->edge[2] = (struct Edge){1, 2, 1};
    graph->edge[3] = (struct Edge){1, 4, 1};
    graph->edge[4] = (struct Edge){2, 3, 1};
    graph->edge[5] = (struct Edge){0, 3, 3};

    // Adjacency matrix for Dijkstra
    int adjMatrix[100][100] = {
        { 0, 1, 4, 6, 1 }, // Node A (0) connections
        { 1, 0, 0, 2, 0 }, // Node B (1) connections
        { 4, 0, 0, 0, 1 }, // Node C (2) connections
        { 6, 2, 0, 0, 5 }, // Node D (3) connections
        { 1, 0, 1, 5, 0 } // Node E (4) connections
    };
    // Measure Bellman-Ford performance
    clock_t startBellman = clock();
    BellmanFord(graph, 0);
    clock_t endBellman = clock();
    double timeBellman = ((double)(endBellman - startBellman) * 1000.0) / CLOCKS_PER_SEC;

    // Measure Dijkstra performance
    clock_t startDijkstra = clock();
    Dijkstra(adjMatrix, V, 0);
    clock_t endDijkstra = clock();
    double timeDijkstra = ((double)(endDijkstra - startDijkstra) * 1000.0) / CLOCKS_PER_SEC;

    // Print performance results
    printf("\nTime taken by Bellman-Ford: %.2f milliseconds\n", timeBellman);
    printf("Time taken by Dijkstra: %.2f milliseconds\n", timeDijkstra);

    free(graph->edge);
    free(graph);
    return 0;
}
