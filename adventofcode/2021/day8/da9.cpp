#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;


string fiveCheck(string input, string fourUnknowns, string one) {
    int oneCount = 0;
    for (auto i : one) {
        for (auto j : input) {
            if (i == j) oneCount++;
        }
    }
    if(oneCount == 2) return "3";
    int fourCount = 0;
    for (auto i : fourUnknowns) {
        for (auto j : input) {
            if (i == j) {
                fourCount += 1;
            }
        }
    }
    return fourCount == 1 ? "2" : "5";
}


string sixCheck(string input, string fourUnknowns, string one) {
    int fourCount = 0;
    for (auto i : fourUnknowns) {
        for (auto j : input) {
            if (i == j) {
                fourCount++;
            }
        }
    }

    int oneCount = 0;
    for (auto i : one) {
        for (auto j : input) {
            if (i == j) oneCount++;
        }
    }
    if(fourCount == 2 and oneCount == 2) return "9";
    if(fourCount == 1 and oneCount == 2) return "0";
    return "6";
}

int main(){
    ifstream inFile;
    inFile.open("input.txt");
    if (!inFile) {
        cout << "File opening failed." << endl;
        return 0;
    }

    string input;
    int count = 0;
    while(inFile>>input){
        int length = input.length();;
        switch(length){
            case 2:
            case 3:
            case 4:
            case 7:
                count += 1;
                break;
        }
    }
    cout << count << endl;

    inFile.clear();
    inFile.close();
    inFile.open("input2 .txt");
    if (!inFile) {
        cout << "File opening failed." << endl;
        return 0;
    }

    string line;
    int sum = 0;
    while(getline(inFile, line)){
        stringstream ss(line);
        string one;
        string four;
        string seven;
        char top;

        while(ss>>input){
            if(input == "|") break;
            if(not(one.empty() or four.empty() or seven.empty())) continue;
            int length = input.length();
            switch(length){
                case 2:
                    one = input;
                    break;
                case 3:
                    seven = input;
                    break;
                case 4:
                    four = input;
                    break;
            }
        }
        string fourUnknowns = "";
        for(auto i : four){
            bool flag = false;
            for(auto j : one){
                if(i == j){
                    flag = true;
                }
            }
            if(flag == false){
                fourUnknowns += i;
            }
        }

        string ans = "";
        while(ss>>input){
            int length = input.length();
            switch (length) {
                case 2:
                    ans += "1";
                    break;
                case 3:
                    ans += "7";
                    break;
                case 4:
                    ans += "4";
                    break;
                case 5:
                    ans += fiveCheck(input, fourUnknowns, one);
                    break;
                case 6:
                    ans += sixCheck(input, fourUnknowns, one);
                    break;
                case 7:
                    ans += "8";
                    break;
            }
        }
        sum += stoi(ans);


    }
    cout << sum << endl;
}