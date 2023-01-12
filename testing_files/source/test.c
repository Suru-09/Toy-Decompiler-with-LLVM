#include <stdio.h>
#include <stdlib.h>


int calc_sum(int n)
{
    int sum = 0;
    for(int i = 0 ; i < n; ++i)
    {
        for(int j = 0; j < n / 2; ++j)
        {
            if(i > 2)
            {
                sum += i * 3 + j;
            }
        }
    }

    return sum;
}



int main()
{
    printf("Value of sum: <%d>\n", calc_sum(10));
    return 0;
}