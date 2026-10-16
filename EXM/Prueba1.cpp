/*
================================================================================
Conteo de Elementos en Rango (Nivel Examen / Plantilla AVL)
Te dan n números que se insertan en un AVL usando la plantilla de clase.
Luego, te dan q consultas con un rango [l, r] para responder cuántos elementos
guardados en el árbol se encuentran dentro de ese rango, inclusive.
================================================================================
*/

#include<bits/stdc++.h>

using namespace::std;

// --- PLANTILLA OFICIAL DE LA CLASE AVL ---
template<typename data_type>
struct AVL {
    struct TreeNode {
        int height;
        data_type data;
        TreeNode* left;
        TreeNode* right;
        TreeNode(data_type data = data_type(), int height = 0,
        TreeNode* left = nullptr, TreeNode* right = nullptr) :
        data(data), height(height), left(left), right(right) {}
    };

    TreeNode* root;
    AVL() { root = nullptr; }

    void update(TreeNode* u) {
        u -> height = 1 + max(h(u -> left) , h(u -> right));
    }
    int h(TreeNode* u) {
        return u == nullptr ? -1 : u -> height;
    }
    int FB(TreeNode* u) {
        return h(u -> left) - h(u -> right);
    }
    TreeNode* rotate_left(TreeNode* u) {
        TreeNode* v = u -> right;
        u -> right = v -> left;
        v -> left = u;
        update(u);
        update(v);
        return v;
    }
    TreeNode* rotate_right(TreeNode* u) {
        TreeNode* v = u -> left;
        u -> left = v -> right;
        v -> right = u;
        update(u);
        update(v);
        return v;
    }
    TreeNode* rebalance(TreeNode* u) {
        update(u);
        if (FB(u) > 1) {
            if (FB(u -> left) < 0) {
                u -> left = rotate_left(u -> left);
            }
            return rotate_right(u);
        }
        if (FB(u) < -1) {
            if (FB(u -> right) > 0) {
                u -> right = rotate_right(u -> right);
            }
            return rotate_left(u);
        }
        return u;
    }
    TreeNode* insert(TreeNode* u, data_type value) {
        if (u == nullptr) {
            return new TreeNode(value, 0);
        }
        if (value < u -> data) {
            u -> left = insert(u -> left, value);
        }
        else {
            u -> right = insert(u -> right, value);
        }
        return rebalance(u);
    }
    void insert(data_type value) {
        root = insert(root, value);
    }
};

// Vector global para aplanar el AVL en orden
vector<int> inorder_elements;

template<typename T>
void collect_inorder(typename AVL<T>::TreeNode* u) {
    if (u == nullptr) return;
    collect_inorder<T>(u->left);
    inorder_elements.push_back(u->data);
    collect_inorder<T>(u->right);
}

int main() {
    cin.tie(0) -> sync_with_stdio(false);

    int n, q;
    if (!(cin >> n >> q)) return 0;

    AVL<int> T;
    for (int i = 0; i < n; ++i) {
        int x;
        cin >> x;
        T.insert(x);
    }

    // Aplanamos el árbol para aprovechar búsqueda binaria rápida
    collect_inorder<int>(T.root);

    while (q--) {
        int l, r;
        cin >> l >> r;

        auto it_l = lower_bound(inorder_elements.begin(), inorder_elements.end(), l);
        auto it_r = upper_bound(inorder_elements.begin(), inorder_elements.end(), r);

        cout << distance(it_l, it_r) << '\n';
    }

    return 0;
}