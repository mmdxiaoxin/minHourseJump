#pragma once

template <typename T>
class ListNode {
public:
	/**
	 * 节点存储的数据
	 */
	T data;

	/**
	 * 指向前一个节点的指针
	 */
	ListNode* prev;

	/**
	 * 指向后一个节点的指针
	 */
	ListNode* next;

	/**
	 * 构造函数，创建一个节点并初始化数据。
	 *
	 * @param val 节点存储的数据
	 */
	ListNode(const T& val) : data(val), prev(nullptr), next(nullptr) {}

	/**
	 * 默认构造函数，创建一个空节点。
	 */
	ListNode() : prev(nullptr), next(nullptr) {}
};

template <typename T>
class List {
private:
	ListNode<T>* head; // 头节点指针
	ListNode<T>* tail; // 尾节点指针
	size_t size_; // 链表的大小

public:
	/**
	 * 默认构造函数，创建一个空链表。
	 */
	List();

	/**
	 * 构造函数，创建一个指定大小并初始化元素的链表。
	 *
	 * @param n 链表的大小
	 * @param elem 初始化元素的值
	 */
	List(size_t n, const T& elem = T());

	/**
	 * 拷贝构造函数，创建一个与给定链表相同的新链表。
	 *
	 * @param other 要拷贝的链表
	 */
	List(const List& other);

	/**
	 * 移动构造函数，创建一个从给定链表移动而来的新链表。
	 *
	 * @param other 要移动的链表
	 */
	List(List&& other);

	/**
	 * 构造函数，根据给定范围内的节点创建一个链表。
	 *
	 * @param begin 范围的起始节点指针
	 * @param end 范围的结束节点指针
	 */
	List(ListNode<T>* begin, ListNode<T>* end);

	/**
	 * 析构函数，销毁链表，并释放占用的内存。
	 */
	~List();

	/**
	 * 将当前链表赋值为另一个链表的拷贝。
	 *
	 * @param other 要拷贝的链表
	 * @return 拷贝后的当前链表的引用
	 */
	List& operator=(const List& other);

	/**
	 * 将当前链表赋值为另一个链表的移动。
	 *
	 * @param other 要移动的链表
	 * @return 移动后的当前链表的引用
	 */
	List& operator=(List&& other);

	/**
	 * 获取链表的第一个元素。
	 *
	 * @return 链表的第一个元素的引用
	 */
	T& front();

	/**
	 * 获取链表的第一个元素（只读）。
	 *
	 * @return 链表的第一个元素的常引用
	 */
	const T& front() const;

	/**
	 * 获取链表的最后一个元素。
	 *
	 * @return 链表的最后一个元素的引用
	 */
	T& back();

	/**
	 * 获取链表的最后一个元素（只读）。
	 *
	 * @return 链表的最后一个元素的常引用
	 */
	const T& back() const;

	/**
	 * 获取链表的起始节点指针。
	 *
	 * @return 链表的起始节点指针
	 */
	ListNode<T>* begin();

	/**
	 * 获取链表的起始节点指针（只读）。
	 *
	 * @return 链表的起始节点指针的常引用
	 */
	const ListNode<T>* begin() const;

	/**
	 * 获取链表的结束节点指针。
	 *
	 * @return 链表的结束节点指针
	 */
	ListNode<T>* end();

	/**
	 * 在链表的末尾添加一个元素。
	 *
	 * @param val 要添加的元素的值
	 */
	void push_back(const T& val);

	/**
	 * 在链表的头部添加一个元素。
	 *
	 * @param val 要添加的元素的值
	 */
	void push_front(const T& val);

	/**
	 * 在指定位置插入一个元素。
	 *
	 * @param pos 插入位置的节点指针
	 * @param val 要插入的元素的值
	 */
	void insert(ListNode<T>* pos, const T& val);

	/**
	 * 在指定位置插入多个元素。
	 *
	 * @param pos 插入位置的节点指针
	 * @param n 要插入的元素个数
	 * @param val 要插入的元素的值
	 */
	void insert(ListNode<T>* pos, size_t n, const T& val);

	/**
	 * 在指定位置插入一个范围内的元素。
	 *
	 * @param pos 插入位置的节点指针
	 * @param begin 范围的起始节点指针
	 * @param end 范围的结束节点指针
	 */
	void insert(ListNode<T>* pos, ListNode<T>* begin, ListNode<T>* end);

	/**
	 * 移除链表的最后一个元素。
	 */
	void pop_back();

	/**
	 * 移除链表的第一个元素。
	 */
	void pop_front();

	/**
	 * 移除链表中指定范围的元素。
	 *
	 * @param begin 范围的起始节点指针
	 * @param end 范围的结束节点指针
	 */
	void erase(ListNode<T>* begin, ListNode<T>* end);

	/**
	 * 移除链表中与指定值相等的元素。
	 *
	 * @param val 要移除的元素的值
	 */
	void erase(const T& val);

	/**
	 * 清空链表，移除所有元素。
	 */
	void clear();

	/**
	 * 获取链表的大小。
	 *
	 * @return 链表的大小
	 */
	size_t size() const;

	/**
	 * 检查链表是否为空。
	 *
	 * @return 如果链表为空，则返回 true，否则返回 false
	 */
	bool empty() const;
};


template <typename T>
List<T>::List() : head(nullptr), tail(nullptr), size_(0) {}

