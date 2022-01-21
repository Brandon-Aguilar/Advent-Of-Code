#include <iostream>
#include <fstream>
#include <vector>
#include <utility>

using namespace std;

void flash(vector<vector<pair<int, bool>>> &map, int i, int j){
    if(map[i][j].second == true) return;
    map[i][j].second = true;
    if(i > 0){
        map[i-1][j].first += 1;
        if(map[i-1][j].first > 9){
            flash(map, i-1, j);
        }
        if(j > 0){
            map[i-1][j-1].first += 1;
            if(map[i-1][j-1].first > 9){
                flash(map, i-1, j-1);
            }
        }
        if(j < map[i].size() - 1){
            map[i-1][j+1].first += 1;
            if(map[i-1][j+1].first > 9){
                flash(map, i-1, j+1);
            }
        }
    }
    if(j > 0){
        map[i][j-1].first += 1;
        if(map[i][j-1].first > 9){
            flash(map, i, j-1);
        }
        
        if(i < map.size() - 1){
            map[i+1][j-1].first += 1;
            if(map[i+1][j-1].first > 9){
                flash(map, i+1, j-1);
            }
        }
    }
    if(j < map[i].size() - 1){
        map[i][j+1].first += 1;
        if(map[i][j+1].first > 9){
            flash(map, i, j+1);
        }

        if(i < map.size() - 1){
            map[i+1][j+1].first += 1;
            if(map[i+1][j+1].first > 9){
                flash(map, i+1, j+1);
            }
        }
    }
    if(i < map.size() - 1){
        map[i+1][j].first += 1;
        if(map[i+1][j].first > 9){
            flash(map, i+1, j);
        }
    }
}

    int main() {
    ifstream inFile;
    int steps = 100;
    inFile.open("input.txt");
    if (!inFile) {
        cout << "File opening failed." << endl;
        return 0;
    }

    vector<vector<pair<int,bool>>> map;
    string line;
    while(inFile>>line){
        vector<pair<int,bool>> curr;
        for(auto i : line){
            curr.push_back(make_pair(i-'0', false));
        }
        map.push_back(curr);
    }
    int flashes = 0;
    for(int step = 0; step < steps; step++){
        for(int i = 0; i < map.size(); i++){
            for (int j = 0; j < map[i].size(); j++) {
                map[i][j].first += 1;
            }
        }
        for (int i = 0; i < map.size(); i++) {
            for (int j = 0; j < map[i].size(); j++) {
                if(map[i][j].first > 9){
                    flash(map, i, j);
                }
            }
        }

        for (int i = 0; i < map.size(); i++) {
            for (int j = 0; j < map[i].size(); j++) {
                if (map[i][j].second == true) {
                    map[i][j].second = false;
                    map[i][j].first = 0;
                    flashes += 1;
                }
            }
        }
        cout << step+ 1 << endl;
        for (int i = 0; i < map.size(); i++) {
            for (int j = 0; j < map[i].size(); j++) {
                cout << map[i][j].first;
            }
            cout << endl;
        }
        cout << endl;
    }


    cout << endl << flashes << endl;
}