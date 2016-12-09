#! /bin/bash

#seuential1
gcc -std=c99 seq_1_d.c -o seq_1_d -lm

for i in `seq 1 5`;
do
     ./seq_1_d "$i.txt" "pattern.txt" 1 >> seq_1_d_k1.txt
     ./seq_1_d "$i.txt" "pattern.txt" 2 >> seq_1_d_k2.txt
     ./seq_1_d "$i.txt" "pattern.txt" 5 >> seq_1_d_k5.txt
echo
done
#
gcc -std=c99 seq_1_r.c -o seq_1_r -lm

for i in `seq 1 5`;
do
     ./seq_1_r "$i.txt" "pattern.txt" 1 >> seq_1_r_k1.txt
     ./seq_1_r "$i.txt" "pattern.txt" 2 >> seq_1_r_k2.txt
     ./seq_1_r "$i.txt" "pattern.txt" 5 >> seq_1_r_k5.txt
echo
done
#
gcc -std=c99 seq_1_memeff.c -o seq_1_memeff -lm

for i in `seq 1 5`;
do
     ./seq_1_memeff "$i.txt" "pattern.txt" 1 >> seq_1_memeff_k1.txt
     ./seq_1_memeff "$i.txt" "pattern.txt" 2 >> seq_1_memeff_k2.txt
     ./seq_1_memeff "$i.txt" "pattern.txt" 5 >> seq_1_memeff_k5.txt
echo
done
#
gcc -std=c99 seq_1_r.c -o seq_2_r -lm

for i in `seq 1 5`;
do
     ./seq_2_r "$i.txt" "pattern.txt" 1 >> seq_2_r_k1.txt
     ./seq_2_r "$i.txt" "pattern.txt" 2 >> seq_2_r_k2.txt
     ./seq_2_r "$i.txt" "pattern.txt" 5 >> seq_2_r_k5.txt
echo
done
#
gcc -std=c99 seq_nk.c -o seq_nk -lm

for i in `seq 1 5`;
do
     ./seq_nk "$i.txt" "pattern.txt" 1 >> seq_nk_k1.txt
     ./seq_nk "$i.txt" "pattern.txt" 2 >> seq_nk_k2.txt
     ./seq_nk "$i.txt" "pattern.txt" 5 >> seq_nk_k5.txt
echo
done
##

gcc -fopenmp -std=c99 par_1_omp_d.c -o par_1_omp_d -lm

for i in `seq 1 5`;
do
     ./par_1_omp_d "$i.txt" "pattern.txt" 1 >> par_1_omp_d_k1.txt
     ./par_1_omp_d "$i.txt" "pattern.txt" 2 >> par_1_omp_d_k2.txt
     ./par_1_omp_d "$i.txt" "pattern.txt" 5 >> par_1_omp_d_k5.txt
echo
done
#
gcc -fopenmp -std=c99 par_1_omp_r.c -o par_1_omp_r -lm

for i in `seq 1 5`;
do
     ./par_1_omp_r "$i.txt" "pattern.txt" 1 >> par_1_omp_r_k1.txt
     ./par_1_omp_r "$i.txt" "pattern.txt" 2 >> par_1_omp_r_k2.txt
     ./par_1_omp_r "$i.txt" "pattern.txt" 5 >> par_1_omp_r_k5.txt
echo
done
#
gcc -fopenmp -std=c99 par_1_omp_memeff.c -o par_1_omp_memeff -lm

for i in `seq 1 5`;
do
     ./par_1_omp_memeff "$i.txt" "pattern.txt" 1 >> par_1_omp_memeff_k1.txt
     ./par_1_omp_memeff "$i.txt" "pattern.txt" 2 >> par_1_omp_memeff_k2.txt
     ./par_1_omp_memeff "$i.txt" "pattern.txt" 5 >> par_1_omp_memeff_k5.txt
echo
done
#
gcc -pthread -std=c99 par_1_t_r.c -o par_1_t_r -lm

for i in `seq 1 5`;
do
     ./par_1_t_r "$i.txt" "pattern.txt" 1 >> par_1_t_r_k1.txt
     ./par_1_t_r "$i.txt" "pattern.txt" 2 >> par_1_t_r_k2.txt
     ./par_1_t_r "$i.txt" "pattern.txt" 5 >> par_1_t_r_k5.txt
echo
done



#
gcc -fopenmp -std=c99 par_2_omp_d.c -o par_2_omp_d -lm

for i in `seq 1 5`;
do
     ./par_2_omp_d "$i.txt" "pattern.txt" 1 >> par_2_omp_d_k1.txt
     ./par_2_omp_d "$i.txt" "pattern.txt" 2 >> par_2_omp_d_k2.txt
     ./par_2_omp_d "$i.txt" "pattern.txt" 5 >> par_2_omp_d_k5.txt
echo
done
#
gcc -fopenmp -std=c99 par_2_omp_r.c -o par_2_omp_r -lm

for i in `seq 1 5`;
do
     ./par_1_omp_r "$i.txt" "pattern.txt" 1 >> par_1_omp_r_k1.txt
     ./par_1_omp_r "$i.txt" "pattern.txt" 2 >> par_1_omp_r_k2.txt
     ./par_1_omp_r "$i.txt" "pattern.txt" 5 >> par_1_omp_r_k5.txt
echo
done
#

gcc -pthread -std=c99 par_2_t_r.c -o par_2_t_r -lm

for i in `seq 1 5`;
do
     ./par_2_t_r "$i.txt" "pattern.txt" 1 >> par_2_t_r_k1.txt
     ./par_2_t_r "$i.txt" "pattern.txt" 2 >> par_2_t_r_k2.txt
     ./par_2_t_r "$i.txt" "pattern.txt" 5 >> par_2_t_r_k5.txt
echo
done

