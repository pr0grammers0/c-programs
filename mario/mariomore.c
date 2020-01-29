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

    for (int line = 0; line < height; line++)
    {
        for (int width = height ; width != 0 ; width--)
        {
            if (line + 1  < width)
            {
                printf(" ");
            }
            else
            {
                printf("#");
            }
        }
        printf("  ");
        for (int i = 0; i <= line; i++)
        {
            printf("#");
        }
        printf("\n");
    }
}