#pragma once
#include "List.h"

template <typename T>
class Queue {
private:
    List<T> container;

public:
    void push(const T& val);
    void pop();
    T& front();
    const T& front() const;
    bool empty() const;
    size_t size() const;
};

template <typename T>
void Queue<T>::push(const T& val) {
    container.push_back(val);
}

template <typename T>
void Queue<T>::pop() {
    container.pop_front();
}

template <typename T>
T& Queue<T>::front() {
    return container.front();
}

template <typename T>
const T& Queue<T>::front() const {
    return container.front();
}

template <typename T>
bool Queue<T>::empty() const {
    return container.empty();
}

template <typename T>
size_t Queue<T>::size() const {
    return container.size();
}

