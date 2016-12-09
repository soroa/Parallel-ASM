// Dynamic Programming - Efficient Algorithm : O(kn + m^2)
#include <stdio.h>
#include "rdtsc.h"
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <limits.h>

struct Triple
{
    int u;
    int v;
    int w;
};

int n, m, k;
char *text;
char *pattern;
int **prefix;
int **C;
struct Triple *triple;


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
void set_C_table(int i, int j, int value)
{
    C[i + 1][j + k + 1] = value;
}

int get_C_table(int i, int j)
{
    return C[i + 1][j + k + 1];
}

int within(int t, int *r)
{
    while (*r <= k && t > triple[*r].v)
        (*r)++;
    if (*r > k)
        return 0;
    else
    {
        if (t >= triple[*r].u)
            return 1;
        else
            return 0;
    }
}

void preprocess(char *pattern)
{
    // Initialize C table
    for (int d = 0; d <= (n - m + k + 1); d++) //Parallelize
        set_C_table(-1, d, d - 1);
    for (int d = -(k + 1); d <= -1; d++) //Parallelize
    {
        set_C_table(-d - 1, d, -1);
        set_C_table(-d - 2, d, INT_MIN);
    }
    // Initialize prefix array
    for (int d = 1; d < m; d++)
    {
        int i = 0;
        while (i + d < m)
        {
            int c = 1;
            while (i + c + d <= m && pattern[i + c - 1] == pattern[i + c + d - 1])
                c++;
            for (int j = 1; j <= c; j++)
                prefix[i + j][i + j + d] = c - j;
            i = i + c;
        }
    }
    // Initialize triple (Ue, Ve, We)
    for (int e = 0; e <= k; e++)
    {
        triple[e].u = 0;
        triple[e].v = 0;
        triple[e].w = 0;
    }
}

int main(int argc, char *argv[])
{
	unsigned long long t1, t2;
	t1=rdtsc();
    if (argc != 4)
        printf("usage: ./exec text pattern k");
    

    readTextandPattern(argv);

    n = strlen(text);
    m = strlen(pattern);
    k = atoi(argv[3]);

    C = (int **)malloc((k + 2) * sizeof(int *));
    for (int i = 0; i < k + 2; i++)
        C[i] = (int *)malloc((n - m + 2 * k + 3) * sizeof(int));
    prefix = (int **)malloc((m + 1) * sizeof(int *));
    for (int i = 0; i < m + 1; i++)
        prefix[i] = (int *)malloc((m + 1) * sizeof(int));
    triple = (struct Triple *)malloc((k + 1) * sizeof(struct Triple));

    preprocess(pattern);

    for (int c = 0; c <= n - m + k; c++)
    {
        int r = 0;
        for (int e = 0; e <= k; e++)
        {
            int d = c - e;
            int col = fmax(fmax(get_C_table(e - 1, d - 1) + 1, get_C_table(e - 1, d) + 1), get_C_table(e - 1, d + 1));
            int Se = col + 1;
            int found = 0;
            while (!found)
            {
                if (within(col + 1, &r))
                {
                    int f = triple[r].v - col;
                    int g = prefix[col + 1 - d][col + 1 - triple[r].w];
                    if (f == g)
                        col += f;
                    else
                    {
                        col += fmin(f, g);
                        found = 1;
                    }
                }
                else
                {
                    if (col < n && col - d < m && text[col] == pattern[col - d])
                        col++;
                    else
                        found = 1;
                }
            }
            set_C_table(e, d, fmin(fmin(col, m + d), n));
            // Update reference triple (Ue, Ve, We)
            if (triple[e].v >= get_C_table(e, d))
            {
                if (e == 0)
                    triple[e].u = c + 1;
                else
                    triple[e].u = fmax(triple[e].u, triple[e - 1].v + 1);
            }
            else
            {
                triple[e].v = get_C_table(e, d);
                triple[e].w = d;
                if (e == 0)
                    triple[e].u = c + 1;
                else
                    triple[e].u = fmax(Se, triple[e - 1].v + 1);
            }
        }
    }



    for (int d = -k; d <= n - m; d++)
        // if (get_C_table(k, d) == d + m && d + m > 0)
            // printf("%d ", d + m);

    for (int i = 0; i < k + 2; i++)
        free(C[i]);
    free(C);
    for (int i = 0; i < m + 1; i++)
        free(prefix[i]);
    free(prefix);
    free(triple);
	t2=rdtsc();
	printf("%llu \n", t2-t1);
}