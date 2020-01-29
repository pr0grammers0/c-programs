#include <cs50.h>
#include <stdio.h>
#include <math.h>

int main(void)
{
    int i = 0;
    int cents;
    float dollars;
    do
    {
        dollars = get_float("change owed: ");
    }
    while (dollars <= 0);

    cents = round(dollars * 100);
    while (cents != 0)
    {
        if (cents - 25 > -0.1)
        {
            cents -= 25;
            i++;
        }
        else if (cents - 10 > -0.1)
        {
            cents -= 10;
            i++;
        }
        else if (cents - 5 > -0.1)
        {
            cents -= 5;
            i++;
        }
        else if (cents - 1 > -0.1)
        {
            cents -= 1;
            i++;
        }
    }
    printf("%i\n", i);
}