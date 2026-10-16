#include<bits/stdc++.h>

using namespace::std;

int main() {
    cin.tie(0) -> sync_with_stdio(false);
    
    int q;
    if (!(cin >> q)) return 0;
    
    // Mantiene los códigos de los libros ordenados de menor a mayor
    set<long long> books;
    
    while (q--) {
        int t;
        long long y;
        cin >> t >> y;
        
        if (t == 1) {
            // Llega un nuevo libro con código x (y)
            books.insert(y);
        } 
        else if (t == 2) {
            // Sale prestado el libro con código x (y)
            books.erase(y);
        } 
        else {
            // Buscar el k-ésimo menor código (donde k = y)
            // Como k está 1-indexado, avanzamos k-1 posiciones desde el inicio
            auto it = books.begin();
            advance(it, y - 1);
            
            cout << *it << '\n';
        }
    }
    
    return 0;
}