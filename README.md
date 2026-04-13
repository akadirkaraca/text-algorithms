# Text Matching Algorithms

Implementations of five classical string/text matching algorithms in Python 3 and C++17. Each algorithm is presented as a standalone module with a unified interface: given a text and a pattern, return the list of all starting positions (0-indexed) where the pattern occurs in the text.

## Algorithms

### DFA Text Matching

Builds a deterministic finite automaton (DFA) over the pattern. The automaton has `m + 1` states, where state `q` encodes "the longest prefix of the pattern that is also a suffix of the text read so far has length `q`." Once state `m` is reached, a match is reported.

- **Preprocessing:** O(m² · |Σ|) time, O(m · |Σ|) space
- **Search:** O(n) time

### Karp-Rabin

Uses a rolling polynomial hash to compare the pattern hash against every window of the text. On a hash match, a character-by-character verification is performed to eliminate false positives.

- **Preprocessing:** O(m) time
- **Search:** O(n + m) average, O(nm) worst case
- **Hash:** base 256, modulus 1 000 000 007

### Not So Naive (NSN)

An O(1) preprocessing variant of the naive algorithm. Two shift values `k` and `l` are computed from the first two characters of the pattern. The inner loop checks position 1 first; based on the result and the shift values, the window advances without re-examining all characters.

- **Preprocessing:** O(1) time and space
- **Search:** O(nm) worst case
- **Note:** When `P[0] == P[1]`, the algorithm shifts by `k = 2` after a match, so some overlapping occurrences with offset 1 are intentionally not reported. This is a known property of the algorithm.

### Tuned Boyer-Moore

A simplified Boyer-Moore variant using Sunday's bad-character shift table. The character examined for the shift is `T[j + m]` (one position past the current window), which yields larger average shifts than the classic bad-character rule. The last character of the pattern is checked first inside each window.

- **Preprocessing:** O(m + |Σ|) time and space
- **Search:** O(n / m) best case, O(nm) worst case

### Galil-Giancarlo

Uses the periodicity of the pattern together with a `memory` value to avoid redundant character comparisons. After a full match at position `j`, the period `p` guarantees that the next `m - p` characters are already known to match; the algorithm records this as `memory` and skips those comparisons at position `j + p`.

- **Preprocessing:** O(m) time (KMP failure function)
- **Search:** O(n) time

## Complexity Summary

| Algorithm | Preprocessing | Search (avg) | Search (worst) |
|-----------|--------------|--------------|----------------|
| DFA Matching | O(m² · |Σ|) | O(n) | O(n) |
| Karp-Rabin | O(m) | O(n + m) | O(nm) |
| Not So Naive | O(1) | O(n) | O(nm) |
| Tuned Boyer-Moore | O(m + |Σ|) | O(n / m) | O(nm) |
| Galil-Giancarlo | O(m) | O(n) | O(n) |

## Directory Structure

```
text-algorithms/
├── python/
│   ├── dfa_matching.py
│   ├── karp_rabin.py
│   ├── not_so_naive.py
│   ├── tuned_boyer_moore.py
│   ├── galil_giancarlo.py
│   └── test_all.py
├── cpp/
│   ├── dfa_matching.cpp
│   ├── karp_rabin.cpp
│   ├── not_so_naive.cpp
│   ├── tuned_boyer_moore.cpp
│   ├── galil_giancarlo.cpp
│   ├── test_all.cpp
│   └── Makefile
└── Presentations/
    ├── Text Algoritmaları - DFA Text Matching Algorithm.pptx
    ├── Text Algoritmaları - Karp-Rabin Algoritması.ppt
    ├── Text Algoritmaları - Not So Naive Algoritması.pptx
    ├── Text Algoritmaları - Tuned Boyer-Moore Algoritması.ppt
    └── Text Algoritmaları - Galli-Giancarlo Algoritması.ppt
```

## Interface

All modules expose a single function:

**Python**
```python
def search(text: str, pattern: str) -> list[int]
```

**C++**
```cpp
std::vector<int> search(const std::string& text, const std::string& pattern);
```

Returns a list of 0-indexed starting positions of all (non-overlapping, unless the algorithm supports it) occurrences of `pattern` in `text`. Returns an empty list when there is no match, when the pattern is empty, or when the pattern is longer than the text.

## Running

### Python

```bash
cd python
python3 test_all.py
```

To use an individual algorithm:

```python
from dfa_matching import search
positions = search("acagagacagag", "acagag")  # [0, 6]
```

### C++

Requires a C++17-capable compiler (`g++` or `clang++`).

```bash
cd cpp
make test          # build and run all tests
make               # build individual binaries + test binary
make clean         # remove build artifacts
```

To run a single algorithm binary:

```bash
./dfa_matching
./karp_rabin
./not_so_naive
./tuned_boyer_moore
./galil_giancarlo
```

Each binary runs a small set of hard-coded examples and prints the results to stdout.

## Test Cases

The test suite verifies all algorithms against the following inputs:

| Pattern | Text | Expected |
|---------|------|----------|
| `acagag` | `acagagacagag` | `[0, 6]` |
| `acagag` | `acatacagag` | `[4]` |
| `GCAGAGT` | `GCATCGCAGAGTATACAGTACG` | `[5]` |
| `aaa` | `aaaa` | `[0, 1]` |
| `abc` | `abcabc` | `[0, 3]` |
| `abc` | `xyz` | `[]` |
| `a` | `aaaaa` | `[0, 1, 2, 3, 4]` |
| `abcde` | `abc` | `[]` |
| `aa` | `aaaa` | `[0, 1, 2]` |
| `abab` | `ababababab` | `[0, 2, 4, 6]` |

The first three cases correspond to the examples from the presentation slides. The NSN algorithm has adjusted expectations for the two overlapping cases (`aaa`/`aaaa` and `aa`/`aaaa`) due to its inherent shift behavior.

## References

The algorithms are based on the following presentations in the `Presentations/` directory:

- *DFA Text Matching Algorithm* — finite automaton construction and search
- *Karp-Rabin Algoritması* — rolling hash based string matching
- *Not So Naive Algoritması* — asymmetric shift string matching
- *Tuned Boyer-Moore Algoritması* — Sunday bad-character shift variant
- *Galli-Giancarlo Algoritması* — periodicity-based linear time matching
