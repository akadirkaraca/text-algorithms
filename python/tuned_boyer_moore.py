def _build_shift(pattern: str) -> tuple:
    m = len(pattern)
    default = m + 1
    shift = {}
    for i in range(m):
        shift[pattern[i]] = m - i
    return shift, default


def search(text: str, pattern: str) -> list:
    n, m = len(text), len(pattern)
    if m == 0 or m > n:
        return []

    shift, default = _build_shift(pattern)
    matches = []
    j = 0

    while j <= n - m:
        if text[j + m - 1] == pattern[m - 1]:
            i = m - 2
            while i >= 0 and pattern[i] == text[j + i]:
                i -= 1
            if i < 0:
                matches.append(j)

        if j + m >= n:
            break
        j += shift.get(text[j + m], default)

    return matches


if __name__ == "__main__":
    print(search("acagagacagag", "acagag"))   # [0, 6]
    print(search("GCATCGCAGAGTATACAGTACG", "GCAGAGT"))  # [6]
    print(search("aaaa", "aaa"))  # [0, 1]
