#pragma once

template<typename T>
class Vector {
private:
	T* data;
	size_t capacity_;
	size_t size_;

public:
	Vector();
	Vector(size_t n, const T& elem = T());
	Vector(const Vector& other);
	Vector(Vector&& other);
	Vector(T* begin, T* end);
	~Vector();
	size_t capacity() const;
	size_t size() const;
	T& operator[](int idx);
	const T& operator[](int idx) const;
	Vector<T>& operator=(const Vector& other);
	Vector<T>& operator=(Vector&& other);
	void push_back(const T& elem);
	void pop_back();
	T& front();
	T& back();
	T* begin() const;
	T* end() const;
	void insert(T* pos, const T& elem);
	void insert(T* pos, size_t n, const T& elem);
	template<typename Iter>
	void insert(T* pos, Iter begin, Iter end);
	T* erase(T* pos);
	T* erase(T* begin, T* end);
	bool empty() const;
	void resize(size_t newSize);
	template<typename U>
	void resize(size_t newSize, const U& elem = U());
	void reverse(T* pos1, T* pos2);

private:
	void reserve(size_t newCapacity);
};

template<typename T>
Vector<T>::Vector() : data(nullptr), capacity_(0), size_(0) {}

template<typename T>
Vector<T>::Vector(size_t n, const T& elem) : data(nullptr), capacity_(n), size_(n) {
	data = new T[capacity_];
	for (size_t i = 0; i < size_; ++i) {
		data[i] = elem;
	}
}

template<typename T>
Vector<T>::Vector(const Vector& other) : data(nullptr), capacity_(other.size_), size_(other.size_) {
	data = new T[capacity_];
	for (size_t i = 0; i < size_; ++i) {
		data[i] = other.data[i];
	}
}

template<typename T>
Vector<T>::Vector(Vector&& other) : data(other.data), capacity_(other.capacity_), size_(other.size_) {
	other.data = nullptr;
	other.capacity_ = 0;
	other.size_ = 0;
}

template<typename T>
Vector<T>::Vector(T* begin, T* end) : data(nullptr), capacity_(end - begin), size_(end - begin) {
	data = new T[capacity_];
	for (size_t i = 0; i < size_; ++i) {
		data[i] = begin[i];
	}
}

template<typename T>
Vector<T>::~Vector() {
	delete[] data;
}

template<typename T>
size_t Vector<T>::capacity() const {
	return capacity_;
}

template<typename T>
size_t Vector<T>::size() const {
	return size_;
}

template<typename T>
T& Vector<T>::operator[](int idx) {
	if (idx < 0 || idx >= size_) {
		throw std::out_of_range("Index out of range");
	}
	return data[idx];
}

template<typename T>
const T& Vector<T>::operator[](int idx) const {
	if (idx < 0 || idx >= size_) {
		throw std::out_of_range("Index out of range");
	}
	return data[idx];
}

template<typename T>
Vector<T>& Vector<T>::operator=(const Vector& other) {
	if (this == &other) {
		return *this;
	}

	delete[] data;
	capacity_ = other.size_;
	size_ = other.size_;
	data = new T[capacity_];
	for (size_t i = 0; i < size_; ++i) {
		data[i] = other.data[i];
	}

	return *this;
}

template<typename T>
Vector<T>& Vector<T>::operator=(Vector&& other) {
	if (this == &other) {
		return *this;
	}

	delete[] data;

	data = other.data;
	capacity_ = other.capacity_;
	size_ = other.size_;

	other.data = nullptr;
	other.capacity_ = 0;
	other.size_ = 0;

	return *this;
}


template<typename T>
void Vector<T>::push_back(const T& elem) {
	if (size_ == capacity_) {
		if (capacity_ == 0) {
			reserve(1);
		} else {
			reserve(2 * capacity_);
		}
	}
	data[size_] = elem;
	size_++;
}