template <typename T>
List<T>::List(size_t n, const T& elem) : head(nullptr), tail(nullptr), size_(0) {
	for (size_t i = 0; i < n; i++) {
		push_back(elem);
	}
}

template <typename T>
List<T>::List(const List& other) : head(nullptr), tail(nullptr), size_(0) {
	ListNode<T>* current = other.head;
	while (current != nullptr) {
		push_back(current->data);
		current = current->next;
	}
}

template <typename T>
List<T>::List(List&& other) : head(other.head), tail(other.tail), size_(other.size_) {
	other.head = nullptr;
	other.tail = nullptr;
	other.size_ = 0;
}

template <typename T>
List<T>::List(ListNode<T>* begin, ListNode<T>* end) : head(nullptr), tail(nullptr), size_(0) {
	ListNode<T>* current = begin;
	while (current != end) {
		push_back(current->data);
		current = current->next;
	}
}

template <typename T>
List<T>::~List() {
	clear();
}

template <typename T>
List<T>& List<T>::operator=(const List& other) {
	if (this == &other) {
		return *this; // 处理自我赋值
	}

	clear();

	ListNode<T>* current = other.head;
	while (current != nullptr) {
		push_back(current->data);
		current = current->next;
	}

	return *this;
}

template <typename T>
List<T>& List<T>::operator=(List&& other) {
	if (this == &other) {
		return *this; // 处理自我赋值
	}

	clear();

	head = other.head;
	tail = other.tail;
	size_ = other.size_;

	other.head = nullptr;
	other.tail = nullptr;
	other.size_ = 0;

	return *this;
}

template <typename T>
T& List<T>::front() {
	return head->data;
}

template <typename T>
const T& List<T>::front() const {
	return head->data;
}

template <typename T>
T& List<T>::back() {
	return tail->data;
}

template <typename T>
const T& List<T>::back() const {
	return tail->data;
}

template <typename T>
ListNode<T>* List<T>::begin() {
	return head;
}

template <typename T>
const ListNode<T>* List<T>::begin() const {
	return head;
}

template <typename T>
ListNode<T>* List<T>::end() {
	return nullptr;
}

template <typename T>
void List<T>::push_back(const T& val) {
	ListNode<T>* newNode = new ListNode<T>(val);
	if (head == nullptr) {
		head = tail = newNode;
	} else {
		newNode->prev = tail;
		tail->next = newNode;
		tail = newNode;
	}
	size_++;
}

template <typename T>
void List<T>::push_front(const T& val) {
	ListNode<T>* newNode = new ListNode<T>(val);
	if (head == nullptr) {
		head = tail = newNode;
	} else {
		newNode->next = head;
		head->prev = newNode;
		head = newNode;
	}
	size_++;
}

template <typename T>
void List<T>::insert(ListNode<T>* pos, const T& val) {
	if (pos == nullptr) {
		push_back(val);
		return;
	}

	if (pos == head) {
		push_front(val);
		return;
	}

	ListNode<T>* newNode = new ListNode<T>(val);
	newNode->prev = pos->prev;
	newNode->next = pos;
	pos->prev->next = newNode;
	pos->prev = newNode;

	size_++;
}

template <typename T>
void List<T>::insert(ListNode<T>* pos, size_t n, const T& val) {
	for (size_t i = 0; i < n; ++i) {
		insert(pos, val);
	}
}

template <typename T>
void List<T>::insert(ListNode<T>* pos, ListNode<T>* begin, ListNode<T>* end) {
	while (begin != end) {
		insert(pos, begin->data);
		begin = begin->next;
	}
}

template <typename T>
void List<T>::pop_back() {
	if (tail != nullptr) {
		ListNode<T>* temp = tail;
		tail = tail->prev;
		if (tail != nullptr) {
			tail->next = nullptr;
		} else {
			head = nullptr;
		}
		delete temp;
		size_--;
	}
}

template <typename T>
void List<T>::pop_front() {
	if (head != nullptr) {
		ListNode<T>* temp = head;
		head = head->next;
		if (head != nullptr) {
			head->prev = nullptr;
		} else {
			tail = nullptr;
		}
		delete temp;
		size_--;
	}
}

template <typename T>
void List<T>::erase(ListNode<T>* begin, ListNode<T>* end) {
	while (begin != end) {
		ListNode<T>* temp = begin;
		begin = begin->next;
		if (temp == head) {
			pop_front();
		} else if (temp == tail) {
			pop_back();
		} else {
			temp->prev->next = temp->next;
			temp->next->prev = temp->prev;
			delete temp;
			size_--;
		}
	}
}

template <typename T>
void List<T>::erase(const T& val) {
	ListNode<T>* current = head;
	while (current != nullptr) {
		ListNode<T>* temp = current;
		current = current->next;
		if (temp->data == val) {
			if (temp == head) {
				pop_front();
			} else if (temp == tail) {
				pop_back();
			} else {
				temp->prev->next = temp->next;
				temp->next->prev = temp->prev;
				delete temp;
				size_--;
			}
		}
	}
}

template <typename T>
void List<T>::clear() {
	ListNode<T>* current = head;
	while (current != nullptr) {
		ListNode<T>* temp = current;
		current = current->next;
		delete temp;
	}
	head = tail = nullptr;
	size_ = 0;
}

template <typename T>
size_t List<T>::size() const {
	return size_;
}

template <typename T>
bool List<T>::empty() const {
	return size_ == 0;
}
