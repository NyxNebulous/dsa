#include <bits/stdc++.h>
using namespace std;

/* =======================
   BUBBLE SORT
   ======================= */

// Iterative Bubble Sort
void bubbleSortIter(vector<int>& a) {
    int n = a.size();
    for (int i = 0; i < n - 1; i++)
        for (int j = 0; j < n - i - 1; j++)
            if (a[j] > a[j + 1])
                swap(a[j], a[j + 1]);
}

// Recursive Bubble Sort
void bubbleSortRec(vector<int>& a, int n) {
    if (n == 1) return;
    for (int i = 0; i < n - 1; i++)
        if (a[i] > a[i + 1])
            swap(a[i], a[i + 1]);
    bubbleSortRec(a, n - 1);
}

/* =======================
   SELECTION SORT
   ======================= */

// Iterative Selection Sort
void selectionSortIter(vector<int>& a) {
    int n = a.size();
    for (int i = 0; i < n - 1; i++) {
        int minIdx = i;
        for (int j = i + 1; j < n; j++)
            if (a[j] < a[minIdx])
                minIdx = j;
        swap(a[i], a[minIdx]);
    }
}

// Recursive Selection Sort
void selectionSortRec(vector<int>& a, int i) {
    int n = a.size();
    if (i == n - 1) return;

    int minIdx = i;
    for (int j = i + 1; j < n; j++)
        if (a[j] < a[minIdx])
            minIdx = j;

    swap(a[i], a[minIdx]);
    selectionSortRec(a, i + 1);
}

/* =======================
   MERGE SORT
   ======================= */

void merge(vector<int>& a, int l, int m, int r) {
    vector<int> left(a.begin() + l, a.begin() + m + 1);
    vector<int> right(a.begin() + m + 1, a.begin() + r + 1);

    int i = 0, j = 0, k = l;
    while (i < left.size() && j < right.size())
        a[k++] = (left[i] <= right[j]) ? left[i++] : right[j++];

    while (i < left.size()) a[k++] = left[i++];
    while (j < right.size()) a[k++] = right[j++];
}

// Recursive Merge Sort
void mergeSortRec(vector<int>& a, int l, int r) {
    if (l >= r) return;
    int m = (l + r) / 2;
    mergeSortRec(a, l, m);
    mergeSortRec(a, m + 1, r);
    merge(a, l, m, r);
}

// Iterative Merge Sort
void mergeSortIter(vector<int>& a) {
    int n = a.size();
    for (int size = 1; size < n; size *= 2) {
        for (int l = 0; l < n - size; l += 2 * size) {
            int m = l + size - 1;
            int r = min(l + 2 * size - 1, n - 1);
            merge(a, l, m, r);
        }
    }
}

/* =======================
   LINEAR SEARCH
   ======================= */

// Iterative Linear Search
int linearSearchIter(vector<int>& a, int key) {
    for (int i = 0; i < a.size(); i++)
        if (a[i] == key) return i;
    return -1;
}

// Recursive Linear Search
int linearSearchRec(vector<int>& a, int key, int i) {
    if (i == a.size()) return -1;
    if (a[i] == key) return i;
    return linearSearchRec(a, key, i + 1);
}

/* =======================
   BINARY SEARCH (ARRAY MUST BE SORTED)
   ======================= */

// Iterative Binary Search
int binarySearchIter(vector<int>& a, int key) {
    int l = 0, r = a.size() - 1;
    while (l <= r) {
        int m = l + (r - l) / 2;
        if (a[m] == key) return m;
        if (a[m] < key) l = m + 1;
        else r = m - 1;
    }
    return -1;
}

// Recursive Binary Search
int binarySearchRec(vector<int>& a, int l, int r, int key) {
    if (l > r) return -1;
    int m = l + (r - l) / 2;
    if (a[m] == key) return m;
    if (a[m] < key) return binarySearchRec(a, m + 1, r, key);
    return binarySearchRec(a, l, m - 1, key);
}

/* =======================
   DRIVER
   ======================= */

int main() {
    vector<int> a = {5, 2, 9, 1, 5, 6};

    // Sorting
    bubbleSortIter(a);
    // bubbleSortRec(a, a.size());
    // selectionSortIter(a);
    // selectionSortRec(a, 0);
    // mergeSortRec(a, 0, a.size() - 1);
    // mergeSortIter(a);

    // Searching
    int key = 5;
    cout << "Linear Iter: " << linearSearchIter(a, key) << endl;
    cout << "Linear Rec : " << linearSearchRec(a, key, 0) << endl;
    cout << "Binary Iter: " << binarySearchIter(a, key) << endl;
    cout << "Binary Rec : " << binarySearchRec(a, 0, a.size() - 1, key) << endl;

    return 0;
}
