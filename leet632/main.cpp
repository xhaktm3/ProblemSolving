#include <iostream>
#include <map>
#include <vector>

using namespace std;

class MinHeap {
private:
    vector<pair<int,pair<int,int>>> heap;
    int getParentIndex(int index) {
        return (index - 1) / 2;
    }
    int getLeftChildIndex(int index) {
        return 2 * index + 1;
    }
    int getRightChildIndex(int index) {
        return 2 * index + 2;
    }
    void heapifyUp(int index) {
        if (index != 0) {
            pair<int,pair<int,int>> now = heap[index];
            pair<int,pair<int,int>> parent = heap[getParentIndex(index)];
            if (now<parent) {
                heap[getParentIndex(index)] = now;
                heap[index] = parent;
                heapifyUp(getParentIndex(index));
            }
        }
    }
    void heapifyDown(int index) {
        if (index >= heap.size()) {
            return;
        }
        int leftChild, rightChild, smallestIndex = index, size = heap.size();
        pair<int,pair<int,int>> tmp;
        if (getLeftChildIndex(index) < size && heap[getLeftChildIndex(index)].first < heap[smallestIndex].first ) {
            smallestIndex = getLeftChildIndex(index);
        }
        if (getRightChildIndex(index) < size && heap[getRightChildIndex(index)].first < heap[smallestIndex].first ) {
            smallestIndex = getRightChildIndex(index);
        }
        if (smallestIndex != index) {
            tmp = heap[smallestIndex];
            heap[smallestIndex] = heap[index];
            heap[index] = tmp;
            heapifyDown(smallestIndex);
        }
    }

public:
    void push(pair<int,pair<int,int>> k) {
        heap.push_back(k);
        heapifyUp(heap.size()-1);
    }
    void pop() {
        if (heap.empty()) {
            return;
        }
        heap[0] = heap.back();
        heap.pop_back();
        heapifyDown(0);
    }
    pair<int,pair<int,int>> top() {
        return heap[0];
    }
    void print() {
        for (auto it = heap.begin(); it != heap.end(); it++) {
            cout << (*it).first << " ";
        }
    }
};

int main()
{
    MinHeap heap;
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