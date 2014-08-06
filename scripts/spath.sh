#!/bin/sh
output="shortestpath.txt"
# "mkdir" "-p" "real_networks/degree_distribution" "real_networks/random_graphs/"
"touch" "$output"
FILES=real_networks/input/*
for input in $FILES
do
  filename=${input##*/}
  network=${filename%%.*}
  temp="temp.txt"
  printf "Network %s" "$network"
  "./compare" "$input" "$temp"
  "cat" "$temp" >> "$output"
  for((j=0;j<5;j++)); do
    graph="real_networks/random_graphs/${network}_${j}.txt"
    "./compare" "$graph" "$temp"
    "cat" "$temp" >> "$output"
    printf "."
  done
    printf "\n"
done
exit 0