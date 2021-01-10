#include "DottyTree.h"

DottyTree::DottyTree(NodePoint* _root) {
	this->root = _root;
}

void DottyTree::dottyPrint(std::ostream& out) {
	out << "digraph instructionstree {" << std::endl;
	helper(out, root);
	out << "}";
}

void DottyTree::helper(std::ostream& out, NodePoint* root) {
	if (root == nullptr){
		return;
	}
	for (auto kid : root->getKids()) {
		out << (long)root << "->" << (long)kid << std::endl;
		helper(out, kid);
	}
	out << (long)root << "[label=\"" << root->getData() << "\"];" << std::endl;
}