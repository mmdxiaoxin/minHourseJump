#pragma once
template <typename T>
class ListNode {
public:
	T data;
	ListNode* prev;
	ListNode* next;

	ListNode(const T& val) : data(val), prev(nullptr), next(nullptr) {}
};

template <typename T>
class List {
private:
	ListNode<T>* head;
	ListNode<T>* tail;
	size_t size;

public:
	List();
	~List();
	T& front();
	const T& front() const;
	T& back();
	const T& back() const;
	ListNode<T>* begin();
	const ListNode<T>* begin() const;
	ListNode<T>* end();
	const ListNode<T>* end() const;
	void push_back(const T& val);
	void push_front(const T& val);
	void insert(ListNode<T>* pos, const T& val);
	void insert(ListNode<T>* pos, size_t n, const T& val);
	void insert(ListNode<T>* pos, ListNode<T>* begin, ListNode<T>* end);
	void pop_back();
	void pop_front();
	void erase(ListNode<T>* begin, ListNode<T>* end);
	void erase(const T& val);
	void clear();
	size_t size() const;
	bool empty() const;
};

template <typename T>
List<T>::List() : head(nullptr), tail(nullptr), size(0) {}

template <typename T>
List<T>::~List() {
	clear();
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
const ListNode<T>* List<T>::end() const {
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
	size++;
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
	size++;
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

	size++;
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
		size--;
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
		size--;
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
			size--;
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
				size--;
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
	size = 0;
}

template <typename T>
size_t List<T>::size() const {
	return size;
}

template <typename T>
bool List<T>::empty() const {
	return size == 0;
}
