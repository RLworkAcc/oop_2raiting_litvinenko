#include <iostream>
#include <queue>
#include <unordered_map>
#include <vector>
using namespace std;

// узел дерева Хаффмана
struct Node {
    char ch;
    int freq;
    Node* left;
    Node* right;
    Node(char c, int f) : ch(c), freq(f), left(nullptr), right(nullptr) {}
    Node(Node* l, Node* r) : ch(0), freq(l->freq + r->freq), left(l), right(r) {}
};

struct Cmp {
    bool operator()(Node* a, Node* b) {
        return a->freq > b->freq;
    }
};

void buildCodes(Node* root, const string& s, unordered_map<char, string>& out) {
    if (!root) return;
    if (!root->left && !root->right) {
        out[root->ch] = s;
        return;
    }
    buildCodes(root->left, s + "0", out);
    buildCodes(root->right, s + "1", out);
}

int main() {
    string text = "AAAABAABABABABCBCAAAD";

    unordered_map<char, int> freq;
    for (char c : text) freq[c]++;

    priority_queue<Node*, vector<Node*>, Cmp> pq;

    for (auto& x : freq)
        pq.push(new Node(x.first, x.second));

    while (pq.size() > 1) {
        Node* a = pq.top(); pq.pop();
        Node* b = pq.top(); pq.pop();
        pq.push(new Node(a, b));
    }

    Node* root = pq.top();

    unordered_map<char, string> codes;
    buildCodes(root, "", codes);

    cout << "Коды Хаффмана:\n";
    for (auto& el : codes) {
        cout << el.first << " -> " << el.second << "\n";
    }

    string encoded = "";
    for (char c : text) encoded += codes[c];

    cout << "\nИсходная длина (символы): " << text.size() * 8 << " бит (условно)\n";
    cout << "Код Хаффмана длина: " << encoded.size() << " бит\n\n";
    cout << "Закодированный текст:\n" << encoded << "\n";

    return 0;
}
