#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

int next_index = 1;

vector<vector<int>> concatTile(vector<vector<int>> upperLeft, vector<vector<int>> upperRight, vector<vector<int>>lowerLeft, vector<vector<int>>lowerRight) {
    upperLeft.insert(upperLeft.end(), lowerLeft.begin(), lowerLeft.end());
    upperRight.insert(upperRight.end(), lowerRight.begin(), lowerRight.end());
    for(int i = 0; i< upperRight.size(); i++) {
        upperLeft[i].insert(upperLeft[i].end(), upperRight[i].begin(), upperRight[i].end());
    }
    return upperLeft;
}

vector<vector<int>> makeTile(int N, int zero_locaiton, int zero_index) {
    vector<vector<int>> result;
    if (N==1) {
        if (zero_locaiton == 0) {  // left upper
            int index = next_index++;
            result.push_back(vector<int>{zero_index,index});
            result.push_back(vector<int>{index,index});
            return result;
        }
        if (zero_locaiton == 1) {  // left upper
            int index = next_index++;
            result.push_back(vector<int>{index,zero_index});
            result.push_back(vector<int>{index,index});
            return result;
        }
        if (zero_locaiton == 2) {  // left upper
            int index = next_index++;
            result.push_back(vector<int>{index,index});
            result.push_back(vector<int>{index,zero_index});
            return result;
        }
        if (zero_locaiton == 3) {  // left upper
            int index = next_index++;
            result.push_back(vector<int>{index,index});
            result.push_back(vector<int>{zero_index,index});
            return result;
        }
    }
    if (zero_locaiton == 0) {  // left upper
        int fill_index = next_index++;
        return concatTile(makeTile(N-1,0,zero_index),makeTile(N-1,3,fill_index),makeTile(N-1,1,fill_index),makeTile(N-1,0,fill_index));
    }
    if (zero_locaiton == 1) {  // right upper
        int fill_index = next_index++;
        return concatTile(makeTile(N-1,2,fill_index),makeTile(N-1,1,zero_index),makeTile(N-1,1,fill_index),makeTile(N-1,0,fill_index));
    }
    if (zero_locaiton == 2) {  // right lower
        int fill_index = next_index++;
        return concatTile(makeTile(N-1,2,fill_index),makeTile(N-1,3,fill_index),makeTile(N-1,1,fill_index),makeTile(N-1,2,zero_index));
    }
    if (zero_locaiton == 3) {  // left lower
        int fill_index = next_index++;
        return concatTile(makeTile(N-1,2,fill_index),makeTile(N-1,3,fill_index),makeTile(N-1,3,zero_index),makeTile(N-1,0,fill_index));
    }
}

vector<vector<int>> determineZero(int N, int r, int c) {
    vector<vector<int>> result;
    if (N==1) {
        if (r==1 && c == 1) {  // left upper
            int index = next_index++;
            result.push_back(vector<int>{0,index});
            result.push_back(vector<int>{index,index});
            return result;
        }
        if (r==1 && c == 2) {  // right upper
            int index = next_index++;
            result.push_back(vector<int>{index,0});
            result.push_back(vector<int>{index,index});
            return result;
        }
        if (r==2 && c == 2) {  // right lower
            int index = next_index++;
            result.push_back(vector<int>{index,index});
            result.push_back(vector<int>{index,0});
            return result;
        }
        if (r==2 && c == 1) {  // left lower
            int index = next_index++;
            result.push_back(vector<int>{index,index});
            result.push_back(vector<int>{0,index});
            return result;
        }
    }

    int boradLen = pow(2,N);
    if (r <= boradLen/2 && c <= boradLen/2) {
        int fill_index = next_index++;
        return concatTile(determineZero(N-1,r,c), makeTile(N-1,3,fill_index),makeTile(N-1,1,fill_index),makeTile(N-1,0,fill_index));
    }
    if (r <= boradLen/2 && c > boradLen/2) {
        int fill_index = next_index++;
        return concatTile(makeTile(N-1,2,fill_index),determineZero(N-1,r,c-boradLen/2), makeTile(N-1,1,fill_index),makeTile(N-1,0,fill_index));
    }
    if (r > boradLen/2 && c > boradLen/2) {
        int fill_index = next_index++;
        return concatTile(makeTile(N-1,2,fill_index),makeTile(N-1,3,fill_index),makeTile(N-1,1,fill_index),determineZero(N-1,r-boradLen/2,c-boradLen/2));
    }
    if (r > boradLen/2 && c <= boradLen/2) {
        int fill_index = next_index++;
        return concatTile(makeTile(N-1,2,fill_index),makeTile(N-1,3,fill_index),determineZero(N-1,r-boradLen/2,c),makeTile(N-1,0,fill_index));
    }
}

int main() {
    int N,r,c;
    cin >> N >> r >> c;
    vector<vector<int>> answer = determineZero(N,r,c);
    for(int i = 0; i < answer.size();i++) {
        for(int j = 0; j < answer[i].size();j++) {
            cout << answer[i][j] << " ";
        }
        cout << "\n";
    }
}