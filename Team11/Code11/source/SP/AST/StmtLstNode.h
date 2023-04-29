#pragma once

#include <vector>
#include "TNode.h"

class Visitor;
class StmtNode;

class StmtLstNode : public TNode {
public:
	StmtLstNode();
	~StmtLstNode();

	void addStmt(StmtNode* stmt);
	void accept(Visitor* visitor);
	int getStmtIndex();
	std::vector<StmtNode*> getStmtNodes();

private:
	int stmtIndex;
	std::vector<StmtNode*> stmtNodes;
};
