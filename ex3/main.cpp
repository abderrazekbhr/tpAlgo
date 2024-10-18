#include <iostream>
#include <vector>
#include <fstream>
#include <queue>

using namespace std;

// Fonction pour effectuer BFS et trouver un arbre couvrant
vector<pair<int, int>> bfs(int start, const vector<vector<int>> &adj, int nb_node)
{
    vector<pair<int, int>> mst;           // Arbre couvrant
    vector<bool> visited(nb_node, false); // Marque les sommets visités
    queue<int> q;                         // File d'attente pour BFS

    visited[start] = true; 
    q.push(start);         

    while (!q.empty())
    {
        int u = q.front(); 
        q.pop();           

        // Explorer tous les sommets adjacents
        for (int v : adj[u])
        {
            if (!visited[v])
            {                                  // Si le sommet n'est pas encore visité
                visited[v] = true;             // Marquer comme visité
                mst.push_back({u + 1, v + 1}); // Ajouter l'arête à l'arbre couvrant
                q.push(v);                     // Ajouter le sommet à la file
            }
        }
    }
    return mst;
}

// Fonction pour construire le tableau d'adjacence
vector<vector<int>> build_adjacency_list(const vector<pair<int, int>> &edges, int nb_node)
{
    vector<vector<int>> adj(nb_node);
    for (const auto &edge : edges)
    {
        adj[edge.first - 1].push_back(edge.second - 1); // Ajouter l'arête
        adj[edge.second - 1].push_back(edge.first - 1); // Ajouter l'arête dans les deux sens
    }
    return adj;
}

// Fonction pour ecriture du resultat
void write_result(const vector<pair<int, int>> &mst, ofstream &outfile)
{
    for (const auto &edge : mst)
    {
        outfile << edge.first << " " << edge.second << endl; 
    }
}

int main()
{
    ifstream infile("INPARBGRAPH.txt");
    ofstream outfile("OUTARBGRAPH.txt");

    int nb_node, nb_edges;
    infile >> nb_node >> nb_edges;

    vector<pair<int, int>> graph; // Vecteur pour stocker les arêtes
    for (int i = 0; i < nb_edges; i++)
    {
        int u, v;
        infile >> u >> v;
        graph.push_back({u, v});
    }

    // Construire la liste d'adjacence
    vector<vector<int>> adj = build_adjacency_list(graph, nb_node);

    // Trouver l'arbre couvrant en utilisant BFS
    vector<pair<int, int>> mst = bfs(0, adj, nb_node);

    // Écrire l'arbre couvrant dans le fichier de sortie
    write_result(mst, outfile);

    infile.close();
    outfile.close();

    return 0;
}
