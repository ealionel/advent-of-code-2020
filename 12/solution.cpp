#include <array>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

enum Direction {
    EAST = 0,
    SOUTH = 1,
    WEST = 2,
    NORTH = 3,
    FORWARD = 4,
    LEFT = 5,
    RIGHT = 6,
};

unordered_map<char, Direction> dir_mapping = {
    {'E', EAST},    {'S', SOUTH}, {'W', WEST}, {'N', NORTH},
    {'F', FORWARD}, {'L', LEFT},  {'R', RIGHT}};

struct ShipState {
    int pos[2] = {0, 0};  // X, Y;
    Direction pointing = EAST;
};

array<array<int, 2>, 4> dir_arr = {{
    {1, 0},
    {0, -1},
    {-1, 0},
    {0, 1},
}};

pair<Direction, int> parse_instruction(string instruction) {
    Direction dir = dir_mapping[instruction[0]];

    int val = stoi(string(instruction.begin() + 1, instruction.end()));

    return make_pair(dir, val);
}

int modulo(int a, int b) { return (b + (a % b)) % b; }

void rotate_ship(ShipState &ship, Direction rot, int val) {
    int nb_rotations = val / 90;

    ship.pointing = (Direction)modulo(
        ship.pointing + (rot == LEFT ? -1 : 1) * nb_rotations, 4);
}

void move_ship(ShipState &ship, Direction dir, int val) {
    array<int, 2> moves =
        dir == FORWARD ? dir_arr[ship.pointing] : dir_arr[dir];

    ship.pos[0] += moves[0] * val;
    ship.pos[1] += moves[1] * val;
}

void move_ship_second(ShipState &ship, Direction dir, int val) {}

void print_ship(ShipState ship) {
    printf("EAST: %d, NORTH: %d, POINTING: %d\n", ship.pos[0], ship.pos[1],
           ship.pointing);
}

int main() {
    string line;

    ShipState ship;

    print_ship(ship);

    while (cin >> line) {
        auto parsed = parse_instruction(line);

        Direction cmd = parsed.first;
        int val = parsed.second;

        if (cmd == LEFT || cmd == RIGHT) {
            rotate_ship(ship, cmd, val);
        } else {
            move_ship(ship, cmd, val);
        }
        cout << line << "\t";
        print_ship(ship);
    }

    cout << "Solution is " << abs(ship.pos[0]) + abs(ship.pos[1]) << endl;
}