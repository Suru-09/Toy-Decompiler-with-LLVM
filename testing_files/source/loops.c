#include <stdio.h>
#include <stdlib.h>


void n_way_conditional_switch(int n)
{
    int choice = 5;
    switch(n)
    {
        case 1:
            break;
        case 2:
            break;
        case 3:
            break;
        case 5:
            printf("Found myself!\n");
            break;
        default:
            exit(2);
    }
}

void for_loop() 
{
    int i = 0;
    for(int i = 0; i < 10; ++i)
    {
        int  a = 2, b = 5;
        int z = a + b;
        i += 1;
    }
}

void while_pre_tested_loop() 
{
    int i = 0;
    while(i <= 10)
    {
        int  a = 2, b = 5;
        int z = a + b;
        i += 1;
    }
}

void while_post_tested_loop() 
{
    int i = 0;
    do
    {
        int  a = 2, b = 5;
        int z = a + b;
        i += 1;
    }while(i <= 10);
}

int main()
{   
    n_way_conditional_switch(5);
    for_loop();
    while_pre_tested_loop();
    while_post_tested_loop();
    
    return 0;
}