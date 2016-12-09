
#include <stdio.h>
#include "rdtsc.h"
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
void readTextandPattern(char *argv[]) {
    char *textFileName;
    char *patternFileName;
    textFileName = argv[1];
    patternFileName = argv[2];
    //reading from text file
    FILE *f = fopen(textFileName, "r");
    if (f == NULL)
    {
        perror("Error opening file");
        return ;
    }
    fseek(f, 0, SEEK_END);
    int SIZE = ftell(f);

    fseek(f, 0, SEEK_SET);

    char textBuf[SIZE + 1];
    if (fgets( textBuf, SIZE + 1, f) != NULL) {
        // printf("text read correctly\n");
        text = textBuf;
    } else {
        // printf("returned null \n");
    }
    fclose(f);

    f = fopen(patternFileName, "r");
    if (f == NULL)
    {
        perror("Error opening file");
        return;
    }
    fseek(f, 0, SEEK_END);
    SIZE = ftell(f);
    fseek(f, 0, SEEK_SET);
    char patternBuf[SIZE + 1];
    if (fgets( patternBuf, SIZE + 1, f) != NULL) {
        // printf("pattern read correctly\n");
        pattern = patternBuf;
    } else {
        // printf("returned null \n");
    }

    fclose(f);
}



int main(int argc, char *argv[]) {
	unsigned long long t1, t2;
	t1=rdtsc();

    if (argc != 4) {

        printf("usage: ./exec text pattern k");
        return -1;
    }
    // printf( "%d" + argc);
    readTextandPattern(argv);
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
    // printD();

    for (int d =  1; d < n + m; d ++ ) {
        int i = 1;
        while (i <= m && (d - i + 1) >= 1 ) {

            int a = fmin(fmin(getDiagonalElem(d - 1, i - 1) + 1, getDiagonalElem(d - 1, i) + 1), getDiagonalElem(d - 2, i - 1) + (pattern[i - 1] == text[d - i] ? 0 : 1));
            setDiagonalElem(d, i, a);
            i++;
        }

    }
    // printD();

    for (int i = 0; i <= n; i = i + 1) {
        // if (D[m][i] <= k)
            // printf("k-match at i:%d \n", i - 1);
    }




    free(D[m]);
    free(D);
    t2=rdtsc();
	printf("%llu \n", t2-t1);

}