#pragma once
#include "nodePoint.h"
#include <vector>
#include <algorithm>
using std::vector;

class TreeFactory {
public:
	static NodePoint* createTree(vector<vector<char>> instructions);
	static void helperTree(vector<char> instr, NodePoint* root, int index);
	static void createTreeHelp(vector<char> instr, NodePoint* root, int index);
	static NodePoint* containsInstruction(vector<NodePoint*> kids, char inst);

};