#include <iostream>
#include <regex>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

// <rule> ::= <color> bags contain <number> <color> bags, <number> <color> bags,
// ...
pair<string, vector<pair<string, int>>> parse_rule(string line) {
    string token = " bags contain ";
    auto token_pos = line.find(token);

    string bag_color = string(line.begin(), line.begin() + token_pos);

    regex e("([0-9]+) ([a-z]+ [a-z]+) bag");

    auto words_begin =
        sregex_iterator(line.begin() + token_pos + token.size(), line.end(), e);
    auto words_end = sregex_iterator();

    vector<pair<string, int>> colors;

    for (auto i = words_begin; i != words_end; i++) {
        smatch match = *i;
        colors.push_back(make_pair(match.str(2), stoi(match.str(1))));
    }

    return make_pair(bag_color, colors);
}

// First part solution using depth first search (a node is visited only once)
int count_unique_bags_containing(
    string bag, unordered_map<string, vector<string>> contained_by,
    unordered_map<string, bool> &visited) {
    auto bags = contained_by[bag];

    visited[bag] = true;

    int sum = 0;

    for (auto b : bags) {
        if (!visited[b]) {
            sum += count_unique_bags_containing(b, contained_by, visited);
            sum++;
        }
    }

    return sum;
}

// Second part solution using depth first search
int count_bags(string bag,
               unordered_map<string, vector<pair<string, int>>> contains) {
    int count = 0;

    auto bags = contains[bag];

    for (auto b : bags) {
        int bags_count = b.second;
        count += bags_count + count_bags(b.first, contains) * bags_count;
    }

    return count;
}

int main() {
    string line;

    // Map representing the list of bags color (value) that contains a bag of
    // color (key)
    unordered_map<string, vector<string>> contained_by;
    unordered_map<string, bool> visited;

    // Hashtable representing the list of bags and their number (value) that
    // must contain a bag of color (key)
    unordered_map<string, vector<pair<string, int>>> contains;

    while (getline(cin, line)) {
        auto parsed = parse_rule(line);

        for (auto bag : parsed.second) {
            // First part map
            contained_by[bag.first].push_back(parsed.first);
            visited[bag.first] = false;

            // Second part map
            contains[parsed.first].push_back(bag);
        }
    }

    cout << count_unique_bags_containing("shiny gold", contained_by, visited)
         << " can contain shiny gold (first part)" << endl;
    cout << count_bags("shiny gold", contains)
         << " bags must be contained (second part)" << endl;
}