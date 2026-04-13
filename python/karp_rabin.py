BASE = 256
MOD = 1_000_000_007


def search(text: str, pattern: str) -> list:
    n, m = len(text), len(pattern)
    if m == 0 or m > n:
        return []

    h = pow(BASE, m - 1, MOD)
    p_hash = t_hash = 0

    for i in range(m):
        p_hash = (BASE * p_hash + ord(pattern[i])) % MOD
        t_hash = (BASE * t_hash + ord(text[i])) % MOD

    matches = []
    for i in range(n - m + 1):
        if t_hash == p_hash and text[i:i + m] == pattern:
            matches.append(i)
        if i < n - m:
            t_hash = (BASE * (t_hash - ord(text[i]) * h % MOD) + ord(text[i + m])) % MOD
            t_hash = (t_hash + MOD) % MOD

    return matches


if __name__ == "__main__":
    print(search("acagagacagag", "acagag"))   # [0, 6]
    print(search("GCATCGCAGAGTATACAGTACG", "GCAGAGT"))  # [6]
    print(search("aaaa", "aaa"))  # [0, 1]
