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
    int dir[] = {-1, 0, 1};

    int height = map.size();
    int width = map[0].size();

    int neighbours = 0;

    for (auto i : dir) {
        for (auto j : dir) {
            if ((i != 0 || j != 0) && ((row + i) >= 0 && (row + i) < height &&
                                       (col + j) >= 0 && (col + j) < width)) {
                neighbours += map[row + i][col + j] == '#' ? 1 : 0;
            }
        }
    }

    return neighbours;
}

void print_found(vector<char> found) {
    cout << "Found : ";
    for (auto c : found) {
        cout << c << " ";
    }
    cout << endl;
}

// Second part neighbours conditions
int nb_visible_occupied(vector<string> map, int row, int col) {
    int dir[] = {-1, 0, 1};

    int height = map.size();
    int width = map[0].size();

    vector<char> found(8, '_');
    int nb_found = 0;

    int distance = 1;

    while (nb_found < 8) {
        int k = 0;

        for (auto i : dir) {
            for (auto j : dir) {
                int i_pos = row + i * distance;
                int j_pos = col + j * distance;

                bool is_center = i == 0 && j == 0;
                bool is_in_boundary = (i_pos) >= 0 && (i_pos) < height &&
                                      (j_pos) >= 0 && (j_pos) < width;

                if (found[k] == '_' && !is_center) {
                    auto cell = map[i_pos][j_pos];

                    if (!is_in_boundary) {
                        found[k] = '+';
                        nb_found++;
                    } else {
                        if (cell != '.') {
                            found[k] = cell;
                            nb_found++;
                        }
                    }
                }

                if (!is_center) k++;
            }
        }
        // cout << endl;
        // print_found(found);

        distance++;
    }

    int visible = count(found.begin(), found.end(), '#');

    return visible;
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

vector<string> next_second(vector<string> map, int &nb_changes) {
    vector<string> next_map(map);

    int width = map[0].length();
    int height = map.size();

    nb_changes = 0;

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            char prev = map[i][j];
            char &current = next_map[i][j];

            int visible = nb_visible_occupied(map, i, j);

            if (prev == 'L' && visible == 0) {
                nb_changes++;
                current = '#';
            } else if (prev == '#' && visible >= 5) {
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

    // First part

    int nb_changes = 0;
    vector<string> map_first(map);
    int nb_iter = 0;

    do {
        map_first = next(map_first, nb_changes);
        nb_iter++;
    } while (nb_changes != 0);

    int ans_first = count_seats(map_first, '#');

    cout << "Finished in " << nb_iter << endl;
    cout << ans_first << " is the answer (first part)" << endl;

    // Second part

    vector<string> map_second(map);
    nb_iter = 0;
    nb_changes = 0;

    do {
        map_second = next_second(map_second, nb_changes);
        nb_iter++;
    } while (nb_changes != 0);

    int ans_second = count_seats(map_second, '#');

    cout << "Finished in " << nb_iter << endl;
    cout << ans_second << " is the answer (second part)" << endl;
}