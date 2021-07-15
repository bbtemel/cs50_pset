#include <stdio.h>
#include <cs50.h>

int main(void)
{
    int h;
    do
    {
        h = get_int("Height:");

    }while(h<=0 || h>8);

    for(int i=0; i<h; i++){

        for(int j=h-i-1; j>0; j--){
            printf(" ");
        }
        for(int k=0; k<=i; k++){
            printf("#");
        }
        printf("  ");
        for(int a=0; a<i+1; a++){
            printf("#");
        }
        printf("\n");
    }
}