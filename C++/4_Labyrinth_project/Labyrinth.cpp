/*	Name:		Peter Stegeby (pets2001)
*	Created:	April 2021
*	Modified:	May 2021
*	Grade:		A
*/

#include <stack>
#include <deque>
#include <string>
#include <limits>
#include "Labyrinth.h"

#define ESC "\033["
#define RESET "\033[m"
#define RED_BKG "41"
#define RED_TEXT "31"
#define WHITE_BKG "47"
#define WHITE_TEXT "7"
#define BLACK_BKG "32"
#define BLACK_TEXT "30"
#define GREEN_BKG "42"
#define GREEN_TEXT "32"


Labyrinth::Labyrinth(int row, int col) {
	try {
		if (row % 2 == 0 || col % 2 == 0) {
			throw std::logic_error("Having x-value or y-value being divisable with 2 may not be a good idea..");
		}
		setSize(row, col);
		setNodes(row, col);
		grid = createGrid();
	}
	catch (std::logic_error& le) {
		while (row % 2 == 0 || col % 2 == 0) {
			this->exceptionHandling(le);
			std::cout << "Enter new y-value: >";
			std::cin >> row;
			if (std::cin.good()) { std::cout << "Enter new x-value: >"; }
			std::cin >> col;
			while (!std::cin.good()) {
				std::cerr << "[NOTE] Please keep y AND x and integer." << std::endl;
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				std::cout << "Enter new y-value: >";
				std::cin >> row;
				if (std::cin.good()) { std::cout << "Enter new x-value: >"; }
				std::cin >> col;
			}
		}
		setSize(row, col);
		setNodes(row, col);
		grid = createGrid();
	}
}

/*	Function revertDir()
*	Returns the opposite direction of e
*	Function is used in: move()
*/
Labyrinth::dir Labyrinth::revertDir(dir e) {
	try {
		dir revert;
		if (e == dir::UP) { revert = dir::DOWN; }
		else if (e == dir::DOWN) { revert = dir::UP; }
		else if (e == dir::LEFT) { revert = dir::RIGHT; }
		else if (e == dir::RIGHT) { revert = dir::LEFT; }
		else { throw std::invalid_argument("Cannot revert given parameter!"); }

		return revert;
	}
	catch (std::invalid_argument& ia) {
		this->exceptionHandling(ia);
		exit(EXIT_FAILURE);
	}
}

/*	Function canVisitNeighbor()
*	Checking if node n can move in any direction
*	Function is used in: generateMaze()
*/
bool Labyrinth::canVisitNeighbor(node n, type move) {
	return canMove(n, dir::UP, move) || canMove(n, dir::DOWN, move) || canMove(n, dir::LEFT, move) || canMove(n, dir::RIGHT, move) ? true : false;
}

