class Solution {
public:
    int minimumPushes(string word) {
        int n = word.length();
        int ans = 0;
        
        for (int i = 0; i < n; i++) {
            // (i / 8) gives the zero-indexed layer:
            // 0..7   -> 1 push
            // 8..15  -> 2 pushes
            // 16..23 -> 3 pushes
            // 24..25 -> 4 pushes
            ans += (i / 8) + 1;
        }
        
        return ans;
    }
};