/*	Name:		Peter Stegeby (Pets2001)
	Created:	April 2021
	Modified:	April 2021
*/

#include "linkedList.h"

linked_list::linked_list() {
	this->head = nullptr;
	this->tail = nullptr;
}

linked_list::linked_list(const linked_list& src) {
	this->head = nullptr;
	this->tail = nullptr;
	*this = src; // Copies the list with help of overloaded "="-operator.
}

// Destructor of class, removes each list from the heap.
linked_list::~linked_list() {
	while (!this->is_empty()) {
		this->pop_front();
	}
}

linked_list::node::node(double value) {
	this->value = value;
	this->next = nullptr;
	this->prev = nullptr;
}

linked_list& linked_list::operator= (const linked_list &rhs) {
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

linked_list& linked_list::operator+= (const linked_list& rhs) {
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
std::size_t linked_list::size() const noexcept {
	return this->m_size;
}

bool linked_list::is_empty() const {
	return this->m_size == 0 ? true : false;
}