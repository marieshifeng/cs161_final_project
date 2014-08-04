scc: scc_finder.c
	gcc -std=c11 -march=native -Wall -O4 helpers/graph.c helpers/stack.c scc_finder.c -o sccfinder

rg: random_graph.c
	gcc -std=c11 -march=native -Wall -O4 random_graph.c -o randomgraph

dd: degree_distribution.c
	gcc -std=c11 -march=native -Wall -O4 helpers/graph.c degree_distribution.c -o degreedistribution

clean:
	rm -rf sccfinder randomgraph degreedistribution
	rm -rf random_graph/lower
	rm -rf random_graph/upper
	rm -rf lower.txt upper.txt