#include <iostream>
#include <cmath>
using namespace std;

bool canShipInDays(int weights[], int n, int days, int capacity) {
    int currentWeight = 0;
    int dayCount = 1;
    for (int i = 0; i < n; i++) {
        currentWeight += weights[i];
        if (currentWeight > capacity) {
            dayCount++;
            currentWeight = weights[i];
        }
    }
    return dayCount <= days;
}

int shipWithinDays(int weights[], int n, int days) {
    int left = 0;
    int right = 0;
    for (int i = 0; i < n; i++) {
        if (weights[i] > left) left = weights[i];
        right += weights[i];
    }

    while (left < right) {
        int mid = left + (right - left) / 2;
        if (canShipInDays(weights, n, days, mid)) {
            right = mid;
        } else {
            left = mid + 1;
        }
    }
    return left;
}

int main() {
    int n, days;
    cin >> n;
    int weights[100];  // Giới hạn mảng có 100 phần tử
    for (int i = 0; i < n; i++) {
        cin >> weights[i];
    }
    cin >> days;
    int result = shipWithinDays(weights, n, days);
    cout << result << endl;
    return 0;
}
