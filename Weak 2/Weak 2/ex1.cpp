#include <iostream>
using namespace std;

int linearSearch(int a[], int n, int k) {
    for (int i = 0; i < n; i++) {
        if (a[i] == k) {
            return i;  // Trả về chỉ số nếu tìm thấy
        }
    }
    return -1;  // Nếu không tìm thấy
}

int main() {
    int n, k;
    cin >> n;
    int a[100];  // Giới hạn mảng có 100 phần tử
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    cin >> k;
    int result = linearSearch(a, n, k);
    cout << result << endl;
    return 0;
}
