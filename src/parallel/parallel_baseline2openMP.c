// Dynamic Programming - C table : k+1 threads, O(n) in theory
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <limits.h>
#include <pthread.h>
#include <omp.h>

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

    printf("C allocated");


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
        if (ID == 0) {
            printf("initialization started\n");
        }
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
            for (int d = ID * subportion + remainder; d < ID * subportion + subportion + remainder; d++)
                set_C_table(-1, d, d - 1);
        }
        if (ID == 0) {
            printf("initialization in progress \n");
        }

        //initializng two diagonals to -infinity and -1. One thread per row
        for (int d = -(k + 1) + ID; d <= -1; d = d + nthreads) {
            set_C_table(-d - 1, d, -1);
            set_C_table(-d - 2, d, INT_MIN);
        }
        if (ID == 0) {
            printf("initialization completed\n");
        }
        #pragma omp barrier
        for (int e = ID; e <= k; e = e + nthreads)
        {
            for (int c = 0; c <= n - m + k; c++)
            {

                int d = c - e;
                while (get_C_table(e - 1, d + 1) == not_initialized) {
                    // printf("wait C[%d, %d]\n", e-1, d+1);
                }
                int col = fmax(fmax(get_C_table(e - 1, d - 1) + 1, get_C_table(e - 1, d) + 1), get_C_table(e - 1, d + 1));
                while (col < n && col - d < m && text[col] == pattern[col - d]) {
                    col++;
                }
                set_C_table(e, d, fmin(fmin(col, m + d), n));
            }
        }
        // #pragma omp barrier
        // //Matrix computed. Going through last line
        // printf("result");
        // for (int d = -k + ID; d <= n - m; d = d + nthreads)
        //     if (get_C_table(k, d) == d + m && d + m > 0)
        //         printf("%d ", d + m);




    }

    for (int i = 0; i < k + 2; i++)
        free(C[i]);
    free(C);




}