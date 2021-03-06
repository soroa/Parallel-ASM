// Dynamic Programming - C table : k+1 threads, O(n) in theory
#include <stdio.h>
#include "rdtsc.h"
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <limits.h>
#include <pthread.h>
#include <omp.h>


#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define MIN(x, y) (((x) < (y)) ? (x) : (y))
int n, m, k;
char *text, *pattern;
int **C;
static const int NUMBER_OF_THREADS = 8;
short *initializedLines;


void set_C_table(int i, int j, int value)
{

  C[i + 1][j + k + 1] = value;
}

int get_C_table(int i, int j)
{
  return C[i + 1][j + k + 1];
}




void printC() {

  for (int j = 0; j < k + 2; j++) {
    for (int i = 0; i < n - m + 2 * k + 3; i++) {
      printf("|%d| ", C[j][i]);
    }
    printf("\n");
  }
  printf("\n\n\n");


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


int main(int argc, char *argv[])
{





  unsigned long long t1, t2;
  t1 = rdtsc();
  if (argc != 4) {
    printf("\n usage: ./exec text pattern k \n \n ");
    return 0;
  }

  readTextandPattern(argv, &n, &m);

  k = atoi(argv[3]);
  int not_initialized = -2;

  C = (int **)malloc((k + 2) * sizeof(int *));
  for (int i = 0; i < k + 2; i++)
    C[i] = (int *)malloc((n - m + 2 * k + 3) * sizeof(int));

  initializedLines = (short *) calloc((k + 2), sizeof(short));

  // printf("C allocated \n ");




  #pragma omp parallel
  {
    int nthreads;
    nthreads = omp_get_num_threads();

    int ID = omp_get_thread_num();

    int not_initialized = -2;



    //**********************************************************
    //************************  MATRIX INITIALIZATION  *********************
    //**********************************************************


    int subportion  = (n - m + k + 2) / nthreads;
    int remainder = (n - m + k + 2) % nthreads;




//first line initialize

    if (ID == 0) {
      for (int d = 0; d < subportion + remainder; d++)
        set_C_table(-1, d, d - 1);
    } else {
      for (int d = ID * subportion + remainder; d < ID * subportion + subportion + remainder; d++)
        set_C_table(-1, d, d - 1);
    }

    initializedLines[0] = 1;


// //first two diagonals initialized

    for (int d = -(k + 1) + ID; d <= -1; d = d + nthreads) {
      set_C_table(-d - 1, d, -1);
      set_C_table(-d - 2, d, INT_MIN);
    }



//initializing  the rest to -2

    if (ID >= nthreads / 2) {
      for (int e = ID - nthreads / 2; e <= k; e = e + nthreads / 2) {
        for (int c = 0; c <= n - m + k; c++) {
          set_C_table(e, c - e, not_initialized);
        }
        initializedLines[e + 1] = 1;

      }

    }


//     //**********************************************************
//     //************************  Computation: working in parallel  *********************
//     //**********************************************************


    if (ID < nthreads / 2) {

      for (int e = ID; e <= k; e = e + nthreads / 2)
      {
        while (initializedLines[e + 1] == 0) {
          // printf("T %d waiting for line %d \n", ID, e - 1);
        }
        for (int c = 0; c <= n - m + k; c++)
        {
          int d = c - e;
          while (get_C_table(e - 1, d + 1) == not_initialized) {}
          int col = MAX(MAX(get_C_table(e - 1, d - 1) + 1, get_C_table(e - 1, d) + 1), get_C_table(e - 1, d + 1));
          while (col < n && col - d < m && text[col] == pattern[col - d]) {
            col++;
          }
          set_C_table(e, d, MIN(MIN(col, m + d), n));
        }
      }
    }


//     //**********************************************************
//     //************************  Output: working in parallel  *********************
//     //**********************************************************

    #pragma omp barrier
    if (ID == 0) {
      printC();
    }
    #pragma omp barrier
//     //Matrix computed. Going through last line


    for (int d = -k + ID ; d <= n - m; d = d + nthreads)
      if (get_C_table(k, d) == d + m && d + m > 0)
      printf("%d  ", d + m-1);





//       //**********************************************************
//       //************************  Dealloc: working in parallel  *********************
//       //**********************************************************

    #pragma omp barrier
    for (int i = ID; i < k + 2; i = i + nthreads)
      free(C[i]);

  }



  free(C);

  t2 = rdtsc();
   printf("\n");
  printf("%llu \n", t2 - t1);


}