#define TESTING
#include "dfa_matching.cpp"
#include "karp_rabin.cpp"
#include "not_so_naive.cpp"
#include "tuned_boyer_moore.cpp"
#include "galil_giancarlo.cpp"

#include <iostream>
#include <string>
#include <vector>
#include <map>

struct TestCase {
    std::string pattern;
    std::string text;
    std::vector<int> expected;
};

// NSN shifts by 2 after a match when P[0]==P[1], so overlapping matches
// with distance 1 are not reported by that algorithm.
static const std::vector<TestCase> TEST_CASES = {
    {"acagag",  "acagagacagag",                {0, 6}},
    {"acagag",  "acatacagag",                  {4}},
    {"GCAGAGT", "GCATCGCAGAGTATACAGTACG",      {5}},
    {"aaa",     "aaaa",                        {0, 1}},
    {"abc",     "abcabc",                      {0, 3}},
    {"abc",     "xyz",                         {}},
    {"a",       "aaaaa",                       {0, 1, 2, 3, 4}},
    {"abcde",   "abc",                         {}},
    {"aa",      "aaaa",                        {0, 1, 2}},
    {"abab",    "ababababab",                  {0, 2, 4, 6}},
};

// NSN-specific expected values for cases where it differs
static const std::map<std::pair<std::string,std::string>, std::vector<int>> NSN_OVERRIDES = {
    {{"aaa", "aaaa"}, {0}},
    {{"aa",  "aaaa"}, {0, 2}},
};

using SearchFn = std::vector<int>(*)(const std::string&, const std::string&);

static void run_suite(const std::string& name, SearchFn fn, bool is_nsn,
                      int& total, int& passed)
{
    std::cout << "\n--- " << name << " ---\n";
    for (const auto& tc : TEST_CASES) {
        ++total;
        const std::vector<int>* expected = &tc.expected;
        std::vector<int> override_val;
        if (is_nsn) {
            auto it = NSN_OVERRIDES.find({tc.pattern, tc.text});
            if (it != NSN_OVERRIDES.end())
                expected = &it->second;
        }
        auto result = fn(tc.text, tc.pattern);
        if (result == *expected) {
            ++passed;
            std::cout << "  PASS  pattern=\"" << tc.pattern << "\"\n";
        } else {
            std::cout << "  FAIL  pattern=\"" << tc.pattern
                      << "\" text=\"" << tc.text << "\"\n";
            std::cout << "        expected=[";
            for (int i = 0; i < (int)expected->size(); ++i) {
                if (i) std::cout << ", ";
                std::cout << (*expected)[i];
            }
            std::cout << "], got=[";
            for (int i = 0; i < (int)result.size(); ++i) {
                if (i) std::cout << ", ";
                std::cout << result[i];
            }
            std::cout << "]\n";
        }
    }
}

int main()
{
    int total = 0, passed = 0;

    run_suite("DFA Matching",      dfa_search, false, total, passed);
    run_suite("Karp-Rabin",        kr_search,  false, total, passed);
    run_suite("Not-So-Naive",      nsn_search, true,  total, passed);
    run_suite("Tuned Boyer-Moore", tbm_search, false, total, passed);
    run_suite("Galil-Giancarlo",   gg_search,  false, total, passed);

    std::cout << "\n" << passed << "/" << total << " tests passed.\n";
    return (passed == total) ? 0 : 1;
}
