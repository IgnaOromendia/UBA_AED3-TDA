### Ejercicio 4

[Codigo en C++](../../Codigo/Ej_04.cpp)

En este caso $S$ es un "conjunto ordenado" y $\min^*$ es una función que dados dos conjuntos los evalúa y devuelve los conjuntos.

$$
f_D(i, S) = \begin{cases} 
S & \text{si } i = n \\
\min_{j=i+1\dots n}^*(f(i+1, S\cup\{D_j\})) & \text{cc}
\end{cases}
$$