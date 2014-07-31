scc: scc_finder_iterative.c scc_finder_recursive.c
	gcc -std=c11 -march=native -Wall -O4 graph.c stack.c scc_finder_iterative.c -o sccIterative
	gcc -std=c11 -march=native -Wall -O4 graph.c stack.c scc_finder_recursive.c -o sccRecursive

sccIterative: scc_finder_iterative.c
	gcc -std=c11 -march=native -Wall -O4 graph.c stack.c scc_finder_iterative.c -o sccIterative

sccRecursive: scc_finder_recursive.c
	gcc -std=c11 -march=native -Wall -O4 graph.c stack.c scc_finder_recursive.c -o sccRecursive

rg: random_graph.c
	gcc -std=c11 -march=native -Wall -O4 random_graph.c -o rg

clean:
	rm -f sccIterative sccRecursive rg
