#include<vector>
#include<iostream>

using namespace std;

const int INF = 1e6;

vector<vector<int> > memo;
vector<bool> cortes;

// Top Down
int corte(int i, int j) {
    if (i+1 == j) return 0;
    if(memo[i][j] == -1) {
        int costo = cortes.size();
        for(int q = i + 1; q < j; q++) {
            costo = min(costo, corte(i,q) + corte(q,j));
        }
        memo[i][j] = j - i + costo;
    }
    return memo[i][j];
}

// Bottom Up
int corte_bu(int l) {
    vector<vector<int> > M(l+1, vector<int>(l+1,l));

    M[0][0] = 0;

    for(int i = 1; i < l; i++) {
        for (int j = 1; j < l; j++) {
            int costo = cortes.size();
            for(int q = i + 1; q < j; q++) {
                costo = min(costo, M[i][q] + M[q][j]);
            }
            M[i][j] = j - i + costo;
        }
    }

    return M[l][l];
}

int main() {
    int l, c; cin >> l >> c;

    cortes = vector<bool>(l,false);
    memo = vector<vector<int> >(l+1, vector<int>(l+1, -1));

    while(c--) {
        int e; cin >> e;
        cortes[e] = true;
    }

    int coste = corte(0,l);

    cout << "Coste de los cortes (TD): " << coste << endl;

    coste = corte_bu(l);

    cout << "Coste de los cortes (BU): " << coste << endl;



}