#include <stdio.h>

int main() {
    int a=1;
    int b=2;
    int c=3;
    int d=4;

    int sum1 = a + b;
    int sum2 = c + d;

    a = sum1;
    b = sum2;

    sum1 = sum1 + a;
    sum2 = sum2 + b;

    printf("%d,%d\n", sum1,sum2);
    return 0;
}
