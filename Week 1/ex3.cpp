#include <iostream>
using namespace std;

void generateBinaryStrings(int n, string str) {
    // Điều kiện dừng: nếu n = 0, in chuỗi nhị phân hiện tại
    if (n == 0) {
        cout << str << endl;
    } else {
        // Đệ quy: thêm '0' vào chuỗi và gọi đệ quy
        generateBinaryStrings(n - 1, str + "0");
        // Đệ quy: thêm '1' vào chuỗi và gọi đệ quy
        generateBinaryStrings(n - 1, str + "1");
    }
}

int main() {
    int n;
    cout << "Enter a number: ";
    cin >> n;
    // Gọi hàm sinh chuỗi nhị phân cho độ dài n
    generateBinaryStrings(n, "");
    return 0;
}
