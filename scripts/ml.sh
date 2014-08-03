#!/bin/sh
declare -a vertices=("100" "1000" "10000" "50000" "100000" "200000" "300000" "500000")
declare -a edges=("465" "6699" "91033" "529969" "1127313" "2383748" "3799859" "6468665")
"touch" "lower.txt"
for((i=0;i<8;i++)); do
    let n=${vertices[i]}
    printf "%d: " "$n" >> "lower.txt"
    for((k=0;k<10;k++)); do
        let m=$((edges[i]+k))
        "mkdir" "-p" "random_graph/lower/input" "random_graph/lower/my_output"
        printf "(%d, %d)" "$n" "$m"
        let numSCGs=0
        for((j=0;j<10;j++)); do
            "./randomgraph" "$n" "$m" "random_graph/lower/input/${n}_${m}_${j}.txt"
            "./sccfinder" "random_graph/lower/input/${n}_${m}_${j}.txt" "random_graph/lower/my_output/${n}_${m}_${j}.txt"
            if cmp -s "random_graph/correct_output/${n}.txt" "random_graph/lower/my_output/${n}_${m}_${j}.txt"
                then
                let numSCGs=$((numSCGs+1))
                printf "|"
            else
               printf "."
            fi 
            sleep 1
        done
        printf "%d/10\n" "$numSCGs"
        if [ $numSCGs -eq 1 ]
            then
            printf "%d " "$m" >> "lower.txt"
        fi
        "rm" "-rf" "random_graph/lower/input" "random_graph/lower/my_output"
    done
    printf '%*s\n' "${COLUMNS:-$(tput cols)}" '' | tr ' ' -
    printf "\n" >> "lower.txt"
done
exit 0