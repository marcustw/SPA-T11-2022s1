
#include "ModifiesS.h"

ModifiesS::ModifiesS() {}

void ModifiesS::insertModifiesS(StmtIndex stmtNum, std::vector<std::string> varLst) {
	std::string stmt = std::to_string(stmtNum);
	std::unordered_map<std::string, std::unordered_set<std::string>>::const_iterator stmtExist =
		modifiesSStmtVarTable.find(stmt);
	std::unordered_set<std::string> varSet;
	if (stmtExist != modifiesSStmtVarTable.end()) {
		varSet = stmtExist->second;
	}
	for (auto& variable : varLst) {
		varSet.insert(variable);
		std::unordered_map<std::string, std::unordered_set<std::string>>::const_iterator varExist =
			modifiesSVarStmtLstTable.find(variable);
		std::unordered_set<std::string> stmtSet;
		if (varExist != modifiesSVarStmtLstTable.end()) {
			stmtSet = varExist->second;
		}
		stmtSet.insert(stmt);
		modifiesSVarStmtLstTable[variable] = stmtSet;
	}
	modifiesSStmtVarTable[stmt] = varSet;
}

std::vector<std::string> ModifiesS::getModifiesSLeftArgLst(std::string varName) {
	std::vector<std::string> res;
	std::unordered_map<std::string, std::unordered_set<std::string>>::const_iterator varExist =
		modifiesSVarStmtLstTable.find(varName);
	if (varExist != modifiesSVarStmtLstTable.end()) {
		std::unordered_set<std::string> stmtSet = varExist->second;
		res = std::vector<std::string>(stmtSet.begin(), stmtSet.end());
	}
	return res;
}

std::vector<std::string> ModifiesS::getModifiesSRightArgLst(StmtIndex stmtNum) {
	std::vector<std::string> res;
	std::unordered_map<std::string, std::unordered_set<std::string>>::const_iterator stmtExist =
		modifiesSStmtVarTable.find(std::to_string(stmtNum));
	if (stmtExist != modifiesSStmtVarTable.end()) {
		std::unordered_set<std::string> stmtSet = stmtExist->second;
		res = std::vector<std::string>(stmtSet.begin(), stmtSet.end());
	}
	return res;
}

std::unordered_map<std::string, std::vector<std::string>> ModifiesS::getModifiesSTable() {
	std::unordered_map<std::string, std::vector<std::string>> res;
	for (auto& row : modifiesSStmtVarTable) {
		std::string key = row.first;
		std::unordered_set<std::string> valueSet = row.second;
		std::vector<std::string> valueLst = std::vector<std::string>(valueSet.begin(), valueSet.end());
		res.insert({ key, valueLst });
	}
	return res;
}
