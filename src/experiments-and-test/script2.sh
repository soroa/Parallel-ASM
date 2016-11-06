#! /bin/bash

#seuential1
gcc -std=c99 sequential_baseline1.c -o sequential_baseline1 -lm

for i in `seq 1 10` ;
do
    { time ./sequential_baseline1 "$(cat $i.txt)" "$(cat pattern1.txt)" 1 ; } 2>> outBase1K1.txt
    { time ./sequential_baseline1 "$(cat $i.txt)" "$(cat pattern1.txt)" 2 ; } 2>> outBase1K2.txt
    { time ./sequential_baseline1 "$(cat $i.txt)" "$(cat pattern1.txt)" 5 ; } 2>> outBase1K5.txt
echo
done

#seuential2
gcc -std=c99 sequential_baseline2.c -o sequential_baseline2 -lm

for i in `seq 1 10` ;
do
    { time ./sequential_baseline2 "$(cat $i.txt)" "$(cat pattern1.txt)" 1 ; } 2>> outBase2K1.txt
    { time ./sequential_baseline2 "$(cat $i.txt)" "$(cat pattern1.txt)" 2 ; } 2>> outBase2K2.txt
    { time ./sequential_baseline2 "$(cat $i.txt)" "$(cat pattern1.txt)" 5 ; } 2>> outBase2K5.txt
echo
done

#efficient sequential
gcc -std=c99 sequential_efficient.c -o sequential_efficient -lm

for i in `seq 1 10` ;
do
    { time ./sequential_efficient "$(cat $i.txt)" "$(cat pattern1.txt)" 1 ; } 2>> outEfficientK1.txt
    { time ./sequential_efficient "$(cat $i.txt)" "$(cat pattern1.txt)" 2 ; } 2>> outEfficientK2.txt
    { time ./sequential_efficient "$(cat $i.txt)" "$(cat pattern1.txt)" 5 ; } 2>> outEfficientK5.txt
   
echo
done


#parallel1
gcc -pthread -std=c99 parallel_baseline1.c -o parallel_baseline1 -lm

for i in `seq 1 10` ;
do
    { time ./sequential_baseline1 "$(cat $i.txt)" "$(cat pattern1.txt)" 1 ; } 2>> outPar1K1.txt
    { time ./sequential_baseline1 "$(cat $i.txt)" "$(cat pattern1.txt)" 2 ; } 2>> outPar1K2.txt
    { time ./sequential_baseline1 "$(cat $i.txt)" "$(cat pattern1.txt)" 5 ; } 2>> outPar1K5.txt
echo
done

#parallel2
gcc -pthread -std=c99 parallel_baseline2.c -o parallel_baseline2 -lm

for i in `seq 1 10` ;
do
    { time ./sequential_baseline2 "$(cat $i.txt)" "$(cat pattern1.txt)" 1 ; } 2>> outPar2K1.txt
    { time ./sequential_baseline2 "$(cat $i.txt)" "$(cat pattern1.txt)" 2 ; } 2>> outPar2K2.txt
    { time ./sequential_baseline2 "$(cat $i.txt)" "$(cat pattern1.txt)" 5 ; } 2>> outPar2K5.txt
echo
done

