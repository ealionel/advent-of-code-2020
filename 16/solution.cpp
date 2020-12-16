#include <array>
#include <iostream>
#include <regex>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

// departure location: 49-848 or 871-949
// departure station: 33-670 or 687-969
// departure platform: 41-909 or 916-974
// departure track: 40-397 or 422-972
// departure date: 31-481 or 505-960
// departure time: 37-299 or 312-965

pair<string, vector<pair<int, int>>> parse_rule(string rule) {
    regex e("^([a-z ]+): ([0-9]+)-([0-9]+) or ([0-9]+)-([0-9]+)$");
    vector<pair<int, int>> ranges;

    smatch match;
    regex_search(rule, match, e);

    string field = match.str(1);

    ranges.push_back(make_pair(stoi(match.str(2)), stoi(match.str(3))));
    ranges.push_back(make_pair(stoi(match.str(4)), stoi(match.str(5))));

    return make_pair(field, ranges);
}

bool in_range(int val, pair<int, int> range) {
    return val >= range.first && val <= range.second;
}

int main() {
    string line;

    unordered_map<string, vector<pair<int, int>>> field_rules;

    while (getline(cin, line) && line.size() != 0) {
        // cout << line << endl;
        auto r = parse_rule(line);

        field_rules[r.first] = r.second;
    }

    vector<int> my_tickets;

    getline(cin, line);
    getline(cin, line);

    istringstream ss(line);
    string tickets;

    while (getline(ss, tickets, ',')) {
        my_tickets.push_back(stoi(tickets));
    }

    getline(cin, line);
    getline(cin, line);
    vector<int> nearby_tickets;

    while (getline(cin, line)) {
        istringstream ss(line);
        while (getline(ss, tickets, ',')) {
            nearby_tickets.push_back(stoi(tickets));
        }
    }

    long int sum = 0;

    // First part

    for (auto ticket : nearby_tickets) {
        for (auto f : field_rules) {
            for (auto range : f.second) {
                if (in_range(ticket, range)) goto out;
            }
        }

        sum += ticket;

    out:;
    }

    cout << sum << " (first part)" << endl;
}