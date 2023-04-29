
#include "Assign.h"

Assign::Assign() {}

void Assign::insertAssign(StmtIndex stmtNum, std::string varName) {
	stmtVarAssignTable.insert({ stmtNum, varName });  // inserts only if statement has not been inserted before
	std::unordered_map<std::string, std::unordered_set<std::string>>::const_iterator varExist =
		varStmtLstAssignTable.find(varName);
	std::unordered_set<std::string> stmtSet;
	if (varExist != varStmtLstAssignTable.end()) {
		stmtSet = varExist->second;
	}
	stmtSet.insert(std::to_string(stmtNum));
	varStmtLstAssignTable[varName] = stmtSet;
}

std::vector<std::string> Assign::getAllAssignments() {
	std::vector<std::string> res;

	for (auto& assignment : stmtVarAssignTable) {
		res.push_back(std::to_string(assignment.first));
	}

	return res;
}

std::vector<std::string> Assign::getStmtLstByVarAssignment(std::string varName) {
	std::unordered_map<std::string, std::unordered_set<std::string>>::const_iterator varExist =
		varStmtLstAssignTable.find(varName);
	std::vector<std::string> res;

	if (varExist != varStmtLstAssignTable.end()) {
		std::unordered_set<std::string> stmtLst = varExist->second;
		for (auto& stmt : stmtLst) {
			res.push_back(stmt);
		}
	}
	return res;
}

std::vector<std::string> Assign::getAssignmentFromStmtIdx(StmtIndex stmtNum) {
	std::vector<std::string> res;
	std::unordered_map<StmtIndex, std::string>::const_iterator stmtExist = stmtVarAssignTable.find(stmtNum);
	if (stmtExist != stmtVarAssignTable.end()) {
		res = { stmtExist->second };
	}
	return res;
}
