#include<iostream>
#include<vector>

using namespace std;

#define INF 1e9
#define IMP "IMPOSIBLE"
#define POS "POSIBLE"

int n;
vector<vector<int> > distancia;
vector<vector<int> > velocidad;

bool armar_red() {
    for(int k = 1; k <= n; k++) {
        for(int i = 1; i <= n; i++) {
            for(int j = 1; j <= n; j++) {
                if (k == i or k == j or i == j) continue;
                if (velocidad[i][j] < velocidad[i][k] + velocidad[k][j]) {
                    if (distancia[i][j] == 0) distancia[i][j] = distancia[j][i] = 1;
                    //cout << "d(" << i << "," << j << "): " << velocidad[i][j] << " < d(" << i << "," << k << "): " << velocidad[i][k] << " + d(" << k << "," << j << "): " << velocidad[k][j] << endl;
                } else if (velocidad[i][j] == velocidad[i][k] + velocidad[k][j]) {
                    //cout << "d(" << i << "," << j << "): " << velocidad[i][j] << " = d(" << i << "," << k << "): " << velocidad[i][k] << " + d(" << k << "," << j << "): " << velocidad[k][j] << endl;
                    distancia[i][j] = distancia[j][i] =  distancia[j][i] + 1;
                }
                else return false;
            }
        }
    }
    return true;
}

int main() {
    int c; cin >> c;
    while(c--) {
        cin >> n;

        distancia.assign(n+1, vector<int>(n+1, 0));
        velocidad.assign(n+1, vector<int>(n+1, INF));

        for(int i = 1; i <= n; i++) velocidad[i][i] = 0;

        int i = 2, j = 1;
        while(i <= n) {
            int vel; cin >> vel;
            velocidad[i][j] = velocidad[j][i] = vel;
            j++;
            if (i == j) {i++;j=1;}
        }

        for(int i = n+1; i <= n; i++) {
            for(int j = 1; j <= n; j++) {
                cout << velocidad[i][j] << " ";
            }
            cout << endl;
        }

        if (!armar_red()) {
            cout << IMP << endl;
        } else {
            cout << POS << endl;
            for(int i = 1; i <= n; i++) {
                for(int j = 1; j <= n; j++) {
                    cout << distancia[i][j] << " ";
                }
                cout << endl;
            }
        }
    }
}
