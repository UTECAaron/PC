#include<bits/stdc++.h>

using namespace::std;

int main() {
    cin.tie(0) -> sync_with_stdio(false);

    int q;
    if (!(cin >> q)) return 0;

    // Usamos multiset porque las lecturas pueden repetirse y deben estar ordenadas
    multiset<long long> readings;

    while (q--) {
        int type;
        cin >> type;

        if (type == 1) {
            long long x;
            cin >> x;
            // Se guarda una lectura con valor x
            readings.insert(x);
        }
        else if (type == 2) {
            long long x;
            cin >> x;
            // Se descarta solo una de las lecturas con valor x (si existe)
            auto it = readings.find(x);
            if (it != readings.end()) {
                readings.erase(it);
            }
        }
        else {
            long long l, r;
            cin >> l >> r;

            // lower_bound encuentra el primer elemento mayor o igual a l
            auto it_l = readings.lower_bound(l);
            // upper_bound encuentra el primer elemento estrictamente mayor que r
            auto it_r = readings.upper_bound(r);

            // La distancia entre ambos iteradores nos da la cantidad de elementos en el rango [l, r]
            int count = distance(it_l, it_r);
            cout << count << '\n';
        }
    }

    return 0;
}