#include <iostream>
using namespace std;

int fibonacci(int n) {
    int fib[n+1];
    fib[0] = 0;
    fib[1] = 1;
    for (int i = 2; i <= n; i++) {
        fib[i] = fib[i - 1] + fib[i - 2];
    }
    return fib[n];
}
int main() {
    int n;
    cout << "Nhập số n: ";
    cin >> n;
    
    cout << "Dãy Fibonacci từ 0 đến " << n << ": ";
    for (int i = 0; i <= n; i++) {
        cout << fibonacci(i) << " ";
    }
    cout << endl;
    
    return 0;
}