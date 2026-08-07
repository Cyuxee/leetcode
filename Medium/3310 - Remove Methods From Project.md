# LeetCode #3310 - Remove Methods From Project
 
LeetCode Link： [link](https://leetcode.com/problems/remove-methods-from-project/description/)


- **Date**: 2026/08/07
- **Difficulty**: Medium
- **Topic**: Staff、Depth-First Search、Breadth-First Search、Graph Theory
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

You are maintaining a project that has `n` methods numbered from `0` to `n - 1`.

You are given two integers `n` and `k`, and a 2D integer array `invocations`, where `invocations[i] = [ai, bi]` indicates that method `ai` invokes method `bi`.

There is a known bug in method `k`. Method `k`, along with any method invoked by it, either **directly** or **indirectly**, are considered **suspicious** and we aim to remove them.

A group of methods can only be removed if no method **outside** the group invokes any methods **within** it.

Return an array containing all the remaining methods after removing all the **suspicious** methods. You may return the answer in *any order*. If it is not possible to remove **all** the suspicious methods, **none** should be removed.

---

## Example 1

**Input**

```text
n = 4, k = 1, invocations = [[1,2],[0,1],[3,2]]
```

**Output**

```text
[0,1,2,3]
```

**Explanation**

Method 2 and method 1 are suspicious, but they are directly invoked by methods 3 and 0, which are not suspicious. We return all elements without removing anything.

---

## Example 2

**Input**

```text
n = 5, k = 0, invocations = [[1,2],[0,2],[0,1],[3,4]]
```

**Output**

```text
[3,4]
```

**Explanation**

Methods 0, 1, and 2 are suspicious and they are not directly invoked by any other method. We can remove them.

---

## Example 3

**Input**

```text
n = 3, k = 2, invocations = [[1,2],[0,1],[2,0]]
```

**Output**

```text
[]
```

**Explanation**

All methods are suspicious. We can remove them.

---

## Constraints

```text
1 <= n <= 10^5
0 <= k <= n - 1
0 <= invocations.length <= 2 * 10^5
invocations[i] == [ai, bi]
0 <= ai, bi <= n - 1
ai != bi
invocations[i] != invocations[j]
```

---

# 💡 Idea

因為節點的值是不重複的，所以先用 DFS 或 BFS 從 k (source) 把所有從源頭可以到達的點全部放到一個 set 裡面，這個 set 依照題目定義，就是有潛力被移除的 method 們。接著再將剩下的點每一個都做 DFS 或 BFS，只要有其中一個邊是可以到達該 set 裡面的其中一個點，代表有節點可以連進這個群組裡面，那就不能移除 set 中的 method 們，反之則全部留著。

---

# 💻 Code

```cpp
class Solution {
public:
    set<int> nodes;
    bool canRemove;

    void dfs_find_first_closure(int now, vector<vector<int>> &graph, vector<bool> &visited) {

        nodes.insert(now);

        for (int node : graph[now]) { 
            if (!visited[node]) {
                visited[node] = true;
                dfs_find_first_closure(node, graph, visited);
            }
        }

    }
    void dfs(int now, vector<vector<int>> &graph, vector<bool> &visited) {

        if (nodes.count(now) != 0) {
            canRemove = false;
            return;
        }

        for (int node : graph[now]) {
            if (!visited[node]) {
                visited[node] = true;
                dfs(node, graph, visited);
            }
        }

    }

    vector<int> remainingMethods(int n, int k, vector<vector<int>>& invocations) {
        vector<vector<int>> graph(n, vector<int>(0));
        vector<bool> visited(n, false);
        canRemove = true;

        for(auto edge : invocations)
            graph[edge[0]].push_back(edge[1]);
         

        dfs_find_first_closure(k, graph, visited);
 

        for (auto i : visited) i = false;

        for (int i = 0; i < n; i++) {
            if (!nodes.count(i)) {
                dfs(i, graph, visited);
            }
        }


        vector<int> result;

        if (canRemove) {
            for (int i = 0; i < n; i++) {
                if (!nodes.count(i)) {
                    result.push_back(i);
                }
            }
        } else {
            for (int i = 0; i < n; i++) {
                result.push_back(i);
            }
        }

        return result;
    }
};
```

---

# ⏱ Complexity

| Complexity | Value |
|------------|-------|
| Time | O(N) |
| Space | O(E) |


---