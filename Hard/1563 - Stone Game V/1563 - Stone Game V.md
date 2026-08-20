# LeetCode #1563 - Stone Game V

LeetCode Link： [link](https://leetcode.com/problems/stone-game-v/)


- **Date**: 2026/08/17
- **Difficulty**: Hard
- **Topic**: Array、Math、Dynamic Programming、Game Theory
- **Language**: C++
- **Status**:
  - [X] First AC 
  - [ ] Optimized
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

區間 DP + 記憶化。`dp[left][right]` = Alice 在子陣列 `[left, right]` 這段能拿到的最高分。用 `prefix` 前綴和 O(1) 取任一段的和。

列舉切割點 `i`（把 `[left, right]` 切成左段 `[left, i-1]` 和右段 `[i, right]`）：

- `left_score = prefix[i] - prefix[left]`（左段和）
- `right_score = prefix[right + 1] - prefix[i]`（右段和）
- 左 > 右：Bob 丟掉較大的左段，Alice 保留右段拿 `right_score`，再往右段遞迴 → `solve(i, right) + right_score`
- 左 < 右：Bob 丟右段，Alice 保留左段拿 `left_score`，再往左段遞迴 → `solve(left, i-1) + left_score`
- 兩邊相等：由 Alice 選一邊留，取 `max(solve(left, i-1), solve(i, right)) + left_score`

Base case：只剩 1 顆 (`left == right`) 回 0；剩 2 顆 (`right - left == 1`) 回兩顆裡較小的那顆（大的會被丟掉）。

小地方：`dp` 用 0 當「還沒算」的標記剛好安全 —— 長度 ≥ 2 的區間答案至少是某段和 ≥ 1，不會真的等於 0，所以不會誤判。

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
                dp[left][right] = max(dp[left][right], solve(dp, prefix, i, right) + right_score);
            } else if (left_score < right_score) {
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

設 `n = stoneValue.size()`。狀態數 O(N^2)，每個狀態列舉切割點 O(N)。

| Complexity | Value |
|------------|-------|
| Time | O(N^3) |
| Space | O(N^2) |


---
