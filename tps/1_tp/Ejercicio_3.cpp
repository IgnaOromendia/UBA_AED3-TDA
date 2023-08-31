#include<iostream>
#include<vector>

using namespace std;

// Constantes

const char POSITIVO = '+';
const char NEGATIVO = '-';
const char INDETERMINADO = '?'; 

// Variables Globales
int n, saldo_final;
vector<int> cuentas;
vector<char> resultado;
vector<vector<int> > memo;

bool detectar_cuentas(int i, int s, vector<char>& signos) {
    // Caso base
    if (i == n ) {
        if (s == saldo_final) resultado = signos;
        return s == saldo_final;
    }

    if (memo[i][s] == -1) {
        signos[i] = POSITIVO;
        bool sumando = detectar_cuentas(i + 1, s + cuentas[i], signos);

        signos[i] = NEGATIVO;
        bool restando = detectar_cuentas(i + 1, s - cuentas[i], signos);
    
        signos[i] = ' ';

        memo[i][s] = sumando or restando;
    }

    return memo[i][s];
}

int main() {
    int c; cin >> c;
    while(c--) {
        cin >> n >> saldo_final;

        memo = vector<vector<int> >(n, vector<int>(saldo_final, -1));
        cuentas = vector<int>(n);
        resultado = vector<char>(n);

        int i = 0;
        while(i < n) {
            int e; cin >> e;
            cuentas[i] = e;
            i++;
        }

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