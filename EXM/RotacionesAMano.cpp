#include<bits/stdc++.h>

using namespace::std;

const int N = 200000 + 5;

int root = 1;
int L[N]; // Hijo izquierdo de cada nodo
int R[N]; // Hijo derecho de cada nodo
int P[N]; // Padre de cada nodo

// Función para enlazar el hijo derecho manteniendo el puntero al padre
void add_right_child(int x, int y) {
    R[x] = y;
    if (y > 0) P[y] = x;
}

// Función para enlazar el hijo izquierdo manteniendo el puntero al padre
void add_left_child(int x, int y) {
    L[x] = y;
    if (y > 0) P[y] = x;
}

// Rotación a la izquierda en el nodo x
void rotate_left(int x) {
    int p = P[x];
    int y = R[x];

    add_right_child(x, L[y]);

    if (p > 0) {
        if (L[p] == x) add_left_child(p, y);
        else add_right_child(p, y);
    } else {
        root = y;
        P[y] = 0;
    }

    add_left_child(y, x);
}

// Rotación a la derecha en el nodo x
void rotate_right(int x) {
    int p = P[x];
    int y = L[x];

    add_left_child(x, R[y]);

    if (p > 0) {
        if (L[p] == x) add_left_child(p, y);
        else add_right_child(p, y);
    } else {
        root = y;
        P[y] = 0;
    }

    add_right_child(y, x);
}

int main() {
    cin.tie(0) -> sync_with_stdio(false);

    int n, q;
    cin >> n >> q;

    // Leemos la estructura inicial del árbol y registramos los padres
    for (int i = 1; i <= n; ++i) {
        int left_child, right_child;
        cin >> left_child >> right_child;

        if (left_child > 0) add_left_child(i, left_child);
        if (right_child > 0) add_right_child(i, right_child);
    }

    // Procesamos cada una de las q rotaciones
    while (q--) {
        char op;
        int x;
        cin >> op >> x;

        if (op == 'I') rotate_left(x);
        else rotate_right(x);
    }

    // Imprimimos la raíz final y la estructura de los hijos de cada nodo
    cout << root << '\n';
    for (int i = 1; i <= n; ++i) {
        cout << L[i] << " " << R[i] << '\n';
    }

    return 0;
}