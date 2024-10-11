#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>

using namespace std;

struct Subsequence {
    int length;  // Longueur de la sous-séquence
    int parent;  // Indice du précédent élément dans la sous-séquence
    int sum_mod; // Somme mod k
};

vector<int> findDivisibleSubsequence(const vector<int>& A, int n, int k) {
    vector<vector<Subsequence>> dp(n + 1, vector<Subsequence>(k, {-1, -1, 0}));
    
    dp[0][0] = {0, -1, 0};  // Initialisation: la somme modulo k de 0 peut être atteinte avec 0 éléments
    
    // Calcul dynamique
    for (int i = 1; i <= n; ++i) {
        for (int r = 0; r < k; ++r) {
            // Ne pas inclure l'élément A[i-1]
            dp[i][r] = dp[i-1][r];
        }
        for (int r = 0; r < k; ++r) {
            if (dp[i-1][r].length != -1) {
                int new_r = (r + A[i-1]) % k;
                if (dp[i][new_r].length < dp[i-1][r].length + 1) {
                    dp[i][new_r] = {dp[i-1][r].length + 1, i - 1, new_r};
                }
            }
        }
    }
    for (int r = 0; r<k; r++){
        for (int i=0; i <n; i++){
            
            cout << "{" << dp[i][r].length << ", " << dp[i][r].parent << ", " << dp[i][r].sum_mod << "},\t ";
        }
        cout << endl;
    }
    // Trouver la sous-séquence ayant une somme modulo k égale à 0
    vector<int> result;
    int current_r = 0;
    int current_i = n;
    
    // Reconstruction de la sous-séquence
    while (current_i > 0 && dp[current_i][current_r].parent != -1) {
        int parent_idx = dp[current_i][current_r].parent;
        result.push_back(parent_idx + 1); // Ajoute 1 pour un indice 1-based
        int element_value = A[parent_idx];
        
        current_r = (current_r - element_value % k + k) % k;
        current_i = parent_idx;
    }
    
    // On renverse le résultat pour avoir les indices dans le bon ordre
    reverse(result.begin(), result.end());
    return result;
}

int main() {
    ifstream infile("INPDIVSEQ.txt");
    ofstream outfile("OUTDIVSEQ.txt");
    
    int n, k;
    infile >> n >> k;
    vector<int> A(n);
    
    for (int i = 0; i < n; ++i) {
        infile >> A[i];
    }
    
    vector<int> result_indices = findDivisibleSubsequence(A, n, k);
    
    // Écriture de la longueur de la sous-séquence dans le fichier de sortie
    outfile << result_indices.size() << endl;
    
    // Écriture des éléments de la sous-séquence dans le fichier de sortie
    int total_sum = 0;
    for (int idx : result_indices) {
        outfile << "a[" << idx << "] = " << A[idx - 1] << endl;
        total_sum += A[idx - 1];
    }
    
    // Écriture de la somme des éléments dans le fichier de sortie
    outfile << "Sum = " << total_sum << endl;
    
    infile.close();
    outfile.close();
    
    return 0;
}
