# LeetCode #455 - Assign Cookies

LeetCode Link： [link](https://leetcode.com/problems/assign-cookies/description/)


- **Date**: 2026/08/16
- **Difficulty**: Easy
- **Topic**: Array、Two Pointers、Greedy、Sorting
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

Assume you are an awesome parent and want to give your children some cookies. But, you should give each child at most one cookie.

Each child `i` has a greed factor `g[i]`, which is the minimum size of a cookie that the child will be content with; and each cookie `j` has a size `s[j]`. If `s[j] >= g[i]`, we can assign the cookie `j` to the child `i`, and the child `i` will be content. Your goal is to maximize the number of your content children and output the maximum number.

---

## Example 1

**Input**

```text
g = [1,2,3], s = [1,1]
```

**Output**

```text
1
```

**Explanation**

You have 3 children and 2 cookies. The greed factors of 3 children are 1, 2, 3.
And even though you have 2 cookies, since their size is both 1, you could only make the child whose greed factor is 1 content.
You need to output 1.

---

## Example 2

**Input**

```text
g = [1,2], s = [1,2,3]
```

**Output**

```text
2
```

**Explanation**

You have 2 children and 3 cookies. The greed factors of 2 children are 1, 2.
You have 3 cookies and their sizes are big enough to gratify all of the children,
You need to output 2.

---

## Constraints

```text
1 <= g.length <= 3 * 10^4
0 <= s.length <= 3 * 10^4
1 <= g[i], s[j] <= 2^31 - 1
```
---

# 💡 Idea

貪心 + 雙指標。把小孩的貪婪度 `g` 和餅乾大小 `s` 都由小到大排序，然後從最小的餅乾開始，優先餵給需求最低的小孩。

技巧：這裡 `ans` 一物兩用 —— 既是「已滿足的小孩數」，同時也是「下一個要嘗試滿足的小孩 index」（因為 `g` 排序過，第 `ans` 個就是目前還沒滿足、需求最小的小孩）。

- 用 `i` 掃每一塊餅乾（由小到大）。
- 只要當前餅乾 `s[i] >= g[ans]`，就把它配給這個小孩，`ans++`。
- 配不上的餅乾（太小）就跳過，換下一塊更大的。
- 迴圈條件 `ans < g.size()` 代表所有小孩都滿足就提早結束。

因為兩邊都排序、每次都用「剛好夠用的最小餅乾」去滿足「需求最小的小孩」，不會浪費大餅乾，能滿足的人數最多。

---

# 💻 Code

```cpp
class Solution {
public:
    int findContentChildren(vector<int>& g, vector<int>& s) {
        sort(s.begin(), s.end());
        sort(g.begin(), g.end());
        int ans = 0;
        for (int i = 0; ans < g.size() && i < s.size(); i++) {
            if (s[i] >= g[ans]) {
                ans++;
            }
        }
        return ans;
    }
};
```

---

# ⏱ Complexity

設 `n = g.size()`、`m = s.size()`。

| Complexity | Value |
|------------|-------|
| Time | O(N log N + M log M) |
| Space | O(1) |


---
