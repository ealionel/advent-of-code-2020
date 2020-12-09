#include <deque>
#include <iostream>
#include <regex>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

#define PREV_SIZE 25

int main() {
    string line;

    deque<int> previous;

    vector<int> input;

    int cnt = 0;

    for (int i = 0; i < PREV_SIZE; i++) {
        cin >> line;
        previous.push_back(stoi(line));
        cnt++;
    }

    int target;

    // First part
    // Time Complexity : O(n * W) = O(n) with n the number of numbers, and W the
    // size of the previous window Space Complexity : O(W) = O(1);

    while (cin >> line) {
        cnt++;
        unordered_map<int, int> complements;
        int current = stoi(line);
        bool found_pair = false;

        input.push_back(current);

        for (auto p : previous) {
            complements[current - p] = p;

            if (complements.find(p) != complements.end()) {
                found_pair = true;
                break;
            }
        }

        if (!found_pair) {
            target = current;
            printf("%d is not the sum of any previous %d values. (line %d) \n",
                   current, PREV_SIZE, cnt + 1);
            break;
        }

        previous.pop_front();
        previous.push_back(current);
    }

    // Second part
    // Time Complexity : O(n) one traversal with double pointer
    // Space Complexity : O(1) for finding the subarray that sums to target
    //                    O(n) for finding the maximum of that subarray

    int start_cursor = 0;
    int end_cursor = 0;
    int sum = 0;

    deque<int> set;

    while (end_cursor < input.size()) {
        int current = input[end_cursor];

        if (sum + current > target) {
            sum -= input[start_cursor];
            set.pop_front();
            start_cursor++;
        } else {
            set.push_back(current);
            sum += current;
            end_cursor++;
        }

        if (sum == target) {
            printf("Sum of value in indexes [%d, %d] = %d (answer is %d)\n",
                   start_cursor, end_cursor, target,
                   *max_element(set.begin(), set.end()) +
                       *min_element(set.begin(), set.end()));
            break;
        }
    }
}