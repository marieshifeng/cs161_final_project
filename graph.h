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

// struct vertex {
// 	int value;
// 	vertex *next;
// };

// typedef struct vertex *vertexT;

// struct graph {
//     int n; // Number of vertices
//     int m; // Number of edges
//     struct successors {
//     	int d; // Out degree; probably can remove...
//         char isSorted;
//         vertexT v;
//     } *alist[1];
// };

typedef struct graph *graphT;

graphT GraphInit(int numVertices);
void GraphDestroy(graphT g);
int GraphNumVertices(graphT g);
int GraphNumEdges(graphT g);
int GraphOutDegreeForVertex(graphT g, int source);
int GraphHasEdge(graphT g, int source, int sink);
void GraphAddEdge(graphT g, int source, int sink);
void GraphForEach(graphT g, int source, void (*f)(graphT g, int source, int sink, void *data), void *data);
void GraphPrint(graphT g);
void GraphPrintDescription(graphT g);

#endif  /* not defined _GRAPH_H */