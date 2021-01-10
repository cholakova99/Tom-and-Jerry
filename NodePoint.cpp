#include "nodePoint.h"
#include <algorithm>
#include <list>
#include <vector>
#include <iostream>

char NodePoint::getData() {
	return this->data;
}

NodePoint::NodePoint(char _data) {
	this->data = _data;
}

std::vector<NodePoint*> NodePoint::getKids() {
	return kids;
}

/////////////////////// IF WE TRY WITH LIST
NodePoint* NodePoint::validInstruction(std::vector<NodePoint*> instructions, char instruction) {
	for (auto it = instructions.begin(); it != instructions.end(); ++it) {
		if ((*it)->getData() == instruction) {
			return *it;
		}
	}

	return nullptr;
}

//////////////////////////// IF WE TRY WITH LIST
void NodePoint::addEdge(std::list<char> instructions) {
	
	NodePoint* current = this;
	std::list<char>::iterator it;
	for (it = instructions.begin(); it != instructions.end(); ++it) {
		NodePoint* wantedKid = validInstruction(current->getKids(), *it);
		if (wantedKid == nullptr) {
			current->kids.push_back(new NodePoint(*it));
			current = current->getKids().back();
		}
		else{
			current = wantedKid;
		}
	}
}
