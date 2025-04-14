#include <iostream>
using namespace std;

void threeSum(int nums[], int n) {
    for (int i = 0; i < n - 2; i++) {
        int left = i + 1, right = n - 1;
        while (left < right) {
            int sum = nums[i] + nums[left] + nums[right];
            if (sum == 0) {
                cout << "[" << nums[i] << ", " << nums[left] << ", " << nums[right] << "]" << endl;
                left++;
                right--;
            } else if (sum < 0) {
                left++;
            } else {
                right--;
            }
        }
    }
}

int main() {
    int n;
    cin >> n;
    int nums[100];  // Giới hạn mảng có 100 phần tử
    for (int i = 0; i < n; i++) {
        cin >> nums[i];
    }
    threeSum(nums, n);
    return 0;
}
