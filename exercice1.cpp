#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

int main(){
    ifstream infile("INPMONOSEQ.txt");
    ofstream outfile("OUTMONOSEQ.txt");
    
    int n;
    infile >> n;
    cout << n << endl;
    vector<int> A(n);
    for (int i = 0; i < n; i++) {
        infile >> A[i];
        cout << A[i] << endl;
    }
    return 0;
}