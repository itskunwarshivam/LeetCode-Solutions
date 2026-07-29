#include <string>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
private:
    // Global static Pascal's triangle table capped at 1,000,005
    static inline int C[5001][5001];
    static inline bool initialized = false;

    void initCombinations() {
        if (initialized) return;
        const int CAP = 1000005;
        for (int i = 0; i <= 5000; ++i) {
            C[i][0] = 1;
            for (int j = 1; j <= i; ++j) {
                C[i][j] = min(CAP, C[i - 1][j - 1] + C[i - 1][j]);
            }
        }
        initialized = true;
    }

    // Calculates total unique permutations for the given remaining character counts
    long long getPermutations(const vector<int>& count, int rem_len, int k) {
        long long total = 1;
        int n = rem_len;
        for (int freq : count) {
            if (freq == 0) continue;
            total *= C[n][freq];
            if (total > k) {
                return k + 1; // Cap at k + 1 to prevent overflow
            }
            n -= freq;
        }
        return total;
    }

public:
    string smallestPalindrome(string s, int k) {
        initCombinations();

        int n = s.length();
        vector<int> full_count(26, 0);
        for (char ch : s) {
            full_count[ch - 'a']++;
        }

        int half_len = n / 2;
        vector<int> half_count(26, 0);
        string mid = "";

        // Halve character frequencies for the first half
        for (int i = 0; i < 26; ++i) {
            half_count[i] = full_count[i] / 2;
            if (full_count[i] % 2 != 0) {
                mid += (char)('a' + i);
            }
        }

        // Check if there are at least k permutations in total
        if (getPermutations(half_count, half_len, k) < k) {
            return "";
        }

        string half_s = "";
        int rem_len = half_len;

        // Construct the first half lexicographically
        for (int i = 0; i < half_len; ++i) {
            for (int c = 0; c < 26; ++c) {
                if (half_count[c] == 0) continue;

                // Temporarily place char 'a' + c
                half_count[c]--;
                long long perms = getPermutations(half_count, rem_len - 1, k);

                if (perms >= k) {
                    // Pick this character and proceed
                    half_s += (char)('a' + c);
                    rem_len--;
                    break;
                } else {
                    // Skip these permutations
                    k -= perms;
                    half_count[c]++; // Backtrack and try next character
                }
            }
        }

        // Construct full palindromic string
        string rev_half = half_s;
        reverse(rev_half.begin(), rev_half.end());

        return half_s + mid + rev_half;
    }
};