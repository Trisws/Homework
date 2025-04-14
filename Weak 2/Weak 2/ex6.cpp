#include <iostream>
using namespace std;

bool twoSum(int nums[], int n, int target) {
    int left = 0, right = n - 1;
    while (left < right) {
        int sum = nums[left] + nums[right];
        if (sum == target) {
            return true;
        } else if (sum < target) {
            left++;
        } else {
            right--;
        }
    }
    return false;
}

int main() {
    int n, target;
    cin >> n;
    int nums[100];  // Giới hạn mảng có 100 phần tử
    for (int i = 0; i < n; i++) {
        cin >> nums[i];
    }
    cin >> target;
    if (twoSum(nums, n, target)) {
        cout << "YES" << endl;
    } else {
        cout << "NO" << endl;
    }
    return 0;
}
