#include<bits/stdc++.h>

using namespace::std;

int main() {
    cin.tie(0) -> sync_with_stdio(false);
    
    int q;
    if (!(cin >> q)) return 0;
    
    // Usamos multiset para permitir precios repetidos y mantenerlos ordenados
    multiset<long long> prices;
    
    while (q--) {
        int type;
        cin >> type;
        
        if (type == 1) {
            long long x;
            cin >> x;
            // Llega un producto de precio x
            prices.insert(x);
        } 
        else if (type == 2) {
            long long x;
            cin >> x;
            // Se vende solo uno de los productos con precio x (si existe)
            auto it = prices.find(x);
            if (it != prices.end()) {
                prices.erase(it);
            }
        } 
        else {
            long long l, r;
            cin >> l >> r;
            
            // Delimitamos el rango con lower_bound y upper_bound
            auto it_l = prices.lower_bound(l);
            auto it_r = prices.upper_bound(r);
            
            long long total_sum = 0;
            // Recorremos los elementos en el rango [l, r] sumando sus precios
            // Usamos long long para evitar desbordamientos en la suma
            for (auto it = it_l; it != it_r; ++it) {
                total_sum += *it;
            }
            
            cout << total_sum << '\n';
        }
    }
    
    return 0;
}