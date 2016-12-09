#include <omp.h>
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
short *initializedLines; 

static const int NUMBER_OF_THREADS = 8;


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



void setDiagonalElem(int d, int i, int el) {
    D[i][d + 1 - i] = el;

}

int getDiagonalElem(int d, int i) {
    return D[i][d + 1 - i];
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

    initializedLines = (short *) calloc((m+1),sizeof(short)); 


    /*
    *   MATRIX INIT: FIRST COLUMN=i, FIRST ROW=0, REST=-1
    */

    omp_set_num_threads(NUMBER_OF_THREADS);
    #pragma omp parallel 
    {
        int nthreads;
        nthreads = omp_get_num_threads();

        int ID = omp_get_thread_num();

        /*
        *   D MATRIX INITIALIZATION
        */

        if (ID == 0) {
            for (int i = 0; i <= n; i = i + 1)
                D[0][i] = 0;
            initializedLines[0]=1; 

        }

        if (ID == 1) {
            // printf("initializing first colum\n");
            for (int i = 1 ; i <= m; i = i + 1)
                D[i][0] = i;
        }

        if(ID>=nthreads/2){
          printf("started initializng \n"); 
        for (int i = 1 + ID - nthreads/2; i <= m; i = i + nthreads/2)
            for (int j = 1; j <= n; j = j + 1) {
                D[i][j] = -1;
                initializedLines[i]=1;
                if(j==n){
                    printf("T %d initialized row %d \n",ID, i); 
                }
            }
        }


        //threads must sync here
        // #pragma omp barrier

        /*
        *   D MATRIX COMPUTATION
        */
        

        if(ID<nthreads/2){
        for (int d =  1+ID; d < n + m; d = d+nthreads/2) {
            int i = 1;
            while(initializedLines[i]==0){
              printf("waiting for line %d \n ", i); 
              // printf("i = %d", i); 
            }
            while (i <= m && (d - i + 1) >= 1 ) {
                while (getDiagonalElem(d - 1, i)  == -1) {}
                int a = fmin(fmin(getDiagonalElem(d - 1, i - 1) + 1, getDiagonalElem(d - 1, i) + 1), getDiagonalElem(d - 2, i - 1) + (pattern[i - 1] == text[d - i] ? 0 : 1));
                setDiagonalElem(d, i, a);
                i++;
            }
        }
      }


        // //threads must sync here
        #pragma omp barrier

        // *    Last Row Iteration and Result Output

        for (int i = ID; i <= n; i = i + nthreads) {
            // if (D[m][i] <= k)
               // printf("k-match at i:%d \n", i-1);
        }




        // *   Free all row except last one - no synch necessary because only row=m is being used

        for (int i = ID; i < m; i = i + nthreads) {
            free(D[i]);
        }


    }

    free(D[m]);
    free(D);
	t2=rdtsc();
	printf("%llu \n", t2-t1);


}