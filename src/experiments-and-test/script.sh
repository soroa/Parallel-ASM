#! /bin/bash

#seuential1
gcc sequential_baseline1.c -o sequential_baseline1

for i in `seq 1 10` ;
do
    { time ./sequential_baseline1 "$(cat $i.txt)" "$(cat pattern1.txt)" 1 ; } 2>> outBase1K1.txt
    { time ./sequential_baseline1 "$(cat $i.txt)" "$(cat pattern1.txt)" 2 ; } 2>> outBase1K2.txt
done

#seuential2
gcc sequential_baseline2.c -o sequential_baseline2

for i in `seq 1 10` ;
do
    { time ./sequential_baseline2 "$(cat $i.txt)" "$(cat pattern1.txt)" 1 ; } 2>> outBase2K1.txt
    { time ./sequential_baseline2 "$(cat $i.txt)" "$(cat pattern1.txt)" 2 ; } 2>> outBase2K2.txt
echo
done

#efficient sequential
gcc sequential_efficient.c -o sequential_efficient

for i in `seq 1 10` ;
do
    { time ./sequential_efficient "$(cat $i.txt)" "$(cat pattern1.txt)" 1 ; } 2>> outEfficientK1.txt
    { time ./sequential_efficient "$(cat $i.txt)" "$(cat pattern1.txt)" 2 ; } 2>> outEfficientK2.txt
echo
done

