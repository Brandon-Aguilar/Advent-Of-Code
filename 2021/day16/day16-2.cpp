#include <iostream>
#include <bitset>
#include <fstream>
#include <vector>

using namespace std;

long long unpack(string, long long);
long long literal(string , long long, long long&);
vector<long long> opLength(string, long long, long long, long long&);
vector<long long> opPackets(string, long long, long long, long long&);

long long evaluate(vector<long long> values, long long typeID){
    long long ans = 0;
    if (typeID == 0 or typeID == 1 or typeID == 2 or typeID == 3) {
        ans = values[0];
        for (long long i = 1; i < values.size(); i++) {
            if (typeID == 0)
                ans += values[i];
            else if (typeID == 1)
                ans *= values[i];
            else if (typeID == 2) {
                if (values[i] < ans) ans = values[i];
            } else if (typeID == 3) {
                if (values[i] > ans) ans = values[i];
            }
        }
    }
    else if(typeID == 5){
        ans = values[0] > values[1];
    } else if(typeID == 6){
        ans = values[0] < values[1];
    } else if(typeID == 7){
        ans = values[0] == values[1];
    } else if(typeID == 4){
        ans = values[0];
    } else {
        cout << "ERROR" << endl;
    }

    return ans;
}

long long unpack(string bitString, long long start, long long& curr){
    bitset<3> version(bitString.substr(start, 3));
    bitset<3> type(bitString.substr(start + 3, 3));
    vector<long long> values;
    
    if (type.to_ullong() == 4) {
        long long value;
        start = curr = literal(bitString, start + 6, value);
        values.push_back(value);
    } else {
        bitset<1> lengthBit = bitString[start + 6];
        if (lengthBit.to_ullong() == 0) {
            bitset<15> lengthNum(bitString.substr(start + 7, 15));
            long long current = start + 22;
            values = opLength(bitString, current, lengthNum.to_ullong() + current, current);
            start = curr = current;
        } else {
            bitset<11> packetsNum(bitString.substr(start + 7, 11));  //
            long long current = start + 18;
            values = opPackets(bitString, current, packetsNum.to_ullong(), current);  //
            start = curr = current;
        }
    }
    long long ans = 0;
    ans = evaluate(values, type.to_ullong());
    return ans;
}


// returns length;
long long literal(string bitString, long long start, long long& value){
    long long i = start;
    string bitNum = "";
    while(bitString[i] != '0'){
        bitNum += bitString.substr(i+1, 4);
        i += 5;
    }
    bitNum += bitString.substr(i + 1, 4);
    value = stoll(bitNum, 0, 2);
    return i+5;
}

vector<long long> opLength(string bitString, long long start, long long len, long long& curr){
    vector<long long> values;
    while(start < len){
        values.push_back(unpack(bitString, start, curr));
        start = curr;
    }
    return values;
}

vector<long long> opPackets(string bitString, long long start, long long packets, long long& curr){
    vector<long long> values;
    long long totalPackets = 0;
    while(totalPackets < packets){
        totalPackets += 1;
        values.push_back(unpack(bitString, start, curr));
        start = curr;
    }
    return values;
}



int main(){
    ifstream inFile;
    long long steps = 100;
    inFile.open("input.txt");
    if (!inFile) {
        cout << "File opening failed." << endl;
        return 0;
    }

    string inputString;
    inFile >> inputString;
    //inputString = "A0016C880162017C3686B18A3D4780";
    string bitString = "";
    for(auto ch : inputString){
        switch (ch) {
            case '0': bitString += "0000"; break;
            case '1': bitString += "0001"; break;
            case '2': bitString += "0010"; break;
            case '3': bitString += "0011"; break;
            case '4': bitString += "0100"; break;
            case '5': bitString += "0101"; break;
            case '6': bitString += "0110"; break;
            case '7': bitString += "0111"; break;
            case '8': bitString += "1000"; break;
            case '9': bitString += "1001"; break;
            case 'A': bitString += "1010"; break;
            case 'B': bitString += "1011"; break;
            case 'C': bitString += "1100"; break;
            case 'D': bitString += "1101"; break;
            case 'E': bitString += "1110"; break;
            case 'F': bitString += "1111"; break;
        }
    }

    long long versionTotal = 0;
    long long curr;
    cout << unpack(bitString, 0, curr) << endl;
}