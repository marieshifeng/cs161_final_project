#!/bin/sh
for((i=1;i<11;i++)); do
    input="scc_finder/input/network${i}.txt"
    my_output="network${i}.txt"
    correct_output="scc_finder/correct_output/network${i}_output.txt"

    # To run on local:
    # printf "Network %s: " "$i"
    # "time" "./sccfinder" "$input" "$my_output"
    # "diff" "$my_output" "$correct_output"
    # "rm" "$my_output"

    # To run on corn:
    printf "Network %s:\n " "$i"
    "valgrind" "--leak-check=full" "--show-reachable=yes" "./sccfinder" "$input" "$my_output"
    "time" "-p" "./sccfinder" "$input" "$my_output"
    "diff" "$my_output" "$correct_output"
    "rm" "$my_output"
    printf "\n"
done
exit 0