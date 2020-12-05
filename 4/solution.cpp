#include <iostream>
#include <regex>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

std::vector<std::string> split(const std::string& s, char delimiter) {
    std::vector<std::string> tokens;
    std::string token;
    std::istringstream tokenStream(s);
    while (std::getline(tokenStream, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
}

function<bool(string)> numberValidatorFactory(int min, int max) {
    return [min, max](string str) {
        int val = stoi(str);
        return val >= min && val <= max;
    };
}

bool hgtValidator(string str) {
    smatch m;
    regex_search(str, m, regex("[a-zA-Z]+$"));

    if (m.empty()) {
        return false;
    }

    string unit = m[0];

    smatch v;
    regex_search(str, v, regex("^[0-9]+"));

    if (v.empty()) {
        return false;
    }

    int height = stoi(v[0]);

    if (unit == "cm") {
        return height >= 150 && height <= 193;
    } else if (unit == "in") {
        return height >= 59 && height <= 76;
    } else {
        return false;
    }
}

bool hclValidator(string str) {
    regex r("^#[0-9a-f]{6}$");
    return regex_match(str, r);
}

bool eclValidator(string str) {
    string accepted[] = {"amb", "blu", "brn", "gry", "grn", "hzl", "oth"};
    return find(begin(accepted), end(accepted), str) != end(accepted);
}

bool pidValidator(string str) {
    regex r("^[0-9]{9}$");
    return regex_match(str, r);
}

typedef std::function<bool(std::string)> Validator;
typedef unordered_map<string, string> Passport;

bool isPassportValid(Passport passport,
                     unordered_map<string, Validator> validators) {
    for (auto f : passport) {
        if (validators.find(f.first) != validators.end()) {
            Validator validate = validators[f.first];

            if (!validate(f.second)) {
                return false;
            }
        }
    }

    return true;
}

int main() {
    string line;

    vector<string> fields_name = {"byr", "iyr", "eyr", "hgt",
                                  "hcl", "ecl", "pid", "cid"};

    Passport passport;

    unordered_map<string, Validator> field_validators = {
        {"byr", numberValidatorFactory(1920, 2002)},
        {"iyr", numberValidatorFactory(2010, 2020)},
        {"eyr", numberValidatorFactory(2020, 2030)},
        {"hgt", hgtValidator},
        {"hcl", hclValidator},
        {"ecl", eclValidator},
        {"pid", pidValidator},
    };

    int nb_valid = 0;
    int nb_valid_second = 0;

    while (getline(cin, line)) {
        if (line.length() == 0) {
            if (passport.size() == fields_name.size() ||
                (passport.size() == fields_name.size() - 1 &&
                 passport.find("cid") == passport.end())) {
                nb_valid++;

                if (isPassportValid(passport, field_validators)) {
                    nb_valid_second++;
                }
            }
            passport.clear();
        }

        vector<string> fields = split(line, ' ');

        for (auto f : fields) {
            vector<string> parsed = split(f, ':');
            passport[parsed[0]] = parsed[1];
        }
    }

    cout << nb_valid << " valid passports (first part)" << endl;
    cout << nb_valid_second << " valid passports (second part)" << endl;
}