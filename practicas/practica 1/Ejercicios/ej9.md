### Ejercicio 9

[Codigo en C++](../../Codigo/Ej_09.cpp)

$$
\text{minVida}(i,j) = \begin{cases}
1 &si\quad i = N \land j = M \\
\infin &si\quad fueraDeRango(i,j) \\
\max(1, \min(\text{minVida}(i+1,j), \text{minVida}(i,j+1)) - A_{ij})&cc
\end{cases}
$$

Donde $i$ y $j$ son los índices del terreno $A$