#include<iostream>
#include<vector>

using namespace std;
using costo = pair<int, int>;

const int INF = 1e6;

vector<vector<costo> > memo;
vector<int> B;
int c;

// Backtracking
costo min_exceso(int i, int j, int q) {
    if (j <= 0) return make_pair(-j + c, q);
    if (i == B.size() and j > 0) return make_pair(INF, INF);
    return min(min_exceso(i + 1, j - B[i], q + 1), min_exceso(i + 1, j, q));
}

// Top-Down
costo min_exceso_td(int i, int j, int q) {
    if (j <= 0) return make_pair(0,0);
    if (i == B.size() and j > 0) return make_pair(INF, INF);
    if (memo[i][j].second == -1) {
        costo gasto = min_exceso_td(i + 1, j - B[i], q + 1);
        costo nuevo_gasto = make_pair(B[i] + gasto.first, 1 + gasto.second);
        memo[i][j] = min(nuevo_gasto, min_exceso_td(i + 1, j, q));
    }
    return memo[i][j];
}

// Bottom-Up
costo min_exceso_bu(int c) {
    int n = B.size();
    vector<vector<costo> > M(n+1, vector<costo>(c+1, make_pair(INF, INF)));

    M[0][0] = make_pair(0,0);

    for(int i = 1; i <= n; i++) {
        for(int j = c; j >= 0; j--) {
            costo gasto = M[i - 1][max(0, j - B[i])];
            costo nuevo_gasto = make_pair(B[i] + gasto.first, 1 + gasto.second);
            M[i][j] = min(nuevo_gasto, M[i - 1][j]);
        }
    }
    return M[n][c];
}

int main() {
    int n; cin >> n >> c;

    memo = vector<vector<costo> >(n+1, vector<costo>(c+1, make_pair(0,-1)));

    while(n--) {
        int e; cin >> e;
        B.push_back(e);
    }

    cout << " --- Backtracking --- " << endl;

    costo gasto = min_exceso(0, c, 0);

    cout << "Suma: " << gasto.first << endl;

    cout << "Cantidad: " << gasto.second << endl;

    cout << " --- Top Down --- " << endl;

    gasto = min_exceso_td(0, c, 0);

    cout << "Suma: " << gasto.first << endl;

    cout << "Cantidad: " << gasto.second << endl;

    cout << " --- Bottom Up --- " << endl;

    gasto = min_exceso_bu(c);

    cout << "Suma: " << gasto.first << endl;

    cout << "Cantidad: " << gasto.second << endl;
}

/*
6 14
2 3 5 10 20 20
*/