#pragma once

#ifndef PROCEDURE_H
#define PROCEDURE_H

#include <unordered_map>
#include <unordered_set>

#include "../../Common/Types.h"
#include "../../Common/SPAException.h"

class Procedure {
private:
	// key: procName, value: range of stmt belonging to proc
	std::unordered_map<std::string, std::vector<StmtIndex>> procRangeTable;

	// key: stmtNume, value: proc that contains stmt
	std::unordered_map<StmtIndex, std::string> stmtProcTable;

public:
	Procedure();
	void insertProc(StmtIndex startStmtNum, StmtIndex endStmtNum, std::string procName);
	std::vector<std::string> getAllProcedures();
	std::vector<std::string> getProcedureFromStmtIdx(StmtIndex stmtNum);
	std::pair<std::vector<std::string>, std::vector<std::string>> getAllProcedureNames();
};

#endif
