#include<iostream>
#include<vector>

using namespace std;

#define oil_deposit '@'
#define empty '*'

int n, m;

vector<bool> visited;
vector<vector<int> > adj;
vector<vector<char> > grid;

void dfs(int v) {
    visited[v] = true;
    for(int u: adj[v]) {
        if(!visited[u]) dfs(u);
    }
}

int oil_regions() {
    int count = 0;

    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            int v = (i * m) + j;
            if (!visited[v] and grid[i][j] == oil_deposit) {
                count++;
                dfs(v);
            }
        }
    }

    return count;
}

int main() {
    while(true) {
        cin >> n >> m;

        if (n+m == 0) break;
        
        grid.assign(n, vector<char>(m));
        adj.assign(n*m, vector<int>());
        visited.assign(n*m, false);

        for(int i = 0; i < n; i++) {
            for(int j = 0; j < m; j++) {
                char c; cin >> c;
                grid[i][j] = c;
            }
        }

        for(int i = 0; i < n; i++) {
            for(int j = 0; j < m; j++) {
                if (grid[i][j] == empty) continue;
                int v = (i * m) + j;

                // Up
                if (i > 0 and grid[i-1][j] == oil_deposit) adj[v].push_back(v-m);

                // Down
                if (i < n - 1 and grid[i+1][j] == oil_deposit) adj[v].push_back(v+m);

                // Right
                if (j < m - 1 and grid[i][j+1] == oil_deposit) adj[v].push_back(v+1);

                // Left
                if (j > 0 and grid[i][j-1] == oil_deposit) adj[v].push_back(v-1);

                // Diagonal Left Up
                if (j > 0 and i > 0 and grid[i-1][j-1] == oil_deposit) adj[v].push_back(v-1-m);

                // Diagonal Left Down
                if (j > 0 and i < n-1 and grid[i+1][j-1] == oil_deposit) adj[v].push_back(v-1+m);

                // Diagonal Right Up
                if (j < m-1 and i > 0 and grid[i-1][j+1] == oil_deposit) adj[v].push_back(v+1-m);

                // Diagonal Righ Down
                if (j < m-1 and i < n-1 and grid[i+1][j+1] == oil_deposit) adj[v].push_back(v+1+m);
            }
        }

        cout << oil_regions() << endl;
    }
}