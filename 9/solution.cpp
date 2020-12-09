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

    int cnt = 0;

    for (int i = 0; i < PREV_SIZE; i++) {
        cin >> line;
        previous.push_back(stoi(line));
        cnt++;
    }

    while (cin >> line) {
        cnt++;
        unordered_map<int, int> complements;
        int current = stoi(line);
        bool found_pair = false;

        for (auto p : previous) {
            complements[current - p] = p;

            if (complements.find(p) != complements.end()) {
                found_pair = true;
            }
        }

        if (!found_pair) {
            printf("%d is not the sum of any previous %d values. (line %d) \n",
                   current, PREV_SIZE, cnt + 1);
            break;
        }

        previous.pop_front();
        previous.push_back(current);
    }
}