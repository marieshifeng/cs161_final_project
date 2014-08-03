#!/bin/sh
declare -a vertices=("36694" "265216" "75880" "77362" "875714")
declare -a edges=("367664" "418960" "508839" "828164" "5105042")
"mkdir" "-p" "real_networks/my_output" "real_networks/random_graphs/"
index=0
FILES=real_networks/input/*
for input in $FILES
do
  filename=${input##*/}
  network=${filename%%.*}
  network_scc="real_networks/my_output/${network}_ssc.txt"
  printf "Network %s" "$network"
  "./sccfinder" "$input" "$network_scc"
  for((j=0;j<10;j++)); do
    graph="real_networks/random_graphs/${network}_${j}.txt"
    graph_scc="real_networks/my_output/${network}_${j}_ssc.txt"
  	"./randomgraph" "${vertices[index]}" "${edges[index]}" "$graph"
  	"./sccfinder" "$graph" "$graph_scc"
  	printf "."
    sleep 1
  done
  let index=$((index+1))
	printf "\n"
done
exit 0