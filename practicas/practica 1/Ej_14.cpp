#include<vector>
#include<iostream>
#include<queue>

using namespace std;

int n;
vector<int> numeros;
priority_queue<int> heap;

// O(n log n)
int costo_minimo() {
    int costo = 0; 

    int prim = heap.top(); heap.pop();
    int seg = heap.top(); heap.pop();

    costo = prim + seg;

    while(not heap.empty()) {
        int num1 = heap.top(); heap.pop();
        int nuevo_costo = costo + num1;
        costo += nuevo_costo;
    }

    return -costo;
}

int main() {
    cin >> n;
    int i = 0;

    // O(n log n)
    while(i < n){
        int e; cin >> e;
        heap.push(-e);
        i++;
    }

    int costo = costo_minimo();

    cout << "El costo minimo de sumar los numeros es " << costo << endl;


}