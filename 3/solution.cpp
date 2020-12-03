#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() {
    vector<string> map;
    string line;

    // We don't care about first line here
    cin >> line;

    while (cin >> line) {
        map.push_back(line);
    }

    struct Slope {
        int right;
        int down;
        int cursor;
        int nb_trees;
    };

    Slope slopes[] = {
        {1, 1, 0, 0}, {3, 1, 0, 0}, {5, 1, 0, 0}, {7, 1, 0, 0}, {1, 2, 0, 0},
    };

    // Time Complexity : O(n) with n the number of lines
    // Space Complexity: O(1)

    int width = map[0].size();
    for (int i = 0; i < map.size(); i++) {
        for (auto &slope : slopes) {
            if ((i + 1) % slope.down != 0) {
                continue;
            }

            slope.cursor = (slope.cursor + slope.right) % width;

            if (map[i][slope.cursor] == '#') slope.nb_trees++;
        }
    }

    long long int answer = 1;
    for (auto slope : slopes) {
        cout << "Number of trees : " << slope.nb_trees << " (slope "
             << slope.right << "," << slope.down << ")" << endl;
        answer *= slope.nb_trees;
    }

    cout << "Answer : " << answer << endl;
}