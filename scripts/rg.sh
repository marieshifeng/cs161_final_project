#!/bin/sh

"mkdir" "-p" "random_correct_output"
"mkdir" "-p" "random_my_graph"

declare -a numVertices=("100" "1000" "10000" "50000" "100000" "200000" "300000" "500000")

for n in "${numVertices[@]}"; do
    file_out_val="random_correct_output/${n}_output.txt" #Golden output
    echo "${n}\t0\t0\t0\t0" > "$file_out_val"
    for((m=$((n-1));m<500;m++)); do
        "./randomgraph" "$n" "$m" "random_my_graph/${n}_${m}_graph.txt"
        "./sccfinder" "random_my_graph/${n}_${m}_graph.txt" "random_correct_output/${n}_output.txt"



    done


    # # Pad network with suffixes
    # # file_in="input/network${file}.txt"
    # file_out_tst="random_my_output/my_network${file}_output.txt" 
    # echo > "$file_out_tst"

    # # Validate infile exists (do the same for out validate file)
    # if [ ! -f "$file_in" ]; then
    #     printf "In file %s is missing\n" "$file_in"
    #     continue;
    # fi
    # if [ ! -f "$file_out_val" ]; then
    #     printf "Validation file %s is missing\n" "$file_out_val"
    #     continue;
    # fi

    # printf "Network %s\n" "$file"

    # # Run application, redirect in file to app, and output to out file
    # # "./$bin" < "$file_in" > "$file_out_tst"
    # "time" "-p" "./$bin" "$file_in" "$file_out_tst"

    # # Execute diff
    # $diff "$file_out_tst" "$file_out_val"
    # printf "\n"
done



# for i in {1..100}; do
#     echo "Welcome $i times"
# done

# # Creates my_output directory if it doesn't exist
# "mkdir" "-p" "my_output"

# declare -a network=("1" "2" "3" "4" "5" "6" "7" "8" "9" "10")

# # Loop the array
# for file in "${network[@]}"; do
#     # Pad network with suffixes
#     # file_in="input/network${file}.txt"
#     file_out_val="correct_output/network${file}_output.txt"
#     file_out_tst="my_output/my_network${file}_output.txt"
#     echo > "$file_out_tst"

#     # Validate infile exists (do the same for out validate file)
#     if [ ! -f "$file_in" ]; then
#         printf "In file %s is missing\n" "$file_in"
#         continue;
#     fi
#     if [ ! -f "$file_out_val" ]; then
#         printf "Validation file %s is missing\n" "$file_out_val"
#         continue;
#     fi

#     printf "Network %s\n" "$file"

#     # Run application, redirect in file to app, and output to out file
#     # "./$bin" < "$file_in" > "$file_out_tst"
#     "time" "-p" "./$bin" "$file_in" "$file_out_tst"

#     # Execute diff
#     $diff "$file_out_tst" "$file_out_val"
#     printf "\n"
# done

# # Removes my_output directory
# "rm" "-r" "my_output"

# Clean exit with status 0
exit 0