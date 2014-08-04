#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "helpers/graph.h"
#include "helpers/queue.h"

#define LIMIT 5
#define UNDEFINED (-1)


void findShortestPath(graphT g, int u, int v){
    // queue

// 1  procedure BFS(G,v) is
// 2      create a queue Q
// 3      create a set V
// 4      add v to V
// 5      enqueue v onto Q
// 6      while Q is not empty loop
// 7         t ← Q.dequeue()
// 8         if t is what we are looking for then
// 9            return t
// 10        end if
// 11        for all edges e in G.adjacentEdges(t) loop
// 12           u ← G.adjacentVertex(t,e)
// 13           if u is not in V then
// 14               add u to V
// 15               enqueue u onto Q
// 16           end if
// 17        end loop
// 18     end loop
// 19     return none
// 20 end BFS
}

/* average number of nodes in the shortest path between all pairs of nodes */
//(1) for a given pair of nodes, find shortest path between them in terms of number of hops (nodes)
//(2) iterate (1) for ALL pairs of nodes
//(3) take average
//assumption: node "a" to itself has a path of 1 if there's an edge from A to A, also start at 0
void findAvgPathLength(graphT g){
  return;
}

/*average minimum distance between all pairs of nodes*/
//(1) for a given pair of nodes, find shortest path between them in terms of "number of edges needed"
//(2) iterate (1) for ALL pairs of nodes
//(3) take average
//assumption: node "a" to itself is only valid when there's an edge to itself
void findNetworkDiameter(graphT g){
  return;
}

void findNumTriangles(graphT g){
  return;
}

int main(int argc, char **argv) {
  queueT q = QueueInit(100);
  QueueDestroy(q);
  printf("HI - moving along\n");
  return 0; 
} 