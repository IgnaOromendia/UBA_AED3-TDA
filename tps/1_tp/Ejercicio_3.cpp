#include<iostream>
#include<vector>

using namespace std;

// Constantes

// Variables Globales
int n, saldo_final;
vector<int> cuentas;
vector<char> resultado;
vector<char> signos;
vector<vector<int> > memo;

void detectar_cuentas(int i, int s, vector<char>& signos) {
    // Caso base
    if (i == n and s != saldo_final) return;

    if (i == n and s == saldo_final) {
        for(int i = 0; i < n; i++) resultado[i] = signos[i];
        return;
    }

    signos[i] = '+';
    detectar_cuentas(i + 1, s + cuentas[i], signos);

    signos[i] = '-';
    detectar_cuentas(i + 1, s - cuentas[i], signos);

    signos[i] = ' ';
}

int main() {
    int c; cin >> c;
    while(c--) {
        cin >> n >> saldo_final;

        //memo = vector<vector<int> >(n, vector<int>(saldo_final, -1));
        resultado = vector<char>(n);
        signos = vector<char>(n);
        cuentas = vector<int>(n);

        int i = 0;
        while(i < n) {
            int e; cin >> e;
            cuentas.push_back(e);
            i++;
        }

        detectar_cuentas(0, 0, signos);

        for(int i = 0; i < n; i++) cout << resultado[i];
        cout << endl;

    }
}

/*
2
2 -200
500 700
4 400
500 700 700 100
*/