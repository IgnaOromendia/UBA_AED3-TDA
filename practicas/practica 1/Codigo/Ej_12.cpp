#include<vector>
#include<iostream>

using namespace std;

vector<vector<int> > memo_d;
vector<vector<vector<int> > > memo_i;
int caras;

// Escenario A (dados distinguibles)

int suma_dados_d(int n, int s) {
    if (s < 0) return 0;
    if(n == 0) return s == 0;
    if (memo_d[n][s] == -1) {
        int total = 0;

        for(int i = 1; i <= caras; i++) 
            total += suma_dados_d(n - 1, s - i);

        memo_d[n][s] = total;
    }
    return memo_d[n][s];
}

// Escenario B (dados indistinguibles)

int suma_dados_i(int n, int s, int k) {
    // Si s es negativo es invalido
    if (s < 0) return 0;

    // Si no quedan más dados tenemos que chequear la suma
    if (n == 0) return s == 0;

    // Chequea memoria
    if (memo_i[n][s][k] == -1) {
        int total = 0;
        for(int i = 0; i < n; i++) {
            total += suma_dados_i(n - i, s - (k * i), k - 1);
        }
        memo_i[n][s][k] = total;
    }
    
    return memo_i[n][s][k];
}

int main() {
   //int n, s; cin >> n >> caras >> s;
   int n = 3;
   int s = 6;
   caras = 4;
    if (caras * n > s) {
        memo_d = vector<vector<int> >(n+1, vector<int>(s+1, -1));
        memo_i = vector<vector<vector<int> > >(n+1, vector<vector<int> >(s+1, vector<int>(caras+1, -1)));

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