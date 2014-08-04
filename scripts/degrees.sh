#!/bin/sh
output="output.txt"
"mkdir" "-p" "real_networks/degree_distribution" "real_networks/random_graphs/"
"touch" "$output"
FILES=real_networks/input/*
for input in $FILES
do
  filename=${input##*/}
  network=${filename%%.*}
  network_dd="real_networks/degree_distribution/${network}_dd.txt"
  printf "Network %s" "$network"
  "./degreedistribution" "$input" "$network_dd"
  for((j=0;j<10;j++)); do
    graph="real_networks/random_graphs/${network}_${j}.txt"
    graph_dd="real_networks/degree_distribution/${network}_${j}_dd.txt"
    "./degreedistribution" "$graph" "$graph_dd"
  	printf "."
  done
	printf "\n"
done
exit 0