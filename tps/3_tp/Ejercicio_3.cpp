#include<iostream>
#include<vector>

using namespace std;

int n; 
vector<bool> marcado;
vector<vector<int> > red;

int main() {
    int c; cin >> c;
    while(c--) {
        cin >> n;

        marcado.assign(n*n, false);
        red.assign(2*n*n, vector<int>());

        // Marcamos los que son inaccesibles
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < n; j++) {
                int indice = (n * i) + j;
                int v; cin >> v;
                marcado[indice] = v;
            }
        }

        // Agrego la red
        for(int i = 0; i < n*n; i++) {

        }
    }
}