def search(text: str, pattern: str) -> list:
    n, m = len(text), len(pattern)
    if m == 0:
        return []
    if m == 1:
        return [i for i in range(n) if text[i] == pattern[0]]

    k = 2 if pattern[0] == pattern[1] else 1
    l = 1 if pattern[0] == pattern[1] else 2

    matches = []
    j = 0
    while j <= n - m:
        if pattern[1] != text[j + 1]:
            j += k
        else:
            i = 2
            while i < m and pattern[i] == text[j + i]:
                i += 1
            if i == m and pattern[0] == text[j]:
                matches.append(j)
            if pattern[0] != pattern[1]:
                j += l
            else:
                j += k

    return matches


if __name__ == "__main__":
    print(search("acagagacagag", "acagag"))   # [0, 6]
    print(search("GCATCGCAGAGTATACAGTACG", "GCAGAGT"))  # [6]
    print(search("aaaa", "aaa"))  # [0, 1]
