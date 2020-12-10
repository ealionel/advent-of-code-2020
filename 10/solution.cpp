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

    printf("%d * %d = %d is the answer (first part)\n", diff_count[0],
           diff_count[2], diff_count[0] * diff_count[2]);
}