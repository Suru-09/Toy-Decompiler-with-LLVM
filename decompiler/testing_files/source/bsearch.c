#include<stdio.h>
#include<stdbool.h>

void guess(int s , int d  ){

     int m ;

     while(s < d ){

         m = ( s + d )/ 2;


                printf("Is your number greater than %d ? [Y/N]" , m);

                int c = getchar();
                c = getchar();

                if(c == 'Y'){

                    s = m + 1;
                }
                else{

                    d = m;
                }
     }
     printf("\nYour number is : %d \n" , s );
}

int main(){

    printf("Did you pick a number between 1 and 100?");
    int c = getchar();

    if(c == 'Y'){

        guess(1, 100);
    }
    else{

        printf("\n Game over");
    }
    c = getchar();

    return 0;
}