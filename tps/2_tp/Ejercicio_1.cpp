#include<vector>
#include<iostream>

using namespace std;

/* 
-- Estrategia 1 --
n = 10^3
m = 2*10^3
Complejidad: O(nm + m^2)
Operaciones: 2*10^6 + 4*10^6 = 6*10^6 < 10^9
Por cada arista:
    Eliminarla del grafo m_i
    Verificar si el grafo tiene puentes
    Si es verdadero, agregar la arista m_i a la lista de importantes
*/