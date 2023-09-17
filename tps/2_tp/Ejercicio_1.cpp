#include<vector>
#include<iostream>
#include<algorithm>

using namespace std;
using arista = pair<int, int>;

/* 
n = 10^3
m = 2*10^3
-- Estrategia 1 --
Complejidad lista de ady: O(m log m + m(2n + 2m))
--
Operaciones: 
2*10^3 * log (2*10^3) + 2*10^3 * (2*10^3 + 2*10^3) = 
2*10^3 * log (2*10^3) + 8*10^6 = 
2*10^3 * (log(2) + 3log(10)) + 8*10^6 =
2*10^3 + 8*10^6 ≈ 8*10^6
--
Algoritmo:             
Ordenamos las aristas por output
Por cada arista
        Eliminar la arista
        Verificar si el grafo tiene puentes
        Si es verdadero, agregar la arista a la lista de importantes
*/

// Constantes
const int NO_LO_VI       = -1;
const int EMPECE_A_VER   = 0;
const int TERMINE_DE_VER = 1;

// Variabels globales
int n, m;
vector<int> back_edges_con_extremo_inferior_en;
vector<int> back_edges_con_extremo_superior_en;

vector<vector<int> > tree_edges;
vector<vector<int> > lista_adyacencia;

vector<arista> lista_arista;
vector<arista> importantes;

vector<int> memo;
vector<int> estado;

arista arista_marcada;

// Complejidad: O(n + m)
void inicializar_variables() {
    tree_edges       = vector<vector<int> >(n, vector<int>());
    estado           = vector<int>(n, NO_LO_VI);
    memo             = vector<int>(n, -1);

    back_edges_con_extremo_inferior_en = vector<int>(n, 0);
    back_edges_con_extremo_superior_en = vector<int>(n, 0);
}

// Complejidad: O(n + m)
void dfs(int v, int padre = -1) {
    estado[v] = EMPECE_A_VER;

    for(int u: lista_adyacencia[v]) {
        if (make_pair(u,v) == arista_marcada or make_pair(v,u) == arista_marcada) continue;

        if (estado[u] == NO_LO_VI) {
            tree_edges[v].push_back(u);
            dfs(u, v);
        } else if (u != padre and estado[u] == EMPECE_A_VER) {
            back_edges_con_extremo_inferior_en[v]++;
            back_edges_con_extremo_superior_en[u]++;
        }
    }

    estado[v] = TERMINE_DE_VER;
}

// Complejidad: O(n + m)
int cubren(int v, int p = -1) {
    if (memo[v] != -1) return memo[v];
    int res = 0;
    for (int hijo : tree_edges[v])
        if (hijo != p) res += cubren(hijo, v);

    res -= back_edges_con_extremo_superior_en[v];
    res += back_edges_con_extremo_inferior_en[v];
    
    return memo[v] = res; 
}

// Complejidad: O(n + m)
bool tiene_puentes() {
    int componentes = 0, puentes = 0;
    for(int i = 0; i < n; i++) {
        if (estado[i] == NO_LO_VI) {
            dfs(i);
            componentes++;
        }
    }

    for(int i = 0; i < n; i++)
        if(cubren(i) == 0) puentes++;

    return puentes - componentes > 0;
}

// Complejidad: O(m(n + m))
void marcar_importantes() {
    for(int i = 0; i < m; i++) {
        // Marcamos la arista para "eliminarla"
        arista_marcada = lista_arista[i];

        // Inicializamos las variables
        inicializar_variables(); // O(n + m)

        // Si tiene puentes, agregar la arista m_i a la lista de importantes
        if (tiene_puentes()) importantes.push_back(arista_marcada); // O(n + m)
    }
}

int main() {
    int c; cin >> c;
    while(c--) {
        cin >> n >> m;

        lista_arista     = vector<arista>(m);
        lista_adyacencia = vector<vector<int> >(n, vector<int>());

        for(int i = 0; i < m; i++) {
            int u, v; cin >> u >> v;
            lista_adyacencia[u].push_back(v);
            lista_adyacencia[v].push_back(u);
            lista_arista[i] = u < v ? make_pair(u,v) : make_pair(v,u);
        }

        // Ordenamos las aristas O(m log m)
        sort(lista_arista.begin(), lista_arista.end());

        // Marcamos las aristas importantes O(m(n + m))
        marcar_importantes();

        // Mostramos los importantes
        cout << importantes.size() << endl;
        for(int i = 0; i < importantes.size(); i++)
            cout << importantes[i].first << " " << importantes[i].second << endl;

        // Limpiamos la lista
        importantes.clear();
    }
}