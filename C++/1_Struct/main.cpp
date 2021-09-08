/* Skapare:    Peter Stegeby (pets2001)
*  Datum:      Mars 2021
*  Mod:        Mars 2021
*  Hours:      About 17 Hours was put into this project.
*  Comment:    This program can print <how many times a name occurs> and
*              <how many people live in the same city> from a given textdocument.
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <stdio.h> // isupper, tolower
#include <string>
#include <algorithm>

struct adress {
    std::string street;
    unsigned int zip = 0;
    std::string city;
};

struct person {
    std::string name;
    std::string id;
    adress location;
};

std::vector<person> read_file(std::string);
size_t find_in_names(std::vector<person>, std::string);
std::vector<person> find_person_from_city(std::vector<person>, std::string);
std::ifstream& operator >> (std::ifstream&, person&);

std::ostream& operator << (std::ostream&, person&);
void showMenu();
void menu(std::string);
bool handleMenu(char, std::string, std::vector<person>, std::vector<person>);
void clearConsole();
int toUpper(int c);

int main() {
    // Setting 'charset to 1252' in order to print å ä ö in the terminal.
    // And sending it to the empty void with '>> NUL'
    std::system("chcp 1252 >> NUL");
    clearConsole();
    std::string filename;
    std::cout << "Firstly.. What text dokument do you want to use? >";
    std::cin >> filename;
    menu(filename);

    return 0;
}
// *************************** FUNCTIONS FROM API ***************************
 /* Function read_file()
   Filename should be textfile to be used in program.
   Returns a vector<person> with given attributes.
 */
std::vector<person> read_file(std::string filename) {
    std::vector<person> list;
    std::ifstream input;
    person p;

    input.open(filename);

    // >> Operation in use is overloaded to handle struct 'person' and 'adress'
    while (input >> p)
    {
        if (input.eof()) {
            break;
        }
        list.push_back(p);
    }
    input.close();
    return list;
}

/* Function find_in_names()
*  Takes in <name of vector<person>> and <subset of name of person as std::string> as parameters.
*  Returns an size_t of how many time(s) the name occurs in vector<person>.
*/
size_t find_in_names(std::vector<person> haystack, std::string name_part) {
    std::size_t findings = 0;
    std::size_t found;
    std::string temp;

    std::transform(name_part.begin(), name_part.end(), name_part.begin(), tolower);
    
    for (std::size_t i = 0; i < haystack.size(); i++)
    {
        temp = haystack[i].name;
        std::transform(temp.begin(), temp.end(), temp.begin(), tolower);

        found = temp.find(name_part);
        if (found != std::string::npos)
            findings++;
    }

    return findings;
}

/* Function find_person_from_city()
*  Takes in <name of vector<person>> and <name of city as std::string> as parameters.
*  Returns a vector<person> with all the people living in the same city.
*/
std::vector<person> find_person_from_city(std::vector<person> haystack, std::string city) {
    std::vector<person> peopleInCity;

    std::transform(city.begin(), city.end(), city.begin(), toUpper);

    for (std::size_t i = 0; i < haystack.size(); i++) {
        
        /*std::string temp = haystack[i].location.city;
        std::transform(temp.begin(), temp.end(), temp.begin(), toLower);
        std::cout << "city: " << temp << std::endl;*/
        
        if (city == haystack[i].location.city)
            peopleInCity.push_back(haystack[i]);
    }

    return peopleInCity;
}

/* Overloading >> so istream can write to struct 'person' & 'adress'.
*  Using the lines 1 and 2 in given textdocument for 'person'
*  Adds value to person p.name and p.id.
*  Using line 3 in given textdocument for 'adress'
*/
std::ifstream& operator >> (std::ifstream &in, person &p) {
    int first, second;

    std::getline(in, p.name);
    std::getline(in, p.id);
    std::getline(in, p.location.street, ',');
    
    in >> first >> second;
    p.location.zip = (first * 100) + second;
    std::getline(in.ignore(), p.location.city);
    std::size_t pos = 0;
    pos = p.location.city.find("  ");
    
    // If pos finds <double spaces>, create a substring and erase it from p.location.city
    if (pos != std::string::npos) {
        std::string str1 = p.location.city.substr(pos);
        p.location.city.erase(pos, str1.length());
    }
    
    // Removing the 'space' before the name of the city. 
    if (isspace(p.location.city[0]))
    {
        p.location.city.erase(p.location.city.begin() + 0);
    }

    return in;
}

