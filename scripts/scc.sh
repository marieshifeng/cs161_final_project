#!/bin/sh
"mkdir" "-p" "my_output"
declare -a network=("1" "2" "3" "4" "5" "6" "7" "8" "9" "10")
for file in "${network[@]}"; do
    input="input/network${file}.txt"
    my_output="my_output/my_network${file}_output.txt"
    correct_output="correct_output/network${file}_output.txt"
    printf "Iterative %s: " "$file"
    "time" "./sccIterative" "$input" "$my_output"
    "diff" "$my_output" "$correct_output"
    printf "Recursive %s: " "$file"
    "time" "./sccRecursive" "$input" "$my_output"
    "diff" "$my_output" "$correct_output"
    printf "\n"
done
"rm" "-r" "my_output"
exit 0