#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <limits>
#include <stack>
#include <list>
#include <map>
#include <algorithm>

using namespace std;

const int INF = numeric_limits<int>::max();

// Structure pour représenter une arête avec un sommet et un poids
struct Edge
{
    int vertex, weight;
    Edge(int v, int w) : vertex(v), weight(w) {}
};

// 5.1 Utilisation de la matrice d'adjacence pour Dijkstra
void dijkstra_matrix(int start, int end, const vector<vector<int>> &adjMatrix, vector<int> &dist, vector<int> &pred)
{
    int n = adjMatrix.size();
    dist.assign(n, INF);
    pred.assign(n, -1);
    vector<bool> visited(n, false);
    dist[start] = 0;

    for (int i = 0; i < n; ++i)
    {
        int u = -1;
        for (int j = 0; j < n; ++j)
        {
            if (!visited[j] && (u == -1 || dist[j] < dist[u]))
            {
                u = j;
            }
        }

        if (dist[u] == INF)
            break;
        visited[u] = true;

        for (int v = 0; v < n; ++v)
        {
            if (adjMatrix[u][v] != 0 && dist[u] + adjMatrix[u][v] < dist[v])
            {
                dist[v] = dist[u] + adjMatrix[u][v];
                pred[v] = u;
            }
        }
    }
}

// 5.2 Utilisation de la liste d'adjacence pour Dijkstra
void dijkstra_list(int start, int n, const vector<vector<Edge>> &adjList, vector<int> &dist, vector<int> &pred)
{
    dist.assign(n, INF);
    pred.assign(n, -1);
    dist[start] = 0;

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push({0, start});

    while (!pq.empty())
    {
        int d = pq.top().first;
        int u = pq.top().second;
        pq.pop();

        if (d > dist[u])
            continue;

        for (const Edge &edge : adjList[u])
        {
            int v = edge.vertex;
            int w = edge.weight;
            if (dist[u] + w < dist[v])
            {
                dist[v] = dist[u] + w;
                pred[v] = u;
                pq.push({dist[v], v});
            }
        }
    }
}

// Fonction pour reconstruire le chemin
vector<int> reconstruct_path(int start, int end, const vector<int> &pred)
{
    vector<int> path;
    for (int v = end; v != -1; v = pred[v])
    {
        path.push_back(v);
    }
    reverse(path.begin(), path.end());
    if (path[0] == start)
        return path;
    return {};
}

// Fonction pour écrire le résultat
void write_result(ofstream &outfile, int dist, const vector<int> &path)
{
    if (dist == INF)
    {
        outfile << "Pas de chemin trouvé" << endl;
    }
    else
    {
        outfile << dist << endl;
        for (size_t i = 0; i < path.size(); ++i)
        {
            outfile << (path[i] + 1);
            if (i != path.size() - 1)
            {
                outfile << " → ";
            }
        }
        outfile << endl;
    }
}

// 5.3 Utilisation d'un tas pour Dijkstra
void dijkstra_heap(int start, int n, const vector<vector<Edge>> &adjList, vector<int> &dist, vector<int> &pred)
{
    dist.assign(n, INF);
    pred.assign(n, -1);
    dist[start] = 0;

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push({0, start});

    while (!pq.empty())
    {
        int d = pq.top().first;
        int u = pq.top().second;
        pq.pop();

        if (d > dist[u])
            continue;

        for (const Edge &edge : adjList[u])
        {
            int v = edge.vertex;
            int w = edge.weight;
            if (dist[u] + w < dist[v])
            {
                dist[v] = dist[u] + w;
                pred[v] = u;
                pq.push({dist[v], v});
            }
        }
    }
}

// 5.4 Trouver les plus courts chemins entre le sommet de départ et tous les autres
void dijkstra_all_pairs(int start, const vector<vector<int>> &adjMatrix, vector<int> &dist, vector<vector<int>> &paths)
{
    int n = adjMatrix.size();
    dist.assign(n, INF);
    vector<int> pred(n, -1);
    dist[start] = 0;

    for (int i = 0; i < n; ++i)
    {
        int u = -1;
        for (int j = 0; j < n; ++j)
        {
            if (dist[j] < dist[u])
            {
                u = j;
            }
        }

        if (dist[u] == INF)
            break;

        for (int v = 0; v < n; ++v)
        {
            if (adjMatrix[u][v] != 0 && dist[u] + adjMatrix[u][v] < dist[v])
            {
                dist[v] = dist[u] + adjMatrix[u][v];
                pred[v] = u;
            }
        }
    }

    // Reconstruire les chemins pour tous les sommets
    for (int v = 0; v < n; ++v)
    {
        paths[v] = reconstruct_path(start, v, pred);
    }
}

int main()
{
    ifstream infile("INPDIJGRAPH.txt");
    ofstream outfile("OUTCONGRAPH.txt");

    int n, m, start, end;
    infile >> n >> m >> start >> end;
    start--; // Indice de départ (1-based vers 0-based)
    end--;

    vector<vector<int>> adjMatrix(n, vector<int>(n, 0)); // Matrice d'adjacence
    vector<vector<Edge>> adjList(n);                     // Liste d'adjacence

    // Lecture des arêtes
    for (int i = 0; i < m; ++i)
    {
        int u, v, w;
        infile >> u >> v >> w;
        u--;
        v--; // Pour indexer à partir de 0
        adjMatrix[u][v] = w;
        adjMatrix[v][u] = w; // Graphe non orienté
        adjList[u].emplace_back(v, w);
        adjList[v].emplace_back(u, w);
    }

    vector<int> dist(n), pred(n);
    vector<int> shortest_path;

    // 5.1 Utilisation de la matrice d'adjacence
    dijkstra_matrix(start, end, adjMatrix, dist, pred);
    shortest_path = reconstruct_path(start, end, pred);
    write_result(outfile, dist[end], shortest_path);

    // 5.2 Utilisation de la liste d'adjacence
    dijkstra_list(start, n, adjList, dist, pred);
    shortest_path = reconstruct_path(start, end, pred);
    write_result(outfile, dist[end], shortest_path);

    // 5.3 Utilisation d'un tas pour stocker les nœuds
    dijkstra_heap(start, n, adjList, dist, pred);
    shortest_path = reconstruct_path(start, end, pred);
    write_result(outfile, dist[end], shortest_path);

    // // 5.4 Trouver les plus courts chemins entre le sommet de départ et tous les autres
    vector<vector<int>> all_paths(n);
    for (int i = 0; i < n; i++)
    {
        dijkstra_matrix(start, i, adjMatrix, dist, pred);
        all_paths[i] = reconstruct_path(start, i, pred);
    }

    outfile << "Tous les chemins depuis le sommet de départ :" << endl;
    for (int i = 0; i < n; ++i)
    {
        outfile << "Sommet " << (i + 1) << " : ";
        for (int node : all_paths[i])
        {
            outfile << (node + 1) << " ";
        }
        outfile << "(Distance: " << dist[i] << ")" << endl;
    }

    return 0;
}
