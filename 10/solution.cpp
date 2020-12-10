#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() {
    vector<int> adapters = {0};

    int val;

    while (cin >> val) {
        adapters.push_back(val);
    }

    sort(adapters.begin(), adapters.end());
    adapters.push_back(adapters.back() + 3);

    // First part
    int diff_count[3] = {0, 0, 0};

    int prev = 0;  // The power outlet
    for (auto v : adapters) {
        int diff = v - prev;
        if (diff == 0) continue;

        diff_count[diff - 1]++;
        prev = v;
    }

    // Second part
    // Time Complexity : O(n) with memoized top-down approach :
    //      - the i-th adapter, has all the possible combination of all the
    //      adapters that it can be plugged to (so adapters that have a
    //      difference value of maximum 3)
    //
    // Space Complexity : O(n)

    vector<long long int> dp(adapters.size(), 0);
    dp.back() = 1;

    for (int i = dp.size() - 2; i >= 0; i--) {
        for (int j = 1; j < min((size_t)4, dp.size() - i); j++) {
            int diff = adapters[i + j] - adapters[i];

            if (diff <= 3) dp[i] += dp[i + j];
        }
    }

    printf("%d * %d = %d is the answer (first part)\n", diff_count[0],
           diff_count[2], diff_count[0] * diff_count[2]);
    printf("There is %lld possible combination (second part)\n", dp[0]);
}