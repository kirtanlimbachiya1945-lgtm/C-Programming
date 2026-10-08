//gcc ILOVEYOU.c -o ILOVEYOU -lm
//.\ILOVEYOU

#include <stdio.h>
#include <math.h>

int main()
{
    int x, y;

    /* I */
    for(y = 0; y < 15; y++)
    {
        for(x = 0; x < 25; x++)
        {
            if(y == 0 || y == 14 || x == 12)
                printf("*");
            else
                printf(" ");
        }
        printf("\n");
    }

    printf("\n\n");

    /* HEART */
    for(y = 12; y >= -12; y--)
    {
        for(x = -30; x <= 30; x++)
        {
            float a = x * 0.05;
            float b = y * 0.1;

            if(pow(a*a + b*b - 1, 3) - a*a*b*b*b <= 0)
                printf("*");
            else
                printf(" ");
        }
        printf("\n");
    }

    printf("\n\n");

    /* U */
    for(y = 0; y < 15; y++)
    {
        for(x = 0; x < 25; x++)
        {
            if(((x == 0 || x == 24) && y != 14) ||
               ((x > 0 && x < 24) && y == 14))
                printf("*");
            else
                printf(" ");
        }
        printf("\n");
    }

    return 0;
}