#include "MapGame.h"
#include <iostream>


// z is the cell in which we would like to go
// current is our current position
// dist - distance (a.k.a distance from the neighbourhood point from which we are coming + 1)
// front - the queue of points
void MapGame::helpingFuncForMoving(FromStart& z, Point& current, Point nextone, const int& dist, std::queue<Point>& front, std::vector<char> map[]) 
{
	//we use '1' to initialize the furniture in the room => we can't step there
	if (map[nextone.row][nextone.col] != '1' && dist <= z.distance) {

		if (dist < z.distance)
		{

			z.points.clear();
			front.push(nextone);
		}
		z.points.insert(current);
		z.distance = dist;
	}
}

//ourStack is already created stack 
//ourPoint is the destination
void MapGame::findShortestPathsHelping(std::stack<Point>& ourStack, Point& ourPoint, FromStart**& visited, vector<vector<Point>>& paths) {
	// in our stack, insert the ourpoint
	ourStack.push(ourPoint);

	// if we have reached to there with ony 1 way
	FromStart& f = visited[ourPoint.row][ourPoint.col];
	if (f.points.empty()) {
		vector<Point> newone;
		while (!ourStack.empty())
		{
			newone.push_back(ourStack.top());
			ourStack.pop();
		}
		paths.push_back(newone);
		return;
	}
	unsigned int counter = 0;
	// iter recursive so az to find more than 1 short way
	for (const Point& _p : f.points) {
		Point p(_p);
		if (counter < (f.points.size() - 1))
		{
			std::stack<Point> helper = ourStack;
			findShortestPathsHelping(helper, p, visited, paths);
		}
		else {
			findShortestPathsHelping(ourStack, p, visited, paths);
		}
	}

}


// func to find the shortest paths to the destination
vector<vector<Point>>* MapGame::findShortestPaths(std::vector<char> map[], int _row, int _col, Point source, Point dest)
{
	FromStart** visited = new FromStart * [_row];
	for (int i = 0; i < _row; i++)
	{
		visited[i] = new FromStart[_col];
	}
	std::queue<Point> front;
	front.push(source);
	// distance from the start should be 0
	visited[source.row][source.col].distance = 0;

	// bfs
	while (!front.empty()) {
		Point current = front.front();
		const int dist = visited[current.row][current.col].distance + 1;
		front.pop();
		Point nextone;
		if (current.row > 0) {
			nextone.row = current.row - 1;
			nextone.col = current.col;
			helpingFuncForMoving(visited[nextone.row][nextone.col], current, nextone, dist, front, map);
		}
		if (current.row < _row - 1) {
			nextone.row = current.row + 1;
			nextone.col = current.col;
			helpingFuncForMoving(visited[nextone.row][nextone.col], current, nextone, dist, front, map);
		}
		if (current.col > 0) {
			nextone.row = current.row;
			nextone.col = current.col - 1;
			helpingFuncForMoving(visited[nextone.row][nextone.col], current, nextone, dist, front, map);
		}
		if (current.col < _col - 1) {
			nextone.row = current.row;
			nextone.col = current.col + 1;
			helpingFuncForMoving(visited[nextone.row][nextone.col], current, nextone, dist, front, map);
		}

	}
	vector<vector<Point>>* paths = new vector<vector<Point>>;
	std::stack<Point> ourStackOfPoint;
	findShortestPathsHelping(ourStackOfPoint, dest, visited, *paths);
	return paths;
}