/*	Function canMove()
*	Is the move logic for generation maze and the solution
*	Function is used in: move()
*/
bool Labyrinth::canMove(Labyrinth::node n, dir direction, type move) {
	try {
		char goodMove;
		char pathWay;
		std::size_t y = n.y;
		std::size_t yTwo, yOne;
		std::size_t x = n.x;
		std::size_t xTwo, xOne;
		if (move == type::NORMAL) { goodMove = '*'; pathWay = ' '; }
		else if (move == type::CUSTOM) { goodMove = '/'; pathWay = '/'; }
		else { throw std::invalid_argument("That 'move' argument in invalid!"); }

		if (direction == dir::UP) {
			yTwo = y - 2;
			yOne = y - 1;
			if ((grid[y][x].value == 'S' || grid[y][x].value == 'E') && y != m_row - 1) { return false; } // Can go UP if 'S' or 'E' is on BOT-side
			if (grid[yOne][x].value == 'E' && !grid[yOne][x].visited) { return true; }
			if (grid[yOne][x].value == 'S' && !grid[yOne][x].visited) { return true; } // For solution
			if (grid[yOne][x].value == goodMove && grid[yOne][x].visited) { return false; }
			if (grid[yOne][x].value == '/' && !grid[yOne][x].visited) { return true; } // For solution
			if (grid[yOne][x].value != goodMove && grid[yOne][x].value != pathWay) { return false; }
			if (y >= 2) {
				if ((grid[yTwo][x].value == goodMove && !grid[yTwo][x].visited) ||
					(grid[yOne][x].value == goodMove && !grid[yOne][x].visited)) {
					return true;
				}
			}
		}
		else if (direction == dir::DOWN) {
			yTwo = y + 2;
			yOne = y + 1;
			if ((grid[y][x].value == 'S' || grid[y][x].value == 'E') && y != 0) { return false; } // Can go DOWN if 'S' or 'E' is on TOP-side
			if (grid[yOne][x].value == 'E' && !grid[yOne][x].visited) { return true; }
			if (grid[yOne][x].value == 'S' && !grid[yOne][x].visited) { return true; } // For solution
			if (grid[yOne][x].value == goodMove && grid[yOne][x].visited) { return false; }
			if (grid[yOne][x].value == '/' && !grid[yOne][x].visited) { return true; } // For solution
			if (grid[yOne][x].value != goodMove && grid[yOne][x].value != pathWay) { return false; }
			if (y <= (m_row - 3)) {
				if ((grid[yTwo][x].value == goodMove && !grid[yTwo][x].visited) ||
					(grid[yOne][x].value == goodMove && !grid[yOne][x].visited)) {
						return true;
				}
			}
		}
		else if (direction == dir::LEFT) {
			xTwo = x - 2;
			xOne = x - 1;
			if ((grid[y][x].value == 'S' || grid[y][x].value == 'E') && x != m_col - 1) { return false; } // Can go LEFT if 'S' or 'E' is on RIGHT-side
			if (grid[y][xOne].value == 'E' && !grid[y][xOne].visited) { return true; }
			if (grid[y][xOne].value == 'S' && !grid[y][xOne].visited) { return true; } //  For solution
			if (grid[y][xOne].value == goodMove && grid[y][xOne].visited) { return false; }
			if (grid[y][xOne].value == '/' && !grid[y][xOne].visited) { return true; } // For solution
			if (grid[y][xOne].value != goodMove && (grid[y][xOne].value != pathWay)) { return false; }
			if (x >= 2) {
				if ((grid[y][xTwo].value == goodMove && !grid[y][xTwo].visited) ||
					(grid[y][xOne].value == goodMove && !grid[y][xOne].visited)) {
					return true;
				}
			}
		}
		else if (direction == dir::RIGHT) {
			xTwo = x + 2;
			xOne = x + 1;
			if ((grid[y][x].value == 'S' || grid[y][x].value == 'E') && x != 0) { return false; } // Can go RIGHT if 'S' or 'E' is on LEFT-side
			if (grid[y][xOne].value == 'E' && !grid[y][xOne].visited) { return true; }
			if (grid[y][xOne].value == 'S' && !grid[y][xOne].visited) { return true; } //  For solution
			if (grid[y][xOne].value == goodMove && grid[y][xOne].visited) { return false; }
			if (grid[y][xOne].value == '/' && !grid[y][xOne].visited) { return true; } // For solution
			if (grid[y][xOne].value != goodMove && grid[y][xOne].value != pathWay) { return false; }
			if (x <= (m_col - 3)) {
				if ((grid[y][xTwo].value == goodMove && !grid[y][xTwo].visited) ||
					(grid[y][xOne].value == goodMove && !grid[y][xOne].visited)) {
						return true;
					}
			}
		}
		else {
			throw std::invalid_argument("Unknown direction!");
		}
		return false;
	}
	catch (std::invalid_argument& ia) {
		this->exceptionHandling(ia);
		exit(EXIT_FAILURE);
	}
}

