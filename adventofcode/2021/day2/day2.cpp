#include "iostream"
#include "fstream"
#include "sstream"

using namespace std;

int main(){
    

    string dir;
    int horiz = 0;
    int depth = 0;
    int aim = 0;
    while(cin>>dir){
        int x;
        cin>>x;
        if(dir == "forward"){
            horiz += x;
            depth += aim * x;
        }else if(dir == "down"){
            aim += x;
        } else if (dir == "up") {
            aim -= x;
        }
    }   
    
    cout << depth * horiz << endl;


}