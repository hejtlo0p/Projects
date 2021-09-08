#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <filesystem>

//namespace fs = std::filesystem;

#include "Book.h"
#include "Code.h"

void fill_vector_with_Books(std::vector<Book>&, const std::vector<std::string>&);
void fill_vector_with_Codes(std::vector<Code>&, const std::vector<std::string>&);
void fill_book_titles(std::vector<std::string>&);

void printResult(const Book&, const Code&);
void printCode(const std::vector<std::string>&);
void printCodes(const std::vector<std::vector<std::string>>&);
void exceptionHandle(std::exception&);


int main() {
	std::system("chcp 1252 >> NUL");
	std::vector<std::string> book_titles; /*= { "The Importance of Being Earnest" };*/
	std::vector<std::string> code_titles = { "codes" };
	std::vector<Book> books;
	std::vector<Code> codes;
	fill_book_titles(book_titles);
	fill_vector_with_Books(books, book_titles);
	fill_vector_with_Codes(codes, code_titles);

	std::cout << "[CODE]: "; printCodes(codes[0].getFinal_vector());
	for (auto c : codes) {
		for (auto b : books) {
			printResult(b, c);
		}
	}
	return 0;
}

void fill_vector_with_Books(std::vector<Book>& books, const std::vector<std::string>& book_titles) {
	std::ifstream input;
	std::string bookPath = "Books/";
	for (auto filename : book_titles) {
		Book b(filename);
		input.open(bookPath + filename+".txt");
		b.fill(input);
		input.close();
		books.push_back(b);
	}
}

void fill_vector_with_Codes(std::vector<Code>& codes, const std::vector<std::string>& code_titles) {
	std::string codePath = "Codes/";
	for (auto filename : code_titles) {
		Code c(filename);
		c.createVectorForCode(c.getName(), codePath);
		c.formatCode();
		c.addCodeToVector(); // Contains the same as number but is now a vector within a vector.
		c.formatString(3, 2, 2);
		codes.push_back(c);
	}
}

void fill_book_titles(std::vector<std::string>& book_titles) {
	std::ifstream input;
	std::string title;
	std::string bookPath = "Books/";
	input.open(bookPath+"1_Titles.txt");
	while (!input.eof()) {
		std::getline(input, title);
		if (input.bad()) { break; }
		book_titles.push_back(title);
	}
	input.close();
}

void printResult(const Book& b, const const Code& c) {
	std::cout << "\n[KEY]      : " << b.getName() << std::endl;
	std::cout << "[PLAINTEXT]: " << b.crackCode(c.getCode()[0], c.getCode()[1], c.getCode()[2], c.getWordsPerRow_vector()) << std::endl;
}

void printCode(const std::vector<std::string>& code) {
	for (auto n : code) {
		std::cout << n << std::endl;
	}
}

void printCodes(const std::vector<std::vector<std::string>>& code) {
	for (auto i : code) {
		for (auto j : i) {
			std::cout << j << " ";
		}
		std::cout << std::endl;
	}
}

void exceptionHandle(std::exception& e) {
	std::cerr << std::endl << "[EXCEPTION] " << e.what() << std::endl;
}