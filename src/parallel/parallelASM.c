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
#include <math.h>


#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define MIN(x, y) (((x) < (y)) ? (x) : (y))


void printM(int** M,int m){

   for(int i=0; i<3;i++){
   for(int j=0; j<m+1; j++){
    printf(" %d ",M[i][j]);

    }
    printf("\n");
  }
}
  

int mod(int a, int b)
{
    int r = a % b;
    return r < 0 ? r + b : r;
}


int main (int argc, char *argv[]) 
{
  int nthreads, tid;
 
  char* pattern; 
  char* targetText; 
  int n=0;
  int m=0;
  int** DMatrix; 

  if ( argc != 3 ) /* argc should be 2 for correct execution */
  {
  
      printf( "It looks like your parameters are wrong" );
  }
  
  else{
      m = strlen(argv[1]);
      n = strlen(argv[2]);;
      pattern= argv[1];
      targetText = argv[2];
  }

  DMatrix = (int **) malloc(3*sizeof(int *));
  printf("m is %d\n", m);
  for( int i = 0; i < 3; i++){
    
    DMatrix[i] = (int *) malloc((m+1)*sizeof(int));
  }

 
  // printM(DMatrix, m);



  int minVal = m; 
  int j=0;
  DMatrix[0][0]=0;
  for(int k=0; k<=n+m-1; k++){
    printf("k : %d \n", k);
    for(int i=0; i<=m; i++){

      j = k-i+1; 
  
      // printf("i is %d and j is %d \n", i, j);
      if(i==0){
        DMatrix[j%3][i]=0; 
        printf("set %d %d %d\n", j, i,   DMatrix[j%3][i]);

      }

      else if(j==0) {
        DMatrix[j%3][i] = i; 
        printf("set %d %d %d\n", j, i,   DMatrix[j%3][i]);

      }
      
      else if((j>=1) && (j<=n)) {
        
        // printf("assignment loop \n"); 
        DMatrix[j%3][i] = MIN(DMatrix[mod((j-1),3)][i]+1, MIN(DMatrix[mod((j),3)][i-1]+1, DMatrix[mod((j-1),3)][i-1]+ (pattern[i-1]==targetText[j-1]?0:1)));
        printf("check %d %d %d\n", DMatrix[mod((j-1),3)][i]+1,DMatrix[mod((j),3)][i-1]+1,DMatrix[mod((j-1),3)][i-1]+ (pattern[i-1]==targetText[j-1]?0:1)) ;
        // printf(" check prev diag elem %d, chars are disequal: %d", DMatrix[mod((j-1),3)][i-1], (pattern[i-1]==targetText[j-1]?0:1));
        printf("set %d %d %d\n", j, i,   DMatrix[j%3][i]);
        // printM(DMatrix,m);
        if(i==m){
        if(DMatrix[mod(j,3)][m]<minVal) minVal = DMatrix[mod(j,3)][m]; 
        }
      }

     }  

    
    printM(DMatrix,m);
    }
    


  

   printf("\n \n Min value is %d \n \n ", minVal); 
   free(DMatrix);
  }




