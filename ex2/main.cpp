#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

int n, k;
vector<int> a;
vector<vector<int>> memo;
vector<vector<int>> previous;  // Pour suivre les indices pour la reconstruction

// Fonction récursive avec mémoïsation
int findMaxSubsequence(int index, int mod) {
    // Si on a dépassé le dernier élément
    if (index == n) {
        return (mod == 0) ? 0 : -100000; // Si la somme mod k est 0, on retourne 0 (valid), sinon une grande valeur négative
    }

    // Si on a déjà calculé ce sous-problème
    if (memo[index][mod] != -1) {
        return memo[index][mod];
    }

    // Ne pas prendre l'élément a[index]
    int exclude = findMaxSubsequence(index + 1, mod);

    // Prendre l'élément a[index]
    int newMod = (mod + a[index]) % k;
    int include = 1 + findMaxSubsequence(index + 1, newMod);

    // Trouver la meilleure solution et mémoriser l'indice
    if (include > exclude) {
        memo[index][mod] = include;
        previous[index][mod] = 1;  // 1 signifie qu'on inclut cet élément
    } else {
        memo[index][mod] = exclude;
        previous[index][mod] = 0;  // 0 signifie qu'on exclut cet élément
    }

    return memo[index][mod];
}

// Fonction pour reconstruire la sous-séquence et afficher les indices
void buildSubsequence(int index, int mod, vector<int>& subsequence, vector<int>& indices) {
    while (index < n) {
        if (previous[index][mod] == 1) {  // Si on a inclus cet élément
            subsequence.push_back(a[index]);
            indices.push_back(index + 1);  // On ajoute l'indice (+1 pour base 1)
            mod = (mod + a[index]) % k;  // Mettre à jour le mod
        }
        index++;  // Passer à l'élément suivant
    }
}

int main() {
    ifstream inFile("INPDIVSEQ.txt");
    ofstream outFile("OUTDIVSEQ.txt");

    inFile >> n >> k;
    a.resize(n);
    memo.assign(n, vector<int>(k, -1));  // Initialise le tableau de mémoïsation
    previous.assign(n, vector<int>(k, -1));  // Pour reconstruire la séquence

    for (int i = 0; i < n; ++i) {
        inFile >> a[i];
    }

    // Appeler la fonction récursive
    int maxLength = findMaxSubsequence(0, 0);

    // Sortie : La longueur de la sous-séquence
    outFile << maxLength << endl;

    // Reconstruire la sous-séquence et ses indices
    vector<int> subsequence;
    vector<int> indices;
    buildSubsequence(0, 0, subsequence, indices);

    // Sortie : Les éléments de la sous-séquence avec indices
    for (int i = indices.size() - 1; i >= 0; --i) {
        outFile << "a[" << indices[i] << "] = " << subsequence[i] << endl;
    }

    // Sortie : La somme de la sous-séquence
    int sum = 0;
    for (int elem : subsequence) {
        sum += elem;
    }
    outFile << "Sum = " << sum << endl;

    return 0;
}
