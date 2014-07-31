#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "graph.h"

#define THRESHOLD (9)

graphT GraphInit(int numVertices) {
    assert(numVertices > 0);
    graphT g;
    g = malloc(sizeof(struct graph) + sizeof(struct successors *) * (numVertices - 1));
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

void GraphDestroy(graphT g) {
    for(int i = 0; i < g->n; ++i) free(g->alist[i]);
    free(g);
}

int GraphNumVertices(graphT g) { return g->n; }

int GraphNumEdges(graphT g) { return g->m; }

int GraphOutDegreeForVertex(graphT g, int source) {
    assert(source > -1);
    assert(source < g->n);
    return g->alist[source]->d;
}

int intcmp(const void *a, const void *b) { return *((const int *) a) - *((const int *) b); }

int GraphHasEdge(graphT g, int source, int sink) {
    assert(source > -1);
    assert(source < g->n);
    assert(sink > -1);
    assert(sink < g->n);
    assert(sink != source);
    if(GraphOutDegreeForVertex(g, source) > THRESHOLD) {
        if(!(g->alist[source]->isSorted)) {
            qsort(g->alist[source]->list, g->alist[source]->d, sizeof(int), intcmp);
        }
        return bsearch( &sink, g->alist[source]->list, g->alist[source]->d, sizeof(int), intcmp) != 0;
    } else {
        for(int i = 0; i < g->alist[source]->d; ++i) {
            if(g->alist[source]->list[i] == sink) return 1;
        }
    }
    return 0;
}

void GraphAddEdge(graphT g, int source, int sink) {
    assert(source > -1); //source is at least one
    assert(source < g->n); //source is no more than n nodes
    assert(sink > -1);
    assert(sink < g->n);
    if (source != sink && !GraphHasEdge(g, source, sink)) { //(1) not adding (u,u) (2) graph has doesn't already have u->v
        while(g->alist[source]->d >= g->alist[source]->len) {
            g->alist[source]->len += 1; // OMG THIS SUCKS!
            g->alist[source] = realloc(g->alist[source], sizeof(struct successors) + sizeof(int) * (g->alist[source]->len - 1));
        }
        g->alist[source]->list[g->alist[source]->d++] = sink;
        g->alist[source]->isSorted = 0;
        g->m++;
    }
}

void GraphForEach(graphT g, int source, void (*f)(graphT g, int source, int sink, void *data), void *data) {
    assert(source > -1);
    assert(source < g->n);
    for(int i = 0; i < g->alist[source]->d; ++i) { f(g, source, g->alist[source]->list[i], data); }
}

void GraphPrint(graphT g) {
    for (int i = 0; i < g->n; ++i) {
        printf("Vertex %d: ", i);
        for (int j = 0; j < g->alist[i]->d; ++j) {
            printf("%d ", g->alist[i]->list[j]);
        }
        printf("\n");
    }
}

void GraphPrintDescription(graphT g) { printf("The graph has %d nodes and %d edges.\n", g->n, g->m); }