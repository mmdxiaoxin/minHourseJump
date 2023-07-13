#pragma once

template<typename T>
class Vector {
private:
	T* data;
	size_t capacity_;
	size_t size_;

public:
	/**
	 * 构造函数，创建一个空的 Vector 对象。
	 */
	Vector();

	/**
	 * 构造函数，创建一个指定大小并初始化元素的 Vector 对象。
	 *
	 * @param n 要创建的元素个数
	 * @param elem 初始化元素的值
	 */
	Vector(size_t n, const T& elem = T());

	/**
	 * 拷贝构造函数，创建一个与给定 Vector 对象相同的新对象。
	 *
	 * @param other 要拷贝的 Vector 对象
	 */
	Vector(const Vector& other);

	/**
	 * 移动构造函数，创建一个从给定 Vector 对象移动而来的新对象。
	 *
	 * @param other 要移动的 Vector 对象
	 */
	Vector(Vector&& other);

	/**
	 * 构造函数，根据给定范围内的元素创建一个 Vector 对象。
	 *
	 * @param begin 范围的起始迭代器
	 * @param end 范围的结束迭代器
	 */
	Vector(T* begin, T* end);

	/**
	 * 析构函数，销毁 Vector 对象，并释放占用的内存。
	 */
	~Vector();

	/**
	 * 获取 Vector 的容量。
	 *
	 * @return Vector 的容量
	 */
	size_t capacity() const;

	/**
	 * 获取 Vector 的大小。
	 *
	 * @return Vector 的大小
	 */
	size_t size() const;

	/**
	 * 访问 Vector 中指定索引处的元素。
	 *
	 * @param idx 要访问的元素的索引
	 * @return 索引处的元素的引用
	 */
	T& operator[](int idx);

	/**
	 * 访问 Vector 中指定索引处的元素（只读）。
	 *
	 * @param idx 要访问的元素的索引
	 * @return 索引处的元素的常引用
	 */
	const T& operator[](int idx) const;

	/**
	 * 将当前 Vector 对象赋值为另一个 Vector 对象的拷贝。
	 *
	 * @param other 要拷贝的 Vector 对象
	 * @return 拷贝后的当前 Vector 对象的引用
	 */
	Vector<T>& operator=(const Vector& other);

	/**
	 * 将当前 Vector 对象赋值为另一个 Vector 对象的移动。
	 *
	 * @param other 要移动的 Vector 对象
	 * @return 移动后的当前 Vector 对象的引用
	 */
	Vector<T>& operator=(Vector&& other);

	/**
	 * 在 Vector 的末尾添加一个元素。
	 *
	 * @param elem 要添加的元素的值
	 */
	void push_back(const T& elem);

	/**
	 * 移除 Vector 的最后一个元素。
	 */
	void pop_back();

	/**
	 * 获取 Vector 的第一个元素。
	 *
	 * @return Vector 的第一个元素的引用
	 */
	T& front();

	/**
	 * 获取 Vector 的最后一个元素。
	 *
	 * @return Vector 的最后一个元素的引用
	 */
	T& back();

	/**
	 * 获取指向 Vector 开始位置的指针。
	 *
	 * @return 指向 Vector 开始位置的指针
	 */
	T* begin() const;

	/**
	 * 获取指向 Vector 结束位置的指针。
	 *
	 * @return 指向 Vector 结束位置的指针
	 */
	T* end() const;

	/**
	 * 在指定位置插入一个元素。
	 *
	 * @param pos 插入元素的位置
	 * @param elem 要插入的元素的值
	 */
	void insert(T* pos, const T& elem);

	/**
	 * 在指定位置插入多个元素。
	 *
	 * @param pos 插入元素的位置
	 * @param n 要插入的元素个数
	 * @param elem 要插入的元素的值
	 */
	void insert(T* pos, size_t n, const T& elem);

	/**
	 * 在指定位置插入一个范围内的元素。
	 *
	 * @tparam Iter 迭代器类型
	 * @param pos 插入元素的位置
	 * @param begin 范围的起始迭代器
	 * @param end 范围的结束迭代器
	 */
	template<typename Iter>
	void insert(T* pos, Iter begin, Iter end);

	/**
	 * 移除 Vector 中指定位置的元素。
	 *
	 * @param pos 要移除的元素的位置
	 * @return 移除元素后下一个位置的指针
	 */
	T* erase(T* pos);

	/**
	 * 移除 Vector 中指定范围的元素。
	 *
	 * @param begin 范围的起始位置
	 * @param end 范围的结束位置
	 * @return 移除元素后下一个位置的指针
	 */
	T* erase(T* begin, T* end);

	/**
	 * 检查 Vector 是否为空。
	 *
	 * @return 如果 Vector 为空，则返回 true，否则返回 false
	 */
	bool empty() const;

	/**
	 * 调整 Vector 的大小。
	 *
	 * @param newSize 新的大小
	 */
	void resize(size_t newSize);

	/**
	 * 调整 Vector 的大小，并用给定元素进行填充。
	 *
	 * @tparam U 元素类型
	 * @param newSize 新的大小
	 * @param elem 填充元素的值
	 */
	template<typename U>
	void resize(size_t newSize, const U& elem = U());

	/**
	 * 反转 Vector 中指定范围的元素。
	 *
	 * @param pos1 范围的起始位置
	 * @param pos2 范围的结束位置
	 */
	void reverse(T* pos1, T* pos2);

private:
	/**
	 * 调整 Vector 的容量。
	 *
	 * @param newCapacity 新的容量
	 */
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
