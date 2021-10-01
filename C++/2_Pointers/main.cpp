/*	Name:		Peter Stegeby (Pets2001)
	Created:	April 2021
	Modified:	August 2021

	Update:		August 2021: Added template so that the linked_list could be generic and hold any datatype.
				Also imported all .cpp files so that I would not get linker error.
*/

#include <iostream>
#include <time.h>
#include <stdlib.h>
#include "linkedList.h"
#include "linkedList.cpp"
#include "output.cpp"
#include "modify.cpp"


linked_list<> createList(double, std::size_t, int); // Test 1
int RemoveLargestElementInMiddle(linked_list<>&, linked_list<>&); // Test 2
void cutListInHalf(linked_list<>&); // Test 4
void print_list(linked_list<>); // Test 5
linked_list<> merge(linked_list<>&, linked_list<>&); // Test 6
bool is_sorted(linked_list<> const&); // Test 7

void enterToContinue();
void clearConsole();
void runTests();


int main() {
	time_t srand(time(NULL));
	//runTests();

	linked_list<std::string> list;
	list.push_back("Hello");
	list.push_back("World");
	list.push_back("!");

	linked_list<linked_list<double> > llist;

	list.print();
	llist.push_back(createList(1.5, 2, 10));
	llist.push_back(createList(2.4, 4, 5));

	llist.at(1).print();
	
	return 0;
}

// ********************************************* Global functions for main **************************************************

/*	Function createList()
*	Creates a list with starting value and of sizeOflist.
*	Values increases randomly.
*/
linked_list<> createList(double value, std::size_t increment, int sizeOfList) {
	linked_list<> list;
	int i = 0;
	for (i; i < sizeOfList; i++) {
		increment = rand() % 5;
		list.push_back(value);
		value += increment;
	}
	return list;
}

/*	Function RemoveLargestElementInMiddle()
*	Checks which list has the largest element in middle
*	e.g. list with 50 elements, checks 25th element.
*	Removes that element.
*/
int RemoveLargestElementInMiddle(linked_list<>& one, linked_list<>& two) {
	int list;
	std::size_t half_one = (one.size() / 2) - 1, half_two = (two.size() / 2) - 1; // If the list has 50 element then this is the 25th element.
	if ((one.at(half_one)) > (two.at(half_two))) {
		std::cout << "One: (" << (one.at(half_one)) << ") > Two: (" << (two.at(half_two)) << ")" << std::endl;
		std::cout << "Sequence One: " << one.at(half_one - 1) << " " << one.at(half_one) << " "
			<< one.at(half_one + 1) << std::endl;
		one.remove(half_one);
		list = 1;
	}
	else {
		std::cout << "Two: (" << (two.at(half_two)) << ") > One: (" << (one.at(half_one)) << ")" << std::endl;
		std::cout << "Sequence Two: " << two.at(half_two - 1) << " " << two.at(half_two) << " "
			<< two.at(half_two + 1) << std::endl;
		two.remove(half_two);
		list = 2;
	}
	return list;
}

/*	Function cutListInHalf()
*	Cuts a list in half.
*/
void cutListInHalf(linked_list<>& list) {
	int i = 0;
	for (i; i < list.size(); i++) {
		list.pop_back();
		list.push_front(list.pop_back());
	}
}

/*	Function print_list()
*	Creates a copy of list l using the copy constructor and prints the list.
*/
void print_list(linked_list<> l) {
	l.print();
}

/*	Function merge()
*	Merges list1 and list2 into a sorted list3.
*/
linked_list<> merge(linked_list<>& list1, linked_list<>& list2) {
	linked_list<> list3;
	if (list1.is_empty()) {
		list3 = list2;
	}
	else if (list2.is_empty()) {
		list3 = list1;
	}
	else {
		while (!list1.is_empty() && !list2.is_empty()) {
			if (list1.front() < list2.front()) {
				list3.push_back(list1.pop_front());
			}
			else {
				list3.push_back(list2.pop_front());
			}

			if (list2.is_empty()) {
				list3 += list1;
				while (!list1.is_empty()) {
					list1.pop_back();
				}
			}
			else if (list1.is_empty()) {
				list3 += list2;
				while (!list2.is_empty()) {
					list2.pop_back();
				}
			}
		}
	}
	return list3;
}

