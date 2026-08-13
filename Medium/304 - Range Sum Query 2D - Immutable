# LeetCode #304 - Range Sum Query 2D - Immutable

LeetCode Link： [link](https://leetcode.com/problems/range-sum-query-2d-immutable/description/)


- **Date**: 2026/08/07
- **Difficulty**: Medium
- **Topic**: Array、Design、Matrix、Prefix Sum
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

Given a 2D matrix `matrix`, handle multiple queries of the following type:

Calculate the sum of the elements of `matrix` inside the rectangle defined by its upper left corner (`row1`, `col1`) and lower right corner (`row2`, `col2`).

Implement the NumMatrix class:

`NumMatrix(int[][] matrix)` Initializes the object with the integer matrix `matrix`.

`int sumRegion(int row1, int col1, int row2, int col2)` Returns the sum of the elements of `matrix` inside the rectangle defined by its upper left corner (`row1`, `col1`) and lower right corner (`row2`, `col2`).

You must design an algorithm where `sumRegion` works on O(1) time complexity.

---

## Example 1

**Input**

```text
["NumMatrix", "sumRegion", "sumRegion", "sumRegion"]
[[[[3, 0, 1, 4, 2], [5, 6, 3, 2, 1], [1, 2, 0, 1, 5], [4, 1, 0, 1, 7], [1, 0, 3, 0, 5]]], [2, 1, 4, 3], [1, 1, 2, 2], [1, 2, 2, 4]]
```

**Output**

```text
[null, 8, 11, 12]
```

**Explanation**

`NumMatrix numMatrix = new NumMatrix([[3, 0, 1, 4, 2], [5, 6, 3, 2, 1], [1, 2, 0, 1, 5], [4, 1, 0, 1, 7], [1, 0, 3, 0, 5]]);`

`numMatrix.sumRegion(2, 1, 4, 3); // return 8 (i.e sum of the red rectangle)`

`numMatrix.sumRegion(1, 1, 2, 2); // return 11 (i.e sum of the green rectangle)`

`numMatrix.sumRegion(1, 2, 2, 4); // return 12 (i.e sum of the blue rectangle)`

---

## Constraints

```text
m == matrix.length
n == matrix[i].length
1 <= m, n <= 200
-104 <= matrix[i][j] <= 104
0 <= row1 <= row2 < m
0 <= col1 <= col2 < n
At most 104 calls will be made to sumRegion.
```
---

# 💡 Idea

前綴和，後面算面積的部分，推一下公式就好，用 (1, 1) 當初始座標會比較好做。

---

# 💻 Code

```cpp
class NumMatrix {
public:
    vector<vector<int>> prefix;
    NumMatrix(vector<vector<int>>& matrix) {
        int m = matrix.size();
        int n = matrix[0].size();
        prefix = vector<vector<int>>(m + 1, vector<int>(n + 1, 0));
        
        for (int i = 1; i <= m; i++) {
            for (int j = 1; j <= n; j++) {
                prefix[i][j] = prefix[i][j - 1] + matrix[i - 1][j - 1];
            }
        }
        for (int i = 1; i <= m; i++) {
            for (int j = 1; j <= n; j++) {
                prefix[i][j] += (prefix[i - 1][j]);
            }
        }
    }
    //init: (0, 0) ~ (m, 0) == 0
    //init: (0, 0) ~ (0, n) == 0
    //cord of prefix sum table : (1, 1) -> (m + 1, n + 1)
    //start from (r1, c1) : prefix[r2 + 1][c2 + 1] - prefix[r1][c2 + 1] - prefix[r2 + 1][c1] + prefix[r1][c1];
    //(1, 1) -> (3, 3)
    // prefix[4][4] - prefix[1][4] - prefix[4][1] + prefix[1][1]
    
    
    int sumRegion(int row1, int col1, int row2, int col2) {

        return prefix[row2 + 1][col2 + 1] - prefix[row1][col2 + 1] - prefix[row2 + 1][col1] + prefix[row1][col1];
    }
};

/**
 * Your NumMatrix object will be instantiated and called as such:
 * NumMatrix* obj = new NumMatrix(matrix);
 * int param_1 = obj->sumRegion(row1,col1,row2,col2);
 */
```

---

# ⏱ Complexity

| Complexity | Value |
|------------|-------|
| Time | O(N^2) |
| Space | O(N^2) |


---