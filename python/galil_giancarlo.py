def _failure_function(pattern: str) -> list:
    m = len(pattern)
    pi = [0] * m
    k = 0
    for i in range(1, m):
        while k > 0 and pattern[k] != pattern[i]:
            k = pi[k - 1]
        if pattern[k] == pattern[i]:
            k += 1
        pi[i] = k
    return pi


def _compute_period(pattern: str) -> int:
    m = len(pattern)
    if m == 0:
        return 1
    pi = _failure_function(pattern)
    p = m - pi[m - 1]
    return p if m % p == 0 else m


def search(text: str, pattern: str) -> list:
    n, m = len(text), len(pattern)
    if m == 0:
        return []
    if m > n:
        return []

    p = _compute_period(pattern)
    s = p  # critical position: end of first period

    matches = []
    j = 0
    memory = -1

    while j <= n - m:
        # Right phase: compare P[s..m-1] against T[j+s..j+m-1]
        i = max(s, memory + 1) if memory >= 0 else s
        while i < m and pattern[i] == text[j + i]:
            i += 1

        if i < m:
            # Mismatch in right phase
            j += max(1, i - s + 1)
            memory = -1
        else:
            # Left phase: compare P[0..s-1] against T[j..j+s-1]
            if memory < 0:
                i = 0
                while i < s and pattern[i] == text[j + i]:
                    i += 1
            else:
                i = s  # already verified by memory

            if i >= s:
                matches.append(j)
                memory = m - p - 1
                j += p
            else:
                j += i + 1
                memory = -1

    return matches


if __name__ == "__main__":
    print(search("acagagacagag", "acagag"))   # [0, 6]
    print(search("GCATCGCAGAGTATACAGTACG", "GCAGAGT"))  # [6]
    print(search("aaaa", "aaa"))  # [0, 1]
