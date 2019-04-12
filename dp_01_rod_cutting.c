#include<stdio.h>
#include<stdlib.h>
#define Negative_infinity -10000    

void print(int * a, int n)
{
    for (int i = 0; i < n; i++)
        printf("%d\t", a[i]);
    printf("\n");
}

int rod_cutting_recursive(int A[], int n, int q[], int cut[])
{
    int temp;
    if (q[n] >= 0)
        return q[n];
    if (n == 0)
        temp = 0;
    else
    {
        temp = Negative_infinity;
        for (int i = 1; i <= n; i++)
        {
            int temp_2 = rod_cutting_recursive(A, n - i, q, cut);
            if (temp < (A[i] + temp_2))
            {
                temp = A[i] + temp_2;
                cut[n] = i;
            }
        }
    }
    q[n] = temp;
    return temp;
}

void rod_cutting(int A[], int n)
{
    int q[11];
    for (int i = 0; i <= n; i++)
        q[i] = Negative_infinity;
    int cut[11];
    for (int i = 0; i <= n; i++)
        cut[i] = i;
    rod_cutting_recursive(A, n, q, cut);
    while(n > 0)
    {
        printf("%d\t", cut[n]);
        n = n - cut[n];
    }
    printf("\n");
}

int main()
{
    int benefit[11] = {0, 1, 5, 8, 9, 10, 17, 17, 20, 24, 30};
    int a;
    while(1)
    {
        printf("Enter '-1' to exit and any other key for solution of that part.\n");
        scanf("%d", &a);
        if (a == -1 || a > 10)
            break;
        else
        {
            rod_cutting(benefit, a);
        }
        
    }
}
