/*  
 * This is the interface for a graph backed by 
 * adjacency list. Vertices and edges are integers.
 */

#ifndef _GRAPH_H
#define _GRAPH_H

struct graph {
    int n;             
    int m;              
    struct successors {
        int d; // Out degree of vertex
        int len; // Capacity of array
        char isSorted;
        int list[1]; 
    } *alist[1];
};

typedef struct graph *graphT;
graphT GraphInit(int numVertices);
int GraphNumVertices(graphT g);
int GraphNumEdges(graphT g);
void GraphDestroy(graphT g);
int GraphOutDegreeForVertex(graphT g, int source);
int GraphHasEdge(graphT g, int source, int sink);
void GraphAddEdge(graphT g, int source, int sink);
void GraphForEach(graphT g, int source, void (*f)(graphT g, int source, int sink, void *data), void *data);
void GraphPrint(graphT g);
void GraphPrintDescription(graphT g);

#endif  /* not defined _GRAPH_H */