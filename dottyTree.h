#pragma once
#include <fstream>
#include "nodePoint.h"

class DottyTree {
public:
	NodePoint* root;
	DottyTree(NodePoint* _root);
	void dottyPrint(std::ostream& out);
	void helper(std::ostream& out, NodePoint* root);
};