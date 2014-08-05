#!/bin/sh
# Given the real network graph and corresponding ten random graphs, finds all total number of SCCs and all SCC sizes
"mkdir" "-p" "real_networks/my_output"
FILES=real_networks/input/*
for input in $FILES
do
  filename=${input##*/}
  network=${filename%%.*}
  network_scc="real_networks/my_output/${network}_ssc.txt"
  printf "Network %s" "$network"
  "./sccc" "$input" "$network_scc"
  for((j=0;j<10;j++)); do
    graph="real_networks/random_graphs/${network}_${j}.txt"
    graph_scc="real_networks/my_output/${network}_${j}_ssc.txt"
  	"./sccc" "$graph" "$graph_scc"
  	printf "."
    sleep 1
  done
	printf "\n"
done
exit 0