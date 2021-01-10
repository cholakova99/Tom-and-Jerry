#pragma once
#include <set>
#include <vector>
#include <queue>
#include <stack>
#include <fstream>
#include <iostream>
#include <string>
#include <list>
#include "point.h"
#include "FromStart.h"
#include "TreeFactory.h"
#include "DottyTree.h"
using std::vector;


class MapGame
{
public:
	static void helpingFuncForMoving(FromStart& z, Point& current, Point nextone, const int& dist, std::queue<Point>& front, std::vector<char> map[]);
	static void findShortestPathsHelping(std::stack<Point>& ourStack, Point& ourPoint, FromStart**& visited, vector<vector<Point>>& res);
	static vector<vector<Point>>* findShortestPaths(std::vector<char> map[], int _row, int _col, Point source, Point dest);
	static void printAllShortWays(vector<vector<Point>>& pathGame, vector<char>* MapGame);
	static vector<vector<char>> convertToCharCommands(vector<vector<Point>>& pathGame, vector<char>* MapGame);
	static void printCharCommands(vector<vector<char>>& commands);
	static void ReadAndCreate(const char* myFilePath);
	static int countPaint(vector<char> ins);
	static int countTurns(vector<char> path);
	static vector<char> leastTurns(vector<vector<char>> maxPainted);
	static vector<vector<char>> maxPaint(vector<vector<char>> instructions);
	static void printTree(NodePoint* root);
};