
#include <stdio.h>

int main() {
    int arr[] = {5, 10, 15, 20, 25};
    int n = sizeof(arr) / sizeof(arr[0]);
    int sum = 0;


    for (int i = 0; i < n; i++) {
        sum += arr[i];
    }


    printf("数组元素的和为：%d\n", sum);
    return 0;
}

int main1() {
    int a[] = {5, 10, 15, 20, 25};
    int n = sizeof(a) / sizeof(a[0]);
    int s = 0;


    for (int i = 0; i < n; i++) {
        s += a[i];
    }

    printf("数组元素的和为：%d\n", s);
    return 0;
}

int func1(int argc, char ** argv)
{
    int n, i, sum;
    // printf("Enter a positive number: ");
    n = 10;
    // n=10
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