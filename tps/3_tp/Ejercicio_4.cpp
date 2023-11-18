#include<iostream>
#include<vector>
#include<queue>

using namespace std;

const int INF = 1e9;

int s = 0, t, x, n;
vector<vector<int> > red, capacity, capacity_og;

void print_red() {
    for(int i = 1; i < n; i++) {
        cout << i << ": ";
        for(int v: red[i]) {
            cout << "(" << v << ", " << capacity[i][v] << ") ";
        }
        cout << endl;
    }
}

int bfs(int s, int t, vector<int>& parent) {
    fill(parent.begin(), parent.end(), -1);
    parent[s] = -2;
    queue<pair<int, int> > q;
    q.push(make_pair(s, INF));

    while (!q.empty()) {
        int cur = q.front().first;
        int flow = q.front().second;
        q.pop();

        for (int next : red[cur]) {
            if (parent[next] == -1 && capacity[cur][next]) {
                parent[next] = cur;
                int new_flow = min(flow, capacity[cur][next]);
                if (next == t)
                    return new_flow;
                q.push(make_pair(next, new_flow));
            }
        }
    }

    return 0;
}

int maxflow(int s, int t) {
    int flow = 0;
    vector<int> parent(n);
    int new_flow;

    while (new_flow = bfs(s, t, parent)) {
        flow += new_flow;
        int cur = t;
        while (cur != s) {
            int prev = parent[cur];
            capacity[prev][cur] -= new_flow;
            capacity[cur][prev] += new_flow;
            cur = prev;
        }
    }

    return flow;
}

void ajustar_capacidades(int c) {
    if (c == 0) return;
    capacity[s][1] = x;
    for(int v = 1; v < n; v++) {
        for(int u: red[v]) {
            if (capacity_og[v][u] == 0) continue;
            capacity[v][u] = capacity_og[v][u] / c;
            capacity[u][v] = 0;
        }
    }
}

long long herramientas(long long salida_taller) {
    int lower = 0;
    int upper = salida_taller;

    // c representa la cantidad de herramientas por persona
    // x representa la cantidad de personas
    while(upper - lower > 1) {
        long long c = (lower + upper) / 2;

        ajustar_capacidades(c);

        long long new_flow = c == 0 ? 0 : maxflow(s,t);
        
        if (new_flow >= x) {
            lower = c;
        } else {
            upper = c;
        }
    }

    if (upper == 0) return 0;
    ajustar_capacidades(upper);
    long long upper_flow = maxflow(s,t);

    if (upper_flow >= x) return upper * x;

    return lower * x;
}


int main() {
    int c; cin >> c;
    while (c--) {
        int m;
        cin >> n >> m >> x;

        t = n; 
        n++;

        red.assign(n, vector<int>());
        capacity_og.assign(n, vector<int>(n,0));
        capacity.assign(n, vector<int>(n,0));

        long long max_salida_taller = 0;

        red[s].push_back(1);
        red[1].push_back(s);
        capacity_og[s][1] = x;

        while(m--) {
            int v,w,h; cin >> v >> w >> h;
            red[v].push_back(w);
            red[w].push_back(v);
            capacity_og[v][w] = h;
            max_salida_taller += h;
        }

        cout << herramientas(max_salida_taller) << endl;
    }
}