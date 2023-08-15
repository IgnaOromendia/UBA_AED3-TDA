#include<vector>
#include<string>
#include<iostream>
#include<math.h>

using namespace std;

int numero_magico, n;
vector<int> numeros;

bool esDiagonal1(int i, int j) {return i == j;}

bool esDiagonal2(int i, int j) {return j == n - i - 1;}

bool chequeoSumas(int suma, int indice) {
    return ((indice < n-1 && suma < numero_magico) or (indice == n-1 && suma == numero_magico));
}

bool chequeoDiagonales(int i, int j, int sumaD1, int sumaD2) {
    if (esDiagonal1(i,j)) return chequeoSumas(sumaD1, j);
    if (esDiagonal2(i,j)) return chequeoSumas(sumaD2, i);
    return true;
}

pair<int,int> avanzar(int i, int j){
    if (i < n and j < n-1) return make_pair(i,j+1);
    if (i == n-1 and j == n-1) return make_pair(n,n);
    return make_pair(i+1,0);
}

int cant_cuardados_magicos(int i, int j, vector<int>& sumaFila, vector<int>& sumaColumna, int sumaDiagonal1, int sumaDiagonal2) {
    // Ultima pos en fila
    if (j == n - 1 and numeros[numero_magico - sumaFila[i] - 1] == 1) return 0;

    // Ultima pos en columna
    if (i == n - 1 and numeros[numero_magico - sumaColumna[i] - 1] == 1) return 0;

    // Ultima pos en diagonal 1
    if (i == n - 1 and j == n - 1 and numeros[numero_magico - sumaDiagonal1 - 1]) return 0;

    // Ultima pos en diagonal 1
    if (i == n - 1 and j == 0 and numeros[numero_magico - sumaDiagonal2 - 1]) return 0;

    if (i == n and j == n) return 1;

    int contador = 0;

    for(int elem = 1; elem <= numeros.size(); elem++) {
        if (numeros[elem - 1] == 1) continue;

        numeros[elem - 1] = 1;

        sumaFila[i] += elem;
        sumaColumna[j] += elem;
        sumaDiagonal1 += elem * int(esDiagonal1(i,j));
        sumaDiagonal2 += elem * int(esDiagonal2(i,j));

        if (chequeoSumas(sumaFila[i],j) and 
            chequeoSumas(sumaColumna[j],i) and
            chequeoDiagonales(i, j, sumaDiagonal1, sumaDiagonal2)) {
            
            pair<int, int> coord = avanzar(i,j);

            contador += cant_cuardados_magicos(coord.first, coord.second, sumaFila, sumaColumna, sumaDiagonal1, sumaDiagonal2);
        }

        numeros[elem - 1] = 0;
        sumaFila[i] -= elem;
        sumaColumna[j] -= elem;
        sumaDiagonal1 -= elem * int(esDiagonal1(i,j));
        sumaDiagonal2 -= elem * int(esDiagonal2(i,j));
    }

    return contador;
}

int main() {
    // <- Generar n
    n = 3;

    numero_magico = (int(pow(n,3)) + n) / 2;
    numeros = vector<int>(n*n,0);
    vector<int> sumaF = vector<int>(n,0);
    vector<int> sumaC = vector<int>(n,0);

    int cant = cant_cuardados_magicos(0, 0, sumaF, sumaC, 0, 0);

    cout << cant << endl;
}