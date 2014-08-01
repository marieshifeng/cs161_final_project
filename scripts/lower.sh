#!/bin/sh
declare -a numVertices=("100" "1000" "10000" "50000" "100000" "200000" "300000" "500000")
"mkdir" "-p" "random_graph/input"
"mkdir" "-p" "random_graph/my_output"
for n in "${numVertices[@]}"; do
    m=$((n+n+n))
    counter=0
    index=0
    while true; do
        for((i=0;i<10;i++)); do
            "./randomgraph" "$n" "$m" "random_graph/input/${n}_${m}_${i}.txt"
            "./sccfinder" "random_graph/input/${n}_${m}_${i}.txt" "random_graph/my_output/${n}_${m}_${i}.txt"
            if cmp -s "random_graph/correct_output/${n}.txt" "random_graph/my_output/${n}_${m}_${i}.txt"
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
            let m=$((m-1))
            let counter=0
            let index=$((index+1))
        else
            break
        fi
        "rm" "-rf" "random_graph/input"
        "rm" "-rf" "random_graph/my_output"
        "mkdir" "-p" "random_graph/input"
        "mkdir" "-p" "random_graph/my_output"
    done
done
"rm" "-rf" "random_graph/input"
"rm" "-rf" "random_graph/my_output"
exit 0