#pragma once

#ifndef STATEMENT_H
#define STATEMETN_H

#include <unordered_map>
#include <string>

#include "../../Common/Types.h"
#include "../../Common/SPAException.h"

class Statement {
private:
	// key: stmtNum (every line), value: Statement Type of every statement
	std::unordered_map<StmtIndex, StatementType> stmtNumToTypeTable;

public:
	Statement();

	// assume this will be called for every stmt line of SOURCE code
	void insertStmt(StmtIndex stmtNum, StatementType stmtType);

	std::vector<std::string> getAllStmts();
	std::vector<StatementType> getStmtTypeFromStmtIdx(StmtIndex stmtNum);
};

#endif
