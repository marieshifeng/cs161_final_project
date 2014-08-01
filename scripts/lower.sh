#!/bin/sh
declare -a numVertices=("100" "1000" "10000" "50000" "100000" "200000" "300000" "500000")
"mkdir" "-p" "random_graph/lower/input"
"mkdir" "-p" "random_graph/lower/my_output"
"touch" "lower.txt"
for n in "${numVertices[@]}"; do
    m=$((n+n+n))
    counter=0
    index=0
    printf "%d: " "$n" >> "lower.txt"
    while true; do
        for((i=0;i<10;i++)); do
            "./randomgraph" "$n" "$m" "random_graph/lower/input/${n}_${m}_${i}.txt"
            "./sccfinder" "random_graph/lower/input/${n}_${m}_${i}.txt" "random_graph/lower/my_output/${n}_${m}_${i}.txt"
            if cmp -s "random_graph/correct_output/${n}.txt" "random_graph/lower/my_output/${n}_${m}_${i}.txt"
                then
                let counter=$((counter+1))
            fi
            sleep 1
        done
        printf "A graph with %d vertices and %d edges creates %d/10 strongly connected graphs.\n" "$n" "$m" "$counter"
        if [ $counter -lt 1 ]
            then
            let m=$((m+m/10))
            let counter=0
        elif [ $index -lt 10 ]
            then
            if [ $counter -eq 1 ]
                then
                printf "%d " "$m" >> "lower.txt"
            fi
            let m=$((m-2))
            let counter=0
            let index=$((index+1))
        else
            break
        fi
        "rm" "-rf" "random_graph/lower/input"
        "rm" "-rf" "random_graph/lower/my_output"
        "mkdir" "-p" "random_graph/lower/input"
        "mkdir" "-p" "random_graph/lower/my_output"
    done
    printf "\n" >> "lower.txt"
done
"rm" "-rf" "random_graph/lower/input"
"rm" "-rf" "random_graph/lower/my_output"
exit 0