#include <string>
#include <vector>
#include <iostream>

static const long long BASE = 256;
static const long long MOD  = 1'000'000'007;

std::vector<int> kr_search(const std::string& text, const std::string& pattern)
{
    int n = (int)text.size();
    int m = (int)pattern.size();
    if (m == 0 || m > n) return {};

    // h = BASE^(m-1) mod MOD
    long long h = 1;
    for (int i = 0; i < m - 1; ++i)
        h = (h * BASE) % MOD;

    long long p_hash = 0, t_hash = 0;
    for (int i = 0; i < m; ++i) {
        p_hash = (BASE * p_hash + (unsigned char)pattern[i]) % MOD;
        t_hash = (BASE * t_hash + (unsigned char)text[i])    % MOD;
    }

    std::vector<int> matches;
    for (int i = 0; i <= n - m; ++i) {
        if (t_hash == p_hash && text.substr(i, m) == pattern)
            matches.push_back(i);

        if (i < n - m) {
            t_hash = (BASE * (t_hash - (unsigned char)text[i] * h % MOD) +
                      (unsigned char)text[i + m]) % MOD;
            t_hash = (t_hash + MOD) % MOD;
        }
    }
    return matches;
}

#ifndef TESTING
int main()
{
    auto print = [](const std::vector<int>& v) {
        std::cout << "[";
        for (int i = 0; i < (int)v.size(); ++i) {
            if (i) std::cout << ", ";
            std::cout << v[i];
        }
        std::cout << "]\n";
    };
    print(kr_search("acagagacagag",                "acagag"));   // [0, 6]
    print(kr_search("GCATCGCAGAGTATACAGTACG",      "GCAGAGT")); // [5]
    print(kr_search("aaaa",                        "aaa"));     // [0, 1]
    return 0;
}
#endif
