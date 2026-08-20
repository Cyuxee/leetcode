# LeetCode #3069 - Distribute Elements Into Two Arrays I

LeetCode Link： [link](https://leetcode.com/problems/distribute-elements-into-two-arrays-i/description/)


- **Date**: 2026/08/20
- **Difficulty**: Easy
- **Topic**: Array、Simulation
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

Given a 1-indexed array of distinct integers `nums`, distribute all elements between two arrays `arr1` and `arr2` using `n` operations, where `n` is the length of `nums`.

**Distribution Rules:**
- Start by putting `nums[1]` into `arr1` and `nums[2]` into `arr2`.
- For each element `nums[i]` where `i >= 3`:
  - If the last element of `arr1` is **greater** than the last element of `arr2`, append `nums[i]` to `arr1`.
  - Otherwise, append `nums[i]` to `arr2`.

Return the resulting array by concatenating `arr1` and `arr2`.

---

## Example 1

**Input**

```text
nums = [2,1,3]
```

**Output**

```text
[2,3,1]
```

**Explanation**

Initially, arr1 = [2] and arr2 = [1].
Since arr1's last element (2) > arr2's last element (1), append nums[2] = 3 to arr1.
arr1 = [2, 3], arr2 = [1].
Concatenate to get [2, 3, 1].

---

## Example 2

**Input**

```text
nums = [5,4,3,8]
```

**Output**

```text
[5,3,4,8]
```

**Explanation**

Initially, arr1 = [5] and arr2 = [4].
Since 5 > 4, append 3 → arr1 = [5, 3].
Since 4 > 3, append 8 → arr2 = [4, 8].
Result: [5, 3, 4, 8].

---

## Constraints

```text
3 <= n <= 50
1 <= nums[i] <= 100
All elements in nums are distinct
```
---

# 💡 Idea

模擬過程。用兩個向量分別存 arr1 和 arr2，從第 3 個元素開始逐個加入。每次比較兩個陣列的最後一個元素（`.back()`），根據大小關係決定要加到哪一邊。

步驟簡單直接：初始化→掃 nums→判斷→加入→合併。因為 n ≤ 50，效率沒問題。

---

# 💻 Code

```cpp
class Solution {
public:
    vector<int> resultArray(vector<int>& nums) {
        vector<int> ans;
        vector<vector<int>> vec(2, vector<int>());
        vec[0].push_back(nums[0]);
        vec[1].push_back(nums[1]);
        for (int i = 2; i < nums.size(); i++) {
            if (vec[0].back() > vec[1].back())
                vec[0].push_back(nums[i]);
            else
                vec[1].push_back(nums[i]); 
        }
        for (int i = 0; i < vec[0].size(); i++) {
            ans.push_back(vec[0][i]);
        }
        
        for (int i = 0; i < vec[1].size(); i++) {
            ans.push_back(vec[1][i]);
        }
        return ans;
    }
};
```

---

# ⏱ Complexity

設 `n = nums.size()`。

| Complexity | Value |
|------------|-------|
| Time | O(N) |
| Space | O(N) |


---
