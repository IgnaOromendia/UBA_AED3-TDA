### Ejercicio 2

[Codigo en C++](../../Codigo/Ej_02.cpp)

$$
contadorMagico(i,j,S,P) = \begin{cases}
esCuadradoMagico(S) &si\quad i = n \land j = n \\
(\forall x\in P)(contadorMagico(i+1,0,S_{ij} = x, P \setminus x)) &si\quad i \neq n \land j = n \\
(\forall x\in P)(contadorMagico(i,j+1,S_{ij} = x, P \setminus x))  &cc
\end{cases}
$$

$esCuadradoMagico$ recibe un cuadrado y verifica que sea un `cuadrado mágico` devolviendo 1 si lo es. Luego en cada cada caso si no estamos parados en la última casilla agregamos en la posición $ij$ un número de $P$. Este último contiene los número de 1 a n.