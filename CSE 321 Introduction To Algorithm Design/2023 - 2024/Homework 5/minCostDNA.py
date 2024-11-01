# This function computes the minimum cost and sequence of operations to transform one DNA sequence (seq1) 
# into another DNA sequence (seq2), considering insertion/deletion and substitution costs.
def minCostDNA(seq1, seq2, insDelCost, subsitionCost):
    m = len(seq1)
    n = len(seq2)

    dp = [[0] * (n + 1) for _ in range(m + 1)]

    for i in range(m + 1):
        dp[i][0] = i * insDelCost

    for j in range(n + 1):
        dp[0][j] = j * insDelCost

    for i in range(1, m + 1):
        for j in range(1, n + 1):
            if seq1[i - 1] == seq2[j - 1]:
                dp[i][j] = dp[i - 1][j - 1]
            else:
                dp[i][j] = min(
                    dp[i - 1][j] + insDelCost,
                    dp[i][j - 1] + insDelCost,
                    dp[i - 1][j - 1] + subsitionCost
                )

    i, j = m, n
    operations = []
    while i > 0 or j > 0:
        if i > 0 and dp[i][j] == dp[i - 1][j] + insDelCost:
            operations.append(f"Delete {seq1[i - 1]} from seq1")
            i -= 1
        elif j > 0 and dp[i][j] == dp[i][j - 1] + insDelCost:
            operations.append(f"Insert {seq2[j - 1]} into seq1")
            j -= 1
        else:
            if seq1[i - 1] != seq2[j - 1]:
                operations.append(f"Substitute {seq1[i - 1]} in seq1 with {seq2[j - 1]}")
            i -= 1
            j -= 1

    operations.reverse()

    return dp[m][n], operations


# Test Codes
seq1 = "AGTACG"
seq2 = "TAGCT"

cost, operations = minCostDNA(seq1, seq2, 1, 3)

print(f"Minimum cost: {cost}")
print("Operations:")
for op in operations:
    print(op)
