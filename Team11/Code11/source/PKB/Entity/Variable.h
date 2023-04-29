#pragma once

#ifndef VARIABLE_H
#define VARIABLE_H

#include <unordered_set>
#include <unordered_map>

#include "../../Common/Types.h"
#include "../../Common/SPAException.h"

class Variable {
private:
	// key: stmtNum, value: list of vars in given statement
	std::unordered_map<std::string, std::unordered_set<std::string>> stmtVarLstTable;

	// key: varName, value: list of statements where var appears
	std::unordered_map<std::string, std::unordered_set<std::string>> varStmtLstTable;

public:
	Variable();
	void insertVar(StmtIndex stmtNum, std::string varName);
	std::vector<std::string> getAllVars();
	std::vector<std::string> getVarLstFromStmtIdx(StmtIndex stmtNum);
};

#endif
