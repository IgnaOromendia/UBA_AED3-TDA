#include<iostream>
#include<vector>

using namespace std;

int n, m;
vector<int> c1;
vector<int> c2;

int max_parejas() {
    int parejas = 0;
    int i = 0, j = 0;

    while(i < n and j < m){
        if (abs(c1[i] - c2[j]) <= 1) {
            parejas++;
            i++;
            j++;
        } 
        else if (c1[i] < c2[j]) i++;
        else j++;
    }

    return parejas;
}

int main() {
    cin >> n >> m;
    int i = 0;

    while(i < n) {
        int e;cin >> e;
        c1.push_back(e);
        i++;
    }

    i = 0;
    while(i < m) {
        int e;cin >> e;
        c2.push_back(e);
        i++;
    }

    int parejas = max_parejas();

    cout << "Máxima cantidad de parejas: " << parejas << endl;
}