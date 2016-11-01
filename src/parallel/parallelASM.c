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
  int sizeY=0;
  int sizeX=0;
  int** eMatrix; 
/* Fork a team of threads giving them their own copies of variables */

   if ( argc != 3 ) /* argc should be 2 for correct execution */
    {
        /* We print argv[0] assuming it is the program name */
        printf( "It looks like your parameters are wrong" );
    }
    else{
        sizeX = strlen(argv[1]);
        sizeY = strlen(argv[2]);;
        pattern= argv[1];
        targetText = argv[2];
        printf("X is %s \n", pattern);
        printf("Y is %s \n", targetText);
        printf("size of X is %d \n", sizeX);



       
    }
  eMatrix =createEMatrix(3,sizeX);
  for(int i=0; i<3;i++){
    for(int j=0; j<sizeX; j++){
      printf("%d ",eMatrix[i][j]);

    }
    printf("\n");
  }


  

}
