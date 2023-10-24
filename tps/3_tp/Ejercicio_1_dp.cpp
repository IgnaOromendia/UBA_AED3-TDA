#include<iostream>
#include<vector>

using namespace std;

#define INF 1e9

int n, m;
vector<vector<int> > adj, memo;
vector<int> dist;

int rescatar(int v, int k) {
    if (v == n) return 0;

    if (k > 3) return INF;

    if (memo[v][k] == -1) {
        int d = INF;
        for(int u: adj[v]) {
            if (u != v+1) 
                d = min(d, 2 + rescatar(u, k + 1)); // Tomar pasadizo
            else 
                d = min(d, 1 + rescatar(u, k));     // Pasar a la siguiente pared
        }
        memo[v][k] = d;
    }

    return memo[v][k];
}

int main() {
    int c; cin >> c; 
    while(c--) {
        cin >> n >> m;

        adj.assign(n, vector<int>());
        memo.assign(n+1, vector<int>(4,-1));
        dist.assign(n+1, INF);
        
        // Conectamos al i-esimo con el i+1-esimo
        for(int i = 0; i < n; i++) {
            adj[i].push_back(i+1);
        }

        while(m--) {
            int v,u; cin >> v >> u;
            adj[v].push_back(u);
        }

        cout << rescatar(0,0) << endl;


        for(int i = 0; i < n; i++) {
            cout << i << ": ";
            for(int j = 0; j < 4; j++) {
                cout << memo[i][j] << " ";
            }
            cout << endl;
        }

    }
}