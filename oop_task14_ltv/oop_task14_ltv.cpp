#include <iostream>
#include <string>
using namespace std;

// рабин-карп
void rabinKarp(const string& text, const string& pattern) {
    int n = text.size(), m = pattern.size();
    int base = 256, mod = 101;
    int p = 0, t = 0, h = 1;

    for (int i = 0; i < m - 1; i++) h = (h * base) % mod;
    for (int i = 0; i < m; i++) { p = (base * p + pattern[i]) % mod; t = (base * t + text[i]) % mod; }

    for (int i = 0; i <= n - m; i++) {
        if (p == t) {
            bool match = true;
            for (int j = 0; j < m; j++) if (text[i + j] != pattern[j]) { match = false; break; }
            if (match) cout << "Pattern found at index " << i << "\n";
        }
        if (i < n - m) t = (base * (t - text[i] * h) + text[i + m]) % mod;
        if (t < 0) t += mod;
    }
}

// мейн
int main() {
    string text = "ABABDABACDABABCABAB";
    string pattern = "ABABCABAB";
    rabinKarp(text, pattern);
    return 0;
}
