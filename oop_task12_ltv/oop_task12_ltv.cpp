#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

// дейкстра
void dijkstra(int src, vector<vector<pair<int, int>>>& g) {
    int n = g.size();
    vector<int> dist(n, 1e9);
    dist[src] = 0;
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push(make_pair(0, src));
    while (!pq.empty()) {
        int d = pq.top().first, u = pq.top().second;
        pq.pop();
        if (d > dist[u]) continue;
        for (size_t i = 0; i < g[u].size(); i++) {
            int v = g[u][i].first;
            int w = g[u][i].second;
            if (dist[v] > dist[u] + w) {
                dist[v] = dist[u] + w;
                pq.push(make_pair(dist[v], v));
            }
        }
    }
    cout << "Dijkstra distances from " << src << ":\n";
    for (int x : dist) cout << x << " ";
    cout << "\n";
}

// краскал
struct Edge { int u, v, w; };
int findSet(int v, vector<int>& parent) {
    if (parent[v] == v) return v;
    return parent[v] = findSet(parent[v], parent);
}
void kruskal(int n, vector<Edge>& edges) {
    sort(edges.begin(), edges.end(), [](Edge a, Edge b) { return a.w < b.w; });
    vector<int> parent(n); for (int i = 0; i < n; i++) parent[i] = i;
    int cost = 0;
    cout << "Kruskal edges:\n";
    for (size_t i = 0; i < edges.size(); i++) {
        int a = findSet(edges[i].u, parent);
        int b = findSet(edges[i].v, parent);
        if (a != b) {
            cout << edges[i].u << "-" << edges[i].v << " w=" << edges[i].w << "\n";
            cost += edges[i].w;
            parent[a] = b;
        }
    }
    cout << "Total MST cost=" << cost << "\n";
}

// прим
void prim(int n, vector<vector<pair<int, int>>>& g) {
    vector<int> key(n, 1e9), parent(n, -1);
    vector<bool> inMST(n, false);
    key[0] = 0;
    for (int i = 0; i < n; i++) {
        int u = -1;
        for (int v = 0; v < n; v++) if (!inMST[v] && (u == -1 || key[v] < key[u])) u = v;
        inMST[u] = true;
        for (size_t j = 0; j < g[u].size(); j++) {
            int v = g[u][j].first;
            int w = g[u][j].second;
            if (!inMST[v] && w < key[v]) { key[v] = w; parent[v] = u; }
        }
    }
    cout << "Prim MST edges:\n";
    for (int v = 1; v < n; v++) cout << parent[v] << "-" << v << " w=" << key[v] << "\n";
}

// мейн
int main() {
    int n = 4;
    vector<vector<pair<int, int>>> g(4);
    g[0].push_back(make_pair(1, 5));
    g[0].push_back(make_pair(3, 10));
    g[1].push_back(make_pair(2, 3));
    g[2].push_back(make_pair(3, 1));

    dijkstra(0, g);

    vector<Edge> edges;
    edges.push_back({ 0,1,5 });
    edges.push_back({ 1,2,3 });
    edges.push_back({ 2,3,1 });
    edges.push_back({ 0,3,10 });
    kruskal(n, edges);

    prim(n, g);
    return 0;
}
