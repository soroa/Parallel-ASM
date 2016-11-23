
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>
#include <string.h>
#include <math.h>

int n, m, k;
char *text, *pattern;
int **D;
static const int NUMBER_OF_THREADS = 4;


void printD() {
    // printf("\n ");
    for (int j = 0; j <= m; j++) {
        for (int i = 0; i <= n; i++) {
            printf("|%d|", D[j][i]);
        }
        printf("\n");
    }

    printf("\n \n ");

}


void setDiagonalElem(int d, int i, int el) {
    D[i][d + 1 - i] = el;

}

int getDiagonalElem(int d, int i) {
    return D[i][d + 1 - i];
}



int main(int argc, char *argv[]) {

    if (argc != 4) {

        printf("usage: ./exec text pattern k");
        return -1;
    }
    // printf( "%d" + argc);
    text = argv[1];
    pattern = argv[2];
    n = strlen(text);
    m = strlen(pattern);
    k = atoi(argv[3]);


    /*
    *   ALLOCATING MEMORY FOR D, (N+1xM+1)
    */



    D = (int **)malloc((m + 1) * sizeof(int *));
    for (int i = 0; i < m + 1; i = i + 1) {
        D[i] = (int *)malloc((n + 1) * sizeof(int));
    }

    for (int i = 0; i <= n; i = i + 1)
        D[0][i] = 0;



    for (int i = 1 ; i <= m; i = i + 1)
        D[i][0] = i;
    printD();

    for (int d =  1; d < n + m; d ++ ) {
        int i = 1;
        while (i <= m && (d - i + 1) >= 1 ) {

            int a = fmin(fmin(getDiagonalElem(d - 1, i - 1) + 1, getDiagonalElem(d - 1, i) + 1), getDiagonalElem(d - 2, i - 1) + (pattern[i - 1] == text[d - i] ? 0 : 1));
            setDiagonalElem(d, i, a);
            i++;
        }

    }
    printD();

    for (int i = 0; i <= n; i = i +1) {
        if (D[m][i] <= k)
            printf("k-match at i:%d \n", i-1);
    }




    free(D[m]);
    free(D);


}