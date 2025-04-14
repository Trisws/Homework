#include <iostream>
using namespace std;

int sentinelLinearSearch(int a[], int n, int k) {
    int last = a[n - 1];  // Lưu giá trị cuối mảng
    a[n - 1] = k;         // Gán sentinel là k

    int i = 0;
    while (a[i] != k) {
        i++;
    }

    a[n - 1] = last;  // Khôi phục giá trị cuối mảng

    // Kiểm tra nếu tìm thấy trong dãy ban đầu, trả về chỉ số
    if (i < n - 1 || a[n - 1] == k)
        return i;
    
    return -1;
}

int main() {
    int n, k;
    cin >> n;
    int a[100];  // Giới hạn mảng có 100 phần tử
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    cin >> k;
    int result = sentinelLinearSearch(a, n, k);
    cout << result << endl;
    return 0;
}
