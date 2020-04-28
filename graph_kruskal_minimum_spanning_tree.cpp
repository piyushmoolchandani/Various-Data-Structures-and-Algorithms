#include<iostream>
#include<algorithm>
using namespace std;

class Edge{
    public:
        int x, y, w;
};

class Graph{
    public:
        int v, e;
        Edge * edges;

    Graph(int v, int e){
        this -> v = v;
        this -> e = e;
        this -> edges = new Edge[e];
    }
};

class subset{
    public:
        int parent;
};

int find(subset * subsets, int i){
    if (subsets[i].parent != i){
        int temp = find(subsets, subsets[i].parent);
        return temp;
    }
    return i;
}
  
int union_(subset * subsets, int i, int j){
    int x = find(subsets, i);
    int y = find(subsets, j);
    
    if (x == y)
        return -1;

    subsets[min(x, y)].parent = max(x, y);
    return 1;
}

int sort_(Edge a, Edge b){
    return a.w < b.w;
}

void print(Edge * edges, int e){
    for (int i = 0; i < e; i++){
        cout << edges[i].x << ' ' << edges[i].y << ' ' << edges[i].w << endl;
    }    
}

int main(){
    int v = 9;
    int e = 14;
    Graph * graph = new Graph(v, e);
    
    Edge * spanning_tree_edges = new Edge[v - 1];
    graph->edges[0].x = 3;  
    graph->edges[0].y = 5;  
    graph->edges[0].w = 14;  
  
    graph->edges[1].x = 7;  
    graph->edges[1].y = 6;  
    graph->edges[1].w = 1;  
    
    graph->edges[2].x = 1;  
    graph->edges[2].y = 7;  
    graph->edges[2].w = 11;  
  
    graph->edges[3].x = 8;  
    graph->edges[3].y = 2;  
    graph->edges[3].w = 2;  
  
    graph->edges[4].x = 5;  
    graph->edges[4].y = 4;  
    graph->edges[4].w = 10;  
    
    graph->edges[5].x = 6;  
    graph->edges[5].y = 5;  
    graph->edges[5].w = 2;

    graph->edges[6].x = 0;  
    graph->edges[6].y = 1;  
    graph->edges[6].w = 4;
    
    graph->edges[7].x = 3;  
    graph->edges[7].y = 4;  
    graph->edges[7].w = 9;
    
    graph->edges[8].x = 2;  
    graph->edges[8].y = 5;  
    graph->edges[8].w = 4;

    graph->edges[9].x = 6;  
    graph->edges[9].y = 8;  
    graph->edges[9].w = 6;

    graph -> edges[10].x = 2;
    graph -> edges[10].y = 3;
    graph -> edges[10].w = 7;
    
    graph->edges[11].x = 7;  
    graph->edges[11].y = 8;  
    graph->edges[11].w = 7;

    graph->edges[12].x = 0;  
    graph->edges[12].y = 7;  
    graph->edges[12].w = 8;
    
    graph->edges[13].x = 1;  
    graph->edges[13].y = 2;  
    graph->edges[13].w = 8;

    subset * subsets = new subset[v];
    for (int i = 0; i < v; i++){
        subsets[i].parent = i;
    }
  
    sort(graph -> edges, graph -> edges + e, sort_);
    int i = 0;
    int j = 0;
    while (i < v - 1){
        int x = graph -> edges[j].x;
        int y = graph -> edges[j].y;
        int w = graph -> edges[j].w;
        if (union_(subsets, x, y) == 1){
            spanning_tree_edges[i].x = x;
            spanning_tree_edges[i].y = y;
            spanning_tree_edges[i].w = w;
            i++;
        }
        j++;
    }
    cout << "Edges in Minimum spanning tree:" << endl;
    print(spanning_tree_edges, v - 1);
}
