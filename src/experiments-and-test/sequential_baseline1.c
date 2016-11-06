// Dynamic Programming - D table : O(mn)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int main(int argc, char *argv[])
{
    if (argc != 4)
        printf("usage: ./exec text pattern k");
    char *text = argv[1];
    char *pattern = argv[2];
    int n = strlen(text), m = strlen(pattern);
    int k = atoi(argv[3]);
    
    // int D[m+1][n+1];
    int **D = (int **)malloc((m+1) * sizeof(int *));
    for (int i = 0; i <= m; i++)
        D[i] = (int *)malloc((n+1) * sizeof(int));

    for (int i = 0; i <= n; i++)
        D[0][i] = 0;
    for (int i = 1; i <= m; i++)
        D[i][0] = i;

    for (int i = 1; i <= m; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            if (pattern[i-1] == text[j-1])
                D[i][j] = fmin(fmin(D[i-1][j] + 1, D[i][j-1] + 1), D[i-1][j-1]);
            else
                D[i][j] = fmin(fmin(D[i-1][j] + 1, D[i][j-1] + 1), D[i-1][j-1] + 1);
        }
    }
    for (int i = 1; i <= n; i++)
        if (D[m][i] <= k) 
            printf("%d ", i);

    for (int i = 0; i <= m; i++)
        free(D[i]);
    free(D);
}