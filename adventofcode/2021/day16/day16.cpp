#include <iostream>
#include <bitset>
#include <fstream>
#include <vector>

using namespace std;

int unpack(string, int);
int literal(string , int );
int opLength(string, int, int, int&);
int opPackets(string, int, int, int&);

int unpack(string bitString, int start, int& curr){
    int count = 0;
    bitset<3> version(bitString.substr(start, 3));
    bitset<3> type(bitString.substr(start + 3, 3));
    
    if (type.to_ullong() == 4) {
        count += version.to_ullong();
        int value;
        start = curr = literal(bitString, start + 6);
    } else {
        bitset<1> lengthBit = bitString[start + 6];
        if (lengthBit.to_ullong() == 0) {
            bitset<15> lengthNum(bitString.substr(start + 7, 15));
            int current = start + 22;
            count += version.to_ullong() + opLength(bitString, current, lengthNum.to_ullong() + current, current);
            start = curr = current;
        } else {
            bitset<11> packetsNum(bitString.substr(start + 7, 11));  //
            int current = start + 18;
            count += version.to_ullong() + opPackets(bitString, current, packetsNum.to_ullong(), current);  //
            start = curr = current;
        }
    }
    return count;
}


// returns length;
int literal(string bitString, int start){
    int i = start;
    string bitInt = "";
    while(bitString[i] != '0'){
        bitInt += bitString.substr(i+1, 4);
        i += 5;
    }
    bitInt += bitString.substr(i + 1, 4);
    return i+5;
}

int opLength(string bitString, int start, int len, int& curr){
    int count = 0;
    while(start < len){
        count += unpack(bitString, start, curr);
        start = curr;
    }
    return count;
}

int opPackets(string bitString, int start, int packets, int& curr){
    int count = 0;
    int totalPackets = 0;
    while(totalPackets < packets){
        totalPackets += 1;
        count += unpack(bitString, start, curr);
        start = curr;
    }
    return count;
}



int main(){
    ifstream inFile;
    int steps = 100;
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

    int versionTotal = 0;
    int curr;
    cout << unpack(bitString, 0, curr) << endl;
}