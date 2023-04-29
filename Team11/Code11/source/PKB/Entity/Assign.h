#pragma once

#ifndef ASSIGN_H
#define ASSIGN_H

#include <unordered_map>
#include <unordered_set>
#include <string>

#include "../../Common/Types.h"

class Assign {
private:
	// key: stmtNum where var is assigned, value: varName
	std::unordered_map<StmtIndex, std::string> stmtVarAssignTable;

	// key: varName, value: stmtLst where var is assigned
	std::unordered_map<std::string, std::unordered_set<std::string>> varStmtLstAssignTable;

public:
	Assign();
	void insertAssign(StmtIndex stmtNum, std::string varName);
	std::vector<std::string> getAllAssignments();  // return list of statement numbers with assignments
	std::vector<std::string> getStmtLstByVarAssignment(std::string varName);
	std::vector<std::string> getAssignmentFromStmtIdx(StmtIndex stmtNum);
};

#endif
