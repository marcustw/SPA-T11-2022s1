#pragma once

#ifndef READVAR_H
#define READVAR_H

#include <unordered_map>
#include <unordered_set>

#include "../../Common/Types.h"
#include "../../Common/SPAException.h"

class ReadVar {
private:
	// key: stmtNum, value: var_being_read
	std::unordered_map<StmtIndex, std::string> stmtVarReadTable;

	// key: varName, value: stmtLst where var is read
	std::unordered_map<std::string, std::unordered_set<std::string>> varStmtLstReadTable;

public:
	ReadVar();
	void insertRead(StmtIndex stmtNum, std::string varName);
	std::vector<std::string> getStmtLstfromVar(std::string varName);
	std::vector<std::string> getVarfromStmtIdx(StmtIndex stmtNum);
	std::vector<std::string> getAllReads();
	std::pair<std::vector<std::string>, std::vector<std::string>> getAllReadsVarName();
};

#endif
