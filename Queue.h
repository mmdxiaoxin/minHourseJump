#pragma once
#include "List.h"

template <typename T, template<typename> class Container = List>
class Queue {
private:
    Container<T> container;

public:
    void push(const T& val);
    void pop();
    T& front();
    const T& front() const;
    bool empty() const;
    size_t size() const;
};

template <typename T, template<typename> class Container>
void Queue<T, Container>::push(const T& val) {
    container.push_back(val);
}

template <typename T, template<typename> class Container>
void Queue<T, Container>::pop() {
    container.pop_front();
}

template <typename T, template<typename> class Container>
T& Queue<T, Container>::front() {
    return container.front();
}

template <typename T, template<typename> class Container>
const T& Queue<T, Container>::front() const {
    return container.front();
}

template <typename T, template<typename> class Container>
bool Queue<T, Container>::empty() const {
    return container.empty();
}

template <typename T, template<typename> class Container>
size_t Queue<T, Container>::size() const {
    return container.size();
}

