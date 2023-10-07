#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

struct edge {
    int u;
    int v;
    long long d;
    long long r;
    double costo;
    bool es_treeEdge = false;
    edge(int u, int v, long long d, long long r): u(u), v(v), d(d), r(r) {}
    void aplicar_costo(double c) { costo = (d - (c * r)); }
};

int n, m;

vector<edge> edges;
long long suma_distancias = 0, suma_repetidores = 0;

struct DSU {
    vector<int> p;
    vector<int> rank;

    DSU(int n){
        p = vector<int>(n, -1);
        rank = vector<int>(n, 1);
    }

    void unite(int u, int v){
        int c1, c2;
        c1 = find(u); c2 = find(v);
        if(c1 == c2) return;
        if(rank[c2] > rank[c1]) swap(c1, c2);
        p[c2] = c1;
        rank[c1] = max(rank[c1], rank[c2]+1);
    }
    
    int find(int u){
        if(p[u] == -1) return u;
        int rep = find(p[u]);
        p[u] = rep;
        return rep;
    }

};

void kruskal(double c) {
    suma_distancias = suma_repetidores = 0;
    for(edge &e: edges) {
        e.aplicar_costo(c);
        e.es_treeEdge = false;
    }

    sort(edges.begin(), edges.end(), [](edge a, edge b) { return a.costo > b.costo; });

    DSU dsu(n);

    for(edge &e: edges) {
        if(dsu.find(e.u) != dsu.find(e.v)) {
            dsu.unite(e.u, e.v);
            e.es_treeEdge = true;
            suma_distancias += e.d;
            suma_repetidores += e.r;
        }
    }
}

double calcular_costo(double c) {
    double suma = 0;
    for(edge &e: edges) {
        if (e.es_treeEdge) suma += e.costo;
    }        
    return suma;
}

void buscar_costo_optimo() {
    double limite_inferior = 0;
    double limite_superior = 10e6;
    int cantidad_refinamiento = 60;

    while(cantidad_refinamiento--) {
        double c_medio = (limite_inferior + limite_superior) / 2;

        kruskal(c_medio);

        // Si el w(T) es mayor a 0 quiero probar con un c más grande
        if (calcular_costo(c_medio) >= 0) {
            limite_inferior = c_medio;
        } else {
            // Si no lo achicamos
            limite_superior = c_medio;
        }
    }
}

int main() {
    int c; cin >> c;
    while(c--) {
        cin >> n >> m;

        edges.clear();

        while(m--) {
            int u, v;
            long long d, r; 
            cin >> u >> v >> d >> r;
            edges.push_back(edge(u-1,v-1,d,r));
        }
        
        buscar_costo_optimo();

        cout << suma_distancias << " " << suma_repetidores << endl;

    }
}