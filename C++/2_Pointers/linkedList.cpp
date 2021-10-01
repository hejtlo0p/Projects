/*	Name:		Peter Stegeby (Pets2001)
	Created:	April 2021
	Modified:	April 2021
*/

#include "linkedList.h"

template <typename T>
linked_list<T>::linked_list() {
	this->head = nullptr;
	this->tail = nullptr;
}

template <typename T>
linked_list<T>::linked_list(const linked_list& src) {
	this->head = nullptr;
	this->tail = nullptr;
	*this = src; // Copies the list with help of overloaded "="-operator.
}

// Destructor of class, removes each list from the heap.
template <typename T>
linked_list<T>::~linked_list() {
	while (!this->is_empty()) {
		this->pop_front();
	}
}

template <typename T>
linked_list<T>::node::node(T value) {
	this->value = value;
	this->next = nullptr;
	this->prev = nullptr;
}

template <typename T>
linked_list<T>& linked_list<T>::operator= (const linked_list<T> &rhs) {
	if (this != &rhs) {
		// Clean old data
		while (!this->is_empty()) {
			this->pop_back();
		}
		
		node* n = rhs.head;
		if (!rhs.is_empty()) {
			this->push_back(n->value); // Pushes in the first value (incase rhs only has one value)
			while (n->next != nullptr) {
				n = n->next;
				this->push_back(n->value);
			}
		}
	}
	return *this;
}

template <typename T>
linked_list<T>& linked_list<T>::operator+= (const linked_list<T>& rhs) {
	if (this->is_empty()) {
		*this = rhs;
	}
	else if (!rhs.is_empty()) {
		node* n = rhs.head;
		std::size_t index = 0;
		std::size_t size = rhs.size();
		for (index; index < size; index++) {
			this->push_back(rhs.at(index));
		}
	}
	return *this;
}

// Status
template <typename T>
std::size_t linked_list<T>::size() const noexcept {
	return this->m_size;
}

template <typename T>
bool linked_list<T>::is_empty() const {
	return this->m_size == 0 ? true : false;
}

