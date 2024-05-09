#include<vector>
#include<iostream>

using namespace std;

struct Caja {
    Caja(int p, int s, int m): peso(p), soportando(s), max_soporte(m) {}
    int peso;
    int soportando;
    int max_soporte;
};

const int INF = 1e9;

vector<int> pesos;
vector<int> soportes;
vector<Caja> resultado;
vector<vector<int> > memo;

bool validar(vector<Caja>& pila) {
    for(int i = 0; i < pila.size(); i++) {
        if (pila[i].max_soporte < pila[i].soportando) return false;
    }
    return true;
}

bool actualizar_soportes(vector<Caja>& pila, int nuevo_peso, bool suma) {
    bool valido = true;
    for(int i = 0; i < pila.size(); i++) {
        if (suma) pila[i].soportando += nuevo_peso;
        else pila[i].soportando -= nuevo_peso;

        if (pila[i].soportando > pila[i].max_soporte) valido = false;
    }
    return valido;
}

// Backtracking O(2^n)
int max_cajas_bt(int i, vector<Caja>& pila) {
    if (not validar(pila)) return -INF;

    if (i == pesos.size() and validar(pila)) {
        if (resultado.empty()) for(int i = 0; i < pila.size(); i++) resultado.push_back(pila[i]);
        return pila.size();
    }
    
    Caja c = Caja(pesos[i],0,soportes[i]);

    bool valido = actualizar_soportes(pila,c.peso,true);
    int agregar = -INF;

    if (valido) {
        pila.push_back(c);
        agregar = max_cajas_bt(i+1, pila);
        pila.pop_back();
        actualizar_soportes(pila,c.peso,false);
    }

    int no_agregar = max_cajas_bt(i+1, pila);

    return max(agregar, no_agregar);
}

// Top Down O(n^2)
int max_cajas_td(int i, vector<Caja>& pila) {
    if (not validar(pila)) return -INF;

    if (i == pesos.size() and validar(pila)) {
        if (resultado.empty()) for(int i = 0; i < pila.size(); i++) resultado.push_back(pila[i]);
        return pila.size();
    }

    if (memo[i][pila.size()] == -1) {
        Caja c = Caja(pesos[i],0,soportes[i]);

        bool valido = actualizar_soportes(pila,c.peso,true);
        int agregar = -INF;

        if (valido) {
            pila.push_back(c);
            agregar = max_cajas_bt(i+1, pila);
            pila.pop_back();
            actualizar_soportes(pila,c.peso,false);
        }

        int no_agregar = max_cajas_bt(i+1, pila);
        memo[i][pila.size()] = max(agregar, no_agregar);
    }

    return memo[i][pila.size()];
}

int max_cajas_bu() {return 0;}

int main() {
    int n;cin >> n;
    int i = 0;

    memo = vector<vector<int> >(n+1, vector<int>(n+1,-1));

    while(i < 2*n) {
        int e;cin >> e;
        if (i < n) pesos.push_back(e);
        else soportes.push_back(e);
        i++;
    }

    vector<Caja> pila;

    int cajas = max_cajas_td(0, pila);

    cout << cajas << endl;

    for(int i = 0; i < resultado.size(); i++) cout << "(" << resultado[i].peso << ", " << resultado[i].soportando << ", " << resultado[i].max_soporte << ")"<< " ";
    cout << endl;
}

/* 
5
19 7 5 6 1
15 13 7 8 2
*/