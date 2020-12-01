#include <iostream>
#include <unordered_map>
#include <vector>
using namespace std;

int main() {
    int year;
    vector<int> years;

    while (cin >> year) {
        years.push_back(year);
    }

    // First part

    unordered_map<int, int> complements;
    for (auto y : years) {
        complements[2020 - y] = y;
        if (complements.find(y) != complements.end()) {
            cout << y << " + " << complements[y] << " = 2020 !\n";
            cout << "Answer is : " << y * complements[y] << endl;

            break;
        }
    }

    // Second part

    for (auto t : years) {
        int target = 2020 - t;
        unordered_map<int, int> complements;

        for (auto y : years) {
            complements[target - y] = y;

            if (complements.find(y) != complements.end()) {
                cout << y << " + " << complements[y] << " + " << t
                     << " = 2020 !\n";
                cout << "Answer is : " << y * complements[y] * t << endl;

                return EXIT_SUCCESS;
            }
        }
    }

    return 0;
}