#include<iostream>
#include<vector>

using namespace std;

const int INF = 1e9;
using datos = pair<int,pair<int, int> >;

int n, cant_prov;
vector<int> puestos;
vector<int> proveedurias;
vector<vector<vector<int> > > memo;
vector<vector<vector<datos> > > padres;

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
int costos_intermedios(int d, int h) {
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

    if (memo[i][k][u] == -1) {
        // Pongo la proveeduria en i y calculo los costos entre i y la ultima proveeduria
        if (i == 0) k = -1;
        int poner = costos_intermedios(u, i) + min_costo(i + 1, k + 1, i);
        if (i == 0) k = 0;

        // Salteo la posicion i
        int saltear = i > 0 ? min_costo(i + 1, k, u) : INF;

        // Me quedo con el minimo de poner y saltear
        if(poner <= saltear) {
            memo[i][k][u] = poner;
            if (i == 0) {
                padres[i][k][u] = make_pair(i + 1, make_pair(k, i));
            } else {
                padres[i][k][u] = make_pair(i + 1, make_pair(k + 1, i));
            }
            
        } else {
            memo[i][k][u] = saltear;
            padres[i][k][u] = make_pair(i + 1, make_pair(k, u));
        }
    }

    return memo[i][k][u];
}

void reconstruir_solucion(int i, int k, int u) {
    cout << i << " " << k << " " << u << endl;

    if (proveedurias[k] != -1) return;
    if (padres[i][k][u].first == -1) return;

    int new_i = padres[i][k][u].first;
    int new_k = padres[i][k][u].second.first;
    int new_u = padres[i][k][u].second.second;

    if (k == 0) proveedurias[k] = puestos[new_i];
    else if (proveedurias[k - 1] != new_u) proveedurias[k] = puestos[new_i];
    reconstruir_solucion(new_i, new_k, new_u);
}

int main() {
    int c;cin >> c;
    while(c--) {
        cin >> n >> cant_prov;
        n++;

        puestos      = vector<int>(n);
        proveedurias = vector<int>(cant_prov, -1);

        memo   = vector<vector<vector<int> > >(n, 
                 vector<vector<int> >(cant_prov, 
                 vector<int>(n, -1)));

        padres = vector<vector<vector<datos> > >(n, 
                 vector<vector<datos> >(cant_prov, 
                 vector<datos>(n, make_pair(-1, make_pair(-1, -1)))));
        
        puestos[0] = -INF;

        int i = 1;
        while(i < n) {
            int e; cin >> e;
            puestos[i] = e;
            i++;
        }

        int costo = min_costo(0,0, 0);
        
        for(int k = 0; k < n; k++) {
            for(int j = 0; j < cant_prov; j++) {
                for(int q = 0; q < n; q++) {
                    cout << "padres[" << k << "][" << j << "][" << q << "] = " << padres[k][j][q].first << ", " << padres[k][j][q].second.first << ", " << padres[k][j][q].second.second << endl;
                }
            }
        }

        for(int k = n; k < n; k++) {
            for(int j = 0; j < cant_prov; j++) {
                for(int q = 0; q < n; q++) {
                    cout << "memo[" << k << "][" << j << "][" << q << "] = " << memo[k][j][q] << endl;
                }
            }
        }

        reconstruir_solucion(0,0,0);
        
        cout << costo << endl;
        for(int j = 0; j < cant_prov; j++) cout << proveedurias[j] << " ";
        cout << endl;
    }
}