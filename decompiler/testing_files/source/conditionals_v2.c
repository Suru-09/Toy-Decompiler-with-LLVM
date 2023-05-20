#include "stdio.h"

int if_else(int n)
{
    if(n < 5)
    {
        return 2;
    }
    else
    {
        return 3;
    }
}

int nested_if_else(int j, int i)
{
    if(j > i)
    {
        if(j > 10)
        {
            return 4;
        }
        else
        {
            return 5;
        }
    }
    else
    {
        if(i > 10)
        {
            return 6;
        }
        else
        {
            return 7;
        }
    }
}

int switch_case(int n)
{
    switch(n)
    {
        case 1:
            return n + 2;
        case 2:
            return 15;
        case 3:
            return 3 * n;
        case 6:
            return 20;
        default:
            return 4;
    }
}


int main()
{
    printf("If else: %d\n", if_else(5));
    printf("Nested if else: %d\n", nested_if_else(10, 5));
    printf("Switch case: %d\n", switch_case(6));
    return 0;
}