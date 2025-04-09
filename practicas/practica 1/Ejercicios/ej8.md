### Ejercicio 8

[Codigo en C++](../../Codigo/Ej_08.cpp)

$$
corte(i,j) = \begin{cases}
0 &si\quad j = i \\
\min_{q=i\dots j}(j-i + corte(i,q) + corte(q,j)) &cc
\end{cases}
$$

Donde $i$ y $j$ son los índices del corte