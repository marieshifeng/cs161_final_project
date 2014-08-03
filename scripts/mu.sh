#!/bin/sh
declare -a vertices=("100" "1000" "10000" "50000" "100000" "200000" "300000" "500000")
declare -a edges=("775" "9510" "120150" "693843" "1428015" "3055894" "4578397" "8156529")
"touch" "upper.txt"
for((i=0;i<8;i++)); do
    let n=${vertices[i]}
    printf "%d: " "$n" >> "upper.txt"
    for((k=0;k<10;k++)); do
        let m=$((edges[i]+k))
        "mkdir" "-p" "random_graph/upper/input" "random_graph/upper/my_output"
        printf "(%d, %d)" "$n" "$m"
        let numSCGs=0
        for((j=0;j<10;j++)); do
            "./randomgraph" "$n" "$m" "random_graph/upper/input/${n}_${m}_${j}.txt"
            "./sccfinder" "random_graph/upper/input/${n}_${m}_${j}.txt" "random_graph/upper/my_output/${n}_${m}_${j}.txt"
            if cmp -s "random_graph/correct_output/${n}.txt" "random_graph/upper/my_output/${n}_${m}_${j}.txt"
                then
                let numSCGs=$((numSCGs+1))
                printf "|"
            else
               printf "."
            fi 
            sleep 1
        done
        printf "%d/10\n" "$numSCGs"
        if [ $numSCGs -eq 9 ]
            then
            printf "%d " "$m" >> "upper.txt"
        fi
        "rm" "-rf" "random_graph/upper/input" "random_graph/upper/my_output"
    done
    printf '%*s\n' "${COLUMNS:-$(tput cols)}" '' | tr ' ' -
    printf "\n" >> "upper.txt"
done
exit 0