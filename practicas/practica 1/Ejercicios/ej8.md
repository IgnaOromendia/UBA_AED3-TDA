### Ejercicio 8

[Codigo en C++](../../Codigo/Ej_08.cpp)

$$
corte(i,j) = \begin{cases}
0 &si\quad j = i \\
min((\forall q: i \leq q \leq j)(j-i + corte(i,q) + corte(q,j))) &cc
\end{cases}
$$

Donde $i$ y $j$ son los índices del corte