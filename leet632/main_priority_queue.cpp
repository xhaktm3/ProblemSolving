#include <iostream>
#include <map>
#include <vector>
#include <queue>

using namespace std;

class Compare {
public:
    bool operator()(const pair<int,pair<int, int>>& p1, const pair<int,pair<int, int>>& p2) {
        return p1.first > p2.first;
    }
};

int main()
{
    priority_queue<pair<int,pair<int, int>>,vector<pair<int,pair<int, int>>>,Compare> heap;
    vector<vector<int>>nums = {{4,10,15,24,26},{0,9,12,20},{5,18,22,30}};

    int maxV = numeric_limits<int>::min();
    for (int i=0; i<nums.size();i++){
        pair<int,int> ip(i,0);
        pair<int,pair<int,int>> p(nums[i][0],ip);
        heap.push(p);
        maxV = max(maxV, p.first);
    }
    pair<int,pair<int,int>> t = heap.top();
    int minV = t.first;
    int minRange = maxV-minV;
    int l_index = t.second.first;
    int index = t.second.second;
    int selMinV = minV, selMaxV=maxV;
    while (index < nums[l_index].size()-1) {
        heap.pop();
        int newV = nums[l_index][index+1];
        pair<int,int> ip(l_index,index+1);
        pair<int,pair<int,int>> p(newV,ip);
        heap.push(p);

        t=heap.top();
        l_index = t.second.first;
        index = t.second.second;
        minV = t.first;
        maxV = max(maxV, p.first);
        if (maxV-minV  < minRange) {
            minRange = maxV-minV;
            selMinV = minV;
            selMaxV = maxV;
        }
    }
    cout << selMinV << selMaxV;
    return 0;
}