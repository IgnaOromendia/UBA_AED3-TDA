#include<iostream>
#include<string>
#include<vector>

using namespace std;

using long_caminos = pair<int, int>;
using coord = pair<int, int>;

// Constantes
const int INF = 1e9;

const int INICIO = -1;
const int ARRIBA = 0;
const int DERECHA = 1;
const int ABAJO = 2;
const int IZQUIERDA = 3;

const char L = 'L';
const char I = 'I';
const char PLUS = '+';
const char EMPTY = '#';

const string POSIBLE = "POSIBLE";
const string IMPOSIBLE = "IMPOSIBLE";

// Variables Globales

int n, m;
vector<vector<char> > tablero;
vector<vector<bool> > min_track;
vector<vector<bool> > max_track;

bool en_rango(int i, int j) {
    return 0 <= i and i < n and 0 <= j and j < m;
}

coord seguir_derecho(int i, int j, int DIR) {
    if (DIR == ARRIBA)      return make_pair(i + 1, j);
    if (DIR == DERECHA)     return make_pair(i, j - 1);
    if (DIR == IZQUIERDA)   return make_pair(i, j + 1);
    return make_pair(i - 1, j); // Venir desde abajo
}

/**
 * Encuentra el camino minimo en el tablero
 * 
 * @param i iterador de las filas
 * @param j iterador de las columans
 * @param DIR la dirección de donde se llegó a esa posicion
 * @return el camino minimo hasta ese punto
*/
long_caminos encontrar_camino(int i, int j, int DIR) {
    // Caso base llego a la esquina inferior derecha
    if(i == n - 1 and j == m - 1) return make_pair(0, 0);

    // Si se va de rango es invalido
    if(not en_rango(i,j)) return make_pair(INF, -INF); 

    // Si ya pase por esta posicion es un camino invalido
    if(min_track[i][j]) return make_pair(INF, -INF);

    // Si estoy parado en un # es invalido
    if(tablero[i][j] == EMPTY) return make_pair(INF, -INF);

    // Marcamos la posicon por done se pasa
    min_track[i][j] = true;
    max_track[i][j] = true;

    // Si es la posicion inicial puedo elegir
    if (DIR == INICIO) {
        long_caminos bajar = encontrar_camino(i + 1, j, ARRIBA);
        long_caminos derecha = encontrar_camino(i, j + 1, IZQUIERDA);
        min_track[i][j] = false;
        max_track[i][j] = false;
        return make_pair(1 + min(bajar.first, derecha.first), 1 + max(bajar.second, derecha.second));;
    }

    // En caso de que este parado en un I
    if(tablero[i][j] == I) {
        coord c = seguir_derecho(i, j, DIR);
        long_caminos camino = encontrar_camino(c.first, c.second, DIR);
        min_track[i][j] = false;
        max_track[i][j] = false;
        return make_pair(1 + camino.first, 1 + camino.second);
    }
    
    // En caso de que este parado en un L
    if (tablero[i][j] == L) {
        // Si vengo de arriba o abajo puedo ir para la izquierda o derecha
        if (DIR == ARRIBA or DIR == ABAJO) {
            long_caminos der = encontrar_camino(i, j + 1, IZQUIERDA);
            long_caminos izq = encontrar_camino(i, j + 1, IZQUIERDA);
            min_track[i][j] = false;
            max_track[i][j] = false;
            return make_pair(1 + min(der.first, izq.first), 1 + max(der.second, izq.second));
        }  
        
        if (DIR == DERECHA or DIR == IZQUIERDA){ 
            // Si vengo de la derecha o izquierda puedo ir para arriba o para abajo
            long_caminos bajar = encontrar_camino(i + 1, j, ARRIBA);
            long_caminos subir = encontrar_camino(i - 1, j, ABAJO);
            min_track[i][j] = false;
            max_track[i][j] = false;
            return make_pair(1 + min(bajar.first, subir.first), 1 + max(bajar.second, subir.second));
        }
    }

    // En caso de que este parado en un +
    if (tablero[i][j] == PLUS) {
        int min, max;
        long_caminos pasos = make_pair(INF, -INF);

        // Pudeo elegir entre 3 direcciones ya que por donde vengo no puedo volver 

        if (DIR != ARRIBA) pasos = encontrar_camino(i - 1, j, ABAJO);
        min = pasos.first;
        max = pasos.second;

        if (DIR != ABAJO) pasos = encontrar_camino(i + 1, j, ARRIBA);
        if (min > pasos.first) min = pasos.first;
        if (max < pasos.second) max = pasos.second;

        if (DIR != DERECHA) pasos = encontrar_camino(i, j + 1, IZQUIERDA);
        if (min > pasos.first) min = pasos.first;
        if (max < pasos.second) max = pasos.second;

        if (DIR != IZQUIERDA) pasos = encontrar_camino(i, j - 1, DERECHA);
        if (min > pasos.first) min = pasos.first;
        if (max < pasos.second) max = pasos.second;

        min_track[i][j] = false;
        max_track[i][j] = false;

        return make_pair(1 + min, 1 + max);
    }

    min_track[i][j] = false;
    max_track[i][j] = false;

    return make_pair(-1, -1);
}

int main() {
    int c = 1; //cin >> c;

    while(c--) {
        // cin >> n >> m;
        n = 4;
        m = 4;

        tablero = vector<vector<char> >(n, vector<char>(m));
        min_track = vector<vector<bool> >(n, vector<bool>(m, false));
        max_track = vector<vector<bool> >(n, vector<bool>(m, false));

        int i = n;
        int j = 0;

        while(i < n) {
            while(j < m) {
                char e; cin >> e;
                tablero[i][j] = e;
                j++;
            }
            i++;
            j = 0;
        }

        tablero[0][0] = L;
        tablero[0][1] = I;
        tablero[0][2] = PLUS;
        tablero[0][3] = L;

        tablero[1][0] = PLUS;
        tablero[1][1] = PLUS;
        tablero[1][2] = I;
        tablero[1][3] = L;

        tablero[2][0] = I;
        tablero[2][1] = EMPTY;
        tablero[2][2] = PLUS;
        tablero[2][3] = EMPTY;

        tablero[3][0] = L;
        tablero[3][1] = I;
        tablero[3][2] = PLUS;
        tablero[3][3] = PLUS;

        long_caminos camino = encontrar_camino(0, 0, INICIO);

        if (camino.first < INF) cout << POSIBLE << " " << camino.first << " " << camino.second << endl;
        else cout << IMPOSIBLE << endl;
    }
}
/*
3
3 3
ILI
#IL
+L+
2 2
+#
#L
4 4
LI+L
++IL
I#+#
LI++

*/