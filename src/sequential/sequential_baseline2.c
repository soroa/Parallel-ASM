// Dynamic Programming - C table : O(mn)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <limits.h>

int k;
int **C;

void set_C_table(int i, int j, int value)
{
    C[i+1][j+k+1] = value;
}

int get_C_table(int i, int j)
{
    return C[i+1][j+k+1];
}

int main(int argc, char *argv[])
{
    if (argc != 4)
        printf("usage: ./exec text pattern k");
    char *text = argv[1];
    char *pattern = argv[2];
    int n = strlen(text), m = strlen(pattern);
    k = atoi(argv[3]);

    C = (int **)malloc((k+2) * sizeof(int *));
    for (int i = 0; i < k+2; i++)
        C[i] = (int *)malloc((n-m+2*k+3) * sizeof(int));

    for (int d = 0; d <= (n-m+k+1); d++)
        set_C_table(-1, d, d-1);
    for (int d = -(k+1); d <= -1; d++)
    {
        set_C_table(-d-1, d, -1);
        set_C_table(-d-2, d, INT_MIN);
    }
        
    for (int c = 0; c <= n-m+k; c++)
    {
        for (int e = 0; e <= k; e++)
        {
            int d = c - e;
            int col = fmax(fmax(get_C_table(e-1, d-1) + 1, get_C_table(e-1, d) + 1), get_C_table(e-1, d+1));
            while (col < n && col - d < m && text[col] == pattern[col-d]) {
                col++;
            }
            set_C_table(e, d, fmin(fmin(col, m + d), n));
        }
    }

    // for (int i = -1; i <= k; i++)
    // {
    //     for (int j = -(k+1); j <= n-m+k+1; j++)
    //       printf("%d\t", get_C_table(i, j));
    //     printf("\n");
    // }

    for (int d = -k; d <= n-m; d++)
        if (get_C_table(k,d) == d+m)
            printf("%d ", d+m);

    for (int i = 0; i < k+2; i++)
        free(C[i]);
    free(C);
}