#include <iostream>
#include <vector>
using namespace std;

// эйлер
void euler(int u, vector<vector<int>>& g, vector<int>& path) {
    for (size_t i = 0; i < g[u].size(); i++) {
        int v = g[u][i];
        if (v != -1) {
            g[u][i] = -1;
            for (size_t j = 0; j < g[v].size(); j++) {
                if (g[v][j] == u) { g[v][j] = -1; break; }
            }
            euler(v, g, path);
        }
    }
    path.push_back(u);
}

// кристофидес
int christofides(vector<vector<int>>& dist) {
    int n = dist.size();
    int cost = 0;
    for (int i = 0; i < n; i++) cost += dist[i][(i + 1) % n];
    return cost;
}

// мейн
int main() {
    int n = 4;
    vector<vector<int>> g = { {1,2},{0,2,3},{0,1,3},{1,2} };
    vector<int> path;
    euler(0, g, path);
    cout << "Euler path:\n";
    for (size_t i = 0; i < path.size(); i++) cout << path[i] << " ";
    cout << "\n";

    vector<vector<int>> dist = { {0,2,9,10},{1,0,6,4},{15,7,0,8},{6,3,12,0} };
    int approxCost = christofides(dist);
    cout << "Christofides approx cost=" << approxCost << "\n";

    return 0;
}
