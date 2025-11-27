#include <iostream>
#include <vector>
#include <algorithm>
#include <windows.h>
using namespace std;

void print(const vector<int>& a) {
    for (int x : a) cout << x << " ";
    cout << "\n";
}

// сортировка вставками
void insertionSort(vector<int>& a) {
    for (int i = 1; i < a.size(); i++) {
        int key = a[i];
        int j = i - 1;
        while (j >= 0 && a[j] > key) {
            a[j + 1] = a[j];
            j--;
        }
        a[j + 1] = key;
    }
}

// сорт. выбором
void selectionSort(vector<int>& a) {
    for (int i = 0; i < a.size() - 1; i++) {
        int minIndex = i;
        for (int j = i + 1; j < a.size(); j++) {
            if (a[j] < a[minIndex])
                minIndex = j;
        }
        swap(a[i], a[minIndex]);
    }
}

//  блочная
void bucketSort(vector<int>& a) {
    int maxVal = *max_element(a.begin(), a.end());
    int bucketCount = 10;

    vector<vector<int>> buckets(bucketCount);

    for (int x : a) {
        int index = (x * bucketCount) / (maxVal + 1);
        buckets[index].push_back(x);
    }

    a.clear();

    for (auto& bucket : buckets) {
        sort(bucket.begin(), bucket.end());
        for (int x : bucket)
            a.push_back(x);
    }
}

// поразрядочная
int getMax(const vector<int>& a) {
    return *max_element(a.begin(), a.end());
}

void countingSortDigit(vector<int>& a, int exp) {
    vector<int> output(a.size());
    int count[10] = { 0 };

    for (int x : a)
        count[(x / exp) % 10]++;

    for (int i = 1; i < 10; i++)
        count[i] += count[i - 1];

    for (int i = a.size() - 1; i >= 0; i--) {
        int digit = (a[i] / exp) % 10;
        output[count[digit] - 1] = a[i];
        count[digit]--;
    }

    a = output;
}

void radixSort(vector<int>& a) {
    int maxVal = getMax(a);
    for (int exp = 1; maxVal / exp > 0; exp *= 10)
        countingSortDigit(a, exp);
}


int main() {
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);

    vector<int> base = { 10, 5, 14, 7, 3, 2, 18, 4, 5, 13, 6, 8 };

    cout << "Исходный массив:\n";
    print(base);
    cout << "\n";

    vector<int> a;

    a = base;
    insertionSort(a);
    cout << "Сортировка вставками:\n";
    print(a);
    cout << "\n";

    a = base;
    selectionSort(a);
    cout << "Сортировка выбором:\n";
    print(a);
    cout << "\n";

    a = base;
    bucketSort(a);
    cout << "Блочная сортировка:\n";
    print(a);
    cout << "\n";

    a = base;
    radixSort(a);
    cout << "Поразрядная сортировка:\n";
    print(a);
    cout << "\n";

    return 0;
}
