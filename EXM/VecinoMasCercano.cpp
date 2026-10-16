#include<bits/stdc++.h>

using namespace::std;

int main() {
    cin.tie(0) -> sync_with_stdio(false);

    int q;
    if (!(cin >> q)) return 0;

    set<long long> stations; // Almacena los kilómetros con estaciones de forma ordenada

    while (q--) {
        int type;
        long long x;
        cin >> type >> x;

        if (type == 1) {
            // Inaugurar estación en el kilómetro x
            stations.insert(x);
        }
        else if (type == 2) {
            // Cerrar la estación del kilómetro x
            stations.erase(x);
        }
        else {
            // Buscar la estación más cercana al kilómetro x
            auto it = stations.lower_bound(x);

            long long best = -1;
            long long min_dist = -1;

            // Evaluamos el elemento mayor o igual a x
            if (it != stations.end()) {
                best = *it;
                min_dist = abs(*it - x);
            }

            // Evaluamos el elemento menor a x (el anterior en el set)
            if (it != stations.begin()) {
                auto prev_it = prev(it);
                long long dist = abs(*prev_it - x);

                // Si la distancia es menor, o si es igual (desempate: menor kilómetro)
                if (min_dist == -1 || dist <= min_dist) {
                    best = *prev_it;
                    min_dist = dist;
                }
            }

            cout << best << '\n';
        }
    }

    return 0;
}