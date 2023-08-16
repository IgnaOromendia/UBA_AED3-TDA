#include<vector>
#include<iostream>

using namespace std;

int n;
vector<vector<int> > M;
vector<int> I;
vector<int> maxs_fila;
int max_sum = -1;

int suma(vector<int>& indices, int i) {
    int res = 0;
    for(int j = 0; j < indices.size(); j++) res += M[i][indices[j]-1];
    return res *= 2;
}

void max_mat_sum(int k, int i, int sum, vector<int>& indices, int max_alcanzable) {
    if (k == 0) {
        if(sum > max_sum) {
            I = indices;
            max_sum = sum;
        }
    } else if (i < M.size()){
        if (max_alcanzable > max_sum) {
            indices.push_back(i+1);
            int new_sum = suma(indices, i);

            max_mat_sum(k - 1, i + 1, sum + new_sum, indices, max_alcanzable - maxs_fila[i]);
            indices.pop_back();
            max_mat_sum(k, i + 1, sum, indices, max_alcanzable - maxs_fila[i]);

        }
    }
}

int max_vector_sim(vector<int>& v, int j) {
    int m = 0;
    for(int i = j; i < v.size(); i++) {
        if (v[i] > m) m = v[i];
    }
    maxs_fila.push_back(m);
    return m;
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

    int max_alcanzable = 0;
    for(int i = 0; i < M.size(); i++) {
        int max_fila = max_vector_sim(M[i], i+1);
        max_alcanzable += max_fila;
    }

    max_mat_sum(k, 0, 0, indices, max_alcanzable);

    cout << "Maximo: " << max_sum << endl;

    cout << "I = { ";

    for(int i = 0; i < I.size(); i++) cout << I[i] << " ";
    cout << "}" << endl;

}

/*
4 3            
0 10 10 1
10 0 5 2
10 5 0 1
1 2 1 0
*/