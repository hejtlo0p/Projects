#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <iostream>

//template<typename T>
class linked_list {
public:
	linked_list();
	linked_list(const linked_list &src);

	~linked_list();

	linked_list& operator= (const linked_list& rhs);

	// Appends elements from rhs
	linked_list& operator+= (const linked_list& rhs);

	//	Inserting elements
	void insert(double value, std::size_t pos);
	void push_back(double value);
	void push_front(double value);

	//	Accessing elements
	double front() const;
	double back() const;
	double at(std::size_t pos) const;

	//	Removing elements
	void remove(std::size_t pos);
	double pop_front();
	double pop_back();

	//	Status
	std::size_t size() const noexcept;
	bool is_empty() const;

	//	Output
	void print() const;
	void print_reverse() const;
	void exceptionHandle(std::exception& e) const;

private:
	struct node {
		node(double value);
		double value;
		node* prev;
		node* next;
	};
	node* head;
	node* tail;
	std::size_t m_size = 0;
};

#endif








