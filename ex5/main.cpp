#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <limits>
#include <algorithm>

using namespace std;

const int INF = numeric_limits<int>::max();

// Structure pour représenter une arête avec un sommet et un poids
struct Edge {
    int vertex, weight;
    Edge(int v, int w) : vertex(v), weight(w) {}
};

// Fonction pour appliquer Dijkstra
void dijkstra(int start, int n, const vector<vector<Edge>>& adj, vector<int>& dist, vector<int>& pred) {
    dist.assign(n, INF);
    pred.assign(n, -1);
    dist[start] = 0;
    
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push({0, start});
    
    while (!pq.empty()) {
        int d = pq.top().first;
        int u = pq.top().second;
        pq.pop();
        
        if (d > dist[u]) continue;
        
        for (const Edge& edge : adj[u]) {
            int v = edge.vertex;
            int w = edge.weight;
            if (dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                pred[v] = u;
                pq.push({dist[v], v});
            }
        }
    }
}

// Fonction pour reconstruire le chemin
vector<int> reconstruct_path(int start, int end, const vector<int>& pred) {
    vector<int> path;
    for (int v = end; v != -1; v = pred[v])
        path.push_back(v);
    reverse(path.begin(), path.end());
    if (path[0] == start)
        return path;
    return {};
}

int main() {
    ifstream infile("INPDIJGRAPH.txt");
    ofstream outfile("OUTCONGRAPH.txt");

    int n, m, start, end;
    infile >> n >> m >> start >> end;
    start--;  // Pour indexer à partir de 0
    end--;

    vector<vector<Edge>> adj(n);

    for (int i = 0; i < m; ++i) {
        int u, v, w;
        infile >> u >> v >> w;
        u--; v--;  // Pour indexer à partir de 0
        adj[u].emplace_back(v, w);
        adj[v].emplace_back(u, w);  // Graphe non orienté
    }

    vector<int> dist(n), pred(n);
    dijkstra(start, n, adj, dist, pred);

    int shortest_distance = dist[end];
    vector<int> shortest_path = reconstruct_path(start, end, pred);

    if (shortest_distance == INF) {
        outfile << "Pas de chemin trouvé" << endl;
    } else {
        outfile << shortest_distance << endl;
        for (size_t i = 0; i < shortest_path.size(); ++i) {
            outfile << (shortest_path[i] + 1);
            if (i != shortest_path.size() - 1)
                outfile << " → ";
        }
        outfile << endl;
    }

    return 0;
}
