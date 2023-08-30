#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;
using minuto = int;
using costo = int;

const int INF = 1e9;

int n;
vector<minuto> minutos;
vector<costo> descontentos;
vector<bool> parciales_corregidos;

/// @param i iterador de parciales
/// @param mins contador de minutos
/// @param corregidos cantidad de parciales corregidos
/// @return el minimo desconteto
int minimo_descontento(int i, int mins, int corregidos) {
    // Caso base: corrigió todo
    if (corregidos == n) return 0;
    
    // Si paso del ultimo parcial puede que no haya corregido los primeros entocnes vuelve a empezar
    if (i == n and corregidos > 0) return minimo_descontento(0, mins, corregidos);

    // Si paso del ultimo parcial y no corrigio ninguno tenemos que cortar el bucle
    if (i == n and corregidos == 0) return INF;

    // Pasar al siguiente parcial
    int pasar = minimo_descontento(i + 1, mins, corregidos);
    int corregir = INF;

    // Si no corrigio el parcial lo corrige
    if (not parciales_corregidos[i]) {
        parciales_corregidos[i] = true;
        corregir = descontentos[i] * (mins + minutos[i]) + minimo_descontento(i + 1, mins + minutos[i], corregidos + 1);
        parciales_corregidos[i] = false;
    }

    return min(pasar, corregir);
}

int main() {
    int c = 1; //cin >> c;
    while(c--) {
        //cin >> n;
        n = 3;
        int i = n;

        minutos              = vector<minuto>(n);
        descontentos         = vector<costo>(n);
        parciales_corregidos = vector<bool>(n, false);

        while(i < n) {
            int e; cin >> e;
            minutos[i] = e;
            i++;
        }

        i = n;
        while(i < n) {
            int e; cin >> e;
            descontentos[i] = e;
            i++;
        }

        minutos[0] = 1;
        minutos[1] = 2;
        minutos[2] = 3;

        descontentos[0] = 2;
        descontentos[1] = 2;
        descontentos[2] = 2;

        int descontento = minimo_descontento(0, 0, 0);

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