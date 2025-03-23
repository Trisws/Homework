#include <iostream>
using namespace std;

void towerOfHanoi(int n, char from_rod, char to_rod, char aux_rod) {
    // Điều kiện dừng: nếu chỉ còn 1 đĩa, di chuyển nó từ cột nguồn đến cột đích
    if (n == 1) {
        cout << "Move disk 1 from rod " << from_rod << " to rod " << to_rod << endl;
        return;
    }
    // Đệ quy: di chuyển n-1 đĩa từ cột nguồn đến cột phụ
    towerOfHanoi(n - 1, from_rod, aux_rod, to_rod);
    // Di chuyển đĩa thứ n từ cột nguồn đến cột đích
    cout << "Move disk " << n << " from rod " << from_rod << " to rod " << to_rod << endl;
    // Đệ quy: di chuyển n-1 đĩa từ cột phụ đến cột đích
    towerOfHanoi(n - 1, aux_rod, to_rod, from_rod);
}

int main() {
    int n;
    cout << "Enter the number of disks: ";
    cin >> n;
    // Gọi hàm giải quyết bài toán Tháp Hà Nội với n đĩa
    towerOfHanoi(n, 'A', 'C', 'B');
    return 0;
}
