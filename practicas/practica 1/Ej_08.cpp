#include<vector>
#include<iostream>

using namespace std;

const int INF = 1e6;

vector<vector<int> > memo;
vector<bool> cortes;

// Top Down
int min_costo(int i, int j) {
    if (i+1 == j) return 0;
    if (memo[i][j] == -1) {
        int costo = cortes.size(); // corte más largo
        bool hay_corte = false;
        for(int q = i + 1; q < j; q++) {
            // En caso de que el las posicion sea de un corte caluclo el minimo
            if (cortes[q]) {
                costo = min(costo, min_costo(i, q) + min_costo(q, j));
                hay_corte = true;
            }
        }
        if (hay_corte) memo[i][j] = costo + j - i;
        else memo[i][j] = 0;
    }
    return memo[i][j];
}

// Bottom Up

int min_costo_bu(int l) {
    vector<vector<int> > M(l+1, vector<int>(l+1, -1));

    // Hacer un corte sin longitud
    M[0][0] = 0;

    for (int i = 0; i <= l; i++) {
        for(int j = i; j <= l; j++) {
            
        }
    }

}


int main() {
    int l, c; cin >> l >> c;

    cortes = vector<bool>(l,false);
    memo = vector<vector<int> >(l+1, vector<int>(l+1, -1));

    while(c--) {
        int e; cin >> e;
        cortes[e] = true;
    }

    int coste = min_costo(0,l);

    cout << "Coste de los cortes (TD): " << coste << endl;

    /*coste = corte_bu(l);

    cout << "Coste de los cortes (BU): " << coste << endl;*/



}