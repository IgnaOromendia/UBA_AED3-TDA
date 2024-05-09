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
    vector<vector<int> > M(n+1, vector<int>(n+1, -INF));

    for(int i = 0; i <= n; i++){
        M[0][i] = 0;
        M[i][0] = 0;
    }

    for(int j = 1; j <= n; j++) {
        for(int c = 1; c <= j; c++) {
            // Mantengo las misma cantidad de cajas
            int no_operar  = M[j-1][c];

            // Compre hoy (j) entonces el día anterior tenia una caja menos
            int comprar = M[j-1][c - 1] - precios[j - 1];

            // Vendi hoy (j) entonces el día anterior tenia una caja más
            int vender = c < n ? M[j-1][c + 1] + precios[j - 1] : -INF;

            // Busco la máxima ganancia
            M[j][c] = max(vender, max(comprar, no_operar));
        }
    }

    int max = -1;
    for (int i = 0; i <= n; i++) if (max < M[n][i]) max = M[n][i];
    return max;
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