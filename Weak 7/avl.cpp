#include <iostream>
#include <vector>

using namespace std;

struct NODE{
 int key;
 NODE* p_left;
 NODE* p_right;
 int height;
 };
 int getHeight(NODE* node) {
    if (node == nullptr)
        return 0;
    return node->height;
}
int getBalanceFactor(NODE* node) {
    if (node == nullptr)
        return 0;
    return getHeight(node->p_left) - getHeight(node->p_right);
}
 NODE* createNode(int data){
    NODE* newNode = new NODE();
    newNode->key = data;
    newNode->p_left = nullptr;
    newNode->p_right = nullptr;
    newNode->height = 1;
    return newNode;
 }
 NODE* rightRotate(NODE* y) {
    NODE* x = y->p_left;
    NODE* T2 = x->p_right;
    x->p_right = y;
    y->p_left = T2;
    y->height = max(getHeight(y->p_left), getHeight(y->p_right)) + 1;
    x->height = max(getHeight(x->p_left), getHeight(x->p_right)) + 1;
    return x;
}
NODE* leftRotate(NODE* x) {
    NODE* y = x->p_right;
    NODE* T2 = y->p_left;
    y->p_left = x;
    x->p_right = T2;
    x->height = max(getHeight(x->p_left), getHeight(x->p_right)) + 1;
    y->height = max(getHeight(y->p_left), getHeight(y->p_right)) + 1;
    return y;
}
 void Insert(NODE* &pRoot, int x){
    if (pRoot == nullptr) {
        pRoot = createNode(x);
        return;
    }

    if (x < pRoot->key)
        Insert(pRoot->p_left, x);
    else if (x > pRoot->key)
        Insert(pRoot->p_right, x);
    else
        return;
    pRoot->height = 1 + max(getHeight(pRoot->p_left), getHeight(pRoot->p_right));
    int balance = getBalanceFactor(pRoot);
    // Trường hợp Left Left (LL)
    if (balance > 1 && x < pRoot->p_left->key) {
        pRoot = rightRotate(pRoot);
        return;
    }

    // Trường hợp Right Right (RR)
    if (balance < -1 && x > pRoot->p_right->key) {
        pRoot = leftRotate(pRoot);
        return;
    }

    // Trường hợp Left Right (LR)
    if (balance > 1 && x > pRoot->p_left->key) {
        pRoot->p_left = leftRotate(pRoot->p_left);
        pRoot = rightRotate(pRoot);
        return;
    }

    // Trường hợp Right Left (RL)
    if (balance < -1 && x < pRoot->p_right->key) {
        pRoot->p_right = rightRotate(pRoot->p_right);
        pRoot = leftRotate(pRoot);
        return;
    }
 }
 NODE* findMinValueNode(NODE* node) {
    NODE* current = node;

    // Tìm lá trái nhất
    while (current->p_left != nullptr)
        current = current->p_left;

    return current;
}

 void Remove(NODE* &pRoot, int x){
    if (pRoot == nullptr)
        return;

    if (x < pRoot->key)
        Remove(pRoot->p_left, x);
    else if (x > pRoot->key)
        Remove(pRoot->p_right, x);
    else {
        if ((pRoot->p_left == nullptr) || (pRoot->p_right == nullptr)) {
            NODE* temp = pRoot->p_left ? pRoot->p_left : pRoot->p_right;
            if (temp == nullptr) {
                temp = pRoot;
                pRoot = nullptr;
            } else
                *pRoot = *temp;

            delete temp;
        } else {
            NODE* temp = findMinValueNode(pRoot->p_right);
            pRoot->key = temp->key;
            Remove(pRoot->p_right, temp->key);
        }
    }
    if (pRoot == nullptr)
        return;
    pRoot->height = 1 + max(getHeight(pRoot->p_left), getHeight(pRoot->p_right));
    int balance = getBalanceFactor(pRoot);

    // Trường hợp Left Left (LL)
    if (balance > 1 && getBalanceFactor(pRoot->p_left) >= 0) {
        pRoot = rightRotate(pRoot);
        return;
    }

    // Trường hợp Left Right (LR)
    if (balance > 1 && getBalanceFactor(pRoot->p_left) < 0) {
        pRoot->p_left = leftRotate(pRoot->p_left);
        pRoot = rightRotate(pRoot);
        return;
    }

    // Trường hợp Right Right (RR)
    if (balance < -1 && getBalanceFactor(pRoot->p_right) <= 0) {
        pRoot = leftRotate(pRoot);
        return;
    }

    // Trường hợp Right Left (RL)
    if (balance < -1 && getBalanceFactor(pRoot->p_right) > 0) {
        pRoot->p_right = rightRotate(pRoot->p_right);
        pRoot = leftRotate(pRoot);
        return;
    }

 }
 bool isAVL(NODE* pRoot){
    if (pRoot == nullptr)
        return true;
    int balance = getBalanceFactor(pRoot);
    if (balance < -1 || balance > 1)
        return false;
    int actualHeight = 1 + max(getHeight(pRoot->p_left), getHeight(pRoot->p_right));
    if (pRoot->height != actualHeight)
        return false;
    return isAVL(pRoot->p_left) && isAVL(pRoot->p_right);
 }