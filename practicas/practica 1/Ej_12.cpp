#include<vector>
#include<iostream>

using namespace std;

vector<vector<int> > memo;
int caras;

// Escenario A (dados distinguibles)

int suma_dados_d(int n, int s) {
    if (s < 0) return 0;
    if(n == 0) return s == 0;
    if (memo[n][s] == -1) {
        int total = 0;
        for(int i = 1; i <= caras; i++) {
            total += suma_dados_d(n - 1, s - i);
        }
        memo[n][s] = total;
    }
    return memo[n][s];
}

// Escenario B (dados indistinguibles)

int suma_dados_i(int n, int s, int k) {

}

int main() {
    int n, s; cin >> n >> caras >> s;
    if (caras * n < s) {
        memo = vector<vector<int> >(n+1, vector<int>(s+1, -1));

        int posibilidades = suma_dados_d(n,s);
        cout << "Posibilidades de sumar " << s << " con " << n << " dados distinguibles de " << caras << " caras es "; 
        cout << posibilidades << endl;

        posibilidades = suma_dados_i(n,s,caras);
        cout << "Posibilidades de sumar " << s << " con " << n << " dados indistinguibles de " << caras << " caras es "; 
        cout << posibilidades << endl;
    } else {
        cout << "No hay solución" << endl;
    }
}