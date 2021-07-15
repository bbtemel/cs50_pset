#include <stdio.h>
#include <cs50.h>
#include <math.h>

int main(void){

    long cnum;

    cnum = get_long("Card number:");

    int summ=0;
    int add=0;
    double counter=0;
    int sum = 0;
    int size=0;
    double count=1;
    long v=cnum;
    while (v != 0)
   {
       v=v/10;
       size++;
   }
   while ( count <= size)
   {




        long divd = pow(10,count);

        int d = ((cnum / divd) % 10);

        int c = d*2;

        int s=0;
        int k=c;
        while(k != 0)
   {

       k = k / 10;
       s++;
   }
        if (s == 1)
        {
            sum += c;
        }
        else if (s == 2)
        {
            sum += (c%10) + (c/10);
        }
        count += 2;


   }

   while ( counter < size)
   {


        long divde = pow(10,counter);

        int l = ((cnum / divde) % 10);

        add += l;
        counter += 2;
}
    long f = cnum / pow(10,(size-1));
    if(f==4)
    {
        printf("Visa");
    }
    else if(f==5)
    {
        printf("MasterCard");
    }
    else if(f==3)
    {
        printf("Amex");
    }
    summ=add+sum;
    if(summ%10==0){
        printf("Valid\n");
    }
    else if(summ%10 != 0){
        printf("Invalid\n");
    }

}