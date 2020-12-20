#include <deque>
#include <iostream>
#include <regex>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

deque<string> parse_expression(string line) {
    vector<string> tokens;

    smatch sm;
    regex e("([0-9]+|\\(|\\)|\\+|\\*)");

    auto tokens_begin = sregex_iterator(line.begin(), line.end(), e);
    auto tokens_end = sregex_iterator();

    for (auto i = tokens_begin; i != tokens_end; i++) {
        smatch match = *i;
        tokens.push_back(match.str());
    }

    deque<string> output;
    vector<string> operator_stack;

    for (string token : tokens) {
        if (token == "(") {
            operator_stack.push_back(token);
        } else if (token == ")") {
            while (operator_stack.back() != "(") {
                output.push_back(operator_stack.back());
                operator_stack.pop_back();
            }

            // Discards opening parenthesis
            operator_stack.pop_back();

        } else if (token == "+" || token == "*") {
            while (operator_stack.size() > 0 && operator_stack.back() != "(") {
                output.push_back(operator_stack.back());
                operator_stack.pop_back();
            }

            operator_stack.push_back(token);
        } else {
            output.push_back(token);
        }
    }

    while (operator_stack.size() > 0) {
        output.push_back(operator_stack.back());
        operator_stack.pop_back();
    }

    return output;
}

long long int evaluate_rpn_expression(deque<string> expression) {
    vector<long long int> stack;

    for (auto v : expression) {
        if (v == "+") {
            auto left = stack.back();
            stack.pop_back();
            auto right = stack.back();
            stack.pop_back();
            stack.push_back(left + right);
        } else if (v == "*") {
            auto left = stack.back();
            stack.pop_back();
            auto right = stack.back();
            stack.pop_back();
            stack.push_back(left * right);
        } else {
            stack.push_back(stoi(v));
        }
    }

    return stack.back();
}

int main() {
    string line;

    vector<string> expressions;

    long long int total_sum = 0;

    while (getline(cin, line)) {
        expressions.push_back(line);
        auto expr = parse_expression(line);

        total_sum += evaluate_rpn_expression(expr);
    }

    cout << total_sum << " (first part)" << endl;
}