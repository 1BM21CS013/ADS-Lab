#include <bits/stdc++.h>
using namespace std;

class DisjointSet {
  vector<int> parent;
  int setCount;

public: 
  DisjointSet(int n) {
    parent.resize(n);
    setCount = n;

    for(int i = 0 ; i < n ; i++)
      parent[i] = -1;
  }
  
  int findParent(int node) {
    if(parent[node] < 0)
      return node;
    return parent[node] = findParent(parent[node]);
  }

  void unite(int node1, int node2) {
    int parent1 = findParent(node1);
    int parent2 = findParent(node2);

    if(parent1 == parent2)
      return;

    if(abs(parent[parent1]) >= abs(parent[parent2])) {
      parent[parent1] += parent[parent2];
      parent[parent2] = parent1;
    } else {
      parent[parent2] += parent[parent1];
      parent[parent1] = parent2;
    }

    setCount--;
  }

  int getSetCount() {
    return setCount;
  }

};

bool isMergePossible(vector<vector<int>>& mat ,int r1, int c1, int r2, int c2, int n, int m) {
  if(r1 < 0 || c1 < 0 || r2 < 0 || c2 < 0)
    return false;
  if(r1 >= n || c1 >= m || r2 >= n || c2 >= m)
    return false;
  if(mat[r1][c1] == 1 && mat[r2][c2] == 1)
    return true;
  return false;
}

int findNumberOfIslands(vector<vector<int>>& mat)
{    
    int n = mat.size();
    int m = mat[0].size();

    int dr[8] = {0, 1, 0, -1, -1, 1, 1, -1};
    int dc[8] = {1, 0, -1, 0, 1, 1, -1, -1};

    DisjointSet dsu(n * m);
    
    for(int i = 0 ; i < n ; i++)
      for(int j = 0 ; j < m ; j++) 
        for(int k = 0 ; k < 8 ; k++)
          if(isMergePossible(mat, i, j, i + dr[k], j + dc[k], n, m))        
            dsu.unite(i * m + j, (i + dr[k]) * m + j + dc[k]);

    int water = 0;
    for(int i = 0 ; i < n ; i++)
      for(int j = 0 ; j < m ; j++)
        if(mat[i][j] == 0)
          water++;

    return dsu.getSetCount() - water;
}

int main()
{
    int n, m;
    cin >> n >> m;
    vector<vector<int>> mat(n, vector<int>(m));

    for(int i = 0 ; i < n ; i++)
      for(int j = 0 ; j < m ; j++)
        cin >> mat[i][j];

    cout << findNumberOfIslands(mat);
    return 0;
}