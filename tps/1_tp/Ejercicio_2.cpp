#include<iostream>
#include<vector>

using namespace std;

int n, min_d;
vector<int> minutos;
vector<int> descontento;

int minimo_descontento(int i, int m) {
    if (i == n) return 0;
    return min(minimo_descontento(i + 1, m + 1), minimo_descontento(i + 1, m + 1));
}

int main() {
    int c; cin >> c;
    while(c--) {
        cin >> n;
        int i = 0;

        while(i < 2*n) {
            int e; cin >> e;
            if(i < n) minutos.push_back(e);
            else descontento.push_back(e);
            i++;
        }
    }
}

/*
1
3
1 2 3
2 2 2
*/