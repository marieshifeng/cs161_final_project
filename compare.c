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

void findSSShortestPath(graphT g, int v, int **distance) {
// int* findSSShortestPath(graphT g, int v) {
    queueT queue = QueueInit(n);
    // GraphPrint(g);
    // int* distance = malloc(sizeof(int) * n);
    int* parent = malloc(sizeof(int) * n);
    for (int i = 0; i < n; ++i) {
        // distance[i] = INT_MAX;
        (*distance)[i] = INT_MAX;
        parent[i] = UNDEFINED;
    }
    // distance[v] = 0;
    (*distance)[v] = 0;
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
            if ((*distance)[w] == INT_MAX){
            // if (distance[w] == INT_MAX){
                parent[w] = t;
                // distance[w] = distance[t] + 1;
                (*distance)[w] = (*distance)[t] + 1;
                QueueEnqueue(queue, w);
                // printf("Enqueued %d\n", w);
            }
        }
    }
    // printArray(distance, n);
    QueueDestroy(queue);
    free(parent);
}

float findAvgSingleArrayInt(int* array){
    int sum = 0;
    for(int i=0; i<n; ++i){
        if (array[i] != INT_MAX){
            sum += array[i];
        }
    }
    float avg = (float)sum/(float)n;
    return avg;
}

float findAvgSingleArrayFloat(float* array){
    float sum = 0;
    for(int i = 0; i< n; ++i){
      sum += array[i];
    }
    float avg = sum/n;
    return avg;
}
    
float findAvgPathLength(graphT g){
    float* vertexAvg = malloc(sizeof(float) * n);
    // int* oneVertex;
    for (int i = 0; i < n; ++i){
        int* distance = malloc(sizeof(int) * n);
        findSSShortestPath(g, i, &distance);
        vertexAvg[i] = findAvgSingleArrayInt(distance);
        free(distance);
        printf("Calculating Shortest Path for Node %d\n", i);
    }
    float avgPL = findAvgSingleArrayFloat(vertexAvg);
    free(vertexAvg);
    return avgPL;
}

int findMaxOfArray(int* array){
    int max = 0;
    for(int i = 0; i< n; ++i){
      if (max < array[i] && array[i] != INT_MAX) max = array[i];
    }
    return max;
}

void findAvgPathLengthNetworkDiameter(graphT g, float* avg, int* max){
    int insideMax = 0;
    float* vertexAvg = malloc(sizeof(float) * n);
    for (int i = 0; i < n; ++i){
        int* distance = malloc(sizeof(int) * n);
        findSSShortestPath(g, i, &distance);
        vertexAvg[i] = findAvgSingleArrayInt(distance);

        int thisMax = findMaxOfArray(distance);
        if (insideMax < thisMax) insideMax = thisMax;

        free(distance);
        printf("Calculating Shortest Path for Node %d\n", i);
    }
    *avg = findAvgSingleArrayFloat(vertexAvg);
    *max = insideMax;
    free(vertexAvg);
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
    float avg;
    int max;
    findAvgPathLengthNetworkDiameter(graph, &avg, &max);
    printf("Graph: %s\n Average Shortest Path: %f  Network Diameter: %d\n", argv[1], avg, max);
    GraphDestroy(graph);
    // queueT q = QueueInit(10);
    // for (int i = 0; i < 10; i++) {
    //     QueueEnqueue(q, i);
    //     printf("%d ", i);
    //     if (i < 10) printf("> ");
    // }
    // printf("\n");
    // while (!QueueIsEmpty(q)) {
    //     printf("%d ", QueueDequeue(q));
    // }
    // QueueDestroy(q);
    return 0; 
} 