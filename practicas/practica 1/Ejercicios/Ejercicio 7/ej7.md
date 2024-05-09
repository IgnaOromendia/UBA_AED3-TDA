### Ejercicio 7

[Codigo en C++](../../Codigo/Ej_07.cpp)

$$
mgn(c,j) = \begin{cases}
0 &si\quad j = n \land c \geq 0 \\
-\infin &si\quad c < 0 \\
max(-p_j + mgn(c+1,j+1), p_j+ mgn(c-1,j+1), mgn(c,j+1)) &cc
\end{cases}
$$

Donde $c$ es la cantidad de asteroides y $j$ son los días