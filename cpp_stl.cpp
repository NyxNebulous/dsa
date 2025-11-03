#include <iostream>
using namespace std;

template <typename T>
class Vector {
    T *arr;
    int capacity;
    int length;

    void expand() {
        capacity = (capacity == 0 ? 1 : capacity * 2);
        T *newArr = new T[capacity];
        for (int i = 0; i < length; i++)
            newArr[i] = arr[i];
        delete[] arr;
        arr = newArr;
    }

public:
    Vector() : arr(nullptr), capacity(0), length(0) {}

    void push_back(T val) {
        if (length == capacity) expand();
        arr[length++] = val;
    }

    void pop_back() {
        if (length > 0) length--;
    }

    T& operator[](int index) { return arr[index]; }
    const T& operator[](int index) const { return arr[index]; }

    int size() const { return length; }
    bool empty() const { return length == 0; }

    ~Vector() { delete[] arr; }
};

template <typename T>
class Stack {
    T *arr;
    int capacity;
    int topIndex;

    void expand() {
        capacity = (capacity == 0 ? 1 : capacity * 2);
        T *newArr = new T[capacity];
        for (int i = 0; i <= topIndex; i++)
            newArr[i] = arr[i];
        delete[] arr;
        arr = newArr;
    }

public:
    Stack() : arr(nullptr), capacity(0), topIndex(-1) {}

    void push(T val) {
        if (topIndex + 1 == capacity) expand();
        arr[++topIndex] = val;
    }

    void pop() {
        if (topIndex >= 0) topIndex--;
    }

    T& top() { return arr[topIndex]; }
    bool empty() const { return topIndex == -1; }

    ~Stack() { delete[] arr; }
};

template <typename T>
class Queue {
    T *arr;
    int capacity;
    int frontIndex;
    int rearIndex;
    int count;

    void expand() {
        int newCap = (capacity == 0 ? 1 : capacity * 2);
        T *newArr = new T[newCap];
        for (int i = 0; i < count; i++)
            newArr[i] = arr[(frontIndex + i) % capacity];
        delete[] arr;
        arr = newArr;
        capacity = newCap;
        frontIndex = 0;
        rearIndex = count - 1;
    }

public:
    Queue() : arr(nullptr), capacity(0), frontIndex(0), rearIndex(-1), count(0) {}

    void push(T val) {
        if (count == capacity) expand();
        rearIndex = (rearIndex + 1) % capacity;
        arr[rearIndex] = val;
        count++;
    }

    void pop() {
        if (count > 0) {
            frontIndex = (frontIndex + 1) % capacity;
            count--;
        }
    }

    T& front() { return arr[frontIndex]; }
    bool empty() const { return count == 0; }
    int size() const { return count; }

    ~Queue() { delete[] arr; }
};

template <typename T>
class LinkedList {
    struct Node {
        T data;
        Node *next;
        Node(T val) : data(val), next(nullptr) {}
    };

    Node *head;

public:
    LinkedList() : head(nullptr) {}

    void insertEnd(T val) {
        Node *newNode = new Node(val);
        if (!head) { head = newNode; return; }
        Node *temp = head;
        while (temp->next) temp = temp->next;
        temp->next = newNode;
    }

    void display() {
        Node *temp = head;
        while (temp) {
            cout << temp->data << " ";
            temp = temp->next;
        }
        cout << endl;
    }

    ~LinkedList() {
        Node *temp;
        while (head) {
            temp = head;
            head = head->next;
            delete temp;
        }
    }
};

template <typename T>
class PriorityQueue {
    T *arr;
    int capacity;
    int count;
    bool isMinQueue;

    void expand() {
        int newCap = capacity ? capacity * 2 : 1;
        T *newArr = new T[newCap];
        for (int i = 0; i < count; i++)
            newArr[i] = arr[i];
        delete[] arr;
        arr = newArr;
        capacity = newCap;
    }

    void sortQueue() {
        for (int i = 0; i < count - 1; i++)
            for (int j = i + 1; j < count; j++)
                if ((!isMinQueue && arr[i] < arr[j]) || (isMinQueue && arr[i] > arr[j]))
                    swap(arr[i], arr[j]);
    }

public:
    PriorityQueue(bool minQueue = false)
        : arr(nullptr), capacity(0), count(0), isMinQueue(minQueue) {}

    void push(T val) {
        if (count == capacity) expand();
        arr[count++] = val;
        sortQueue();
    }

    void pop() { if (count > 0) count--; }
    T& top() { return arr[0]; }
    bool empty() const { return count == 0; }

    ~PriorityQueue() { delete[] arr; }
};
