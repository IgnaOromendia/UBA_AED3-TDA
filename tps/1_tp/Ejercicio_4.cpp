#include<iostream>
#include<vector>

using namespace std;

const int INF = 1e9;

int n, cant_prov;
vector<int> puestos;
vector<int> proveedurias;
vector<vector<vector<int> > > memo;


/// @param d desde que puesto calcular
/// @return el costo de los puestos que estan adelante de la proveeduria d
int costos_restantes(int d) {
    int suma = 0;
    for(int i = d + 1; i < n; i++) {
        suma += abs(puestos[i] - puestos[d]);
    }
    return suma;
}

/// @param d Desde este puesto
/// @param h Hasta este puesto
/// @return los costos minimos de las distancias de los puestsos entre las proveedurias d y h
int calcular_costos(int d, int h) {
    int suma = 0;
    for(int i = d + 1; i < h; i++) {
        if (d == -1) suma += abs(puestos[i] - puestos[h]);
        else suma += min(abs(puestos[i] - puestos[d]), abs(puestos[i] - puestos[h]));
    }
    return suma;
}

/// @param i el i-esimo puesto
/// @param k la cantidad restante de proveedurias
/// @param u la posicion de la última proveeduria
/// @return el minimo costo de poner las k proveeduras
int min_costo(int i, int k, int u) {
    if (i <= n and k == cant_prov)  return costos_restantes(u);
    if (i == n and k < cant_prov)   return INF;

    int param_u = u;

    if (u == -1) param_u = i;

    if (memo[i][k][param_u] == -1) {
        int poner = calcular_costos(u, i) + min_costo(i + 1, k + 1, i);
        int saltear = min_costo(i + 1, k, u);
        memo[i][k][param_u] = min(poner, saltear);
    }

    return memo[i][k][param_u];
}

void reconstruir_solucion(int i, int k, int u, int costo) {
    if (i == n and k < cant_prov) return;
    if (i <= n and k == cant_prov)
        if (costo - costos_restantes(i) == 0) return;

    int param_u = u;

    if (u == -1) param_u = i;

    if(memo[i][k][param_u] == costo) {
        proveedurias[k] = i;
        int costo_i = calcular_costos(u,i);
        reconstruir_solucion(i + 1, k + 1, i, costo - costo_i);
    } else {
        reconstruir_solucion(i + 1, k, u, costo);
    }
}

int main() {
    int c;cin >> c;
    while(c--) {
        cin >> n >> cant_prov;

        puestos      = vector<int>(n);
        proveedurias = vector<int>(cant_prov);
        memo = vector<vector<vector<int> > >(n, vector<vector<int> >(cant_prov, vector<int>(n, -1)));
        
        int i = 0;
        while(i < n) {
            int e; cin >> e;
            puestos[i] = e;
            i++;
        }

        int costo = min_costo(0,0, -1);

        for(int k = n; k < n; k++) {
            for(int j = 0; j < cant_prov; j++) {
                for(int q = 0; q < n; q++) {
                    cout << "memo[" << k << "][" << j << "][" << q << "] = " << memo[k][j][q] << endl;
                }
            }
        }

        reconstruir_solucion(0,0,-1,costo);
        
        cout << costo << endl;
        for(int j = cant_prov - 1; j >= 0; j--) cout << proveedurias[j] << " ";
        cout << endl;
    }
}