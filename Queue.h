#pragma once
#include "List.h"

template <typename T>
class Queue {
private:
    List<T> container; // 底层容器使用链表实现

public:
    /**
     * 将元素推入队列的尾部。
     *
     * @param val 要推入队列的元素的值
     */
    void push(const T& val);

    /**
     * 弹出队列的头部元素。
     */
    void pop();

    /**
     * 获取队列的头部元素的引用。
     *
     * @return 队列的头部元素的引用
     */
    T& front();

    /**
     * 获取队列的头部元素的常引用。
     *
     * @return 队列的头部元素的常引用
     */
    const T& front() const;

    /**
     * 检查队列是否为空。
     *
     * @return 如果队列为空，则返回 true，否则返回 false
     */
    bool empty() const;

    /**
     * 获取队列中元素的个数。
     *
     * @return 队列中元素的个数
     */
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

