// Given an integer array nums, find three numbers whose product is maximum and return the maximum product.


// Example 1:

// Input: nums = [1,2,3]
// Output: 6
// Example 2:

// Input: nums = [1,2,3,4]
// Output: 24
// Example 3:

// Input: nums = [-1,-2,-3]
// Output: -6
 

// Constraints:

// 3 <= nums.length <= 104
// -1000 <= nums[i] <= 1000


// 這題暴力解 O(N^3) 過不了。
// 所以思路是先拆成正負數各一邊，並對各自做排序後，
// 再考慮正負數要各拿幾個才會使得三個數乘積最大。

class Solution {
public:
    int maximumProduct(vector<int>& nums) {
        
        // Time Complexity : O(NlgN) 
        // Space Complexity : O(N)

        if (nums.size() == 3) return nums[0] * nums[1] * nums[2];

        vector<int> pos{};
        vector<int> neg{};
        for (auto i : nums) {
            if (i >= 0) {
                pos.push_back(i);
            } else {
                neg.push_back(i);
            }
        }
        sort(pos.begin(), pos.end(), greater<int>());
        sort(neg.begin(), neg.end());

        
        if (pos.size() == 0) {
            int n = neg.size();

            return neg[n - 1] * neg[n - 2] * neg[n - 3];
        }
        if (pos.size() == 1) {
            return pos[0] * neg[0] * neg[1];
        }
        if (pos.size() == 2) {
            return pos[0] * neg[0] * neg[1];
        }
            
        int res = pos[0] * pos[1] * pos[2];

        if (neg.size() >= 2) {
            res = max(res, neg[0] * neg[1] * pos[0]);
        }

        return res;
        
    }
};
