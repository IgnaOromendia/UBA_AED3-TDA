#include<vector>
#include<iostream>
#include<math.h>

using namespace std;

vector<vector<int> > memo;
vector<int> numeros;
int w;

bool operaciones(int i, int x) {
    if (i == numeros.size()) return x == w;
    if (memo[i][x] == -1) {
        memo[i][x] = operaciones(i + 1, x + numeros[i]) or
                     operaciones(i + 1, x * numeros[i]) or
                     operaciones(i + 1, pow(x,numeros[i]));
    } 
    return memo[i][x];
}

int main() {
    int n; cin >> n >> w;

    memo = vector<vector<int> >(n+1, vector<int>(w+1, -1));

    while(n--) {
        int e; cin >> e;
        numeros.push_back(e);
    }

    bool op = operaciones(0,0);

    cout << (op ? "True" : "False") << endl;
}