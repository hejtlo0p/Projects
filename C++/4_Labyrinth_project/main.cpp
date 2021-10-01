/*	Name:		Peter Stegeby (pets2001)
*	Created:	April 2021
*	Modified:	May 2021
*	Grade:		A
*/

#include <iostream>
#include <time.h>
#include <limits>
#include "Labyrinth.h"

Labyrinth createMaze();
void printMenu();
void menu();
void clearConsole();
void enterToContinue();

int main() {
	srand(static_cast<unsigned int>(time(NULL)));
	
	Labyrinth custom;
	std::cout << "Please enter your maze or press [Enter] to continue to main program." << std::endl;
	custom.createCustomGrid();
		
	if (custom.is_empty()) { // If nothing is entered into the custom maze, go to menu
		std::cout << "Welcome to a Maze-generation program!" << std::endl;
		menu();
	}
	else {
		Labyrinth::algorithm DFS = Labyrinth::algorithm::DFS;
		Labyrinth::Grid SOLUTION = Labyrinth::Grid::SOLUTION;
		Labyrinth::type CUSTOM = Labyrinth::type::CUSTOM;
		custom.generateMaze(DFS, SOLUTION, CUSTOM);
		custom.generateSolution(CUSTOM);
		custom.printGrid(Labyrinth::print::CUSTOM);
	}

	return 0;
}

Labyrinth createMaze() {
	try {
		std::cout << "How big of a maze would you like? " << std::endl;
		int y, x;
		std::cout << "Please enter y-value: > ";
		std::cin >> y;
		if (std::cin.good()) { std::cout << "Please enter x-value: > "; }
		std::cin >> x;
		if (!std::cin.good()) { throw std::invalid_argument("Please keep y AND x and integer."); }
		else {
			Labyrinth maze(y, x);
			return maze;
		}
	}
	// To handle wrong input: https://stackoverflow.com/questions/27003967/how-to-check-if-cin-is-int-in-c
	catch (std::invalid_argument& ia) {
		int y = 0, x = 0;
		while (!std::cin.good()) {
			std::cerr << "Exception: " << ia.what() << std::endl;
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cout << "Please enter correct y-value: > ";
			std::cin >> y;
			if (std::cin.good()) { std::cout << "Please enter correct x-value: > "; }
			std::cin >> x;
		}
		Labyrinth maze(y, x);
		return maze;
	}
}

void printMenu() {
	std::cout << "[MENU]" << std::endl;
	std::cout << "1.) Create a grid" << std::endl;
	std::cout << "2.) Generate a maze. -DFS" << std::endl;
	std::cout << "3.) Generate a maze. -BFS" << std::endl;
	std::cout << "4.) Generate a solution." << std::endl;
	std::cout << "5.) Print maze to console. -Color" << std::endl;
	std::cout << "6.) Print maze to console. -No color" << std::endl;
	std::cout << "0.) Exit program." << std::endl;
}

void menu() {
	bool exit = false;
	Labyrinth maze(11,11);
	Labyrinth::Grid grid = Labyrinth::Grid::SOLUTION;
	while (!exit) {
		std::cout << "Maze-y: <" << maze.getRow() << "> Maze-x: <" << maze.getCol() << ">" << std::endl << std::endl; 
		printMenu();
		char choice;
		std::cout << "What would you like to do? >";
		std::cin >> choice;

		switch (choice) {
		case '1':
			clearConsole();
			std::cout << "[1] Creating a maze: " << std::endl;
			maze = createMaze();
			grid = Labyrinth::Grid::SOLUTION;
			break;
		case '2':
			clearConsole();
			std::cout << "[2] Generating a maze: -DFS" << std::endl;
			maze.generateMaze(Labyrinth::algorithm::DFS, grid);
			grid = Labyrinth::Grid::MAZE;
			break;
		case '3':
			clearConsole();
			std::cout << "[3] Generating a maze: -BFS" << std::endl;
			maze.generateMaze(Labyrinth::algorithm::BFS, grid);
			grid = Labyrinth::Grid::MAZE;
			break;
		case '4':
			clearConsole();
			std::cout << "[4] Creating a solution:" << std::endl;
			maze.generateSolution();
			break;
		case '5':
			clearConsole();
			std::cout << "[5] Printing maze: - Color" << std::endl << std::endl;
			maze.printGrid(Labyrinth::print::MAZE);
			enterToContinue();
			break;
		case '6':
			std::cout << "[5] Printing maze: - No color" << std::endl << std::endl;
			maze.printGrid(Labyrinth::print::GRID);
			enterToContinue();
			break;
		case '0':
			clearConsole();
			std::cout << "[5] Exiting program:" << std::endl;
			exit = true;
			break;
		default:
			clearConsole();
			std::cout << "<" << choice << "> Is not an option!" << std::endl;
			break;
		}
	}
}

void clearConsole() {
	std::cout << "\x1B[2J\x1B[H";
}

void enterToContinue() {
	system("pause");
}