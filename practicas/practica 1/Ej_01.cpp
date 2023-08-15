#include<vector>
#include<iostream>
#include<string>

using namespace std;

int k;
vector<int> C;

bool subset_sum(int i, int j, int total_sum) {
    if (total_sum < j) return false;
    if (j < 0) return false;
    if (i == 0) {
        return j == 0;
    } else {
        return subset_sum(i - 1, j, total_sum - C[i]) or subset_sum(i - 1, j - C[i], total_sum - C[i]);
    }
}

int main() {
    // <- Generar C
    C.push_back(6);
    C.push_back(12);
    C.push_back(6);
    // <- Generar k
    k = 12;

    int total_sum = 0;
    for(int i = 0; i < C.size(); i++) total_sum += C[i];

    string anwser = subset_sum(C.size(), k, total_sum) ? "True" : "False";

    cout << anwser << endl;
}