#!/bin/sh
"touch" "outputIterative.txt"
"touch" "outputRecursive.txt"
FILES=random_graphs_input/*
for f in $FILES
do
	printf "Iterative %s " "$f"
  	"time" "./sccIterative" "$f" "outputIterative.txt"
  	cat "outputIterative.txt"
	printf "\nRecursive %s " "$f"
  	"time" "./sccRecursive" "$f" "outputRecursive.txt"
  	cat "outputRecursive.txt"
    "diff" "outputIterative.txt" "outputRecursive.txt"
    printf "\n"
done
"rm" "outputIterative.txt"
"rm" "outputRecursive.txt"
exit 0