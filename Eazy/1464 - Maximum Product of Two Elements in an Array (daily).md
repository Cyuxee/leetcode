# LeetCode #1464 - Maximum Product of Two Elements in an Array (daily)
 
LeetCode Link： [link](https://leetcode.com/problems/maximum-product-of-two-elements-in-an-array/description/)


- **Date**: 2026/07/27
- **Difficulty**: Easy
- **Topic**: Mid Level、Array、Sorting、Heap (Priority Queue)
- **Language**: C++
- **Status**:
  - [ ] First AC 
  - [X] Optimized
  - [ ] Review Completed

<!-- First AC: 當你第一次把這題寫過並成功 AC，就打勾。
Optimized: 代表你不是只有 AC，而是已經改成比較好的解法。
Review Completed: 代表你隔幾天重新寫一次，而且沒有看答案也能寫出來。 -->
---

# 🎯 Problem

Given the array of integers `nums`, you will choose two different indices `i` and `j` of that array.

Return the maximum value of

```text
(nums[i]-1)*(nums[j]-1)
```

---

## Example 1

**Input**

```text
nums = [3,4,5,2]
```

**Output**

```text
12
```

**Explanation**

If you choose the indices `i=1` and `j=2` (indexed from 0), you will get the maximum value, that is,

```text
(nums[1]-1)*(nums[2]-1) = (4-1)*(5-1) = 3*4 = 12
```

---

## Example 2

**Input**

```text
nums = [1,5,4,5]
```

**Output**

```text
16
```

**Explanation**

Choosing the indices `i=1` and `j=3` (indexed from 0), you will get the maximum value of

```text
(5-1)*(5-1) = 16
```

---

## Example 3

**Input**

```text
nums = [3,7]
```

**Output**

```text
12
```

---

## Constraints

```text
2 <= nums.length <= 500
1 <= nums[i] <= 10^3
```


---

# 💡 Idea

原本想太難了，其實只要每次都替換最小的那個，然後確保你維護的元素們有保持大小順序。
就像在維護一個大小為 2 的 max heap 一樣。每次插入都會捨棄掉最小的，然後 heapify，如此循環至遍歷完整個陣列。

---

# 💻 Code

```cpp
class Solution {
public:
    int maxProduct(vector<int>& nums) {
        int fir = 0;
        int sec = 0;
        int tmp;

        for (int i = 0; i < nums.size(); i++) {
            if (nums[i] > sec) {
                sec = nums[i];
            }

            tmp = fir + sec;
            fir = max(fir, sec);
            sec = tmp - fir;
        } 

        return (fir - 1) * (sec - 1);
    }
};
```

---

# ⏱ Complexity

| Complexity | Value |
|------------|-------|
| Time | O(N) |
| Space | O(1) |


---