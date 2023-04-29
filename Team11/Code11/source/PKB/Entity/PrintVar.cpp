
#include "PrintVar.h"

PrintVar::PrintVar() {}

void PrintVar::insertPrint(StmtIndex stmtNum, std::string varName) {
	printVarTable.insert({ stmtNum, varName });
	std::unordered_map<std::string, std::unordered_set<std::string>>::const_iterator varExist =
		varStmtLstTable.find(varName);
	if (varExist == varStmtLstTable.end()) {
		varStmtLstTable.insert({ varName, {std::to_string(stmtNum)} });
	} else {
		std::unordered_set<std::string> stmtLst = varExist->second;
		stmtLst.insert(std::to_string(stmtNum));
		varStmtLstTable[varName] = stmtLst;
	}
}

std::vector<std::string> PrintVar::getStmtLstfromVar(std::string varName) {
	std::unordered_map<std::string, std::unordered_set<std::string>>::const_iterator stmtExist =
		varStmtLstTable.find(varName);
	std::vector<std::string> res;
	if (stmtExist != varStmtLstTable.end()) {
		std::unordered_set<std::string> stmtLst = stmtExist->second;
		for (auto& stmt : stmtLst) {
			res.push_back(stmt);
		}
	}
	return res;
}

std::vector<std::string> PrintVar::getVarfromStmtIdx(StmtIndex stmtNum) {
	std::unordered_map<StmtIndex, std::string>::const_iterator varExist = printVarTable.find(stmtNum);
	std::vector<std::string> res;
	if (varExist != printVarTable.end()) {
		res = { varExist->second };
	}
	return res;
}

std::vector<std::string> PrintVar::getAllPrints() {
	std::vector<std::string> res;

	for (auto& stmtVar : printVarTable) {
		res.push_back(std::to_string(stmtVar.first));
	}

	return res;
}

std::pair<std::vector<std::string>, std::vector<std::string>> PrintVar::getAllPrintsVarNames() {
	std::vector<std::string> res;
	std::vector<std::string> resIdx;
	for (auto& var : printVarTable) {
		res.push_back(var.second);
		resIdx.push_back(std::to_string(var.first));
	}

	return { res, resIdx };
}
