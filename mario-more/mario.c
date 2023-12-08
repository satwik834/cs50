#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int height;
    do
    {
        height = get_int("height: ");

    }
    while (height <= 0 | height > 8);

    int kuo = 1;

    /* loop starts for hash columns*/
    for (int i = 0; i < height; i++)
    {
        /* loop starts for hash rows*/
        for (int k = 0; k < height; k++)
        {
            /* loop for make a slant pyramid*/
            while (kuo < height + 1)
            {
                /*printing spaces */
                for (int y = 0; y < height - kuo; y++)
                {
                    printf(" ");
                }
                /* printing hash*/
                for (int p = 0; p < kuo; p++)
                {
                    printf("#");
                }
                printf("  ");
                /*printing hashes again*/
                for (int p = 0; p < kuo; p++)
                {
                    printf("#");
                }


                /* going to a new line and increasing the variable */
                printf("\n");
                kuo++;
            }

        }


    }




}