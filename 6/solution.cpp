#include <iostream>
#include <sstream>
#include <string>

using namespace std;

int main() {
    int counter[26] = {0};

    string line;

    // For both part :
    // Time Complexity : O(n) with n the total number of people
    // Space Complexity : O(1) using an array with fixed size of 26 to count
    // occurences

    int nb_questions_first = 0;
    int nb_questions_second = 0;

    int people_count = 0;

    while (getline(cin, line)) {
        if (line.length() == 0) {
            nb_questions_second +=
                count_if(begin(counter), end(counter),
                         [people_count](int n) { return n == people_count; });

            fill(begin(counter), end(counter), 0);
            people_count = 0;
        } else {
            people_count++;
        }

        for (auto letter : line) {
            if (counter[letter - 'a'] == 0) {
                nb_questions_first++;
            }

            counter[letter - 'a']++;
        }
    }

    nb_questions_second +=
        count_if(begin(counter), end(counter),
                 [people_count](int n) { return n == people_count; });

    cout << "Sum of answered questions is " << nb_questions_first
         << " (first part)" << endl;
    cout << "Sum of answered questions is " << nb_questions_second
         << " (second part)" << endl;
}