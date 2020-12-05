#include <iostream>
#include <string>

using namespace std;

pair<int, int> findSeat(string s) {
    string first_part = s.substr(0, 7);
    string second_part = s.substr(7, 3);

    int a = 0;
    int b = 127;

    for (char c : first_part) {
        int mid = a + (b - a) / 2;

        if (c == 'F') b = mid;
        if (c == 'B') a = mid + 1;
    }

    int l = 0;
    int r = 7;

    for (char c : second_part) {
        int mid = l + (r - l) / 2;

        if (c == 'L') r = mid;
        if (c == 'R') l = mid + 1;
    }

    return make_pair(a, l);
}

int computeSeatId(int row, int column) { return row * 8 + column; }

int main() {
    string line;

    int highest_seat_id = 0;

    bool seats[128][8] = {0};

    while (cin >> line) {
        auto seat = findSeat(line);

        seats[seat.first][seat.second] = true;

        highest_seat_id =
            max(highest_seat_id, computeSeatId(seat.first, seat.second));
    }

    for (int i = 0; i < 128; i++) {
        for (int j = 0; j < 8; j++) {
            if (!seats[i][j]) {
                printf("Candidate seat %d, %d, ID = %d\n", i, j,
                       computeSeatId(i, j));
            }
        }
    }

    cout << "Highest seat ID is " << highest_seat_id << endl;
}