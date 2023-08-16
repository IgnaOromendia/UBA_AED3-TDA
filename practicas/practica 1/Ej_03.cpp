#include<vector>
#include<iostream>

using namespace std;

int n;
vector<vector<int> > M;
vector<int> I;
int max_sum = -1;

void max_mat_sum(int k, int i, int sum, vector<int>& indices) {
    if (k == 0) {
        if(sum > max_sum) {
            I = indices;
            max_sum = sum;
        }
    } else if (i < M.size()){
        indices.push_back(i+1);
        int new_sum = 0;
        for(int j = 0; j < indices.size(); j++) new_sum += M[i][indices[j]-1];
        new_sum *= 2;
        max_mat_sum(k - 1, i + 1, sum + new_sum, indices);
        indices.pop_back();
        max_mat_sum(k, i + 1, sum, indices);
    }
}

int main() {
    int k;
    cin >> n >> k;

    vector<int> indices;
    indices.reserve(k);
    int copy = n;

    while(n--) {
        vector<int> fila;
        int i = 0;
        while(i < copy) {
            int e; cin >> e;
            fila.push_back(e);
            i++;
        }
        M.push_back(fila);
    }

    max_mat_sum(k, 0, 0, indices);
    cout << max_sum << endl;

    for(int i = 0; i < I.size(); i++) cout << I[i] << " ";
    cout << endl;

}

/*
4 3            
0 0 10 1
0 0 5 2
10 5 0 1
1 2 1 0
*/