#pragma once

#ifndef USESS_H
#define USESS_H

#include <unordered_map>
#include <unordered_set>
#include <string>

#include "../../Common/Types.h"

class UsesS {
private:
	// key: stmtNum, value: variable used in stmt on the right side of '='
	std::unordered_map<std::string, std::unordered_set<std::string>> usesSStmtVarLstTable;
	std::unordered_map<std::string, std::unordered_set<std::string>> usesSVarStmtLstTable;

public:
	UsesS();
	void insertUsesS(StmtIndex stmtNum, std::vector<std::string> varLst);
	std::vector<std::string> getUsesSLeftArgLst(std::string varName);
	std::vector<std::string> getUsesSRightArgLst(StmtIndex stmtNum);
	std::unordered_map<std::string, std::vector<std::string>> getUsesSTable();
};

#endif
