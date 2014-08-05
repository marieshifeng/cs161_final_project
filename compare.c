#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <limits.h>
#include "helpers/graph.h"
#include "helpers/queue.h"

#define LIMIT 5
#define UNDEFINED (-1)

/*global*/
int n;

graphT ReadFileAndBuildGraph(const char *inputFile) {
  FILE *ifp = fopen(inputFile, "r");
  int n, m;
  fscanf(ifp, "%d", &n);
  fscanf(ifp, "%d", &m);
  graphT g = GraphInit(n);
  for (int i = 0; i < m; ++i) {
    int u, v;
    fscanf(ifp, "%d %d", &u, &v);
    // Input graphs are indexed from 1 to n and we represent graphs from 
    // 0 to n-1
    --u;
    --v;
    GraphAddEdge(g, u, v);
  }
  fclose(ifp);
  return g;
}

void printArray(int* a, int n){
    for(int i = 0; i < n; ++i){
        printf(" | %d ", a[i]);
    }
    printf("\n");
}

int* findSSShortestPath(graphT g, int v) {
    queueT queue = QueueInit(n);
    // GraphPrint(g);
    int* distance = malloc(sizeof(int) * n);
    int* parent = malloc(sizeof(int) * n);
    for (int i = 0; i < n; ++i) {
        distance[i] = INT_MAX;
        parent[i] = UNDEFINED;
    }
    distance[v] = 0;
    // printArray(distance, n);
    QueueEnqueue(queue, v);
    // printf("Enqueued %d\n", v);

    while (!QueueIsEmpty(queue)){

        int t = QueueDequeue(queue);
        // printf("Dequeued %d\n", t);

        // printf("Neighbor of %d: \n", t);
        for (int i = 0; i < GraphOutDegreeForVertex(g, t); ++i) {
            int w = g->alist[t]->list[i];
            // printf("    %d\n", w);
            if (distance[w] == INT_MAX){
                parent[w] = t;
                distance[w] = distance[t] + 1;
                QueueEnqueue(queue, w);
                // printf("Enqueued %d\n", w);
            }
        }
    }
    printArray(distance, n);
    free(parent);
    return distance;
}

float findAveragePathLengthOneVertex(int* distance){
    int sum = 0;
    for(int i=0; i<n; ++i){
      sum += distance[i];
    }
    float avg = (float)sum/(float)n;
    return avg;
}
    
/* average number of nodes in the shortest path between all pairs of nodes */
//(1) for a given pair of nodes, find shortest path between them in terms of number of hops (nodes)
//(2) iterate (1) for ALL pairs of nodes
//(3) take average
//assumption: node "a" to itself has a path of 1 if there's an edge from A to A, also start at 0
int findAvgPathLength(graphT g){
    int* eachVertexAvgs = malloc(sizeof(int) * n);

    // for (int i = 0; i < m; ++i){
    //     eachVertexAvgs[i] = 
    // }
    return 5;
}

/*the maximum (shortest path) distance between any pair of nodes in a graph*/
void findNetworkDiameter(graphT g){
  return;
}

void findNumTriangles(graphT g){
  return;
}

int main(int argc, char **argv) {
    graphT graph = ReadFileAndBuildGraph(argv[1]);
    n = GraphNumVertices(graph);
    int* spath = findSSShortestPath(graph, 0);
    float avg = findAveragePathLengthOneVertex(spath);
    printf("Avg shortest path for node 0: %f\n", avg);
    return 0; 
} 