/*	Function move()
*	Directions: "UP"	(n.y -= 1)		"DOWN"	(n.y += 1)
*				"LEFT"	(n.x -= 1)		"RIGHT"	(n.x += 1)
*	Function is used in: generateMaze(), generateSolution()
*/
void Labyrinth::move(node& n, dir direction, type typeOfMaze, bool changeDir, int triedPaths) {
	try {
		if (triedPaths == 4) {
			throw std::logic_error("There are no pathways!");
		}
		if (canMove(n, direction, typeOfMaze)) {
			switch (direction) {
			case dir::UP:
				n.y -= 1;
				if (changeDir) { grid[n.y][n.x].from = revertDir(direction); }
				break;
			case dir::DOWN:
				n.y += 1;
				if (changeDir) { grid[n.y][n.x].from = revertDir(direction); }
				break;
			case dir::LEFT:
				n.x -= 1;
				if (changeDir) { grid[n.y][n.x].from = revertDir(direction); }
				break;
			case dir::RIGHT:
				n.x += 1;
				if (changeDir) { grid[n.y][n.x].from = revertDir(direction); }
				break;
			default:
				throw std::invalid_argument("That is an unknown direction..");
			}
		}
		else {
			triedPaths++;
			if (direction == dir::UP) { move(n, revertDir(direction), typeOfMaze, changeDir, triedPaths); }
			else if (direction == dir::DOWN) { move(n, dir::LEFT, typeOfMaze, changeDir, triedPaths); }
			else if (direction == dir::LEFT) { move(n, revertDir(direction), typeOfMaze, changeDir, triedPaths); }
			else if (direction == dir::RIGHT) { move(n, dir::UP, typeOfMaze, changeDir, triedPaths); }
		}
	}
	catch (std::invalid_argument& ia) {
		this->exceptionHandling(ia);
		exit(EXIT_FAILURE);
	}
	catch (std::logic_error& le) {
		this->exceptionHandling(le);
	}
}

/*	Function generateMaze()
*	Types of algorithms: DFS or BFS
*/
void Labyrinth::generateMaze(algorithm al, Grid g, type typeOfMaze) {
	try {
		std::stack<node> m_stack;
		std::deque<node> m_deque;
		if (al == algorithm::DFS || al == algorithm::BFS) {
			if (g == Grid::MAZE) { this->changeGrid(g); }
			node curr = start;
			char goodMove;
			char pathWay;
			if (typeOfMaze == type::NORMAL) { goodMove = '*'; pathWay = '/'; }
			else if (typeOfMaze == type::CUSTOM) { goodMove = '/'; pathWay = '/'; } // All blankspaces in createCustomGrid() are made into '/'
			else { throw std::invalid_argument("that 'type' is invalid!"); }
			
			int random = 0;
			grid[curr.y][curr.x].visited = true; // Start is now added
			m_stack.push(grid[curr.y][curr.x]);
			m_deque.push_back(grid[curr.y][curr.x]);

			while (!m_stack.empty() && !m_deque.empty()) {

				if (al == algorithm::DFS) { // The container´s front/top value
					curr = m_stack.top();
					m_stack.pop();
				}
				else if (al == algorithm::BFS) {
					curr = m_deque.front();
					m_deque.pop_front();
				}
				random = getRandomNumber();

				if (canVisitNeighbor(curr, typeOfMaze)) {
					if (al == algorithm::DFS) { m_stack.push(grid[curr.y][curr.x]); }
					else if (al == algorithm::BFS) { m_deque.push_back(grid[curr.y][curr.x]); }

					move(curr, dir(random), typeOfMaze);

					if (grid[curr.y][curr.x].value == goodMove || grid[curr.y][curr.x].value == 'E') {
						grid[curr.y][curr.x].visited = true;
						if (grid[curr.y][curr.x].value == 'E') { end = grid[curr.y][curr.x]; }
					}
					else {
						grid[curr.y][curr.x].value = pathWay; // Opens up the way.
						grid[curr.y][curr.x].visited = true;
						if (al == algorithm::BFS) { move(curr, dir(random), typeOfMaze); grid[curr.y][curr.x].visited = true; }
					}
					if (al == algorithm::DFS) { m_stack.push(grid[curr.y][curr.x]); }
					else if (al == algorithm::BFS) { m_deque.push_back(grid[curr.y][curr.x]); }
				}
			}
		}
		else { throw std::invalid_argument("That is not a viable algorithm!"); }
	}
	catch (std::invalid_argument& ia) {
		this->exceptionHandling(ia);
		exit(EXIT_FAILURE);
	}
}

/*	Function generateSolution()
*	Function is used in: main()
*/
void Labyrinth::generateSolution(type typeOfMaze) {
	try {
		node curr;
		if (end.visited == false) { throw std::invalid_argument("No solution could be generated!"); }
		this->changeGrid();
		curr = end;
		grid[curr.y][curr.x].path = true;
		while (grid[curr.y][curr.x].value != start.value) {
			move(curr, grid[curr.y][curr.x].from, typeOfMaze, false);
			grid[curr.y][curr.x].path = true;
		}
	}
	catch (std::invalid_argument& ia) {
		this->exceptionHandling(ia);
	}
}

