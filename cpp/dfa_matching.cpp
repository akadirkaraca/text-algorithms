#include <string>
#include <vector>
#include <array>
#include <iostream>

// Build transition table delta[state][char] using ASCII (0-127).
static std::vector<std::array<int, 128>> build_delta(const std::string& pattern)
{
    int m = (int)pattern.size();
    std::vector<std::array<int, 128>> delta(m + 1);
    for (auto& row : delta) row.fill(0);

    for (int q = 0; q <= m; ++q) {
        for (int c = 0; c < 128; ++c) {
            // Find largest k such that pattern[0..k-1] is suffix of pattern[0..q-1]+c
            int k = std::min(m, q + 1);
            // Build the string pattern[0..q-1] + c and check suffix
            // Efficient check: compare pattern[0..k-1] against pattern[q-k..q-1]+c
            while (k > 0) {
                // Check if pattern[0..k-1] is a suffix of pattern[0..q-1] + char(c)
                bool ok = true;
                // The last char of the candidate suffix is c; must match pattern[k-1]
                if (pattern[k - 1] != (char)c) { --k; continue; }
                // Remaining k-1 chars: pattern[0..k-2] must equal pattern[q-k..q-2]
                for (int i = 0; i < k - 1; ++i) {
                    if (pattern[i] != pattern[q - k + 1 + i]) { ok = false; break; }
                }
                if (ok) break;
                --k;
            }
            delta[q][c] = k;
        }
    }
    return delta;
}

std::vector<int> dfa_search(const std::string& text, const std::string& pattern)
{
    if (pattern.empty() || text.empty()) return {};

    auto delta = build_delta(pattern);
    int m = (int)pattern.size();
    std::vector<int> matches;
    int q = 0;

    for (int i = 0; i < (int)text.size(); ++i) {
        unsigned char c = (unsigned char)text[i];
        q = (c < 128) ? delta[q][c] : 0;
        if (q == m)
            matches.push_back(i - m + 1);
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
    print(dfa_search("acagagacagag",                "acagag"));   // [0, 6]
    print(dfa_search("GCATCGCAGAGTATACAGTACG",      "GCAGAGT")); // [5]
    print(dfa_search("aaaa",                        "aaa"));     // [0, 1]
    return 0;
}
#endif
