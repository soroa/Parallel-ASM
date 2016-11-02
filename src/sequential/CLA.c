// this is a part of code in 1990 algo that does the CLA

int d;
int i;
int j;
int prefix1[100][100];
int c;

 for (d=1; d=m; d++) 
     {
       i=0;
       
       while ((i+d)<m)
             {
               c=1;

               
               while (((i+c+d) <= m) && (y[i+c] == y[i+c+d]))
                     {
                      c++;
                     }

               for (j=1; j<c; j++)
                    {
                     prefix1 [i+j][i+j+d] =c-j;
                    }
              
               i= i+c;
             } 

     }
