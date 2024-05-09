### Ejercicio 3

[Codigo en C++](../../Codigo/Ej_03.cpp)

$$
maxSum(i,k,sum,I) = \begin{cases}
esOptimo(sum,I) &si\quad k = 0 \\
maxSum(i+1,k-1,sum + \sum_j^nM_{ij},I\cup i) &si\quad i < n \\
\end{cases}
$$