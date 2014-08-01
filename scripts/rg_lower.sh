#!/bin/sh
# declare -a numVertices=("100" "1000" "10000" "50000" "100000" "200000" "300000" "500000")
"mkdir" "-p" "random_input"
"mkdir" "-p" "random_my_output"
declare -a numVertices=("100")
for n in "${numVertices[@]}"; do
    mu=450
    counter=0
    index=0
    while true; do
        for((i=0;i<10;i++)); do
            "./rg" "$n" "$mu" "random_input/${n}_${mu}_${i}.txt"
            sleep 1
        done
        for((i=0;i<10;i++)); do
            "./sccIterative" "random_input/${n}_${mu}_${i}.txt" "random_my_output/${n}_${mu}_${i}.txt"
            if cmp -s "random_input/${n}_${mu}_${i}.txt" "random_my_output/${n}_${mu}_${i}.txt"
                then
                let counter=counter+1
            fi
            let index=index+1
        done
        let index=0
        printf "%d(%d)\n\n\n" "$mu" "$counter"
        if [ $counter -lt 1 ]
        then
            let mu=mu+1
            let counter=0
            "rm" "-rf" "random_input"
            "rm" "-rf" "random_my_output"
            "mkdir" "-p" "random_input"
            "mkdir" "-p" "random_my_output"
        else
            break
        fi
    done
done
"rm" "-rf" "random_input"
"rm" "-rf" "random_my_output"
exit 0