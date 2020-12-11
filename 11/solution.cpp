#include <iostream>
#include <string>
#include <vector>

using namespace std;

void print_map(vector<string> map) {
    for (auto row : map) {
        for (auto c : row) {
            cout << c;
        }
        cout << "\n";
    }

    cout << "\n";
}

int nb_neighbours(vector<string> map, int row, int col) {
    int pos[] = {-1, 0, 1};

    int height = map.size();
    int width = map[0].size();

    int neighbours = 0;

    for (auto i : pos) {
        for (auto j : pos) {
            if ((i != 0 || j != 0) && ((row + i) >= 0 && (row + i) < height &&
                                       (col + j) >= 0 && (col + j) < width)) {
                neighbours += map[row + i][col + j] == '#' ? 1 : 0;
            }
        }
    }

    return neighbours;
}

vector<string> next(vector<string> map, int &nb_changes) {
    vector<string> next_map(map);

    int width = map[0].length();
    int height = map.size();

    nb_changes = 0;

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            char prev = map[i][j];
            char &current = next_map[i][j];

            int neighbours = nb_neighbours(map, i, j);

            if (prev == 'L' && neighbours == 0) {
                nb_changes++;
                current = '#';
            } else if (prev == '#' && neighbours >= 4) {
                nb_changes++;
                current = 'L';
            }
        }
    }

    return next_map;
}

int count_seats(vector<string> map, char c) {
    int n = 0;
    for (auto m : map) {
        for (auto character : m) {
            n += character == c ? 1 : 0;
        }
    }

    return n;
}

int main() {
    string line;
    vector<string> map;

    while (cin >> line) {
        map.push_back(line);
    }

    int nb_changes = 0;
    vector<string> next_map(map);

    int nb_iter = 0;

    do {
        next_map = next(next_map, nb_changes);
        nb_iter++;
    } while (nb_changes != 0);

    print_map(next_map);

    int ans_first = count_seats(next_map, '#');

    cout << "Finished in " << nb_iter << endl;

    cout << ans_first << " is the answer (first part)" << endl;
}