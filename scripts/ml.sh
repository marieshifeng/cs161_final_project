#!/bin/sh
# Finds ml given number of vertices
declare -a vertices=("100" "1000" "10000" "50000" "100000" "200000" "300000" "500000")
declare -a edges=("468" "6700" "91036" "529962" "1127315" "2383748" "3799860" "6468665")
"touch" "lower.txt"
for((i=0;i<8;i++)); do
    let n=${vertices[i]}
    let m=${edges[i]}
    let numOneSCGs=0
    printf "%d: " "$n" >> "lower.txt"
    while [ $numOneSCGs -lt 10 ]; do
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
            if [ $numSCGs -gt 1 ]
                then
                let j=10
            fi
            sleep 1
        done
        printf "%d/10\n" "$numSCGs"
        if [ $numSCGs -eq 1 ]
            then
            printf "%d " "$m" >> "lower.txt"
            let numOneSCGs=$((numOneSCGs+1))
            let m=$((m-5))
        elif [ $numSCGs -lt 1 ]
            then
            let m=$((m+m/10))
        elif [ $numSCGs -gt 1 ]
            then
            let m=$((m-m/10))
        fi
        "rm" "-rf" "random_graph/lower/input" "random_graph/lower/my_output"
    done
    printf '%*s\n' "${COLUMNS:-$(tput cols)}" '' | tr ' ' -
    printf "\n" >> "lower.txt"
done
exit 0