// func to print all possible shortest ways
void MapGame::printAllShortWays(vector<vector<Point>>& pathGame, vector<char>* MapGame)
{
	std:: cout << " Shortest path has : " << pathGame[0].size() - 1 << " steps " << std::endl;
	for (int i = 0; i < pathGame.size(); i++)
	{
		// two integers to count the times we have turned while walking & times we have used the paint
		int countRTurns = 0;
		int counterPaint = 0;
		for (int j = 1; j < pathGame[i].size(); j++)
		{
			if (MapGame[pathGame[i][j].row][pathGame[i][j].col] == 'p')
			{
				counterPaint++;
			}
			if (j - 2 >= 0)
			{
				if (pathGame[i][j].row == pathGame[i][j - 1].row && pathGame[i][j - 2].row != pathGame[i][j].row)
				{
					countRTurns++;
				}
				if (pathGame[i][j].col == pathGame[i][j - 1].col && pathGame[i][j - 2].col != pathGame[i][j].col)
				{
					countRTurns++;
				}
			}
			std::cout << "(" << pathGame[i][j].row << "," << pathGame[i][j].col << ")" << " -> ";

		}
		std::cout << " number of turns is " << countRTurns << std::endl;
		std::cout << " number painted places is " << counterPaint << std::endl;
		std::cout << " length of that way was : " << pathGame[i].size() - 1 << std::endl;
		std::cout << std::endl;
	}

}

vector<vector<char>> MapGame::convertToCharCommands(vector<vector<Point>>& pathGame, vector<char>* MapGame)
{
	std::vector<vector<char>> commands(pathGame.size());
	for (int i = 0; i < pathGame.size(); i++)
	{
		std::vector<char> hh;
		commands.push_back(hh);
		commands[i].push_back('T');
		for (int j = 1; j < pathGame[i].size(); j++)
		{
			if (MapGame[pathGame[i][j].row][pathGame[i][j].col] == 'p')
			{
				commands[i].push_back('P');
			}

			if (pathGame[i][j].row == pathGame[i][j - 1].row && pathGame[i][j].col == (pathGame[i][j - 1].col - 1)) {

				commands[i].push_back('N');
			}
			else if (pathGame[i][j].row == pathGame[i][j - 1].row && pathGame[i][j].col == (pathGame[i][j - 1].col + 1)) {

				commands[i].push_back('S');
			}
			else if (pathGame[i][j].row == (pathGame[i][j - 1].row - 1) && pathGame[i][j].col == (pathGame[i][j - 1].col)) {

				commands[i].push_back('W');
			}
			else if (pathGame[i][j].row == (pathGame[i][j - 1].row + 1) && pathGame[i][j].col == pathGame[i][j - 1].col) {

				commands[i].push_back('E');
			}
		}
	}
	return commands;
}

int MapGame::countPaint(vector<char> ins) {
	int res = 0;
	for (int i = 0; i < ins.size(); i++) {
		if (ins[i] == 'P')
		{
			res++;
		}
	}
	return res;
}

vector<vector<char>> MapGame::maxPaint(vector<vector<char>> instructions)
{
	int maxPaint = -1;
	std::vector<vector<char>> res;
	for (int i = 0; i < instructions.size(); i++)
	{
		if (maxPaint == countPaint(instructions[i]))
		{
			res.push_back(instructions[i]);
		}
		else if (maxPaint < countPaint(instructions[i])) {
			maxPaint = countPaint(instructions[i]);
			res.clear();
			res.push_back(instructions[i]);
		}
	}
	return res;
}

int MapGame::countTurns(vector<char> path)
{
	int counter = 0;
	char k;
	for (int i = 1; i < path.size(); i++)
	{
		k = path[i];
		if (k == 'P') {
			if (path[i + 1] != path[i - 1])
			{
				counter++;
			}
			i++;
		}
		if (k != 'P' && (path[i - 1] != path[i]))
		{
			counter++;
		}

	}
	return counter;
}

vector<char> MapGame::leastTurns(vector<vector<char>> maxPainted)
{
	int leastTurns = countTurns(maxPainted.front());
	vector<char> res;
	for (int i = 1; i < maxPainted.size(); i++)
	{
		if (leastTurns > countTurns(maxPainted[i]))
		{
			res = maxPainted[i];
		}
	}
	return res;
}

