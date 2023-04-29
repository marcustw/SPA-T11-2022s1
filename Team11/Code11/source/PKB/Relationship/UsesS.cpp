
#include "UsesS.h"

UsesS::UsesS() {}

void UsesS::insertUsesS(StmtIndex stmtNum, std::vector<std::string> varLst) {
	std::string stmt = std::to_string(stmtNum);
	std::unordered_map<std::string, std::unordered_set<std::string>>::const_iterator stmtExist =
		usesSStmtVarLstTable.find(std::to_string(stmtNum));
	std::unordered_set<std::string> varSet;
	if (stmtExist != usesSStmtVarLstTable.end()) {
		varSet = stmtExist->second;
	}
	for (auto& variable : varLst) {
		varSet.insert(variable);
		std::unordered_map<std::string, std::unordered_set<std::string>>::const_iterator varExist =
			usesSVarStmtLstTable.find(variable);
		std::unordered_set<std::string> stmtSet;
		if (varExist != usesSVarStmtLstTable.end()) {
			stmtSet = varExist->second;
		}
		stmtSet.insert(std::to_string(stmtNum));
		usesSVarStmtLstTable[variable] = stmtSet;
	}
	usesSStmtVarLstTable[stmt] = varSet;
}

std::vector<std::string> UsesS::getUsesSLeftArgLst(std::string varName) {
	std::vector<std::string> res;
	std::unordered_map<std::string, std::unordered_set<std::string>>::const_iterator varExist =
		usesSVarStmtLstTable.find(varName);
	if (varExist != usesSVarStmtLstTable.end()) {
		std::unordered_set<std::string> stmtSet = varExist->second;
		res = std::vector<std::string>(stmtSet.begin(), stmtSet.end());
	}
	return res;
}

std::vector<std::string> UsesS::getUsesSRightArgLst(StmtIndex stmtNum) {
	std::vector<std::string> res;
	std::unordered_map<std::string, std::unordered_set<std::string>>::const_iterator stmtExist =
		usesSStmtVarLstTable.find(std::to_string(stmtNum));
	if (stmtExist != usesSStmtVarLstTable.end()) {
		std::unordered_set<std::string> varSet = stmtExist->second;
		res = std::vector<std::string>(varSet.begin(), varSet.end());
	}
	return res;
}

std::unordered_map<std::string, std::vector<std::string>> UsesS::getUsesSTable() {
	std::unordered_map<std::string, std::vector<std::string>> res;
	for (auto& row : usesSStmtVarLstTable) {
		std::string key = row.first;
		std::unordered_set<std::string> valueSet = row.second;
		std::vector<std::string> valueLst = std::vector<std::string>(valueSet.begin(), valueSet.end());
		res.insert({ key, valueLst });
	}
	return res;
}
