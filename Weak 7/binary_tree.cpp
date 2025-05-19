#include <iostream>
#include <vector>
using namespace std;
#include <algorithm>
#include <string>
#include <queue>
struct NODE{
 int key;
 NODE* p_left;
 NODE* p_right;
 };

 NODE* createNode(int data){
    NODE* newNode = new NODE();
    newNode->key = data;
    newNode->p_left = NULL;
    newNode->p_right = NULL;
    return newNode;
 }
//Duyệt cây nhị phân theo thứ tự trước (Node-Left-Right) và trả về một vector chứa các khóa của các nút đã được thăm.
vector<int> NLR (NODE* pRoot){
    vector<int> result;
    if (pRoot == nullptr) return result;
    result.push_back(pRoot->key);
    vector<int> left = NLR(pRoot->p_left);
    vector<int> right = NLR(pRoot->p_right);
    result.insert(result.end(), left.begin(), left.end());
    result.insert(result.end(), right.begin(), right.end());
    return result;
}
//  Duyệt cây theo thứ tự giữa (Left-Node-Right) và trả về một vector các khóa của các nút đã thăm
vector<int> LNR (NODE* pRoot){
    vector<int> result;
    if (pRoot == nullptr) return result;
    vector<int> left = LNR(pRoot->p_left);
    result.push_back(pRoot->key);
    vector<int> right = LNR(pRoot->p_right);
    result.insert(result.end(), left.begin(), left.end());
    result.insert(result.end(), right.begin(), right.end());
    return result;
}
vector<int> LRN(NODE* pRoot){
    vector<int> result;
    if (pRoot == nullptr) return result;
    vector<int> left = LRN(pRoot->p_left);
    vector<int> right = LRN(pRoot->p_right);
    result.push_back(pRoot->key);
    result.insert(result.end(), left.begin(),left.end());
    result.insert(result.end(), right.begin(), left.end());
    return result;
}
//Duyệt cây theo từng cấp độ và trả về một vector 2D trong đó mỗi vector con lưu trữ các khóa của các nút ở cấp độ đó.
vector<vector<int>> LevelOrder(NODE* pRoot){
    vector<vector<int>> result;
    if (pRoot == nullptr) return result;
    queue<NODE*> q;
    q.push(pRoot);
    while (!q.empty()) {
        vector<int> curLevel;
        int size = q.size();
        for (int i=0;i<size;i++){
            NODE* curNode = q.front();
            q.pop();
            curLevel.push_back(curNode->key);
            if (curNode->p_left != nullptr) q.push(curNode->p_left);
            if (curNode->p_right != nullptr) q.push(curNode->p_right);

        }
        result.push_back(curLevel);
    }
    return result;
}
int countNode(NODE* pRoot){
    if (pRoot == nullptr) return 0;
    int l = countNode(pRoot->p_left);
    int r = countNode(pRoot->p_right);
    return 1 + l + r;
}
int sumNode(NODE* pRoot){
    if (pRoot == nullptr) return 0;
    int l = sumNode(pRoot->p_left);
    int r = sumNode(pRoot->p_right);
    return pRoot->key + l + r;
}
int getHeight(NODE* node) {
    if (node == nullptr) {
        return -1;
    }
    return 1 + std::max(getHeight(node->p_left), getHeight(node->p_right));
}
int heightNode(NODE* pRoot, int value){
    if (pRoot == nullptr) return -1;
    if (pRoot->key == value) return getHeight(pRoot);
    int l = heightNode(pRoot->p_left,value);
    if (l != -1) return l;
    return heightNode(pRoot->p_right,value);
}
int Level(NODE* pRoot, NODE* p){
    if(pRoot == nullptr) return -1;
    int h = -1;
    if ((pRoot == p) || (h = Level(pRoot->p_left, p)) >= 0 || (h = Level(pRoot->p_right,p)>=0 )) return h + 1;
    return h; 
}
int countLeaf(NODE* pRoot){
    if (pRoot == nullptr) return 0;
    if (pRoot->p_left == nullptr && pRoot->p_right == nullptr) return 1;
    return countLeaf(pRoot->p_left) + countLeaf(pRoot->p_right);
}
