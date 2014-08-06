#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "helpers/graph.h"
#include "helpers/stack.h"

#define LIMIT 5
#define UNDEFINED (-1)

// Globals needed for Tarjan's algorithm
int index = 0;
int *vertexIndex;
int *lowlink;
char *onStack;
int *vIndex;
int *parent;

// Globals for comparison against real-world networks
int counter = 0;
int *allSCCs;
int numVertices = 0;

void InitializeArrays(int n) {
  vertexIndex = malloc(sizeof(int) * n);
  lowlink = malloc(sizeof(int) * n);
  vIndex = malloc(sizeof(int) * n);
  parent = malloc(sizeof(int) * n);
  onStack = malloc(sizeof(char) * n);
  allSCCs = malloc(sizeof(int) * n);
  numVertices = n;
  for (int i = 0; i < n; ++i) {
    vertexIndex[i] = UNDEFINED;
    lowlink[i] = UNDEFINED;
    onStack[i] = 0;
    allSCCs[i] = 0;
  }
}

int intcmpmax(const void *a, const void *b) { 
  return *((const int *) b) - *((const int *) a); 
}

void AddElementToCompareFile(int element) {
  allSCCs[counter++] = element;
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

void IterativeTarjan(int v, stackT s, graphT g) {
  vertexIndex[v] = index;
  lowlink[v] = index;
  ++index;
  vIndex[v] = 0;
  StackPush(s, v);
  parent[v] = UNDEFINED;
  onStack[v] = 1;
  int last = v;
  while (1) {
    if (vIndex[last] < GraphOutDegreeForVertex(g, last)) {
      int w = g->alist[last]->list[vIndex[last]];
      vIndex[last]++;
      if (vertexIndex[w] == UNDEFINED) {
        parent[w] = last;
        vIndex[w] = 0;
        vertexIndex[w] = index;
        lowlink[w] = index;
        ++index;
        StackPush(s, w);
        onStack[w] = 1;
        last = w;
      } else if (onStack[w] && vertexIndex[w] < lowlink[last]) {
        lowlink[last] = vertexIndex[w];
      }
    } else {
      if (lowlink[last] == vertexIndex[last]) {
        int top = StackPop(s);
        onStack[top] = 0;
        int size = 1;
        while(top != last) {
          top = StackPop(s);
          onStack[top] = 0;
          size++;
        }
        AddElementToCompareFile(size);
      }
      int newLast = parent[last];
      if (newLast != UNDEFINED) {
        if (lowlink[last] < lowlink[newLast]) { 
          lowlink[newLast] = lowlink[last]; 
        }
        last = newLast;
      } else {
        break;
      }
    }
  }
  qsort(allSCCs, numVertices, sizeof(int), intcmpmax); 
}

void FindSCCs(const char *inputFile) {
  graphT g = ReadFileAndBuildGraph(inputFile);
  stackT s = StackInit(GraphNumVertices(g));
  InitializeArrays(GraphNumVertices(g));
  for (int i = 0; i < GraphNumVertices(g); ++i) {
    if (vertexIndex[i] == UNDEFINED) { IterativeTarjan(i, s, g); }
  }
  StackDestroy(s);
  GraphDestroy(g);
  free(vertexIndex);
  free(lowlink);
  free(onStack);
  free(vIndex);
  free(parent);
  free(allSCCs);
}

void PrintSCCs(const char *outputFile) {
  FILE *out = fopen(outputFile, "w");
  if (out == NULL) {
    fprintf(stderr, "Couldn't open output file %s!\n", outputFile);
    exit(1);
  }
  fprintf(out, "Total SCCs: %d\n", counter);
  for (unsigned i = 0; i < numVertices; ++i) {
    fprintf(out, "%u\n", allSCCs[i]);
  }
  fclose(out);
}

int main(int argc, char **argv) {
  assert(argc == 3);
  FindSCCs(argv[1]);
  PrintSCCs(argv[2]);
  return 0; 
} 