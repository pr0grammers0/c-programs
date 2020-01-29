#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int height;
    do
    {
        height = get_int("height: ");

    }
    while (height <= 0 || height > 8);


    int line = 0;
    int width;
    while (line != height)
    {

        for (width = height ; width != 0 ; width--)
        {
            if (line + 1 < width)
            {
                printf(" ");
            }
            else
            {
                printf("#");
            }
        }
        printf("\n");
        line++;
    }

}