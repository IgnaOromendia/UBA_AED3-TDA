#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

const long long m = 1000000007LL;

struct parcial {
    long long mins;
    long long descontento;
    double coeficiente;
};

int n;
vector<parcial> parciales;

long long mod(long long x) {
    long long modulo = x % m;
    return modulo < 0 ? modulo + m : modulo;
}

bool comp(parcial p1, parcial p2) {
    return p1.coeficiente > p2.coeficiente;
}

/// @return el minimo desconteto
int minimo_descontento() {
    sort(parciales.begin(), parciales.end(), comp);

    long long descontento = 0;
    int minutos = 0;

    for(int i = 0; i < n; i++) {
        minutos += parciales[i].mins;
        long long nuevo_descontento = mod(mod(parciales[i].descontento) * minutos);
        descontento = mod(descontento + nuevo_descontento);
    }

    return descontento;
}

int main() {
    int c ;cin >> c;
    while(c--) {
        cin >> n;
        int i = 0;

        parciales = vector<parcial>(n);

        while(i < n) {
            long long e; cin >> e;
            parciales[i].mins = e;
            i++;
        }

        i = 0;
        while(i < n) {
            long long e; cin >> e;
            parciales[i].descontento = e;
            parciales[i].coeficiente = e / double(parciales[i].mins);
            i++;
        }

        int descontento = minimo_descontento();

        cout << descontento << endl;
    }
}