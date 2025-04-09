### Ejercicio 3

[Codigo en C++](../../Codigo/Ej_03.cpp) (diferente a la recursión)

$$
\text{maxSum}(i,k,I) = \begin{cases}
I &si\quad k = 0 \\
\max(\text{maxsum}(i+1,k-1, I \cup i), \text{maxsum}(i+1,k, I)) &si\quad i < n \\
\end{cases}
$$

El $\max(I,I')$ se traduce a $\max(\sum_{j\in I}^nM_{ij}, \sum_{j\in I'}^nM_{ij})$ devolviendo el conjunto que maximice la usma