#include <stdio.h>
#include<stdlib.h>
#include<string.h>
#include<limits.h>
#include<time.h>

void generate_price_array(int n ,int price[]){

    srand(time(0));
    for(int i = 0 ; i < n ; ++i)
        price[i] = rand() % 100;
}

int maxi(int a , int b){
    if(a > b)
        return a;
    return b;
}

int rod_cutting(int n , int price[]){

    int array_ways[n + 1];
    memset(array_ways , 0 , (n + 1) * sizeof(int));

    for(int i = 1 ; i <= n ; ++i){
        int max = INT_MIN;
        for(int j = 0 ; j <  i ; ++j){
            max = maxi(price[j] + array_ways[i - j - 1] , max);
            array_ways[i] = max;
        }
    }

    return array_ways[n];
}
int main() {

    int n ;
    printf("Enter the n value : ");
    scanf("%d" , &n);
    int price[n];

    generate_price_array(n ,price);
    printf("The array of prices is : \n");
    for(int i = 0 ; i < n ; ++i)
        printf(" %d " , price[i]);

    printf("\nThe best value you can get is : %d\n" , rod_cutting(n , price));
    return 0;
}
