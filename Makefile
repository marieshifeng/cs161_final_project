scc: scc_finder.c
	gcc -std=c11 -march=native -Wall -O4 graph.c stack.c scc_finder.c -o sccfinder

rg: random_graph.c
	gcc -std=c11 -march=native -Wall -O4 random_graph.c -o randomgraph

clean:
	rm -f sccIterative sccRecursive rg
	rm -rf random_graph/input
	rm -rf random_graph/my_output