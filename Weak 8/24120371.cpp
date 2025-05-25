#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <queue>
#include <stack>
#include <algorithm>
#include <limits>
using namespace std;

vector<vector<int>> convertMatrixToList(const string& filename){
    ifstream fin(filename);
    vector<vector<int>> list;
    vector<int> row;
    int n;
    if (!fin.is_open()) {
        cout << "Error opening file" << filename << endl;
        return {};
    }
    fin >> n;
    fin.ignore();
    int val;
    for (int i = 0; i < n; i++)
    {
        int count = 0;
        for (int j = 0; j < n; j++){
            fin >> val;
            if (val = 1){
                count++;
                row.push_back(j);
            }
        }
        row.insert(row.begin(),count);
        list.push_back(row);
        row.clear();
    }
    
    return list;
}
vector<vector<int>> convertListToMatrix(const string& filename){
    ifstream fin(filename);
    vector<vector<int>> matrix;
    vector<int> row;
    int n;
    if (!fin.is_open()) {
        cout << "Error opening file" << filename << endl;
        return {};
    }
    fin >> n;
    fin.ignore();
    row.clear();
    row.resize(n);
    int count;
    int pos;
    for (int i = 0; i < n ; i++){
        fin >> count;
        for (int j = 0; i< count; j++){
            fin >> pos;
            row[pos] = 1;
        }
        matrix.push_back(row);
        row.clear();
    }    
    return matrix;
}
bool isDirected(const vector<vector<int>>& adjMatrix){
    int n = adjMatrix.size();
    for(int i = 1; i <= n; i++){
        for(int j = (i + 1); j <= n; j++){
            if(adjMatrix[i-1][j-1] != adjMatrix[j-1][i-1]) return true;//directed
        }
    }
    return false;//undirected
}
int countVertices(const vector<vector<int>>& adjMatrix){
    return adjMatrix.size();
}
int countEdges(const vector<vector<int>>& adjMatrix){
    int n = adjMatrix.size();
    int count = 0;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            if(adjMatrix[i][j] == 1) count++;
        }
    }
    if (!isDirected) count /= 2;
    return count;
}
vector<int> getIsolatedVertices(const vector<vector<int>>& adjMatrix){
    vector<int> isolated;
    int n = adjMatrix.size();
    for(int i = 0; i < n; i++){
        bool isolate = true;
        if (isDirected) {
            for (int j = 0; j < n; ++j) {
                if (adjMatrix[i][j] != 0 ||  adjMatrix[j][i] != 0)
                    isolate = false;
            }
        } else {
            for (int j = 0; j < n; ++j) {
                if (adjMatrix[i][j] != 0)
                    isolate = false;
            }
        }
        if (isolate)
        {
            isolated.push_back(i);
        }   
    }
    return isolated;
}
bool isCompleteGraph(const vector<vector<int>>& adjMatrix){
    int n = adjMatrix.size();
    for(int i = 1; i < n; i++){
        for(int j = j; j < n; j++){
            if((i == j) && adjMatrix[i][j] != 0) return false;
            if ((i != j) && adjMatrix[i][j] != 1) return false;
        }
    }
    return true;
}
// two color: 0 , 1
bool isBipartite(const std::vector<std::vector<int>>& adjMatrix){
    int n = adjMatrix.size();
    vector<int> color(n, -1);
    queue<int> q;
    for(int i = 0; i < n; i++){
        if(color[i] == -1){    
            q.push(i);
            color[i] = 0;
            while(!q.empty()){
                int u = q.front();
                q.pop();
                for(int v = 0; v < n; v++){
                    if(adjMatrix[u][v] == 1){
                        if (color[v] == -1)
                        {   
                            color[v] = 1 - color [u];
                            q.push(v);
                        }else if (color[u] == color[v])
                        {
                            return false;
                        }
                    }
                }
            }
        }
    }
    return true;
}
bool isCompleteBipartite(const vector<vector<int>>& adjMatrix){
    int n = adjMatrix.size();
    vector<int> color(n, -1);
    queue<int> q;
    vector<int> A,B;
    for(int i = 0; i < n; i++){
        if(color[i] == -1){    
            q.push(i);
            color[i] = 0;
            A.push_back(i);
            while(!q.empty()){
                int u = q.front();
                q.pop();
                for(int v = 0; v < n; v++){
                    if(adjMatrix[u][v] == 1){
                        if (color[v] == -1)
                        {   
                            color[v] = 1 - color [u];
                            q.push(v);
                            if (color[v] == 0) A.push_back(v);
                            else B.push_back(v);
                            
                        }else if (color[u] == color[v])
                        {
                            return false;
                        }
                    }
                }
            }
        }
    }
    for(int u : A){
        for(int v : B){
            if (adjMatrix[u][v] != 1) return false;
        }
    }
}
vector<vector<int>> convertToUndirectedGraph(const vector<vector<int>>& adjMatrix) {
    int n = adjMatrix.size();
    vector<vector<int>> undirected(n, vector<int>(n, 0));

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (adjMatrix[i][j] == 1 || adjMatrix[j][i] == 1) {
                undirected[i][j] = 1;
                undirected[j][i] = 1;
            }
        }
    }

    return undirected;
}
vector<vector<int>> getComplementGraph(const vector<vector<int>>& adjMatrix){
    int n = adjMatrix.size();
    vector<vector<int>> Matrix(n, vector<int>(n, 0));
    for (int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            if (i != j && adjMatrix[i][j] == 0) Matrix[i][j] = 1;
        }
    }
}
vector<int> findEulerCycle(const vector<vector<int>>& adjMatrix){
    vector<vector<int>> graph = adjMatrix;
    int n = adjMatrix.size();
    stack<int> st;
    vector<int> EC;
    
    for (int i = 0; i < n; ++i) {
        int degree = 0;
        for (int j = 0; j < n; ++j)
            degree += adjMatrix[i][j];
        if (degree % 2 != 0) return {}; // Euler cycle does not exist
    }


    st.push(0);
    while (!st.empty())
    {
        int u = st.top();
        bool hasEdge = false;
        for (int v = 0; v < n; v++)
        {
            if (graph[u][v] == 1)
            {
                hasEdge = true;
                st.push(v);
                graph[u][v] = 0;
                graph[v][u] = 0;
                break;
            }
            
        }
        if (!hasEdge)
        {
            st.pop();
            EC.push_back(u);
        }
    }
    reverse(EC.begin(), EC.end());
    return EC;
}
vector<vector<int>> dfsSpanningTree(const vector<vector<int>>& adjMatrix, int start){
    int n = adjMatrix.size();
    vector<bool> color(n, false);
    vector<vector<int>> tree(n, vector<int>(n, 0));
    stack<int> st;
    color[start] = true;
    st.push(start);
    while (!st.empty())
    {
        int u = st.top();
        st.pop();
        for (int v = n - 1; v >= 0; --v)
        {
            if (adjMatrix[u][v] == 1 && !color[v])
            {
                color[v] = true;
                tree[u][v]=tree[v][u]=1;
                st.push(v);
            }
        }
    }
    return tree;
}
vector<vector<int>> bfsSpanningTree(const vector<vector<int>>& adjMatrix, int start){
    int n = adjMatrix.size();
    vector<bool> color(n, false);
    vector<vector<int>> tree(n, vector<int>(n, 0));
    queue<int> q;
    color[start] = true;
    q.push(start);
    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        for (int v = 0; v < n; v++)
        {
            if (!color[v] && adjMatrix[u][v] == 1)
            {
                color[v] = true;
                tree[u][v]=tree[v][u]=1;
                q.push(v);
            }
        }
    }
    return tree;
}
bool isConnected(int u, int v, const vector<vector<int>>& adjMatrix){
    int n = adjMatrix.size();
    stack<int> st;
    vector<bool> color(n, false);

    st.push(u);
    while (!st.empty())
    {
        int u = st.top();
        st.pop();
        if (u == v) return true;
        for(int i = n-1; i >= 0; --i){
            if (adjMatrix[u][i] == 1 && !color[i])
            {
                color[i] = true;
                st.push(i);
            }
            
        }
    }
    return false;
}
vector<int> dijkstra(int start, int end, const vector<vector<int>>& adjMatrix){
    int n = adjMatrix.size();
    vector<bool> visited(n, false);
    vector<int> distance(n, numeric_limits<int>::max());
    vector<int> parent(n, -1);
    // {distance, vertex}
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;
    distance[start] = 0;
    pq.push({0,start});
    while (!pq.empty())
    {
        int u = pq.top().second;
        pq.pop();
        if(!visited[u]) continue;
        visited[u] = true;
        for (int v = 0; v < n; v++)
        {
            int weight = adjMatrix[u][v];
            if (weight > 0 && distance[u] + weight < distance[v]) {
                distance[v] = distance[u] + weight;
                parent[v] = u;
                pq.push({distance[v], v});
            }
        }
    }
    
    vector<int> path;
    if (distance[end] = numeric_limits<int>::max()) return path;
    for (int at = end; at != -1; at = parent[at])
        path.push_back(at);

    reverse(path.begin(), path.end());
    return path;

}
vector<int> bellmanFord(int start, int end, const vector<vector<int>>& adjMatrix){
    int n = adjMatrix.size();
    vector<int> distance(n, numeric_limits<int>::max());
    vector<int> parent(n ,-1);

    distance[start] = 0;

    // Lặp V - 1 lần
    for (int i = 0; i < n - 1; ++i) {
        for (int u = 0; u < n; ++u) {
            for (int v = 0; v < n; ++v) {
                int weight = adjMatrix[u][v];
                if (weight != 0 && distance[u] != numeric_limits<int>::max() &&
                    distance[u] + weight < distance[v]) {
                    distance[v] = distance[u] + weight;
                    parent[v] = u;
                }
            }
        }
    }

    // Kiểm tra chu trình âm
    for (int u = 0; u < n; ++u) {
        for (int v = 0; v < n; ++v) {
            int weight = adjMatrix[u][v];
            if (weight != 0 && distance[u] != numeric_limits<int>::max() &&
                distance[u] + weight < distance[v]) {
                // Phát hiện chu trình âm
                return {};
            }
        }
    }

    vector<int> path;
    if (distance[end] == numeric_limits<int>::max())
        return path; // Không có đường đi

    for (int at = end; at != -1; at = parent[at])
        path.push_back(at);

    reverse(path.begin(), path.end());
    return path;
}

