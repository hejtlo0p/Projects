#ifndef BOOK_H
#define BOOK_H

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
//#include <iconv.h>

class Book {
public:
	Book(std::string name) { this->name = name; }
	enum class type { CHAR, WORD };

	struct row {
		row() { text = "Empty"; };
		std::string text;

	};
	struct page {
		std::vector<row> p_vector;
		int number{};
	};
	std::string getName() const { return this->name; }

	std::vector<row> getPage(int pageNr) const { return b_vector[pageNr].p_vector; }
	std::vector<page> getBook() const { return b_vector; }
	void addPage(int pageNr, row r) { b_vector[pageNr].p_vector.push_back(r); }
	void fill(std::ifstream&);
	void fillPages(int&, std::ifstream&);
	std::size_t size() const { return b_vector.size(); }
	bool is_empty() const { return b_vector.empty() ? true : false; }

	char getCharFromCode(int pageNr, int rowNr, int charNr) const;
	std::vector<std::string> convertCodeToVector(int, int) const;
	std::string getStringFromCode(int, int, int) const;
	std::string getWordFromCode(int, int, int) const;
	std::string crackCode(const std::vector<int>&, const std::vector<int>&, const std::vector<int>&, const std::vector<int>&, Book::type t = type::CHAR) const;

	friend std::ostream& operator<<(std::ostream&, const page&);
	friend std::ostream& operator<<(std::ostream&, const row&);
	friend std::istream& operator>>(std::istream&, row&);
	void exceptionHandle(std::exception& e) const { std::cerr << std::endl << "[EXCEPTION] " << e.what() << std::endl; }
private:
	std::vector<page> b_vector;
	std::string name;
};

#endif // !PAGE_H
