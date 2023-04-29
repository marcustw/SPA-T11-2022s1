#pragma once

#ifndef CONSTANT_H
#define CONSTANT_H

#include <unordered_map>
#include <unordered_set>
#include <string>

#include "../../Common/Types.h"

class Constant {
private:
	// key: constant , value: stmtlst where constant appears
	std::unordered_map<ConstValue, std::unordered_set<StmtIndex>> constStmtTable;

	// key: stmtNum, value: list of constants found in the statement
	std::unordered_map<StmtIndex, std::unordered_set<std::string>> stmtConstLstTable;

public:
	Constant();
	void insertConst(StmtIndex stmtNum, std::vector<ConstValue> constLst);
	std::vector<std::string> getAllConsts();
};

#endif
