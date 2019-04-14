#include<stdio.h>
#include<stdlib.h>
int length(char * a)
{
    int count = 0;
    while(1)
    {
        if (a[count + 1] == '\0')
            break;
        count++;
    }
    return count+1;
}

void print_matrix(char ** a, int x, int y)
{
    for (int i = 0; i < x; i++){
        for (int j = 0; j < y; j++)
            printf("%4c\t", a[i][j]);
        printf("\n");
    }
}

void print_matrix_int(int ** a, int x, int y)
{
    for (int i = 0; i < x; i++){
        for (int j = 0; j < y; j++)
            printf("%4d\t", a[i][j]);
        printf("\n");
    }
}

void print_path(char ** path, char * a, int x, int y)
{
    if (x == 0 || y == 0)
        return;
    if (path[x][y] == 'd')
    {
        print_path(path, a, x-1, y-1);
        printf("%c ", a[x-1]);
    }
    else if (path[x][y] == 'a')
        print_path(path, a, x-1, y);
    else
        print_path(path, a, x, y - 1);
    return;
}

void LCS(char * a, char * b)
{
    /* Diagonally upward: 'd', above: 'a', backwards: 'b' */
    int m = length(a) + 1;
    int n = length(b) + 1;
    int ** lcs_length = (int **)malloc((m) * sizeof(int *));
    char ** path = (char **)malloc((m) * sizeof(char *));
    for (int i = 0; i < m; i++)
    {
        lcs_length[i] = (int *)malloc((n) * sizeof(int));
        path[i] = (char *)malloc((n) * sizeof(char));
    }

    for (int i = 0; i < n; i++)
        lcs_length[0][i] = 0;
    for (int j = 0; j < m; j++)
        lcs_length[j][0] = 0;

    for (int i = 1; i < m; i++)
    {
        for (int j = 1; j < n; j++)
        {
            if (a[i - 1] == b[j - 1])
            {
                lcs_length[i][j] = lcs_length[i - 1][j - 1] + 1;
                path[i][j] = 'd';
            }
            else if (lcs_length[i - 1][j] >= lcs_length[i][j - 1])
            {
                lcs_length[i][j] = lcs_length[i - 1][j];
                path[i][j] = 'a';
            }
            else
            {
                lcs_length[i][j] = lcs_length[i][j - 1];
                path[i][j] = ' ';
            }  
        }
    }
    //print_matrix(path, m, n);
    //printf("\n\n");
    //print_matrix_int(lcs_length, m, n);
    printf("Longest path length: %d\n", lcs_length[m - 1][n - 1]);
    print_path(path, a, m - 1, n - 1);
    return;
}

int main()
{
    char a[] = "ACCGGTCGAGTGCGCGGAAGCCGGCCGAA";
    char b[] = "GTCGTTCGGAATGCCGTTGCTCTGTAAA";
    LCS(a, b);
}