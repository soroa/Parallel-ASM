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


#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define MIN(x, y) (((x) < (y)) ? (x) : (y))

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

void printCol() {
  for (int i = 0; i <= m; i++) {
    printf("|%d|", D[i][0]);
  }
  printf("\n \n");
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



int main(int argc, char *argv[]) {
  unsigned long long t1, t2;
  t1 = rdtsc();

  if (argc != 4) {

    printf("usage: ./exec text pattern k");
    return -1;
  }
  // printf( "%d" + argc);
  readTextandPattern(argv, &n, &m);
  k = atoi(argv[3]);


  /*
  *   ALLOCATING MEMORY FOR D, (N+1xM+1)
  */

  D = (int **)malloc((m + 1) * sizeof(int *));
  for (int i = 0; i < m + 1; i = i + 1) {
    D[i] = (int *)malloc((n + 1) * sizeof(int));
  }





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
      D[1][1] = -1;
      initializedDiags[0] = 1;

    }


    if (ID == 1) {
      // printf("initializing first colum\n");
      for (int i = 1 ; i <= m; i = i + 1)
        D[i][0] = i;


      initializedDiags[1] = 1;
      initializedDiags[2] = 1;
    }




    if (ID >= nthreads / 2) {
      // if (ID ==4) {
      for (int sum = 3; sum <= n + m; sum = sum + 1) {

        for (int i = MAX(1, sum - n) + ID - nthreads / 2; i <= MIN(sum - 1, m); i = i + nthreads / 2) {
          int j  = sum - i;

          D[i][j] = -1;
          if (i == 4 && j == 1) printf("T%d set D[%d][%d] to -1 \n", ID, i, j );

          #pragma omp atomic
          initializedDiags[sum] = initializedDiags[sum] + 1;



          if (i == MIN(sum - 1, m)) {
            printf("T%d set  d: %d to init \n ", ID,  sum);
          }
        }



      }



    }



    #pragma omp barrier


    if (ID < nthreads / 2) {
      for (int sum =  2; sum <= n + m; sum = sum + 1) {
        if (sum > 3) {
          while (initializedDiags[sum - 1] != MIN(sum - 2, m) - (MAX(1, sum - 1 - n) - 1) || initializedDiags[sum - 2] != MIN(sum - 3, m) - (MAX(1, sum - 2 - n) - 1) ) {

            // printf("T %d waiting for %d or %d \n ", ID, sum - 1, sum - 2);
            // printf("D%d= %d and D%d= %d  expected %d %d \n", sum - 1, initializedDiags[sum - 1], sum - 2, initializedDiags[sum - 2], MIN(sum - 2, m), MIN(sum - 3, m));
          }
        }

        for (int i = MAX(1, sum - n) + ID; i <= MIN(sum - 1, m); i = i + nthreads / 2) {
          int j = sum - i;

          while (D[i - 1][j] == -1 ) {
            printf("T%d D[%d][%d] = -1 \n", ID, i - 1, j);
          }
          int v = MIN(MIN(D[i - 1][j] + 1, D[i][j - 1] + 1), D[i - 1][j - 1] + (pattern[i - 1] == text[j - 1] ? 0 : 1));

          D[i][j] = v;
          if (i == m && j == 5) {
            printf("values are %d %d %d %d ",  D[i - 1][j], D[i][j - 1], D[i - 1][j - 1], (pattern[i - 1] == text[j - 1] ? 0 : 1) );

            printf("T%d set D[%d][%d] to %d \n", ID, i, j, v );
          }


        }

      }


    }


    // //threads must sync here


    #pragma omp barrier
    if (ID == 0) {
      printD();
    }

    // *    Last Row Iteration and Result Output

    #pragma omp barrier


    // *   Free all row except last one - no synch necessary because only row=m is being used

    for (int i = ID; i < m; i = i + nthreads) {
      free(D[i]);
    }


  }




  // free(D[m]);
  free(D);
  free(initializedDiags);
  t2 = rdtsc();
  printf("%llu \n", t2 - t1);


}