/*	Function is_sorted()
*	Checks if a list is sorted.
*	is used to check if the function merge() produces a sorted list.
*/
bool is_sorted(linked_list<> const& list) {
	double first;
	double second;
	std::size_t i = 1;
	try {
		if (i >= list.size()) {
			throw std::out_of_range("Index is out of range!");
		}
		first = list.front();
		second = list.at(i);
		while (i < list.size() - 1) {
			i++;
			if (first <= second) {
				first = second;
				second = list.at(i);
			}
			else {
				return false;
			}
		}
		return true;
	}
	catch (std::out_of_range& e) {
		list.exceptionHandle(e);
	}
	return NULL;
}

// ********************************************* Global functions for main **************************************************

/*	Function enterToContinue()
*	Used to make program look nice in a step-by-step way.
*/
void enterToContinue() {
	std::cout << "Please press enter to continue...";
	std::cin.get();
	std::cout << "********************************" << std::endl;
}

void clearConsole() {
	std::cout << "\x1B[2J\x1B[H";
}

void runTests() {
	std::size_t increment1 = rand() % 5;
	std::size_t increment2 = rand() % 5;

	// ***** 1. *****
	std::cout << "[TEST 1] Create two linked_lists:" << std::endl;
	linked_list<> one(createList(0.0, increment1, 50));
	linked_list<> two;
	two = createList(0.0, increment2, 50);

	std::cout << "One: ";
	one.print();
	std::cout << "Two: ";
	two.print();
	std::cout << "One.size(): " << one.size() << " Two.size(): " << two.size() << std::endl;

	// ***** 2. *****
	enterToContinue();
	std::cout << std::endl << "[TEST 2] Remove 25th element from a list:" << std::endl;
	int list = RemoveLargestElementInMiddle(one, two);
	std::cout << "One.size(): " << one.size() << " Two.size(): " << two.size() << std::endl;

	// ***** 3. *****
	enterToContinue();
	std::cout << std::endl << "[TEST 3] Create a Third list, print it reversed:" << std::endl;
	linked_list<> three;
	if (list == 1) {
		three = one;
		std::cout << "Three = One" << std::endl;
	}
	else {
		three = two;
		std::cout << "Three = Two" << std::endl;
	}
	std::cout << "One.size(): " << one.size() << " Two.size(): " << two.size() << " Three.size(): " << three.size() << std::endl;
	std::cout << "Three: ";
	three.print_reverse();

	// ***** 4 & 5. *****
	enterToContinue();
	std::cout << std::endl << "[TEST 4 & 5] Cutting the list in half with 50 element and print it by calling the function print_list():" << std::endl;
	if (list == 1) {
		cutListInHalf(two);
		std::cout << "Two.size(): " << two.size() << std::endl;
		std::cout << "Two: ";
		print_list(two);
	}
	else {
		cutListInHalf(one);
		std::cout << "One.size(): " << one.size() << std::endl;
		std::cout << "One: ";
		print_list(one);
	}

	// ***** 6. *****
	enterToContinue();
	clearConsole();
	std::cout << std::endl << "[TEST 6] Merging to lists together:" << std::endl;
	linked_list<double> four;
	if (one.size() > two.size()) {
		std::cout << "One: ";
		one.print();
		std::cout << "Two: ";
		two.print();
	}
	else {
		std::cout << "Two: ";
		two.print();
		std::cout << "One: ";
		one.print();
	}
	std::size_t s_one = one.size(), s_two = two.size();
	four = merge(two, one);
	// Testing self assignment!
	four = four;
	std::cout << "Four.size(): " << four.size() << " Which should be == (" << s_one << " + " << s_two << ")" << std::endl;
	std::cout << "Four: ";
	four.print();

	// ***** 7. *****
	enterToContinue();
	std::cout << std::endl << "[TEST 7] Checking if merged list is sorted:" << std::endl;
	bool sorted = is_sorted(four);
	if (sorted) {
		std::cout << "Yes, the merged list is sorted." << std::endl;
	}
	else {
		std::cout << "No, the merged list is not sorted." << std::endl;
	}
	linked_list<> five(three);
	five.insert(5, 0);
	sorted = is_sorted(five);
	if (sorted) {
		std::cout << "Yes, the other list is sorted." << std::endl;
	}
	else {
		std::cout << "No, the other list is not sorted." << std::endl;
	}
	std::cout << "Other: ";
	five.print();

	std::cout << "Jimmys megaSuperDuper tricky test to make my computer crash.. (The first time only) ;)" << std::endl;
	linked_list<> six(createList(4.0, 3, 3));
	std::cout << "Six.size(): " << six.size() << std::endl;
	std::cout << "Six before +=: ";
	six.print();
	six += six;
	std::cout << "Six.size(): " << six.size() << std::endl;
	std::cout << "Six after +=: ";
	six.print();
}
