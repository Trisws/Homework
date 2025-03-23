#include <iostream>
using namespace std;

bool isSorted(int arr[], int n) {
    // Điều kiện dừng: nếu mảng chỉ có 1 phần tử hoặc không có phần tử nào, thì coi như đã sắp xếp
    if (n == 1 || n == 0) {
        return true;
    }

    // Kiểm tra xem phần tử hiện tại có nhỏ hơn hoặc bằng phần tử tiếp theo không
    if (arr[n - 1] < arr[n - 2]) {
        return false; // Nếu không, mảng không được sắp xếp
    }

    // Đệ quy kiểm tra các phần tử còn lại
    return isSorted(arr, n - 1);
}

int main() {
    int arr[] = {1, 2, 3, 4, 5}; // Thử với mảng đã sắp xếp
    int n = sizeof(arr) / sizeof(arr[0]);

    if (isSorted(arr, n)) {
        cout << "Mảng đã được sắp xếp" << endl;
    } else {
        cout << "Mảng không được sắp xếp" << endl;
    }

    return 0;
}
