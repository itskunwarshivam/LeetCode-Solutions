#include <vector>
#include <algorithm>

class Solution {
public:
    bool predictTheWinner(std::vector<int>& nums) {
        int n = nums.size();
        // If the array length is even, Player 1 can always win by choosing 
        // either all even-indexed elements or all odd-indexed elements.
        if (n % 2 == 0) return true;

        std::vector<int> dp = nums; // DP table for space-optimized 1D approach

        for (int len = 2; len <= n; ++len) {
            for (int i = 0; i <= n - len; ++i) {
                int j = i + len - 1;
                dp[i] = std::max(nums[i] - dp[i + 1], nums[j] - dp[i]);
            }
        }

        return dp[0] >= 0;
    }
};