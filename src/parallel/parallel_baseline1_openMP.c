#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>
#include <string.h>
#include <math.h>

int n, m, k;
char *text, *pattern;
int **D;
int NUMBER_OF_THREADS = 4;


void printD(int** D){

		if (ID == 0) {
			for (int j = 0; j <= m; j++) {
				for (int i = 0; i <= n; i++) {
					printf("%d", D[j][i]);
				}
				printf("\n");
			}
		}

}

int main(int argc, char *argv[]) {

	printf("entered\n");
	if (argc != 4) {

		printf("usage: ./exec text pattern k");
		return -1;
	}
	printf(	"%d" + argc);
	text = argv[1];
	pattern = argv[2];
	n = strlen(text);
	m = strlen(pattern);
	k = atoi(argv[3]);


	/*
	*	ALLOCATING MEMORY FOR D, (N+1xM+1)
	*/
	D = (int **)malloc((m + 1) * sizeof(int *));
	for (int i = 0; i < m + 1; i = i + 1) {
		D[i] = (int *)malloc((n + 1) * sizeof(int));
	}

	/*
	*	MATRIX INIT: FIRST COLUMN=i, FIRST ROW=0, REST=-1
	*/

	omp_set_num_threads(NUMBER_OF_THREADS);
	#pragma omp parallel
	{
		int nthreads;
		nthreads = omp_get_num_threads();

		int ID = omp_get_thread_num();

		/*
		*	D MATRIX INITIALIZATION
		*/

		if (ID == 0) {
			for (int i = 0; i <= n; i = i + 1)
				D[0][i] = 0;
		}

		if (ID == 1) {
			printf("initializing first colum\n");
			for (int i = 1 ; i <= m; i = i + 1)
				D[i][0] = i;
		}

		for (int i = 1 + ID; i <= m; i = i + nthreads)
			for (int j = 1; j <= n; j = j + 1) {

				D[i][j] = -1;
			}

		//threads must sync here
		#pragma omp barrier

		/*
		*	D MATRIX COMPUTATION
		*/
		for (int i = ID + 1; i <= m; i = i + nthreads ) {
			for (int j = 1; j <= n; j++) {
				while (D[i - 1][j] == -1) {}
				D[i][j] = fmin(fmin(D[i - 1][j] + 1, D[i][j - 1] + 1), D[i - 1][j - 1] + (pattern[i - 1] == text[j - 1] ? 0 : 1));
			}


		}
		if (ID == 0) printf("D matrix computed");
		// //threads must sync here
		#pragma omp barrier



		// *	Last Row Iteration and Result Output

		for (int i = ID; i <= n; i = i + nthreads) {
			if (D[m][i] <= k)
				printf("k-match at i:%d \n", i);
		}



		/*
		*	Free all row except last one - no synch necessary because only row=m is being used
		*/
		for(int i=ID; i<m; i=i+nthreads){
			free(D[i]);
		}


	}
		
		free(D[m]);
		free(D);






}