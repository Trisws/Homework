#include <iostream>
using namespace std;

int findMin(int nums[], int low, int high) {
    while (low < high) {
        int mid = low + (high - low) / 2;
        if (nums[mid] > nums[high]) {
            low = mid + 1;
        } else {
            high = mid;
        }
    }
    return nums[low];
}

int main() {
    int n;
    cin >> n;
    int nums[100];  // Giới hạn mảng có 100 phần tử
    for (int i = 0; i < n; i++) {
        cin >> nums[i];
    }
    int result = findMin(nums, 0, n - 1);
    cout << result << endl;
    return 0;
}
