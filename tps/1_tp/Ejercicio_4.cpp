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
    if (i <= n and k == 0)  return costos_restantes(u);
    if (i == n and k > 0)   return INF;

    if (memo[i][k-1][u+1] == -1) {
        int poner = calcular_costos(u, i) + min_costo(i + 1, k - 1, i);
        int saltear = min_costo(i + 1, k, u);
        memo[i][k-1][u+1] = min(poner, saltear);
    }

    return memo[i][k-1][u+1];
}

void reconstruir_solucion(int i, int k, int u) {
    // TODO
}

int main() {
    int c;cin >> c;
    while(c--) {
        cin >> n >> cant_prov;

        puestos      = vector<int>(n);
        proveedurias = vector<int>(cant_prov);
        memo = vector<vector<vector<int> > >(n, vector<vector<int> >(cant_prov, vector<int>(n+1, -1)));
        
        int i = 0;
        while(i < n) {
            int e; cin >> e;
            puestos[i] = e;
            i++;
        }

        int costo = min_costo(0,cant_prov, -1);

        for(int k = 0; k < n; k++) {
            cout << "i" << endl; 
            for(int j = 0; j < cant_prov; j++) {
                for(int q = 0; q <= n; q++) {
                    cout << memo[k][j][q] << " ";
                }
                cout << endl;
            }
            cout << endl;
        }
        
        cout << costo << endl;
        for(int j = cant_prov - 1; j >= 0; j--) cout << proveedurias[j] << " ";
        cout << endl;
    }
}