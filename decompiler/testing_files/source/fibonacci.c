#include "stdio.h"


int fibo(int n) {
   return n > 1 ? fibo(n - 1) + fibo(n - 2) : 1;
}

int main() {

    int n = 15;
    printf("Fibonacci of <%d> is : [%d]\n", n, fibo(n - 1));
    return 0;
}