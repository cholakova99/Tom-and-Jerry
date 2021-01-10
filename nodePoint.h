#pragma once
#include <vector>
#include <list>

class NodePoint
{
private:
	char data;
public:
	NodePoint* validInstruction(std::vector<NodePoint*> instructions, char instruction);
	std::vector<NodePoint*> kids;
	std::vector<NodePoint*> getKids();
	void addEdge(std::list<char> instructions);
	char getData();
	NodePoint(char _data);

};