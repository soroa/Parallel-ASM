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

void printC() {

    for (int j = 0; j < k + 2; j++) {
        for (int i = 0; i < n - m + 2 * k + 3; i++) {
            printf("|%d| ", C[j][i]);
        }
        printf("\n");
    }
    printf("\n\n\n");


}

int main(int argc, char *argv[])
{
    if (argc != 4) {
        printf("\n usage: ./exec text pattern k \n \n ");
        return 0;
    }
    text = argv[1];
    pattern = argv[2];
    n = strlen(text);
    m = strlen(pattern);
    k = atoi(argv[3]);
    int not_initialized = -2;

    C = (int **)malloc((k + 2) * sizeof(int *));
    for (int i = 0; i < k + 2; i++)
        C[i] = (int *)malloc((n - m + 2 * k + 3) * sizeof(int));

    // for (int i = 0; i < k + 2; i++) {
    //     for (int j = 0; j < n - m + 2 * k + 3; j++) {

    //         C[i][j] = not_initialized;

    //     }
    // }






    printf("C allocated \n ");


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

    

        for (int i = ID; i < k + 2; i = i + nthreads)
           for (int j = 0; j < n-m+2*k+3; j++)
                C[i][j] = not_initialized;


        #pragma omp barrier 

        int subportion  = (n - m + k + 2) / nthreads;
        int remainder = (n - m + k + 2) % nthreads;
        if (ID == 0) {
            for (int d = 0; d < subportion + remainder; d++)
                set_C_table(-1, d, d - 1);
        } else {
            for (int d = ID * subportion + remainder; d < ID * subportion + subportion + remainder; d++)
                set_C_table(-1, d, d - 1);
        }
    

        for (int d = -(k + 1) + ID; d <= -1; d = d + nthreads) {
            set_C_table(-d - 1, d, -1);
            set_C_table(-d - 2, d, INT_MIN);
        }


        //**********************************************************
        //************************  Computation  *********************
        //**********************************************************



    
        #pragma omp barrier


        for (int e = ID; e <= k; e = e + nthreads)
        {
            for (int c = 0; c <= n - m + k; c++)
            {
                int d = c - e;
                while (get_C_table(e - 1, d + 1) == not_initialized) {
                    printf("%d waiting \n", ID);
                    // printf("wait C[%d, %d]\n", e-1, d+1);
                }
                int col = fmax(fmax(get_C_table(e - 1, d - 1) + 1, get_C_table(e - 1, d) + 1), get_C_table(e - 1, d + 1));
                while (col < n && col - d < m && text[col] == pattern[col - d]) {
                    col++;
                }
                set_C_table(e, d, fmin(fmin(col, m + d), n));
            }
        }


        //**********************************************************
        //************************  Output: working in parallel  *********************
        //**********************************************************


        #pragma omp barrier
        //Matrix computed. Going through last line


        for (int d = -k + ID ; d <= n - m; d = d + nthreads)
            if (get_C_table(k, d) == d + m && d + m > 0)
                printf("%d  ", d + m);



        //**********************************************************
        //************************  Dealloc: working in parallel  *********************
        //**********************************************************

        #pragma omp barrier
        for (int i = ID; i < k + 2; i = i + nthreads)
            free(C[i]);

    }


    free(C);




}