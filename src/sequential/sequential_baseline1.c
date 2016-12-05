// Dynamic Programming - D table : O(mn)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

char *text;
char *pattern;

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
        printf("text read correctly\n");
        text = textBuf;
    } else {
        printf("returned null \n");
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
        printf("pattern read correctly\n");
        pattern = patternBuf;
    } else {
        printf("returned null \n");
    }

    fclose(f);
}





int main(int argc, char *argv[])
{
    if (argc != 4)
        printf("usage: ./exec text pattern k");
    readTextandPattern(argv);
    int n = strlen(text), m = strlen(pattern);
    int k = atoi(argv[3]);

    int D[m + 1][n + 1];
    for (int i = 0; i <= n; i++)
        D[0][i] = 0;
    for (int i = 1; i <= m; i++)
        D[i][0] = i;

    for (int i = 1; i <= m; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            if (pattern[i - 1] == text[j - 1])
                D[i][j] = fmin(fmin(D[i - 1][j] + 1, D[i][j - 1] + 1), D[i - 1][j - 1]);
            else
                D[i][j] = fmin(fmin(D[i - 1][j] + 1, D[i][j - 1] + 1), D[i - 1][j - 1] + 1);
        }
    }
    for (int i = 1; i <= n; i++)
        if (D[m][i] <= k)
            printf("%d ", i);
}