#include <iostream>
#include <regex>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

struct Instruction {
    string name;
    int argument;
};

class Program {
   public:
    Program(vector<Instruction> instructions) : instructions(instructions) {
        instructions_visit.resize(instructions.size(), 0);
    }

    vector<Instruction> instructions;
    int accumulator = 0;

    void init() {
        cursor = 0;
        accumulator = 0;
    }

    void run() {
        init();
        while (instructions_visit[cursor] < 2) {
            run_instruction(cursor);
        }
    }

    void run_second() {
        init();
        while (cursor != instructions.size()) {
            run_instruction(cursor);
        }
    }

    void run_instruction(int index) {
        auto visits = instructions_visit[index]++;

        if (visits == 1) {
            cout << "!";
        }
        cout << index << " -> ";

        Instruction instruction = instructions[index];

        op_map[instruction.name](instruction.argument);
    }

   private:
    vector<int> instructions_visit;
    int cursor = 0;
    unordered_map<string, function<void(int)>> op_map = {
        {"nop", bind(&Program::nop, this, placeholders::_1)},
        {"jmp", bind(&Program::jmp, this, placeholders::_1)},
        {"acc", bind(&Program::acc, this, placeholders::_1)},
    };

    void nop(int arg) { cursor++; }
    void acc(int arg) {
        accumulator += arg;
        cursor++;
    }
    void jmp(int arg) { cursor += arg; }
};

int main() {
    string token;

    vector<Instruction> instructions;

    while (cin >> token) {
        Instruction instruction;
        instruction.name = token;
        cin >> token;
        instruction.argument = stoi(token);

        instructions.push_back(instruction);
    }

    Program p(instructions);

    p.run();
    // p.run_second();

    // cout << "Program accumulator is " << p.accumulator << endl;
}