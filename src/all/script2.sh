#! /bin/bash

#seuential1
gcc -std=c99 sequential_baseline1.c -o sequential_baseline1 -lm

for i in `seq 1 5`;
do
     ./sequential_baseline1 "$i.txt" "pattern.txt" 1 >> outBase1K1.txt
     ./sequential_baseline1 "$i.txt" "pattern.txt" 2 >> outBase1K2.txt
     ./sequential_baseline1 "$i.txt" "pattern.txt" 5 >> outBase1K5.txt
echo
done

#seq_baseline1_diagonalwise

gcc -std=c99 seq_baseline1_diagonalwise.c -o seq_baseline1_diagonalwise -lm

for i in `seq 1 5`;
do
     ./seq_baseline1_diagonalwise "$i.txt" "pattern.txt" 1 >> outBase1K1Diagonal.txt
     ./seq_baseline1_diagonalwise "$i.txt" "pattern.txt" 2 >> outBase1K2Diagonal.txt
     ./seq_baseline1_diagonalwise "$i.txt" "pattern.txt" 5 >> outBase1K5Diagonal.txt
echo
done

#sequential_baseline1_memory_efficient

gcc -std=c99 sequential_baseline1_memory_efficient.c -o sequential_baseline1_memory_efficient -lm

for i in `seq 1 5`;
do
     ./sequential_baseline1_memory_efficient "$i.txt" "pattern.txt" 1 >> outBase1K1MEMEFF.txt
     ./sequential_baseline1_memory_efficient "$i.txt" "pattern.txt" 2 >> outBase1K2MEMEFF.txt
     ./sequential_baseline1_memory_efficient "$i.txt" "pattern.txt" 5 >> outBase1K5MEMEFF.txt
echo
done

#seuential2
gcc -std=c99 sequential_baseline2.c -o sequential_baseline2 -lm

for i in `seq 1 5`;
do
     ./sequential_baseline2 "$i.txt" "pattern.txt" 1 >> outBase2K1.txt
     ./sequential_baseline2 "$i.txt" "pattern.txt" 2 >> outBase2K2.txt
     ./sequential_baseline2 "$i.txt" "pattern.txt" 5 >> outBase2K5.txt
echo
done

#efficient sequential
gcc -std=c99 sequential_efficient.c -o sequential_efficient -lm

for i in `seq 1 5`;
do
     ./sequential_efficient "$i.txt" "pattern.txt" 1 >> outEfficientK1.txt
     ./sequential_efficient "$i.txt" "pattern.txt" 2 >> outEfficientK2.txt
     ./sequential_efficient "$i.txt" "pattern.txt" 5 >> outEfficientK5.txt
   
echo
done



#parallel1
gcc -pthread -std=c99 parallel_baseline1.c -o parallel_baseline1 -lm

for i in `seq 1 5`;
do
     ./sequential_baseline1 "$i.txt" "pattern.txt" 1 >> outPar1K1.txt
     ./sequential_baseline1 "$i.txt" "pattern.txt" 2 >> outPar1K2.txt
     ./sequential_baseline1 "$i.txt" "pattern.txt" 5 >> outPar1K5.txt
echo
done

#parallel_baseline1_memory_efficient_openMP
gcc -fopenmp -std=c99 parallel_baseline1_memory_efficient_openMP.c -o parallel_baseline1_memory_efficient_openMP -lm

for i in `seq 1 5`;
do
     ./parallel_baseline1_memory_efficient_openMP "$i.txt" "pattern.txt" 1 >> outPar1K1_MEMEFF_OMP.txt
     ./parallel_baseline1_memory_efficient_openMP "$i.txt" "pattern.txt" 2 >> outPar1K2_MEMEFF_OMP.txt
     ./parallel_baseline1_memory_efficient_openMP "$i.txt" "pattern.txt" 5 >> outPar1K5_MEMEFF_OMP.txt
echo
done

#parallel_baseline1_openMP_RowWise
gcc -fopenmp -std=c99 parallel_baseline1_openMP_RowWise.c -o parallel_baseline1_openMP_RowWise -lm

for i in `seq 1 5`;
do
     ./parallel_baseline1_openMP_RowWise "$i.txt" "pattern.txt" 1 >> outPar1K1_ROW_OMP.txt
     ./parallel_baseline1_openMP_RowWise "$i.txt" "pattern.txt" 2 >> outPar1K2_ROW_OMP.txt
     ./parallel_baseline1_openMP_RowWise "$i.txt" "pattern.txt" 5 >> outPar1K5_ROW_OMP.txt
echo
done


#parallel2
gcc -pthread -std=c99 parallel_baseline2.c -o parallel_baseline2 -lm

for i in `seq 1 5`;
do
     ./sequential_baseline2 "$i.txt" "pattern.txt" 1 >> outPar2K1.txt
     ./sequential_baseline2 "$i.txt" "pattern.txt" 2 >> outPar2K2.txt
     ./sequential_baseline2 "$i.txt" "pattern.txt" 5 >> outPar2K5.txt
echo
done

#parallel2b
gcc -pthread -std=c99 parallel_baseline2b.c -o parallel_baseline2b -lm

for i in `seq 1 5`;
do
     ./parallel_baseline2b "$i.txt" "pattern.txt" 1 >> outPar2K1b.txt
     ./parallel_baseline2b "$i.txt" "pattern.txt" 2 >> outPar2K2b.txt
     ./parallel_baseline2b "$i.txt" "pattern.txt" 5 >> outPar2K5b.txt
echo
done

#parallel_baseline2_diagonalw_openMP
gcc -fopenmp -std=c99 parallel_baseline2_diagonalw_openMP.c -o parallel_baseline2_diagonalw_openMP -lm

for i in `seq 1 5`;
do
     ./parallel_baseline2_diagonalw_openMP "$i.txt" "pattern.txt" 1 >> outPar2K1_Diag_OMP.txt
     ./parallel_baseline2_diagonalw_openMP "$i.txt" "pattern.txt" 2 >> outPar2K2_Diag_OMP.txt
     ./parallel_baseline2_diagonalw_openMP "$i.txt" "pattern.txt" 5 >> outPar2K5_Diag_OMP.txt
echo
done

#parallel_baseline2openMP
gcc -fopenmp -std=c99 parallel_baseline2openMP.c -o parallel_baseline2openMP -lm

for i in `seq 1 5`;
do
     ./parallel_baseline2openMP "$i.txt" "pattern.txt" 1 >> outPar2K1_OMP.txt
     ./parallel_baseline2openMP "$i.txt" "pattern.txt" 2 >> outPar2K2_OMP.txt
     ./parallel_baseline2openMP "$i.txt" "pattern.txt" 5 >> outPar2K5_OMP.txt
echo
done



