/*	Name:		Peter Stegeby (Pets2001)
	Created:	April 2021
	Modified:	April 2021
*/

#include "linkedList.h"

// Prints the list
template <typename T>
void  linked_list<T>::print() const {
	node* n = head;
	for (n; n != nullptr ; n = n->next) {
		if (n->next == nullptr) {
			std::cout << n->value << ";";
		}
		else {
			std::cout << n->value << ", ";
		}
	}
	std::cout << std::endl;
	std::cout << "------------------" << std::endl;
}

// Prints the list reversed
template <typename T>
void linked_list<T>::print_reverse() const {
	node* n = tail;
	for (n; n != nullptr; n = n->prev) {
		if (n->prev == nullptr) {
			std::cout << n->value << ";";
		}
		else {
			std::cout << n->value << ", ";
		}
	}
	std::cout << std::endl;
	std::cout << "------------------" << std::endl;
}

template <typename T>
T linked_list<T>::front() const {
	try {
		if (is_empty()) {
			throw std::invalid_argument("List is empty!");
		}
		return head->value;
	}
	catch (std::invalid_argument& ia) {
		this->exceptionHandle(ia);
	}
}

template <typename T>
T linked_list<T>::back() const {
	try {
		if (is_empty()) {
			throw std::invalid_argument("List is empty!");
		}
		return tail->value;
	}
	catch (std::invalid_argument& ia) {
		this->exceptionHandle(ia);
	}
}

// Returns the value of node at pos. Starting at 0 and ends at list.size()-1.
template <typename T>
T linked_list<T>::at(std::size_t pos) const {
	try {
		if (is_empty()) {
			throw std::invalid_argument("List is empty!");
		}
		else if (pos > m_size) {
			throw std::out_of_range("Index is out of range");
		}
		else {
			std::size_t index = 0;
			node* n = head;
			while (index < pos) {
				n = n->next;
				index++;
			}
			return n->value;
		}
	}
	catch (std::out_of_range& oor) {
		this->exceptionHandle(oor);
	}
	catch (std::invalid_argument& ia) {
		this->exceptionHandle(ia);
	}
}

template <typename T>
void linked_list<T>::exceptionHandle(std::exception& e) const {
	std::cerr << "Exception: " << e.what() << std::endl;
	exit(EXIT_FAILURE);
}