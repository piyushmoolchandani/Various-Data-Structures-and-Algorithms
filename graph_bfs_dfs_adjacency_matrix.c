#include<stdio.h>
#include<stdlib.h>
#define n 8

/** Queue ----------------------------------------------------------------------------------------------**/
struct qnode
{
    int key;
    struct qnode * next;
};

typedef struct qnode qnode;

qnode * create_qnode (int key)
{
    qnode * temp = (qnode *)malloc(sizeof(qnode));
    temp -> key = key;
    temp -> next = NULL;
    return temp;
}

typedef struct Queue 
{ 
    struct qnode *front, *rear; 
}Queue;

Queue *create_Queue() 
{ 
    Queue *q = (Queue*)malloc(sizeof(Queue)); 
    q->front = q->rear = NULL; 
    return q; 
} 
  
void enQueue(Queue *q, int k) 
{ 
    qnode *temp = create_qnode(k); 
   
    if (q->rear == NULL) 
    { 
       q->front = q->rear = temp; 
       return; 
    } 
   
    q->rear->next = temp; 
    q->rear = temp; 
} 

int is_emptyq(Queue *q)
{
    if (q -> front == NULL)
        return 1;
    return 0;
} 

int deQueue(Queue *q) 
{ 
    if (!is_emptyq(q))
    {
        qnode *temp = q->front;
        int temp_int = temp -> key;
        q->front = q->front->next;
   
        if (q->front == NULL) 
            q->rear = NULL; 
        free(temp);
        return temp_int;
    }
} 
/** -------------------------------------------------------------------------------------------------------**/

/** Stack -------------------------------------------------------------------------------------------------**/
struct node
{
    int key;
    struct node * next;
};

typedef struct node node;

node * create_stack()
{
    return NULL;
}

 node * create_node (int key)
{
    node * temp = (node *)malloc(sizeof(node));
    temp -> key = key;
    temp -> next = NULL;
    return temp;
}

void push(node ** root, int key)
{
    if (*root == NULL)
    {
        * root = create_node(key);
        return;
    }

    node * temp = create_node(key);
    temp -> next = *root;
    *root = temp;
    return;
}

int is_empty(node * root)
{
    if (root == NULL)
        return 1;
    return 0;
}

void pop(node ** root)
{
    if (!is_empty(*root))
    {
        node * temp_node = *root;
        *root = (*root) -> next;
        free(temp_node);
        return;
    }
}

int top(node ** root)
{
    if (!is_empty(*root))
    {
        int temp = (*root) -> key;
        return temp;
    }
}
/** -------------------------------------------------------------------------------------------------------**/

// function scan_arr(a): scans an array of size n
void scan_arr(int a[])
{
    for (int i = 0; i < n; i++)
        scanf("%d", &a[i]);
}

// function print_arr(a): prints an array of size n
void print_arr(int a[])
{
    for (int i = 0; i < n; i++)
        printf("%d ", a[i]);
    printf("\n");
}

// function scan_mat(a): scans adjacency matrix of size n*n
void scan_mat(int **a)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            scanf("%d", &a[i][j]);
        }
    }
}

// funtion print_mat(a): prints adjacency matrix of size n*n
void print_mat(int **a)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            printf("%d ", a[i][j]);
        }
        printf("\n");
    }
}

// function create() : Allocates memory for adjacency matrix of size n*n
int ** create()
{
    int **mat = (int **)malloc(n * sizeof(int *));
    for (int i = 0; i < n; i++)
        mat[i] = (int *)malloc(n * sizeof(int));
    
    return mat;
}

// function find_index(var, m): finds index of var in array m
int find_index(int var, int m[])
{
    for (int i = 0; i < n; i++)
    {
        if (m[i] == var)
        {
            return i;
        }
    }
    return -1;
}

// function bfs_connected(a, adj, index, visited): performs bfs for connected graph
void bfs_connected(int a[], int ** adj, int index, int visited[])
{
    // Create a queue, enqueue starting node and mark it as visited.
    Queue* p = create_Queue();
    enQueue(p, a[index]);
    visited[index] = 1;

    // Run loop until queue is empty.
    while(!is_emptyq(p))
    {
        // perform one dequeue and print the element.
        int temp = deQueue(p);
        int temp_index = find_index(temp, a);
        printf("%d\t", temp);
        
        // Traverse through adjacency list and enqueue connected elements(only unvisited ones.)
        for (int i = 0; i < n; i++)
        {
            if (adj[temp_index][i] != 0 && visited[i] != 1)
            {
                    enQueue(p, a[i]);
                    visited[i] = 1;
            }
        }
    }
    printf("\n");
}

// function bfs(a, adj, index): performs bfs on any kind of graph
void bfs(int a[], int **adj, int index)
{   
    // Create visited list and perform bfs using given node.
    int visited[n] = {0};
    bfs_connected(a, adj, index, visited);

    // Perform bfs for remaining nodes.
    for (int i = 0; i < n; i++)
    {
        if (visited[i] == 0)
        {
            bfs_connected(a, adj, i, visited);
        }
    }
}

// function dfs_connected(a, adj, index, visited): performs dfs for connected graph
void dfs_connected(int a[], int ** adj, int index, int visited[])
{
	visited[index] = 1;
    printf("%d\t", a[index]);

    for (int i = 0; i < n; i++)
    {
        if (adj[index][i] == 1 && !visited[i])
                dfs_connected(a, adj, i, visited);
    }
}

void dfs(int a[], int ** adj, int index)
{
    // Create visited list and perform dfs using given node.
    int visited[n] = {0};
    dfs_connected(a, adj, index, visited);
    printf("\n");

    // Perform dfs for remaining nodes.
    for (int i = 0; i < n; i++)
    {
        if (visited[i] == 0)
        {
            dfs_connected(a, adj, i, visited);
            printf("\n");
        }
    }
}

int main()
{
    int arr[n];
    scan_arr(arr);
    int ** mat = create();
    scan_mat(mat);
    int a = 8;
    while(a--)
    {
        printf("\n");
        bfs(arr, mat, a);
        dfs(arr, mat, a);
    }
}