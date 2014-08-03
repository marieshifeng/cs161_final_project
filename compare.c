#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "helpers/graph.h"
#include "helpers/stack.h"

#define LIMIT 5
#define UNDEFINED (-1)



void findShortestPath(int u, int v){

}

/* average number of nodes in the shortest path between all pairs of nodes */
//(1) for a given pair of nodes, find shortest path between them in terms of number of hops (nodes)
//(2) iterate (1) for ALL pairs of nodes
//(3) take average
//assumption: node "a" to itself has a path of 1 if there's an edge from A to A, also start at 0
void findAvgPathLength(GraphT g){

}

/*average minimum distance between all pairs of nodes*/
//(1) for a given pair of nodes, find shortest path between them in terms of "number of edges needed"
//(2) iterate (1) for ALL pairs of nodes
//(3) take average
//assumption: node "a" to itself is only valid when there's an edge to itself
void findNetworkDiameter(GraphT g){

}

void findNumTriangles(GraphT g){

}