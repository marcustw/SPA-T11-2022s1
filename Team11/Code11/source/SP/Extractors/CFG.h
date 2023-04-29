#pragma once

#include <unordered_map>
#include <unordered_set>
#include <string>

#include "../AST/ProgrammeNode.h"

class CFG {
private:
	std::unordered_map<int, std::unordered_set<int>>* cfgMap;
	std::vector<int> predecessors;

	void processProgrammeNode(ProgrammeNode* ASTRoot);
	void processProcedureNode(ProcedureNode* procedureNode);
	void processStmtLst(StmtLstNode* stmtLstNode);
	void processStmt(StmtNode* stmt);
	void processWhileNode(StmtNode* stmt);
	void processIfNode(StmtNode* stmt);
public:
	CFG();

	std::unordered_map<int, std::unordered_set<int>>* generateCFGMap(ProgrammeNode* ASTRoot);
};
