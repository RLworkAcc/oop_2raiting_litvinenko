#include <iostream>
#include <vector>
using namespace std;


// быстрая сортировка
int partitionQS(vector<int>& a, int low, int high) {
    int pivot = a[(low + high) / 2];
    while (low <= high) {
        while (a[low] < pivot) low++;
        while (a[high] > pivot) high--;
        if (low <= high) {
            swap(a[low], a[high]);
            low++;
            high--;
        }
    }
    return low;
}

void quickSort(vector<int>& a, int low, int high) {
    if (low >= high) return;
    int index = partitionQS(a, low, high);
    quickSort(a, low, index - 1);
    quickSort(a, index, high);
}


// слиянием
void merge(vector<int>& a, int l, int m, int r) {
    int i = l, j = m + 1;
    vector<int> tmp;
    tmp.reserve(r - l + 1);

    while (i <= m && j <= r) {
        if (a[i] < a[j]) tmp.push_back(a[i++]);
        else tmp.push_back(a[j++]);
    }
    while (i <= m) tmp.push_back(a[i++]);
    while (j <= r) tmp.push_back(a[j++]);

    for (int k = 0; k < tmp.size(); k++) {
        a[l + k] = tmp[k];
    }
}

void mergeSort(vector<int>& a, int l, int r) {
    if (l >= r) return;
    int m = (l + r) / 2;
    mergeSort(a, l, m);
    mergeSort(a, m + 1, r);
    merge(a, l, m, r);
}


// пирамида
void heapify(vector<int>& a, int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && a[left] > a[largest])
        largest = left;
    if (right < n && a[right] > a[largest])
        largest = right;

    if (largest != i) {
        swap(a[i], a[largest]);
        heapify(a, n, largest);
    }
}

void heapSort(vector<int>& a) {
    int n = a.size();
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(a, n, i);

    for (int i = n - 1; i > 0; i--) {
        swap(a[0], a[i]);
        heapify(a, i, 0);
    }
}


// пузырьковая
void bubbleSort(vector<int>& a) {
    int n = a.size();
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (a[j] > a[j + 1]) {
                swap(a[j], a[j + 1]);
            }
        }
    }
}


// мейн
int main() {
    vector<int> data = { 10, 5, 14, 7, 3, 2, 18, 4, 5, 13, 6, 8 };

    cout << "Original array:\n";
    for (int x : data) cout << x << " ";
    cout << "\n\n";

    vector<int> a1 = data;
    bubbleSort(a1);

    vector<int> a2 = data;
    quickSort(a2, 0, a2.size() - 1);

    vector<int> a3 = data;
    mergeSort(a3, 0, a3.size() - 1);

    vector<int> a4 = data;
    heapSort(a4);

    cout << "Quick sort:\n";
    for (int x : a2) cout << x << " ";
    cout << "\n\n";

    cout << "Merge sort:\n";
    for (int x : a3) cout << x << " ";
    cout << "\n\n";

    cout << "Heap sort:\n";
    for (int x : a4) cout << x << " ";
    cout << "\n";

    cout << "Bubble sort:\n";
    for (int x : a1) cout << x << " ";
    cout << "\n\n";

    return 0;
}