/*	Function changeGrid()
*	Parameter  - changes all nodes in grid to visited = false
*	Parameter 1 - changes grid completely
*/
void Labyrinth::changeGrid(Grid doOver) { // Parameter can be bool
	try {
		if (doOver == Grid::SOLUTION) {
			for (std::size_t y = 0; y < m_row; y++) {
				for (std::size_t x = 0; x < m_col; x++) {
					grid[y][x].visited = false;
				}
			}
		}
		else if (doOver == Grid::MAZE) {
			grid = createGrid();
		}
		else {throw std::invalid_argument("That doOver argument is invalid!"); }
	}
	catch (std::invalid_argument& ia) {
		this->exceptionHandling(ia);
		exit(EXIT_FAILURE);
	}

}

/*	Function printGrid()
*	Parameter "maze" prints maze.
*	Parameter "custom" prints maze for CLI solution
*	Parameter "grid" prints maze for createCustomGrid()
*/
void Labyrinth::printGrid(Labyrinth::print typeOfPrint) const {
	if (typeOfPrint == print::MAZE) {
		for (std::size_t y = 0; y < this->grid.size(); y++) {
			for (std::size_t x = 0; x < this->grid[y].size(); x++) {
				if (grid[y][x].path) {
					if (grid[y][x].value == 'S' || grid[y][x].value == 'E') { 
						std::cout << ESC << GREEN_BKG << ";" << BLACK_TEXT << "m";
					}
					else {
						std::cout << ESC << GREEN_BKG << ";" << GREEN_TEXT << "m";
					}
					std::cout << grid[y][x].value << " ";
					std::cout << RESET;
				}
				else if (grid[y][x].value == '#' || grid[y][x].value == ' ') {

					std::cout << ESC << RED_BKG << ";" << RED_TEXT << "m";
					std::cout << grid[y][x].value << " ";
					std::cout << RESET;
				}
				else if (grid[y][x].value == 'E' || grid[y][x].value == 'S') {
					std::cout << ESC << WHITE_BKG << ";" << BLACK_TEXT << "m";
					std::cout << grid[y][x].value << " ";
					std::cout << RESET;
				}
				else {
					std::cout << ESC << WHITE_BKG << ";" << WHITE_TEXT << "m";
					std::cout << grid[y][x].value << " ";
					std::cout << RESET;
				}
			}
			std::cout << std::endl;
		}
		std::cout << std::endl;
	}
	else if (typeOfPrint == print::CUSTOM) {
		for (std::size_t y = 0; y < this->grid.size(); y++) {
			for (std::size_t x = 0; x < this->grid[y].size(); x++) {
				if (grid[y][x].path) {
					if (grid[y][x].value == 'S' || grid[y][x].value == 'E') { std::cout << grid[y][x].value << " "; }
					else { std::cout << "1 "; }
				}
				else if (grid[y][x].value == 'E' || grid[y][x].value == 'S') {
					std::cout << grid[y][x].value << " ";
				}
				else if (grid[y][x].value != '/') {
					std::cout << "- ";
				}
				else {
					std::cout << "  ";
				}
			}
			std::cout << std::endl;
		}
		std::cout << std::endl;
	}
	else if (typeOfPrint == print::GRID) {
		for (std::size_t y = 0; y < this->grid.size(); y++) {
			for (std::size_t x = 0; x < this->grid[y].size(); x++) {
				if (grid[y][x].value == '/' || grid[y][x].value == '*') {
					std::cout << " ";
				}
				else if (grid[y][x].value == 'S' || grid[y][x].value == 'E') {
					std::cout << grid[y][x].value;
				}
				else {
					std::cout << "-";
				}
			}
			std::cout << std::endl;
		}
		std::cout << std::endl;
	}
}

