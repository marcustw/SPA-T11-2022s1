
#include "ReadVar.h"

ReadVar::ReadVar() {}

void ReadVar::insertRead(StmtIndex stmtNum, std::string varName) {
	stmtVarReadTable.insert({ stmtNum, varName });
	std::unordered_map<std::string, std::unordered_set<std::string>>::const_iterator varExist =
		varStmtLstReadTable.find(varName);
	if (varExist == varStmtLstReadTable.end()) {
		varStmtLstReadTable.insert({ varName, {std::to_string(stmtNum)} });
	} else {
		std::unordered_set<std::string> stmtLst = varExist->second;
		stmtLst.insert(std::to_string(stmtNum));
		varStmtLstReadTable[varName] = stmtLst;
	}
}

std::vector<std::string> ReadVar::getStmtLstfromVar(std::string varName) {
	std::unordered_map<std::string, std::unordered_set<std::string>>::const_iterator stmtExist =
		varStmtLstReadTable.find(varName);
	std::vector<std::string> res;
	if (stmtExist != varStmtLstReadTable.end()) {
		std::unordered_set<std::string> stmtLst = stmtExist->second;
		for (auto& stmt : stmtLst) {
			res.push_back(stmt);
		}
	}
	return res;
}

std::vector<std::string> ReadVar::getVarfromStmtIdx(StmtIndex stmtNum) {
	std::unordered_map<StmtIndex, std::string>::const_iterator varExist =
		stmtVarReadTable.find(stmtNum);
	std::vector<std::string> res;
	if (varExist != stmtVarReadTable.end()) {
		res = { varExist->second };
	}
	return res;
}

std::vector<std::string> ReadVar::getAllReads() {
	std::vector<std::string> res;
	for (auto& stmtVarLst : stmtVarReadTable) {
		res.push_back(std::to_string(stmtVarLst.first));
	}
	return res;
}

std::pair<std::vector<std::string>, std::vector<std::string>> ReadVar::getAllReadsVarName() {
	std::vector<std::string> res;
	std::vector<std::string> resIdx;
	for (auto& stmtVarLst : stmtVarReadTable) {
		res.push_back(stmtVarLst.second);
		resIdx.push_back(std::to_string(stmtVarLst.first));
	}
	return { res, resIdx };
}
