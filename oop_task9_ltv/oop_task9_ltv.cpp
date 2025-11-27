#include <iostream>
#include <vector>
using namespace std;

// бинарный поиск
int binarySearch(const vector<int>& a, int x) {
    int l = 0, r = a.size() - 1;
    while (l <= r) {
        int m = (l + r) / 2;
        if (a[m] == x) return m;
        if (a[m] < x) l = m + 1;
        else r = m - 1;
    }
    return -1;
}

// узел bst
struct Node {
    int key;
    Node* left;
    Node* right;
    Node(int k) : key(k), left(nullptr), right(nullptr) {}
};

// вставка в bst
Node* bstInsert(Node* root, int key) {
    if (!root) return new Node(key);
    if (key < root->key) root->left = bstInsert(root->left, key);
    else root->right = bstInsert(root->right, key);
    return root;
}

// вывод bst
void bstPrint(Node* root) {
    if (!root) return;
    bstPrint(root->left);
    cout << root->key << " ";
    bstPrint(root->right);
}

// высота узла
int height(Node* n) {
    if (!n) return 0;
    return max(height(n->left), height(n->right)) + 1;
}

// баланс-фактор avl
int balance(Node* n) {
    return height(n->left) - height(n->right);
}

// правый поворот
Node* rotateRight(Node* y) {
    Node* x = y->left;
    y->left = x->right;
    x->right = y;
    return x;
}

// левый поворот
Node* rotateLeft(Node* x) {
    Node* y = x->right;
    x->right = y->left;
    y->left = x;
    return y;
}

// вставка в avl
Node* avlInsert(Node* root, int key) {
    if (!root) return new Node(key);

    if (key < root->key) root->left = avlInsert(root->left, key);
    else root->right = avlInsert(root->right, key);

    int bf = balance(root);

    // ll
    if (bf > 1 && key < root->left->key)
        return rotateRight(root);

    // rr
    if (bf < -1 && key > root->right->key)
        return rotateLeft(root);

    // lr
    if (bf > 1 && key > root->left->key) {
        root->left = rotateLeft(root->left);
        return rotateRight(root);
    }

    // rl
    if (bf < -1 && key < root->right->key) {
        root->right = rotateRight(root->right);
        return rotateLeft(root);
    }

    return root;
}

// вывод avl
void avlPrint(Node* root) {
    if (!root) return;
    avlPrint(root->left);
    cout << root->key << " ";
    avlPrint(root->right);
}

// мейн
int main() {
    vector<int> arr = { 1, 4, 5, 7, 9, 12, 15, 20 };

    cout << "binary search (find 9): " << binarySearch(arr, 9) << "\n\n";

    Node* bst = nullptr;
    for (int x : arr) bst = bstInsert(bst, x);
    cout << "bst: ";
    bstPrint(bst);
    cout << "\n\n";

    Node* avl = nullptr;
    for (int x : arr) avl = avlInsert(avl, x);
    cout << "avl: ";
    avlPrint(avl);
    cout << "\n";

    return 0;
}
