#include <iostream>
#include <bitset>
#include <vector>
using namespace std;

int main(){
    int count = 0;
    const size_t bitLength = 12;
    bitset<bitLength> x;
    vector<int> bitCount(bitLength, 0);
    vector<bitset<bitLength>> possible;
    while(cin>>x){
        for(int i = 0; i < bitLength; i++){
            bitCount[i] += x[i];
        }
        possible.push_back(x);
        count++;
    }
    bitset<bitLength> mostCommon;
    bitset<bitLength> leastCommon;
    for (int i = bitLength - 1; i >= 0; i--) {
        if(bitCount[i] >= count/2){
            mostCommon[i] = 1;
            leastCommon[i] = 0;
        } else{
            mostCommon[i] = 0;
            leastCommon[i] = 1;
        }
    }
    vector<int> currMost(possible.size());
    for(int i = 0; i < currMost.size(); i++){
        currMost[i] = i;
    }
    vector<int> possMost = currMost;
    vector<int> possLeast = currMost;
    vector<int> currLeast = currMost;

    vector<int> bitCount2(bitLength, 0);
    for(int i = bitLength-1; i >= 0; i--){
        currMost = possMost;
        possMost.clear();
        if(i > 0){
            bitCount[i-1] = 0;
            bitCount2[i-1] = 0;
        }
        for(int j = 0; currMost.size() > 1 and j < currMost.size(); j++){
            if(possible[currMost[j]][i] == mostCommon[i]){
                possMost.push_back(currMost[j]);
                if(i > 0){
                    bitCount[i-1] += possible[currMost[j]][i-1];
                }
            }
        }

        currLeast = possLeast;
        possLeast.clear();
        for (int j = 0; currLeast.size() > 1 and j < currLeast.size(); j++) {
            if (possible[currLeast[j]][i] == leastCommon[i]) {
                possLeast.push_back(currLeast[j]);
                if (i > 0) {
                    bitCount2[i - 1] += possible[currLeast[j]][i - 1];
                }
            }
        }
        if(i > 0){
            if (bitCount[i - 1] >= possMost.size() / 2) {
                mostCommon[i - 1] = 1;
            } else {
                mostCommon[i - 1] = 0;
            }

            if (bitCount2[i - 1] >= possLeast.size() / 2) {
                leastCommon[i - 1] = 0;
            } else {
                leastCommon[i - 1] = 1;
            }
        }
        
    }

    cout << possible[possMost[0]].to_ullong() << " " << possible[possLeast[0]].to_ullong()  << " " << possible[possMost[0]].to_ullong() * possible[possLeast[0]].to_ullong()  << endl;
    return 0;
}