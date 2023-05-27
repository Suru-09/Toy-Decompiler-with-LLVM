#include <stdio.h>
#include <stdlib.h>


int n_way_conditional_switch(int n)
{
    int choice = 5;
    switch(n)
    {
        case 1:
            return choice + 15;
        case 2:
            return choice + 13;
        case 3:
            return choice + 11;
        case 5:
            return choice;
        default:
            return -1;
    }
}

int for_loop(int j) 
{
    int acc = 0;
    for(int i = 0; i < j; ++i)
    {
        int  a = 2, b = 5;
        int z = a + b;
        acc += z;
        i += 1;
    }
    return acc;
}

int while_pre_tested_loop(int flag_2) 
{
    int i = 0;
    int acc = 0;
    while(i <= flag_2)
    {
        int  a = 2, b = 5;
        int z = a + b;
        acc += z;
        i += 1;
    }
    return acc;
}

int while_post_tested_loop(int flag) 
{
    int i = 0;
    int acc = 0;
    do
    {
        int  a = 2, b = 5;
        int z = a + b;
        acc += z;
        i += 1;
    }while(flag <= 15);
    return acc;
}

int main()
{   
    printf("%d\n", n_way_conditional_switch(5));
    printf("%d\n", for_loop(5));
    printf("%d\n", while_pre_tested_loop(5));
    printf("%d\n", while_post_tested_loop(5));
    
    return 0;
}