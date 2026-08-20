# LeetCode #1386 - Cinema Seat Allocation

LeetCode Link： [link](https://leetcode.com/problems/cinema-seat-allocation/description/)


- **Date**: 2026/08/19
- **Difficulty**: Medium
- **Topic**: Array、Hash Table、Greedy
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

A cinema has `n` rows of seats numbered 1 to `n`, with each row containing 10 seats numbered 1 to 10. Given a 2D array `reservedSeats` indicating already-reserved seats, you must allocate four-person groups to seats in the same row.

Groups can only occupy one of these seat blocks:
- seats 2, 3, 4, 5
- seats 4, 5, 6, 7
- seats 6, 7, 8, 9

A block is valid only if none of its seats are reserved, and each seat can serve at most one group. Return the maximum number of groups that can be assigned.

---

## Example 1

**Input**

```text
n = 3, reservedSeats = [[1,2],[1,3],[1,8],[2,6],[3,1],[3,10]]
```

**Output**

```text
4
```

**Explanation**

The optimal allocation assigns four groups using available seat blocks across the three rows.

---

## Example 2

**Input**

```text
n = 2, reservedSeats = [[2,1],[1,8],[2,6]]
```

**Output**

```text
2
```

---

## Example 3

**Input**

```text
n = 4, reservedSeats = [[4,3],[1,4],[4,6],[1,7]]
```

**Output**

```text
4
```

---

## Constraints

```text
1 <= n <= 10^9
1 <= reservedSeats.length <= min(10 * n, 10^4)
reservedSeats[i] == [rowi, seati]
1 <= rowi <= n and 1 <= seati <= 10
All entries in reservedSeats are distinct
```
---

# 💡 Idea

貪心 + Hash Map。關鍵觀察：只有有預訂座位的行才會影響分配，其他行都能放 2 個家庭（左區 2-5 和右區 6-9）。

大致流程：
1. 初始答案設為 `2 * n`（假設每行都能放 2 個）。
2. 用 hash map 存每行被預訂的座位。
3. 只對「有預訂座位的行」逐一檢查：
   - 檢查左區（2-5）是否有被預訂 → `left`
   - 檢查中區（4-7）是否有被預訂 → `mid`
   - 檢查右區（6-9）是否有被預訂 → `right`
   - 根據三個區間的可用性決定這行能放幾個家庭 `tn`
   - 從 `2 * n` 減去這行「無法放的家庭數」
4. 因為只需處理 m 行（有預訂的行），時間複雜度遠優於掃整個 n。

關鍵點：三個區間有部分重疊（中區與左、右都有重疊），所以最多只能選左+右（各 1 個）或中區（1 個），最少 0 個。

---

# 💻 Code

```cpp
class Solution {
public:
    int maxNumberOfFamilies(int n, vector<vector<int>>& reservedSeats) {
        int ans = 2 * n;
        int m = reservedSeats.size();
        unordered_map<int, vector<int>> mp{}; 

        int f, s;
        for (int i = 0; i < m; i++) {
            f = reservedSeats[i][0];
            s = reservedSeats[i][1];

            mp[f].push_back(s);
        }
        bool left, mid, right;
        for (auto [i, vec] : mp) {
            left  = true;
            mid   = true;
            right = true;

            for (auto k : vec) {
                if (k >= 2 && k <= 5) left = false;
                if (k >= 4 && k <= 5) {
                    left = false;
                    mid = false;
                }
                if (k >= 6 && k <= 7) {
                    right = false;
                    mid = false;
                }
                if (k >= 8 && k <= 9) right = false;
            }
            int tn = 2;
            if (left && right) tn = 0;
            else if (mid || right || left) tn = 1;

            ans -= tn;
        }

        return ans;
    }
};
```

---

# ⏱ Complexity

設 `m = reservedSeats.size()`。

| Complexity | Value |
|------------|-------|
| Time | O(M) |
| Space | O(M) |


---