/*	Function createGrid()
*	Creates a grid according to how big Labyrinth-members m_row[y] and m_col[x] are.
*	Function is used in: Labyrint constructor, changeGrid()
*/
std::vector<std::vector<Labyrinth::node> > Labyrinth::createGrid() {
	try {
		std::vector<std::vector<Labyrinth::node> > grid(m_row, std::vector<Labyrinth::node>(m_col));
		int r1 = rand(), r2 = rand();
		int sideOne = rand() % 10;
		int sideTwo = rand() % 10;
		std::size_t sMod = (m_col / 2) - 1 == 0 ? 1 : ((m_col / 2) - 1);
		std::size_t eMod = (m_col / 2) - 1 == 0 ? 1 : ((m_col / 2) - 1);
		if (sideOne % 2 != 0) { sMod = (m_row / 2) - 1 == 0 ? 1 : ((m_row / 2) - 1); }
		if (sideTwo % 2 != 0) { eMod = (m_row / 2) - 1 == 0 ? 1 : ((m_row / 2) - 1); }
		
			
		std::size_t s = 2 * (r1 % sMod) + 1; // Want to make sure only odd numbers will be used.
		std::size_t e = 2 * (r2 % eMod) + 1;
		for (std::size_t y = 0; y < m_row; y++) {
			for (std::size_t x = 0; x < m_col; x++) {
				Labyrinth::node n;
				if (y == 0 || x == 0) { // LEFT-side and TOP-side
					setNode(n, y, x);
					if (sideOne % 2 == 0) {
						if (s == x) {
							setNode(n, y, x);
							n.value = 'S';
							start = n;
						}
						else { n.value = '#'; }
					}
					else {
						if (s == y) {
							setNode(n, y, x);
							n.value = 'S';
							start = n;
						}
						else { n.value = '#'; }
					}
				}
				else if (y == (m_row - 1) || x == (m_col - 1)) { // BOT-side and RIGHT-side
					setNode(n, y, x);
					if (sideTwo % 2 == 0) {
						if (e == x) {
							setNode(n, y, x);
							n.value = 'E';
							end = n;
						}
						else {
							n.value = '#';
						}
					}
					else {
						if (e == y) {
							setNode(n, y, x);
							n.value = 'E';
							end = n;
						}
						else {
							n.value = '#';
						}
					}
				}
				else if (y % 2 == 1 && x % 2 == 1) { // Creating "real" nodes on every odd number.
					setNode(n, y, x);
					n.value = '*';
				}
				else {
					setNode(n, y, x);
					n.value = ' ';
				}
				grid[y][x] = n;
			}
		}
		return grid;
	}
	catch (std::invalid_argument& ia) {
		this->exceptionHandling(ia);
		exit(EXIT_FAILURE);
	}
}

/*	Function createCustomGrid()
*	Used in order to create a custom grid from std::cin
*/
void Labyrinth::createCustomGrid() {
	std::vector<std::vector<node> > grid;
	std::vector<node> v_nodes;
	std::string str;
	bool exit = false;

	std::getline(std::cin,str);
	m_col = str.length();
	m_row = m_col == 0 ? 0 : 1;
	for (std::size_t y = 0; y < m_row; y++) {
		grid.push_back(v_nodes);
		for (std::size_t x = 0; x < m_col; x++) {
			node n;
			if (str[x] == ' ') { n.value = '/'; }
			else { n.value = str[x]; }
			setNode(n, y, x);
			if (str[x] == 'S') { start = n; }
			else if (str[x] == 'E') { end = n; }
			grid[y].push_back(n);
		}
		std::getline(std::cin, str);
		if (!str.empty()) { m_col = str.length(); }
		if (exit) { break; }
		if (std::cin.eof()) { exit = true; } // So that the last line will be printed.
		if (str.empty()) { break; } // If no input is given, exit function!
		m_row++;
	}
	if (m_row != 0) { setNodes(static_cast<double>(m_row), static_cast<double>(m_col)); }
	this->grid = grid;
}

/*	Function generateRandomNumber()
*	Generates a number between min and max.
*	Function is used in: getRandomNumber()
*/
int Labyrinth::generateRandomNumber(int min, int max) {
	int number;
	number = rand() % max;
	return number+1;
}

/*	Function getRandomNumber()
*	Returns a random number between 1 and 4.
*	Function is used in: generateMaze()
*/
int Labyrinth::getRandomNumber() {
	return generateRandomNumber(1, 4);
}
/*	Function exceptionHandling()
*	Being used to simply handle exceptions I want to throw.
*/
void Labyrinth::exceptionHandling(std::exception e) {
	std::cout << "Exception: " << e.what() << std::endl;
}
