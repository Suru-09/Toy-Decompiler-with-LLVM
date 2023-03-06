#include "stdio.h"
#include "stdlib.h"

int two_way(int n)
{
    if(n < 5)
    {
        if(n < 1)
        {
            return 2;
        }
        else
        {
            return 3;
        }
    }
    else if(n > 5)
    {
        if(n > 15)
        {
            return 4;
        }
        else if(n > 10)
        {
            return 5;
        }
        else
        {
            return 6;
        }
    }
    else
    {
        return 6;
    }
    return -1;
}


int main()
{
    printf("Two way conditional: %d", two_way(15));
    return 0;
}