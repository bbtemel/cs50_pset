#include <stdio.h>
#include <cs50.h>

int main(void)
{
    int h;
    do
    {
        h = get_int("Height:");

    }while(0>h || h>9);

    for(int i=0; i<h; i++){

        for(int j=h-i-1; j>0; j--){
            printf(" ");
        }
        for(int k=0; k<=i; k++){
            printf("#");
        }
        printf("\n");
    }
}