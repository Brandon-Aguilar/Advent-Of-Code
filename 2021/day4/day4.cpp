#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>
#include <utility>

#define INT_MAX 2147483647;
using namespace std;

int main(){
    vector<int> draws;
    stringstream ss;
    ifstream inFile;
    int boardSize = 5;

    inFile.open("input.txt");
    if(!inFile){
        cout << "error opening file" << endl; return 0;
    }

    string line;
    getline(inFile, line);
    ss.str(line);
    for(int i; ss>> i;){
        draws.push_back(i);
        if(ss.peek() == ',') ss.ignore();
    }
    
    
    vector<vector<vector<int>>> boards;
    vector<int> boardScores;
    vector<vector<int>> currentBoard;
    int score = 0;
    getline(inFile, line);
    while(getline(inFile, line)){
        if(line.empty()){
            boardScores.push_back(score);
            boards.push_back(currentBoard);
            currentBoard.clear();
            score = 0;
        } else{
            ss.clear();
            ss.str(line);
            vector<int> currentLine;
            string currentString;
            while(ss>>currentString){
                currentLine.push_back(stoi(currentString));
                score += stoi(currentString);
            }
            currentBoard.push_back(currentLine);
        }
    }
    boardScores.push_back(score);
    boards.push_back(currentBoard);
    
    int minBoard = 0;
    int minDraws = INT_MAX;
    int maxBoard = 0;
    int maxDraws = 0;
    int minScore = 0;
    int maxScore = 0;
    vector<pair<int,int>> winDraws;
    for (int i = 0; i < boards.size(); i++) {
        vector<int> xMarked(boardSize, 0);
        vector<int> yMarked(boardSize, 0);
        bool boardDone = false;
        for(int draw = 0; draw < draws.size() and !boardDone; draw++){
            for (int j = 0; j < boardSize and !boardDone; j++) {
                for (int k = 0; k < boardSize and !boardDone; k++) {
                    if(boards[i][j][k] == draws[draw]){
                        boardScores[i] -= boards[i][j][k];
                        xMarked[j]++;
                        yMarked[k]++;
                        if(xMarked[j] == boardSize or yMarked[k] == boardSize){
                            boardDone = true;
                            if(draw < minDraws){
                                minDraws = draw;
                                minBoard = i;
                                minScore = boardScores[i] * draws[draw];
                            }
                            if (draw > maxDraws) {
                                maxDraws = draw;
                                maxBoard = i;
                                maxScore = boardScores[i] * draws[draw];
                            }
                        }
                    }
                }
            }
        }
    }

    cout << minScore << " " << maxScore << endl;




    //for(auto i : boards){
    //    cout << endl;
    //    for(auto j : i){
    //        for(auto k : j){
    //            cout << k << " ";
    //        }
    //        cout << endl;
    //    }
    //    cout << endl;
    //}

}