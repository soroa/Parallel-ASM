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
int** D;

#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define MIN(x, y) (((x) < (y)) ? (x) : (y))

static const int NUMBER_OF_THREADS = 4;

void printD()
{
  // printf("\n ");
  for (int j = 0; j <= m; j++) {
    for (int i = 0; i <= n; i++) {
      printf("|%d|", D[j][i]);
    }
    printf("\n");
  }

  printf("\n \n ");
}

void printCol()
{
  for (int i = 0; i <= m; i++) {
    printf("|%d|", D[i][0]);
  }
  printf("\n \n");
}

void readTextandPattern(char* argv[], int* p_n, int* p_m)
{
  // Read text file
  FILE* f = fopen(argv[1], "r");
  if (f == NULL) {
    perror("Error opening file");
    return;
  }
  fseek(f, 0, SEEK_END);
  *p_n = ftell(f);
  fseek(f, 0, SEEK_SET);
  text = (char*)malloc((*p_n + 1) * sizeof(char));
  if (fgets(text, *p_n + 1, f) == NULL) {
    perror("Error reading file");
    return;
  }
  fclose(f);

  // Read pattern file
  f = fopen(argv[2], "r");
  if (f == NULL) {
    perror("Error opening file");
    return;
  }
  fseek(f, 0, SEEK_END);
  *p_m = ftell(f);
  fseek(f, 0, SEEK_SET);
  pattern = (char*)malloc((*p_m + 1) * sizeof(char));
  if (fgets(pattern, *p_m + 1, f) == NULL) {
    perror("Error reading file");
    return;
  }
  fclose(f);
}

int main(int argc, char* argv[])
{
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

  D = (int**)malloc((m + 1) * sizeof(int*));
  for (int i = 0; i < m + 1; i = i + 1) {
    D[i] = (int*)calloc((n + 1), sizeof(int));
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


    int subportion  = (n + 1) / nthreads;
    int remainder = (n + 1) % nthreads;
    if (ID == 0) {
      for (int i = 0; i < subportion + remainder; i++)
        D[0][i] = 1;
    } else {
      for (int i = ID * subportion + remainder; i < ID * subportion + subportion + remainder; i++)
        D[0][i] = 1;
    }


    // printf("initializing first colum\n");
    for (int i = 1 + ID; i <= m; i = i + nthreads)
      D[i][0] = i + 1;




    #pragma omp barrier

    for (int sum = 2; sum <= n + m; sum = sum + 1) {

      for (int i = MAX(1, sum - n) + ID; i <= MIN(sum - 1, m); i = i + nthreads) {
        int j = sum - i;

        while (D[i - 1][j] == 0 || D[i][j - 1] == 0) {
          // printf("line %d \n ", i);
          // printf("T%d D[%d][%d] = -1 \n", ID, i - 1, j);
        }
        D[i][j] = MIN(MIN(D[i - 1][j] + 1, D[i][j - 1] + 1), D[i - 1][j - 1] + (pattern[i - 1] == text[j - 1] ? 0 : 1));
      }
    }

// *    Last Row Iteration and Result Output
    // #pragma omp barrier
    // if (ID == 0) printD();
    // #pragma omp barrier

    // *    Free all row except last one - no synch necessary because only row=m is being used

    for (int i = ID; i < m; i = i + nthreads) {
      free(D[i]);
    }
  }

  // free(D[m]);
  free(D);
  t2 = rdtsc();
  printf("%llu \n", t2 - t1);
}