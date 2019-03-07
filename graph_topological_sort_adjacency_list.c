#include<stdio.h>
#include<stdlib.h>

/** Stack -------------------------------------------------------------------------------------------------**/
struct snode
{
    int key;
    struct snode * next;
};

typedef struct snode snode;

snode * create_stack()
{
    return NULL;
}

 snode * create_snode (int key)
{
    snode * temp = (snode *)malloc(sizeof(snode));
    temp -> key = key;
    temp -> next = NULL;
    return temp;
}

void push(snode ** root, int key)
{
    if (*root == NULL)
    {
        *root = create_snode(key);
        return;
    }

    snode * temp = create_snode(key);
    temp -> next = *root;
    *root = temp;
    return;
}

int is_empty(snode * root)
{
    if (root == NULL)
        return 1;
    return 0;
}

void pop(snode ** root)
{
    if (!is_empty(*root))
    {
        snode * temp_snode = *root;
        *root = (*root) -> next;
        free(temp_snode);
        return;
    }
}

int top(snode ** root)
{
    if (!is_empty(*root))
    {
        int temp = (*root) -> key;
        return temp;
    }
}

void print_stack(snode * root)
{
    if (!is_empty(root))
    {
        snode * temp = root;
        while (temp != NULL)
        {
            printf("%d\t", temp -> key);
            temp = temp -> next;
        }
        printf("\n");
        return;
    }
    printf("%s\n", "Stack Empty!");
}
/** -------------------------------------------------------------------------------------------------------**/


typedef struct adj_list_node{
    int destination;
    struct adj_list_node * next;
}node;

typedef struct adj_list{
    node * head;
}adj_list;

typedef struct graph{
    int vertices;
    struct adj_list * array;
}graph;

graph * create_graph(int vertices)
{
    graph * new = (graph *)malloc(sizeof(graph));
    new -> vertices = vertices;
    new -> array = (adj_list *)malloc(vertices * sizeof(adj_list));
    for (int i = 0; i < vertices; i++)
        new -> array[i].head = NULL;
    return new;
}

node * create_node(int destination)
{
    node * temp = (node *)malloc(sizeof(node));
    temp -> destination = destination;
    temp -> next = NULL;
    return temp;    
}

void print_graph(graph * g)
{
    for (int i = 0; i < g -> vertices; i++)
    {
        node * temp = g -> array[i].head;
        printf("%d: ", i);
        while(temp)
        {
            printf("%d -> ", temp -> destination);
            temp = temp -> next;
        }
        printf("\n");
    }
}

void add_edge(graph * Graph, int source, int destination)
{
    node * new_node = create_node(destination);
    new_node -> next = Graph -> array[source].head;
    Graph -> array[source].head = new_node;
}

void topological_sort_(graph * Graph, int i, int visited[], snode ** Stack)
{
    visited[i] = 1;
    node * temp = Graph -> array[i].head;
    /**while(temp)
    {
        if (visited[temp -> destination] == 0)
            topological_sort_(Graph, temp -> destination, visited, Stack);
        temp = temp -> next;
    }**/
    for (node * temp = Graph -> array[i].head; temp != NULL; temp = temp -> next)
    {    
        if (visited[temp -> destination] == 0)
            topological_sort_(Graph, temp -> destination, visited, Stack);
    }
    push(Stack, i);
}

void topological_sort(graph * Graph)
{
    int v = Graph -> vertices;
    int visited[v];
    for (int i = 0; i < v; i++)
        visited[i] = 0;
    snode * Stack = create_stack();
    for (int i = 0; i < Graph -> vertices; i++)
        if (visited[i] == 0)
            topological_sort_(Graph, i, visited, &Stack);
    print_stack(Stack);
}

int main()
{
    graph * Graph = create_graph(6);
    add_edge(Graph, 5, 2);
    add_edge(Graph, 5, 0);
    add_edge(Graph, 4, 0);
    add_edge(Graph, 4, 1);
    add_edge(Graph, 2, 3);
    add_edge(Graph, 3, 1);
    printf("%s\n", "Following is a Topological Sort of the given graph:"); 
    topological_sort(Graph);

    graph * Graph_2 = create_graph(10);
    add_edge(Graph_2, 7, 1);
    add_edge(Graph_2, 7, 3);
    add_edge(Graph_2, 7, 6);
    add_edge(Graph_2, 5, 3);
    add_edge(Graph_2, 5, 6);
    add_edge(Graph_2, 6, 8);
    add_edge(Graph_2, 4, 8);
    add_edge(Graph_2, 4, 2);
    add_edge(Graph_2, 2, 10);
    printf("%s\n", "Following is a Topological Sort of the given graph:"); 
    topological_sort(Graph_2);
}