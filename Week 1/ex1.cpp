#include <iostream>
using namespace std;

int fibonacci(int n) {
    // Khởi tạo mảng để lưu các giá trị Fibonacci
    int fib[n+1];
    fib[0] = 0; // F(0) = 0
    fib[1] = 1; // F(1) = 1
    // Tính giá trị Fibonacci cho các phần tử từ 2 đến n
    for (int i = 2; i <= n; i++) {
        fib[i] = fib[i - 1] + fib[i - 2]; // Công thức tính Fibonacci
    }
    return fib[n]; // Trả về giá trị Fibonacci của phần tử thứ n
}

int main() {
    int n;
    cout << "Nhập số n: ";
    cin >> n;
    
    cout << "Dãy Fibonacci từ 0 đến " << n << ": ";
    // In ra tất cả các giá trị Fibonacci từ 0 đến n
    for (int i = 0; i <= n; i++) {
        cout << fibonacci(i) << " ";
    }
    cout << endl;
    
    return 0;
}
