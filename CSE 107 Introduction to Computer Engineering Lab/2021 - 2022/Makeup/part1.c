#include <stdio.h>

int main()
{
    int n =3, i, j, k;
    scanf("%d",&n);
    for (int j = 0; j < n; j++)
    {
        for (int k = 0; k < 3; k++)
        {
            for (int i = 0; i < (2 * n) - ((k * 2) + j) ; i++)
            {
                printf(" ");
            }
            for (int i =0; i < (j * 2) + (k * 4) + 1; i++)
            {
                printf("*");
            }
            printf("\n");
        }
       
    }
    for (i = 0; i < 2; i++)
    {
        for(j = 0; j < (2 * n) - 1; j++)
        {
            printf(" ");
        }
        printf("***\n");
    }
    
    return 0;
}