#include <omp.h>
#include <stdio.h>
#include "rdtsc.h"
#include <stdlib.h>
#include <time.h>
#include <limits.h>
#include <string.h>
#include <math.h>

int n, m, k;
char  *pattern;
int **D;

char *text, *pattern;
static const int NUMBER_OF_THREADS = 4;


void printD(int** D) {

	for (int j = 0; j <= m; j++) {
		for (int i = 0; i <= n; i++) {
			printf("%d", D[j][i]);
		}
		printf("\n");
	}


}

void readTextandPattern(char *argv[]){
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

		printf("usage: ./exec text_path pattern_path k");
		return -1;
	}


	readTextandPattern(argv); 

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
		// //threads must sync here
		#pragma omp barrier



		// *	Last Row Iteration and Result Output

		for (int i = ID; i <= n; i = i + nthreads) {
			if (D[m][i] <= k)
				// printf("k-match at i:%d \n", i);
		}



		/*
		*	Free all row except last one - no synch necessary because only row=m is being used
		*/
		for (int i = ID; i < m; i = i + nthreads) {
			free(D[i]);
		}


	}

	free(D[m]);
	free(D);

    t2=rdtsc();
	printf("%llu \n", t2-t1);




}