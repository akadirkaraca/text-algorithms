#include <string>
#include <vector>
#include <iostream>

std::vector<int> nsn_search(const std::string& text, const std::string& pattern)
{
    int n = (int)text.size();
    int m = (int)pattern.size();
    if (m == 0) return {};
    if (m == 1) {
        std::vector<int> matches;
        for (int i = 0; i < n; ++i)
            if (text[i] == pattern[0]) matches.push_back(i);
        return matches;
    }

    int k = (pattern[0] == pattern[1]) ? 2 : 1;
    int l = (pattern[0] == pattern[1]) ? 1 : 2;

    std::vector<int> matches;
    int j = 0;
    while (j <= n - m) {
        if (pattern[1] != text[j + 1]) {
            j += k;
        } else {
            int i = 2;
            while (i < m && pattern[i] == text[j + i])
                ++i;
            if (i == m && pattern[0] == text[j])
                matches.push_back(j);
            if (pattern[0] != pattern[1])
                j += l;
            else
                j += k;
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
    print(nsn_search("acagagacagag",           "acagag"));   // [0, 6]
    print(nsn_search("GCATCGCAGAGTATACAGTACG", "GCAGAGT")); // [5]
    print(nsn_search("aaaa",                   "aaa"));     // [0] (k=2 skip)
    return 0;
}
#endif
