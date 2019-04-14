#include<stdio.h>
#include<stdlib.h>
#define Infinite 100000

void print_parenthesized(int ** previous, int i, int j)
{
    if (i == j)
        printf("A%d", i+1);
    else
    {
        printf("(");
        print_parenthesized(previous, i, previous[i][j]);
        printf(" * ");
        print_parenthesized(previous, previous[i][j] + 1, j);
        printf(")");
    }
}

void print_matrix(int ** a, int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
            printf("%10d", a[i][j]);
        printf("\n");
    }
}

int top_down(int * a, int i, int j, int **cost, int **previous)
{
    if (cost[i][j] < Infinite)
    {
        //printf("Value already present [%d %d]\n", i, j);
        return cost[i][j];
    }
    if (i == j)
    {
        //printf("Indexes are same [%d %d]\n", i, j);
        cost[i][j] = 0;
    }
    else
    {
        //printf("Caluculating for [%d %d]\n", i, j);
        for (int k = i; k < j; k++)
        {
            int temp_a = top_down(a, i, k, cost, previous);
            int temp_b = top_down(a, k+1, j, cost, previous);
            int temp_c = a[i] * a[k+1] * a[j+1];
            if (cost[i][j] >= temp_a + temp_b + temp_c)
            {
                cost[i][j] = temp_a + temp_b + a[i] * a[k+1] * a[j+1];
                previous[i][j] = k;
            }
            //print_matrix(cost, 6);
        }
    }
    //printf("Caluculated for [%d %d]\n", i, j);
    return cost[i][j];
}

void matrix_chain_multiplication_order(int a[], int n)
{
    n = n - 1;
    int ** cost = (int **)malloc(n * sizeof(int *));
    for (int i = 0; i < n; i++)
        cost[i] = (int *)malloc(n * sizeof(int));
    int ** previous = (int **)malloc(n * sizeof(int *));
    for (int i = 0; i < n; i++)
        previous[i] = (int *)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            cost[i][j] = Infinite;
    top_down(a, 0, n - 1, cost, previous);
    print_parenthesized(previous, 0, n - 1);
}

int main()
{
    int a[] = {30, 35, 15, 5, 10, 20, 25};
    matrix_chain_multiplication_order(a, 7);
}