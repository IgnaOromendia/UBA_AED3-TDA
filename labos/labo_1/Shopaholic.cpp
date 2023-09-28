#include<vector>
#include<iostream>
#include<algorithm>

using namespace std;

vector<int> prices;

int maximum_discount(int i) {
    if (i < 0) return 0;
    return prices[i] + maximum_discount(i - 3);
}


int main() {
    int c; cin >> c;
    while(c--) {
        int n; cin >> n;

        prices = vector<int>(n);

        for(int i = 0; i < n; i++) {
            cin >> prices[i];
        }

        sort(prices.begin(), prices.end());

        cout << maximum_discount(prices.size() - 3) << endl;


    }
}
