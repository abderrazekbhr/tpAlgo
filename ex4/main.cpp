#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

void dfs(int v, const vector<vector<int>>& graph, vector<bool>& visited, vector<int>& component) {
    visited[v] = true;
    component.push_back(v);
    
    for (int neighbor : graph[v]) {
        if (!visited[neighbor]) {
            dfs(neighbor, graph, visited, component);
        }
    }
}

int main() {
    // Lecture du fichier d'entrée
    ifstream inputFile("INPCONGRAPH.txt");
    int n, m;
    inputFile >> n >> m;

    vector<vector<int>> graph(n + 1); // Graphe (1-indexed)
    
    for (int i = 0; i < m; ++i) {
        int u, v;
        inputFile >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u); // Ajout de l'arête dans les deux sens (non orienté)
    }
    
    inputFile.close();

    vector<bool> visited(n + 1, false); // Liste pour suivre les sommets visités
    vector<vector<int>> components; // Liste pour stocker les composantes connexes

    // Trouver toutes les composantes connexes
    for (int v = 1; v <= n; ++v) {
        if (!visited[v]) {
            vector<int> component; // Composante connexe actuelle
            dfs(v, graph, visited, component);
            components.push_back(component);
        }
    }

    // Écriture du fichier de sortie
    ofstream outputFile("OUTCONGRAPH.txt");
    outputFile << components.size() << endl; // Nombre de composantes connexes
    for (int i = 0; i < components.size(); ++i) {
        outputFile << "composante connexe " << (i + 1) << endl;
        sort(components[i].begin(), components[i].end()); // Trier les sommets
        for (int vertex : components[i]) {
            outputFile << vertex << " ";
        }
        outputFile << endl;
    }

    outputFile.close();
    return 0;
}
