scc: scc_finder.c
	gcc -std=c11 -march=native -Wall -O4 helpers/graph.c helpers/stack.c scc_finder.c -o sccfinder

rg: random_graph.c
	gcc -std=c11 -march=native -Wall -O4 random_graph.c -o randomgraph

compare: compare.c
	gcc -std=c11 -march=native -Wall -O4 helpers/queue.c helpers/graph.c compare.c -o compare

clean:
	rm -rf sccfinder randomgraph
	rm -rf random_graph/lower
	rm -rf random_graph/upper
	rm -rf lower.txt upper.txt
	rm -rf compare
