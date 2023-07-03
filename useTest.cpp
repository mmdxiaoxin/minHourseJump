#include <iostream>
#include "Vector.h"
#include "List.h"

using namespace std;

int test1() {
	Vector<int> vec;

	std::cout << "Capacity: " << vec.capacity() << std::endl;
	std::cout << "Size: " << vec.size() << std::endl;

	vec.push_back(1);
	vec.push_back(2);
	vec.push_back(3);

	std::cout << "Capacity: " << vec.capacity() << std::endl;
	std::cout << "Size: " << vec.size() << std::endl;

	for (int i = 0; i < vec.size(); i++) {
		std::cout << vec[i] << " ";
	}
	std::cout << std::endl;

	std::cout << "Front: " << vec.front() << std::endl;
	std::cout << "Back: " << vec.back() << std::endl;

	vec.pop_back();

	std::cout << "Size after pop_back: " << vec.size() << std::endl;

	vec.insert(vec.begin() + 1, 4);

	for (int i = 0; i < vec.size(); i++) {
		std::cout << vec[i] << " ";
	}
	std::cout << std::endl;

	vec.erase(vec.begin());

	for (int i = 0; i < vec.size(); i++) {
		std::cout << vec[i] << " ";
	}
	std::cout << std::endl;

	vec.reverse(vec.begin(), vec.end() - 1);

	for (int i = 0; i < vec.size(); i++) {
		std::cout << vec[i] << " ";
	}
	std::cout << std::endl;

	return 0;
}

int test2() {
	List<int> lt;
	lt.push_back(1);
	lt.push_back(2);
	lt.push_front(0);

	std::cout << "Front: " << lt.front() << std::endl; // 输出：Front: 0
	std::cout << "Back: " << lt.back() << std::endl;   // 输出：Back: 2

	std::cout << "List elements: ";
	for (ListNode<int>* it = lt.begin(); it != lt.end(); it = it->next) {
		std::cout << it->data << " ";
	}
	std::cout << std::endl;
	// 输出：List elements: 0 1 2

	lt.pop_back();
	lt.erase(lt.begin(), lt.begin()->next);

	std::cout << "List elements after deletion: ";
	for (ListNode<int>* it = lt.begin(); it != lt.end(); it = it->next) {
		std::cout << it->data << " ";
	}
	std::cout << std::endl;
	// 输出：List elements after deletion: 1

	return 0;
}