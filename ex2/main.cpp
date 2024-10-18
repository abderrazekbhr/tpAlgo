#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>

using namespace std;

int main()
{
    // Lecture du fichier d'entrée
    ifstream infile("INPDIVSEQ.TXT");
    int n, k;
    infile >> n >> k;

    vector<int> a(n);
    for (int i = 0; i < n; ++i)
    {
        infile >> a[i];
    }
    infile.close();

    // Table DP pour stocker la longueur maximale de sous-séquence pour chaque reste [0, k-1]
    vector<int> dp(k, -1);
    dp[0] = 0; // Le reste 0 a une sous-séquence de longueur 0 au début

    vector<vector<int>> subsequences(k); // Stocke les éléments de sous-séquences pour chaque reste
    vector<vector<int>> indices(k);      // Stocke les indices des éléments pour chaque sous-séquence

    // Traitement de chaque élément dans le tableau
    for (int i = 0; i < n; ++i)
    {
        vector<int> new_dp(dp);
        vector<vector<int>> new_subsequences(subsequences);
        vector<vector<int>> new_indices(indices);

        for (int j = 0; j < k; ++j)
        {
            if (dp[j] != -1)
            { // Considère seulement les sous-séquences valides
                int new_remainder = (j + a[i]) % k;
                if (new_dp[new_remainder] < dp[j] + 1)
                {
                    new_dp[new_remainder] = dp[j] + 1;
                    new_subsequences[new_remainder] = subsequences[j];
                    new_subsequences[new_remainder].push_back(a[i]);
                    new_indices[new_remainder] = indices[j];
                    new_indices[new_remainder].push_back(i + 1); // Stocke l'indice (1-indexé)
                }
            }
        }

        // Considère le démarrage d'une nouvelle sous-séquence avec l'élément courant
        int current_remainder = a[i] % k;
        if (new_dp[current_remainder] < 1)
        {
            new_dp[current_remainder] = 1;
            new_subsequences[current_remainder] = {a[i]};
            new_indices[current_remainder] = {i + 1}; // 1-indexé
        }

        dp = new_dp;
        subsequences = new_subsequences;
        indices = new_indices;
    }

    // Le résultat est la sous-séquence avec un reste de 0
    ofstream outfile("OUTDIVSEQ.TXT");
    outfile << dp[0] << endl; // La longueur de la plus longue sous-séquence

    int sum = 0;
    for (size_t i = 0; i < subsequences[0].size(); ++i)
    {
        outfile << "a[" << indices[0][i] << "]=" << subsequences[0][i] << endl;
        sum += subsequences[0][i];
    }
    outfile << "Sum = " << sum << endl; // La somme des éléments
    outfile.close();

    return 0;
}
