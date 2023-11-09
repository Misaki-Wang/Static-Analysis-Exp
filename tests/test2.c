#include <stdio.h>

int main(int argc, char ** argv)
{
    int n, i, sum;
    printf("Enter a positive number: ");
    n = argv[1];
    sum = 0;
    i = 1;    
    for(i=1;i<=n;i++)
    {
     sum = sum + i;
     i = i + 1;
    }
    printf ("sum = %d\n", sum);
    printf ("i = %d\n", i);
    return 0;
}

int func1(int argc, char ** argv)
{
    int n, i, sum;
    printf("Enter a positive number: ");
    n = argv[1];
    sum = 0;
    i = 1;    
    while (i <= n)
    {
     sum = sum + i;
     i = i + 1;
    }
    printf ("sum = %d\n", sum);
    printf ("i = %d\n", i);
    return 0;
}