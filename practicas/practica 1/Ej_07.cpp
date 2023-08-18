#include<vector>
#include<iostream>

using namespace std;

const int INF = 1e9;

vector<int> precios;
vector<vector<int> > memo;

// Top Down
// j = dias
// c = cantidad de asteroides
int mgn(int j, int c) {
    if (c < 0 or c > j) return -INF;
    if (j == 0) return 0;
    if (memo[j - 1][c] == -1) {
        int no_operar  = mgn(j - 1, c);
        int comprar    = mgn(j - 1, c - 1) - precios[j - 1];
        int vender     = mgn(j - 1, c + 1) + precios[j - 1];
        memo[j - 1][c] = max(vender, max(comprar, no_operar));
    }
    return memo[j - 1][c];
}

// Bottom Up
int mgn_bu(){
    int n = precios.size();
    vector<vector<int> > M(n+1, vector<int>(n+1, -1));

    M[0][0] = 0;

    for(int j = 1; j <= n; j++) {
        for(int c = j; c > 0; c--) {
            int no_operar  = M[j-1][c];
            int comprar    = M[j-1][c - 1] - precios[j - 1];
            int vender     = M[j-1][c + 1] + precios[j - 1];
            M[j][c]        = max(vender, max(comprar, no_operar));
        }
    }

    return M[n][n];
}

int main() {
    int n; cin >> n;

    memo = vector<vector<int> >(n+1, vector<int>(n+1, -1));

    while(n--) {
        int e; cin >> e;
        precios.push_back(e);
    }

    int maxima_ganancia_neta = mgn(precios.size(), 0);

    cout << "Máxima ganacia neta (Top Down): " << maxima_ganancia_neta << endl;

    maxima_ganancia_neta = mgn_bu();

    cout << "Máxima ganacia neta (Bottom Up): " << maxima_ganancia_neta << endl;

}