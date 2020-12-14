#include <iostream>
#include <sstream>
#include <unordered_map>
#include <vector>

using namespace std;

#define X 2
#define ll unsigned long long int
#define BYTE_LEN 36

struct MemoryContext {
    int mask[BYTE_LEN];
    unordered_map<int, ll> memory;
};

ll mask_val(int mask[BYTE_LEN], ll val) {
    ll sum = 0;
    // cout << "Mask ";
    cout << endl;

    for (int i = 35; i >= 0; i--) {
        int mask_bit = mask[BYTE_LEN - i - 1];
        int bit = (val >> i) & 1;

        if (mask_bit == X) {
            sum += bit;
        } else {
            sum += mask_bit;
        }

        if (i != 0) sum = sum << 1;

        cout << bit;

        // printf("(%d) bit : %d, mask: %d, sum: %llu\n", BYTE_LEN - i - 1, bit,
        //        mask_bit, sum);
    }
    cout << endl;

    for (int i = 0; i < BYTE_LEN; i++) {
        cout << mask[i];
    }
    cout << endl;

    for (int i = 35; i >= 0; i--) {
        cout << ((sum >> i) & 1);
    }

    cout << " = " << sum << endl;

    return sum;
}

void execute_line(string line, MemoryContext &context) {
    stringstream ss(line);
    auto token_pos = line.find(" = ");

    string cmd = string(line.begin(), line.begin() + token_pos);

    string rval(line.begin() + token_pos + 3, line.end());

    if (cmd == "mask") {
        for (int i = 0; i < BYTE_LEN; i++) {
            switch (rval[i]) {
                case '0':
                    context.mask[i] = 0;
                    break;
                case '1':
                    context.mask[i] = 1;
                    break;
                case 'X':
                    context.mask[i] = X;
                    break;
            }
        }
    } else {
        ll val = stoi(rval);
        int mem = stoi(string(line.begin() + 4, line.begin() + token_pos - 1));

        context.memory[mem] = mask_val(context.mask, val);
    }
}

int main() {
    string line;

    MemoryContext context;

    while (getline(cin, line)) {
        execute_line(line, context);
    }

    ll sum = 0;
    for (auto mem : context.memory) {
        cout << mem.first << " = " << mem.second << endl;
        sum += mem.second;
    }

    cout << sum << " is the sum of all memory (first part)" << endl;
}