#include<bits/stdc++.h>

using namespace::std;

int main() {
    cin.tie(0) -> sync_with_stdio(false);
    
    int q;
    if (!(cin >> q)) return 0;
    
    // Mantiene los puntajes registrados ordenados de menor a mayor
    set<long long> scores;
    
    while (q--) {
        int type;
        long long x;
        cin >> type >> x;
        
        if (type == 1) {
            // Registrar el puntaje x
            scores.insert(x);
        } 
        else {
            // Responder cuántos puntajes son estrictamente menores que x
            // lower_bound nos da el primer elemento que es mayor o igual a x
            auto it = scores.lower_bound(x);
            
            // La distancia desde el inicio del set hasta 'it' representa 
            // exactamente la cantidad de elementos menores que x
            int count = distance(scores.begin(), it);
            
            cout << count << '\n';
        }
    }
    
    return 0;
}