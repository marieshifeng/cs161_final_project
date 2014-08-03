#!/bin/sh
"mkdir" "-p" "random_graphs_input"
for((n=100;n<10000000;n*=10)); do
	m=$((n*7))
  printf "Creating network (%s, %s)\n" "$n" "$m"

  # To run on local:
  "./randomgraph" "$n" "$m" "random_graphs_input/${n}_${m}.txt"

  # To run on corn:
	# "valgrind" "--leak-check=full" "--show-reachable=yes" "./randomgraph" "$n" "$m" "random_graphs_input/${n}_${m}.txt"
 #  printf "\n"
done
FILES=random_graphs_input/*
for f in $FILES
do
  printf "Network %s" "$f"

	# To run on local:
  printf ": "
  "time" "./sccfinder" "$f" "output.txt"
  	
	# To run on corn:
  # printf "\n"
  # "valgrind" "--leak-check=full" "--show-reachable=yes" "./sccfinder" "$f" "output.txt"
  # "time" "-p" "./sccfinder" "$f" "output.txt"
  # printf "\n"
done
"rm" "output.txt"
"rm" "-rf" "random_graphs_input"
exit 0