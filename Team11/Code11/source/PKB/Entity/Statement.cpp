
#include "Statement.h"

Statement::Statement() {}

void Statement::insertStmt(StmtIndex stmtNum, StatementType stmtType) {
	stmtNumToTypeTable.insert({ stmtNum, stmtType });
}

std::vector<StatementType> Statement::getStmtTypeFromStmtIdx(StmtIndex stmtNum) {
	std::unordered_map<StmtIndex, StatementType>::const_iterator stmtTypeExist =
		stmtNumToTypeTable.find(stmtNum);
	std::vector<StatementType> res;

	if (stmtTypeExist != stmtNumToTypeTable.end()) {
		res = { stmtTypeExist->second };
	}
	return res;
}

std::vector<std::string> Statement::getAllStmts() {
	std::vector<std::string> res;

	for (auto& element : stmtNumToTypeTable) {
		res.push_back(std::to_string(element.first));
	}

	return res;
}
