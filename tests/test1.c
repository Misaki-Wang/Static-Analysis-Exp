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

int test1() {
    int a1=1;
    int b1=2;
    int c1=3;
    int d1=4;

    int s1 = a1 + b1;
    int s2 = c1 +d1;

    a1 = s1;
    b1 = s2;

    s1 = s1 + a1;
    s2 = s2 + b1;

    printf("%d,%d\n", s1,s2);
    return 0;
}