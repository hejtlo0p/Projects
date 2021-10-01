#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <iostream>

template<typename T = double>
class linked_list {
public:
	linked_list<T>();
	linked_list<T>(const linked_list &src);

	~linked_list<T>();

	linked_list<T>& operator= (const linked_list<T>& rhs);

	// Appends elements from rhs
	linked_list<T>& operator+= (const linked_list<T>& rhs);

	//	Inserting elements
	void insert(T value, std::size_t pos);
	void push_back(T value);
	void push_front(T value);

	//	Accessing elements
	T front() const;
	T back() const;
	T at(std::size_t pos) const;

	//	Removing elements
	void remove(std::size_t pos);
	T pop_front();
	T pop_back();

	//	Status
	std::size_t size() const noexcept;
	bool is_empty() const;

	//	Output
	void print() const;
	void print_reverse() const;
	void exceptionHandle(std::exception& e) const;

private:
	struct node {
		node(T value);
		T value;
		node* prev;
		node* next;
	};
	node* head;
	node* tail;
	std::size_t m_size = 0;
};


#endif








