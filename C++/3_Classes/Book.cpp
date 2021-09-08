#include "Book.h"
#include <algorithm>
#include <ctype.h>

void Book::fill(std::ifstream& input) {
	int pageNr = 0;
	while (!input.eof()) {
		if (input.eof()) { break; }
		fillPages(pageNr, input);
	}
}

void Book::fillPages(int& pageNr, std::ifstream& input) {
	Book::page p;
	p.number = pageNr + 1;
	b_vector.push_back(p);
	Book::row r;
	while (true) {
		input >> r;
		if (r.text.empty()) { input >> r; }
		if (r.text == ("[Page " + std::to_string(pageNr + 2) + "]")) { break; } // Breaks when new page begins.
		addPage(pageNr, r);
		if (input.eof()) { break; } // When the last page is read this breaks.
	}
	pageNr++;
}

/*	Function is_alpha
*	Function is used in remove_if statement as predicate to remove all
*	unwanted characters
*	Function is used in: getCharFromCode()
*/
bool is_alpha(const char c) {
	if (int(c) == -61 || int(c) == -87) { return true; }
	if (isalpha(c)) { return false; }
	return true;
}

int convertAccent(const int c) {
	if (c == 'é') { return 'e'; }
	else if (c == 'É') { return 'E'; }
	return c;
}

char Book::getCharFromCode(int pageNr, int rowNr, int charNr) const {
	try {
		if (std::size_t(pageNr) <= 0 || std::size_t(pageNr) > b_vector.size()) { throw std::out_of_range("[getCharFromCode]: pageNr is out of range!"); }
		else if (std::size_t(rowNr) <= 0 || std::size_t(rowNr) > b_vector[pageNr - 1].p_vector.size()) { throw std::out_of_range("[getCharFromCode]: rowNr is out of range!"); }
		
		std::string str = b_vector[pageNr - 1].p_vector[rowNr - 1].text;
		std::size_t pos;
		while (true) { // converting é to e and deleting the extra char.
			pos = str.find('Ã');
			if (pos == std::string::npos) { break; }
			str[pos] = 'e';
			str.erase(str.begin() + pos+1);
		}
		while (true) { // converting ° to @ and deleting
			pos = str.find('Â');
			if (pos == std::string::npos) { break; }
			str[pos] = '@';
			str.erase(str.begin() + pos + 1);
		}
		
		str.erase(std::remove_if(str.begin(), str.end(), is_alpha), str.end());
		if (std::size_t(charNr) <= 0 || std::size_t(charNr) > str.size()) { throw std::out_of_range("[getCharFromCode]: charNr is out of range!"); }
		
		return str[charNr - 1];
	}
	catch (std::out_of_range& oor) {
		//this->exceptionHandle(oor);
		//std::cerr << "Cannot produce an character!" << std::endl;
		return '*';
	}
}

/*	Function getStringFromCode
*	Using charNr to count columns
*	Returns the word that charNr-1 is on no matter where in the word charNr-1 points to.
*/
std::string Book::getStringFromCode(int pageNr, int rowNr, int charNr) const {
	try {
		if (std::size_t(pageNr) <= 0 || std::size_t(pageNr) >= b_vector.size()) {
			throw std::out_of_range("[getStringFromCode]: pageNr is out of range!");
		}
		else if (std::size_t(rowNr) <= 0 || std::size_t(rowNr) >= b_vector[pageNr - 1].p_vector.size()) {
			throw std::out_of_range("[getStringFromCode]: rowNr is out of range!");
		}
		std::string result;
		int beforeChar = charNr - 1;
		std::string str = b_vector[pageNr - 1].p_vector[rowNr - 1].text;
		char character = str[charNr - 1];
		while (character != ' ') {
			if (str[beforeChar] == ' ' || beforeChar == 0) { break; }
			character = str[beforeChar];
			beforeChar--;
		}
		if (beforeChar == 0) { result = str.substr(beforeChar, str.size() - (beforeChar)); }
		else { result = str.substr(beforeChar + 1, str.size() - (beforeChar + 1)); }
		std::size_t pos = result.find(" ");
		result = result.substr(0, pos);
		while (!isalpha(result[result.size() - 1])) { result.pop_back(); }

		return result;
	}
	catch (std::out_of_range& oor) {
		/*this->exceptionHandle(oor);
		std::cerr << "Cannot produce an string!" << std::endl;*/
		return "*";
	}
}

/*	Function getWordFromCode
*	Similar to getStringFromCode, the big different is that this function searches on words rather than characters.
*	Returns word in wordNr - 1 position
*/
std::string Book::getWordFromCode(int pageNr, int rowNr, int wordNr) const {
	std::vector<std::string> words;
	std::string result;
	words = convertCodeToVector(pageNr, rowNr);
	result = words[wordNr - 1];

	return result;
}

std::vector<std::string> Book::convertCodeToVector(int pageNr, int rowNr) const {
	std::vector<std::string> result;
	try {
		if (std::size_t(pageNr) <= 0 || std::size_t(pageNr) >= b_vector.size()) { throw std::out_of_range("[ConvertCodeToVector]: pageNr is out of range!"); }
		else if (std::size_t(rowNr) <= 0 || std::size_t(rowNr) >= b_vector[pageNr - 1].p_vector.size()) { throw std::out_of_range("[ConvertCodeToVector]: rowNr is out of range!"); }
		std::string temp;
		std::string str = b_vector[pageNr - 1].p_vector[rowNr - 2].text;

		std::size_t pos;

		do {
			pos = str.find(" ");
			temp = str.substr(0, pos);
			str.erase(str.begin(), str.begin() + (pos + 1));
			while (!isalpha(temp[temp.size() - 1])) { temp.pop_back(); } // If the last character is not a letter, remove.
			result.push_back(temp);
		} while (pos != std::string::npos);

		return result;
	}
	catch (std::out_of_range& oor) {
		this->exceptionHandle(oor);
		std::cerr << "Cannot produce an vector!" << std::endl;
		return result;
	}
}

std::string Book::crackCode(const std::vector<int>& pageNr, const std::vector<int>& rowNr, const std::vector<int>& charNr, const std::vector<int>& amount, Book::type t) const {
	std::string result = "";
	char ch;
	std::size_t i = 0;
	int count = 0;
	int x = 0;
	int page, row, character;
	while (i < pageNr.size()) {
		page = pageNr[i];
		row = rowNr[i];
		character = charNr[i];
		if (t == type::CHAR) {
			if (count == amount[x]) { ch = ' '; count = -1; x++; }
			else { ch = getCharFromCode(page, row, character); }
			result.push_back(ch);
			count++;
		}
		else if (t == type::WORD) { result += getWordFromCode(page, row, character) + " "; }
		if (count != 0) { i++; }
	}
	return result;
}


std::istream& operator>>(std::istream& in, Book::row& r) {
	do {
		std::getline(in, r.text);
	} while (r.text.empty());
	return in;
}

std::ostream& operator<<(std::ostream& out, const Book::row& r) {
	out << r.text << std::endl;
	return out;
}

std::ostream& operator<<(std::ostream& out, const Book::page& p) {
	std::cout << "[Page " << p.number << "]" << std::endl;
	for (auto p : p.p_vector) {
		std::cout << p;
	}
	std::cout << std::endl;
	return out;
}
