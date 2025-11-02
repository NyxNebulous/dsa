#include <bits/stdc++.h>
using namespace std;

struct Count {
    long long comparisons = 0;
    long long swaps = 0;
};

void bubbleSort(vector<int> arr, Count &c) {
    int n = arr.size();
    for(int i = 0; i < n - 1; i++){
        for(int j = 0; j < n - i - 1; j++){
            c.comparisons++;
            if(arr[j] > arr[j+1]){
                swap(arr[j], arr[j+1]);
                c.swaps++;
            }
        }
    }
}

void selectionSort(vector<int> arr, Count &c) {
    int n = arr.size();
    for(int i = 0; i < n - 1; i++){
        int minIdx = i;
        for(int j = i + 1; j < n; j++){
            c.comparisons++;
            if(arr[j] < arr[minIdx])
                minIdx = j;
        }
        if(minIdx != i) {
            swap(arr[minIdx], arr[i]);
            c.swaps++;
        }
    }
}

void insertionSort(vector<int> arr, Count &c) {
    int n = arr.size();
    for(int i = 1; i < n; i++){
        int key = arr[i];
        int j = i - 1;
        while(j >= 0){
            c.comparisons++;
            if(arr[j] > key){
                arr[j+1] = arr[j];
                c.swaps++;
                j--;
            }
            else break;
        }
        arr[j+1] = key;
    }
}

void merge(vector<int> &arr, int l, int m, int r, Count &c) {
    int n1 = m - l + 1, n2 = r - m;
    vector<int> L(n1), R(n2);
    for(int i = 0; i < n1; i++) L[i] = arr[l + i];
    for(int i = 0; i < n2; i++) R[i] = arr[m + 1 + i];

    int i = 0, j = 0, k = l;
    while(i < n1 && j < n2){
        c.comparisons++;
        if(L[i] <= R[j]) arr[k++] = L[i++];
        else arr[k++] = R[j++];
    }
    while(i < n1) arr[k++] = L[i++];
    while(j < n2) arr[k++] = R[j++];
}

void mergeSort(vector<int> &arr, int l, int r, Count &c) {
    if(l < r){
        int m = l + (r - l) / 2;
        mergeSort(arr, l, m, c);
        mergeSort(arr, m + 1, r, c);
        merge(arr, l, m, r, c);
    }
}

void heapify(vector<int> &arr, int n, int i, Count &c){
    int largest = i;
    int l = 2 * i + 1, r = 2 * i + 2;

    if(l < n){ c.comparisons++; if(arr[l] > arr[largest]) largest = l; }
    if(r < n){ c.comparisons++; if(arr[r] > arr[largest]) largest = r; }

    if(largest != i){
        swap(arr[i], arr[largest]);
        c.swaps++;
        heapify(arr, n, largest, c);
    }
}

void heapSort(vector<int> arr, Count &c){
    int n = arr.size();
    for(int i = n / 2 - 1; i >= 0; i--) heapify(arr, n, i, c);
    for(int i = n - 1; i > 0; i--){
        swap(arr[0], arr[i]);
        c.swaps++;
        heapify(arr, i, 0, c);
    }
}

int partitionQS(vector<int> &arr, int low, int high, Count &c){
    int pivot = arr[high];
    int i = low - 1;
    for(int j = low; j < high; j++){
        c.comparisons++;
        if(arr[j] <= pivot){
            i++;
            swap(arr[i], arr[j]);
            c.swaps++;
        }
    }
    swap(arr[i+1], arr[high]);
    c.swaps++;
    return i + 1;
}

void quickSort(vector<int> &arr, int low, int high, Count &c){
    if(low < high){
        int pi = partitionQS(arr, low, high, c);
        quickSort(arr, low, pi - 1, c);
        quickSort(arr, pi + 1, high, c);
    }
}

int main() {
    vector<int> arr = {10, 3, 5, 2, 8, 6};

    Count c1, c2, c3, c4, c5, c6;

    bubbleSort(arr, c1);
    selectionSort(arr, c2);
    insertionSort(arr, c3);

    vector<int> v4 = arr; mergeSort(v4, 0, v4.size() - 1, c4);
    heapSort(arr, c5);

    vector<int> v6 = arr; quickSort(v6, 0, v6.size() - 1, c6);

    cout << "Bubble Sort -> Comparisons: " << c1.comparisons << ", Swaps: " << c1.swaps << endl;
    cout << "Selection Sort -> Comparisons: " << c2.comparisons << ", Swaps: " << c2.swaps << endl;
    cout << "Insertion Sort -> Comparisons: " << c3.comparisons << ", Swaps: " << c3.swaps << endl;
    cout << "Merge Sort -> Comparisons: " << c4.comparisons << ", Swaps: " << c4.swaps << endl;
    cout << "Heap Sort -> Comparisons: " << c5.comparisons << ", Swaps: " << c5.swaps << endl;
    cout << "Quick Sort -> Comparisons: " << c6.comparisons << ", Swaps: " << c6.swaps << endl;

    return 0;
}
