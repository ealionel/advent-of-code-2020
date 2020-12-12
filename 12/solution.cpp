#include <array>
#include <cmath>
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
    int waypoint_pos[2] = {10, 1};
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

void move_waypoint(ShipState &ship, Direction dir, int val) {
    auto moves = dir_arr[dir];

    ship.waypoint_pos[0] += moves[0] * val;
    ship.waypoint_pos[1] += moves[1] * val;
}

void rotate_waypoint(ShipState &ship, Direction dir, int val) {
    int nb_rotations = val / 90;

    int rot_dir = (dir == LEFT ? -1 : 1) * (nb_rotations == 3 ? -1 : 1);

    if (nb_rotations == 2) {
        ship.waypoint_pos[0] *= -1;
        ship.waypoint_pos[1] *= -1;
    } else {
        int prev[2] = {ship.waypoint_pos[0], ship.waypoint_pos[1]};
        ship.waypoint_pos[0] = prev[1] * rot_dir;
        ship.waypoint_pos[1] = -prev[0] * rot_dir;
    }
}

void move_forward(ShipState &ship, int val) {
    ship.pos[0] += ship.waypoint_pos[0] * val;
    ship.pos[1] += ship.waypoint_pos[1] * val;
}

void print_ship(ShipState ship) {
    printf("EAST: %d, NORTH: %d, POINTING: %d, WAYPOINT: (%d, %d) \n",
           ship.pos[0], ship.pos[1], ship.pointing, ship.waypoint_pos[0],
           ship.waypoint_pos[1]);
}

int main() {
    string line;

    ShipState ship;
    ShipState second_ship;

    // print_ship(ship);

    while (cin >> line) {
        auto parsed = parse_instruction(line);

        cout << line << "\t";
        Direction cmd = parsed.first;
        int val = parsed.second;

        if (cmd == LEFT || cmd == RIGHT) {
            rotate_ship(ship, cmd, val);
            rotate_waypoint(second_ship, cmd, val);
        } else {
            move_ship(ship, cmd, val);

            if (cmd == FORWARD) {
                move_forward(second_ship, val);
            } else {
                move_waypoint(second_ship, cmd, val);
            }
        }
        print_ship(second_ship);
    }

    cout << "Solution is " << abs(ship.pos[0]) + abs(ship.pos[1]) << endl;
    cout << "Solution is " << abs(second_ship.pos[0]) + abs(second_ship.pos[1])
         << endl;
}