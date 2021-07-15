#include <stdio.h>
#include <cs50.h>
#include <math.h>

int main(void)
{
    float dolars;
    do
    {

        dolars = get_float("change owed:");


    }
    while (dolars < 0);



    int cents = round(dolars * 100);
    int coins;

    while (cents > 25)
    {

        coins = cents / 25;
        cents = cents % 25;

    }
    while (cents > 10 && cents < 25)
    {

        coins += cents / 10;
        cents = cents % 10;

    }
    while (cents > 5 && cents < 10)
    {

        coins += cents / 5;
        cents = cents % 5;

    }
    while (cents > 0 && cents < 5)
    {

        coins += cents / 1;
        cents = cents % 1;

    }
    printf("coins:%i \n", coins);
}