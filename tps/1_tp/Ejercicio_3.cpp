#include<iostream>
#include<vector>

using namespace std;

// Constantes

const char POSITIVO = '+';
const char NEGATIVO = '-';
const char INDETERMINADO = '?'; 

// Variables Globales
int n, saldo_final, offset;
vector<int> cuentas;
vector<char> resultado;
vector<vector<int> > memo;

/// @param s el saldo actual
/// @return el saldo multiplicado x2 y positivo
int parametrizar(int s) {
    return s < 0 ? -s : s + offset;
}

void asignar_signo(int i, bool s, bool r) {
    if (s and r) 
        resultado[i] = INDETERMINADO;
    else if (s) 
        resultado[i] = POSITIVO;
    else if (r)
        resultado[i] = NEGATIVO;
    else 
        resultado[i] = 'e';
}

void resetar_memo(int s) {
    for(int j = 0; j < n; j++) {
        for(int k = 0; k < s; k++) {
            memo[j][k] = -1;
        }
    }
}

/// @param i numero al cual vamos a sumar o restar
/// @param s suma que va llevando para comparar contra el saldo final
/// @param j indice fijo que indica la cuenta que se quiere fijar la suma o la resta
/// @param b true si se quiere fijar la suma de j o false para fijar la resta
/// @return Si es posible hacer una combinación de sumas y restas para llegar al saldo final
bool detectar_cuentas(int i, int s, int j, bool b) {
    // Caso base
    if (i == n) return s == saldo_final;

    int saldo = parametrizar(s);

    if (memo[i][saldo] == -1) {
        // Forzamos a j para que sume
        if (i == j and b) memo[i][saldo] = detectar_cuentas(i + 1, s + cuentas[i], j, b);
        // Forzamos a j para que reste
        else if (i == j and not b) memo[i][saldo] = detectar_cuentas(i + 1, s - cuentas[i], j, b);
        // Caso contrario
        else memo[i][saldo] = detectar_cuentas(i + 1, s + cuentas[i], j, b) or detectar_cuentas(i + 1, s - cuentas[i], j, b);
    }

    return memo[i][saldo];
}

int main() {
    int c; cin >> c;
    while(c--) {
        cin >> n >> saldo_final;

        // Como todos los xi son multiplos de 100, dividimos todo por 100 para tener numeros más chicos
        saldo_final /= 100;

        cuentas = vector<int>(n);
        resultado = vector<char>(n);

        int param_s = 0;

        int i = 0;
        while(i < n) {
            int e; cin >> e;
            e /= 100;
            cuentas[i] = e;
            param_s += e;
            i++;
        }

        offset = param_s;
        param_s *= 2;

        // O(2wn)
        memo = vector<vector<int> >(n+1, vector<int>(param_s, -1));

        // Probamos todas las posibilidades
        for(int i = 0; i < n; i++) {
            resetar_memo(param_s);

            bool sumando = detectar_cuentas(0,0,i,true);

            resetar_memo(param_s);

            bool restando = detectar_cuentas(0,0,i,false);

            asignar_signo(i, sumando, restando);
        }

        for(int i = 0; i < n; i++) cout << resultado[i];
        cout << endl;

    }
}