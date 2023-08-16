#include<vector>
#include<iostream>
#include<string>

using namespace std;

vector<vector<int> > memo;

// O(nk) temporal y espacial

bool subset_sum_td(vector<int>& C, int i, int j) {
    if(j < 0) return false;
    if(i == 0) return j == 0;
    if (memo[i][j] == -1) memo[i][j] = subset_sum_td(C,i-1,j) or subset_sum_td(C,i-1,j - C[i]);
    return memo[i][j];
}

// O(nk) temporal y espacial

bool subset_sum_bu(vector<int>& C, int k) {
    int n = C.size();
    vector<vector<bool> > M(n+1, vector<bool>(k+1));
    for(int j = 0; j < k+1; j++) M[0][j] = j == 0;

    for (int i = 1; i <= n; i++) {
        for(int j = 1; j <= k; j++) {
            M[i][j] = M[i - 1][j] or (j - C[i] >= 0 and M[i - 1][j - C[i]]);
        }
    }
    return M[n][k];
}

// O(nk) temporal y O(k) espacial

bool subset_sum_bu_opt(vector<int>& C, int k) {
    int n = C.size();
    vector<bool> M(k+1);
    M[0] = true;
    for(int i = 0; i < n; i++) {
        for (int j = 0; j <= k; j++) {
            M[j] = M[j] or (j - C[i] >= 0 and M[j - C[i]]);
        }
    }
    return M[k];
}

int main(){ 
    int n, k; cin >> n >> k;

    memo = vector<vector<int> >(n+1,vector<int>(k+1,-1));

    vector<int> C;
    while(n--) {
        int e; cin >> e;
        C.push_back(e);
    }

    string anwser_bu = subset_sum_bu(C, k) ? "True" : "False";
    string anwser_bu_opt = subset_sum_bu_opt(C, k) ? "True" : "False";
    string anwser_td = subset_sum_td(C, C.size(), k) ? "True" : "False";
    

    cout << "Top Down: " << anwser_td << endl;
    cout << "Bottom Up: " << anwser_bu << endl;
    cout << "Bottom Up Optimizado: " << anwser_bu_opt << endl;
}