#!/bin/sh
declare -a numVertices=("100" "1000" "10000" "50000" "100000" "200000" "300000" "500000")
declare -a startingBounds=("400" "6000" "80000" "469897" "1000000" "2120412" "3286273" "5698970")
"mkdir" "-p" "random_graph/lower/input"
"mkdir" "-p" "random_graph/lower/my_output"
"touch" "lower.txt"
for((j=0;j<10;j++)); do
    n=${numVertices[j]}
    m=${startingBounds[j]}
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
                let index=$((index+1))
                let m=$((m-1))
            else
                let m=$((m-m/(${startingBounds[j]}/2)))
            fi
            let counter=0
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