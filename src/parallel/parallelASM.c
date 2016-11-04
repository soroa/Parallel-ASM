/******************************************************************************
* FILE:
* DESCRIPTION:
* AUTHORS:
* LAST REVISED: 
******************************************************************************/
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// #include <omp.h>
#include <limits.h>


#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define MIN(x, y) (((x) < (y)) ? (x) : (y))

int ** createEMatrix(unsigned int rows, unsigned int cols) {
  int ** matrix;
  matrix = (int **) calloc(cols, sizeof(int *));
  for(unsigned int i = 0; i < cols; i++)
    matrix[i] = (int *) calloc(rows, sizeof(int));
  return matrix;
}



int main (int argc, char *argv[]) 
{
  int nthreads, tid;
 
  char* pattern; 
  char* targetText; 
  int n=0;
  int m=0;
  int** eMatrix; 

   if ( argc != 3 ) /* argc should be 2 for correct execution */
    {
        /* We print argv[0] assuming it is the program name */
        printf( "It looks like your parameters are wrong" );
    }
    else{
        m = strlen(argv[1]);
        n = strlen(argv[2]);;
        pattern= argv[1];
        targetText = argv[2];
        printf("X is %s \n", pattern);
        printf("Y is %s \n", targetText);
    }
  eMatrix =createEMatrix(3,m);
  
  for(int i=0; i<3;i++){
    for(int j=0; j<m; j++){
      printf("%d ",eMatrix[i][j]);

    }
    printf("\n");
  }

  int minVal = INT_MAX; 

  for(int k=0; k<=n+m-1; k++){
    printf("k : %d \n", k);
    int j=0;
    for(int i=0; i<=m; i++){

      j = k-i+1; 
      printf("i : %d \n", i);

      if(i==0) eMatrix[j%3][i]=0; 

      else if(j=0) eMatrix[j%3][i] = i; 
      else if(j>=1 && j<=n){
        printf("assignment loop \n"); 
        eMatrix[j%3][i] = MIN(eMatrix[(j-1)%3][i]+1, MIN(eMatrix[(j)%3][i-1]+1, eMatrix[(j-1)%3][i-1]+1)+ (pattern[i]==targetText[j]?1:0));
      }

      eMatrix[j%3][i] = i; 

       for(int i=0; i<3;i++){
    for(int j=0; j<m; j++){
      printf("%d ",eMatrix[i][j]);

      }
    printf("\n");
    }

    
    if(eMatrix[j%3][m]<minVal) minVal = eMatrix[j%3][m]; 


    printf("\n");
  }

    printf("\n \n Min value is %d \n \n ", minVal); 

  }
  free(eMatrix);


}
