#!/bin/sh

"rm" "-rf" "random_graphs_input"
"mkdir" "-p" "random_graphs_input"
"./rg" "1000000" "7000000" "random_graphs_input/1000000_20000000.txt"
"./rg" "1000000" "7000000" "random_graphs_input/1000000_7000000.txt"
"./rg" "100000" "700000" "random_graphs_input/100000_700000.txt"
"./rg" "10000" "70000" "random_graphs_input/10000_70000.txt"

"touch" "outputIterative.txt"
"touch" "outputRecursive.txt"
FILES=random_graphs_input/*
for f in $FILES
do
	printf "Iterative %s " "$f"
  	"time" "./sccIterative" "$f" "outputIterative.txt"
	printf "Recursive %s " "$f"
  	"time" "./sccRecursive" "$f" "outputRecursive.txt"
    "diff" "outputIterative.txt" "outputRecursive.txt"
    printf "\n"
done
"rm" "outputIterative.txt"
"rm" "outputRecursive.txt"
"rm" "-rf" "random_graphs_input"
exit 0