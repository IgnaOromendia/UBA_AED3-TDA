#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

struct edge {
    int u;
    int v;
    int cost;
    bool treeEdge = false;
    edge(int u, int v, int c): u(u), v(v), cost(c) {}
};

int n, m;
vector<edge> edges;

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

void kruskal() {
    sort(edges.begin(), edges.end(), [](edge a, edge b) { return a.cost > b.cost; });

    DSU dsu(n+1);

    for(edge &e: edges) {
        if(dsu.find(e.u) != dsu.find(e.v)) {
            dsu.unite(e.u, e.v);
            e.treeEdge = true;
        }
    }
}

int minimum_cost() {
    kruskal();
    int cost = 0;
    for(edge &e: edges)
        if (!e.treeEdge) cost += e.cost;
    return cost;
}

int main() {
    int c; cin >> c;
    while(c--) {
        cin >> n >> m;

        edges.clear();

        while(m--) {
            int u, v, c; cin >> u >> v >> c;
            edges.push_back(edge(u,v,c));
        }

        cout << minimum_cost() << endl;
    }
}