#pragma once

#ifndef MODIFIESS_H
#define MODIFIESS_H

#include <unordered_map>
#include <unordered_set>
#include <string>

#include "../../Common/Types.h"

class ModifiesS {
private:
	// key: stmtNum, value: variable used in stmt on the left side of '='
	std::unordered_map<std::string, std::unordered_set<std::string>> modifiesSStmtVarTable;

	// key: var, value: statements where given variable is modified
	std::unordered_map<std::string, std::unordered_set<std::string>> modifiesSVarStmtLstTable;

public:
	ModifiesS();

	// varLst > 1 elements for container statements
	void insertModifiesS(StmtIndex stmtNum, std::vector<std::string> varLst);

	std::vector<std::string> getModifiesSLeftArgLst(std::string rightArg);
	std::vector<std::string> getModifiesSRightArgLst(StmtIndex leftArg);
	std::unordered_map<std::string, std::vector<std::string>> getModifiesSTable();
};

#endif
