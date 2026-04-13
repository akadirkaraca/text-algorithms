#include <string>
#include <vector>
#include <algorithm>
#include <iostream>

static std::vector<int> failure_function(const std::string& pattern)
{
    int m = (int)pattern.size();
    std::vector<int> pi(m, 0);
    int k = 0;
    for (int i = 1; i < m; ++i) {
        while (k > 0 && pattern[k] != pattern[i])
            k = pi[k - 1];
        if (pattern[k] == pattern[i]) ++k;
        pi[i] = k;
    }
    return pi;
}

static int compute_period(const std::string& pattern)
{
    int m = (int)pattern.size();
    if (m == 0) return 1;
    auto pi = failure_function(pattern);
    int p = m - pi[m - 1];
    return (m % p == 0) ? p : m;
}

std::vector<int> gg_search(const std::string& text, const std::string& pattern)
{
    int n = (int)text.size();
    int m = (int)pattern.size();
    if (m == 0) return {};
    if (m > n)  return {};

    int p = compute_period(pattern);
    int s = p;  // critical position

    std::vector<int> matches;
    int j = 0;
    int memory = -1;

    while (j <= n - m) {
        // Right phase: compare pattern[s..m-1] against text[j+s..j+m-1]
        int i = (memory >= 0) ? std::max(s, memory + 1) : s;
        while (i < m && pattern[i] == text[j + i])
            ++i;

        if (i < m) {
            // Mismatch in right phase
            j += std::max(1, i - s + 1);
            memory = -1;
        } else {
            // Left phase: compare pattern[0..s-1] against text[j..j+s-1]
            if (memory < 0) {
                i = 0;
                while (i < s && pattern[i] == text[j + i])
                    ++i;
            } else {
                i = s;  // already verified by memory
            }

            if (i >= s) {
                matches.push_back(j);
                memory = m - p - 1;
                j += p;
            } else {
                j += i + 1;
                memory = -1;
            }
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
    print(gg_search("acagagacagag",                "acagag"));   // [0, 6]
    print(gg_search("GCATCGCAGAGTATACAGTACG",      "GCAGAGT")); // [5]
    print(gg_search("aaaa",                        "aaa"));     // [0, 1]
    return 0;
}
#endif
