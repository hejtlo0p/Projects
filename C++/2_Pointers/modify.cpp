/*	Name:		Peter Stegeby (Pets2001)
	Created:	April 2021
	Modified:	April 2021
*/

#include "linkedList.h"
#include <cstddef>

// ***** Adding Elements *****
/*	Adds an element of position pos. 
*	When pos == list.size() this function works like push_back()
*	When pos == 0 this function works like push_front()
*/
template <typename T>
void linked_list<T>::insert(T value, std::size_t pos) {
	node* n = new node(value);
	try {
		if (pos > m_size) {
			throw std::out_of_range("Index is out of range.");
		}
		else if (pos == 0) {
			this->push_front(value);
		}
		else if (pos == m_size) {
			this->push_back(value);
		}
		else {
			std::size_t index = 0;
			node* temp = head;
			for (; index < pos; index++) {
				temp = temp->next;
			}
			n->next = temp;
			n->prev = temp->prev;
			temp->prev->next = n;
			temp->prev = n;
			m_size++;
		}
	}
	catch (std::out_of_range& oor) {
		this->exceptionHandle(oor);
	}
}

// Adds an element in the last place of list.
template <typename T>
void linked_list<T>::push_back(T value) {
	node* n = new node(value);
	
	if (!is_empty()) {
		tail->next = n;
		n->prev = tail;
		tail = n;
	}
	else { // If list has no elements
		head = n;
		tail = n;
	}
	m_size++;
}

// Adds an element in the first place of list.
template <typename T>
void linked_list<T>::push_front(T value) {
	node* n = new node(value);
	
	if (!is_empty()) {
		head->prev = n;
		n->next = head;
		head = n;
	}
	else { // If list has no elements
		head = n;
		tail = n;
	}
	m_size++;
}

// ***** Deleting Elements *****
// Removes the element in list of position pos. first element is 0 and last element is list.size()-1
template <typename T>
void linked_list<T>::remove(std::size_t pos) {
	try {
		if (is_empty()) {
			throw std::invalid_argument("List is empty!");
		}
		else if (pos > m_size) {
			throw std::out_of_range("Index is out of range.");
		}

		else {
			node* n = head;
			if (pos == 0) {
				this->pop_front();
			}
			else if (pos == (m_size - 1)) {
				this->pop_back();
			}
			else {
				std::size_t index = 0;
				for (; index < pos; index++) {
					n = n->next;
				}
				n->prev->next = n->next;
				n->next->prev = n->prev;
				delete n;
				m_size--;
			}
		}
	}
	catch (std::out_of_range& oor) {
		this->exceptionHandle(oor);
	}
	catch (std::invalid_argument ia) {
		this->exceptionHandle(ia);
	}
}

// Removes the first element of list.
template <typename T>
T linked_list<T>::pop_front() {
	try {
		if (!is_empty()) {
			node* n = head;
			T value = n->value;
			if (m_size == 1) {
				delete n;
				head = nullptr;
				tail = nullptr;
			}
			else {
				head = head->next;
				head->prev = nullptr;
				delete n;
			}
			m_size--;

			return value;
		}
		else {
			throw std::invalid_argument("List is empty!");
		}
	}
	catch (std::invalid_argument& ia) {
		this->exceptionHandle(ia);
	}
}

// Removes the last element of list.
template <typename T>
T linked_list<T>::pop_back() {
	try {
		if (!is_empty()) {
			node* n = tail;
			double value = n->value;
			if (m_size == 1) { // If list has one element
				delete n;
				head = nullptr;
				tail = nullptr;
			}
			else {
				tail = tail->prev;
				tail->next = nullptr;
				delete n;
			}
			m_size--;

			return value;
		}
		else {
			throw std::invalid_argument("List is empty!");
		}
	}
	catch (std::invalid_argument& ia) {
		this->exceptionHandle(ia);
	}
}