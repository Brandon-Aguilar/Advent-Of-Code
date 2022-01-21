#include <iostream>
#include <bitset>
#include <vector>
#include <fstream>
using namespace std;

int main(){
    ifstream inFile;
    const int bitLength = 12;
    inFile.open("input.txt");
    if(!inFile){
        cout << "File opening failed." << endl;
        return 0;
    }

    string line;

    vector<string> inputs;
    
    int mostCount;
    while(inFile>>line){
        inputs.push_back(line);
        mostCount += line[0] - '0' ? 1 : -1;
    }
    char mostCommon = mostCount >= 0 ? '1' : '0';
    char leastCommon = mostCount >= 0 ? '0' : '1';
    

    vector<string> mostPossible = inputs;
    vector<string> leastPossible = inputs;

    vector<string> mostCurrent;
    vector<string> leastCurrent;
    for(int i = 0; i < bitLength; i++){
        
        
        if(mostPossible.size() > 1){
            mostCurrent = mostPossible;
            mostPossible.clear();
            int mostCount = 0;
            for(auto curr : mostCurrent){
                if(curr[i] == mostCommon){
                    mostPossible.push_back(curr);
                    if(i+1 < bitLength){
                        mostCount += curr[i+1] == '1' ?  1 : -1;
                    }
                }
            }
            mostCommon = mostCount >= 0 ? '1' : '0';
        }

        if(leastPossible.size() > 1){
            leastCurrent = leastPossible;
            leastPossible.clear();
            int leastCount = 0;
            for(auto curr : leastCurrent){
                if(curr[i]== leastCommon){
                    leastPossible.push_back(curr);
                    if(i+1 < bitLength){
                        leastCount += curr[i+1] == '1' ?  1 : -1;
                    }
                }
            }
            if (leastCount == 0) {
                cout << " " << endl;
            }
            leastCommon = leastCount >= 0 ? '0' : '1';
        }
        
    }
    bitset<bitLength> mostAnswer (mostPossible[0]);
    bitset<bitLength> leastAnswer(leastPossible[0]);
    cout << mostAnswer.to_ullong() << " " << leastAnswer.to_ullong()  << " " << mostAnswer.to_ulong() * leastAnswer.to_ulong() << endl;
    // 2795310
    return 0;
}