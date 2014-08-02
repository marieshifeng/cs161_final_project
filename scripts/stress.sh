#!/bin/sh
"mkdir" "-p" "random_graphs_input"
for((n=100;n<10000000;n*=10)); do
	m=$((n*7))
	"./randomgraph" "$n" "$m" "random_graphs_input/${n}_${m}.txt"
done
FILES=random_graphs_input/*
for f in $FILES
do
	# To run on local:
	printf "Network %s:  " "$f"
  	"time" "./sccfinder" "$f" "output.txt"
  	
  	# To run on corn:
    # printf "Network %s\n: " "$f"
    # "time" "-p" "./sccfinder" "$f" "output.txt"
    # printf "\n"
done
"rm" "output.txt"
"rm" "-rf" "random_graphs_input"
exit 0