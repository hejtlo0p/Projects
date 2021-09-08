#ifndef CODE_H
#define CODE_H

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

class Code {
public:
	Code(std::string name) { this->name = name; }

	std::string getName() const { return this->name; }
	std::vector<std::string> getRaw_vector() const { return this->raw_vector; }
	std::vector<std::vector<int> > getCode() const { return this->code; }
	std::vector<int> getWordsPerRow_vector() const { return this->wordsPerRow_vector; }
	std::vector<std::vector<std::string> > getFinal_vector() const { return this->final_vector; }

	void createVectorForCode(std::string, std::string);
	void formatCode();
	std::string splitString(std::string str, int divisor);
	void formatString(int, int, int);
	void addCodeToVector();
private:
	std::vector<std::string> raw_vector;
	std::vector<int> wordsPerRow_vector;
	std::vector<std::vector<std::string> > final_vector;
	std::vector<std::vector<int> > code;
	std::string name;
};

#endif // !CODE_H

