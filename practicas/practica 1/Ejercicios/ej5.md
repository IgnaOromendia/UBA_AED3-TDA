### Ejercicio 5

[Codigo en C++](../../Codigo/Ej_05.cpp)

$$
ss(i,k) = \begin{cases}
1 &si\quad k = 0 \\
0 &si\quad k < 0 \\
ss(i+1, k - c[i]) \lor ss(i+1, k) &cc
\end{cases}
$$

Donde $k$ es la suma buscada e $i$ recorre el conjunto de números posibles $c$