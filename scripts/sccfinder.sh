#!/bin/sh
# Checks the validity of scc_finder.c against given networks and given correct outputs
for((i=1;i<11;i++)); do
    input="scc_finder/input/network${i}.txt"
    my_output="network${i}.txt"
    correct_output="scc_finder/correct_output/network${i}_output.txt"
    printf "Network %s" "$i"

    # To run on local:
    printf ": "
    "time" "./sccfinder" "$input" "$my_output"
    "diff" "$my_output" "$correct_output"
    "rm" "$my_output"

    # To run on corn:
    # printf "\n"
    # "valgrind" "--leak-check=full" "--show-reachable=yes" "./sccfinder" "$input" "$my_output"
    # "time" "-p" "./sccfinder" "$input" "$my_output"
    # "diff" "$my_output" "$correct_output"
    # "rm" "$my_output"
    # printf "\n"
done
exit 0