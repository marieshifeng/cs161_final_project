#!/bin/sh
# declare -a numVertices=("100" "1000" "10000" "50000" "100000" "200000" "300000" "500000")
declare -a numVertices=("100")
for n in "${numVertices[@]}"; do
    mu=550
    counter=0
    index=0
    printf "%d(%d)" "$mu" "$counter"
    while true; do
        "mkdir" "-p" "random_input"
        "mkdir" "-p" "random_my_output"
        for((i=0;i<10;i++)); do
            "./rg" "$n" "$mu" "random_input/${n}_${mu}_${i}.txt"
        done
        graphs=random_input/*
        for g in $graphs; do
            "./sccIterative" "$g" "random_my_output/${n}_${mu}_${index}.txt"
            if cmp -s "correct_random_output/${n}.txt" "random_my_output/${n}_${mu}_${index}.txt"
                then
                let counter=counter+1
            fi
            let index=index+1
        done
        let index=0
        if [ $counter -gt 8 ]
        then
            let mu=mu-1
            printf " > %d(%d)" "$mu" "$counter"
            let counter=0
            "rm" "-rf" "random_input"
            "rm" "-rf" "random_my_output"
        else
            printf " > %d(%d)\n" "$mu" "$counter"
            break
        fi
    done
done
"rm" "-rf" "random_input"
"rm" "-rf" "random_my_output"
exit 0