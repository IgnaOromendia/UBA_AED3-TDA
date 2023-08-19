#include<vector>
#include<iostream>

using namespace std;

const int INF = 1e9;

vector<vector<int> > A;
vector<vector<int> > memo;
int N, M;

// Backtracking
int min_vida(int i, int j) {
    if (i == N and j == M) return 1;
    if (i < 0 or i > N or j < 0 or j > N) return INF;
    else
        return max(1, min(min_vida(i+1,j), min_vida(i, j+1)) - A[i][j]); 
}

// Top down
int min_vida_td(int i, int j) {
    if (i == N and j == M) return 1;
    if (i < 0 or i > N or j < 0 or j > N) return INF;
    if (memo[i][j] == -1) memo[i][j] = max(1, min(min_vida_td(i+1,j), min_vida_td(i, j+1)) - A[i][j]); 
    return memo[i][j];
}

// Bottom up
int min_vida_bu() {
    vector<vector<int> > Mem(N+1, vector<int>(M+1, -1));

    return Mem[N][M];
}


int main() {
    int n, m; cin >> n >> m;

    memo = vector<vector<int> >(n, vector<int>(m,-1));
    N = n - 1;
    M = m - 1;

    while(n--){
        vector<int> fila;
        int i = 0;
        while (i < m) {
            int e; cin >> e;
            fila.push_back(e);
            i++;
        }
        A.push_back(fila);
    }

    int vida_inicial = min_vida_td(0,0);

    cout << "Vida inicial: " << vida_inicial << endl;

}

/*
3 3 -2 -3 3 -5 -10 1 10 30 -5
*/