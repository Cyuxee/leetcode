# LeetCode #307 - Range Sum Query - Mutable

LeetCode Link： [link](https://leetcode.com/problems/range-sum-query-mutable/description/)


- **Date**: 2026/08/16
- **Difficulty**: Medium
- **Topic**: Array、Design、Binary Indexed Tree、Segment Tree
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

Given an integer array `nums`, handle multiple queries of the following types:

1. **Update** the value of an element in `nums`.
2. Calculate the **sum** of the elements of `nums` between indices `left` and `right` inclusive where `left <= right`.

Implement the `NumArray` class:

`NumArray(int[] nums)` Initializes the object with the integer array `nums`.

`void update(int index, int val)` Updates the value of `nums[index]` to be `val`.

`int sumRange(int left, int right)` Returns the sum of the elements of `nums` between indices `left` and `right` inclusive (i.e. `nums[left] + nums[left + 1] + ... + nums[right]`).

---

## Example 1

**Input**

```text
["NumArray", "sumRange", "update", "sumRange"]
[[[1, 3, 5]], [0, 2], [1, 2], [0, 2]]
```

**Output**

```text
[null, 9, null, 8]
```

**Explanation**

```text
NumArray numArray = new NumArray([1, 3, 5]);
numArray.sumRange(0, 2); // return 1 + 3 + 5 = 9
numArray.update(1, 2);   // nums = [1, 2, 5]
numArray.sumRange(0, 2); // return 1 + 2 + 5 = 8
```

---

## Constraints

```text
1 <= nums.length <= 3 * 10^4
-100 <= nums[i] <= 100
0 <= index < nums.length
-100 <= val <= 100
0 <= left <= right < nums.length
At most 3 * 10^4 calls will be made to update and sumRange.
```
---

# 💡 Idea

有 update 的區間和，前綴和不行（改一個值要重建 O(n)），改用**線段樹 (Segment Tree)**。

核心想法：每個樹節點存一段區間 `[start, end]` 的總和，節點 `n` 的左右子樹是 `2n` 與 `2n+1`。

- **build**：遞迴往下切一半，葉子 (`start == end`) 存 `nums[start]`，回傳時把左右子樹相加存回父節點。
- **query(L, R)**：三種情況
  - 節點區間和 `[L, R]` 完全不重疊 → 回 0
  - 節點區間完全被 `[L, R]` 包含 → 直接回 `tree[n]`
  - 部分重疊 → 往左右子樹遞迴再相加
- **update(index, val)**：往下找到那個葉子改值，回程時 `tree[n] = 左 + 右` 更新沿路父節點。

tree 陣列大小：遞迴用 `2n / 2n+1` 定址，最大 index 約 `2 * 次冪(n)`。n 最大 30000，次冪 = 32768，`2 * 32768 = 65536 < 100005`，所以開 `tree[100005]` 夠用。（保險可以直接開 `4 * n`。）

小提醒：`size = nums.size() - 1` 存的是「最後一個 index」，之後 build / query / update 都用 `0 ~ size` 這個閉區間，前後要一致。

---

# 💻 Code

```cpp
class NumArray {
public:
    int tree[100005];
    int size;
    NumArray(vector<int>& nums) {
        size = nums.size() - 1;
        build_tree(nums, 0, size, 1);
    }
    int build_tree(vector<int>& nums, int start, int end, int n) {
        if (start == end) {
            tree[n] = nums[start];
            return tree[n];
        }
        int mid = (start + end) / 2;
        int left = build_tree(nums, start, mid, 2 * n);
        int right = build_tree(nums, mid + 1, end, 2 * n + 1);
        return tree[n] = (left + right);
    }
    int query(int start, int end, int L, int R, int n) {
        if (start > R || end < L) return 0;
        if (start >= L && end <= R) return tree[n];

        int mid = (start + end) / 2;
        int left = query(start, mid, L, R, 2 * n);
        int right = query(mid + 1, end, L, R, 2 * n + 1);

        return left + right;
    }
    void modify(int start, int end, int index, int val, int n) {
        if (index > end || index < start) return;
        if (start == end) {
            tree[n] = val;
            return;
        }
        
        int mid = (start + end) / 2;
        modify(start, mid, index, val, 2 * n);
        modify(mid + 1, end, index, val, 2 * n + 1);
        tree[n] = tree[2 * n] + tree[2 * n + 1];
    }
    void update(int index, int val) {
        modify(0, size, index, val, 1);
    }
    
    int sumRange(int left, int right) {
        return query(0, size, left, right, 1);
    }
};

/**
 * Your NumArray object will be instantiated and called as such:
 * NumArray* obj = new NumArray(nums);
 * obj->update(index,val);
 * int param_2 = obj->sumRange(left,right);
 */
```

---

# ⏱ Complexity

| Operation | Time | Space |
|-----------|------|-------|
| build (constructor) | O(N) | O(N) |
| update | O(log N) | - |
| sumRange | O(log N) | - |


---
