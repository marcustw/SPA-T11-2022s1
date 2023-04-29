#pragma once

#include <unordered_map>
#include <unordered_set>
#include <string>

#include "../../Common/Types.h"

class Pattern {
private:
	// key: stmtNum, value: list of expressions found in given statement
	std::unordered_map<StmtIndex, std::unordered_set<std::string>> stmtExpressionLstTable;

	// key: expression, value: list of statements that expression is found in
	std::unordered_map<std::string, std::unordered_set<std::string>> expressionStmtLstTable;

	// key: full rhs expression, value: list of statements that has the full expression as the rhs
	std::unordered_map<std::string, std::unordered_set<StmtIndex>> fullExpStmtTable;

public:
	Pattern();
	void insertStmtExpressionLst(StmtIndex stmtNum, std::string expression);
	void insertStmtExactExpression(StmtIndex stmtNum, std::string expression);
	std::vector<std::string> getExpressionLstFromStmt(StmtIndex stmtNum);
	std::vector<std::string> getStmtLstFromExactExpression(std::string expression);
};

