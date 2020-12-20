#include <deque>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

typedef deque<deque<string>> space;

template <typename T>
void print_space(T space) {
    // cout << "size" << space.size() << endl;
    for (int z = 0; z < space.size(); z++) {
        cout << "z = " << z << endl;

        for (int y = 0; y < space[z].size(); y++) {
            for (int x = 0; x < space[z][y].size(); x++) {
                cout << space[z][y][x] << " ";
            }
            cout << endl;
        }
    }

    cout << endl;
}

vector<int> make_neighbours_row(string row, char char_comp) {
    vector<int> vec;

    for (int i = 0; i < row.size(); i++) {
        int v = 0;

        if (i != 0) v += row[i - 1] == char_comp ? 1 : 0;
        if (i != row.size() - 1) v += row[i + 1] == char_comp ? 1 : 0;

        vec.push_back(v);
    }

    return vec;
}

vector<vector<int>> make_neighbours_plan(deque<string> slice, char char_comp) {
    vector<vector<int>> neighbours;

    for (auto v : slice) {
        neighbours.push_back(make_neighbours_row(v, char_comp));
    }

    for (int i = 0; i < neighbours.size(); i++) {
        for (int j = 0; j < neighbours[i].size(); j++) {
            if (i != 0) {
                neighbours[i][j] += neighbours[i - 1][j];
            }

            if (i != neighbours.size() - 1) {
                neighbours[i][j] += neighbours[i + 1][j];
            }
        }
    }

    return neighbours;
}

vector<vector<vector<int>>> make_neighbours_space(space space, char char_comp) {
    vector<vector<vector<int>>> neighbours;

    for (auto s : space) {
        neighbours.push_back(make_neighbours_plan(s, char_comp));
    }

    for (int z = 0; z < neighbours.size(); z++) {
        for (int y = 0; y < neighbours[z].size(); y++) {
            for (int x = 0; x < neighbours[z][y].size(); x++) {
                cout << neighbours[z][y][x] << " ";
                if (z != 0) {
                    neighbours[z][y][x] += neighbours[z - 1][y][x];
                }

                if (z != neighbours.size() - 1) {
                    neighbours[z][y][x] += neighbours[z + 1][y][x];
                }
            }
            cout << endl;
        }
        cout << endl;
    }

    return neighbours;
}

space expand_space(space current) {
    deque<string> empty(current[0].size(), string(current[0][0].size(), '.'));

    current.push_back(empty);
    current.push_front(empty);

    for (auto &col : current) {
        int col_size = col.size();

        col.push_front(string(col_size, '.'));
        col.push_back(string(col_size, '.'));
    }

    for (auto &col : current) {
        for (auto &row : col) {
            row = '.' + row + '.';
        }
    }

    return current;
}

space neighbours_to_space(space space, vector<vector<vector<int>>> neighbours) {
    // space space = deque(
    //     neighbours.size(),
    //     deque(neighbours[0].size(), string(neighbours[0][0].size(), '.')));

    for (int z = 0; z < space.size(); z++) {
        for (int y = 0; y < space[z].size(); y++) {
            for (int x = 0; x < space[z][y].size(); x++) {
                char &current = space[z][y][x];
                char current_neighbours = neighbours[z][y][x];

                if (current == '#' && current_neighbours < 2 &&
                    current_neighbours > 3) {
                    current = '.';
                } else if (current == '.' && current_neighbours == 3) {
                    current = '#';
                }
            }
        }
    }

    return space;
}

space next_state(space current, char active_char = '#') {
    space expanded = expand_space(current);

    auto neighbours = make_neighbours_space(expanded, active_char);

    print_space(neighbours);

    auto new_state = neighbours_to_space(expanded, neighbours);

    return new_state;
}

space iterate(space space, int iterations) {
    print_space(space);
    for (int i = 0; i < iterations; i++) {
        space = next_state(space);
        cout << "After " << i + 1 << " cycles:" << endl;
        print_space(space);
    }

    return space;
}

int main() {
    string line;

    // map[z][y][x]
    space map(1, deque<string>({}));

    while (cin >> line) {
        map.front().push_back(line);
    }

    // auto m2 = expand_space(map);

    // print_space(m2);

    iterate(map, 1);
}