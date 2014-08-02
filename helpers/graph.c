#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "graph.h"

#define THRESHOLD (9)

graphT GraphInit(int numVertices) {
    assert(numVertices > 0);
    graphT g;
    g = malloc(sizeof(struct graph) + sizeof(struct successors *) * 
        (numVertices - 1));
    assert(g);
    g->n = numVertices;
    g->m = 0;
    for(int i = 0; i < numVertices; ++i) {
        g->alist[i] = malloc(sizeof(struct successors));
        assert(g->alist[i]);
        g->alist[i]->d = 0;
        g->alist[i]->len = 1;
        g->alist[i]->isSorted= 1;
    }
    return g;
}

int GraphNumVertices(graphT g) { return g->n; }

int GraphNumEdges(graphT g) { return g->m; }

void GraphDestroy(graphT g) {
    for(int i = 0; i < GraphNumVertices(g); ++i) free(g->alist[i]);
    free(g);
}

int GraphOutDegreeForVertex(graphT g, int source) {
    assert(source > -1);
    assert(source < GraphNumVertices(g));
    return g->alist[source]->d;
}

int intcmp(const void *a, const void *b) { 
    return *((const int *) a) - *((const int *) b); 
}

int GraphHasEdge(graphT g, int source, int sink) {
    assert(source > -1);
    assert(source < GraphNumVertices(g));
    assert(sink > -1);
    assert(sink < GraphNumVertices(g));
    assert(sink != source);
    if(GraphOutDegreeForVertex(g, source) > THRESHOLD) {
        if(!(g->alist[source]->isSorted)) {
            qsort(g->alist[source]->list, GraphOutDegreeForVertex(g, source), 
                sizeof(int), intcmp);
        }
        return (bsearch( &sink, g->alist[source]->list, 
            GraphOutDegreeForVertex(g, source), sizeof(int), intcmp) != 0);
    } else {
        for(int i = 0; i < GraphOutDegreeForVertex(g, source); ++i) {
            if(g->alist[source]->list[i] == sink) return 1;
        }
    }
    return 0;
}

void GraphAddEdge(graphT g, int source, int sink) {
    assert(source > -1); // Souce must be at least one
    assert(source < GraphNumVertices(g)); // Souce must be no more than n
    assert(sink > -1);
    assert(sink < GraphNumVertices(g));
    // (1) Does not add (u, u)
    // (2) Graph doesn't already have u -> v
    if (source != sink && !GraphHasEdge(g, source, sink)) {
        while(GraphOutDegreeForVertex(g, source) >= g->alist[source]->len) {
            g->alist[source]->len *= 2;
            g->alist[source] = realloc(g->alist[source], 
                sizeof(struct successors) + sizeof(int) * 
                (g->alist[source]->len - 1));
        }
        g->alist[source]->list[g->alist[source]->d++] = sink;
        g->alist[source]->isSorted = 0;
        g->m++;
    }
}

void GraphForEach(graphT g, int source, 
    void (*f)(graphT g, int source, int sink, void *data), void *data) {
    assert(source > -1);
    assert(source < GraphNumVertices(g));
    for(int i = 0; i < GraphOutDegreeForVertex(g, source); ++i) { 
        f(g, source, g->alist[source]->list[i], data); 
    }
}

void GraphPrint(graphT g) {
    for (int i = 0; i < GraphNumVertices(g); ++i) {
        printf("Vertex %d: ", i);
        for (int j = 0; j < GraphOutDegreeForVertex(g, i); ++j) {
            printf("%d ", g->alist[i]->list[j]);
        }
        printf("\n");
    }
}

void GraphPrintDescription(graphT g) { 
    printf("The graph has %d nodes and %d edges.\n", 
        GraphNumVertices(g), GraphNumEdges(g)); 
}