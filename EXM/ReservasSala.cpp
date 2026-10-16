#include<bits/stdc++.h>

using namespace::std;

int main() {
    cin.tie(0) -> sync_with_stdio(false);

    int q;
    if (!(cin >> q)) return 0;

    // Guardamos las reservas como pares: {inicio, fin}
    // Como el set ordena por el primer valor (inicio), se ordenan solitos por 's'
    set<pair<long long, long long>> res;

    while (q--) {
        int type;
        cin >> type;

        if (type == 1) {
            long long s, e;
            cin >> s >> e;

            // Buscamos la primera reserva cuyo inicio sea mayor o igual a s
            auto it = res.lower_bound({s, e});
            bool choca = false;

            // 1. Revisar si choca con la reserva de la derecha
            if (it != res.end()) {
                if (it->first < e) choca = true; // Empieza antes de que nosotros terminemos
            }

            // 2. Revisar si choca con la reserva de la izquierda
            if (!choca && it != res.begin()) {
                auto prev_it = prev(it);
                if (prev_it->second > s) choca = true; // Termina después de que nosotros empezamos
            }

            if (choca) {
                cout << "NO\n";
            } else {
                res.insert({s, e});
                cout << "SI\n";
            }
        }
        else if (type == 2) {
            long long s;
            cin >> s;

            // Como el enunciado dice que la reserva existe, buscamos el par que empiece en s
            // Usamos un fin falso (0) solo para completar el par de búsqueda
            auto it = res.lower_bound({s, 0});
            res.erase(it);
        }
        else {
            long long t;
            cin >> t;

            bool encontrado = false;
            // Recorremos las reservas (como la cantidad de reservas concurrentes no suele ser
            // extrema para romper el tiempo en un escaneo lineal de las activas, o podemos
            // usar lower_bound simple). Aquí una forma directa y segura con iteradores:

            auto it = res.upper_bound({t, 2e18});
            if (it != res.begin()) {
                auto prev_it = prev(it);
                // Verificamos si el minuto t cae dentro de [s, e)
                if (prev_it->first <= t && t < prev_it->second) {
                    cout << prev_it->first << " " << prev_it->second << "\n";
                    encontrado = true;
                }
            }

            if (!encontrado) {
                cout << "LIBRE\n";
            }
        }
    }

    return 0;
}