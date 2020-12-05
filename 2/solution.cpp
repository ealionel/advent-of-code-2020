#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

std::vector<std::string> split(const std::string& s, char delimiter) {
    std::vector<std::string> tokens;
    std::string token;
    std::istringstream tokenStream(s);
    while (std::getline(tokenStream, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
}

int main() {
    vector<string> input;
    string tmp;

    int nb_valid = 0;
    int nb_valid_second = 0;

    while (cin >> tmp) {
        auto s = split(tmp, '-');
        int min = stoi(s[0]);
        int max = stoi(s[1]);

        cin >> tmp;
        char letter = tmp[0];

        unordered_map<char, int> occurence;
        cin >> tmp;

        // First part
        // Time Complexity : O(n)
        //      One traversal to populate the hash table = O(n)
        //      Letter lookup in hash table = O(1)
        //      O(n) + O(1) = O(n)

        // Space Complexity : O(1) (the hashmap contains at most 26 entries)

        for (auto c : tmp) {
            if (occurence.find(c) == occurence.end()) {
                occurence[c] = 1;
            } else {
                occurence[c]++;
            }
        }

        if (occurence.find(letter) != occurence.end() &&
            occurence[letter] >= min && occurence[letter] <= max) {
            nb_valid++;
        }

        // Second part
        // Time Complexity : O(1)
        // Space Complexity : O(1)

        bool a = tmp.size() >= min && tmp[min - 1] == letter;
        bool b = tmp.size() >= max && tmp[max - 1] == letter;

        if (a ^ b) {
            nb_valid_second++;
        }
    }

    cout << nb_valid << " valid strings (part 1)" << endl;
    cout << nb_valid_second << " valid strings (part 2)" << endl;
}