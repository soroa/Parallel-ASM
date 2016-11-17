// Dynamic Programming - C table : k+1 threads, O(n) in theory
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <limits.h>
#include <pthread.h>

int n, m, k;
char *text, *pattern;
int **C;
static const int NUMBER_OF_THREADS = 4;


void set_C_table(int i, int j, int value)
{
    C[i + 1][j + k + 1] = value;
}

int get_C_table(int i, int j)
{
    return C[i + 1][j + k + 1];
}



int main(int argc, char *argv[])
{
    if (argc != 4)
        printf("usage: ./exec text pattern k");
    text = argv[1];
    pattern = argv[2];
    n = strlen(text);
    m = strlen(pattern);
    k = atoi(argv[3]);

    C = (int **)malloc((k + 2) * sizeof(int *));
    for (int i = 0; i < k + 2; i++)
        C[i] = (int *)malloc((n - m + 2 * k + 3) * sizeof(int));



    static const int NUMBER_OF_THREADS = 4;
    #pragma omp parallel
    {
        int nthreads;
        nthreads = omp_get_num_threads();

        int ID = omp_get_thread_num();

        int not_initialized = -2;


        /*
        *   D MATRIX INITIALIZATION
        */

        //one thread per row
        for (int i = ID; i < k + 2; i = i + nthreads)
            for (int j = 0; j < n - m + 2 * k + 3; j++)
                C[i][j] = not_initialized;
        //initializing first row. Splitting the row in equal parts. Thread 0 taking care of remainder
        int subportion  = (n - m + k + 2) / nthreads;
        int remainder = (n - m + k + 2) % nthreads;
        if (ID == 0) {
            for (int d = 0; d < subportion + remainder; d++)
                set_C_table(-1, d, d - 1);
        } else {
            for (int d = ID * subportion + remainder; d < ID * subportion + subportion+remainder; d++)
                set_C_table(-1, d, d - 1);
        }

        

        //initializng two diagonals to -infinity and -1. One thread per row
        for (int d = -(k + 1) + ID; d <= -1; d = d + nthreads) {
            set_C_table(-d - 1, d, -1);
            set_C_table(-d - 2, d, INT_MIN);
        }

    }





}