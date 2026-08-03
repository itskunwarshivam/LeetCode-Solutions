#include <vector>
#include <string>
#include <algorithm>
#include <climits>

class Solution {
public:
    std::string stoneGameIII(std::vector<int>& stoneValue) {
        int n = stoneValue.size();
        std::vector<int> dp(n + 1, 0);

        for (int i = n - 1; i >= 0; --i) {
            dp[i] = INT_MIN;
            int current_sum = 0;
            
            // Try taking 1, 2, or 3 stones
            for (int k = 1; k <= 3 && i + k <= n; ++k) {
                current_sum += stoneValue[i + k - 1];
                dp[i] = std::max(dp[i], current_sum - dp[i + k]);
            }
        }

        if (dp[0] > 0) return "Alice";
        if (dp[0] < 0) return "Bob";
        return "Tie";
    }
};