#include <string>
#include <vector>
#include <array>
#include <iostream>

std::vector<int> tbm_search(const std::string& text, const std::string& pattern)
{
    int n = (int)text.size();
    int m = (int)pattern.size();
    if (m == 0 || m > n) return {};

    // Sunday shift table: shift[c] = distance to shift based on T[j+m]
    std::array<int, 256> shift;
    shift.fill(m + 1);
    for (int i = 0; i < m; ++i)
        shift[(unsigned char)pattern[i]] = m - i;

    std::vector<int> matches;
    int j = 0;
    while (j <= n - m) {
        if (text[j + m - 1] == pattern[m - 1]) {
            int i = m - 2;
            while (i >= 0 && pattern[i] == text[j + i])
                --i;
            if (i < 0)
                matches.push_back(j);
        }
        if (j + m >= n) break;
        j += shift[(unsigned char)text[j + m]];
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
    print(tbm_search("acagagacagag",                "acagag"));   // [0, 6]
    print(tbm_search("GCATCGCAGAGTATACAGTACG",      "GCAGAGT")); // [5]
    print(tbm_search("aaaa",                        "aaa"));     // [0, 1]
    return 0;
}
#endif
