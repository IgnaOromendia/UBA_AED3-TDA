#include<iostream>
#include<vector>
#include<queue>

using namespace std;

#define PL "Permanently Locked"

int n = 10000, m;
int initial_state, combination, amount_buttons;

vector<int> buttons, dist;
vector<vector<int> > adj;

void bfs(int v) {
    queue<int> q;
    vector<bool> visited(n, false);

    visited[v] = true;
    dist[v] = 0;
    q.push(v);

    while(!q.empty()) {
        int u = q.front(); q.pop();

        for(int w: adj[u]) {
            if(!visited[w]) {
                visited[w] = true;
                dist[w] = dist[u] + 1;
                q.push(w);
            }
        }
    }
}

int main() {
    int c = 1;
    while(true) {
        cin >> initial_state >> combination >> amount_buttons;

        if (initial_state + combination + amount_buttons == 0) break;

        adj.assign(n, vector<int>());
        dist.assign(n, -1);
        buttons.clear();

        while(amount_buttons--) {
            int b; cin >> b;
            buttons.push_back(b);
        }

        for(int b: buttons) {
            for(int v = 0; v < n; v++) {
                int next_node = (v + b) % n;
                adj[v].push_back(next_node);
            }
        }

        for(int i = n+1; i <= n; i++) {
            cout << i << ": ";
            for(int j = 0; j < adj[i].size(); j++) {
                cout << adj[i][j] << " ";
            }
            cout << endl;
        }

        bfs(initial_state);

        if (dist[combination] < 1) cout << "Case " << c << ": " << PL << endl;
        else cout << "Case " << c << ": " << dist[combination] << endl;

        c++;
    }
}