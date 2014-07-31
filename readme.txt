Part I: Strongly connected components
Contains:
	1. scc_finder_iterative.c: implements Tarjan's algorithm with iterative DFS
	2. scc_finder_recursive.c: implements Tarjan's algorithm with recursive DFS
	2. graph.c, graph.h: graph representation backed by adjacency lists
	3. stack.c, stack.h: stacks for integers
	4. input, correct_output directories: local copies of input and golden 
	output files

How to run stuff:
	1. "make scc"
	2. "sh scripts/scc.sh”
---
Part II: Randomized graphs
Contains:
	1. random_graph.c: creates a random graph with n vertices and m edges 
	indexed from 1 to n

How to run stuff:
	1. "make r”g
	2. "sh scripts/rg.sh”