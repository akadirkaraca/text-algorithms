def _compute_delta(pattern: str, alphabet: set) -> list:
    m = len(pattern)
    delta = [{c: 0 for c in alphabet} for _ in range(m + 1)]
    for q in range(m + 1):
        for c in alphabet:
            pqc = pattern[:q] + c
            k = min(m, q + 1)
            while k > 0 and not pqc.endswith(pattern[:k]):
                k -= 1
            delta[q][c] = k
    return delta


def search(text: str, pattern: str) -> list:
    if not pattern or not text:
        return []

    alphabet = set(text) | set(pattern)
    delta = _compute_delta(pattern, alphabet)
    m = len(pattern)
    matches = []
    q = 0

    for i, c in enumerate(text):
        q = delta[q].get(c, 0)
        if q == m:
            matches.append(i - m + 1)

    return matches


if __name__ == "__main__":
    print(search("acagagacagag", "acagag"))   # [0, 6]
    print(search("GCATCGCAGAGTATACAGTACG", "GCAGAGT"))  # [6]
    print(search("aaaa", "aaa"))  # [0, 1]
