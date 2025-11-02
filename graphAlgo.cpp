#include <iostream>
#include <vector>
#include <queue>

using namespace std;

vector<int> topoSortBFS(int V, vector<int> adj[])
{
    vector<int> indeg(V, 0);
    for (int i = 0; i < V; i++)
    {
        for (int neigh : adj[i])
        {
            indeg[neigh]++;
        }
    }

    queue<int> q;
    for (int i = 0; i < V; i++)
        if (indeg[i] == 0)
            q.push(i);

    vector<int> topo;
    while (!q.empty())
    {
        int node = q.front();
        q.pop();
        topo.push_back(node);

        for (int neigh : adj[node])
        {
            indeg[neigh]--;
            if (indeg[neigh] == 0)
                q.push(neigh);
        }
    }

    return topo;
}

void dfs(vector<int> adj[], int node, vector<bool> &visited)
{
    visited[node] = true;
    for (auto neigh : adj[node])
    {
        if (!visited[neigh])
        {
            dfs(adj, neigh, visited);
        }
    }
}

bool dfsCycle(int parent, vector<int> adj[], int node, vector<bool> &visited)
{
    visited[node] = true;
    for (auto neigh : adj[node])
    {
        if (!visited[neigh])
        {
            if (dfsCycle(node, adj, neigh, visited))
                return true;
        }
        else if (parent != neigh)
        {
            return true;
        }
    }
    return false;
}

void dijkstra(int V, vector<pair<int, int>> adj[], int src)
{
    vector<int> dist(V, 1e9);
    dist[src] = 0;

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push({0, src});

    while (!pq.empty())
    {
        int currDist = pq.top().first;
        int node = pq.top().second;
        pq.pop();

        if (currDist > dist[node])
            continue;

        for (auto &edge : adj[node])
        {
            int nextNode = edge.first;
            int edgeWeight = edge.second;

            if (dist[node] + edgeWeight < dist[nextNode])
            {
                dist[nextNode] = dist[node] + edgeWeight;
                pq.push({dist[nextNode], nextNode});
            }
        }
    }

    cout << "Node : Distance from Source " << src << endl;
    for (int i = 0; i < V; i++)
    {
        cout << i << " : " << dist[i] << endl;
    }
}

void prims(int V, vector<pair<int, int>> adj[]) {
    vector<int> key(V, 1e9); // Minimum weight edge to connect
    vector<bool> inMST(V, false);
    vector<int> parent(V, -1);

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    
    key[0] = 0;
    pq.push({0, 0}); // {weight, node}

    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();

        inMST[u] = true;

        for (auto &edge : adj[u]) {
            int v = edge.first;
            int weight = edge.second;

            if (!inMST[v] && weight < key[v]) {
                parent[v] = u;
                key[v] = weight;
                pq.push({key[v], v});
            }
        }
    }

    cout << "Edge  -  Weight\n";
    for (int i = 1; i < V; i++)
        cout << parent[i] << " - " << i << "  : " << key[i] << endl;
}

class DSU {
    vector<int> parent, rank;

public:
    DSU(int n) {
        parent.resize(n);
        rank.resize(n, 0);
        for (int i = 0; i < n; i++) parent[i] = i;
    }

    int find(int x) {
        if (parent[x] != x)
            parent[x] = find(parent[x]); // Path compression
        return parent[x];
    }

    void unite(int x, int y) {
        int rootX = find(x);
        int rootY = find(y);
        if (rootX != rootY) {
            if (rank[rootX] < rank[rootY])
                parent[rootX] = rootY;
            else if (rank[rootX] > rank[rootY])
                parent[rootY] = rootX;
            else {
                parent[rootY] = rootX;
                rank[rootX]++;
            }
        }
    }
};

void kruskal(int V, vector<vector<int>>& edges) {
    // sort(edges.begin(), edges.end(), [](auto &a, auto &b) {
        // return a[2] < b[2]; // Sort by weight
    // });

    DSU dsu(V);
    int totalWeight = 0;

    cout << "Edge  -  Weight\n";
    for (auto &edge : edges) {
        int u = edge[0];
        int v = edge[1];
        int w = edge[2];

        if (dsu.find(u) != dsu.find(v)) {
            dsu.unite(u, v);
            totalWeight += w;
            cout << u << " - " << v << " : " << w << endl;
        }
    }
    cout << "Total weight of MST = " << totalWeight << endl;
}

const int INF = 1e9;

int main() {
    int V;
    cin >> V;

    vector<vector<int>> dist(V, vector<int>(V));

    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            cin >> dist[i][j];
            if (i != j && dist[i][j] == 0)
                dist[i][j] = INF; // No self loop, no direct path
        }
    }

    for (int k = 0; k < V; k++) {
        for (int i = 0; i < V; i++) {
            for (int j = 0; j < V; j++) {
                if (dist[i][k] != INF && dist[k][j] != INF)
                    dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
            }
        }
    }

    cout << "All-Pairs Shortest Path Matrix:\n";
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            if (dist[i][j] == INF) cout << "INF ";
            else cout << dist[i][j] << " ";
        }
        cout << "\n";
    }

    return 0;
}