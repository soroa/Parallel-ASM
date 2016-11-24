// Dynamic Programming - C table : k+1 threads, O(n) in theory
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <limits.h>
#include <pthread.h>
#include <omp.h>


double *C;
static const int NUMBER_OF_THREADS = 4;






int main(int argc, char *argv[])
{

    int size = 100000000;
    C = (double *)malloc(size * sizeof(double*));
    //SEQUENTIAL VERSION
    // for(int i =0; i<size; i=i+1){
    //         C[i]=sqrt(i);
    //     }




    static const int NUMBER_OF_THREADS = 4;
    // #pragma omp parallel for

    // for (int i = 0; i < size; i = i + 1) {
    //     C[i] = sqrt(i);
    // }


    #pragma omp parallel
    {
        int nthreads;
        nthreads = omp_get_num_threads();

        int ID = omp_get_thread_num();
//        PARALLEL VERSION 1: P1|P2|P3|P4|P1|P2|....
        for (int i = ID; i < size; i = i + nthreads) {
            C[i] = sqrt(i);
        }

        // //PARALLEL VERSION 2: |...P1...|....P2....|....P3.....|....P4.....|
        // int subportion  = (size) / nthreads;
        // int remainder = (size) % nthreads;
        // if (ID == 0) {
        //     for (int i = 0; i < subportion + remainder; i++)
        //         C[i] = C[i] = sqrt(i);
        // } else {
        //     for (int i = ID * subportion + remainder; i < ID * subportion + subportion + remainder; i++)
        //         C[i] = C[i] = sqrt(i);
        // }



    }


    free(C);




}