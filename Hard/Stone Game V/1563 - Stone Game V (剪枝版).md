# LeetCode #1563 - Stone Game V

LeetCode Link： [link](https://leetcode.com/problems/stone-game-v/)


- **Date**: 2026/08/17
- **Difficulty**: Hard
- **Topic**: Array、Math、Dynamic Programming、Game Theory
- **Language**: C++
- **Status**:
  - [X] First AC 
  - [X] Optimized
  - [ ] Review Completed

<!-- First AC: 當你第一次把這題寫過並成功 AC，就打勾。
Optimized: 代表你不是只有 AC，而是已經改成比較好的解法。
Review Completed: 代表你隔幾天重新寫一次，而且沒有看答案也能寫出來。 -->
---

# 🎯 Problem

There are several stones arranged in a row, and each stone has an associated value which is an integer given in the array `stoneValue`.

In each round of the game, Alice divides the row into two non-empty rows (i.e. left row and right row), then Bob calculates the value of each row which is the sum of the values of all the stones in this row. Bob throws away the row which has the maximum value, and Alice's score increases by the value of the remaining row. If the value of the two rows are equal, Bob lets Alice decide which row will be thrown away. The next round starts with the remaining row.

The game ends when there is only one stone remaining. Alice's is initially **zero**.

Return the maximum score that Alice can obtain.

---

## Example 1

**Input**

```text
stoneValue = [6,2,3,4,5,5]
```

**Output**

```text
18
```

**Explanation**

In the first round, Alice divides the row to [6,2,3], [4,5,5]. The left row has the value 11 and the right row has value 14. Bob throws away the right row and Alice's score is now 11.
In the second round Alice divides the row to [6], [2,3]. This time Bob throws away the left row and Alice's score becomes 16 (11 + 5).
The last round Alice has only one choice to divide the row which is [2], [3]. Bob throws away the right row and Alice's score is now 18 (16 + 2). The game ends because only one stone is remaining in the row.

---

## Example 2

**Input**

```text
stoneValue = [7,7,7,7,7,7,7]
```

**Output**

```text
28
```

---

## Example 3

**Input**

```text
stoneValue = [4]
```

**Output**

```text
0
```

---

## Constraints

```text
1 <= stoneValue.length <= 500
1 <= stoneValue[i] <= 10^6
```
---

# 💡 Idea

區間 DP + 記憶化 + **剪枝優化**。基本思路跟原版相同，但加上剪枝條件。

核心發現：如果已經找到的答案 `dp[left][right]` 夠大，有些切割點就不用再試。

- 左 > 右 時：如果 `dp[left][right] >= 2 * right_score`，說明已經拿到超過 `right_score` 的兩倍，繼續試下一個 `i` 也不會更好（因為 right_score 會變小），直接 **break**。
- 左 < 右 時：如果 `dp[left][right] >= 2 * left_score`，同理 **continue** 跳過這次迭代。
- 相等時：無法剪枝，列舉所有可能。

這樣在實踐中能大幅減少遞迴呼叫和重複計算，時間上從 O(N³) 降到接近 O(N².5) 或更好（取決於測資）。

---

# 💻 Code

```cpp
class Solution {
public:
    // 6, 2, 3, 4, 5, 5
    // 0  6  8  11 15 20 25
    //   |  |  |  |  |
    int solve(vector<vector<int>> &dp, vector<int> &prefix, int left, int right) { // 0, 5
        int n = dp.size();
        // left = 0, right = 5
        // i = 1 ~ 5
        // (0, 0),(0, 1),(0, 2),(0, 3),(0, 4)
        // 
        if (n == 1) return 0;
        if (right == left) return 0;
        if (dp[left][right] != 0) return dp[left][right];
        if (right - left == 1) {
            return dp[left][right] = min(prefix[left + 1] - prefix[left], prefix[right + 1] - prefix[right]);
        }
        for (int i = left + 1; i <= right; i++) { // 0 0 , 0 1
            int left_score =  (prefix[i] - prefix[left]); 
            int right_score =  (prefix[right + 1] - prefix[i]);

            if (left_score > right_score) {
                if (dp[left][right] >= 2 * right_score) break;   // 換成 right_score,一致地用 break
                dp[left][right] = max(dp[left][right], solve(dp, prefix, i, right) + right_score);
            } else if (left_score < right_score) {
                if (dp[left][right] >= 2 * left_score) continue;
                dp[left][right] = max(dp[left][right], solve(dp, prefix, left, i - 1) + left_score);
            } else {
                dp[left][right] = max(dp[left][right], max(solve(dp, prefix, left, i - 1), solve(dp, prefix, i, right)) + left_score);
            }
        }
        return dp[left][right];
    }

    int stoneGameV(vector<int>& stoneValue) {
        int n = stoneValue.size();
        vector<vector<int>> dp(n, vector<int>(n, 0));

        vector<int> prefix(n + 1, 0);

        for (int i = 0; i < n; i++) {
            prefix[i + 1] = prefix[i] + stoneValue[i];
        }
        return solve(dp, prefix, 0, n - 1);
        // 
    }
};
```

---

# ⏱ Complexity

設 `n = stoneValue.size()`。剪枝後，最壞情況仍是 O(N³)，但實踐中能降到 O(N².5) 或更優。

| Complexity | Value |
|------------|-------|
| Time | O(N³) worst / O(N².5~²) practical |
| Space | O(N²) |


---