// HELP FUNC 
void MapGame::printCharCommands(vector<vector<char>>& commands)
{
	for (int i = 0; i < commands.size(); i++)
	{
		for (int j = 1; j < commands[i].size(); j++)
		{
			if (j == commands[i].size() - 1) {
				std::cout << commands[i][j];
			}
			else {
				std::cout << commands[i][j] << " -> ";
			}
		}
		std::cout << std::endl;
	}
}

void MapGame::ReadAndCreate(const char* myFilePath) {
	std::ifstream myFile;
	myFile.open(myFilePath, std::ios::in);

	if (!myFile.is_open()) {
		return;
	}

	//////////// CREATE ROOM FROM FILE : 
	int roomRows;
	int roomCols;
	Point jerry;
	Point tom;
	int countFurniture;
	int countPaintPlaces;
	myFile >> roomRows >> roomCols;
	vector<char>* MapGame = new vector<char>[roomRows];
	for (int i = 0; i < roomRows; i++)
	{

		for (int j = 0; j < roomCols; j++)
		{
			MapGame[i].push_back('*');
		}

	}
	myFile >> jerry.col >> jerry.row;
	myFile >> tom.col >> tom.row;
	MapGame[jerry.row][jerry.col] = 'j';
	MapGame[tom.row][tom.col] = 't';
	myFile >> countFurniture >> countPaintPlaces;
	for (int i = 0; i < countFurniture; i++)
	{
		Point furniture;
		myFile >> furniture.col >> furniture.row;
		std::string ss;
		myFile.ignore();
		std::getline(myFile, ss);
		int counterRow = 0;

		while (ss.compare("===") != 0)
		{
			for (int i = 0; i < ss.size(); i++)
			{
				MapGame[furniture.row + counterRow][furniture.col + i] = ss[i];
			}
			std::getline(myFile, ss);
			counterRow++;
		}
	}
	for (int i = 0; i < countPaintPlaces; i++)
	{
		Point paint;
		myFile >> paint.col >> paint.row;
		MapGame[paint.row][paint.col] = 'p';
	}
	for (int i = 0; i < roomRows; i++)
	{
		for (int j = 0; j < roomCols; j++)
		{
			int counterPaint = 0;
			if (MapGame[i][j] == 'p')
			{
				counterPaint++;
			}
			std::cout << MapGame[i][j];
		}
		std::cout << std::endl;

	}
	std::cout << std::endl;

	/////////// FIND ALL SHORTEST PATHS :
	vector<vector<Point>>* paths = findShortestPaths(MapGame, roomRows, roomCols, tom, jerry);
	std::cout << paths->size() << " is the number of shortest ways " << std::endl;
	printAllShortWays(*paths, MapGame);
	std::cout << std::endl;

	/////////// CONVERT TO CHAR INFO FOR THE DOTTY TREE
	vector<vector<char>> charcommands = convertToCharCommands(*paths, MapGame);
	printCharCommands(charcommands);
	NodePoint* treeOfTheDron = TreeFactory::createTree(charcommands);

	/// PRINT THE PATH WITH LEAST TURNS AND MOST PAINTED PLACES :
	vector<char> leastTurnsMaxPaintedWay = leastTurns(maxPaint(charcommands));
	std::cout << " WE ARE LOOKING FOR : " << std::endl;
	for (int i = 1; i < leastTurnsMaxPaintedWay.size(); i++)
	{
		std::cout << leastTurnsMaxPaintedWay[i] << " - > ";
	}

	
	std::ofstream file("tomjerry2.dot");
	DottyTree tree(treeOfTheDron);
	tree.dottyPrint(file);
	file.close();
	

	// CREATE IMAGE PART :
	// USE PATH TO THE PROJECT HERE : 
	system("cd C:\\Program Files (x86)\\Graphviz2.38\\bin && .\\dot -Tjpg C:\\Users\\zlatina\\source\\repos\\tom_and_jerry_81867_final\\tomjerry2.dot -o C:\\Users\\zlatina\\source\\repos\\tom_and_jerry_81867_final\\tree.jpg");
	system("C:\\Users\\zlatina\\source\\repos\\tom_and_jerry_81867_final\\tree.jpg");
}