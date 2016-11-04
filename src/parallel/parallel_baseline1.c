// Dynamic Programming - D table : O(mn) //???
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <pthread.h>

int n, m, k;
char *text, *pattern;
int **D;

void *thread_routine(void *arg)
{
    int i = *((int *)arg);
    for (int j = 1; j <= n; j++)
    {
        while(D[i-1][j] == -1) {
            // printf("wait D[%d, %d]\n", i-1, j);
        }
        if (pattern[i-1] == text[j-1])
            D[i][j] = fmin(fmin(D[i-1][j] + 1, D[i][j-1] + 1), D[i-1][j-1]);
        else
            D[i][j] = fmin(fmin(D[i-1][j] + 1, D[i][j-1] + 1), D[i-1][j-1] + 1);
    }

    if (i == m) {
        for (int j = 1; j <= n; j++)
            if (D[m][j] <= k) 
                printf("%d ", j);

        for (int i = 0; i < m+1; i++)
            free(D[i]);
        free(D);
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
    
    D = (int **)malloc((m+1) * sizeof(int *));
    for (int i = 0; i < m+1; i++)
        D[i] = (int *)malloc((n+1) * sizeof(int));

    for (int i = 0; i <= n; i++)
        D[0][i] = 0;
    for (int i = 1; i <= m; i++)
        D[i][0] = i;

    for (int i = 1; i <= m; i++)
        for (int j = 1; j <= n; j++)
            D[i][j] = -1;

    pthread_t threads[m];
    int arg[m];
    for (int i = 1; i <= m; i++) {
        arg[i-1] = i;
        int rc = pthread_create(&threads[i-1], NULL, thread_routine, (void *)&arg[i-1]);
        if (rc) {
            printf("ERROR: return code from pthread_create() is %d\n", rc);
            exit(-1);
        }
    }

    /* Last thing that main() should do */
    pthread_exit(NULL);
}