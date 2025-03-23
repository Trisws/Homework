#include <iostream>
using namespace std;

bool isSorted(int arr[], int n) {
    if (n == 1 || n == 0) {
        return true;
    }
    if (arr[n - 1] < arr[n - 2]) {
        return false;
    }
    return isSorted(arr, n - 1);
}

int main() {
    int arr[] = {1, 2, 3, 4, 5};
    int n = sizeof(arr) / sizeof(arr[0]);

    if (isSorted(arr, n)) {
        cout << "Mảng đã được sắp xếp" << endl;
    } else {
        cout << "Mảng không được sắp xếp" << endl;
    }

    return 0;
}
