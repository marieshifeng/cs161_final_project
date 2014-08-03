#!/bin/sh
declare -a vertices=("36694" "265216" "75880" "77362" "875714")
declare -a edges=("367664" "418960" "508839" "828164" "5105042")
"mkdir" "-p" "real_networks/my_output"
"touch" "networks_output.txt"
index=0
FILES=real_networks/input/*
for f in $FILES
do
  	file="${f##*/}"
  	printf "Network %s:\n" "$file"
 	"./sccfinder" "$f" "real_networks/my_output/${file}_output.txt"
  	"cat" "real_networks/my_output/${file}_output.txt" 
  	printf "\n"
  	for((j=0;j<10;j++)); do
  		"touch" "graph.txt" "scc.txt"
  		"./randomgraph" "${vertices[index]}" "${edges[index]}" "graph.txt"
  		"./sccfinder" "graph.txt" "scc.txt"
  		"cat" "scc.txt"
  		"rm" "-rf" "graph.txt" "scc.txt"
  		printf "\n"
		sleep 1
	done
	printf "\n"
done
"rm" "-rf" "real_networks/my_output"
exit 0