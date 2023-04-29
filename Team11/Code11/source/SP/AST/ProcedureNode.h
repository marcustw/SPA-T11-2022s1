#pragma once

#include <string>
#include <vector>

#include "StmtLstNode.h"
#include "TNode.h"

class Visitor;

class ProcedureNode : public TNode {
public:
	ProcedureNode(std::string procedureName, int stmtIdx);
	~ProcedureNode();

	void addLastStmt(int stmtIdx);
	void addStmtLst(StmtLstNode* stmtLst);
	void accept(Visitor* visitor);

	int getStmtIndex();
	int getLastStmt();
	StmtLstNode* getStmtLstNode();
	std::string getProcedureName();
private:
	int stmtIndex;
	int lastStmt;
	StmtLstNode* stmtLstNode;
	std::string procedureName;
};
