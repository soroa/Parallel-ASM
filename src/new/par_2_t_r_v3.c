// Dynamic Programming - C table : k+1 threads, O(n) in theory
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <limits.h>
#include <pthread.h>
#include "rdtsc.h"

const int nthreads = 4;
int n, m, k;
char *text, *pattern;
int **C;
int *initialized;
static const int not_initialized = -2;
unsigned long long t1, t2; 

void set_C_table(int i, int j, int value)
{
    C[i+1][j+k+1] = value;
}

int get_C_table(int i, int j)
{
    return C[i+1][j+k+1];
}

void readTextandPattern(char *argv[], int *p_n, int *p_m) 
{
    // Read text file
    FILE *f = fopen(argv[1], "r");
    if (f == NULL)
    {
        perror("Error opening file");
        return;
    }
    fseek(f, 0, SEEK_END);
    *p_n = ftell(f);
    fseek(f, 0, SEEK_SET);
    text = (char *)malloc((*p_n + 1) * sizeof(char));
    if (fgets(text, *p_n + 1, f) == NULL) {
        perror("Error reading file");
        return;
    }
    fclose(f);

    // Read pattern file
    f = fopen(argv[2], "r");
    if (f == NULL)
    {
        perror("Error opening file");
        return;
    }
    fseek(f, 0, SEEK_END);
    *p_m = ftell(f);
    fseek(f, 0, SEEK_SET);
    pattern = (char *)malloc((*p_m + 1) * sizeof(char));
    if (fgets(pattern, *p_m + 1, f) == NULL) {
        perror("Error reading file");
        return;
    }
    fclose(f);
}

void initialize(int e)
{
    for (int c = 0; c <= n-m+k; c++) {
        int d = c - e;
        set_C_table(e, d, not_initialized);
    }
    initialized[e] = 1;
}

void *thread_initialize(void *arg)
{
    int id = *((int *)arg);
    for (int e = id; e <= k; e += nthreads) {
        initialize(e);
    }
    pthread_exit(NULL);
}

void compute(int e)
{
    while(initialized[e] == 0) {
    }
    for (int c = 0; c <= n-m+k; c++) {
        int d = c - e;
        while(get_C_table(e-1, d+1) == not_initialized) {
            // printf("wait C[%d, %d]\n", e-1, d+1);
        }
        int col = fmax(fmax(get_C_table(e-1, d-1) + 1, get_C_table(e-1, d) + 1), get_C_table(e-1, d+1));
        while (col < n && col - d < m && text[col] == pattern[col-d]) {
            col++;
        }
        set_C_table(e, d, fmin(fmin(col, m + d), n));
    }

    if (e == k) {
        // Print C table
        // for (int i = -1; i <= k; i++)
        // {
        //     for (int j = -(k+1); j <= n-m+k+1; j++)
        //       printf("%d\t", get_C_table(i, j));
        //     printf("\n");
        // }

        for (int d = -k; d <= n-m; d++) {
            if (get_C_table(k,d) == d + m && d + m > 0) {
                // printf("%d ", d+m);
            }
        }

        for (int i = 0; i < k+2; i++)
            free(C[i]);
        free(C);
        free(text);
        free(pattern);
        free(initialized);
        
        t2 = rdtsc();
        printf("%llu\n", t2 - t1); 
    }
}
void *thread_routine(void *arg)
{
    int id = *((int *)arg);
    for (int e = id; e <= k; e += nthreads) {
        compute(e);
    }
    pthread_exit(NULL);
}

int main(int argc, char *argv[])
{
    if (argc != 4)
        printf("usage: ./exec textfile patternfile k");
    readTextandPattern(argv, &n, &m);
    k = atoi(argv[3]);
    
    t1 = rdtsc();

    C = (int **)malloc((k+2) * sizeof(int *));
    for (int i = 0; i < k+2; i++)
        C[i] = (int *)malloc((n-m+2*k+3) * sizeof(int));

    initialized = (int *)malloc((k+1) * sizeof(int));
    for (int e = 0; e <= k; e++)
        initialized[e] = 0;

    for (int d = 0; d <= (n-m+k+1); d++)
        set_C_table(-1, d, d-1);
    for (int d = -(k+1); d <= -1; d++) {
        set_C_table(-d-1, d, -1);
        set_C_table(-d-2, d, INT_MIN);
    }

    pthread_t threads_initialize[nthreads];
    int arg_initialize[nthreads];
    for (int i = 0; i < nthreads; i++) {
        arg_initialize[i] = i;
        int rc = pthread_create(&threads_initialize[i], NULL, thread_initialize, (void *)&arg_initialize[i]);
        if (rc) {
            printf("ERROR: return code from pthread_create() is %d\n", rc);
            exit(-1);
        }
    }

    pthread_t threads_routine[nthreads];
    int arg_routine[nthreads];
    for (int i = 0; i < nthreads; i++) {
        arg_routine[i] = i;
        int rc = pthread_create(&threads_routine[i], NULL, thread_routine, (void *)&arg_routine[i]);
        if (rc) {
            printf("ERROR: return code from pthread_create() is %d\n", rc);
            exit(-1);
        }
    }
 
    /* Last thing that main() should do */
    pthread_exit(NULL);
}