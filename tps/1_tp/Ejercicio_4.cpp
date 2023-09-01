#include<iostream>
#include<vector>

using namespace std;

const int INF = 1e9;

int n, cant_prov;
vector<int> puestos;
vector<int> proveedurias;

// O(nk)
int costo() {
    int suma = 0;
    for(int i = 0; i < n; i++) {
        int min = INF;
        for(int j = 0; j < cant_prov; j++) {
            int dist = abs(puestos[i] - proveedurias[j]);
            if (dist < min) min = dist;
        }
        suma += min;
    }
    return suma;
}

int min_costo(int i, int k) {
    if (i <= n and k == 0)  return costo();
    if (i == n and k > 0)   return INF;
    
    proveedurias[k-1] = puestos[i];
    int poner =   min_costo(i + 1, k - 1);

    proveedurias[k-1] = INF;
    int saltear = min_costo(i + 1, k);

    if (poner < saltear) proveedurias[k-1] = puestos[i];
    
    return min(poner, saltear);
}

int main() {
    int c;cin >> c;
    while(c--) {
        cin >> n >> cant_prov;

        puestos      = vector<int>(n);
        proveedurias = vector<int>(cant_prov);
        
        int i = 0;
        while(i < n) {
            int e; cin >> e;
            puestos[i] = e;
            i++;
        }

        int costo = min_costo(0,cant_prov);
        
        cout << costo << endl;
        for(int j = cant_prov - 1; j >= 0; j--) cout << proveedurias[j] << " ";
        cout << endl;
    }
}

/*
3
4 2
1 5 15 20
5 1
4 5 6 7 8
4 1
4 5 6 7
*/