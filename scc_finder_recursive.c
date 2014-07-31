#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "graph.h"
#include "stack.h"

#define LIMIT 5
#define UNDEFINED (-1)

// Globals needed for Tarjan's algorithm
int index = 0;
int *vertexIndex;
int *lowlink;

// Globals for output file
int output[LIMIT];

void InitializeArrays(int n) {
  vertexIndex = malloc(sizeof(int) * n);
  lowlink = malloc(sizeof(int) * n);
  for (int i = 0; i < n; ++i) {
    vertexIndex[i] = UNDEFINED;
    lowlink[i] = UNDEFINED;
    if (i < LIMIT) { output[i] = 0; } // We are protected because n >= 100
  }
}

int intcmpmax(const void *a, const void *b) { 
  return *((const int *) b) - *((const int *) a); 
}

void AddElementToTarget(int element) {
  output[LIMIT - 1] = element;
  if (output[LIMIT - 1] > output[LIMIT - 2]) { 
    qsort(output, LIMIT, sizeof(int), intcmpmax); 
  }
}

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

void Tarjan(int v, stackT s, graphT g) {
  vertexIndex[v] = index;
  lowlink[v] = index;
  ++index;
  StackPush(s, v);
  for (int i = 0; i < g->alist[v]->d; ++i) { // Loops through all neighbors of v
    int w = g->alist[v]->list[i]; // Given d neighbors of v, w is one neighbor
    if (vertexIndex[w] == UNDEFINED) { // Calls Tarjan if w is unvisited
      Tarjan(w, s, g);
      if (lowlink[w] < lowlink[v]) { lowlink[v] = lowlink[w]; }
    } else if(StackContains(s, w)) {
      if (vertexIndex[w] < lowlink[v]) { lowlink[v] = vertexIndex[w]; }
    }
  }
  if (lowlink[v] == vertexIndex[v]) {
    int w = UNDEFINED - 1;
    int size = 0;
    while(w != v) {
      w = StackPop(s);
      ++size;
    }
    if (size > output[LIMIT - 1]) { AddElementToTarget(size); }
  }
}

void FindSCCs(const char *inputFile) {
  graphT g = ReadFileAndBuildGraph(inputFile);
  stackT s = StackInit(GraphNumVertices(g));
  InitializeArrays(GraphNumVertices(g));
  for (int i = 0; i < GraphNumVertices(g); ++i) {
    if (vertexIndex[i] == UNDEFINED) {
      Tarjan(i, s, g);
    }
  }
  StackDestroy(s);
  GraphDestroy(g);
  free(vertexIndex);
  free(lowlink);
}

void PrintSCCs(const char *outputFile) {
  FILE *out = fopen(outputFile, "w");
  if (out == NULL) {
    fprintf(stderr, "Couldn't open output file %s!\n", outputFile);
    exit(1);
  }
  for (unsigned i = 0; i < LIMIT; ++i) {
    fprintf(out, "%u", output[i]);
    if (i < LIMIT - 1) fprintf(out, "\t");
  }
  fclose(out);
}

int main(int argc, char **argv) {
  assert(argc == 3);
  FindSCCs(argv[1]);
  PrintSCCs(argv[2]);
  return 0; 
} 