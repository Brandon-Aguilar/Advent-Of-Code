#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

int main() {
    ifstream inFile;
    inFile.open("input.txt");
    if (!inFile) {
        cout << "File opening failed." << endl;
        return 0;
    }

    string line;
    int score1 = 0;
    vector<unsigned long long> scores;
    unordered_map<char, int> lazy;
    lazy['('] = 1;
    lazy['['] = 2;
    lazy['{'] = 3;
    lazy['<'] = 4;
    while (inFile >> line) {
        vector<char> stack;
        bool flag = false;
        for (auto i : line) {
            char curr = stack.size() > 0 ? stack.back() : -1;
            switch (i) {
                case '(':
                case '{':
                case '[':
                case '<':
                    stack.push_back(i);
                    break;
                case ')':
                    if (curr != '(') {
                        score1 += 3;
                        flag = true;
                    } else
                        stack.pop_back();
                    break;
                case ']':
                    if (curr != '[') {
                        score1 += 57;
                        flag = true;
                    } else
                        stack.pop_back();
                    break;
                case '}':
                    if (curr != '{') {
                        score1 += 1197;
                        flag = true;
                    } else
                        stack.pop_back();
                    break;
                case '>':
                    if (curr != '<') {
                        score1 += 25137;
                        flag = true;
                    } else
                        stack.pop_back();
                    break;
            }
            if (flag)
                break;
        }
        if (!flag) {
            unsigned long long tmpScore = 0;

            while (stack.size() != 0) {
                char curr = stack.back();
                tmpScore *= 5;
                tmpScore += lazy[curr];
                stack.pop_back();
            }
            scores.push_back(tmpScore);
        }
    }
    sort(scores.begin(), scores.end());
    cout << score1 << " " << scores[scores.size() / 2] << endl;
}