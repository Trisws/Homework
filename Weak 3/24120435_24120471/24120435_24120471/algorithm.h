#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

/*---------------------------------------------------------------------*/

//Thuật toán bubble sort
void bubble_sort(vector<int>& a) {
    int n = a.size();
    bool swapped;
    for (int i = 0; i < n - 1; i++) { 
        swapped = false;
        for (int j = 0; j < n - i - 1; j++) { 
            if (a[j] > a[j + 1]) {
                swap(a[j], a[j + 1]);
                swapped = true;
            }
        }
        if (!swapped) break; 
    }
}


/*---------------------------------------------------------------------*/

//Thuật toán selection sort
void selection_sort(vector<int>& a) {
    int n = a.size();
    for (int i = 0; i < n - 1; i++) {
        int min = i;
        for (int j = i + 1; j < n; j++) {
            if (a[j] < a[min]) {
                min = j;
            }
        }
        if (min != i) {
            swap(a[i], a[min]);
        }
    }
}


/*---------------------------------------------------------------------*/

//Thuật toán shell sort
void shell_sort(vector<int>& a) {
    int n = a.size();
    for (int gap = n / 2; gap > 0; gap /= 2) { 
        for (int i = gap; i < n; i++) {
            int temp = a[i];
            int j = i;
            while (j >= gap && a[j - gap] > temp) {
                a[j] = a[j - gap];
                j -= gap;
            }
            a[j] = temp;
        }
    }
}


/*---------------------------------------------------------------------*/

//Thuật toán counting sort
void counting_sort(vector<int>& a) {
    if (a.empty()) return;
    int max_a = *max_element(a.begin(), a.end());  
    vector<int> count(max_a + 1, 0); 

    for (int num : a) {
        count[num]++;
    }

    int index = 0;
    for (int i = 0; i <= max_a; i++) {
        while (count[i] > 0) {
            a[index++] = i;
            count[i]--;
        }
    }
}

/*---------------------------------------------------------------------*/

//Thuật toán merge sort
void merge(vector<int>& a, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;
    vector<int> l(n1), r(n2);
    
    for (int i = 0; i < n1; i++) 
        l[i] = a[left + i]; 
    for (int i = 0; i < n2; i++) 
        r[i] = a[mid + 1 + i]; 

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (l[i] <= r[j]) {
            a[k] = l[i++];
        } else {
            a[k] = r[j++];
        }
        k++;
    }

    while (i < n1) a[k++] = l[i++];
    while (j < n2) a[k++] = r[j++];
}

void merge_sort(vector<int>& a, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        merge_sort(a, left, mid);
        merge_sort(a, mid + 1, right);
        merge(a, left, mid, right);
    }
}


/*---------------------------------------------------------------------*/

//Thuật toán flash sort
void flash_sort(vector<int>& a) {
    int n = a.size();

    if (n <= 1) return;

    int min_arr = a[0], max_i = 0;
    for (int i = 1; i < n; i++) {
        if (a[i] < min_arr) min_arr = a[i];
        if (a[i] > a[max_i]) max_i = i;
    }
    if (a[max_i] == min_arr) return;

    int m = int(0.45 * n); 
    vector<int> L(m, 0);
    double scale = (double)(m - 1) / (a[max_i] - min_arr);

    for (int i = 0; i < n; i++) {
        int index = scale * (a[i] - min_arr); 
        L[index]++;
    }

    for (int i = 1; i < m; i++) {
        L[i] += L[i - 1];
    }

    int i = 0, count = 0;
    while (count < n) {
        int index = scale * (a[i] - min_arr);
        while (i >= L[index]) {
            index = scale * (a[++i] - min_arr);
        }

        int temp = a[i];
        while (i != L[index]) {
            index = scale * (temp - min_arr);
            swap(temp, a[--L[index]]);
            count++;
        }
    }

    for (int i = 1; i < n; i++) {
        int key = a[i];
        int j = i - 1;
        while (j >= 0 && a[j] > key) {
            a[j + 1] = a[j];
            j--;
        }
        a[j + 1] = key;
    }
}

/*---------------------------------------------------------------------*/


void insertion_sort(vector<int>& arr) {
    int n = arr.size();
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}


/*---------------------------------------------------------------------*/

void shaker_sort(vector<int>& arr) {
    int n = arr.size();
    int left = 0;      
    int right = n - 1;   
    int temp;            

    while (left < right) {
        for (int i = left; i < right; i++) {
            if (arr[i] > arr[i + 1]) {
                temp = arr[i];
                arr[i] = arr[i + 1];
                arr[i + 1] = temp;
            }
        }
        right--;

        for (int i = right; i > left; i--) {
            if (arr[i] < arr[i - 1]) {
                temp = arr[i];
                arr[i] = arr[i - 1];
                arr[i - 1] = temp;
            }
        }
        left++;
    }
}

/*---------------------------------------------------------------------*/

void Heapify(vector<int>& arr, int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[left] > arr[largest])
        largest = left;
    if (right < n && arr[right] > arr[largest])
        largest = right;

    if (largest != i) {
        swap(arr[i], arr[largest]);
        Heapify(arr, n, largest);
    }
}

void heap_sort(vector<int>& arr) {
    int n = arr.size();

    for (int i = n / 2 - 1; i >= 0; i--)
        Heapify(arr, n, i);

    for (int i = n - 1; i >= 1; i--) {
        swap(arr[0], arr[i]);       
        Heapify(arr, i, 0);          
    }
}

/*---------------------------------------------------------------------*/

void quick_sort(vector<int>& arr, int low, int high) {
    if (low < high) {
        int pivot = arr[high];
        int i = (low - 1);
        for (int j = low; j < high; j++) {
            if (arr[j] < pivot) {
                i++;
                swap(arr[i], arr[j]);
            }
        }

        swap(arr[i + 1], arr[high]);
        int pi = i + 1;

        quick_sort(arr, low, pi - 1);
        quick_sort(arr, pi + 1, high);
    }
}

/*---------------------------------------------------------------------*/

void radix_sort(vector<int>& arr) {
    int n = arr.size();
    if (n <= 1) return; 

    int max_val = *max_element(arr.begin(), arr.end());

    for (int exp = 1; max_val / exp > 0; exp *= 10) {
        vector<int> output(n);
        int count[10] = {0};

        for (int i = 0; i < n; i++) {
            count[(arr[i] / exp) % 10]++;
        }

        for (int i = 1; i < 10; i++) {
            count[i] += count[i - 1];
        }

        for (int i = n - 1; i >= 0; i--) {
            int digit = (arr[i] / exp) % 10;
            output[count[digit] - 1] = arr[i];
            count[digit]--;
        }

        for (int i = 0; i < n; i++) {
            arr[i] = output[i];
        }
    }
}


/*---------------------------------------------------------------------*/
