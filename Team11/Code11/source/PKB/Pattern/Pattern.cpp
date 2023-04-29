
#include "Pattern.h"

Pattern::Pattern() {}

void Pattern::insertStmtExpressionLst(StmtIndex stmtNum, std::string expression) {
	std::unordered_map<StmtIndex, std::unordered_set<std::string>>::const_iterator stmtExist =
		stmtExpressionLstTable.find(stmtNum);
	if (stmtExist == stmtExpressionLstTable.end()) {
		stmtExpressionLstTable.insert({ stmtNum, {expression} });
	} else {
		std::unordered_set<std::string> expLst = stmtExist->second;
		expLst.insert(expression);
		stmtExpressionLstTable[stmtNum] = expLst;
	}
	std::unordered_map<std::string, std::unordered_set<std::string>>::const_iterator expressionExist =
		expressionStmtLstTable.find(expression);
	if (expressionExist == expressionStmtLstTable.end()) {
		expressionStmtLstTable.insert({ expression, {std::to_string(stmtNum)} });
	} else {
		std::unordered_set<std::string> lst = expressionExist->second;
		lst.insert(std::to_string(stmtNum));
		expressionStmtLstTable[expression] = lst;
	}
}

void Pattern::insertStmtExactExpression(StmtIndex stmtNum, std::string expression) {
	std::unordered_map<std::string, std::unordered_set<StmtIndex>>::const_iterator fullExpExist =
		fullExpStmtTable.find(expression);
	if (fullExpExist == fullExpStmtTable.end()) {
		fullExpStmtTable.insert({ expression, {stmtNum} });
	} else {
		std::unordered_set<StmtIndex> stmtLst = fullExpExist->second;
		stmtLst.insert(stmtNum);
		fullExpStmtTable[expression] = stmtLst;
	}
}

std::vector<std::string> Pattern::getExpressionLstFromStmt(StmtIndex stmtNum) {
	std::vector<std::string> res;
	std::unordered_map<StmtIndex, std::unordered_set<std::string>>::const_iterator stmtExist =
		stmtExpressionLstTable.find(stmtNum);
	if (stmtExist != stmtExpressionLstTable.end()) {
		std::unordered_set<std::string> expressionLst = stmtExist->second;
		for (auto& expression : expressionLst) {
			res.push_back(expression);
		}
	}
	return res;
}

std::vector<std::string> Pattern::getStmtLstFromExactExpression(std::string expression) {
	std::unordered_map<std::string, std::unordered_set<StmtIndex>>::const_iterator fullExpExist =
		fullExpStmtTable.find(expression);
	std::vector<std::string> res;
	if (fullExpExist != fullExpStmtTable.end()) {
		std::unordered_set<StmtIndex> stmtLst = fullExpExist->second;
		for (auto& stmt : stmtLst) {
			res.push_back(std::to_string(stmt));
		}
	}
	return res;
}
