#include <iostream>
using namespace std;

int minSubArrayLen(int target, int nums[], int n) {
    int left = 0, right = 0, sum = 0;
    int minLength = 1000000;  // Giá trị ban đầu lớn

    while (right < n) {
        sum += nums[right++];
        while (sum >= target) {
            minLength = minLength < (right - left) ? minLength : (right - left);
            sum -= nums[left++];
        }
    }
    return minLength == 1000000 ? 0 : minLength;
}

int main() {
    int target, n;
    cin >> target >> n;
    int nums[100];  // Giới hạn mảng có 100 phần tử
    for (int i = 0; i < n; i++) {
        cin >> nums[i];
    }
    int result = minSubArrayLen(target, nums, n);
    cout << result << endl;
    return 0;
}
