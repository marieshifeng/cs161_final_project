#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "helpers/graph.h"

int *inDegreeDistribution;
int *outDegreeDistribution;

void InitializeArrays(int n) {
  inDegreeDistribution = malloc(sizeof(int) * (n));
  outDegreeDistribution = malloc(sizeof(int) * (n));
  for (int i = 0; i < n; ++i) {
    inDegreeDistribution[i] = 0;
    outDegreeDistribution[i] = 0;
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

void BuildDegreesArrays(graphT g) {
  for(int i = 0; i < GraphNumVertices(g); ++i) {
    inDegreeDistribution[GraphInDegreeForVertex(g, i)]++;
    outDegreeDistribution[GraphOutDegreeForVertex(g, i)]++;
  } 
}

int FindMaximumDegree(int n) {
  int maximum = 0;
  for(int i = 0; i < n; ++i) {
    if (inDegreeDistribution[i] > 0 || outDegreeDistribution[i] > 0) {
      if (maximum < i) { maximum = i; }
    }
  }
  return maximum;
}

void PrintDegrees(int maximum, int vertices, int edges, const char *outputFile) {
  FILE *out = fopen(outputFile, "w");
  if (out == NULL) {
    fprintf(stderr, "Couldn't open output file %s!\n", outputFile);
    exit(1);
  }
  fprintf(out, "%d : (%d, %d)\n", maximum, vertices, edges);
  for(int i = 0; i < maximum; ++i) {
    fprintf(out, "%d %d\n", inDegreeDistribution[i], outDegreeDistribution[i]);
  }
  fclose(out);
}

void FindAndPrintDegreeDistribution(graphT g, const char *outputFile) {
  BuildDegreesArrays(g);
  int maximum = FindMaximumDegree(GraphNumVertices(g));
  PrintDegrees(maximum + 1, GraphNumVertices(g), GraphNumEdges(g), outputFile);
}

void FindDegrees(const char *inputFile, const char *outputFile) {
  graphT g = ReadFileAndBuildGraph(inputFile);
  InitializeArrays(GraphNumVertices(g));
  // GraphPrintDegrees(g);
  FindAndPrintDegreeDistribution(g, outputFile);
  GraphDestroy(g);
  free(inDegreeDistribution);
  free(outDegreeDistribution);
}

int main(int argc, char **argv) {
  assert(argc == 3);
  FindDegrees(argv[1], argv[2]);
  return 0; 
} 