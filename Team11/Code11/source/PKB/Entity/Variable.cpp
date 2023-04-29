
#include "Variable.h"

Variable::Variable() {}

void Variable::insertVar(StmtIndex stmtNum, std::string varName) {
	std::unordered_map<std::string, std::unordered_set<std::string>>::const_iterator stmtExist =
		stmtVarLstTable.find(std::to_string(stmtNum));
	std::unordered_set<std::string> varSet;
	if (stmtExist != stmtVarLstTable.end()) {  // stmt key found
		varSet = stmtExist->second;
	}
	varSet.insert(varName);
	stmtVarLstTable[std::to_string(stmtNum)]= varSet;
	std::unordered_map<std::string, std::unordered_set<std::string>>::const_iterator varExist =
		varStmtLstTable.find(varName);
	std::unordered_set<std::string> stmtSet;
	if (varExist != varStmtLstTable.end()) {  // var key found
		stmtSet = varExist->second;
	}
	stmtSet.insert(std::to_string(stmtNum));
	varStmtLstTable[varName] = stmtSet;
}

std::vector<std::string> Variable::getAllVars() {
	std::vector<std::string> res;
	for (auto& varStmtLst : varStmtLstTable) {
		std::string var = varStmtLst.first;
		res.push_back(var);
	}
	return res;
}

std::vector<std::string> Variable::getVarLstFromStmtIdx(StmtIndex stmtNum) {
	std::unordered_map<std::string, std::unordered_set<std::string>>::const_iterator stmtExist =
		stmtVarLstTable.find(std::to_string(stmtNum));
	std::vector<std::string> res;
	if (stmtExist != stmtVarLstTable.end()) {
		std::unordered_set<std::string> varSet = stmtExist->second;
		res = std::vector<std::string>(varSet.begin(), varSet.end());
	}
	return res;
}

