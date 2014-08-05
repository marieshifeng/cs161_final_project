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

// Globals for output file
int output[LIMIT];

void InitializeArrays(int n) {
  vertexIndex = malloc(sizeof(int) * n);
  lowlink = malloc(sizeof(int) * n);
  vIndex = malloc(sizeof(int) * n);
  parent = malloc(sizeof(int) * n);
  onStack = malloc(sizeof(char) * n);
  for (int i = 0; i < n; ++i) {
    vertexIndex[i] = UNDEFINED;
    lowlink[i] = UNDEFINED;
    onStack[i] = 0;
    if (i < LIMIT) { output[i] = 0; }
  }
}

int intcmpmax(const void *a, const void *b) { 
  return *((const int *) b) - *((const int *) a); 
}

void AddElementToOutput(int element) {
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
    if (vIndex[last] < GraphOutDegreeForVertex(g,last)) {
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
        if (size > output[LIMIT - 1]) { AddElementToOutput(size); }
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
}

void FindSCCs(const char *inputFile) {
  graphT g = ReadFileAndBuildGraph(inputFile);
  stackT s = StackInit(GraphNumVertices(g));
  InitializeArrays(GraphNumVertices(g));
  for (int i = 0; i < GraphNumVertices(g); ++i) {
    if (vertexIndex[i] == UNDEFINED) {
      IterativeTarjan(i, s, g);
    }
  }
  GraphPrint(g);
  StackDestroy(s);
  GraphDestroy(g);
  free(vertexIndex);
  free(lowlink);
  free(onStack);
  free(vIndex);
  free(parent);
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