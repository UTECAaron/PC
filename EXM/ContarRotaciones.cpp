#include<bits/stdc++.h>

using namespace::std;

// Estructura de nodos para un AVL dinámico basado en memoria estática/punteros
struct TreeNode {
    int key;
    int height;
    TreeNode* left;
    TreeNode* right;
    
    TreeNode(int k) {
        key = k;
        height = 0; // Altura 0 para un solo nodo (hoja)
        left = nullptr;
        right = nullptr;
    }
};

// Variable global para acumular las rotaciones de la operación actual
int rotation_count = 0;

// Obtiene la altura de forma segura (nulo retorna -1)
int h(TreeNode* u) {
    return u == nullptr ? -1 : u->height;
}

// Calcula el Factor de Balance
int FB(TreeNode* u) {
    return h(u->left) - h(u->right);
}

// Actualiza la altura del nodo
void update(TreeNode* u) {
    u->height = 1 + max(h(u->left), h(u->right));
}

// Rotación a la izquierda (cuenta como 1 rotación)
TreeNode* rotate_left(TreeNode* u) {
    rotation_count++;
    TreeNode* v = u->right;
    u->right = v->left;
    v->left = u;
    update(u);
    update(v);
    return v;
}

// Rotación a la derecha (cuenta como 1 rotación)
TreeNode* rotate_right(TreeNode* u) {
    rotation_count++;
    TreeNode* v = u->left;
    u->left = v->right;
    v->right = u;
    update(u);
    update(v);
    return v;
}

// Rebalanceo del nodo u según las reglas del AVL
TreeNode* rebalance(TreeNode* u) {
    update(u);
    
    // Desbalanceo por la izquierda
    if (FB(u) > 1) {
        // Caso LR: si el hijo izquierdo tiene FB < 0, rotación previa a la izquierda
        if (FB(u->left) < 0) {
            u->left = rotate_left(u->left);
        }
        return rotate_right(u);
    }
    
    // Desbalanceo por la derecha
    if (FB(u) < -1) {
        // Caso RL: si el hijo derecho tiene FB > 0, rotación previa a la derecha
        if (FB(u->right) > 0) {
            u->right = rotate_right(u->right);
        }
        return rotate_left(u);
    }
    
    return u;
}

// Inserción recursiva con rebalanceo automático
TreeNode* insert(TreeNode* u, int val) {
    if (u == nullptr) {
        return new TreeNode(val);
    }
    if (val < u->key) {
        u->left = insert(u->left, val);
    } else {
        u->right = insert(u->right, val);
    }
    return rebalance(u);
}

// Encuentra el nodo con la clave mínima (sucesor)
TreeNode* min_element(TreeNode* u) {
    TreeNode* current = u;
    while (current->left != nullptr) {
        current = current->left;
    }
    return current;
}

// Eliminación recursiva con rebalanceo automático
TreeNode* erase(TreeNode* u, int val) {
    if (u == nullptr) return nullptr;
    
    if (val < u->key) {
        u->left = erase(u->left, val);
    } else if (val > u->key) {
        u->right = erase(u->right, val);
    } else {
        // Nodo encontrado
        if (u->left == nullptr) {
            TreeNode* temp = u->right;
            delete u;
            return temp;
        } else if (u->right == nullptr) {
            TreeNode* temp = u->left;
            delete u;
            return temp;
        }
        
        // Si tiene ambos hijos, se reemplaza por el sucesor (mínimo del subárbol derecho)
        TreeNode* succ = min_element(u->right);
        u->key = succ->key;
        u->right = erase(u->right, succ->key);
    }
    
    if (u == nullptr) return nullptr;
    return rebalance(u);
}

int main() {
    cin.tie(0) -> sync_with_stdio(false);
    
    int q;
    if (!(cin >> q)) return 0;
    
    TreeNode* root = nullptr;
    
    while (q--) {
        int type, x;
        cin >> type >> x;
        
        // Reiniciamos el contador para esta operación
        rotation_count = 0;
        
        if (type == 1) {
            root = insert(root, x);
        } else {
            root = erase(root, x);
        }
        
        // Imprimimos la cantidad de rotaciones hechas y la altura actual de la raíz
        cout << rotation_count << " " << h(root) << '\n';
    }
    
    return 0;
}


