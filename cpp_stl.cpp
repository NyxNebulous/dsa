#include <iostream>
using namespace std;

template <typename T>
class Vector
{
    T *arr;
    int capacity;
    int length;

    void expand()
    {
        capacity = capacity ? capacity * 2 : 1;
        T *newArr = new T[capacity];
        for (int i = 0; i < length; i++)
            newArr[i] = arr[i];
        delete[] arr;
        arr = newArr;
    }

public:
    Vector()
    {
        arr = nullptr;
        capacity = 0;
        length = 0;
    }

    void push_back(T val)
    {
        if (length == capacity)
            expand();
        arr[length++] = val;
    }

    void pop_back()
    {
        if (length > 0)
            length--;
    }

    T &operator[](int i) { return arr[i]; }
    const T &operator[](int i) const { return arr[i]; }

    int size() const { return length; }
    int max_size() const { return capacity; }
    bool empty() const { return length == 0; }

    ~Vector() { delete[] arr; }
};

template <typename T>
class Stack
{
    T *arr;
    int capacity;
    int topIndex;

    void expand()
    {
        capacity = capacity ? capacity * 2 : 1;
        T *newArr = new T[capacity];
        for (int i = 0; i <= topIndex; i++)
            newArr[i] = arr[i];
        delete[] arr;
        arr = newArr;
    }

public:
    Stack()
    {
        arr = nullptr;
        capacity = 0;
        topIndex = -1;
    }

    void push(T val)
    {
        if (topIndex + 1 == capacity)
            expand();
        arr[++topIndex] = val;
    }

    void pop()
    {
        if (topIndex != -1)
            topIndex--;
    }

    T &top() { return arr[topIndex]; }
    bool empty() const { return topIndex == -1; }
    int size() const { return topIndex + 1; }

    ~Stack() { delete[] arr; }
};

template <typename T>
class Queue
{
    T *arr;
    int capacity;
    int head;
    int tail;
    int count;

    void expand()
    {
        int newCap = capacity ? capacity * 2 : 1;
        T *newArr = new T[newCap];

        for (int i = 0; i < count; i++)
            newArr[i] = arr[(head + i) % capacity];

        delete[] arr;
        arr = newArr;
        head = 0;
        tail = count;
        capacity = newCap;
    }

public:
    Queue()
    {
        arr = nullptr;
        capacity = 0;
        head = 0;
        tail = 0;
        count = 0;
    }

    void push(T val)
    {
        if (count == capacity)
            expand();
        arr[tail] = val;
        tail = (tail + 1) % capacity;
        count++;
    }

    void pop()
    {
        if (count > 0)
        {
            head = (head + 1) % capacity;
            count--;
        }
    }

    T &front() { return arr[head]; }
    T &back() { return arr[(tail - 1 + capacity) % capacity]; }

    bool empty() const { return count == 0; }
    int size() const { return count; }

    ~Queue() { delete[] arr; }
};


template <typename T>
class PriorityQueue {
    T *arr;
    int capacity;
    int count;

    void resize() {
        int newCap = capacity ? capacity * 2 : 1;
        T *newArr = new T[newCap];
        for (int i = 0; i < count; i++) {
            newArr[i] = arr[i];
        }
        delete[] arr;
        arr = newArr;
        capacity = newCap;
    }

    void sortDescending() {  // Largest element at front like max-heap
        for (int i = 0; i < count - 1; i++) {
            for (int j = i + 1; j < count; j++) {
                if (arr[i] < arr[j]) {
                    swap(arr[i], arr[j]);
                }
            }
        }
    }

public:
    PriorityQueue() {
        arr = nullptr;
        capacity = 0;
        count = 0;
    }

    void push(T val) {
        if (count == capacity) resize();
        arr[count++] = val;
        sortDescending();
    }

    void pop() {
        if (count > 0) count--;
    }

    T& top() {
        return arr[0];
    }

    bool empty() { return count == 0; }
    int size() { return count; }
};
