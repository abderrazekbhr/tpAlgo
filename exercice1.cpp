#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

vector<int> findLIS(vector<int> A, int n){
    vector<int> dp(n, 1), parent(n, -1);
    
    // Calcul de la longueur de LIS
    for (int i = 1; i < n; ++i) {
        for (int j = 0; j < i; ++j) {
            if (A[j] < A[i] && dp[i] < dp[j] + 1) {
                dp[i] = dp[j] + 1;
                parent[i] = j;
            }
        }
    }
    
    // Trouver la longueur maximale et son indice
    int lis_length = 0, lis_end_index = 0;
    for (int i = 0; i < n; ++i) {
        if (dp[i] > lis_length) {
            lis_length = dp[i];
            lis_end_index = i;
        }
    }
    
    // Reconstruction de la sous-séquence
    vector<int> lis_sequence;
    vector<int> lis_indices;
    for (int i = lis_end_index; i != -1; i = parent[i]) {
        lis_sequence.push_back(A[i]);
        lis_indices.push_back(i + 1);  // Ajoute 1 pour les indices 1-based
    }
    
    // Affichage dans l'ordre croissant
    // reverse(lis_sequence.begin(), lis_sequence.end());
    // reverse(lis_indices.begin(), lis_indices.end());
    
    // Sortie
    return lis_indices;
}

int main(){
    ifstream infile("INPMONOSEQ.txt");
    ofstream outfile("OUTMONOSEQ.txt");
    
    int n;
    infile >> n;
    cout << n << endl;
    vector<int> A(n);
    for (int i = 1; i < n; i++) {
        infile >> A[i];
    }

    vector<int> result_index = findLIS(A, n);

    outfile << result_index.size() << endl;
    for (int i :result_index) {
        outfile << i << " (Index: " << A[i] << ")" << endl;
    }
    infile.close();
    outfile.close();
    return 0;
}