#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

class node{
    public:
    bool visited;
    int val;
    int x;
    int y;
    node(int val, int x, int y) : visited{false}, val{val}, x{x}, y{y}{}
};

class board{
    public:
    vector<vector<node*>> boardData;
    unordered_map<int, node*> nums;
    vector<int> xMarked;
    vector<int> yMarked;
    int length;
    board(){
        length = 0;
    }
    board(vector<vector<int>> data){
        length = data.size();
        xMarked = vector<int>(length, 0);
        yMarked = vector<int>(length, 0);
        for (int i = 0; i < length; i++) {
            vector<node*> tmpVector;
            for (int j = 0; j < length; j++) {
                node * tmp = new node(data[i][j], i, j);
                tmpVector.push_back(tmp);
                nums.emplace(data[i][j], tmp);
            }
            boardData.push_back(tmpVector);
        }
    }
    bool update(int n){
        if(nums.find(n) != nums.end()){
            nums[n]->visited = true;
            xMarked[nums[n]->x] += 1;
            yMarked[nums[n]->y] += 1;
            return xMarked[nums[n]->x] == length or yMarked[nums[n]->y] == length;
        }
        return false;
    }
};