template<typename T>
void Vector<T>::pop_back() {
	if (size_ > 0) {
		size_--;
	}
}

template<typename T>
T& Vector<T>::front() {
	if (size_ == 0) {
		throw std::length_error("Vector is empty");
	}
	return data[0];
}

template<typename T>
T& Vector<T>::back() {
	if (size_ == 0) {
		throw std::length_error("Vector is empty");
	}
	return data[size_ - 1];
}

template<typename T>
T* Vector<T>::begin() const {
	return data;
}

template<typename T>
T* Vector<T>::end() const {
	return data + size_;
}

template<typename T>
void Vector<T>::insert(T* pos, const T& elem) {
	if (pos < data || pos > data + size_) {
		throw std::out_of_range("Invalid position");
	}
	size_t idx = pos - data;
	if (size_ == capacity_) {
		size_t newCapacity = (capacity_ == 0) ? 1 : 2 * capacity_;
		reserve(newCapacity);
		pos = data + idx;
	}
	for (size_t i = size_; i > idx; i--) {
		data[i] = data[i - 1];
	}
	data[idx] = elem;
	size_++;
}

template<typename T>
void Vector<T>::insert(T* pos, size_t n, const T& elem) {
	for (size_t i = 0; i < n; i++) {
		insert(pos, elem);
		pos++;
	}
}

template<typename T>
template<typename Iter>
void Vector<T>::insert(T* pos, Iter begin, Iter end) {
	size_t count = 0;
	Iter it = begin;
	while (it != end) {
		count++;
		++it;
	}

	for (size_t i = 0; i < count; i++) {
		insert(pos, *begin);
		pos++;
		begin++;
	}
}

template<typename T>
template<typename U>
void Vector<T>::resize(size_t newSize, const U& elem) {
	if (newSize > size_) {
		if (newSize > capacity_) {
			reserve(newSize);
		}
		for (size_t i = size_; i < newSize; ++i) {
			data[i] = elem;
		}
	} else if (newSize < size_) {
		for (size_t i = newSize; i < size_; ++i) {
			data[i].~T();
		}
	}
	size_ = newSize;
}

template<typename T>
T* Vector<T>::erase(T* pos) {
	if (pos < data || pos >= data + size_) {
		throw std::out_of_range("Invalid position");
	}
	size_t idx = pos - data;
	for (size_t i = idx; i < size_ - 1; i++) {
		data[i] = data[i + 1];
	}
	size_--;
	return pos;
}

template<typename T>
T* Vector<T>::erase(T* begin, T* end) {
	size_t count = end - begin;
	for (size_t i = 0; i < count; i++) {
		erase(begin);
	}
	return begin;
}

template<typename T>
bool Vector<T>::empty() const {
	return size_ == 0;
}

template<typename T>
void Vector<T>::resize(size_t newSize) {
	if (newSize > size_) {
		if (newSize > capacity_) {
			reserve(newSize);
		}
		for (size_t i = size_; i < newSize; ++i) {
			data[i] = T();
		}
	} else if (newSize < size_) {
		for (size_t i = newSize; i < size_; ++i) {
			data[i].~T();
		}
	}
	size_ = newSize;
}

template<typename T>
void Vector<T>::reverse(T* pos1, T* pos2) {
	if (pos1 < data || pos1 >= data + size_ || pos2 < data || pos2 >= data + size_) {
		throw std::out_of_range("Invalid position");
	}
	size_t idx1 = pos1 - data;
	size_t idx2 = pos2 - data;
	while (idx1 < idx2) {
		std::swap(data[idx1], data[idx2]);
		idx1++;
		idx2--;
	}
}

template<typename T>
void Vector<T>::reserve(size_t newCapacity) {
	T* newData = new T[newCapacity];
	for (size_t i = 0; i < size_; i++) {
		newData[i] = data[i];
	}
	delete[] data;
	data = newData;
	capacity_ = newCapacity;
}
