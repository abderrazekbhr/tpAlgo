#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

void findLIS(vector<int> A, int n,const ofstream outfile){
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
    outfile << lis_length << endl;
    for (int i = 0; i < lis_length; ++i) {
        outfile << lis_sequence[i] << " (Index: " << lis_indices[i] << ")" << endl;
    }
}

int main(){
    ifstream infile("INPMONOSEQ.txt");
    ofstream outfile("OUTMONOSEQ.txt");
    
    int n;
    infile >> n;
    cout << n << endl;
    vector<int> A(n);
    for (int i = 0; i < n; i++) {
        infile >> A[i];
    }

    findLIS(A, n, outfile);

    infile.close();
    outfile.close();
    return 0;
}