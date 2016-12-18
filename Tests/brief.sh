#! /bin/bash


#par2
gcc -std=c99 seq_2_r.c -o seq_2_r -lm
gcc -fopenmp -std=c99 par_2_omp_d.c -o par_2_omp_d -lm

for i in `seq 1 100`;
do
     ./seq_2_r "5.txt" "pattern.txt" 2 >> SEQ.txt
     
     ./par_2_omp_d "5.txt" "pattern.txt" 2  2 >> 2core.txt
     ./par_2_omp_d "5.txt" "pattern.txt" 2  4 >> 4core.txt
     ./par_2_omp_d "5.txt" "pattern.txt" 2  8 >> 8core.txt
     ./par_2_omp_d "5.txt" "pattern.txt" 2  16 >> 16core.txt
      
    
echo
done
