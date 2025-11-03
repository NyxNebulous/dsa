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

#include <bits/stdc++.h>
using namespace std;

struct Edge {
    int u, v, w;
};

struct DSU {
    vector<int> parent, rank;
    DSU(int n) {
        parent.resize(n);
        rank.resize(n, 0);
        for (int i = 0; i < n; i++) parent[i] = i;
    }
    int find(int x) {
        if (x == parent[x]) return x;
        return parent[x] = find(parent[x]); // Path compression
    }
    void unite(int x, int y) {
        x = find(x);
        y = find(y);
        if (x != y) {
            if (rank[x] < rank[y]) parent[x] = y;
            else if (rank[x] > rank[y]) parent[y] = x;
            else {
                parent[y] = x;
                rank[x]++;
            }
        }
    }
};

void kruskal(int V, vector<Edge>& edges) {
    sort(edges.begin(), edges.end(), [](Edge a, Edge b) {
        return a.w < b.w;   // Sort by weight
    });

    DSU dsu(V);
    int totalCost = 0;

    for (auto &edge : edges) {
        if (dsu.find(edge.u) != dsu.find(edge.v)) { // No cycle
            totalCost += edge.w;
            dsu.unite(edge.u, edge.v);
        }
    }

    cout << "Total MST Cost (Kruskal's): " << totalCost << endl;
}

int main() {
    int V = 5;
    vector<Edge> edges = {
        {0, 1, 2}, {1, 2, 3}, {0, 3, 6},
        {1, 3, 8}, {2, 3, 5}
    };

    kruskal(V, edges);
    return 0;
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