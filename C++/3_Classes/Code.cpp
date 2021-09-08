#include "Code.h"

void Code::createVectorForCode(std::string filename, std::string path) {
	std::ifstream input;
	input.open(path+filename+".txt");
	std::vector<std::string> numbers;
	std::string text;
	while (!input.eof()) {
		std::getline(input, text, ' ');
		numbers.push_back(text);
	}
	input.close();
	this->raw_vector = numbers;
}

/*	Function formatCode
*	Changes the format of the vector holding all the strings with the code.
*	Function is used in: main().
*/
void Code::formatCode() {
	std::size_t i = 0;
	while (i < raw_vector.size()) {
		std::string str = raw_vector[i];
		raw_vector[i] = splitString(str, 7); // 7 seems to be the common divisor in all strings.
		i++;
	}
}

/*	Function splitString
*	Is used to split string of code into same amount of characters
*	Function is used in: formatCode()
*	Returns the same string but in groups of the size of the divisor.
*/
std::string Code::splitString(std::string str, int divisor) {
	std::string result;
	std::string temp;
	std::size_t i = str.size() / divisor;
	bool needed = true;
	if (i == 1) { needed = false; }
	while (i > 0) {
		if (!needed) { return str; }
		temp = str.substr(0, divisor);
		str.erase(str.begin(), str.begin() + temp.size());
		if (i == 1) { result += temp; }
		else { result += temp + " "; }
		i--;
	}
	return result;
}

/*	Function addCodeToVector
*	Adds a vector of strings in vector 'Vector'
*	Function is used in: main()
*/
void Code::addCodeToVector() {
	std::vector<std::string> vec;
	std::string temp;
	std::string str;
	std::size_t pos;
	std::size_t i = 0;
	while (i < raw_vector.size()) {
		while (!raw_vector[i].empty()) {
			str = raw_vector[i];
			pos = str.find(" ");
			temp = str.substr(0, pos);
			if (pos == std::string::npos) { str.erase(); }
			else { str.erase(str.begin(), str.begin() + (pos + 1)); }
			raw_vector[i] = str;
			vec.push_back(temp);
		}
		i++;
		final_vector.push_back(vec);
		wordsPerRow_vector.push_back(vec.size());
		vec.erase(vec.begin(), vec.end());
	}
	raw_vector.erase(raw_vector.begin(), raw_vector.end());
}

void Code::formatString(int pageDigits, int rowDigits, int wordDigits) {
	std::vector<std::vector<int> > result;
	std::vector<std::vector<std::string>> vec = final_vector;
	std::vector<int> vector;
	result.push_back(vector);
	result.push_back(vector);
	result.push_back(vector);
	std::string temp;
	std::string str;
	int digits[] = { pageDigits, rowDigits, wordDigits };
	int num;
	int i = 0;
	int j;
	int x;
	while (i < vec.size()) {
		j = 0;
		while (j < vec[i].size()) {
			x = 0;
			while (x < 3) {
				str = vec[i][j];
				temp = str.substr(0, digits[x]);
				str.erase(str.begin(), str.begin() + temp.size());
				num = stoi(temp);
				vec[i][j] = str;
				result[x].push_back(num);
				x++;
			}
			j++;
		}
		i++;
	}
	code = result;
}
