#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;
using minuto = int;
using costo = int;
using parcial = pair<minuto, costo>;

const int INF = 1e9;

int n;
vector<parcial> parciales;
vector<minuto> minutos;
vector<costo> descontentos;

int minimo_descontento(int i, int m, int c) {
    if (i == n and c != n) return INF;
    if (i == n) return 0;
    int corregir = parciales[i].second * (m + parciales[i].first) + minimo_descontento(i + 1, m + parciales[i].first, c + 1);
    int siguiente = minimo_descontento(i + 1, m, c);
    return min(corregir, siguiente);
}

bool comp(parcial p1, parcial p2) {
    return p1.second > p2.second;
}

int main() {
    int c; cin >> c;
    while(c--) {
        cin >> n;
        int i = 0;

        minutos      = vector<minuto>(n);
        descontentos = vector<costo>(n);
        parciales    = vector<parcial>(n);

        while(i < n) {
            int e; cin >> e;
            minutos[i] = e;
            i++;
        }

        i = 0;
        while(i < n) {
            int e; cin >> e;
            descontentos[i] = e;
            i++;
        }

        i = 0;
        while(i < n) {
            //cout << minutos[i] << "-" << descontentos[i] << endl;
            parciales[i] = make_pair(minutos[i], descontentos[i]);
            i++;
        }

        sort(parciales.begin(), parciales.end(), comp);

        int descontento = minimo_descontento(0,0,0);

        cout << descontento << endl;
    }
}

/*
2
3
1 2 3
2 2 2
4
2 1 3 2
1 2 2 3
*/