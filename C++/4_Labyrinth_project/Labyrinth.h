/*	Name:		Peter Stegeby (pets2001)
*	Created:	April 2021
*	Modified:	May 2021
*	Grade:		A
*/

#ifndef LABYRINTH_H
#define LABYRINTH_H

#include <iostream>
#include <vector>

class Labyrinth {
private:
	enum class dir { UP = 1, DOWN = 2, LEFT = 3, RIGHT = 4, UNSET = 10 }; // UNSET shows that node hasn't come from anywhere.

	struct node {
		node() = default;
		std::size_t y = 0, x = 0;
		char value{};
		dir from = dir::UNSET;	// Is used for solution
		bool visited = false;
		bool path = false;		// Is used for solution
	};
	
public:
	Labyrinth() = default;
	Labyrinth(int row, int col);

	enum class type { NORMAL, CUSTOM };
	enum class print { MAZE, CUSTOM, GRID };
	enum class Grid {MAZE, SOLUTION };
	enum class algorithm {DFS, BFS };

	// node - Getter and Setter
	std::size_t getNode(node n, std::string xy) { return xy == "x" ? n.x : n.y; }

	// Start and End - Getter and Setter
	std::size_t getStart(std::string xy) { return xy == "x" ? start.x : start.y; }
	std::size_t getEnd(std::string xy) { return xy == "x" ? end.x : end.y; }
	
	// node - move
	bool canMove(node n, dir direction, type t = type::NORMAL);
	bool canVisitNeighbor(node n, type t = type::NORMAL);

	// Grid / maze
	std::vector<std::vector<node> > createGrid();
	void createCustomGrid();
	void generateMaze(algorithm a = algorithm::DFS, Grid g = Grid::SOLUTION, type t = type::NORMAL);
	void generateSolution(type = type::NORMAL);
	void printGrid(print typeOfPrint) const;
	
	// Access/Modify members of class
	std::size_t getRow() const { return this->m_row; }
	std::size_t getCol() const { return this->m_col; }
	double getNodes() const { return this->m_nodes; }
	bool is_empty() const { return m_nodes == 0 ? true : false; }

	// Methods for enum dir
	dir revertDir(dir e);

	// Others
	int generateRandomNumber(int min, int max);
	int getRandomNumber();
	
	void exceptionHandling(std::exception);

private:
	void setNodes(double row, double col) { this->m_nodes = (((row - 1) / 2) * ((col - 1) / 2)) + 2; }
	void setSize(std::size_t row, std::size_t col) { this->m_row = row, this->m_col = col; }
	void setNode(node& n, std::size_t y, std::size_t x, dir from = dir::UNSET) { n.y = y; n.x = x; n.from = from; }
	void move(node& n, dir direction, type t = type::NORMAL, bool changeDir = true, int triedPaths = 0);
	void changeGrid(Grid g = Grid::SOLUTION);
	
	std::size_t m_row = 11;
	std::size_t m_col = 11;
	double m_nodes = 0;
	std::vector<std::vector<node> > grid;
	node start;
	node end;
};

#endif
