#!/bin/sh
declare -a vertices=("100" "1000" "10000" "50000" "100000" "200000" "300000" "500000")
declare -a edges=("777" "9512" "120154" "693847" "1428018" "3055896" "4461284" "8156532")
"touch" "upper.txt"
for((i=0;i<8;i++)); do
    let n=${vertices[i]}
    let m=${edges[i]}
    let numOneSCGs=0
    printf "%d: " "$n" >> "upper.txt"
    while [ $numOneSCGs -lt 10 ]; do
        "mkdir" "-p" "random_graph/upper/input" "random_graph/upper/my_output"
        printf "(%d, %d)" "$n" "$m"
        let numSCGs=0
        let limit=0
        for((j=0;j<10;j++)); do
             "./randomgraph" "$n" "$m" "random_graph/upper/input/${n}_${m}_${j}.txt"
            "./sccfinder" "random_graph/upper/input/${n}_${m}_${j}.txt" "random_graph/upper/my_output/${n}_${m}_${j}.txt"
            if cmp -s "random_graph/correct_output/${n}.txt" "random_graph/upper/my_output/${n}_${m}_${j}.txt"
                then
                let numSCGs=$((numSCGs+1))
                printf "|"
            else
                let limit=$((limit+1))
                printf "."
            fi
            if [ $limit -gt 1 ]
                then
                let j=10
            fi
            sleep 1
        done
        printf "%d/10\n" "$numSCGs"
        if [ $numSCGs -eq 9 ]
            then
            printf "%d " "$m" >> "upper.txt"
            let numOneSCGs=$((numOneSCGs+1))
            let m=$((m-5))
        elif [ $numSCGs -lt 9 ]
            then
            let m=$((m+m/10))
        elif [ $numSCGs -gt 9 ]
            then
            let m=$((m-m/10))
        fi
        "rm" "-rf" "random_graph/upper/input" "random_graph/upper/my_output"
    done
    printf '%*s\n' "${COLUMNS:-$(tput cols)}" '' | tr ' ' -
    printf "\n" >> "upper.txt"
done
exit 0