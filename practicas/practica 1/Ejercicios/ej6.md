### Ejercicio 6

[Codigo en C++](../../Codigo/Ej_06.cpp)

$$
cc(i,s,q) = \begin{cases}
(c - s,q) &si\quad c \leq s \\
(\infin, \infin) &si\quad i > n \\
min(cc(i+1,s+B_i,q+1), cc(i+1,s,q) ) &cc
\end{cases}
$$

Donde $s$ es la suma de billetes y $q$ es la cantidad de billetes usados