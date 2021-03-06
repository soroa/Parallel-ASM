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
static const int not_initialized = -2;

void set_C_table(int i, int j, int value)
{
    C[i+1][j+k+1] = value;
}

int get_C_table(int i, int j)
{
    return C[i+1][j+k+1];
}

void *thread_routine(void *arg)
{
    int e = *((int *)arg);
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
        // for (int i = -1; i <= k; i++)
        // {
        //     for (int j = -(k+1); j <= n-m+k+1; j++)
        //       printf("%d\t", get_C_table(i, j));
        //     printf("\n");
        // }

        for (int d = -k; d <= n-m; d++)
            if (get_C_table(k,d) == d + m && d + m > 0)
                printf("%d ", d+m);

        for (int i = 0; i < k+2; i++)
            free(C[i]);
        free(C);
    }

    pthread_exit(NULL);
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

    C = (int **)malloc((k+2) * sizeof(int *));
    for (int i = 0; i < k+2; i++)
        C[i] = (int *)malloc((n-m+2*k+3) * sizeof(int));

    for (int i = 0; i < k+2; i++)
        for (int j = 0; j < n-m+2*k+3; j++)
            C[i][j] = not_initialized;

    for (int d = 0; d <= (n-m+k+1); d++)
        set_C_table(-1, d, d-1);
    for (int d = -(k+1); d <= -1; d++) {
        set_C_table(-d-1, d, -1);
        set_C_table(-d-2, d, INT_MIN);
    }
    
    pthread_t threads[k+1];
    int arg[k+1];
    for (int e = 0; e <= k; e++) {
        arg[e] = e;
        int rc = pthread_create(&threads[e], NULL, thread_routine, (void *)&arg[e]);
        if (rc) {
            printf("ERROR: return code from pthread_create() is %d\n", rc);
            exit(-1);
        }
    }

    /* Last thing that main() should do */
    pthread_exit(NULL);
}