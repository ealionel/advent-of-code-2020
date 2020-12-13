#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

bool check_cond(unsigned long long int t, vector<pair<int, int>> buses) {
    // cout << endl;
    for (auto bus : buses) {
        // cout << "checking " << t + bus.second << endl;
        if ((t + bus.second) % bus.first != 0) {
            return false;
        }
    }

    return true;
}

int mod(int a, int b) { return (b + (a % b)) % b; }

int main() {
    string tmp;
    vector<pair<int, int>> bus;

    int depart;
    cin >> depart;

    int offset = 0;
    while (getline(cin, tmp, ',')) {
        if (tmp != "x") {
            bus.push_back(make_pair(stoi(tmp), offset));
        }

        offset++;
    }

    for (auto b : bus) {
        cout << b.first << " " << mod(b.first - b.second, b.first) << endl;
    }

    // First part
    // Time Complexity : O(n)
    // Space Complexity : O(1)

    int min_waiting_time = -1;
    int earliest_bus;

    for (auto b : bus) {
        int id = b.first;
        int waiting_time = id - depart % id;

        if (min_waiting_time == -1 || waiting_time < min_waiting_time) {
            min_waiting_time = waiting_time;
            earliest_bus = id;
        }
    }

    cout << "Earliest bus is " << earliest_bus << " and need to wait "
         << min_waiting_time << ". Answer is "
         << min_waiting_time * earliest_bus << endl;

    // Second part using chinese remainder theorem
}
