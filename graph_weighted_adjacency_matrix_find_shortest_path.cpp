#include <iostream>
#include <limits.h>
using namespace std;

void print_matrix(int ** a, int n)
{
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            cout << a[i][j] << ' ';
        }
        cout << endl;
    }
}

void find_min(int ** distance, int ** included, int n, int * min_idx){
    int min = INT_MAX;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            if (!included[i][j] and distance[i][j] < min){
                min = distance[i][j];
                min_idx[0] = i;
                min_idx[1] = j;
            }
    if (min_idx[0] != -1)
        included[min_idx[0]][min_idx[1]] = 1;
    return;
}

bool is_valid_idx(int i, int j, int n){
    if (i >= 0 and j >= 0 and i < n and j < n)
        return true;
    return false;
}

void update(int ** a, int ** distance, int ** path_x, int ** path_y, int x, int y, int n){
    int dx[] = {1, -1, 0, 0};
    int dy[] = {0, 0, 1, -1};
    for (int i = 0; i < 4; i++){
        int temp_x = x + dx[i];
        int temp_y = y + dy[i];
        if (is_valid_idx(temp_x, temp_y, n) and distance[temp_x][temp_y] >= distance[x][y] + a[temp_x][temp_y]){
            distance[temp_x][temp_y] = distance[x][y] + a[temp_x][temp_y];
            path_x[temp_x][temp_y] = x;
            path_y[temp_x][temp_y] = y;
        }
    }
}

void print_path(int ** path_x, int ** path_y, int ** a, int x, int y){
    int i = path_x[x][y];
    int j = path_y[x][y];
    
    if (i == x and j == y)
        return;
    print_path(path_x, path_y, a, i, j);
    cout << a[i][j] << ' ';
}

void dijkstra(int ** a, int n){
    
    int ** distance = new int *[n];
    for (int i = 0; i < n; i++)
        distance[i] = new int[n];
    
    int ** path_x = new int * [n];
    for (int i = 0; i < n; i++)
        path_x[i] = new int[n];
        
    int ** path_y = new int * [n];
    for (int i = 0; i < n; i++)
        path_y[i] = new int[n];
        
    int ** included = new int * [n];
    for (int i = 0; i < n; i++)
        included[i] = new int[n];
    
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++){
            distance[i][j] = INT_MAX;
            path_x[i][j] = -1;
            path_y[i][j] = -1;
            included[i][j] = 0;
        }
    
    distance[0][0] = a[0][0];
    path_x[0][0] = 0;
    path_y[0][0] = 0;
    included[0][0] = 1;
    update(a, distance, path_x, path_y, 0, 0, n);
    
    int min_idx[] = {-1, -1};
    find_min(distance, included, n, min_idx);
    while(min_idx[0] != -1){
        update(a, distance, path_x, path_y, min_idx[0], min_idx[1], n);
        min_idx[0] = -1; min_idx[1] = -1;
        find_min(distance, included, n, min_idx);
    }
    
    // print_matrix(a, n);
    // print_matrix(included, n);
    // print_matrix(distance, n);
    int l, m;
    l = n - 1;
    m = n - 1;
    print_path(path_x, path_y, a, l, m);
    cout << a[l][m] << endl;
    cout << distance[l][m] << endl;
}

int main() {
	//code
	int t;
	cin >> t;
	while(t--){
	    int n;
	    cin >> n;
	    int ** a = new int * [n];
	    for (int i = 0; i < n; i++){
	        a[i] = new int[n];
	    }
	    
	    for (int i = 0; i < n; i++)
	        for (int j = 0; j < n; j++)
	            cin >> a[i][j];
	   
	   dijkstra(a, n); 
	}
	return 0;
}
