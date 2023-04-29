#pragma once

#ifndef PRINTVAR_H
#define PRINTVAR_H

#include <unordered_map>
#include <unordered_set>
#include <string>

#include "../../Common/Types.h"
#include "../../Common/SPAException.h"

class PrintVar {
private:
	// key: stmtNum, value: varName
	std::unordered_map<StmtIndex, std::string> printVarTable;

	// key: varName, value: stmtLst
	std::unordered_map<std::string, std::unordered_set<std::string>> varStmtLstTable;

public:
	PrintVar();
	void insertPrint(StmtIndex stmtNum, std::string varName);
	std::vector<std::string> getStmtLstfromVar(std::string varName);
	std::vector<std::string> getVarfromStmtIdx(StmtIndex stmtNum);
	std::vector<std::string> getAllPrints();
	std::pair<std::vector<std::string>, std::vector<std::string>> getAllPrintsVarNames();
};

#endif
