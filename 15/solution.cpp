#include <array>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

int main() {
    string tmp_str;

    unordered_map<int, int> memory;

    int val;
    int n = 0;

    while (getline(cin, tmp_str, ',')) {
        val = stoi(tmp_str);

        memory[val] = n++;
    }

    val = 0;

    int first_part;
    int second_part;

    int nth = 30000000;

    while (n != nth) {
        int tmp;
        if (memory.find(val) == memory.end()) {
            tmp = 0;
        } else {
            tmp = n - memory[val];
        }

        memory[val] = n++;

        if (n == 2020) first_part = val;
        if (n == 30000000) second_part = val;

        val = tmp;
    }

    cout << first_part << " (first part)" << endl;
    cout << second_part << " (second part)" << endl;
}