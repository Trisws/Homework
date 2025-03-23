#include <iostream>
using namespace std;

int factorial(int n){
    // Điều kiện dừng: nếu n = 0, trả về 1 (0! = 1)
    if (n == 0) return 1;
    else{
        // Đệ quy: n! = n * (n-1)!
        return n * factorial(n-1);
    }
}

int main(){
    int n;
    cout << "Enter a number: ";
    cin >> n;
    // In ra kết quả giai thừa của n
    cout << "Factorial of " << n << " is " << factorial(n) << endl;
    return 0;
}
