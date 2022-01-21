#include <iostream>

using namespace std;

bool simulate(int dx, int dy, int minY, int maxY, int minX, int maxX){
    int y = 0;
    int x = 0;
    while(y >= minY and x <= maxX){
        y += dy;
        dy--;
        x+= dx;
        if(dx > 0)  dx--;
        else if(dx < 0)  dx++;
        if(y >= minY and y <= maxY and x >= minX and x <= maxX) return true;
    }
    return false;
}

int main(){
    int minY = -89;
    int maxY = -59;

    int minX = 192;
    int maxX = 251;

    int max = -2001;
    int count = 0;
    for(int i = 0; i < 1000; i++){
        for(int j = -89; j < 1000; j++){
            if(simulate(i, j, minY, maxY, minX, maxX)){
                if(j > max) 
                    max = j;
                count++;
            }
        }
    }
    cout << max*(max+1)/2 << " " << count << endl;
}