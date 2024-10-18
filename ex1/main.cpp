#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>

using namespace std;

vector<int> findLIS(vector<int> A, int n){
    vector<int> dp(n, 1), parent(n, -1);
    
    // Computing the length of LIS
    for (int i = 1; i < n; ++i) {
        for (int j = 0; j < i; ++j) {
            if (A[j] < A[i] && dp[i] < dp[j] + 1) {
                dp[i] = dp[j] + 1;
                parent[i] = j;
            }
        }
    }
    
    // Finding the maximum length and its indice
    int lis_length = 0, lis_end_index = 0;
    for (int i = 0; i < n; ++i) {
        if (dp[i] > lis_length) {
            lis_length = dp[i];
            lis_end_index = i;
        }
    }
    
    // Rebuilding of the subsequence
    vector<int> lis_indices;
    for (int i = lis_end_index; i != -1; i = parent[i]) {
        lis_indices.push_back(i);  // Garder les indices 0-based
    }
    
    // Reversing indices to get the growing list
    reverse(lis_indices.begin(), lis_indices.end());
    
    return lis_indices;
}

int main(){
    ifstream infile("INPMONOSEQ.txt");
    ofstream outfile("OUTMONOSEQ.txt");
    
    int n;
    infile >> n;
    vector<int> A(n);
    
    for (int i = 0; i < n; i++) {
        infile >> A[i];
    }

    vector<int> result_index = findLIS(A, n);

    // Écriture de la longueur de la LIS
    outfile << result_index.size() << endl;
    
    // Écriture des éléments de la séquence et leurs indices
    for (int i = 0; i < result_index.size(); i++) { 
        int idx = result_index[i];  // Indice 0-based
        outfile << "a[" << (idx + 1) << "] = " << A[idx] << endl;  // idx + 1 pour 1-based
    }

    infile.close();
    outfile.close();
    return 0;
}
