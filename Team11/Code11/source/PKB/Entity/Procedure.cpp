
#include "Procedure.h"

Procedure::Procedure() {}

void Procedure::insertProc(StmtIndex startStmtNum, StmtIndex endStmtNum, std::string procName) {
	for (StmtIndex i = startStmtNum; i <= endStmtNum; ++i) {
		stmtProcTable.insert({ i, procName });
	}
	std::vector<StmtIndex> procRange = { startStmtNum, endStmtNum };
	procRangeTable.insert({ procName, procRange });
}

std::vector<std::string> Procedure::getAllProcedures() {
	std::vector<std::string> res;

	for (auto& proc : procRangeTable) {
		res.push_back(proc.first);
	}
	return res;
}

std::vector<std::string> Procedure::getProcedureFromStmtIdx(StmtIndex stmtNum) {
	std::unordered_map<StmtIndex, std::string>::const_iterator procExist = stmtProcTable.find(stmtNum);
	std::vector<std::string> res;

	if (procExist != stmtProcTable.end()) {
		res = { procExist->second };
	}
	return res;
}

std::pair<std::vector<std::string>, std::vector<std::string>> Procedure::getAllProcedureNames() {
	std::vector<std::string> res;
	std::vector<std::string> resIdx;
	for (auto& proc : stmtProcTable) {
		res.push_back(proc.second);
		resIdx.push_back(proc.second);
	}
	return { res, resIdx };
}