// *************************** FUNCTIONS FROM API ***************************,

// Overloading << so I can read from struct 'person'.
std::ostream& operator << (std::ostream &output, person &p) {
    output << p.id << ", " << p.name << ", " << p.location.city << std::endl;
    return output;
}

void showMenu() {
    std::cout << "Welcome to this application!" << std::endl;
    std::cout << "[MENU]" << std::endl;
    std::cout << "[1]. Search for names." << std::endl;
    std::cout << "[2]. Search for people in city." << std::endl;
    std::cout << "[3]. Exit." << std::endl;
    std::cout << "What do you want to do? >";
}

/* Function menu()
*  Takes in <name of file as string> as parameter
*  Creates vectors used in this program.
*/
void menu(std::string filename) {
    std::vector<person> haystack;
    std::vector<person> peopleInCity;
    char choice = '0';
    bool exit = false;
    haystack = read_file(filename);

    while (!exit) {
        clearConsole();
        std::cout << "File in use: <" << filename << ">" << std::endl << std::endl;
        showMenu();
        std::cin >> choice;
        exit = handleMenu(choice, filename, haystack, peopleInCity);
    }
}

/* Function handleMenu()
*  Handeling the different options in the menu()
*/
bool handleMenu(char choice, std::string filename, std::vector<person> haystack, std::vector<person> peopleInCity) {
    bool quit = false;
    while (!quit)
    {
        char decision;
        if (choice == '1')
        {
            std::string name_part;
            size_t found;
            while (!quit)
            {
                clearConsole();
                std::cout << "Welcome! You can now search for how many times a firstname will occur in '" << filename << "'." << std::endl;
                std::cout << "What name do you want to search for? >";
                std::cin.ignore();
                std::getline(std::cin, name_part);
                found = find_in_names(haystack, name_part);
                std::cout << "The name: " << name_part << " was found: " << found << " time(s)." << std::endl;
                std::cout << "\nDo you want to search for another name? (y/n) >";
                std::cin >> decision;
                if (decision == 'y')
                    ;
                else if (decision == 'n')
                {
                    quit = true;
                }
                else
                    std::cout << "Unknown command: try y or n" << std::endl;
            }
        }
        else if (choice == '2')
        {
            std::string city;
            while (!quit)
            {
                clearConsole();
                std::cout << "Welcome! You can now search for how many people live in the same city from document: '" << filename << "'." << std::endl;
                std::cout << "What city do you want to search for? >";
                std::cin.ignore();
                std::getline(std::cin, city);
                peopleInCity = find_person_from_city(haystack, city);
                std::cout << std::endl << "People living in the city: " << city << " are:" << std::endl;
                std::cout << "********" << std::endl;
                for (std::vector<person>::iterator it = peopleInCity.begin(); it < peopleInCity.end(); it++)
                    std::cout << *it;
                std::cout << "********" << std::endl;

                std::cout << "\nDo you want to search for another name? (y/n) >";
                std::cin >> decision;
                if (decision == 'y')
                    ;
                else if (decision == 'n')
                {
                    quit = true;
                }
                else
                    std::cout << "Unknown command: try y or n" << std::endl;
            }
        }
        else if (choice == '3')
        {
            clearConsole();
            std::cout << "Application exits." << std::endl;
            quit = true;
            return true;
        }
        else
        {
            std::cout << "Command is unknown! please try something between 1-3" << std::endl;
            quit = true;
        }
    }
    return false;
}

void clearConsole() {
    std::cout << "\x1B[2J\x1B[H";
}
// Can convert åäö to ÅÄÖ.
// Could be used in transform instead of toupper
int toUpper(int c) {
    
    if (c == 'ö') {
        return 'Ö';
    }
    else if (c == 'ä') {
        return 'Ä';
    }
    else if (c == 'å') {
        return 'Å';
    }
    else {
        return toupper(c);
    }
}