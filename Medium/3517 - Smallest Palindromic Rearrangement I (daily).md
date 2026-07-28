# LeetCode #3517 - Smallest Palindromic Rearrangement I (daily)
 
LeetCode Link： [link](https://leetcode.com/problems/maximum-product-of-two-elements-in-an-array/description/)


- **Date**: 2026/07/28
- **Difficulty**: Medium
- **Topic**: Senior、String、Sorting、Counting Sort
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

You are given a palindromic string `s`.

Return the lexicographically smallest palindromic permutation of `s`.

---

## Example 1

**Input**

```text
s = "z"
```

**Output**

```text
"z"
```

**Explanation**

A string of only one character is already the lexicographically smallest palindrome.

---

## Example 2

**Input**

```text
s = "babab"
```

**Output**

```text
"abbba"
```

**Explanation**

Rearranging `"babab"` → `"abbba"` gives the smallest lexicographic palindrome.

---

## Example 3

**Input**

```text
s = "daccad"
```

**Output**

```text
"acddca"
```

**Explanation**

Rearranging `"daccad"` → `"acddca"` gives the smallest lexicographic palindrome.

---

## Constraints

```text
1 <= s.length <= 10^5
s consists of lowercase English letters.
s is guaranteed to be palindromic.
```

---

# 💡 Idea

直覺作法就是把所有字元的數量都算出來，
因為題目保證輸入是回文，所以先把奇數個的字元先抓出來放最中間，
剩下偶數個的按最大到最小由內放到外。
做完後，發現記憶體開銷好大，時間上有用快速冪的技巧去加快字串生成，
但感覺還有地方可以加強。

---

# 💻 Code

```cpp
class Solution {
public:

    
    void fast_cat(string &tmp, int &num, char c) {
        string s = "";
        s += c;
        while (num) {
            if (num & 1) {
                tmp += s;
            }
            s += s;
            num >>= 1;
        }
    }

    string smallestPalindrome(string s) {
        vector<int> arr(26, 0);

        for (auto i : s) {
            arr[i - 'a']++;
        }

        string res = "";
        for (int i = 0; i < 26; i++) {
            if (arr[i] & 1) {
                res += ('a' + i);
                arr[i]--;
                break;
            }
        }

        
        for (int i = 25; i >= 0; i--) {
            string tmp = "";
            if (arr[i]) {
                arr[i] >>= 1;
                fast_cat(tmp, arr[i], 'a' + i);
                arr[i] = 0;
            }
            res = tmp + res + tmp;
        }
        return res;
    }
};
```

---

# ⏱ Complexity

| Complexity | Value |
|------------|-------|
| Time | O(N) |
| Space | O(N) |


---