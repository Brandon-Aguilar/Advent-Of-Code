#include <algorithm>
#include <cmath>
#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

class node {
   public:
    bool visited;
    int i;
    int j;
    int val;

    node() {
        visited = false;
        i = -1;
        j = -1;
        val = 0;
    }
    node(int i, int j, int val) {
        visited = false;
        this->i = i;
        this->j = j;
        this->val = val;
    }
    int neighbors(int length, int width, vector<vector<node>> &lavaMap) {
        if(visited) return 0;
        visited = true;
        int sum = 1;
        if (i > 0) {
            if (lavaMap[i - 1][j].val >= val and lavaMap[i - 1][j].val != 9) {
                sum += lavaMap[i - 1][j].neighbors(length, width, lavaMap);
            }
        }
        if (i < length - 1) {
            if (lavaMap[i + 1][j].val >= val and lavaMap[i + 1][j].val != 9) {
                sum += lavaMap[i + 1][j].neighbors(length, width, lavaMap);
            }
        }
        if (j > 0) {
            if (lavaMap[i][j - 1].val >= val and lavaMap[i][j - 1].val != 9) {
                sum += lavaMap[i][j - 1].neighbors(length, width, lavaMap);
            }
        }
        if (j < width - 1) {
            if (lavaMap[i][j + 1].val >= val and lavaMap[i][j + 1].val != 9) {
                sum += lavaMap[i][j + 1].neighbors(length, width, lavaMap);
            }
        }
        return sum;
    }
};

int main() {
    ifstream inFile;
    inFile.open("input.txt");
    if (!inFile) {
        cout << "File opening failed." << endl;
        return 0;
    }

    string line;
    vector<vector<node>> lavaMap;
    int iline = 0;
    int jline = 0;
    while (inFile >> line) {
        vector<node> lavaMapLine;
        for (auto i : line) {
            node x(iline, jline, i - '0');
            lavaMapLine.push_back(x);
            jline++;
        }
        lavaMap.push_back(lavaMapLine);
        iline++;
        jline = 0;
    }

    int length = lavaMap.size();
    int width = lavaMap[0].size();
    int sum = 0;
    vector<node> basins;
    for (int i = 0; i < lavaMap.size(); i++) {
        for (int j = 0; j < lavaMap[i].size(); j++) {
            bool isMin = true;
            node curr = lavaMap[i][j];
            if (i > 0) {
                isMin *= lavaMap[i - 1][j].val > curr.val;
            }
            if (i < length - 1) {
                isMin *= lavaMap[i + 1][j].val > curr.val;
            }
            if (j > 0) {
                isMin *= lavaMap[i][j - 1].val > curr.val;
            }
            if (j < width - 1) {
                isMin *= lavaMap[i][j + 1].val > curr.val;
            }
            if (isMin) {
                sum += curr.val + 1;
                basins.push_back(curr);
            }
        }
    }
    cout << sum << endl;

    vector<int> basinSizes;
    for (auto curr : basins) {
        int val = curr.neighbors(lavaMap.size(), lavaMap[0].size(), lavaMap);
        basinSizes.push_back(val);
    }
    sort(basinSizes.begin(), basinSizes.end(), greater<int>());
    cout << basinSizes[0] * basinSizes[1] * basinSizes[2] << endl;
}