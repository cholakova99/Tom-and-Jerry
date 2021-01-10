#include "TreeFactory.h"

void TreeFactory::createTreeHelp(vector<char> instr, NodePoint* root, int index)
{
	if (instr.size() > index&& index > 0) {		
		root->kids.push_back(new NodePoint(instr[index]));

		if (index < instr.size()) {
			index++;
			createTreeHelp(instr, root->getKids()[0], index);

		}
	}
}

NodePoint* TreeFactory::containsInstruction(vector<NodePoint*> kids, char inst) {
	for (int i = 0; i < kids.size(); i++) {
		if (kids[i]->getData() == inst) {
			return kids[i];
		}
	}
	return nullptr;
}

void TreeFactory::helperTree(vector<char> instr, NodePoint* root, int index) {
	if (root->getKids().size() == 0 && index < instr.size()) {
			root->kids.push_back(new NodePoint(instr[index]));
			index++;
			helperTree(instr, root->getKids().back(), index);
	} else if (root->getKids().size() > 0 && index < instr.size()) {
		NodePoint* foundKid = containsInstruction(root->getKids(), instr[index]);
		if (foundKid==nullptr) {
			root->kids.push_back(new NodePoint(instr[index]));
			index++;
			helperTree(instr, root->getKids().back(), index);
		}
		else  {
			index++;
			helperTree(instr, foundKid, index);
		}
	} 
}

NodePoint* TreeFactory::createTree(vector<vector<char>> instructions)
{
	if (instructions.size() == 0 || instructions[0].size() == 0) {
		return nullptr;
	} 
	NodePoint* root = new NodePoint(instructions[0][0]);
	createTreeHelp(instructions[0], root, 1);
	for (int i = 1; i < instructions.size(); i++)
	{
		helperTree(instructions[i], root, 1);
	}

	return root;
}